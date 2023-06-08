#pragma once


#include "../database/include/sqlite.hpp"
#include <QObject>

class Updater : public QObject {
    Q_OBJECT
public:
    explicit Updater(QWidget * parent = nullptr);

    ~Updater() = default;

public slots:
    void getNewUsername(const QString &newName,const QString &email);

    void getNewPassword(const QString &newPassword,const QString &email);

};
