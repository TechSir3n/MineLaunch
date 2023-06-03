#pragma once

#include "../../utils/logger.hpp"
#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkRequest>
#include <QtNetwork>
#include <QJsonObject>
#include <QByteArray>


class Server : public QObject{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

    ~Server();
signals:
    void dataReceived(const QJsonObject &data);

    void codeReceived(const QJsonObject &data);

public slots:
    void newConnection();

    void receivedData();

private:
    QTcpServer *m_server;
    QList<QTcpSocket*>m_clients;
    Logger logger;
};
