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

public slots:
  void start() override;

  void stop() override;

public slots:
  void getVersionGame(const QString &version);

private:
  QProcess *m_process;
  HandlerSignals *handler;
  QLCDNumber *m_lcdNumber;
  QString m_version;
  bool IsStopped;

private:
  DownloadVersion *version;
  DownloadLibraries *libraries;
};
