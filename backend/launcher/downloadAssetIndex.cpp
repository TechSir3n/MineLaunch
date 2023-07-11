#include "./include/downloadAssetIndex.hpp"
#include "./assistance/path.hpp"

DownloadAssetIndex::DownloadAssetIndex(QObject *parent)
    : QObject(parent), m_index(new CheckAssetIndex()) {
  moveToThread(parent->thread());
  m_manager = new QNetworkAccessManager(this);


  QObject::connect(this, &DownloadAssetIndex::sendVersion, m_index,
                   &CheckAssetIndex::setVersionAssetIndex);
}

DownloadAssetIndex::~DownloadAssetIndex() { delete m_index; }

void DownloadAssetIndex::downloadAssetIndex(const QString &versionGame) {
  const QString path = Path::versionPath() + QDir::separator();
  QDir dir(path);
  QStringList dirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
  if (dirs.contains(versionGame)) {
    QFile file;
    file.setFileName(path + versionGame + "/version.json");
    if (!file.open(QIODevice::ReadOnly)) {
      throw OpenFileException("Failed open file for read [downloadAssetIndex]" +
                              file.errorString().toStdString());
    }

    QByteArray jsonData = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    QJsonObject obj = doc.object();
    QJsonValue assetIndexValue =
        obj.value("assetIndex").toObject().value("url");
    QString httpHashVersion = assetIndexValue.toString().split("/").last();

    QJsonValue indexValueSha = obj.value("assetIndex").toObject().value("sha1");
    QString realSha = indexValueSha.toString();

    QNetworkRequest request(assetIndexValue.toString());
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
          emit sendVersion(versionGame);

          if (bytesReceived == bytesTotal) {
            QString hash = m_index->getAssetIndexSHA();
            if (hash == realSha) {
              emit onFinished();
            } else {
              emit errorDownloadAssetIndex(
                  tr("The file assetIndex was installed but not fully, "
                     "the hash amount does not match"));
            }
          }
        });

    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
      emit errorDownloadAssetIndex("Error download asset index :" +
                                   reply->errorString());
      return;
    }

    QDir saveDir(Path::assetIndexPath() + QDir::separator());
    if (!saveDir.exists()) {
      throw OpenDirectoryException(
          "Directory where you wanted saved doesn't exists "
          "[downloadAssetIndex]");
    }

    QFile saveFile(Path::assetIndexPath() + QDir::separator() +
                   httpHashVersion);
    if (!saveFile.open(QIODevice::WriteOnly)) {
      throw OpenFileException(
          "Failed to open file for write [downloadAssetIndex]:" +
          saveFile.errorString().toStdString());
    }

    saveFile.write(reply->readAll());
    saveFile.close();
    reply->deleteLater();
  }
}

void DownloadAssetIndex::stopIsDownloadingAssetIndex() {
  auto reply = getReply();
  reply->abort();
}

QNetworkReply *DownloadAssetIndex::getReply(QNetworkReply *reply) noexcept {
  return reply;
}
