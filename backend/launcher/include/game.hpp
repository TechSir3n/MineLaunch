#pragma once

#include "./frontend/include/handler_signals.hpp"
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

  void setExtensionSettings(const QStringList &extensionArgs);

  void setScreenMode(const QStringList &screenModeArgs);

  void setGamma(const QStringList &gammaArgs);

  void setQuality(const QStringList &qualityArg);

  void setSoundValue(const QString &soundValueArg);

  void setIPAddressAndPort(const QStringList &connectServerArgs);

  void setModsFiels(const QStringList &modsFiles);

  void setdMaxAndMinMemory(const std::tuple<int,int> &memoryUse);

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
  QStringList m_setUseMemory;
  QStringList m_modsFiles;

private:
  static constexpr const char *mainClass = "net.minecraft.client.main.Main";
    Logger logger;
};
