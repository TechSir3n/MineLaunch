#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QCoreApplication>
#include <QFile>
#include <QDir>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>

class DownloadAssetIndex : public QObject {
    Q_OBJECT
public:
 DownloadAssetIndex(QObject *parent = nullptr);

  ~DownloadAssetIndex();

  DownloadAssetIndex(const DownloadAssetIndex &) = delete;

  DownloadAssetIndex&operator=(const DownloadAssetIndex &) = delete;

public:
  void downloadAssetIndex(const QString &versionGame);

public slots:
  void stopIsDownloadingAssetIndex();

signals:
  void errorDownloadAssetIndex(const QString &errorStr);

  void progressChanged(int progress);

  void onFinished();

private:
  QString &getAssetIndex() const noexcept;

  QNetworkReply *getReply(QNetworkReply *reply = nullptr) noexcept;


private:
    QNetworkAccessManager *m_manager;
};
