#pragma once

#include "./backend/include/updater_data.hpp"
#include "./utils/hashing.hpp"
#include <QDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QStyle>
#include <QStringList>
#include <QGuiApplication>
#include <QApplication>
#include <QInputDialog>
#include <QScreen>
#include <QObject>

class UserSettings : public QDialog {
    Q_OBJECT
private:
  explicit UserSettings(QWidget *parent = nullptr);

  ~UserSettings() = default;

  UserSettings(const UserSettings &) = delete;

  UserSettings &operator=(const UserSettings &) = delete;

public:
  static UserSettings &getInstance() {
    static UserSettings instance;
    return instance;
  }

public slots:
  void getProfileData(const QString &name, const QString &email,
                      const QString &password);
signals:
  void sendUsername(const QString &username);

  void sendNewUsername(const QString &newName,const QString &email);

  void sendNewPassword(const QString &newPassword,const QString &email);

public:
  void initalizeGuiSettings(QTabWidget *m_tab) noexcept;

private:
  QLabel *nameLabel;
  QLabel *emailLabel;
  QLabel *passwordLabel;

  QLabel* nameValueLabel;
  QLabel* emailValueLabel;
  QLabel* passwordValueLabel;

  QPushButton *exitButton;
  QPushButton *editPasswordButton;
  QPushButton *editUsernameButton;

  UserDataUpdater m_update;
  Hash hash;
};
