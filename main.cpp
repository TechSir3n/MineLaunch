#include "mainwindow.h"

#include "./frontend/include/dashboard.hpp"
#include "./backend/database/include/sqlite.hpp"
#include <QApplication>
#include <QInputDialog>
#include <QStringList>
#include <QTranslator>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

    Database db;


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
