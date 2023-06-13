#pragma once

#include "launcher.hpp"
#include "./frontend/include/handler_signals.hpp"

#include <QObject>
#include <QProcess>

class PlayGame : public Launcher {
  Q_OBJECT
public:
  PlayGame();

  virtual ~PlayGame();

  PlayGame(const PlayGame &) = delete;

  PlayGame &operator=(const PlayGame &) = delete;


public:
  bool gameIsRunning() const;

public slots:
  void start() override;

  void stop() override;

private slots:
  void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);

  void onReadyReadStandardError();

  void onReadyReadStandardOutput();

signals:
  void gameLaunchError(int errorCode);

private:
  QProcess *m_process;
  HandlerSignals *signal;
};
