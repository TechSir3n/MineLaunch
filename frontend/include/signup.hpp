#ifndef SIGNUP_HPP
#define SIGNUP_HPP

#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QDialog>
#include <QIcon>
#include <QScreen>
#include <QApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>
#include <QFont>
#include <QTextBrowser>
#include <QDesktopServices>
#include <QToolButton>
#include <QMessageBox>
#include <QNetworkReply>
#include "./utils/logger.hpp"
#include "./utils/defines.hpp"

class SignUp : public QDialog {
    Q_OBJECT
public:
    SignUp(QWidget* parent = nullptr);

    ~SignUp() noexcept;

public:
    std::tuple<int,int> CalculateCenterMonitor();
private:
    void setupUI();

    void readHTML(QTextBrowser *browser);

public slots:
    void onNetworkManagerFinished(QNetworkReply *reply);

    void sendBackend(const QString &usernm,const QString& pass,const QString& email);

public:
    QLabel* labelUsername;
    QLabel* labelEmail;
    QLabel* labelPassword;
    QLabel* labelLogin;
    QLabel* labelTitle;
    QLabel *labelAboutLaunch;

    QLineEdit* lineUsername;
    QLineEdit* lineEmail;
    QLineEdit* linePassword;

    QPushButton* buttonSubmit;

    QCheckBox* rememberMe;

    QNetworkAccessManager *manager;
private:
    Logger logger;
};

#endif
