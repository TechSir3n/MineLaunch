#pragma once

#include "../../../utils/logger.hpp"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class Database : public QObject  {
public:
    Database(QObject *parent = nullptr);

   ~Database();

private:
   bool initDatabase();

   bool insertUserData(const QString &username,const QString&email,const QString&password);

   bool updateUserData();

   bool searchUserByEmail(const QString &email);

private:
   Logger logger;
   QSqlDatabase db;
};
