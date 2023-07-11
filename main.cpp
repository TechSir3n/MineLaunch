#include "./assistance/custom.hpp"
#include "./frontend/include/signin.hpp"
#include "minelaunch.hpp"
#include <QApplication>


int main(int argc, char *argv[]) {
 qRegisterMetaType<DataHandler *>("DataHandler*");

  QApplication a(argc, argv);
  a.setStyle("fusion");

  Server::getInstance();
  DataHandler handler;

  WelcomePage page;
  page.show();

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
