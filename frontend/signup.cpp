#include "./include/signup.hpp"
#include "./include/signin.hpp"
#include "./include/code_submit.hpp"

SignUp::SignUp(QWidget *parent) : QDialog(parent) {
    setupUI();
    manager = new QNetworkAccessManager(this);
    QObject::connect(manager, SIGNAL(finished(QNetworkReply *)), this,
                     SLOT(onNetworkManagerFinished(QNetworkReply *)));
}

SignUp::~SignUp() noexcept {
  delete labelUsername;
  delete labelEmail;
  delete labelPassword;
  delete labelLogin;
  delete lineEmail;
  delete linePassword;
  delete lineUsername;
  delete buttonSubmit;
  delete rememberMe;
}

void SignUp::setupUI() {
  labelUsername = new QLabel(tr("Username"));
  labelEmail = new QLabel(tr("Email"));
  labelPassword = new QLabel(tr("Password"));
  labelLogin = new QLabel(tr("Sign in"));
  labelTitle = new QLabel(tr("Registration Form"));
  labelAboutLaunch = new QLabel(tr("About MineLaunch"));

  lineEmail = new QLineEdit();
  linePassword = new QLineEdit();
  lineUsername = new QLineEdit();

  buttonSubmit = new QPushButton(tr("Create Account"));
  rememberMe = new QCheckBox(tr("Remember Me"));

  QHBoxLayout *checkboxLayout = new QHBoxLayout;
  checkboxLayout->addWidget(rememberMe);
  checkboxLayout->addStretch();
  checkboxLayout->addWidget(buttonSubmit);

  QTextBrowser *textBrowser = new QTextBrowser();
  readHTML(textBrowser);

  QHBoxLayout *signinLayout = new QHBoxLayout;
  signinLayout->addStretch();
  signinLayout->addWidget(labelLogin);
  signinLayout->setAlignment(Qt::AlignRight);

  QHBoxLayout *browserLayout = new QHBoxLayout;
  browserLayout->addWidget(textBrowser);
  browserLayout->setAlignment(Qt::AlignLeft);

  QLabel *logo = new QLabel();
  QPixmap logoImage("/home/ruslan/Documents/MineLaunch/resources/u_ajax.png");
  logo->setPixmap(logoImage);
  logo->setAlignment(Qt::AlignCenter);
  logo->setFixedSize(230, 130);

  QHBoxLayout *centerLayout = new QHBoxLayout;
  centerLayout->addWidget(logo, 0, Qt::AlignCenter);
  centerLayout->setSpacing(20);

  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->insertLayout(0, centerLayout);
  layout->insertWidget(1, labelTitle);
  layout->addWidget(labelUsername);
  layout->addWidget(lineUsername);
  layout->addWidget(labelEmail);
  layout->addWidget(lineEmail);
  layout->addWidget(labelPassword);
  layout->addWidget(linePassword);
  layout->addLayout(checkboxLayout);
  layout->addLayout(signinLayout);
  layout->addLayout(browserLayout);
  layout->setContentsMargins(QMargins(10, 10, 10, 10));
  layout->setSpacing(20);

  labelLogin->setCursor(Qt::PointingHandCursor);
  labelLogin->setStyleSheet(
      "color: blue; font-size: 14px; font-family: Arial;");
  labelTitle->setAlignment(Qt::AlignCenter);

  QFont titleFont("Roboto", 24, QFont::Bold);
  QFont labelFont("Open Sans", 12);

  labelTitle->setFont(titleFont);
  labelUsername->setFont(labelFont);
  labelEmail->setFont(labelFont);
  labelPassword->setFont(labelFont);

  QToolButton* toolButton = new QToolButton();
  toolButton->setIcon(QIcon("/home/ruslan/Documents/MineLaunch/resources/211661_eye_icon.png"));
  toolButton->setCursor(Qt::PointingHandCursor);

  QObject::connect(toolButton, &QToolButton::clicked, [=]() {
      if (linePassword->echoMode() == QLineEdit::Password) {
          linePassword->setEchoMode(QLineEdit::Normal);
      } else {
          linePassword->setEchoMode(QLineEdit::Password);
      }
  });

  linePassword->setEchoMode(QLineEdit::Password);
  linePassword->setPlaceholderText("Enter password");
  lineEmail->setPlaceholderText("Enter email");
  lineUsername->setPlaceholderText("Enter username");

  lineEmail->setStyleSheet(lineEditStyle);
  linePassword->setStyleSheet(lineEditStyle);
  lineUsername->setStyleSheet(lineEditStyle);

  QIcon icon("/home/ruslan/Documents/MineLaunch/resources/u_ajax.png");
  auto result = CalculateCenterMonitor();

  this->setWindowIcon(icon);
  this->setFixedSize(550, 770);
  this->move(std::get<0>(result), std::get<1>(result));


  QObject::connect(labelLogin, &QLabel::linkActivated, [this]() {
       SignIn* sign = new SignIn(this);
      sign->show();
  });

  QObject::connect(buttonSubmit, &QPushButton::clicked, [this]() {

      CodeDialog* codeDialog = new CodeDialog(this);
      codeDialog->show();
  });
}

void SignUp::sendBackend(const QString &usernm, const QString &pass,
                         const QString &email) {

  QUrl url("http://localhost:8080/signup");

  QNetworkRequest request(url);
  request.setHeader(QNetworkRequest::ContentTypeHeader,
                    "application/x-www-form-urlencoded");

  QUrlQuery postData;
  postData.addQueryItem("username", usernm);
  postData.addQueryItem("password", pass);
  postData.addQueryItem("email", email);

  manager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());
}

void SignUp::onNetworkManagerFinished(QNetworkReply *reply) {
  int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
  switch (statusCode) {
  case 200:
    logger.log(LogLevel::Info, "Registration completed successfuly");
    break;
  case 400:
    logger.log(LogLevel::Error,"Registration error: ");
    QMessageBox::warning(this, "Error", "Error registration,status code: " + QString::number(statusCode));
    break;

  default:
    logger.log(LogLevel::Error, "Unknown registration error,status code: " + std::to_string(statusCode));
    break;
  }
  reply->deleteLater();
}

void SignUp::readHTML(QTextBrowser *browser) {
  QString path = "/home/ruslan/Documents/MineLaunch/utils/aboutLaunch.html";
  QUrl url = QUrl::fromLocalFile(path);
  QString href = url.toEncoded();

  browser->insertHtml("<a href = \"" + href + "\">About MineLaunch</a>");
  browser->setStyleSheet(linkStyle);
  browser->setFrameStyle(QFrame::NoFrame);

  QObject::connect(browser, &QTextBrowser::anchorClicked,
                   [=](const QUrl &link) {
                     if (link.isLocalFile()) {
                       QString path = link.toLocalFile();
                       QDesktopServices::openUrl(QUrl::fromLocalFile(path));
                       browser->setSource(QUrl());
                     }
  });
}


std::tuple<int, int> SignUp::CalculateCenterMonitor() {
  QPoint center_point =
      QGuiApplication::primaryScreen()->availableGeometry().center();
  int x = center_point.x() - this->width() / 2;
  int y = center_point.y() - this->height() / 2;
  return std::make_tuple(x, y);
}
