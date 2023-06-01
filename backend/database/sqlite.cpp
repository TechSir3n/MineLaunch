#include "./include/sqlite.hpp">

Database::Database(QObject *parent) : QObject(parent) {
  if (initDatabase() == false) {
    logger.log(LogLevel::Critical, "Failed to init database");
  } else {
    logger.log(LogLevel::Info,"Success connetec to database");
  }
}

Database::~Database() { db.close(); }

bool Database::initDatabase() {
  db = QSqlDatabase::addDatabase("QSQLITE", "SQLITE");
  db.setDatabaseName(QCoreApplication::applicationDirPath() + "/../" + "/MineLaunch/backend/database/MinecraftLauncher.sqlite");

  if (!db.open()) {
    qDebug()<<db.lastError();
    return false;
  }

  QSqlQuery query(db);
  query.exec("CREATE TABLE IF NOT EXISTS UserData(id int PRIMARY KEY,username "
             "VARCHAR(60),email VARCHAR(233),password VARCHAR(233))");

  if(query.lastError().type()!=QSqlError::NoError) {
    logger.log(LogLevel::Error,"Failed to do request to database");
    return false;
  }

  return true;
}

bool Database::insertUserData() {}
