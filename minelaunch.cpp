#include "mainwindow.h"
#include "ui_mainwindow.h"

MineLaunch::MineLaunch(QWidget *parent) : QMainWindow(parent) {

  QIcon icon(QDir::toNativeSeparators("./resources/u_ajax.png"));
  this->setWindowIcon(icon);
  this->setWindowTitle("MineLaunch");
}

MineLaunch::~MineLaunch() {}
