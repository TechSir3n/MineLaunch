#include "./include/handlerData.hpp"


DataHandler::DataHandler(QObject *parent) : QObject(parent)
{

}

DataHandler::~DataHandler()
{

}


void DataHandler::dataHandler(const QJsonObject &object)
{
    QString password = object["password"].toString();
    QString username = object["username"].toString();
    QString email = object["email"].toString();

    qDebug()<<password<<" "<<username<<" "<<email;
}
