#include "./assistance/custom.hpp"
#include "./assistance/path.hpp"
#include "mainwindow.h"
#include "./backend/launcher/include/downloadMod.hpp"
#include <QApplication>

int main(int argc, char *argv[]) {

  QApplication a(argc, argv);

   // DownloadMod mod;
    //mod.setUrlAddressMod("https://curseforge.overwolf.com/downloads/curseforge-latest-linux.zip");

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
