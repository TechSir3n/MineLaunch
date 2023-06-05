#pragma once

#include "../../../utils/logger.hpp"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class Database : public QObject  {
private:
    Database(QObject *parent = nullptr);

   ~Database();

    Database(const Database&) = delete;

   Database & operator=(const Database&) = delete;

public:
   static Database & getInstance() {
       static Database instance;
       return instance;
   }
public:
   bool initDatabase();

   bool insertUserData(const QString &username,const QString&email,const QString&password);

   bool updateUserData();

   QString searchUserByEmail(const QString &email);

   void showData()const noexcept;

private:
   Logger logger;
   QSqlDatabase db;
};
