#include "./include/downloadVersion.hpp"
#include "assistance/path.hpp"

DownloadVersion::DownloadVersion(QObject *parent) : QObject(parent) {
  moveToThread(parent->thread());
  m_manager = new QNetworkAccessManager(this);
}

DownloadVersion::~DownloadVersion() {}

void DownloadVersion::downloadVersion(const QString &versionGame) noexcept {
  m_versionGame = versionGame;

  QUrl url(versionGame);
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

                     if (bytesReceived == bytesTotal) {
                       emit onFinished();
                     }
                   });

  loop.exec();

  if (reply->error() != QNetworkReply::NoError) {
    emit errorDownloadVersion(reply->errorString());
    return;
  }

  QString fileName = url.fileName();
  QStringList parts = fileName.split("/");
  QString version = parts.last().replace(".json", "");

  const QString path = QDir::cleanPath(Path::versionPath() + QDir::separator());
  QDir dir(path);
  if (!dir.exists()) {
    throw OpenDirectoryException("Directory doesn't exists");
  }

  if (!dir.mkdir(version)) {
    throw OpenDirectoryException("Error creating directory: " +
                                 version.toStdString());
  }

  const QString filePath = dir.filePath(version + "/version.json");
  QFile file(filePath);
  if (!file.open(QIODevice::WriteOnly)) {
    throw OpenFileException("Error open file for write: " +
                            file.errorString().toStdString());
  }

  try {
    file.write(reply->readAll());
    file.close();
  } catch (const std::exception &e) {
    qDebug() << "Error writing to file: " << e.what();
    file.remove();
    return;
  }

  reply->deleteLater();
}

QString DownloadVersion::getVersionGame() const noexcept {
  return m_versionGame;
}

QNetworkReply *DownloadVersion::getReply(QNetworkReply *reply) noexcept {
  return reply;
}

void DownloadVersion::stopIsDownloadingVersion() {
  auto reply = getReply();
  reply->abort();
}
