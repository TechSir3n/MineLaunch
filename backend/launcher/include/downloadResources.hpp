#pragma once

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QVector>
#include <QCoreApplication>
#include <QStringList>
#include <QDir>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QByteArray>
#include <QJsonValue>
#include <QFile>

#define HTTP "https://resources.download.minecraft.net"

class DownloadResources : public QObject {
  Q_OBJECT
public:
  DownloadResources(QObject *parent = nullptr);

  ~DownloadResources();

  DownloadResources(const DownloadResources &) = delete;

  DownloadResources &operator=(const DownloadResources &) = delete;

public:
  void downloadResources(const QString &version);

public slots:
  void stopIsDownloadingResources();

signals:
  void errorDownloadResources(const QString &errorStr);

  void progressChanged(int progress);

  void onFinished();

private:
  QNetworkReply *getReply(QNetworkReply *reply = nullptr) noexcept;

private:
  QNetworkAccessManager *m_manager;
  QVector<QString> hashes;
};
