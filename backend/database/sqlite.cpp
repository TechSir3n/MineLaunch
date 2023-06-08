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
  db.setDatabaseName("MinecraftLauncher.sqlite");

  if (!db.open()) {
    logger.log(LogLevel::Error, "Failed to create table UserData",
               db.lastError().text().toStdString());
    return false;
  }

  QSqlQuery query(db);
  query.exec("CREATE TABLE IF NOT EXISTS UserData(id int PRIMARY KEY "
             "AUTOINCREMENT,username "
             "VARCHAR(60),email VARCHAR(233),password VARCHAR(233),created_at "
             "TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");

  if (query.lastError().type() != QSqlError::NoError) {
    logger.log(LogLevel::Error, "Failed to create table UserData",
               query.lastError().text().toStdString());
    return false;
  }

  return true;
}

bool Database::insertUserData(const QString &username, const QString &email,
                              const QString &password) {
  QSqlQuery query(db);
  query.prepare("INSERT INTO UserData(username,email,password) "
                "VALUES(?,?,?)");

  query.bindValue(0, username);
  query.bindValue(1, email);
  query.bindValue(2, password);

  if (!query.exec()) {
    logger.log(LogLevel::Error, "Failed to insert data to database",
               query.lastError().text().toStdString());
    return false;
  }

  db.commit();

  return true;
}

bool Database::updateNameUser(const QString &newName,const QString &email)
{
  QSqlQuery query(db);
  query.prepare("UPDATE UserData SET username=:newName WHERE email=:email");
  query.bindValue(":newName",newName);
  query.bindValue(":email",email);

  if(!query.exec()) {
    QToolTip::showText(QPoint(),"Incorrect password,or email doesn't exists");
    logger.log(LogLevel::Error,"Failed to update user name");
    return false;
  }

  QToolTip::showText(QPoint(),"Success updated user name");
  return true;
}

bool Database::updatePasswordUser(const QString &newPassword,const QString& email)
{
  QSqlQuery query(db);


  if(!query.exec()) {


    return false;
  }

  return true;
}

std::tuple<QString, QString, QString>
Database::searchUserByEmail(const QString &email) {
  QSqlQuery query(db);
  query.prepare("SELECT username,password FROM UserData WHERE email=:email");
  query.bindValue(":email", email);

  QString password, username;
  if (query.exec() && query.next()) {
    username = query.value(0).toString();
    password = query.value(1).toString();
  } else {
    logger.log(LogLevel::Error, "Failed to get data user: " +
                                    query.lastError().text().toStdString());
    return std::make_tuple(QString(), QString(), QString());
  }

  return std::make_tuple(password, username, email);
}

void Database::showData() const noexcept {
  QSqlQuery query(db);
  query.exec("SELECT * FROM UserData"); // выбираем все поля из таблицы UserData

  while (query.next()) {
    // выводим значения полей в консоль или куда-то еще
    int id = query.value(0).toInt();
    QString username = query.value(1).toString();
    QString email = query.value(2).toString();
    QString password = query.value(3).toString();
    QString created_at = query.value(4).toString();
    qDebug() << "id:" << id << "username:" << username << "email:" << email
             << "password:" << password << "created_at:" << created_at;
  }
}
