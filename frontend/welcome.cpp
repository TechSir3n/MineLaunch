#include "./include/welcome.hpp"

WelcomePage::WelcomePage(QWidget *parent) : QDialog(parent)
{
    setupUI();
}


WelcomePage::~WelcomePage()
{
    delete labelPicture;
    delete getStarted;
    delete logIn;
}



void WelcomePage::setupUI()
{
    QPixmap pixmap("/home/ruslan/Documents/MineLaunch/resources/x_ajax.png");
    labelPicture = new QLabel();
    labelPicture->setPixmap(pixmap);

    getStarted = new QPushButton(tr("Get Started"));
    logIn = new QPushButton(tr("Log In"));


    QHBoxLayout* layout_button = new QHBoxLayout;
    layout_button->addWidget(getStarted);
    layout_button->setAlignment(Qt::AlignCenter);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(labelPicture);
    layout->addLayout(layout_button);


    this->setFixedSize(400,280);

}

