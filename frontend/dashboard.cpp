#include "./include/dashboard.hpp"

DashBoard::DashBoard(QWidget *parent)
{
    setupUI();
}

DashBoard::~DashBoard()
{


}

void DashBoard::setupUI()
{
    QTabWidget* tabWidget = new QTabWidget(this);
    tabWidget->setFixedSize(QSize(850, 665));

    QWidget* widgetMods = new QWidget();
    QWidget* widgetCheckUpdates = new QWidget();
    QWidget* widgetManageServers = new QWidget();
    QWidget* widgetShowAboutGame = new QWidget();
    QWidget* widgetServerPerfomance = new QWidget();


    QVBoxLayout* gameLayout = new QVBoxLayout(widgetShowAboutGame);
    tabWidget->addTab(widgetShowAboutGame,"About Game");

    QVBoxLayout* modsLayout = new QVBoxLayout(widgetMods);
    auto files = fileList();
    QListWidget* listWidget = new QListWidget;
    listWidget->addItems(files);
    modsLayout->addWidget(listWidget);
    tabWidget->addTab(widgetMods, "Mods");


    QVBoxLayout* updateLayout = new QVBoxLayout( widgetCheckUpdates);
    tabWidget->addTab(widgetCheckUpdates,"Check Updates");

    QVBoxLayout* serversLayout = new QVBoxLayout(widgetManageServers );
    tabWidget->addTab(widgetManageServers,"Manage Servers");

    QVBoxLayout* perfomanceLayout = new QVBoxLayout( widgetServerPerfomance);
    tabWidget->addTab(widgetServerPerfomance,"Server Perfomance");



   play = new QPushButton(tr("Play"));
   cancel = new QPushButton(tr("Cancel"));
   update = new QPushButton(tr("Update"));

   QHBoxLayout* layout = new QHBoxLayout();
   layout->addWidget(play);
   layout->addWidget(cancel);
   layout->addWidget(update);
   layout->setAlignment(Qt::AlignRight | Qt::AlignBottom);
   gameLayout->addLayout(layout);

//   QMenuBar* menuBar = new QMenuBar(this);
//   QMenu* fileMenu = new QMenu(tr("File"),this);
//   QMenu* settingsMenu = new QMenu(tr("Settings"),this);

//   menuBar->addMenu(fileMenu);
//   menuBar->addMenu(settingsMenu);

 //  QAction* action = new QAction(tr("Good"));

   this->setFixedSize(850,665);
}


QStringList DashBoard::fileList() {
    QStringList nameFilter("*.jar*");
    QDir directory("/home/ruslan/Documents/MineLaunch/resources/mods/");
    QStringList files = directory.entryList(nameFilter,QDir::Files);
    return files;
}






