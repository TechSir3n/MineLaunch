#include "mainwindow.h"
#include "ui_mainwindow.h"

MineLaunch::MineLaunch(QWidget *parent) : QMainWindow(parent) {
  QIcon icon(QDir::toNativeSeparators("./resources/u_ajax.png"));
  this->setWindowIcon(icon);
  this->setWindowTitle("MineLaunch");
}

MineLaunch::~MineLaunch() {}

void MineLaunch::run() {
  qRegisterMetaType<DataHandler *>("DataHandler*");

  std::shared_ptr<WelcomePage> page = std::make_shared<WelcomePage>();
  page->show();

  Server::getInstance();
  DataHandler handler;

  QObject::connect(&Server::getInstance(), &Server::dataReceived, &handler,
                   &DataHandler::dataHandler);
  QObject::connect(&handler, &DataHandler::sendString, &Server::getInstance(),
                   &Server::getString);
}
