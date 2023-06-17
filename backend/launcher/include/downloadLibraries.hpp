#pragma once

#include <QByteArray>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QStandardPaths>
#include <QStringList>
#include <QVector>

class DownloadLibraries : public QObject {
    Q_OBJECT
public:
  DownloadLibraries(QObject *object = nullptr);

  ~DownloadLibraries();

  DownloadLibraries(const DownloadLibraries &) = delete;

  DownloadLibraries &operator=(const DownloadLibraries &) = delete;

public:
  void downloadLibraries(const QString &versionGame) noexcept;

signals:
  void progressChanged(int progress);

private:
  QNetworkAccessManager *m_manager;
  QStringList listLibraries;
  QVector<QUrl> urls;
};