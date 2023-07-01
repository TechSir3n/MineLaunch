#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "./backend/database/include/sqlite.hpp"
#include "./backend/include/dataHandler.hpp"
#include "./backend/include/server.hpp"
#include "./backend/include/smtp.hpp"
#include "./backend/include/updater_data.hpp"
#include "./backend/launcher/include/downloadResources.hpp"
#include "./frontend/include/dashboard.hpp"
#include "./frontend/include/signin.hpp"
#include "./frontend/include/signup.hpp"
#include "./frontend/include/user_settings.hpp"
#include <QInputDialog>
#include <QMainWindow>
#include <QObject>
#include <QStringList>
#include <QTranslator>


class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
};
#endif // MAINWINDOW_H
