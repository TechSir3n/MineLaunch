#include "./include/downloadClient.hpp"

DownloadClient::DownloadClient(QObject *object)
    : QObject(object), m_manager(new QNetworkAccessManager()),
      m_process(new QProcess()) {}

DownloadClient::~DownloadClient() {
  delete m_manager;
  delete m_process;
}

void DownloadClient::downloadClient(const QString &versionClient) {
  const QString path = QCoreApplication::applicationDirPath() + "/../" +
                       "/MineLaunch/backend/launcher/minecraft/versions/";
  QDir dir(path);
  QStringList dirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
  if (dirs.contains(versionClient)) {
    QFile file;
    file.setFileName(path + versionClient + "/version.json");

    if (!file.open(QIODevice::ReadOnly)) {
      qDebug() << "Failed open file for read [downloadClient]"
               << file.errorString();
      return;
    }

    QByteArray jsonData = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    QJsonObject obj = doc.object();
    QJsonValue clientValue = obj.value("downloads")
                                 .toObject()
                                 .value("client")
                                 .toObject()
                                 .value("url")
                                 .toString();

    QNetworkRequest request(clientValue.toString());
    QNetworkReply *reply = m_manager->get(request);

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
      qDebug() << "Reply: " << reply->errorString();
      return;
    } else {
      const QString fileName = "client.jar";
      QFile fileSave(path + versionClient + "/" + fileName);

      if (fileSave.open(QIODevice::WriteOnly)) {
        fileSave.write(reply->readAll());
        fileSave.close();

      } else {
        qDebug() << "Error open file for write [downloadClient]"
                 << fileSave.errorString();
        return;
      }

      file.close();
      reply->deleteLater();
    }
  } else {
    qDebug() << "path doesn't exists";
    return;
  }
}

//    QObject::connect(reply, &QNetworkReply::finished,[&](qint64
//    byteReceived,qint64 bytesTotal)  {
//       int progress= static_cast<int>(byteReceived * 100 / bytesTotal);
//         emit progressChanged(progress);
//    });
