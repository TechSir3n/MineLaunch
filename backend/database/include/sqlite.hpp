#pragma once

#include "../../../assistance/logger.hpp"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QToolTip>
#include <QtSql>

class Database : public QObject {
private:
  Database(QObject *parent = nullptr);

  ~Database();

  Database(const Database &) = delete;

  Database &operator=(const Database &) = delete;

public:
  static Database &getInstance() {
    static Database instance;
    return instance;
  }

public:
  bool initDatabase();

  bool insertUserData(const QString &username, const QString &email,
                      const QString &password);

  bool updateNameUser(const QString &newName, const QString &email);

  bool updatePasswordUser(const QString &newPassword, const QString &email);

  std::tuple<QString, QString, QString> searchUserByEmail(const QString &email);

  void showData() const noexcept;

private:
  Logger logger;
  QSqlDatabase db;
};
