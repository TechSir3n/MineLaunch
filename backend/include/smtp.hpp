#pragma once

#include "../../vendor/SmtpClient/src/SmtpMime"
#include "../../vendor/SmtpClient/src/smtpclient.h"

class Smtp {
public:
  auto sendCodeToEmail(const QString &email, const QString &username) -> int {
    MimeMessage message;

    EmailAddress sender("lalalalalala98912@mail.ru", "MineLaunch Server");
    message.setSender(sender);

    EmailAddress to(email, username);
    message.addRecipient(to);

    int code = generateCode();

    message.setSubject("Submit code");

    MimeText text;

    text.setText("Code for Submit -> " + QString::number(code));

    message.addPart(&text);

    SmtpClient smtp("smtp.mail.ru", 465, SmtpClient::SslConnection);

    smtp.connectToHost();
    if (!smtp.waitForReadyConnected()) {
      qDebug() << "Failed to connect to host!";
      return -1;
    }
    smtp.login("lalalalalala98912@mail.ru", "dmLRsi88nrxKAtii440x");
    if (!smtp.waitForAuthenticated()) {
      qDebug() << "Failed to login!";
      return -2;
    }

    smtp.sendMail(message);
    if (!smtp.waitForMailSent()) {
      qDebug() << "Failed to send mail!";
      return -3;
    }

    smtp.quit();
    return code;
  }


  int generateCode() noexcept{
    srand(time(nullptr));

    int rand_num = 0;
    for(int i = 0;i < COUNT;i++) {
      rand_num  = rand_num *  10 + rand() % 10;
    }

    return rand_num;
  }

private:
  static constexpr int COUNT = 5;
};
