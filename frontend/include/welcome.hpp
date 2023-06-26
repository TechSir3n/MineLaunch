#pragma once

#include "signup.hpp"
#include <QtCore>

class WelcomePage : public QDialog {
    Q_OBJECT
public:
  explicit WelcomePage(QWidget *parent = nullptr);

  ~WelcomePage();

public:
  void setupUI();

private:
  QLabel *labelPicture;

  QPushButton *getStarted; // for registration
  QPushButton *logIn;

  Logger logger;
  SignUp *signup;

  bool IsExitSignIn = false;
  bool IsExitSignUp = false;
};

