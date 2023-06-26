#include "./include/user_settings.hpp"
#include "./include/dashboard.hpp"
#include "./include/welcome.hpp"

QStringList m_data;

UserSettings::UserSettings(QWidget *parent) : QDialog(parent) {
  PlayGame *game = new PlayGame();
  QObject::connect(this, &UserSettings::sendUsername, game,
                   &PlayGame::getUsername);
}

void UserSettings::getProfileData(const QString &name, const QString &email,
                                  const QString &password) {
  m_data = {name, email, password};
}

void UserSettings::initalizeGuiSettings(QTabWidget *m_tab) noexcept {
  QWidget *profileWidget = new QWidget();
  m_tab->addTab(profileWidget, "User Account");
  profileWidget->setFixedSize(980, 590);

  QFrame *frameUsername = new QFrame();
  frameUsername->setFrameShape(QFrame::Box);
  frameUsername->setFrameShadow(QFrame::Sunken);
  frameUsername->setLineWidth(1);
  frameUsername->setFixedSize(175, 70);

  QFrame *frameEmail = new QFrame();
  frameEmail->setFrameShape(QFrame::Box);
  frameEmail->setFrameShadow(QFrame::Sunken);
  frameEmail->setFixedSize(175, 70);

  QFrame *framePassword = new QFrame();
  framePassword->setFrameShape(QFrame::Box);
  framePassword->setFrameShadow(QFrame::Sunken);
  framePassword->setFixedSize(175, 70);

  nameLabel = new QLabel(tr("Username"));
  emailLabel = new QLabel(tr("Email"));
  passwordLabel = new QLabel(tr("Password"));

  nameValueLabel = new QLabel(tr("") + "" + m_data[0]);
  emailValueLabel = new QLabel(tr("") + "" + m_data[1]);
  passwordValueLabel = new QLabel(tr("") + "" + m_data[2]);

  emit sendUsername(nameValueLabel->text());

  nameLabel->setStyleSheet("font-size: 20px;");
  emailLabel->setStyleSheet("font-size: 20px;");
  passwordLabel->setStyleSheet("font-size: 20px;");

  exitButton = new QPushButton(tr("Logout"));
  editPasswordButton = new QPushButton(tr("Change password"));
  editUsernameButton = new QPushButton(tr("Edit Name"));

  QHBoxLayout *buttonLayout = new QHBoxLayout;
  buttonLayout->addWidget(exitButton);
  buttonLayout->addSpacerItem(
      new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
  buttonLayout->addWidget(editPasswordButton);
  buttonLayout->addWidget(editUsernameButton);

  QGridLayout *nameLayout = new QGridLayout();
  nameLayout->addWidget(nameLabel, 0, 0);
  nameLayout->addWidget(nameValueLabel, 1, 0);
  frameUsername->setLayout(nameLayout);

  QGridLayout *emailLayout = new QGridLayout();
  emailLayout->addWidget(emailLabel, 2, 0);
  emailLayout->addWidget(emailValueLabel, 3, 0);
  frameEmail->setLayout(emailLayout);

  QGridLayout *passwordLayout = new QGridLayout();
  passwordLayout->addWidget(passwordLabel, 4, 0);
  passwordLayout->addWidget(passwordValueLabel, 5, 0);
  framePassword->setLayout(passwordLayout);

  QVBoxLayout *profileLayout = new QVBoxLayout();
  profileLayout->addWidget(frameUsername);
  profileLayout->addWidget(frameEmail);
  profileLayout->addWidget(framePassword);
  profileLayout->addLayout(buttonLayout);

  const QString style =
      "QGroupBox { font-weight: bold; font-size: 19px; border: 1px solid "
      "black; border-radius: 5px; margin-top: 10px; margin-bottom: 10px; "
      "padding: 10px; } QGroupBox:title { subcontrol-origin: margin; "
      "subcontrol-position: top center; padding: 0 3px;}";

  QGroupBox *userInfoGroupBox = new QGroupBox(tr("User Information"));
  userInfoGroupBox->setLayout(profileLayout);
  userInfoGroupBox->setStyleSheet(style);

  QHBoxLayout *hLayout = new QHBoxLayout();
  hLayout->addSpacerItem(
      new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
  hLayout->addWidget(userInfoGroupBox);
  hLayout->addSpacerItem(
      new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

  QVBoxLayout *layout = new QVBoxLayout(profileWidget);
  int vSpacing = (profileWidget->height() - userInfoGroupBox->height()) / 2;
  layout->addSpacerItem(new QSpacerItem(0, vSpacing, QSizePolicy::Minimum,
                                        QSizePolicy::Expanding));
  layout->addLayout(hLayout);
  layout->addSpacerItem(new QSpacerItem(0, vSpacing, QSizePolicy::Minimum,
                                        QSizePolicy::Expanding));

  profileWidget->setGeometry(QStyle::alignedRect(
      Qt::LeftToRight, Qt::AlignCenter, profileWidget->size(),
      QGuiApplication::primaryScreen()->availableGeometry()));

  std::shared_ptr<WelcomePage> welcPtr = std::make_shared<WelcomePage>();
  QObject::connect(exitButton, &QPushButton::clicked, this, [welcPtr]() {
    DashBoard::getInstance().close();
    welcPtr->show();
  });

  QObject::connect(editPasswordButton, &QPushButton::clicked, this, [this]() {
    QString newPassword =
        QInputDialog::getText(this, "Input Dialog", "Enter new password");
    emit sendNewPassword(hash.toHash(newPassword), (m_data[1]));
    passwordValueLabel->setText(newPassword);
  });

  QObject::connect(editUsernameButton, &QPushButton::clicked, this, [this]() {
    QString newName =
        QInputDialog::getText(this, "Input Dialog", "Enter new name");
    emit sendNewUsername(newName, m_data[1]);
    nameValueLabel->setText(newName);
  });
}
