#include "./include/signin.hpp"
#include "./assistance/path.hpp"

SignIn::SignIn(QWidget *parent) : QDialog(parent),dialog(new CodeDialog()) {
      setupUI();
}

SignIn::~SignIn() noexcept {
  delete labelEmail;
  delete labelPassword;
  delete labelAccount;
  delete labelTitle;
  delete linePassword;
  delete lineEmail;
  delete buttonSubmit;
}

void SignIn::setupUI() {
  labelEmail = new QLabel(tr("Email"));
  labelPassword = new QLabel(tr("Password"));
  labelAccount = new QLabel(tr("Haven't account yet?"));
  labelTitle = new QLabel(tr("Login to MineLaucnh"));

  linePassword = new QLineEdit();
  lineEmail = new QLineEdit();

  buttonSubmit = new QPushButton(tr("Sign in"));

  QToolButton *toolButton = new QToolButton();
  toolButton->setIcon(QIcon(Path::launcherPath() + "/../" +
                            "/MineLaunch/resources/211661_eye_icon.png"));
  toolButton->setCursor(Qt::PointingHandCursor);

  QObject::connect(toolButton, &QToolButton::clicked, this, [=]() {
    if (linePassword->echoMode() == QLineEdit::Password) {
      linePassword->setEchoMode(QLineEdit::Normal);
    } else {
      linePassword->setEchoMode(QLineEdit::Password);
    }
  });

  QLabel *logo = new QLabel();
  QPixmap logoImage(Path::launcherPath() + "/../" +
                    "MineLaunch/resources/u_ajax.png");
  logo->setPixmap(logoImage);
  logo->setAlignment(Qt::AlignCenter);
  logo->setFixedSize(230, 130);

  rememberMe = new QCheckBox(tr("Remember Me"));
  QHBoxLayout *checkBoxLayout = new QHBoxLayout;
  checkBoxLayout->addWidget(rememberMe);
  checkBoxLayout->setAlignment(Qt::AlignLeft);

  QHBoxLayout *hbox_layout = new QHBoxLayout;
  hbox_layout->addWidget(buttonSubmit);
  hbox_layout->setAlignment(Qt::AlignHCenter);

  QHBoxLayout *tool_layout = new QHBoxLayout;
  tool_layout->addWidget(toolButton);
  tool_layout->setAlignment(Qt::AlignRight);

  QHBoxLayout *centerLayout = new QHBoxLayout;
  centerLayout->addWidget(logo, 0, Qt::AlignCenter);

  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->insertLayout(0, centerLayout);
  layout->insertWidget(1, labelTitle);
  layout->addWidget(labelEmail);
  layout->addWidget(lineEmail);
  layout->addSpacing(10);
  layout->addWidget(labelPassword);
  layout->addWidget(linePassword);
  layout->addSpacing(10);
  layout->addLayout(tool_layout);
  layout->addLayout(hbox_layout);
  layout->addLayout(checkBoxLayout);
  layout->setContentsMargins(50, 20, 50, 20);
  layout->setSpacing(5);

  QFont titleFont("Roboto", 20, QFont::Bold);
  QFont labelFont("Open Sans", 14);

  labelPassword->setFont(labelFont);
  labelEmail->setFont(labelFont);
  labelTitle->setFont(titleFont);
  labelTitle->setAlignment(Qt::AlignCenter);

  linePassword->setEchoMode(QLineEdit::Password);
  linePassword->setPlaceholderText("Enter password");
  lineEmail->setPlaceholderText("Enter email");

  linePassword->setStyleSheet(lineEditStyle);
  lineEmail->setStyleSheet(lineEditStyle);

  auto [x,y] = signup.CalculateCenterMonitor();
  QIcon icon(Path::launcherPath()+ "/../" +
             "/MineLaunch/resources/u_ajax.png");

  this->setWindowIcon(icon);
  this->setFixedSize(550, 700);
  this->move(x, y);

  QObject::connect(buttonSubmit, &QPushButton::clicked, this, [=]() {
    const QString password = linePassword->text();
    const QString email = lineEmail->text();
    dialog->sendLoginData(email, password);
  });

  QObject::connect(rememberMe, &QCheckBox::stateChanged, this,
                   &SignIn::rememberMeStateChanged);
}

bool SignIn::automaticLogin() const noexcept {
  QString email = settings.value("email").toString();
  QString password = settings.value("password").toString();

  if (!email.isEmpty() && !password.isEmpty()) {
    lineEmail->setText(email);
    linePassword->setText(password);
    rememberMe->setChecked(true);
    dialog->sendLoginData(email, password);
    return true;
  }

  return false;
}

void SignIn::showEvent(QShowEvent *event)
{
  QDialog::showEvent(event);
  if (!automaticLogin()) {
    setupUI();
  }
}

void SignIn::rememberMeStateChanged(int state) {
  if (state == Qt::Checked) {
    settings.setValue("email", lineEmail->text());
    settings.setValue("password", linePassword->text());
  } else {
    settings.remove("email");
    settings.remove("password");
  }
}
