#ifndef SIGNIN_HPP
#define SIGIN_HPP


#include "./signup.hpp"
#include <QGridLayout>

class SignIn : public QDialog{
public:
    SignIn(QWidget* parent = nullptr);

    ~SignIn() noexcept;

private:
    void setupUI();

    void sendBackend(const QString& pass,const QString& email);

public:
    static SignIn& getInstance() {
        static SignIn instance;
        return instance;
    }

public slots:
    void onNetworkManagerFinished(QNetworkReply *reply);

private:
    QLabel* labelPassword;
    QLabel* labelEmail;
    QLabel* labelAccount;
    QLabel* labelTitle;

    QLineEdit* linePassword;
    QLineEdit* lineEmail;

    QPushButton *buttonSubmit;

    QNetworkAccessManager *manager;
    Logger logger;
};

#endif
