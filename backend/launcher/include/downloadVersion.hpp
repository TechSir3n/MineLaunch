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

class DownloadVersion : public QObject {
  Q_OBJECT
public:
  DownloadVersion(QObject *parent = nullptr);

  virtual ~DownloadVersion();

  DownloadVersion(const DownloadVersion &) = delete;

  DownloadVersion &operator=(const DownloadVersion &) = delete;

public:
  void downloadVersion(const QString &versionGame) noexcept;

  QString getVersionGame() const noexcept;

private:
  QNetworkReply *getReply(QNetworkReply *reply = nullptr) noexcept;

public slots:
  void stopIsDownloadingVersion();

signals:
  void progressChanged(int progress);

  void errorDownloadVersion();

  void onFinished();

private:
  QNetworkAccessManager *m_manager;
  QString m_versionGame;
};
