#pragma once

#include "../include/smtp.hpp"
#include "./frontend/include/user_settings.hpp"
#include "assistance/hashing.hpp"
#include "assistance/logger.hpp"
#include "assistance/validator.hpp"
#include "backend/database/include/sqlite.hpp"
#include "server.hpp"
#include <QJsonObject>
#include <QMessageBox>
#include <QObject>
#include <cstdlib>
#include <ctime>

class DataHandler : public QObject {
  Q_OBJECT
public:
  explicit DataHandler(QObject *parent = nullptr);

  ~DataHandler();

signals:
  void sendString(const QString &str);

  void sendUsername(const QString &name, const QString &email,
                    const QString &password);

public slots:
  void dataHandler(const QJsonObject &object);

private:
  Logger logger;
  Smtp smtp;
  Validator valid;
  Hash hash;
};
