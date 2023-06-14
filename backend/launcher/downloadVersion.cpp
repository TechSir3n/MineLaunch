#include "./include/downloadVersion.hpp"

DownloadVersion::DownloadVersion(QObject *parent)
    : QObject(parent), m_manager(new QNetworkAccessManager()) {}

DownloadVersion::~DownloadVersion() { delete m_manager; }

bool DownloadVersion::downloadVersion(const QString &versionGame) noexcept {
  QUrl url(versionGame);
  QNetworkRequest request(url);
  QNetworkReply *reply = m_manager->get(request);

  QEventLoop loop;
  connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
  loop.exec();

  if (reply->error() != QNetworkReply::NoError) {
    qDebug() << "Error download version: " << reply->errorString();
    return false;
  }

  QString fileName = url.fileName();
  QStringList parts = fileName.split("/");
  QString version = parts.last().replace(".json", "");

  const QString path =
      "/home/ruslan/Documents/MineLaunch/backend/launcher/minecraft/versions/";
  QDir dir(path);
  if (!dir.exists()) {
    qDebug() << "Directory doesn't exists";
    return false;
  }

  if (!dir.mkdir(version)) {
    qDebug() << "Error creating directory: " << version;
    return false;
  }

  QFile file;
  file.setFileName(path + version + "/version.json");
  if (!file.open(QIODevice::WriteOnly)) {
    qDebug() << "Error open file for write: " << file.errorString();
    return false;
  }

  file.write(reply->readAll());
  file.close();

  return true;
}
