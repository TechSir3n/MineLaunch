#include "./include/dataHandler.hpp"
#include "./frontend/include/user_settings.hpp"

DataHandler::DataHandler(QObject *parent) : QObject(parent) {

  UserSettings *userSettings = &UserSettings::getInstance();
  QObject::connect(this, &DataHandler::sendUsername, userSettings,
                   &UserSettings::getProfileData);
}

DataHandler::~DataHandler() {}

void DataHandler::dataHandler(const QJsonObject &object) {
  static QString password = object["password"].toString();
  static QString username = object["username"].toString();

  static QString email = object["email"].toString();
  QString message = object["message"].toString();

  QString l_email = object["login_email"].toString();
  QString l_password = object["login_password"].toString();

  static int saveCode = -1;
  int get_code = smtp.sendCodeToEmail(email, username);
  if (saveCode == -1) {
    saveCode = get_code;
  }

  if (message == "code") {
    int code = object["submit_code"].toInt();
    if (saveCode == code) {
      QString hashPassword = hash.toHash(password);
      Database::getInstance().insertUserData(username, email, hashPassword);
      emit sendString("success_registration");
    } else {
      QMessageBox::critical(nullptr, "Error",
                            "Failed to registration,something wrong");
      emit sendString("badRequest");
    }
  } else if (message == "login") {
    auto [hashed_password,name,email] = Database::getInstance().searchUserByEmail(l_email);
    if (hash.comparePassword(l_password,hashed_password)) {
      emit sendString("success_login");
      emit sendUsername(name,email,hashed_password);
    } else {
      QMessageBox::critical(
          nullptr, "Error", "Failed to login,enter incorrect password or login");
      emit sendString("badRequest");
    }
  }
}
