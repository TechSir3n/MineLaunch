#ifndef DASHBOARD_HPP
#define DASHBOARD_HPP

#include "signup.hpp"
#include <QMenu>
#include <QMenuBar>


class DashBoard : public QDialog  {
public:

private:
    QPushButton* play;
    QPushButton* settings;
    QPushButton* update;
    QPushButton* save;
    QPushButton* reset;
    QPushButton* cancel;


};


#endif
