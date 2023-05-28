#include "./include/dashboard.hpp"

DashBoard::DashBoard(QWidget *parent) : QDialog(parent) {
  tabWidget = new QTabWidget(this);
  tabWidget->setFixedSize(QSize(1100, 760));
  modsTable = new QTableWidget();
  setupUI();
}

DashBoard::~DashBoard() {}

void DashBoard::setupUI() {

  addMods();

  this->setFixedSize(1100, 760);
}

void DashBoard::addMods() {
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

  QFile file(
      "/home/ruslan/Documents/MineLaunch/resources/mods/config/config.json");
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
        items->setFlags(items->flags() & Qt::ItemIsEnabled);
      }
    }
  }


  QObject::connect(search, &QPushButton::clicked, this,
                   &DashBoard::searchModsByName);

  QObject::connect(download, &QPushButton::clicked, [&]() {

  });
}

void DashBoard::playGame() {
  //  ///* QWidget *widgetCheckUpdates = new QWidget();
  //  //  QWidget *widgetManageServers = new QWidget();
  //  QWidget *widgetShowAboutGame = new QWidget();
  //  //  QWidget *widgetServerPerfomance = new QWidget();

  //  QVBoxLayout *gameLayout = new QVBoxLayout(widgetShowAboutGame);
  //  tabWidget->addTab(widgetShowAboutGame, "Game"); // for use game layout

  //  //  QVBoxLayout *updateLayout = new QVBoxLayout(widgetCheckUpdates);
  //  //  tabWidget->addTab(widgetCheckUpdates, "Check Updates");

  //  //  QVBoxLayout *serversLayout = new QVBoxLayout(widgetManageServers);
  //  //  tabWidget->addTab(widgetManageServers, "Manage Servers");

  //  //  QVBoxLayout *perfomanceLayout = new
  //  QVBoxLayout(widgetServerPerfomance);
  //  //  tabWidget->addTab(widgetServerPerfomance, "Server Perfomance");

  //  play = new QPushButton(tr("Play"));
  //  cancel = new QPushButton(tr("Cancel"));
  //  update = new QPushButton(tr("Update"));

  //  QHBoxLayout *layout = new QHBoxLayout();
  //  layout->addWidget(play);
  //  layout->addWidget(cancel);
  //  layout->addWidget(update);
  //  layout->setAlignment(Qt::AlignRight | Qt::AlignBottom);
  //  gameLayout->addLayout(layout);

  //  QObject::connect(search, &QPushButton::clicked, this,
  //                   &DashBoard::searchModsByName);

  //  QObject::connect(download, &QPushButton::clicked, [&]() {

  //  });

  //  //   QMenuBar* menuBar = new QMenuBar(this);
  //  //   QMenu* fileMenu = new QMenu(tr("File"),this);
  //  //   QMenu* settingsMenu = new QMenu(tr("Settings"),this);

  //  //   menuBar->addMenu(fileMenu);
  //  //   menuBar->addMenu(settingsMenu);

  //  //  QAction* action = new QAction(tr("Good"));
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

  if (item) {
    modsTable->setCurrentItem(item);
    modsTable->scrollToItem(item);
  } else {
    QMessageBox::warning(this, "Not Found", "The item was not found");
  }
}
