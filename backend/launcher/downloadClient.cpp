#include "./include/downloadClient.hpp"

DownloadClient::DownloadClient(QObject *object)
    : QObject(object), m_manager(new QNetworkAccessManager()),
      m_process(new QProcess()) {}

DownloadClient::~DownloadClient() { delete m_manager; }

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
<<<<<<< HEAD
=======
//    QObject::connect(reply, &QNetworkReply::finished,[&](qint64 byteReceived,qint64 bytesTotal)  {
//       int progress= static_cast<int>(byteReceived * 100 / bytesTotal);
//         emit progressChanged(progress);
//    });

>>>>>>> 21eb63f (commit)
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
      return;
    } else {
      const QString fileName = "client.jar";
      QFile fileSave(path + versionClient + "/"  +  fileName);
<<<<<<< HEAD



      if (fileSave.open(QIODevice::WriteOnly)) {
        fileSave.write(reply->readAll());

        fileSave.close();

=======
      if (fileSave.open(QIODevice::WriteOnly)) {
        fileSave.write(reply->readAll());
        fileSave.close();
>>>>>>> 21eb63f (commit)
      } else {

        return;
      }
    }

<<<<<<< HEAD

=======
>>>>>>> 21eb63f (commit)
    file.close();
    reply->deleteLater();
  } else {

    return;
  }

<<<<<<< HEAD

=======
>>>>>>> 21eb63f (commit)
}
