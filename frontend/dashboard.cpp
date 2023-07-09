#include "./include/dashboard.hpp"
#include "./assistance/defines.hpp"
#include "./assistance/path.hpp"

extern const QString sliderStyle;

extern const QString linkStyle;

extern const QString lineEditStyle;

extern const QString tabStyle;

DashBoard::DashBoard(QWidget *parent)
    : QDialog(parent), tabWidget(new QTabWidget(this)),
      modsTable(new QTableWidget()), versionSelector(new QComboBox()),
      menuBar(new QMenuBar()), m_mod(new DownloadMod()),
      m_custom(new Custom()) {

  QString style = settings.value("style").toString();
  if (!style.isEmpty()) {
    tabWidget->setStyleSheet(style);
  }

  m_play = dynamic_cast<PlayGame *>(
      FactoryLauncher::createLauncher(LauncherType::Play));
  m_download = dynamic_cast<Downloader *>(
      FactoryLauncher::createLauncher(LauncherType::Download));

  QObject::connect(this, &DashBoard::sendSaveVersionGame, m_download,
                   &Downloader::setVersionGame);

  QObject::connect(this, &DashBoard::sendSaveVersionGame, m_play,
                   &PlayGame::setVersionGame);

  QObject::connect(this, &DashBoard::sendIPServerAndPort, m_play,
                   &PlayGame::setIPAddressAndPort);

  QObject::connect(this, &DashBoard::sendModURL, m_mod,
                   &DownloadMod::setUrlAddressMod);

  QObject::connect(
      m_mod, &DownloadMod::errorDownloadMod,
      [](const QString &error) { HandlerSignals().onDownloadModError(error); });

  QObject::connect(this, &DashBoard::sendModName, m_play,
                   &PlayGame::setModsFiels);

  QObject::connect(
      tabWidget, &QTabWidget::currentChanged, this, [this](int index) {
        if (index == 1) {
          QMessageBox::information(
              this, "Tip",
              "Set url address .jar file which you want to download");
        }
      });

  tabWidget->setStyleSheet(tabStyle);
  tabWidget->setFixedSize(QSize(1350, 880));
  versionSelector->setFixedWidth(100);

  initalizeUI();
  this->setAutoFillBackground(true);
}

DashBoard::~DashBoard() {
  delete m_custom;
  delete menuBar;
  delete versionSelector;
  delete modsTable;
  delete tabWidget;
  delete m_mod;
}

void DashBoard::initalizeUI() noexcept {
  loadVersionsMinecraft();
  addGameTab();
  loadMods();
  addMenuTab();
  loadServers();
  UserSettings::getInstance().initalizeGuiSettings(tabWidget);
  addSettings();

  this->setMinimumSize(1350, 850);
  this->setWindowTitle("Minecraft Launcher");
}

void DashBoard::loadMods() noexcept {
  QWidget *widgetMods = new QWidget();
  searchButton = new QPushButton(tr("Search"));
  downloadButton = new QPushButton(tr("Download"));

  QHBoxLayout *searchLayout = new QHBoxLayout;
  searchLayout->addWidget(downloadButton);
  searchLayout->addWidget(searchButton);
  searchLayout->setAlignment(Qt::AlignRight);

  editSearch = new QLineEdit();
  editSearch->setPlaceholderText("Set url link mod wish you download");
  addToGame = new QPushButton(tr("Add Game"));

  QHBoxLayout *buttonLayout = new QHBoxLayout;
  buttonLayout->addWidget(addToGame);
  buttonLayout->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);

  QVBoxLayout *modsLayout = new QVBoxLayout(widgetMods);
  modsLayout->addWidget(editSearch);
  modsLayout->addLayout(searchLayout);
  modsLayout->addWidget(modsTable);
  modsLayout->addLayout(buttonLayout);

  tabWidget->addTab(widgetMods, tr("Mods"));

  QDir dir(Path::minecraftPath() + "/mods/");
  QFileInfoList fileList = dir.entryInfoList(QDir::Files);

  int row = 0;
  modsTable->setRowCount(fileList.size());
  modsTable->setColumnCount(5);
  modsTable->setHorizontalHeaderLabels(
      {"Name", "Extension", "Size Mod", "Last Modified", "Storage Location"});
  for (int i = 0; i < modsTable->columnCount(); ++i) {
    modsTable->setColumnWidth(i, 200);
  }

  QStringList filePaths;
  for (const auto &fileInfo : fileList) {
    filePaths.append(fileInfo.absoluteFilePath());

    const qint64 fileSize = fileInfo.size();
    const QString fileExtension = fileInfo.suffix();
    QString sizeText;

    if (fileSize < 1024) {
      sizeText = QString("%1 B").arg(fileSize);
    } else if (fileSize < 1048576) {
      sizeText = QString("%1 KB").arg(fileSize / 1024);
    } else if (fileSize < 1073741824) {
      sizeText = QString("%1 MB").arg(fileSize / 1048576);
    }

    QTableWidgetItem *itemFileName = new QTableWidgetItem(fileInfo.baseName());
    QTableWidgetItem *itemLastModified =
        new QTableWidgetItem(fileInfo.lastModified().toString());
    QTableWidgetItem *itemSizeFileMod = new QTableWidgetItem(sizeText);
    QTableWidgetItem *itemExtensionFileMod =
        new QTableWidgetItem(fileExtension);
    QString m_path;
    for (const auto &path : filePaths) {
      m_path = path;
    }

    QTableWidgetItem *itemStorageLocation = new QTableWidgetItem(m_path);

    modsTable->setItem(row, 0, itemFileName);
    modsTable->setItem(row, 1, itemExtensionFileMod);
    modsTable->setItem(row, 2, itemSizeFileMod);
    modsTable->setItem(row, 3, itemLastModified);
    modsTable->setItem(row, 4, itemStorageLocation);
    row++;
  }

  QObject::connect(searchButton, &QPushButton::clicked, this,
                   &DashBoard::searchModsByName);

  QObject::connect(addToGame, &QPushButton::clicked, this, [this]() {
    const QString modName = editSearch->text();
    if (!modName.isEmpty()) {
      for (int row = 0; row < modsTable->rowCount(); row++) {
        auto item = modsTable->item(row, 0);
        if (item && item->text() == modName) {
          auto modNameLocation = modsTable->item(row, 4);
          emit sendModName(QStringList() << "-Djava.class.path="
                                         << QDir::toNativeSeparators(
                                                modNameLocation->text()));
          QMessageBox::information(this, "Tip", "Mod Success added");
          break;
        }
      }
    } else {
      QObject::connect(
          modsTable, &QTableWidget::cellClicked, this,
          [this](int row, int column) {
            QString storageLocation;
            if (column == 0) {
              auto storageLocationItem = modsTable->item(row, 4);
              if (!storageLocationItem) {
                return;
              }
              storageLocation =
                  storageLocationItem->data(Qt::DisplayRole).toString();
            }
            emit sendModName(QStringList()
                             << "-Djava.class.path="
                             << QDir::toNativeSeparators(storageLocation));
            QMessageBox::information(this, "Tip", "Mod Success added");
          });
    }
  });

  QObject::connect(downloadButton, &QPushButton::clicked, this, [this]() {
    if (!editSearch->text().startsWith("https")) {
      QMessageBox::warning(this, "Error", "Wrong URL");
      return;
    } else {
      emit sendModURL(editSearch->text());
    }
  });
}

void DashBoard::loadServers() noexcept {
  QWebEngineView *webView = new QWebEngineView(this);

  webView->load(QUrl("https://minecraft-server-list.com/"));
  webView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  connectButton = new QPushButton(tr("Connect"));
  connectButton->setStyleSheet("background-color: #1e90ff; color: white;");
  connectButton->setFont(QFont("Arial", 12, QFont::Bold));
  connectButton->setFixedWidth(100);

  editIPServer = new QLineEdit();
  editIPServer->setPlaceholderText(
      tr("Enter IP address for connect to server"));

  editPort = new QLineEdit();
  editPort->setPlaceholderText(tr("Enter port of address server"));

  const QString style =
      "QLineEdit { border: 2px solid gray; border-radius: 10px; padding: 0 "
      "8px; background-color: #f8f8f8; color: #333; }";

  editIPServer->setStyleSheet(style);
  editPort->setStyleSheet(style);

  QHBoxLayout *buttonLayout = new QHBoxLayout();
  buttonLayout->addWidget(editIPServer);
  buttonLayout->addWidget(editPort);
  buttonLayout->addWidget(connectButton);
  buttonLayout->setAlignment(Qt::AlignRight | Qt::AlignBottom);
  buttonLayout->setContentsMargins(0, 0, 0, 0);
  buttonLayout->setSpacing(10);

  QWidget *container = new QWidget();
  QVBoxLayout *layout = new QVBoxLayout();
  layout->addWidget(webView);
  layout->addLayout(buttonLayout);

  layout->setContentsMargins(10, 10, 10, 10);
  layout->setSpacing(10);
  layout->setAlignment(Qt::AlignCenter);

  container->setLayout(layout);

  tabWidget->addTab(container, tr("Servers"));

  QObject::connect(connectButton, &QPushButton::clicked, this, [this]() {
    const QString IPAddress = editIPServer->text();
    const QString port = editPort->text();

    const auto argsConnectToServer = QStringList() << "--server" << IPAddress
                                                   << "--port" << port;
    emit sendIPServerAndPort(argsConnectToServer);

    editIPServer->clear();
    editPort->clear();
  });
}

void DashBoard::loadVersionsMinecraft() noexcept {
  versionSelector->addItem("1.19.4-rc1");
  versionSelector->addItem("23w03a");
  versionSelector->addItem("1.20-pre7");
  versionSelector->addItem("1.20-pre4");
  versionSelector->addItem("1.19.4-pre4");
  versionSelector->addItem("23w17a");
  versionSelector->setCurrentIndex(0);
}

void DashBoard::addMenuTab() noexcept {
  QMenu *fileMenu = new QMenu(tr("File"));
  QMenu *settingsMenu = new QMenu(tr("Settings"));
  QMenu *helpMenu = new QMenu(tr("Help"));

  menuBar->addMenu(fileMenu);
  menuBar->addMenu(settingsMenu);
  menuBar->addMenu(helpMenu);

  QAction *openAction = new QAction(tr("Open"));
  openAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
  QAction *helpAction = new QAction(tr("Help"));
  helpAction->setShortcut(QKeySequence(Qt::ALT | Qt::Key_H));
  QAction *aboutAction = new QAction(tr("About"));
  aboutAction->setShortcut(QKeySequence(Qt::ALT | Qt::Key_Z));
  QAction *clearLogsAction = new QAction(tr("Clear logs"));
  QAction *exitAction = new QAction(tr("Exit"));
  exitAction->setShortcut(Qt::CTRL | Qt::Key_Q);
  QAction *settingsAction = new QAction(tr("Settings Game"));

  fileMenu->addAction(openAction);
  fileMenu->addAction(clearLogsAction);
  fileMenu->addAction(exitAction);

  settingsMenu->addAction(settingsAction);

  helpMenu->addAction(helpAction);
  helpMenu->addAction(aboutAction);

  QObject::connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);

  QObject::connect(helpAction, &QAction::triggered, qApp,
                   &QApplication::aboutQt);

  QObject::connect(aboutAction, &QAction::triggered, this, []() {
    QDesktopServices::openUrl(QUrl(
        QDir::toNativeSeparators(Path::launcherPath() + "/../" +
                                 "/MineLaunch/resources/aboutLaunch.html")));
  });

  QObject::connect(clearLogsAction, &QAction::triggered, this,
                   [this]() { cl.clearLogs(); });

  QObject::connect(openAction, &QAction::triggered, this, [this]() {
    QString directory = QFileDialog::getExistingDirectory(
        this, tr("Select game directory"), QDir::homePath());
    if (!directory.isEmpty()) {
      QMessageBox::warning(this, "Warning",
                           "Directory doesn't exists or incorrect");
    }
  });
}

void DashBoard::addSettings() noexcept {
  QWidget *widgetSettings = new QWidget(this);
  tabWidget->addTab(widgetSettings, tr("Settings"));

  saveButton = new QPushButton(tr("Save"));
  resetButton = new QPushButton(tr("Reset"));

  brightnessSlider = new QSlider(Qt::Horizontal);
  brightnessSlider->setMinimum(0);
  brightnessSlider->setMaximum(50);
  brightnessSlider->setValue(25);
  brightnessSlider->setStyleSheet(sliderStyle);

  soundSlider = new QSlider(Qt::Horizontal);
  soundSlider->setMinimum(0);
  soundSlider->setMaximum(50);
  soundSlider->setValue(25);
  soundSlider->setStyleSheet(sliderStyle);

  choiceColorButton = new QSlider(Qt::Horizontal);
  choiceColorButton->setMinimum(0);
  choiceColorButton->setValue(25);
  choiceColorButton->setMaximum(50);
  choiceColorButton->setStyleSheet(sliderStyle);

  choiceColorButtonText = new QSlider(Qt::Horizontal);
  choiceColorButtonText->setMinimum(0);
  choiceColorButtonText->setMaximum(50);
  choiceColorButtonText->setValue(25);
  choiceColorButtonText->setStyleSheet(sliderStyle);

  maximumUseMemory = new QSlider(Qt::Horizontal);
  maximumUseMemory->setValue(4586);
  maximumUseMemory->setMinimum(2048);
  maximumUseMemory->setMaximum(64000);
  maximumUseMemory->setStyleSheet(sliderStyle);

  minimumUseMemory = new QSlider(Qt::Horizontal);
  minimumUseMemory->setValue(4586);
  minimumUseMemory->setMinimum(2048);
  minimumUseMemory->setMaximum(64000);
  minimumUseMemory->setStyleSheet(sliderStyle);

  choiceColor = new QSlider(Qt::Horizontal);
  choiceColor->setMinimum(0);
  choiceColor->setMaximum(50);
  choiceColor->setValue(25);
  choiceColor->setStyleSheet(sliderStyle);

  screenExtension = new QComboBox();
  screenExtension->addItem(tr("2560x1440"));
  screenExtension->addItem(tr("1920x1080"));
  screenExtension->addItem(tr("1280x720"));
  screenExtension->addItem(tr("1024x768"));
  screenExtension->addItem(tr("854x480"));

  QLabel *languageLabel = new QLabel(tr("Language"));
  choiceLanguage = new QComboBox();
  choiceLanguage->addItem(tr("English"));
  choiceLanguage->addItem(tr("Russian"));

  qualityGraphic = new QComboBox();
  qualityGraphic->addItem(tr("Low"));
  qualityGraphic->addItem(tr("Medium"));
  qualityGraphic->addItem(tr("High"));
  qualityGraphic->addItem(tr("Ultra"));

  groupBoxGame = new QGroupBox(tr("Settings Game"));
  groupBoxLauncher = new QGroupBox(tr("Settings Launcher"));
  groupLauncherState = new QGroupBox(tr("After Launch State"));
  groupMemorySettings = new QGroupBox(tr("Game Memory Settings"));

  groupBoxGame->setFont(QFont("Arial", 12, QFont::Bold));
  groupBoxLauncher->setFont(QFont("Arial", 12, QFont::Bold));
  groupLauncherState->setFont(QFont("Arial", 12, QFont::Bold));
  groupMemorySettings->setFont(QFont("Arial", 12, QFont::Bold));

  fullScreen = new QRadioButton(tr("Full Screen"));
  windowMode = new QRadioButton(tr("Window Mode"));
  launcherOpen = new QRadioButton(tr("Keep Launcher Open"));
  launcherClose = new QRadioButton(tr("Close Launcher"));
  buttonGroup = new QButtonGroup();
  buttonGroup->addButton(fullScreen);
  buttonGroup->addButton(windowMode);
  fullScreen->setChecked(true);

  QLabel *screenLabel = new QLabel(tr("Screen Mode"));
  QLabel *brightLabel = new QLabel(tr("Brightness"));
  QLabel *soundLabel = new QLabel(tr("Sound"));
  QLabel *extenstionLabel = new QLabel(tr("Screen Extension"));
  QLabel *qualityLabel = new QLabel(tr("Quality Graphic"));
  QLabel *colorButtonLabel = new QLabel(tr("Color Button"));
  QLabel *colorButtonTextLabel = new QLabel(tr("Color Button Text"));
  QLabel *colorLabel = new QLabel(tr("Color Launcher"));
  QLabel *minimumUseMemoryLabel = new QLabel(tr("Minimum Use Memory: 2048 MB"));
  QLabel *maximumUseMemoryLabel = new QLabel(tr("Maximum Use Memory: 2048 MB"));

  QFont font("Arial", 11, QFont::Bold);
  screenLabel->setFont(font);
  soundLabel->setFont(font);
  extenstionLabel->setFont(font);
  qualityLabel->setFont(font);
  brightLabel->setFont(font);
  colorLabel->setFont(font);
  colorButtonLabel->setFont(font);
  colorButtonTextLabel->setFont(font);

  QVBoxLayout *memoryLayout = new QVBoxLayout;
  memoryLayout->addWidget(minimumUseMemoryLabel);
  memoryLayout->addWidget(minimumUseMemory);
  memoryLayout->addSpacing(12);
  memoryLayout->addWidget(maximumUseMemoryLabel);
  memoryLayout->addWidget(maximumUseMemory);

  groupMemorySettings->setLayout(memoryLayout);

  QVBoxLayout *stateLaunchLayout = new QVBoxLayout;
  stateLaunchLayout->addWidget(launcherOpen);
  stateLaunchLayout->addWidget(launcherClose);

  groupLauncherState->setLayout(stateLaunchLayout);

  QHBoxLayout *buttonLayout = new QHBoxLayout;
  buttonLayout->addWidget(saveButton);
  buttonLayout->addWidget(resetButton);
  buttonLayout->setAlignment(Qt::AlignRight | Qt::AlignBottom);

  QVBoxLayout *settingLayoutGame = new QVBoxLayout;
  settingLayoutGame->addWidget(screenLabel);
  settingLayoutGame->addWidget(fullScreen);
  settingLayoutGame->addWidget(windowMode);
  settingLayoutGame->addWidget(soundLabel);
  settingLayoutGame->addWidget(soundSlider);
  settingLayoutGame->addWidget(brightLabel);
  settingLayoutGame->addWidget(brightnessSlider);
  settingLayoutGame->addWidget(extenstionLabel);
  settingLayoutGame->addWidget(screenExtension);
  settingLayoutGame->addSpacing(6);
  settingLayoutGame->addWidget(qualityLabel);
  settingLayoutGame->addWidget(qualityGraphic);
  settingLayoutGame->addSpacing(6);
  settingLayoutGame->addWidget(languageLabel);
  settingLayoutGame->addWidget(choiceLanguage);

  groupBoxGame->setLayout(settingLayoutGame);

  QFrame *separator = new QFrame();
  separator->setFrameShape(QFrame::HLine);
  separator->setFrameShadow(QFrame::Sunken);
  separator->setFixedHeight(3);

  QVBoxLayout *settingLauncherLayout = new QVBoxLayout;
  settingLauncherLayout->addWidget(colorLabel);
  settingLauncherLayout->addWidget(choiceColor);
  settingLauncherLayout->addWidget(colorButtonLabel);
  settingLauncherLayout->addWidget(choiceColorButton);
  settingLauncherLayout->addWidget(colorButtonTextLabel);
  settingLauncherLayout->addWidget(choiceColorButtonText);
  settingLauncherLayout->addWidget(separator);

  groupBoxLauncher->setLayout(settingLauncherLayout);

  QVBoxLayout *l_layout = new QVBoxLayout(widgetSettings);
  l_layout->addWidget(groupBoxGame);
  l_layout->addWidget(groupMemorySettings);
  l_layout->addWidget(groupBoxLauncher);
  l_layout->addWidget(groupLauncherState);
  l_layout->addLayout(buttonLayout);

  QObject::connect(choiceColor, &QSlider::valueChanged, this,
                   &DashBoard::onSliderValueChanged);

  QObject::connect(choiceColorButton, &QSlider::valueChanged, this,
                   &DashBoard::onSliderValueChanged);

  QObject::connect(choiceColorButtonText, &QSlider::valueChanged, this,
                   &DashBoard::onSliderValueChanged);

  QObject::connect(minimumUseMemory, &QSlider::valueChanged, this,
                   [minimumUseMemoryLabel, this](int value) {
                     QString textValue =
                         QString("Minimum Memory: %1 MB").arg(value);
                     minimumUseMemoryLabel->setText(textValue);
                   });

  QObject::connect(maximumUseMemory, &QSlider::valueChanged, this,
                   [maximumUseMemoryLabel, this](int value) {
                     QString textValue =
                         QString("Maximum Memory: %1 MB").arg(value);
                     maximumUseMemoryLabel->setText(textValue);
                   });

  m_custom->setMaxAndMinMemory(
      QStringList() << "-Xmx" << QString::number(maximumUseMemory->value())
                    << "-Xms" << QString::number(minimumUseMemory->value()));

  QObject::connect(saveButton, &QPushButton::clicked, this, [this]() {
    const QString extension = screenExtension->currentText();
    const auto argsExtension = QStringList()
                               << "-w" << extension.split("x").at(0) << "-h"
                               << extension.split("x").at(1);
    m_custom->setExtensionGame(argsExtension);

    if (fullScreen->isChecked()) {
      m_custom->setScreenMode(QStringList() << "--fullscreen");

    } else if (windowMode->isChecked()) {
      const auto argsWindowMode = QStringList() << "--width"
                                                << "1300"
                                                << "--height"
                                                << "750";
      m_custom->setScreenMode(argsWindowMode);
    }

    if (choiceLanguage->currentText() == "Russian") {
      m_custom->setLanguage(QStringList() << "--lang"
                                          << "ru");

    } else {
      m_custom->setLanguage(QStringList() << "--lang"
                                          << "en");
    }

    if (launcherOpen->isChecked()) {
      return;
    } else if (launcherClose->isChecked()) {
      QObject::connect(playButton, &QPushButton::clicked, this,
                       [this]() { this->close(); });
    }

    int soundValue = soundSlider->value();
    m_custom->setSound(QStringList()
                       << "--soundVolume" << QString::number(soundValue));

    int gammaValue = brightnessSlider->value();
    auto argsGamma = QStringList() << "--gamma" << QString::number(gammaValue);
    m_custom->setBrightness(argsGamma);

    const QString quality = qualityGraphic->currentText();
    const auto argsQuality = QStringList() << "--quality" << quality;
    m_custom->setQualityGraphic(argsQuality);

    auto languageSelected = choiceLanguage->currentText();
    if (languageSelected == "Russian") {
      emit sendSaveLanguage(RUSSIAN_LANG);
    } else {
      emit sendSaveLanguage(ENGLISH_LANG);
    }
  });

  QObject::connect(resetButton, &QPushButton::clicked, this,
                   [this]() { settings.remove("style"); });

  setSaveSettingsUI();
}

void DashBoard::setSaveSettingsUI() {
  auto screenMode = m_custom->getScreenMode();
  if (screenMode.contains("--fullscreen")) {
    fullScreen->setChecked(true);
  } else {
    windowMode->setChecked(true);
  }
}

void DashBoard::addGameTab() noexcept {
  QWidget *widgetShowGame = new QWidget(this);
  widgetShowGame->setStyleSheet(
      "background-image: url(" +
      QDir::toNativeSeparators(Path::launcherPath() + "/../" +
                               "/MineLaunch/resources/mangrove-river-1.png);"));

  QVBoxLayout *gameLayout = new QVBoxLayout(widgetShowGame);
  tabWidget->addTab(widgetShowGame, tr("Game"));

  playButton = new QPushButton(tr("Play"));
  cancelButton = new QPushButton(tr("Cancel"));
  downloadButton = new QPushButton(tr("Download"));

  QFont font("Arial", 16, QFont::Bold);
  playButton->setFont(font);
  cancelButton->setFont(font);
  downloadButton->setFont(font);

  versionSelector->setFont(QFont("Arial", 12, QFont::Bold));
  versionSelector->setFixedWidth(105);
  versionSelector->setStyleSheet("background-color: dark-green ;color: green;");
  versionSelector->setFocusPolicy(Qt::NoFocus);

  QHBoxLayout *hbox_layout = new QHBoxLayout;
  hbox_layout->addWidget(versionSelector);
  hbox_layout->addStretch();
  hbox_layout->addWidget(playButton);
  hbox_layout->addSpacing(8);
  hbox_layout->addWidget(cancelButton);
  hbox_layout->addSpacing(8);
  hbox_layout->addWidget(downloadButton);
  hbox_layout->setAlignment(Qt::AlignLeft | Qt::AlignBottom);

  QHBoxLayout *layout = new QHBoxLayout();
  gameLayout->setMenuBar(menuBar);
  gameLayout->addLayout(layout);
  gameLayout->addLayout(hbox_layout);

  QObject::connect(playButton, &QPushButton::clicked, this, [this]() {
    QString version = versionSelector->currentText();
    emit sendSaveVersionGame(version);
    m_play->start();
  });

  QObject::connect(downloadButton, &QPushButton::clicked, this, [this]() {
    QString version = versionSelector->currentText();
    emit sendSaveVersionGame(version);
    m_download->start();
  });

  QObject::connect(cancelButton, &QPushButton::clicked, this, [this]() {
    if (m_play->gameIsRunning()) {
      m_play->stop();
    } else if (m_download->IsDownloading()) {
      m_download->stop();
    }
  });
}

void DashBoard::searchModsByName() {
  QString nameMod = editSearch->text();
  QTableWidgetItem *item = nullptr;
  if (!nameMod.isEmpty()) {
    QList<QTableWidgetItem *> items =
        modsTable->findItems(nameMod, Qt::MatchContains);

    if (!items.isEmpty()) {
      item = items.first();
    }
  }

  if (item != nullptr) {
    modsTable->setCurrentItem(item);
    modsTable->scrollToItem(item);
  } else {
    QMessageBox::warning(this, "Not Found", "The item was not found");
  }
}

void DashBoard::onSliderValueChanged(int value) {
  Q_UNUSED(value);

  QString tabStyle;
  if (choiceColorButton->value() <= 5) {
    tabStyle += "QPushButton { background-color: cyan; } ";
  } else if (choiceColorButton->value() <= 10) {
    tabStyle += "QPushButton { background-color: grey; } ";
  } else if (choiceColorButton->value() <= 15) {
    tabStyle += "QPushButton { background-color: aqua; } ";
  } else if (choiceColorButton->value() <= 22) {
    tabStyle += "QPushButton { background-color: blueviolet; } ";
  } else if (choiceColorButton->value() <= 24) {
    tabStyle += "QPushButton { background-color: lightgreen; } ";
  } else if (choiceColorButton->value() <= 25) {
    tabStyle += "QPushButton { background-color: peru; } ";
  } else if (choiceColorButton->value() <= 27) {
    tabStyle += "QPushButton { background-color: magenta; } ";
  } else if (choiceColorButton->value() <= 30) {
    tabStyle += "QPushButton { background-color: green; } ";
  } else if (choiceColorButton->value() <= 35) {
    tabStyle += "QPushButton { background-color: darkcyan; } ";
  } else if (choiceColorButton->value() <= 45) {
    tabStyle += "QPushButton { background-color: azure; } ";
  } else if (choiceColorButton->value() <= 50) {
    tabStyle += "QPushButton { background-color: brown; } ";
  }

  if (choiceColor->value() <= 5) {
    tabStyle +=
        "QTabWidget::pane { border-color: gray; background-color: violet; } ";
  } else if (choiceColor->value() <= 10) {
    tabStyle +=
        "QTabWidget::pane { border-color: gray; background-color: brown; } ";
  } else if (choiceColor->value() <= 15) {
    tabStyle +=
        "QTabWidget::pane { border-color: gray; background-color: olive; } ";
  } else if (choiceColor->value() <= 22) {
    tabStyle +=
        "QTabWidget::pane { border-color: gray; background-color: peach; } ";
  } else if (choiceColor->value() <= 24) {
    tabStyle +=
        "QTabWidget::pane { border-color: gray; background-color: maroon; } ";
  } else if (choiceColor->value() <= 25) {
    tabStyle +=
        "QTabWidget::pane { border-color: gray; background-color: white; } ";
  } else if (choiceColor->value() <= 30) {
    tabStyle +=
        "QTabWidget::pane { border-color: gray; background-color: cyan; } ";
  } else if (choiceColor->value() <= 35) {
    tabStyle += "QTabWidget::pane { border-color: gray; background-color: "
                "lightgreen; } ";
  } else if (choiceColor->value() <= 40) {
    tabStyle += "QTabWidget::pane { border-color: gray; background-color: "
                "darkorange; } ";
  } else if (choiceColor->value() <= 45) {
    tabStyle +=
        "QTabWidget::pane { border-color: gray; background-color: blue; } ";
  } else if (choiceColor->value() <= 50) {
    tabStyle +=
        "QTabWidget::pane { border-color: gray; background-color: crimson; } ";
  }

  if (choiceColorButtonText->value() <= 5) {
    tabStyle += "QPushButton { color: blue; } ";
  } else if (choiceColorButtonText->value() <= 15) {
    tabStyle += "QPushButton { color: grey; } ";
  } else if (choiceColorButtonText->value() <= 15) {
    tabStyle += "QPushButton { color: magenta; } ";
  } else if (choiceColorButtonText->value() <= 22) {
    tabStyle += "QPushButton { color: black; } ";
  } else if (choiceColorButtonText->value() <= 24) {
    tabStyle += "QPushButton { color: violet; } ";
  } else if (choiceColorButtonText->value() <= 25) {
    tabStyle += "QPushButton { color: green; } ";
  } else if (choiceColorButtonText->value() <= 30) {
    tabStyle += "QPushButton { color: peru; } ";
  } else if (choiceColorButtonText->value() <= 35) {
    tabStyle += "QPushButton { color: white; } ";
  } else if (choiceColorButtonText->value() <= 40) {
    tabStyle += "QPushButton { color: maroon; } ";
  } else if (choiceColorButtonText->value() <= 45) {
    tabStyle += "QPushButton { color: limegreen; } ";
  } else if (choiceColorButtonText->value() <= 50) {
    tabStyle += "QPushButton { color: darkblue; } ";
  }

  tabWidget->setStyleSheet(tabStyle);
  settings.setValue("style", tabWidget->styleSheet());
}
