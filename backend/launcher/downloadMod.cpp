#include "./include/downloadMod.hpp"
#include "./assistance/path.hpp"

DownloadMod::DownloadMod(QObject *parent)
    : QObject(parent), m_manager(new QNetworkAccessManager()) {}

DownloadMod::~DownloadMod() { delete m_manager; }

void DownloadMod::setUrlAddressMod(const QString &url) {
  QUrl qurl(url);
  QNetworkRequest request(qurl);
  QNetworkReply *reply = m_manager->get(request);

  QEventLoop loop;
  QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

  if (reply->error() != QNetworkReply::NoError) {
    emit errorDownloadMod(reply->errorString());
    return;
  }

  loop.exec();

  const QString path = Path::minecraftPath() + "/mods";
  QString contentType =
      reply->header(QNetworkRequest::ContentTypeHeader).toString();

  if (contentType == JAR || contentType == OCTET) {
    QString fileName = url.split("/").last();
    QFile file(path + QDir::separator() + fileName);
    if (!file.open(QIODevice::WriteOnly)) {
      qDebug() << "Error open for writeOnly [downloadMod]"
               << file.errorString();
      return;
    } else {
      file.write(reply->readAll());
      file.close();
    }

  } else {
    emit errorDownloadMod("Unknow type file's mod");
    return;
  }

  reply->deleteLater();
}
