#pragma once

#include "../../exception/exception.hpp"
#include <QCryptographicHash>
#include <QDir>
#include <QFile>
#include <QObject>

class CheckAssets : public QObject {
public:
  explicit CheckAssets(QObject *parent = nullptr) : QObject(parent) { }

  ~CheckAssets() = default;

  [[nodiscard]] QVector<QString> getAssetsSHA() const noexcept;

private:
  QString m_version;
  mutable QVector<QString> m_hashes;
};


