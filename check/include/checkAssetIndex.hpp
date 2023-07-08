#pragma once

#include <QCryptographicHash>
#include <QFile>
#include <QObject>

class CheckAssetIndex : public QObject {
public:
  explicit CheckAssetIndex(QObject *parent = nullptr) : QObject(parent) {}

  ~CheckAssetIndex() = default;

  [[nodiscard]] QString getAssetIndexSHA() const noexcept;

public slots:
  void setVersionAssetIndex(const QString &version);

private:
  QString m_version;
};
