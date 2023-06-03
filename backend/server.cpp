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

Server::~Server() {}

void Server::newConnection() {
  QTcpSocket *client = m_server->nextPendingConnection();
  m_clients.append(client);
  connect(client, &QTcpSocket::readyRead, this, &Server::receivedData);

}

void Server::receivedData() {
  for (QTcpSocket *client : m_clients) {
    auto jsonData = client->readAll();
    if (jsonData.size() == 0) {
      logger.log(LogLevel::Error, "Data from client didn't get");
    } else {
      //      QJsonObject response;
      //      response.insert("status", "ok");

      //      QJsonDocument responseDoc(response);
      //      QByteArray arrayJson = responseDoc.toJson();
      //      client->write(arrayJson);
    }

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    QJsonObject data = doc.object();
    emit dataReceived(data);
  }
}


