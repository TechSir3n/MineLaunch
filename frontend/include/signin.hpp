#pragma once

#include "./signup.hpp"
#include <QGridLayout>
#include <QtCore>

class SignIn : public QDialog {
    Q_OBJECT
private:
 explicit SignIn(QWidget *parent = nullptr);

  ~SignIn() noexcept;

  SignIn(const SignIn&) = delete;

  SignIn& operator=(const SignIn&) = delete;

private:
  void setupUI();

  void sendBackend(const QString &pass, const QString &email);

public:
  static SignIn &getInstance() {
    static SignIn instance;
    return instance;
  }

private slots:
  void onNetworkManagerFinished(QNetworkReply *reply);

private:
  QLabel *labelPassword;
  QLabel *labelEmail;
  QLabel *labelAccount;
  QLabel *labelTitle;

  QLineEdit *linePassword;
  QLineEdit *lineEmail;

  QPushButton *buttonSubmit;

  QNetworkAccessManager *manager;
  Logger logger;
};


