#include "mainwindow.h"

#include "./frontend/include/dashboard.hpp"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  // MainWindow w;
  DashBoard s;
  s.show();
  // w.show();
  return a.exec();
}
