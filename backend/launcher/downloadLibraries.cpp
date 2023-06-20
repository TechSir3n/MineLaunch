#include "./include/downloadLibraries.hpp"

DownloadLibraries::DownloadLibraries(QObject *parent)
    : QObject(parent), m_manager(new QNetworkAccessManager()) {}

DownloadLibraries::~DownloadLibraries() { delete m_manager; }

void DownloadLibraries::downloadLibraries(const QString &versionGame) noexcept {
  const QString path = QCoreApplication::applicationDirPath() + "/../" +
                       "/MineLaunch/backend/launcher/minecraft/versions/";
  QDir dir(path);

  QStringList dirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
  if (dirs.contains(versionGame)) {
    QFile file(path + versionGame + "/" + "version.json");
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
      const auto &urlString = obj["downloads"]["artifact"]["url"].toString();
      if (!urlString.contains("windows") && !urlString.contains("macos")) {
        urls.push_back(QUrl(urlString));
      }
    }
  }
  const QString savePath = QCoreApplication::applicationDirPath() +
                           QDir::separator() + ".." + QDir::separator() +
                           "/MineLaunch/backend/launcher/minecraft/libraries/";
  QDir librariesDir(savePath);
  if (!librariesDir.exists()) {
    qDebug() << "like this directory doesn't exits";
    return;
  }
  librariesDir.mkdir(versionGame);

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

                       if (progress == 0) {
                         emit onFinished();
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
