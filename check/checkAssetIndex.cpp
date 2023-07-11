#include "./include/checkAssetIndex.hpp"
#include "./assistance/path.hpp"

[[nodiscard]] QString CheckAssetIndex::getAssetIndexSHA() const noexcept {
  QFile file(Path::assetIndexPath() + QDir::separator() + m_version);
  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << "Open file for readOnly [getAssetIndexSHA]";
    return QString();
  }

  QCryptographicHash hash(QCryptographicHash::Sha1);
  if (hash.addData(&file)) {
    QByteArray result = hash.result();
    return result.toHex();
  } else {
    throw ErrorCalculateHash("Failed to calculate hash [getAssetIndexSHA]");
  }
}

void CheckAssetIndex::setVersionAssetIndex(const QString &version) {
  m_version = version;
}
