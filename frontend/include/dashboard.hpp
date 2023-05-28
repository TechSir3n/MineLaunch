#ifndef DASHBOARD_HPP
#define DASHBOARD_HPP

#include "signup.hpp"
#include <QMenu>
#include <QMenuBar>
#include <QListWidget>
#include <QTabWidget>
#include <QStringList>
#include <QDebug>
#include <QDialog>
#include <QPushButton>
#include <QRegularExpression>
#include <QAction>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTableWidget>
#include <QMap>
#include <QFileInfo>


struct Mod {
    QString name;
    QString description;
    QString file;
};

class DashBoard : public QDialog  {
public:
    DashBoard(QWidget* parent = nullptr);

    ~DashBoard();

public:
    static DashBoard& getInstance() {
        static DashBoard instance;
        return instance;
    }

public slots:
    void searchModsByName();

private:
    void setupUI();

    void addMods();

    void playGame();

    void checkUpdate();

private:
    QPushButton* play;
    QPushButton* settings;
    QPushButton* update;
    QPushButton* save;
    QPushButton* reset;
    QPushButton* cancel;
    QPushButton* search;
    QPushButton* download;

    QTableWidget *modsTable;
    QTabWidget *tabWidget ;
    QLineEdit* editSearch;
    QList<Mod> loadedMods;
private:
    Logger logger;
};


#endif
