#pragma once

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QProcess>

class DownloadClient : public QObject {
  Q_OBJECT

public:
  DownloadClient(QObject *parent = nullptr);

  ~DownloadClient();

  DownloadClient(const DownloadClient &) = delete;

  DownloadClient &operator=(const DownloadClient &) = delete;

public:
  void downloadClient(const QString &versionClient);

private:
  QNetworkReply *getReply(QNetworkReply *reply = nullptr) noexcept;

public slots:
  void stopIsDownloadingClient();

signals:
  void errorDownloadClient(const QString &errorStr);

  void progressChanged(int progress);

  void onFinished();

private:
  void onStandardOutput();

  void onStandardErrorOutput();

private:
  QNetworkAccessManager *m_manager;
  QProcess *m_process;
};
