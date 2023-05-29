#ifndef DASHBOARD_HPP
#define DASHBOARD_HPP

#include "signup.hpp"
#include <QAction>
#include <QComboBox>
#include <QDebug>
#include <QDialog>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QListWidget>
#include <QMap>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QRegularExpression>
#include <QStringList>
#include <QTabWidget>
#include <QTableWidget>

struct Mod {
  QString name;
  QString description;
  QString file;
};

class DashBoard : public QDialog {
public:
  explicit DashBoard(QWidget *parent = nullptr);

  ~DashBoard();

public:
  static DashBoard &getInstance() {
    static DashBoard instance;
    return instance;
  }

private slots:
  void searchModsByName();

private:
  void initalizeUI();

  void loadMods();

  void loadVersionsMinecraft();

  void playGame();

  void addMenu();

private:
  QPushButton *play;
  QPushButton *settings;
  QPushButton *update;
  QPushButton *save;
  QPushButton *reset;
  QPushButton *cancel;
  QPushButton *search;
  QPushButton *download;

  QTableWidget *modsTable;
  QTabWidget *tabWidget;

  QLineEdit *editSearch;
  QVector<Mod> loadedMods;

  QComboBox *versionSelector;
  QMenuBar *menuBar;

private:
  Logger logger;
};

#endif
