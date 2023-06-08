#include "./include/signup.hpp"
#include "./include/code_submit.hpp"
#include "./include/signin.hpp"

SignUp::SignUp(QWidget *parent) : QDialog(parent) {
    setupUI();
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

  const QString path = QCoreApplication::applicationDirPath() + "/../" + "/MineLaunch/resources/aboutLaunch.html";
  QLabel *labelLink = new QLabel("<a href=\"" + path + "\">About MineLaucnh</a>");
  labelLink->setTextFormat(Qt::RichText);
  labelLink->setOpenExternalLinks(true);
  labelLink->setTextInteractionFlags(Qt::TextBrowserInteraction);
  labelLink->setStyleSheet(
      "color: #0000ff;font-weight:bold; text-decoration: none;");

  labelLogin->setCursor(Qt::PointingHandCursor);
  labelLogin->setWordWrap(false);
  labelLogin->setProperty("openExternalLinks",true);
  labelLogin->setToolTip("Click here to sign in");
  labelTitle->setAlignment(Qt::AlignCenter);

  QHBoxLayout *signinLayout = new QHBoxLayout;
  signinLayout->addStretch();
  signinLayout->addWidget(labelLogin);
  signinLayout->setAlignment(Qt::AlignRight | Qt::AlignBottom);

  QHBoxLayout *browserLayout = new QHBoxLayout;
  browserLayout->addWidget(labelLink);
  browserLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

  QLabel *logo = new QLabel();
  QPixmap logoImage(QCoreApplication::applicationDirPath() + "/../" +
                    "/MineLaunch/resources/u_ajax.png");
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

  QFont titleFont("Roboto", 24, QFont::Bold);
  QFont labelFont("Open Sans", 12);

  labelTitle->setFont(titleFont);
  labelUsername->setFont(labelFont);
  labelEmail->setFont(labelFont);
  labelPassword->setFont(labelFont);

  QToolButton *toolButton = new QToolButton();
  toolButton->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/../" +
                            "/MineLaunch/resources/211661_eye_icon.png"));
  toolButton->setCursor(Qt::PointingHandCursor);

  QObject::connect(toolButton, &QToolButton::clicked, [=]() {
    if (linePassword->echoMode() == QLineEdit::Password) {
      linePassword->setEchoMode(QLineEdit::Normal);
    } else {
      linePassword->setEchoMode(QLineEdit::Password);
    }
  });

  linePassword->setEchoMode(QLineEdit::Password);
  linePassword->setPlaceholderText(tr("Enter password"));
  lineEmail->setPlaceholderText(tr("Enter email"));
  lineUsername->setPlaceholderText(tr("Enter username"));

  lineEmail->setStyleSheet(lineEditStyle);
  linePassword->setStyleSheet(lineEditStyle);
  lineUsername->setStyleSheet(lineEditStyle);

  QIcon icon(QCoreApplication::applicationDirPath() + "/../" +
             "/MineLaunch/resources/u_ajax.png");
  auto [x,y] = CalculateCenterMonitor();

  this->setWindowIcon(icon);
  this->setFixedSize(550, 770);
  this->move(x,y);

  QObject::connect(labelLogin, &QLabel::linkActivated, this,&SignUp::onLabelLinkActivated);

  CodeDialog* dialog = new CodeDialog();
  QObject::connect(buttonSubmit, &QPushButton::clicked, this, [dialog,this]() {
    const QString password = linePassword->text();
    const QString email = lineEmail->text();
    const QString username = lineUsername->text();
    dialog->sendData(username, email, password);
    dialog->show();
  });
}

std::tuple<int, int> SignUp::CalculateCenterMonitor() {
  QPoint center_point =
      QGuiApplication::primaryScreen()->availableGeometry().center();
  int x = center_point.x() - this->width() / 2;
  int y = center_point.y() - this->height() / 2;
  return std::make_tuple(x, y);
}

void SignUp::onLabelLinkActivated(const QString &link)
{
  SignIn::getInstance().show();
  close();
}
