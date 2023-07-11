#include "./include/checkLibraries.hpp"
#include "./assistance/path.hpp"

[[nodiscard]] QVector<QString>
CheckLibraries::getLibrariesSHA() const noexcept {
  const QString path = Path::librariesPath() + QDir::separator() + m_version;
  QDir dir(path);
  if (!dir.exists()) {
    qDebug() << "Dir path doesn't exists [getLibrariesSHA]";
    return QVector<QString>();
  }

  foreach (const QString &fileName, dir.entryList(QDir::Files)) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
      qDebug() << "Failed to open file for read [getLibrariesSHA]";
      return QVector<QString>();
    }

    QCryptographicHash hash(QCryptographicHash::Sha1);
    if (hash.addData(&file)) {
      QByteArray result = hash.result();
      m_hashes.emplace_back(result.toHex());
    } else {
      throw ErrorCalculateHash("Failed to calculate Hash [getLibrariesSHA]");
    }
  }

  return m_hashes;
}

void CheckLibraries::setVersionLibraries(const QString &version) {
  m_version = version;
}
