#pragma once

#include <QByteArray>
#include <QCoreApplication>
#include <QDir>
#include <QEventLoop>
#include <QFile>
#include <QJsonArray>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
<<<<<<< HEAD
#include <QDir>
#include <QCoreApplication>
=======
>>>>>>> 21eb63f (commit)

class DownloadVersion : public QObject {
  Q_OBJECT
public:
  DownloadVersion(QObject *parent = nullptr);

  virtual ~DownloadVersion();

  DownloadVersion(const DownloadVersion &) = delete;

  DownloadVersion &operator=(const DownloadVersion &) = delete;

public:
<<<<<<< HEAD
    void downloadVersion(const QString &versionGame) noexcept;
=======
  void downloadVersion(const QString &versionGame) noexcept;

  QString getVersionGame() const noexcept;

signals:
  void progressChanged(int progress);
>>>>>>> 21eb63f (commit)

private:
  QNetworkAccessManager *m_manager;
  QString m_versionGame;
};
