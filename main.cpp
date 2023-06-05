#include "mainwindow.h"
#include "./frontend/include/signin.hpp"
#include "./frontend/include/signup.hpp"
#include "./backend/include/server.hpp"
#include "./backend/include/smtp.hpp"
#include "./backend/database/include/sqlite.hpp"
#include "./backend/include/dataHandler.hpp"
#include <QApplication>
#include <QInputDialog>
#include <QStringList>
#include <QObject>
#include <QTranslator>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  qRegisterMetaType<DataHandler*>("DataHandler*"); // регистрируем новый тип


  Server::getInstance();
  SignIn::getInstance().show();

  DataHandler handler;

  QObject::connect(&Server::getInstance(),&Server::dataReceived,&handler,&DataHandler::dataHandler);
  QObject::connect(&handler,&DataHandler::sendString,&Server::getInstance(),&Server::getString);

  Database::getInstance().showData();



  // MainWindow w;


//  QTranslator t;
//  QStringList languages;
//  languages << "Russian"
//            << "English"
//            << "Chinese"
//            <<"French";

//  QString lang =
//      QInputDialog::getItem(nullptr, "Select language", "Language", languages);

//  if (lang == "Russian") {

//  } else if (lang == "Chinese") {

//  } else if(lang == "French") {

//  }

  //DashBoard s;
 // s.show();
  // w.show();
  return a.exec();
}
