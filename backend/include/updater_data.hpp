#pragma once


#include "../database/include/sqlite.hpp"
#include <QObject>

class Updater : public QObject {
    Q_OBJECT
private slots:
    void getNewUsername(const QString &newName,const QString &email);

};
