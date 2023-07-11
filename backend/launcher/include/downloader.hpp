#pragma once

#include "concurrency.hpp"
#include "launcher.hpp"
#include <QLCDNumber>
#include <QObject>
#include <QProcess>
#include <QProgressDialog>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QSysInfo>
#include <QThreadPool>
#include <mutex>

class Downloader : public Launcher {
  Q_OBJECT
public:
  Downloader();

  virtual ~Downloader();

  Downloader(const Downloader &) = delete;

  Downloader &operator=(const Downloader &) = delete;

signals:
  void downloadError(const QString &descriptonError);

  void downloadFinished();

  void downloadStopped();

  void stopDownloading();

public slots:
  void start() override;

  void stop() override {}

public slots:
  void setVersionGame(const QString &version);

public:
  bool IsDownloading() const noexcept;

private:
  QString versionStr;
  QString m_IsDownloading = "stop";
  QThreadPool *m_pool;
  std::mutex m_mutex;
  std::condition_variable m_cv;
  bool IsReady = false;

private:
  DownloadAssetIndexTask *m_assetIndexTask;
  DownloadClientTask *m_clientTask;
  DownloadLibrariesTask *m_libraryTask;
  DownloadVersionTask *m_versionTask;
  DownloadResourcesTask *m_resourceTask;
};
