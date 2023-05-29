#include "./include/dashboard.hpp"

DashBoard::DashBoard(QWidget *parent) : QDialog(parent) {
  tabWidget = new QTabWidget(this);
  tabWidget->setFixedSize(QSize(780, 640));
  modsTable = new QTableWidget();
  versionSelector = new QComboBox();
  versionSelector->setFixedWidth(100);
  menuBar = new QMenuBar();
  initalizeUI();
}

DashBoard::~DashBoard() {}

void DashBoard::initalizeUI() {
  addMenu();
  loadVersionsMinecraft();
  playGame();
  loadMods();

  this->setMinimumSize(780, 640);
  this->setWindowTitle("Minecraft Launcher");
}

void DashBoard::loadMods() {
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

void DashBoard::loadVersionsMinecraft() {
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
  });
}

void DashBoard::addMenu() {
  QMenu *fileMenu = new QMenu(tr("File"));
  QMenu *settingsMenu = new QMenu(tr("Settings"));
  QMenu *helpMenu = new QMenu(tr("Help"));

  menuBar->addMenu(fileMenu);
  menuBar->addMenu(settingsMenu);
  menuBar->addMenu(helpMenu);

  QAction *fileAction = new QAction(tr("Open file"));
  QAction *helpAction = new QAction(tr("Help use MineLaucnh"));
  QAction *settingAction = new QAction(tr("dsd"));
  fileMenu->addAction(fileAction);
  settingsMenu->addAction(settingAction);
  helpMenu->addAction(helpAction);
}

void DashBoard::playGame() {
  QWidget *widgetShowGame = new QWidget();

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
  hbox_layout->setAlignment(Qt::AlignRight | Qt::AlignBottom);

  QHBoxLayout *layout = new QHBoxLayout();
  layout->insertLayout(0, pixmapLayout);
  layout->setAlignment(Qt::AlignCenter);
  gameLayout->setMenuBar(menuBar);
  gameLayout->addLayout(layout);
  gameLayout->addLayout(hbox_layout);
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
