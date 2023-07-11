#pragma once

#include "../../exception/exception.hpp"
#include <QCryptographicHash>
#include <QFile>
#include <QObject>

class CheckClient : public QObject {
  Q_OBJECT
public:
  explicit CheckClient(QObject *parent = nullptr) : QObject(parent) {}

  ~CheckClient() = default;

  [[nodiscard]] QString getClientSHA() const noexcept;

public slots:
  void setVersionClient(const QString &version);

private:
  QString m_version;
};
