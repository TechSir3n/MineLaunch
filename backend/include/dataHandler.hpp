#pragma once

#include "../include/smtp.hpp"
#include "utils/hashing.hpp"
#include "utils/logger.hpp"
#include "backend/database/include/sqlite.hpp"
#include "server.hpp"
#include "utils/validator.hpp"
#include <QObject>
#include <QJsonObject>
#include <cstdlib>
#include <ctime>
#include <QMessageBox>

class DataHandler : public QObject {
    Q_OBJECT
public:
    explicit DataHandler(QObject *parent  = nullptr);

    ~DataHandler();

signals:
    void sendString(const QString &str);

public slots:
    void dataHandler(const QJsonObject &object);

private:
    Logger logger;
    Smtp smtp;
    Validator valid;
    Hash hash;
};
