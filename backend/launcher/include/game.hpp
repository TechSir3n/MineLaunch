#pragma once

#include "./frontend/include/handler_signals.hpp"
#include "launcher.hpp"
#include "utils/logger.hpp"
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

  void getVersionGame(const QString &t_versionGame);

  void getUsername(const QString &username);

  void getExtensionSettings(const QStringList &extensionArgs);

  void getScreenMode(const QStringList &screenModeArgs);

  void getGamma(const QStringList &gammaArgs);

  void getQuality(const QStringList &qualityArg);

  void getSoundValue(const QString &soundValueArg);

  void getIPAddressAndPort(const QStringList &connectServerArgs);

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
  QString versionGame;
  QString m_assetIndex;
  QString m_soundValue;
  QString m_username = "guest";
  QStringList m_screenModeArgs;
  QStringList m_extensionArgs;
  QStringList m_gammaArgs;
  QStringList m_qualityArgs;
  QStringList m_connectServerArgs;

private:
  static constexpr const char *mainClass = "net.minecraft.client.main.Main";
    Logger logger;
};
