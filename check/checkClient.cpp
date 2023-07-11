#include "./include/checkClient.hpp"
#include "./assistance/path.hpp"

[[nodiscard]] QString CheckClient::getClientSHA() const noexcept {
  QFile file(Path::clientPath() + QDir::separator() + m_version +
             QDir::separator() + "client.jar");

  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << "Failed open file for readOnly [getClientSHA]";
    return QString();
  }

  QCryptographicHash hash(QCryptographicHash::Sha1);

  if (hash.addData(&file)) {
    QByteArray result = hash.result();
    return result.toHex();
  } else {
    throw ErrorCalculateHash("Failed to calculate hash [getClientSHA]");
  }
}

void CheckClient::setVersionClient(const QString &version) {
  m_version = version;
}
