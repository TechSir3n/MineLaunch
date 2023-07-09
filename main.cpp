#include "./assistance/custom.hpp"
#include "./backend/launcher/include/downloadResources.hpp"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  qRegisterMetaType<DataHandler *>("DataHandler*");

  QApplication a(argc, argv);
  a.setStyle("fusion");

  WelcomePage page;
  page.show();

  Server::getInstance();
  DataHandler handler;

  QString language = Custom().getLanguage();
  QTranslator ts;
  if (ts.load(":/translations/launcher_" + language + ".qm"))
    a.installTranslator(&ts);

  QObject::connect(&Server::getInstance(), &Server::dataReceived, &handler,
                   &DataHandler::dataHandler);
  QObject::connect(&handler, &DataHandler::sendString, &Server::getInstance(),
                   &Server::getString);

  return a.exec();
}
