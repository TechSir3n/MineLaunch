#pragma once

#include "dashboard.hpp"
#include "assistance/logger.hpp"
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QString>
#include <QTcpSocket>

class Client : public QObject {
  Q_OBJECT
public:
  explicit Client(QObject *parent = nullptr);

  ~Client();

signals:
  void dataSent(const QJsonObject &data);

public slots:
  void sendData(const QString &username, const QString &email,
                const QString &password);

  void sendSubmitCode(int code);

  void sendUserLoginData(const QString &email, const QString &password);

  void readyRead();

private:
  QTcpSocket *m_socket;
  Logger logger;
};
