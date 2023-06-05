#include "./include/dataHandler.hpp"


DataHandler::DataHandler(QObject *parent) : QObject(parent) {}

DataHandler::~DataHandler() {}

void DataHandler::dataHandler(const QJsonObject &object) {
  static QString password = object["password"].toString();
  static QString username = object["username"].toString();

  static QString email = object["email"].toString();
  QString message = object["message"].toString();

  QString l_email = object["login_email"].toString();
  QString l_password = object["login_password"].toString();
  qDebug() << "l_password" << l_password;

  static int saveCode = -1;
  int get_code = smtp.sendCodeToEmail(email, username);
  if (saveCode == -1) {
    saveCode = get_code;
  }

  qDebug() << "Save Code2:  " << saveCode;

  if (message == "code") {
    int code = object["submit_code"].toInt();
    qDebug() << "Submit_code: " << code;
    qDebug() << "Save: " << saveCode << '\n';
    if (saveCode == code) {
      QString hashPassword = hash.toHash(password);

      Database::getInstance().insertUserData(
          username, email, hashPassword);

      emit sendString("success_registration");

    } else {
      QMessageBox msgBox(QMessageBox::Critical, "Error code",
                         "Entered wrong submit code");
      msgBox.exec();
      emit sendString("badRequest");
    }
  } else if (message == "login") {
    auto dbPassword = Database::getInstance().searchUserByEmail(l_email);
    qDebug()  << "We here" << l_password << l_email; // just empty
    qDebug() << "Db_Password: " << dbPassword;

   if (hash.comparePassword(l_password,dbPassword)) {
      emit sendString("success_login");
    } else {
      QMessageBox msgBox(QMessageBox::Critical, "Failed to login",
                         "Incorrect password or wrong entered email");
      msgBox.exec();
      emit sendString("badRequest");
    }
  }
}

//  if (!valid.isValidEmail(email.toStdString()) ||
//      !valid.isValidPassword(password.toStdString()) ||
//      !valid.isValidUsername(username.toStdString())) {

//    QMessageBox msgBox(QMessageBox::Critical, "Incorrect Data",
//                       "Entered incorrect data");
//    msgBox.exec();
//    return;
//  }
