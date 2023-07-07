#pragma once

#include "./frontend/include/handler_signals.hpp"
#include "./assistance/custom.hpp"
#include "launcher.hpp"
#include "assistance/logger.hpp"
#include <QDir>
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

  void setVersionGame(const QString &t_versionGame);

  void setUsername(const QString &username);

  void setIPAddressAndPort(const QStringList &connectServerArgs);

  void setModsFiels(const QStringList &modsFiles);

private:
  QString getAssetIndex() noexcept;

private slots:
  void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);

  void onReadyReadStandardError();

  void onReadyReadStandardOutput();

signals:
  void gameLaunchError(int errorCode);

private:
  QProcess *m_process;
  HandlerSignals *signal;
  Custom *m_custom;

  QString m_versionGame;
  QString m_assetIndex;
  QString m_username = "guest";

private:
  QStringList m_connectServerArgs;
  QStringList m_setUseMemory;
  QStringList m_modsFiles;
  QStringList m_language;

private:
  static constexpr const char *mainClass = "net.minecraft.client.main.Main";
    Logger logger;
};
