#include "./include/downloadLibraries.hpp"
#include "./assistance/path.hpp"

DownloadLibraries::DownloadLibraries(QObject *parent)
    : QObject(parent), m_manager(new QNetworkAccessManager()),
      m_libraries(new CheckLibraries()) {

  QObject::connect(this, &DownloadLibraries::sendVersion, m_libraries,
                   &CheckLibraries::setVersionLibraries);
}

DownloadLibraries::~DownloadLibraries() {
  delete m_manager;
  delete m_libraries;
}

void DownloadLibraries::downloadLibraries(const QString &versionGame) noexcept {
  const QString path =
      QDir::cleanPath(Path::launcherPath() + "/../" +
                      "/MineLaunch/backend/launcher/minecraft/versions/");
  QDir dir(path);

  QStringList dirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
  if (dirs.contains(versionGame)) {
    const QString filePath = dir.filePath(versionGame + "/version.json");
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
      qDebug() << "Failed open file for read [downloadLibraries] "
               << file.errorString();
      return;
    }

    QByteArray jsonData = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    QJsonArray libraries = doc["libraries"].toArray();

    for (const auto &library : libraries) {
      const auto &obj = library.toObject();
      const auto &hash = obj["downloads"]["artifact"]["sha1"].toString();
      m_hashes.emplace_back(hash);

      const auto &urlString = obj["downloads"]["artifact"]["url"].toString();
      // to do this
      if (!urlString.contains("windows") && !urlString.contains("macos")) {
        urls.push_back(QUrl(urlString));
      }
    }
  }

  const QString savePath = QDir::toNativeSeparators(
      Path::launcherPath() + QDir::separator() + ".." + QDir::separator() +
      "/MineLaunch/backend/launcher/minecraft/libraries/");
  QDir librariesDir(savePath);
  if (!librariesDir.exists()) {
    qDebug() << "like this directory doesn't exits";
    return;
  }
  if (!librariesDir.mkdir(versionGame)) {
    qDebug() << "Error create directory,maybe it created already";
    return;
  }

  for (const auto &url : urls) {
    QNetworkRequest request(url);
    QNetworkReply *reply = m_manager->get(request);
    getReply(reply);
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    QObject::connect(reply, &QNetworkReply::downloadProgress, this,
                     [=](qint64 bytesReceived, qint64 bytesTotal) {
                       int progress = (bytesTotal > 0)
                                          ? (bytesReceived * 100 / bytesTotal)
                                          : 0;
                       emit progressChanged(progress);
                       emit sendVersion(versionGame);

                       if (progress == 0) {
                         QVector<QString> indexSHA =
                             m_libraries->getLibrariesSHA();
                         for (const QString &hash : indexSHA) {
                           if (!m_hashes.contains(hash)) {
                             emit onFinished();
                           } else {
                             emit errorDownloadLibraries(
                                 tr("Libraries was installed,but not "
                                    "full,something went wrong while installing"));
                           }
                         }
                       }
                     });

    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
      emit errorDownloadLibraries(reply->errorString());
      return;
    }

    QString fileName = url.toString().split("/").last();
    QString filePath =
        librariesDir.filePath(versionGame + QDir::separator() + fileName);
    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly)) {
      file.write(reply->readAll());
      file.close();
    } else {
      qDebug() << "Failed to save file: " << file.errorString();
      return;
    }

    reply->deleteLater();
  }
}

QNetworkReply *DownloadLibraries::getReply(QNetworkReply *reply) noexcept {
  return reply;
}

void DownloadLibraries::stopIsDownloadingLibraries() {
  auto reply = getReply();
  reply->abort();
}
