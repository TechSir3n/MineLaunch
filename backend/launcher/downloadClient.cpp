#include "./include/downloadClient.hpp"
#include "./assistance/path.hpp"

DownloadClient::DownloadClient(QObject *parent)
    : QObject(parent), m_process(new QProcess()), m_client(new CheckClient()) {
  moveToThread(parent->thread());
  m_manager = new QNetworkAccessManager(this);

  QObject::connect(this, &DownloadClient::sendVersion, m_client,
                   &CheckClient::setVersionClient);
}

DownloadClient::~DownloadClient() {
  delete m_process;
  delete m_client;
}

void DownloadClient::downloadClient(const QString &versionClient) {
  const QString path = Path::versionPath() + QDir::separator();
  QDir dir(path);
  QStringList dirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
  if (dirs.contains(versionClient)) {
    const QString filePath = dir.filePath(versionClient + "/version.json");
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
      throw OpenFileException("Failed open file for read [downloadClient]" +
                              file.errorString().toStdString());
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

    QJsonValue shaValue = obj.value("downloads")
                              .toObject()
                              .value("client")
                              .toObject()
                              .value("sha1");
    QString realSha = shaValue.toString();

    QNetworkRequest request(clientValue.toString());
    QNetworkReply *reply = m_manager->get(request);
    getReply(reply);

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    QObject::connect(
        reply, &QNetworkReply::downloadProgress, this,
        [=](qint64 bytesReceived, qint64 bytesTotal) {
          int progress =
              (bytesTotal > 0) ? (bytesReceived * 100 / bytesTotal) : 0;
          emit progressChanged(progress);
          emit sendVersion(versionClient);

          if (bytesReceived == bytesTotal) {
            QString shaClientFile = m_client->getClientSHA();
            if (shaClientFile == realSha) {
              emit onFinished();
            } else {
              emit errorDownloadClient(
                  tr("The file client.jar was installed but not fully, "
                     "the hash amount does not match"));
            }
          }
        });

    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
      emit errorDownloadClient(reply->errorString());
      return;
    } else {
      const QString fileName = "client.jar";
      QFile fileSave(path + versionClient + QDir::separator() + fileName);
      if (fileSave.open(QIODevice::WriteOnly)) {
        fileSave.write(reply->readAll());
        fileSave.close();

      } else {
        throw OpenFileException("Error open file for write [downloadClient]" +
                                fileSave.errorString().toStdString());
      }

      file.close();
      reply->deleteLater();
    }
  } else {
    throw OpenDirectoryException("Path doesn't exists");
  }
}

QNetworkReply *DownloadClient::getReply(QNetworkReply *reply) noexcept {
  return reply;
}

void DownloadClient::stopIsDownloadingClient() {
  auto reply = getReply();
  reply->abort();
}
