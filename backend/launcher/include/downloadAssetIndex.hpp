#pragma once

#include "./check/include/checkAssetIndex.hpp"
#include "../../../exception/exception.hpp"
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

  void sendVersion(const QString &version);

private:
  QNetworkReply *getReply(QNetworkReply *reply = nullptr) noexcept;

private:
  QNetworkAccessManager *m_manager;
  CheckAssetIndex *m_index;
  QString m_assetIndex;
};
