#ifndef WELCOME_HPP
#define WELCOME_HPP

#include "signin.hpp"
#include "signup.hpp"

class WelcomePage : public QDialog {
public:
  WelcomePage(QWidget *parent = nullptr);

  ~WelcomePage();

public:
  void setupUI();

private:
  QLabel *labelPicture;

  QPushButton *getStarted; // for registration
  QPushButton *logIn;

  Logger logger;
};

#endif
