#include "mainwindow.h"

#include "./frontend/include/signup.hpp"
#include "./backend/include/server.hpp"
#include "./backend/include/dataHandler.hpp"
#include <QApplication>
#include <QInputDialog>
#include <QStringList>
#include <QObject>
#include <QTranslator>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  qRegisterMetaType<DataHandler*>("DataHandler*"); // регистрируем новый тип

  Server server;
  SignUp sign;
  DataHandler handler;

  QObject::connect(&server,&Server::dataReceived,&handler,&DataHandler::dataHandler);

  sign.show();


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
