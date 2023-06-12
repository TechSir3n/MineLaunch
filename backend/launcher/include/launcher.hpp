#pragma once

#include <QObject>

class Launcher : public QObject {
    Q_OBJECT
public slots:
    virtual void start() = 0;

    virtual void stop() = 0;
};
