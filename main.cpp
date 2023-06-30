#include "./backend/database/include/sqlite.hpp"
#include "./backend/include/dataHandler.hpp"
#include "./backend/include/server.hpp"
#include "./backend/include/smtp.hpp"
#include "./backend/include/updater_data.hpp"
#include "./frontend/include/dashboard.hpp"
#include "./frontend/include/signin.hpp"
#include "./frontend/include/signup.hpp"
#include "./frontend/include/user_settings.hpp"
#include "./backend/launcher/include/downloadResources.hpp"
#include "mainwindow.h"
#include <QApplication>
#include <QInputDialog>
#include <QObject>
#include <QStringList>
#include <QTranslator>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);


  QTranslator ts;
  if(ts.load(":/translations/launcher_ru.qm")) {
      qDebug() << "We here";
  a.installTranslator(&ts);
  } else {
     qDebug()<<"Something went wrong";
  }

  qRegisterMetaType<DataHandler *>("DataHandler*"); // регистрируем новый тип

  Server::getInstance();

  SignIn::getInstance().show();
  DataHandler handler;


  QObject::connect(&Server::getInstance(), &Server::dataReceived, &handler,
                   &DataHandler::dataHandler);
  QObject::connect(&handler, &DataHandler::sendString, &Server::getInstance(),
                   &Server::getString);

  return a.exec();
}
