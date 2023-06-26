#include "./include/welcome.hpp"
#include "./assistance/path.hpp"
#include "./include/signin.hpp"

WelcomePage::WelcomePage(QWidget *parent) : QDialog(parent),signup(new SignUp()) {
  setupUI();
}

WelcomePage::~WelcomePage() {
  delete labelPicture;
  delete getStarted;
  delete logIn;
  delete signup;
}

void WelcomePage::setupUI() {
  QPixmap pixmap(QDir::cleanPath(Path::launcherPath() + "/../" +
                                 "MineLaunch/resources/u_ajax.png"));
  if (pixmap.isNull()) {
    logger.log(LogLevel::Error, "Failed to load image");
  }

  labelPicture = new QLabel();
  labelPicture->setPixmap(pixmap);

  getStarted = new QPushButton(tr("Get Started"));
  logIn = new QPushButton(tr("Log In"));

  QLabel *dummy1 = new QLabel();
  dummy1->setMinimumSize(0, 0);
  QLabel *dummy2 = new QLabel();
  dummy2->setMinimumSize(0, 0);

  const QString path = QDir::cleanPath(
      Path::launcherPath() + "/../" + "/MineLaunch/resources/aboutLaunch.html");
  QLabel *link = new QLabel("<a href=\"" + path + "\">About MineLaucnh</a>");
  link->setTextFormat(Qt::RichText);
  link->setTextInteractionFlags(Qt::TextBrowserInteraction);
  link->setOpenExternalLinks(true);
  link->setStyleSheet(
      "color: #0000ff;font-weight:bold; text-decoration: none;");

  QHBoxLayout *layout_link = new QHBoxLayout;
  layout_link->addWidget(link);
  layout_link->setAlignment(Qt::AlignLeft | Qt::AlignTop);

  QHBoxLayout *layout_button = new QHBoxLayout;
  layout_button->addWidget(dummy1);
  layout_button->addWidget(logIn);
  layout_button->addWidget(dummy2);
  layout_button->addWidget(getStarted);
  layout_button->setAlignment(Qt::AlignRight | Qt::AlignTop);

  QVBoxLayout *layout_image = new QVBoxLayout;
  layout_image->addWidget(labelPicture);
  layout_image->setAlignment(Qt::AlignCenter);

  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->addLayout(layout_image);
  layout->addSpacing(10);
  layout->addLayout(layout_button);
  layout->addLayout(layout_link);
  layout->setSpacing(0);
  layout->setContentsMargins(0, 0, 0, 0);

  QIcon icon(QDir::cleanPath(Path::launcherPath() + "/../" +
                             "/MineLaunch/resources/u_ajax.png"));
  this->setFixedSize(550, 380);
  this->setWindowIcon(icon);

  QObject::connect(getStarted, &QPushButton::clicked, this, [&, this]() {
    this->close();
      signup->show();
  });

  QObject::connect(logIn, &QPushButton::clicked, this, [&, this]() {
    this->close();
    SignIn::getInstance().show();
  });
}
