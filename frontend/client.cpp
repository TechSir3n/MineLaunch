#include "./include/client.hpp"
#include "./include/signin.hpp"

Client::Client(QObject *parent) : QObject(parent) {
  m_socket = new QTcpSocket(this);
  m_socket->connectToHost("127.0.0.1", 8080);
  if (!m_socket->waitForConnected()) {
    logger.log(LogLevel::Error, m_socket->errorString().toStdString());
  }

  QObject::connect(m_socket, &QTcpSocket::readyRead, this, &Client::readyRead);
}

Client::~Client() {}

void Client::sendData(const QString &username, const QString &email,
                      const QString &password) {
  QJsonObject data;
  data["message"] = "data";
  data["username"] = username;
  data["email"] = email;
  data["password"] = password;

  QJsonDocument doc(data);
  QByteArray jsonData = doc.toJson();

  m_socket->write(jsonData);
  emit dataSent(data);
}

void Client::sendSubmitCode(int code) {
  QJsonObject object;
  object["message"] = "code";
  object["code"] = code;

  QJsonDocument doc(object);
  QByteArray jsonCode = doc.toJson();

  m_socket->write(jsonCode);
  emit dataSent(object);
}

void Client::sendUserLoginData(const QString &email, const QString &password) {
  QJsonObject object;
  object["message"] = "login";
  object["login_email"] = email;
  object["login_password"] = password;

  QJsonDocument doc(object);
  QByteArray jsonData = doc.toJson();

  m_socket->write(jsonData);
  emit dataSent(object);
}

void Client::readyRead() {
  const auto jsonData = m_socket->readAll();
  QJsonDocument doc = QJsonDocument::fromJson(jsonData);
  QVariantMap map = doc.toVariant().toMap();

  if (map["status"].toString() == "success_registration") {
    logger.log(LogLevel::Info, "Success registration");
  } else if (map["status"].toString() == "success_login") {
    logger.log(LogLevel::Info, "Success Login");
    SignIn::getInstance().close();
    DashBoard::getInstance().show();
  } else {
    logger.log(LogLevel::Error, map["status"].toString().toStdString());
  }
}
