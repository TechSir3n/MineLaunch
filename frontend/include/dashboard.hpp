#ifndef DASHBOARD_HPP
#define DASHBOARD_HPP

#include "signup.hpp"
#include <QMenu>
#include <QMenuBar>
#include <QListWidget>
#include <QTabWidget>
#include <QStringList>
#include <QAction>

class DashBoard : public QDialog  {
public:
    DashBoard(QWidget* parent = nullptr);

    ~DashBoard();

public:
    void setupUI();

    QStringList fileList();

private:
    QPushButton* play;
    QPushButton* settings;
    QPushButton* update;
    QPushButton* save;
    QPushButton* reset;
    QPushButton* cancel;

};


#endif
