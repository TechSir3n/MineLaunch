#include "./include/downloadVersion.hpp"

DownloadVersion::DownloadVersion(QObject *parent)
    : QObject(parent), m_manager(new QNetworkAccessManager()) {}

DownloadVersion::~DownloadVersion() { delete m_manager; }

void DownloadVersion::downloadVersion(const QString &versionGame) noexcept {
<<<<<<< HEAD
=======
  m_versionGame = versionGame;
>>>>>>> 21eb63f (commit)
  QUrl url(versionGame);
  QNetworkRequest request(url);
  QNetworkReply *reply = m_manager->get(request);

  QEventLoop loop;

//  QObject::connect(reply, &QNetworkReply::finished,
//                   [&](qint64 byteReceived, qint64 bytesTotal) {
//                     int progress =
//                         static_cast<int>(byteReceived * 100 / bytesTotal);
//                     emit progressChanged(progress);
//                   });

  QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
  loop.exec();

  if (reply->error() != QNetworkReply::NoError) {
    qDebug() << "Error download version: " << reply->errorString();
    return;
  }

  QString fileName = url.fileName();
  QStringList parts = fileName.split("/");
  QString version = parts.last().replace(".json", "");

<<<<<<< HEAD
  const QString path = QCoreApplication::applicationDirPath() + "/../" + "/MineLaunch/backend/launcher/minecraft/versions/";
  QDir dir(path);
  if (!dir.exists()) {
    qDebug() << "Directory doesn't exists";
    return ;
=======
  const QString path = QCoreApplication::applicationDirPath() + "/../" +
                       "/MineLaunch/backend/launcher/minecraft/versions/";
  QDir dir(path);
  if (!dir.exists()) {
    qDebug() << "Directory doesn't exists";
    return;
>>>>>>> 21eb63f (commit)
  }

  if (!dir.mkdir(version)) {
    qDebug() << "Error creating directory: " << version;
<<<<<<< HEAD
    return ;
=======
    return;
>>>>>>> 21eb63f (commit)
  }

  QFile file;
  file.setFileName(path + version + "/version.json");
  if (!file.open(QIODevice::WriteOnly)) {
    qDebug() << "Error open file for write: " << file.errorString();
<<<<<<< HEAD
    return ;
=======
    return;
>>>>>>> 21eb63f (commit)
  }

  file.write(reply->readAll());
  file.close();

<<<<<<< HEAD
  return ;
=======
  return;
}

QString DownloadVersion::getVersionGame() const noexcept {

  return m_versionGame;
>>>>>>> 21eb63f (commit)
}
