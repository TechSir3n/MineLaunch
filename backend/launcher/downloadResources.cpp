#include "./include/downloadResources.hpp"
#include "assistance/path.hpp"

DownloadResources::DownloadResources(QObject *parent)
    : QObject(parent), m_manager(new QNetworkAccessManager()) {}

void DownloadResources::downloadResources(const QString &versionGame) {
  const QString path = Path::launcherPath() + "/../" +
                       "/MineLaunch/backend/launcher/minecraft/assets/indexes/";

  QDir dir(path);
  QStringList dirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
  if (dirs.contains(versionGame)) {
    QFile file(path + versionGame + "/" + "version.json");
    if (!file.open(QIODevice::ReadOnly)) {
      qDebug() << "Failed open file for read [downloadResources] "
               << file.errorString();
      return;
    }

    QByteArray data = file.readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();
    QJsonObject objectsObj = jsonObj.value("objects").toObject();

    for (const auto& key : objectsObj.keys()) {
      QJsonObject obj = objectsObj.value(key).toObject();
      QString hashValue = obj.value("hash").toString();
      hashes.push_back(hashValue);
    }

  }


  for(const auto &hash:hashes) {
    QString firstTwoChars = hash.left(2);
    QString restOfChars = hash.mid(2);

    QNetworkRequest request(HTTP + "/" + firstTwoChars + "/" + restOfChars);
    QNetworkReply *reply = m_manager->get(request);
    getReply(reply);

    QEventLoop loop;
    QObject::connect(reply,&QNetworkReply::finished,loop,&QEventLoop::quit);
    loop.exec();

    if(reply->error()!=QNetworkReply::NoError) {
      emit errorDownloadResources("Error downloading resources: " + reply->errorString());
      return;
    }


    const QString savePath = Path::launcherPath() + "/../" +"/MineLaunch/backend/launcher/minecraft/assets/objects/";
    QDir saveDir(savePath);
    if(!saveDir.exists()) {
      qDebug() << "Error directory,inccorect enter path or it doesn't exists";
      return;
    }

    if(!saveDir.mkdir(versionGame)){
      qDebug() <<"Error create directory,maybe it created already";
      return;
    }

    QFile file(savePath + versionGame + "/");
    if(!file.open(QIODevice::WriteOnly)) {
      qDebug() <<"Error open file[downloadResources]: " << file.errorString();
      return;
    }

    file.write(reply->readAll());
    reply->deleteLater();
    file.close();
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
