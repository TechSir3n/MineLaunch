#include "./include/updater_data.hpp"



void Updater::getNewUsername(const QString &newName,const QString &email)
{
    if(!newName.isEmpty()) {
        Database::getInstance().updateNameUser(newName,email);
    }
}
