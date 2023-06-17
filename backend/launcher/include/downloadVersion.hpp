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
#include <QDir>
#include <QCoreApplication>

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

signals:
  void progressChanged(int progress);

private:
  QNetworkAccessManager *m_manager;
  QString m_versionGame;
};
