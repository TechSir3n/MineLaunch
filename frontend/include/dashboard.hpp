#pragma once

#include "signup.hpp"
#include "user_settings.hpp"
#include <QAction>
#include <QButtonGroup>
#include <QCheckBox>
#include <QComboBox>
#include <QDebug>
#include <QDialog>
#include <QFileInfo>
#include <QGroupBox>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QListWidget>
#include <QMap>
#include <QMenu>
#include <QMenuBar>
#include <QFrame>
#include <QPalette>
#include <QPushButton>
#include <QUrl>
#include <QStackedWidget>
#include <QtNetwork>
#include <QtWebEngineWidgets>
#include <QRadioButton>
#include <QRegularExpression>
#include <QSlider>
#include <QStringList>
#include <QTabWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QtCore>
#include <QEventLoop>
#include "./backend/launcher/include/factory.hpp"
#include "./backend/launcher/include/launcher.hpp"

struct Mod {
  QString name;
  QString description;
  QString file;
};

class DashBoard : public QDialog {
  Q_OBJECT
private:
  explicit DashBoard(QWidget *parent = nullptr);

  ~DashBoard();

  DashBoard(const DashBoard&) = delete;

  DashBoard & operator=(const DashBoard&) = delete;

public:
  static DashBoard &getInstance() {
    static DashBoard instance;
    return instance;
  }

private slots:
  void searchModsByName();

  void onSliderValueChanged(int value);

private:
  void initalizeUI() noexcept;

  void loadMods() noexcept;

  void loadServers() noexcept;

  void loadVersionsMinecraft() noexcept;

  void addGameTab() noexcept;

  void addMenuTab() noexcept;

  void addSettings() noexcept;

private:
  QPushButton *playButton;
  QPushButton *updateButton;
  QPushButton *saveButton;
  QPushButton *resetButton;
  QPushButton *cancelButton;
  QPushButton *searchButton;
  QPushButton *downloadButton;
  QPushButton* connectButton;
  QPushButton *updateListButton;
  QPushButton *nextButton;

  QStackedWidget *stackWidget;
  QTableWidget *modsTable;
  QTabWidget *tabWidget;

  QLineEdit *editSearch;
  QLineEdit* editIPServer;

  QVector<Mod> loadedMods;

  QComboBox *versionSelector;
  QComboBox *screenExtension;
  QComboBox *qualityGraphic;
  QComboBox* choiceLanguage;

  QSlider *soundSlider;
  QSlider *brightnessSlider;
  QSlider *choiceColor;

  QMenuBar *menuBar;
  QRadioButton *fullScreen;
  QRadioButton *windowMode;
  QButtonGroup *buttonGroup;

  QGroupBox *groupBoxGame;
  QGroupBox *groupBoxLauncher;

private:
  Logger logger;
};
