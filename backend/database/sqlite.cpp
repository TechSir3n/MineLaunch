#include "./include/sqlite.hpp">

Database::Database(QObject *parent) : QObject(parent) {
  if (!initDatabase()) {
    logger.log(LogLevel::Critical, "Failed to init database");
  } else {
    logger.log(LogLevel::Info, "Success connetec to database");
  }
}

Database::~Database() {
  if (db.isOpen()) {
    db.close();
  }
}

bool Database::initDatabase() {
  db = QSqlDatabase::addDatabase("QSQLITE", "SQLITE");
  db.setDatabaseName(QCoreApplication::applicationDirPath() + "/../" +
                     "/MineLaunch/backend/database/MinecraftLauncher.sqlite");

  if (!db.open()) {
    logger.log(LogLevel::Error, "Failed to create table UserData",db.lastError().text().toStdString());
    return false;
  }

  QSqlQuery query(db);
  query.exec("CREATE TABLE IF NOT EXISTS UserData(id int PRIMARY KEY "
             "AUTOINCREMENT,username "
             "VARCHAR(60),email VARCHAR(233),password VARCHAR(233),created_at "
             "TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");

  if (query.lastError().type() != QSqlError::NoError) {
    logger.log(LogLevel::Error, "Failed to create table UserData",query.lastError().text().toStdString());
    return false;
  }

  return true;
}

bool Database::insertUserData(const QString &username,const QString&email,const QString&password) {
  QSqlQuery query(db);
  query.prepare("INSERT INTO UserData(username,email,password) "
             "VALUE(?,?,?)");

  query.bindValue(0,username);
  query.bindValue(1,email);
  query.bindValue(2,password);

  if(!query.exec()) {
    logger.log(LogLevel::Error,"Failed to insert data to database",query.lastError().text().toStdString());
    return false;
  }

  return true;
}

bool Database::updateUserData()
{

}

bool Database::searchUserByEmail(const QString &email)
{
  QSqlQuery query(db);



  return true;
}
