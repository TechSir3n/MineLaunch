#include "mainwindow.h"

#include <QApplication>
#include "./frontend/include/welcome.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
     //MainWindow w;
    WelcomePage s;
    s.show();
     //w.show();
    return a.exec();
}
