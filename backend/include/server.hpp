#pragma once

#include "../../assistance/logger.hpp"
#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkRequest>
#include <QtNetwork>
#include <QJsonObject>
#include <QByteArray>
#include <QJsonParseError>

class Server : public QObject{
    Q_OBJECT
private:
    explicit Server(QObject *parent = nullptr);

    ~Server() = default;
public:
    static Server & getInstance() {
        static Server server;
        return server;
    }

signals:
    void dataReceived(const QJsonObject &data);

public slots:
    void newConnection();

    void receivedData();

    void getString(const QString &str);
private:
    QTcpServer *m_server;
    QTcpSocket *m_client;
    QVector<QTcpSocket*>m_clients;
    Logger logger;
};
