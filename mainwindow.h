#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "./assistance/path.hpp"
#include "./frontend/include/welcome.hpp"
#include "./backend/include/server.hpp"
#include "./backend/include/dataHandler.hpp"
#include <QMainWindow>
#include <QObject>
#include <QDir>
#include <QIcon>
#include <QTranslator>

class MineLaunch : public QMainWindow {
  Q_OBJECT

public:
  explicit MineLaunch(QWidget *parent = nullptr);

  ~MineLaunch();

  void run();
};
#endif // MAINWINDOW_H
