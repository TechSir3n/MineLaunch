#pragma once

#include "client.hpp"
#include <QMessageBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDialog>

class CodeDialog : public QDialog {
public:
  explicit CodeDialog(QWidget *parent = nullptr)
      : QDialog(parent), client(new Client()) {
    QPushButton *buttonSubmitCode = new QPushButton(tr("Submit"));
    QLabel *labelSubmitCode = new QLabel((tr("Submit Code")));
    QLineEdit *lineSubmitCode = new QLineEdit();

    QHBoxLayout *hbox_layout = new QHBoxLayout;
    hbox_layout->addWidget(buttonSubmitCode);
    hbox_layout->setAlignment(Qt::AlignCenter);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(labelSubmitCode);
    layout->addWidget(lineSubmitCode);
    layout->addLayout(hbox_layout);
    layout->setSpacing(20);

    setWindowTitle(tr("Code Dialog"));

    QObject::connect(buttonSubmitCode, &QPushButton::clicked, this,
                     [this, lineSubmitCode]() {
                       bool ok;
                       int code = lineSubmitCode->text().toInt(&ok);
                       if (ok) {
                         client->sendSubmitCode(code);
                       } else {
                         QMessageBox::critical(this, tr("Error"),
                                               tr("Invalid format code"));
                       }
                     });
  }

  void sendData(const QString &username, const QString &email,
                const QString &password) const {
    assert(client != nullptr);
    client->sendData(username, email, password);
  }

  void sendLoginData(const QString &email, const QString &password) const {
    assert(client != nullptr);
    client->sendUserLoginData(email, password);
  }

  ~CodeDialog() { delete client; }

private:
  Client *client;
};
