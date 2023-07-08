#include "./include/checkAssets.hpp"
#include "./assistance/path.hpp"

[[nodiscard]] QVector<QString> CheckAssets::getAssetsSHA() const noexcept {
  QDir objectsDir(Path::assetsPath() + QDir::separator());
  if (!objectsDir.exists()) {
    qDebug() << "Dir path doesn't exists";
    return QVector<QString>();
  }

  foreach (const auto &dir,
           objectsDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
    QDir currentDir(objectsDir.absoluteFilePath(dir));
    for (const auto &file : currentDir.entryList(QDir::Files)) {
      QString fileName = currentDir.filePath(file).split("/").last();
      m_hashes.emplace_back(fileName);
    }
  }

  return m_hashes;
}
