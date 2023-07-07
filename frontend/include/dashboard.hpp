#pragma once

#include "./assistance/clearLogs.hpp"
#include "./backend/launcher/include/factory.hpp"
#include "./backend/launcher/include/launcher.hpp"
#include "./backend/launcher/include/downloadMod.hpp"
#include "./assistance/custom.hpp"
#include "signup.hpp"
#include "user_settings.hpp"
#include <QAction>
#include <QButtonGroup>
#include <QCheckBox>
#include <QComboBox>
#include <QDebug>
#include <QDesktopServices>
#include <QDialog>
#include <QEventLoop>
#include <QFileInfo>
#include <QFrame>
#include <QGroupBox>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QListWidget>
#include <QMap>
#include <QMenu>
#include <QMenuBar>
#include <QPalette>
#include <QPushButton>
#include <QRadioButton>
#include <QRegularExpression>
#include <QSlider>
#include <QStackedWidget>
#include <QStringList>
#include <QTabWidget>
#include <QTableWidget>
#include <QTimer>
#include <QUrl>
#include <QVBoxLayout>
#include <QtCore>
#include <QtNetwork>
#include <QtWebEngineWidgets>

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

  DashBoard(const DashBoard &) = delete;

  DashBoard &operator=(const DashBoard &) = delete;

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

  void setSaveSettingsUI();

signals:
  void sendSaveVersionGame(const QString &version);

  void sendIPServerAndPort(const QStringList &connectServerArgs);

  void sendModName(const QStringList &modNameArgs);

  void sendSaveLanguage(const char *language);

  void sendModURL(const QString &url);

private:
  QPushButton *playButton;
  QPushButton *saveButton;
  QPushButton *resetButton;
  QPushButton *cancelButton;
  QPushButton *searchButton;
  QPushButton *downloadButton;
  QPushButton *connectButton;
  QPushButton *updateListButton;
  QPushButton *nextButton;
  QPushButton *addToGame;

  QRadioButton *fullScreen;
  QRadioButton *windowMode;
  QRadioButton *launcherOpen;
  QRadioButton *launcherClose;
  QButtonGroup *buttonGroup;

  QStackedWidget *stackWidget;
  QSettings settings;
  QTableWidget *modsTable;
  QTabWidget *tabWidget;

  QLineEdit *editSearch;
  QLineEdit *editIPServer;
  QLineEdit *editPort;

  QVector<Mod> loadedMods;

  QComboBox *versionSelector;
  QComboBox *screenExtension;
  QComboBox *qualityGraphic;
  QComboBox *choiceLanguage;

  QSlider *soundSlider;
  QSlider *brightnessSlider;
  QSlider *choiceColor;
  QSlider *choiceColorButton;
  QSlider *choiceColorButtonText;
  QSlider *maximumUseMemory;
  QSlider *minimumUseMemory;

  QMenuBar *menuBar;

  QGroupBox *groupBoxGame;
  QGroupBox *groupBoxLauncher;
  QGroupBox *groupLauncherState;
  QGroupBox *groupMemorySettings;
private:
  Logger logger;
  Downloader *m_download;
  PlayGame *m_play;
  DownloadMod *m_mod;
  ClearLogs cl;
  Custom *m_custom;
  static constexpr char *ENGLISH_LANG { "en" } ;
  static constexpr char *RUSSIAN_LANG { "ru" };
};
