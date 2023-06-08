#include "./include/dashboard.hpp"

DashBoard::DashBoard(QWidget *parent)
    : QDialog(parent), tabWidget(new QTabWidget(this)),
      modsTable(new QTableWidget()), versionSelector(new QComboBox()),
      menuBar(new QMenuBar()) {
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

  search = new QPushButton(tr("Search"));
  download = new QPushButton(tr("Download"));

  QHBoxLayout *searchLayout = new QHBoxLayout;
  searchLayout->addWidget(download);
  searchLayout->addWidget(search);
  searchLayout->setAlignment(Qt::AlignRight);

  editSearch = new QLineEdit();
  editSearch->setPlaceholderText("What's mod do you need?");

  modsLayout->addWidget(editSearch);
  modsLayout->addLayout(searchLayout);
  modsLayout->addWidget(modsTable);

  tabWidget->addTab(widgetMods, "Mods");

  QFile file(QCoreApplication::applicationDirPath() + "/../" +
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

  QObject::connect(search, &QPushButton::clicked, this,
                   &DashBoard::searchModsByName);

  QObject::connect(download, &QPushButton::clicked, this, [&]() {

  });
}

void DashBoard::loadServers() noexcept {

  QWebEngineView *webView = new QWebEngineView(this);

  webView->load(QUrl("https://minecraft-server-list.com/"));
  webView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  connect = new QPushButton(tr("Connect"));
  editIPServer = new QLineEdit();
  editIPServer->setPlaceholderText("Enter IP address for connect to server");

  QHBoxLayout *buttonLayout = new QHBoxLayout();
  buttonLayout->addWidget(editIPServer);
  buttonLayout->addWidget(connect);
  buttonLayout->setAlignment(Qt::AlignRight | Qt::AlignBottom);

  QWidget *container = new QWidget();
  QVBoxLayout *layout = new QVBoxLayout();
  layout->addWidget(webView);
  layout->addLayout(buttonLayout);
  container->setLayout(layout);

  tabWidget->addTab(container, "Servers");

  QObject::connect(connect, &QPushButton::clicked, this, []() {

  });
}

void DashBoard::loadVersionsMinecraft() noexcept {
  QNetworkAccessManager *manager = new QNetworkAccessManager(this);
  QNetworkReply *reply = manager->get(QNetworkRequest(
      QUrl("https://launchermeta.mojang.com/mc/game/version_manifest.json")));

  QObject::connect(reply, &QNetworkReply::finished, this, [=]() {
    if (reply->error() != QNetworkReply::NoError) {
      logger.log(LogLevel::Error, reply->errorString().toStdString());
      return;
    }

    QByteArray jsonArray = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(jsonArray);

    QStringList versions;
    QJsonArray versionsArr = doc.object()["versions"].toArray();
    int numVersions = qMin(5, versionsArr.size());
    for (int i = 0; i < numVersions; i++) {
      QString versionName = versionsArr.at(i).toObject()["id"].toString();
      versions << versionName;
    }
    versionSelector->addItems(versions);
    reply->deleteLater();
  });
}

void DashBoard::addMenuTab() noexcept {
  QMenu *fileMenu = new QMenu(tr("File"));
  QMenu *settingsMenu = new QMenu(tr("Settings"));
  QMenu *helpMenu = new QMenu(tr("Help"));

  menuBar->addMenu(fileMenu);
  menuBar->addMenu(settingsMenu);
  menuBar->addMenu(helpMenu);

  QAction *openAction = new QAction(tr("Open"));
  openAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
  QAction *helpAction = new QAction(tr("Help"));
  QAction *aboutAction = new QAction(tr("About"));
  QAction *exitAction = new QAction(tr("Exit"));
  QAction *settingsAction = new QAction(tr("Settings Game"));
  exitAction->setShortcut(Qt::CTRL | Qt::Key_Q);

  fileMenu->addAction(openAction);
  fileMenu->addAction(exitAction);
  settingsMenu->addAction(settingsAction);
  helpMenu->addAction(helpAction);
  helpMenu->addAction(aboutAction);
}

void DashBoard::addSettings() noexcept {
  QWidget *widgetSettings = new QWidget(this);
  tabWidget->addTab(widgetSettings, "Settings");

  save = new QPushButton(tr("Save"));
  reset = new QPushButton(tr("Reset"));

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
  buttonLayout->addWidget(save);
  buttonLayout->addWidget(reset);
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

  QObject::connect(save, &QPushButton::clicked, this, []() {

  });

  QObject::connect(reset, &QPushButton::clicked, this, []() {

  });
}

void DashBoard::addGameTab() noexcept {
  QWidget *widgetShowGame = new QWidget(this);

  QVBoxLayout *gameLayout = new QVBoxLayout(widgetShowGame);
  tabWidget->addTab(widgetShowGame, "Game");

  QLabel *image = new QLabel();
  QPixmap pixmap(QCoreApplication::applicationDirPath() + "/../" +
                 "/MineLaunch/resources/images.jpeg");
  QPixmap scaledPixmap = pixmap.scaled(QSize(480, 290), Qt::KeepAspectRatio);
  image->setPixmap(scaledPixmap);

  QVBoxLayout *pixmapLayout = new QVBoxLayout;
  pixmapLayout->addWidget(image);
  pixmapLayout->setAlignment(Qt::AlignCenter);

  play = new QPushButton(tr("Play"));
  cancel = new QPushButton(tr("Cancel"));
  update = new QPushButton(tr("Update"));
  download = new QPushButton(tr("Download"));

  QHBoxLayout *hbox_layout = new QHBoxLayout;
  hbox_layout->addWidget(versionSelector);
  hbox_layout->addStretch();
  hbox_layout->addWidget(play);
  hbox_layout->addWidget(cancel);
  hbox_layout->addWidget(download);
  hbox_layout->addWidget(update);
  hbox_layout->setAlignment(Qt::AlignLeft | Qt::AlignBottom);

  QHBoxLayout *layout = new QHBoxLayout();
  layout->insertLayout(0, pixmapLayout);
  layout->setAlignment(Qt::AlignCenter);
  gameLayout->setMenuBar(menuBar);
  gameLayout->addLayout(layout);
  gameLayout->addLayout(hbox_layout);

  QObject::connect(play, &QPushButton::clicked, this, []() {

  });

  QObject::connect(cancel, &QPushButton::clicked, this, []() {

  });

  QObject::connect(download, &QPushButton::clicked, this, []() {

  });

  QObject::connect(update, &QPushButton::clicked, this, []() {

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
