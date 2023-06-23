#include "./include/dashboard.hpp"
#include "./assistance/path.hpp"

DashBoard::DashBoard(QWidget *parent)
    : QDialog(parent), tabWidget(new QTabWidget(this)),
      modsTable(new QTableWidget()), versionSelector(new QComboBox()),
      menuBar(new QMenuBar()) {

  m_play = dynamic_cast<PlayGame *>(
      FactoryLauncher::createLauncher(LauncherType::Play));
  m_download = dynamic_cast<Downloader *>(
      FactoryLauncher::createLauncher(LauncherType::Download));

  QObject::connect(this, &DashBoard::sendVersionGame, m_download,
                   &Downloader::getVersionGame);
  QObject::connect(this, &DashBoard::sendVersionGame, m_play,
                   &PlayGame::getVersionGame);

  tabWidget->setFixedSize(QSize(1050, 710));
  versionSelector->setFixedWidth(100);
  initalizeUI();
}

DashBoard::~DashBoard() {}

void DashBoard::initalizeUI() noexcept {
  loadVersionsMinecraft();
  addGameTab();
  loadMods();
  addMenuTab();
  loadServers();
  UserSettings::getInstance().initalizeGuiSettings(tabWidget);
  addSettings();

  this->setMinimumSize(1050, 710);
  this->setWindowTitle("Minecraft Launcher");
}

void DashBoard::loadMods() noexcept {
  QWidget *widgetMods = new QWidget();
  QVBoxLayout *modsLayout = new QVBoxLayout(widgetMods);
  modsTable->setColumnCount(3);
  for (int i = 0; i < 3; i++) {
    modsTable->setColumnWidth(i, 350);
  }
  modsTable->setHorizontalHeaderLabels({"Name", "Description", "File"});

  searchButton = new QPushButton(tr("Search"));
  downloadButton = new QPushButton(tr("Download"));

  QHBoxLayout *searchLayout = new QHBoxLayout;
  searchLayout->addWidget(downloadButton);
  searchLayout->addWidget(searchButton);
  searchLayout->setAlignment(Qt::AlignRight);

  editSearch = new QLineEdit();
  editSearch->setPlaceholderText("What's mod do you need?");

  modsLayout->addWidget(editSearch);
  modsLayout->addLayout(searchLayout);
  modsLayout->addWidget(modsTable);

  tabWidget->addTab(widgetMods, "Mods");

  QFile file(Path::launcherPath() + "/../" +
             "/MineLaunch/resources/mods/config/config.json");
  if (!file.open(QIODevice::ReadOnly)) {
    logger.log(LogLevel::Error, "Failed to open file [addMods]");
    return;
  }

  QByteArray jsonData = file.readAll();
  QJsonDocument doc = QJsonDocument::fromJson(jsonData);

  if (!doc.isArray()) {
    logger.log(LogLevel::Error, "Wrong format file");
    return;
  }

  QJsonArray modsArr = doc.array();
  for (const QJsonValue &modValue : modsArr) {
    QJsonObject modObj = modValue.toObject();
    QString name = modObj.value("name").toString();
    QString description = modObj.value("description").toString();
    QString file = modObj.value("file").toString();

    Mod mod;
    mod.name = name;
    mod.description = description;
    mod.file = file;
    loadedMods.append(mod);
  }

  file.close();

  for (const Mod &mod : loadedMods) {
    const int row = modsTable->rowCount();
    modsTable->insertRow(row);

    auto *nameItem = new QTableWidgetItem(mod.name);
    modsTable->setItem(row, 0, nameItem);

    auto *descItem = new QTableWidgetItem(mod.description);
    modsTable->setItem(row, 1, descItem);

    auto *fileItem = new QTableWidgetItem(QFileInfo(mod.file).fileName());
    modsTable->setItem(row, 2, fileItem);
  }

  int rowCount = modsTable->rowCount();
  int columnCount = modsTable->columnCount();

  for (int row = 0; row < rowCount; row++) {
    for (int column = 0; column < columnCount; column++) {
      auto items = modsTable->item(row, column);
      if (items) {
        items->setFlags(items->flags() & ~Qt::ItemIsEditable);
      }
    }
  }

  QObject::connect(searchButton, &QPushButton::clicked, this,
                   &DashBoard::searchModsByName);

  QObject::connect(downloadButton, &QPushButton::clicked, this, [&]() {

  });
}

void DashBoard::loadServers() noexcept {

  QWebEngineView *webView = new QWebEngineView(this);

  webView->load(QUrl("https://minecraft-server-list.com/"));
  webView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  connectButton = new QPushButton(tr("Connect"));
  editIPServer = new QLineEdit();
  editIPServer->setPlaceholderText("Enter IP address for connect to server");

  QHBoxLayout *buttonLayout = new QHBoxLayout();
  buttonLayout->addWidget(editIPServer);
  buttonLayout->addWidget(connectButton);
  buttonLayout->setAlignment(Qt::AlignRight | Qt::AlignBottom);

  QWidget *container = new QWidget();
  QVBoxLayout *layout = new QVBoxLayout();
  layout->addWidget(webView);
  layout->addLayout(buttonLayout);
  container->setLayout(layout);

  tabWidget->addTab(container, "Servers");

  QObject::connect(connectButton, &QPushButton::clicked, this, []() {

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
  helpAction->setShortcut(tr("F1"));

  QAction *aboutAction = new QAction(tr("About"));
  aboutAction->setShortcut(tr("F2"));

  QAction *clearLogs = new QAction(tr("Clear logs"));

  QAction *exitAction = new QAction(tr("Exit"));
  exitAction->setShortcut(Qt::CTRL | Qt::Key_Q);

  QAction *settingsAction = new QAction(tr("Settings Game"));


  fileMenu->addAction(openAction);
  fileMenu->addAction(clearLogs);
  fileMenu->addAction(exitAction);
  settingsMenu->addAction(settingsAction);
  helpMenu->addAction(helpAction);
  helpMenu->addAction(aboutAction);

  QObject::connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);

  QObject::connect(helpAction,&QAction::triggered,this,[this](){
      tabWidget->setCurrentIndex(4);
  });

  QObject::connect(aboutAction, &QAction::triggered, this, []() {
    QDesktopServices::openUrl(QUrl(Path::launcherPath()+ "/../" +
                                     "/MineLaunch/resources/aboutLaunch.html"));
  });
}

void DashBoard::addSettings() noexcept {
  QWidget *widgetSettings = new QWidget(this);
  tabWidget->addTab(widgetSettings, "Settings");

  saveButton = new QPushButton(tr("Save"));
  resetButton = new QPushButton(tr("Reset"));

  brightnessSlider = new QSlider(Qt::Horizontal);
  brightnessSlider->setMinimum(0);
  brightnessSlider->setMaximum(100);
  brightnessSlider->setValue(50);

  soundSlider = new QSlider(Qt::Horizontal);
  soundSlider->setMinimum(0);
  soundSlider->setMaximum(100);
  soundSlider->setValue(100);

  screenExtension = new QComboBox();
  screenExtension->addItem(tr("1920x1080"));
  screenExtension->addItem(tr("1280x760"));
  screenExtension->addItem(tr("1024x768"));

  QLabel *colorLabel = new QLabel(tr("Color Launcher"));
  choiceColor = new QSlider(Qt::Horizontal);
  choiceColor->setMinimum(0);
  choiceColor->setMaximum(100);
  choiceColor->setValue(25);

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

  groupBoxGame->setFont(QFont("Arial", 12, QFont::Bold));
  groupBoxLauncher->setFont(QFont("Arial", 12, QFont::Bold));

  fullScreen = new QRadioButton(tr("Full Screen"));
  windowMode = new QRadioButton(tr("Window Mode"));
  buttonGroup = new QButtonGroup();
  buttonGroup->addButton(fullScreen);
  buttonGroup->addButton(windowMode);
  fullScreen->setChecked(true);

  QLabel *screenLabel = new QLabel(tr("Screen Mode"));
  QLabel *brightLabel = new QLabel(tr("Brightness"));
  QLabel *soundLabel = new QLabel(tr("Sound"));
  QLabel *extenstionLabel = new QLabel(tr("Screen Extension"));
  QLabel *qualityLabel = new QLabel(tr("Quality Graphic"));

  QFont font("Arial", 11, QFont::Bold);

  screenLabel->setFont(font);
  soundLabel->setFont(font);
  extenstionLabel->setFont(font);
  qualityLabel->setFont(font);
  brightLabel->setFont(font);
  colorLabel->setFont(font);

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
  settingLayoutGame->addWidget(qualityLabel);
  settingLayoutGame->addWidget(qualityGraphic);

  groupBoxGame->setLayout(settingLayoutGame);

  QFrame *separator = new QFrame();
  separator->setFrameShape(QFrame::HLine);
  separator->setFrameShadow(QFrame::Sunken);
  separator->setFixedHeight(3);

  QVBoxLayout *settingLauncherLayout = new QVBoxLayout;
  settingLauncherLayout->addWidget(colorLabel);
  settingLauncherLayout->addWidget(choiceColor);
  settingLauncherLayout->addWidget(separator);
  settingLauncherLayout->addWidget(languageLabel);
  settingLauncherLayout->addWidget(choiceLanguage);

  groupBoxLauncher->setLayout(settingLauncherLayout);

  QVBoxLayout *l_layout = new QVBoxLayout(widgetSettings);
  l_layout->addWidget(groupBoxGame);
  l_layout->addWidget(groupBoxLauncher);
  l_layout->addLayout(buttonLayout);

  QObject::connect(choiceColor, &QSlider::valueChanged, this,
                   &DashBoard::onSliderValueChanged);

  QObject::connect(saveButton, &QPushButton::clicked, this, []() {

  });

  QObject::connect(resetButton, &QPushButton::clicked, this, []() {

  });
}

void DashBoard::addGameTab() noexcept {
  QWidget *widgetShowGame = new QWidget(this);

  QVBoxLayout *gameLayout = new QVBoxLayout(widgetShowGame);
  tabWidget->addTab(widgetShowGame, "Game");

  QLabel *image = new QLabel();
  QPixmap pixmap(Path::launcherPath() + "/../" +
                 "/MineLaunch/resources/images.png");
  QPixmap scaledPixmap = pixmap.scaled(QSize(480, 290), Qt::KeepAspectRatio);
  image->setPixmap(scaledPixmap);

  QVBoxLayout *pixmapLayout = new QVBoxLayout;
  pixmapLayout->addWidget(image);
  pixmapLayout->setAlignment(Qt::AlignCenter);

  playButton = new QPushButton(tr("Play"));
  cancelButton = new QPushButton(tr("Cancel"));
  downloadButton = new QPushButton(tr("Download"));

  QHBoxLayout *hbox_layout = new QHBoxLayout;
  hbox_layout->addWidget(versionSelector);
  hbox_layout->addStretch();
  hbox_layout->addWidget(playButton);
  hbox_layout->addWidget(cancelButton);
  hbox_layout->addWidget(downloadButton);
  hbox_layout->setAlignment(Qt::AlignLeft | Qt::AlignBottom);

  QHBoxLayout *layout = new QHBoxLayout();
  layout->insertLayout(0, pixmapLayout);
  layout->setAlignment(Qt::AlignCenter);
  gameLayout->setMenuBar(menuBar);
  gameLayout->addLayout(layout);
  gameLayout->addLayout(hbox_layout);

  QObject::connect(playButton, &QPushButton::clicked, this, [this]() {
    QString version = versionSelector->currentText();
    emit sendVersionGame(version);
    m_play->start();
  });

  QObject::connect(downloadButton, &QPushButton::clicked, this, [this]() {
    QString version = versionSelector->currentText();
    emit sendVersionGame(version);
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

  const QString tabStyle =
      "QTabWidget::pane { border-color: gray; background-color: ";
  if (value <= 10) {
    tabWidget->setStyleSheet(tabStyle + "cyan; }");
  } else if (value <= 20) {
    tabWidget->setStyleSheet(tabStyle + "grey; }");
  } else if (value <= 30) {
    tabWidget->setStyleSheet(tabStyle + "green; }");
  } else if (value <= 40) {
    tabWidget->setStyleSheet(tabStyle + "brown; }");
  } else if (value <= 50) {
    tabWidget->setStyleSheet(tabStyle + "peach; }");
  } else if (value <= 60) {
    tabWidget->setStyleSheet(tabStyle + "white; } ");
  } else if (value <= 70) {
    tabWidget->setStyleSheet(tabStyle + "blue; }");
  } else if (value <= 85) {
    tabWidget->setStyleSheet(tabStyle + "grey; }");
  } else if (value <= 95) {
    tabWidget->setStyleSheet(tabStyle + "magenta; }");
  } else if (value <= 100) {
    tabWidget->setStyleSheet(tabStyle + "black; }");
  }
}
