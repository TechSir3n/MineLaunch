#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    QIcon icon(QDir::toNativeSeparators("./resources/u_ajax.png"));
    this->setWindowIcon(icon);
    this->setWindowTitle("MineLaunch");
}

MainWindow::~MainWindow()
{

}

