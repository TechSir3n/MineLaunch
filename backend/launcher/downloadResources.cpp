#include "./include/downloadResources.hpp"
#include "assistance/path.hpp"

DownloadResources::DownloadResources(QObject *parent)
    : QObject(parent), m_manager(new QNetworkAccessManager()) {}

void DownloadResources::downloadResources(const QString &versionHash) {
  const QString path = Path::launcherPath() + "/../" +
                       "/MineLaunch/backend/launcher/minecraft/assets/indexes/";

  QFile file(path + versionHash + ".json");
  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << "Failed open file for read [downloadResources] "
             << file.errorString();
    return;
  }

  QByteArray data = file.readAll();
  QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
  QJsonObject jsonObj = jsonDoc.object();
  QJsonObject objectsObj = jsonObj.value("objects").toObject();

  for (const auto &key : objectsObj.keys()) {
    QJsonObject obj = objectsObj.value(key).toObject();
    QString hashValue = obj.value("hash").toString();
    hashes.push_back(hashValue);
  }

  const QString savePath =
      Path::launcherPath() + "/../" +
      "/MineLaunch/backend/launcher/minecraft/assets/objects/";
  QDir saveDir(savePath);
  if (!saveDir.exists()) {
    qDebug() << "Error directory,inccorect enter path or it doesn't exists";
    return;
  }

  for (const auto &hash : hashes) {
    QString prefix = hash.left(2);
    QString dirPath = saveDir.filePath(prefix);
    QDir dir(dirPath);
    if (!dir.exists()) {
      if (!dir.mkpath(dirPath)) {
        qDebug() << "Error creating directory: " << dirPath;
        return;
      }
    }

    QNetworkRequest request(QString(HTTP) + "/" + prefix + "/" + hash);
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
      emit errorDownloadResources("Error downloading resources: " +
                                  reply->errorString());
      return;
    }

    QString fileName = hash;
    QString filePath = dir.filePath(fileName);
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
      qDebug() << "Error open file[downloadResources]: " << file.errorString();
      return;
    }

    file.write(reply->readAll());
    file.close();
    reply->deleteLater();
  }
}

void DownloadResources::stopIsDownloadingResources() {
  auto reply = getReply();
  reply->abort();
}

DownloadResources::~DownloadResources() { delete m_manager; }

QNetworkReply *DownloadResources::getReply(QNetworkReply *reply) noexcept {
  return reply;
}
