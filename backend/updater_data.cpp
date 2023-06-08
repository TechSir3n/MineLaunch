#include "./include/updater_data.hpp"
#include "./frontend/include/user_settings.hpp"


Updater::Updater(QWidget *parent) : QObject(parent)
{

}

void Updater::getNewUsername(const QString &newName,const QString &email)
{
    if(!newName.isEmpty() && !email.isEmpty()) {
        Database::getInstance().updateNameUser(newName,email);
    }
}

void Updater::getNewPassword(const QString &newPassword, const QString &email)
{
    if(!newPassword.isEmpty() && !email.isEmpty()) {
        Database::getInstance().updatePasswordUser(newPassword,email);
    }
}
