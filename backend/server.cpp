#include "./include/server.hpp"

Server::Server(QObject *parent) : QObject(parent) {
  m_server = new QTcpServer(this);
  connect(m_server, &QTcpServer::newConnection, this, &Server::newConnection);
  if (!m_server->listen(QHostAddress::Any, 8090)) {
    logger.log(LogLevel::Critical, "Failed to run server");
  } else {
    logger.log(LogLevel::Info, "Server run ...");
  }
}

void Server::newConnection() {
  QTcpSocket *client = m_server->nextPendingConnection();
  m_clients.append(client);
  connect(client, &QTcpSocket::readyRead, this, &Server::receivedData);
}

void Server::receivedData() {
  for (QTcpSocket *client : m_clients) {
    m_client = client;
    auto jsonData = client->readAll();
    qDebug() << jsonData;
    if (jsonData.isEmpty()) {
      logger.log(LogLevel::Error, "Data from client didn't get");
      continue;
    }

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &error);
    if (error.error != QJsonParseError::NoError) {
      logger.log(LogLevel::Error, "Failed to incoming data as json");
      continue;
    }

    QJsonObject data = doc.object();
    emit dataReceived(data);
  }
}

void Server::getString(const QString &str) {
  QJsonObject response;
  if (str == "success_registration") {
    response.insert("status", "success_registration");
    QJsonDocument responseDoc(response);
    QByteArray arrayJson = responseDoc.toJson();
    m_client->write(arrayJson);
  } else if (str == "success_login") {
    response.insert("status", "success_login");
    QJsonDocument responseDoc(response);
    QByteArray arrayJson = responseDoc.toJson();
    m_client->write(arrayJson);
  } else {
    response.insert("status", "badRequest");
    QJsonDocument responseDoc(response);
    QByteArray arrayJson = responseDoc.toJson();
    m_client->write(arrayJson);
  }
}
