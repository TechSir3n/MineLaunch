#pragma once


#include "../database/include/sqlite.hpp"
#include <QObject>

class UserDataUpdater: public QObject {
    Q_OBJECT
public:
    explicit UserDataUpdater(QWidget * parent = nullptr);

    ~UserDataUpdater() = default;

public slots:
    void getNewUsername(const QString &newName,const QString &email);

    void getNewPassword(const QString &newPassword,const QString &email);

};
