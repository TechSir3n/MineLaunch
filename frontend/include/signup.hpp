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
#include <QTextBrowser>
#include <QToolButton>
#include <QUrl>
#include <QUrlQuery>
#include <QVBoxLayout>
#include <QtCore>

class SignUp : public QDialog {
  Q_OBJECT
public:
  explicit SignUp(QWidget *parent = nullptr);

  ~SignUp() noexcept;

  SignUp(const SignUp &) = delete;

  SignUp &operator=(const SignUp &) = delete;

public:
  static SignUp & getInstance() {
      static SignUp instance;
      return instance;
  }

public:
  std::tuple<int, int> CalculateCenterMonitor();

private slots:
  void onLabelLinkActivated(const QString& link);

private:
  void setupUI();

private:
  QLabel *labelUsername;
  QLabel *labelEmail;
  QLabel *labelPassword;
  QLabel *labelLogin;
  QLabel *labelTitle;
  QLabel *labelAboutLaunch;

  QPushButton *buttonSubmit;
  QCheckBox *rememberMe;

  Logger logger;

  QLineEdit *lineUsername;
  QLineEdit *lineEmail;
  QLineEdit *linePassword;
};
