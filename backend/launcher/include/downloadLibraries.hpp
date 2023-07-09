#pragma once

#include "./check/include/checkLibraries.hpp"
#include "../../../exception/exception.hpp"
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
  DownloadLibraries(QObject *parent = nullptr);

  ~DownloadLibraries();

  DownloadLibraries(const DownloadLibraries &) = delete;

  DownloadLibraries &operator=(const DownloadLibraries &) = delete;

private:
  QNetworkReply *getReply(QNetworkReply *reply = nullptr) noexcept;

public:
  void downloadLibraries(const QString &versionGame) noexcept;

public slots:
  void stopIsDownloadingLibraries();

signals:
  void progressChanged(int progress);

  void errorDownloadLibraries(const QString &errorStr);

  void onFinished();

  void sendVersion(const QString &version);
private:
  QNetworkAccessManager *m_manager;
  QStringList listLibraries;
  QVector<QUrl> urls;
  QVector<QString> m_hashes;
  CheckLibraries *m_libraries;
};
