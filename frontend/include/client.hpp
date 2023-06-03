#pragma once

#include "utils/logger.hpp"
#include <QTcpSocket>
#include <QObject>
#include <QString>
#include <QJsonObject>
#include <QByteArray>
#include <QJsonDocument>

class Client : public QObject{
    Q_OBJECT
public:
    explicit Client(QObject * parent = nullptr);

    ~Client();

signals:
    void dataSent(const QJsonObject &data);

public slots:
    void sendData(const QString &username,const QString &email,const QString &password);

    void sendSubmitCode(int code);

    void readyRead();

private:
    QTcpSocket *m_socket;
    Logger logger;
};
