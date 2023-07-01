#pragma once

#include <QCryptographicHash>
#include <cstring>
#include <iostream>

class Hash {
public:
  Hash() = default;

  ~Hash() = default;

public:
  [[nodiscard]] QString toHash(const QString &password) const noexcept {
      try {
    QByteArray hash =
          QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
          return QString(hash.toHex());
      } catch(const std::exception &ex) {
          qCritical() << "Exception caught: " << ex.what();
      }
  }

  [[nodiscard]] bool comparePassword(const QString &password,
                                  const QString& hash) const noexcept {
    QString hashedPassword = toHash(password);
    return (hashedPassword == hash);
  }
};
