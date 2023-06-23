#pragma once

#include <QByteArray>
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

class DownloadAssetIndex : public QObject {
  Q_OBJECT
public:
  DownloadAssetIndex(QObject *parent = nullptr);

  ~DownloadAssetIndex();

  DownloadAssetIndex(const DownloadAssetIndex &) = delete;

  DownloadAssetIndex &operator=(const DownloadAssetIndex &) = delete;

public:
  void downloadAssetIndex(const QString &versionGame);

public slots:
  void stopIsDownloadingAssetIndex();

signals:
  void errorDownloadAssetIndex(const QString &errorStr);

  void progressChanged(int progress);

  void onFinished();

private:
  QNetworkReply *getReply(QNetworkReply *reply = nullptr) noexcept;

private:
  QNetworkAccessManager *m_manager;
  QString m_assetIndex;
};
