#pragma once

#include "../../../frontend/include/handler_signals.hpp"
#include "downloadClient.hpp"
#include "downloadLibraries.hpp"
#include "downloadVersion.hpp"
#include "launcher.hpp"
#include <QLCDNumber>
#include <QProcess>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QSysInfo>
#include <QObject>
#include <QThread>
#include <QProgressDialog>

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

  void stop() override;

  void startProgressDialog();

  void stopProgressDialog();

public slots:
  void getVersionGame(const QString &version);

public:
  bool IsDownloading() const noexcept;

private:
  QProcess *m_process;
  HandlerSignals *handler;
  QString versionStr;
  QString m_IsDownloading = "stop";
  QProgressDialog *m_progress;
  bool IsStopped;

private:
  DownloadVersion *m_version;
  DownloadLibraries *m_library;
  DownloadClient *m_client;
};
