#include "./assistance/custom.hpp"
#include "./assistance/path.hpp"
#include "./backend/launcher/include/downloadMod.hpp"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {

  QApplication a(argc, argv);
  a.setStyle("fusion");

  QString language = Custom().getLanguage();
  QTranslator ts;
  if (ts.load(":/translations/launcher_" + language + ".qm"))
    a.installTranslator(&ts);

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
