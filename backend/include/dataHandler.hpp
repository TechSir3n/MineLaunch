#pragma once

#include "utils/logger.hpp"
#include <QObject>
#include <QJsonObject>

class DataHandler : public QObject {
    Q_OBJECT
public:
    explicit DataHandler(QObject *parent  = nullptr);

    ~DataHandler();
public slots:
    void dataHandler(const QJsonObject &object);


private:
    Logger logger;
};
