#pragma once

#include "code_submit.hpp"
#include "signup.hpp"
#include <QGridLayout>
#include <QtCore>
#include <QSettings>

class SignIn : public QDialog {
  Q_OBJECT
private:
  explicit SignIn(QWidget *parent = nullptr);

  ~SignIn() noexcept;

  SignIn(const SignIn &) = delete;

  SignIn &operator=(const SignIn &) = delete;

private:
  void setupUI();

  bool automaticLogin() const noexcept;

  void showEvent(QShowEvent *event);
public:
  static SignIn &getInstance() {
    static SignIn instance;
    return instance;
  }

private slots:
  void rememberMeStateChanged(int state);

private:
  QLabel *labelPassword;
  QLabel *labelEmail;
  QLabel *labelAccount;
  QLabel *labelTitle;

  QCheckBox *rememberMe;
  QPushButton *buttonSubmit;

  QSettings settings;
  Logger logger;
  SignUp signup;

public:
  QLineEdit *linePassword;
  QLineEdit *lineEmail;
};
