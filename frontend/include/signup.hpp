#pragma once

#include "./utils/defines.hpp"
#include "./utils/logger.hpp"
#include "dashboard.hpp"
#include <QApplication>
#include <QCheckBox>
#include <QCoreApplication>
#include <QDesktopServices>
#include <QDialog>
#include <QDir>
#include <QFont>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPushButton>
#include <QScreen>
#include <QtCore>
#include <QTextBrowser>
#include <QToolButton>
#include <QUrl>
#include <QUrlQuery>
#include <QVBoxLayout>

class SignUp : public QDialog {
  Q_OBJECT
private:
 explicit SignUp(QWidget *parent = nullptr);

  ~SignUp() noexcept;

  SignUp(const SignUp&) = delete;

  SignUp& operator=(const SignUp&) = delete;

public:
  std::tuple<int, int> CalculateCenterMonitor();

  static SignUp &getInstance() {
    static SignUp instance;
    return instance;
  }

private:
  void setupUI();

public slots:
  void onNetworkManagerFinished(QNetworkReply *reply);

  void sendBackend(const QString &usernm, const QString &pass,
                   const QString &email);

public:
  QLabel *labelUsername;
  QLabel *labelEmail;
  QLabel *labelPassword;
  QLabel *labelLogin;
  QLabel *labelTitle;
  QLabel *labelAboutLaunch;

  QLineEdit *lineUsername;
  QLineEdit *lineEmail;
  QLineEdit *linePassword;

  QPushButton *buttonSubmit;
  QCheckBox *rememberMe;

  QNetworkAccessManager *manager;
  Logger logger;
};
