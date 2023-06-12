#pragma once

#include "launcher.hpp"
#include "../../../frontend/include/handler_signals.hpp"
#include <QSysInfo>
#include <QLCDNumber>
#include <QProcess>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include <QObject>

class Downloader :public Launcher {
    Q_OBJECT
public:
   Downloader();

  ~Downloader() = default;

  Downloader(const Downloader &) = delete;

  Downloader &operator=(const Downloader &) = delete;

signals:
  void downloadError();

  void downloadFinished();

  void downloadStopped();

private slots:
  void start() override;

  void stop() override;

private:
  QProcess *m_process;
  HandlerSignals *handler;
  QLCDNumber *m_lcdNumber;
  bool IsStopped;

};
