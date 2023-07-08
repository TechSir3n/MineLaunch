#pragma once

#include <QCryptographicHash>
#include <QDir>
#include <QFile>
#include <QObject>
#include <QVector>

class CheckLibraries : public QObject {
public:
  explicit CheckLibraries(QObject *parent = nullptr) : QObject(parent) {}

  ~CheckLibraries() = default;

  [[nodiscard]] QVector<QString> getLibrariesSHA() const noexcept;

public slots:
  void setVersionLibraries(const QString &version);

private:
  QString m_version;
  mutable QVector<QString> m_hashes;
};
