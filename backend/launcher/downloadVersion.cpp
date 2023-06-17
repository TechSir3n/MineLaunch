#include "./include/downloadVersion.hpp"

DownloadVersion::DownloadVersion(QObject *parent)
    : QObject(parent), m_manager(new QNetworkAccessManager()) {}

DownloadVersion::~DownloadVersion() { delete m_manager; }

void DownloadVersion::downloadVersion(const QString &versionGame) noexcept {

  m_versionGame = versionGame;

  QUrl url(versionGame);
  QNetworkRequest request(url);
  QNetworkReply *reply = m_manager->get(request);

  QEventLoop loop;

  QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
  loop.exec();

  if (reply->error() != QNetworkReply::NoError) {
    qDebug() << "Error download version: " << reply->errorString();
    return;
  }

  QString fileName = url.fileName();
  QStringList parts = fileName.split("/");
  QString version = parts.last().replace(".json", "");


  const QString path = QCoreApplication::applicationDirPath() + "/../" + "/MineLaunch/backend/launcher/minecraft/versions/";
  QDir dir(path);
  if (!dir.exists()) {
    qDebug() << "Directory doesn't exists";
    return ;
  }

  if (!dir.mkdir(version)) {
    qDebug() << "Error creating directory: " << version;

    return ;
  }

  QFile file;
  file.setFileName(path + version + "/version.json");
  if (!file.open(QIODevice::WriteOnly)) {
    qDebug() << "Error open file for write: " << file.errorString();
    return ;
  }

  file.write(reply->readAll());
  file.close();

}

QString DownloadVersion::getVersionGame() const noexcept {
  return m_versionGame;
}


//  QObject::connect(reply, &QNetworkReply::finished,
//                   [&](qint64 byteReceived, qint64 bytesTotal) {
//                     int progress =
//                         static_cast<int>(byteReceived * 100 / bytesTotal);
//                     emit progressChanged(progress);
//                   });
