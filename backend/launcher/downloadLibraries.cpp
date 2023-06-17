#include "./include/downloadLibraries.hpp"

<<<<<<< HEAD
DownloadLibraries::DownloadLibraries(QObject *object) : QObject(object),m_manager(new QNetworkAccessManager())
{

}

DownloadLibraries::~DownloadLibraries()
{
    delete m_manager;
}


void DownloadLibraries::downloadLibraries(const QString &versionGame) noexcept
{
    const QString path = QCoreApplication::applicationDirPath() + "/../" + "/MineLaunch/backend/launcher/minecraft/versions";
    QDir dir(path);

    QStringList dirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    if(dirs.contains(versionGame)) {
            //QFile file("");

    }
=======
DownloadLibraries::DownloadLibraries(QObject *object)
    : QObject(object), m_manager(new QNetworkAccessManager()) {}
>>>>>>> 21eb63f (commit)

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
      qDebug() << "URL:" << urlString;
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

    QEventLoop loop;
//    QObject::connect(reply, &QNetworkReply::finished,
//                     [&](qint64 byteReceived, qint64 bytesTotal) {
//                       int progress =
//                           static_cast<int>(byteReceived * 100 / bytesTotal);
//                       emit progressChanged(progress);
//                     });

    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
      qDebug() << "Reply Error: " << reply->errorString();
      return;
    }

    QString fileName = url.toString().split("/").last();
    QString filePath =
        librariesDir.filePath(versionGame + QDir::separator() + fileName);
    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly)) {
      file.write(reply->readAll());
      file.close();
      qDebug() << "File saved to:" << filePath;
    } else {
      qDebug() << "Failed to save file";
      return;
    }

    reply->deleteLater();
  }
}

