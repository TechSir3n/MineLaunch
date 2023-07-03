#include "./include/game.hpp"
#include "./assistance/path.hpp"

PlayGame::PlayGame() : m_process(new QProcess()), signal(new HandlerSignals()) {

  QObject::connect(this, &PlayGame::gameLaunchError, signal,
                   &HandlerSignals::onGameLauncherError);
}

PlayGame::~PlayGame() { delete m_process; }

void PlayGame::start() {

  QStringList arguments;

  const QString classpath =
      QDir::cleanPath(Path::launcherPath() + "/../" +
                      "/MineLaunch/backend/"
                      "launcher/minecraft/libraries/" +
                      versionGame + "/" + "*:" + Path::launcherPath() + "/../" +
                      "/MineLaunch/backend/"
                      "launcher/minecraft/versions/" +
                      versionGame + "/client.jar");

  const QString assetIndex = getAssetIndex();
  const QString assetDir =
      QDir::cleanPath(Path::launcherPath() + "/../" +
                      "/MineLaunch/backend/launcher/minecraft/assets/");

  const QString token =
      "eyJraWQiOiJhYzg0YSIsImFsZyI6IkhTMjU2In0."
      "eyJ4dWlkIjoiMjUzNTQ0Nzc0NTA0NjIxNiIsImFnZyI6IkFkdWx0Iiwic3ViIjoiZGRlMzU0"
      "ZWEtOWI1Zi00MDgzLWFiMDYtNDA4OTI5OWIyOWZmIiwiYXV0aCI6IlhCT1giLCJucyI6ImRl"
      "ZmF1bHQiLCJyb2xlcyI6W10sImlzcyI6ImF1dGhlbnRpY2F0aW9uIiwiZmxhZ3MiOlsidHdv"
      "ZmFjdG9yYXV0aCIsIm1pbmVjcmFmdF9uZXQiLCJvcmRlcnNfMjAyMiJdLCJwbGF0Zm9ybSI6"
      "IlVOS05PV04iLCJ5dWlkIjoiNjAzZWM3N2ViZDc4NWNmMzJjNDUxMGRlMThhMDA0MDQiLCJu"
      "YmYiOjE2ODY1OTM3ODAsImV4cCI6MTY4NjY4MDE4MCwiaWF0IjoxNjg2NTkzNzgwfQ."
      "p5rNp0OsaZHu2MRXmgD5PN-ss5ndr-xXUXGJUe4PZuw";

  arguments << "-cp" << classpath << mainClass << "--accessToken" << token
            << "--assetsDir" << assetDir << "--assetIndex" << assetIndex
            << "--username" << m_username << "--version" << versionGame
            << "--soundVolume" << m_soundValue << m_extensionArgs
            << m_screenModeArgs << m_gammaArgs << m_qualityArgs
            << m_connectServerArgs << m_setUseMemory;

  m_process->startDetached("java", arguments);

  QObject::connect(m_process, &QProcess::finished, this,
                   &PlayGame::onProcessFinished);

  QObject::connect(m_process, &QProcess::readyReadStandardError, this,
                   &PlayGame::onReadyReadStandardError);

  QObject::connect(m_process, &QProcess::readyReadStandardOutput, this,
                   &PlayGame::onReadyReadStandardOutput);

  if (m_process->state() != QProcess::Running) {
    logger.log(LogLevel::Error, "Something went wrong while start process");
  }
}

bool PlayGame::gameIsRunning() const {
  return m_process->state() == QProcess::Running;
}

void PlayGame::stop() {
  if (m_process->state() == QProcess::Running) {
    m_process->kill();
  }
}

void PlayGame::onProcessFinished(int exitCode,
                                 QProcess::ExitStatus exitStatus) {
  if (exitCode != 0 || exitStatus == QProcess::CrashExit) {
    emit gameLaunchError(exitCode);
    qDebug() << "Exit Code : " << exitCode;
    return;
  } else {
    qDebug() << "Success finished -> " << exitCode;
  }
}

void PlayGame::onReadyReadStandardError() {
  QString errorOutput = m_process->readAllStandardError();
  qDebug() << "errorOutput: " << errorOutput;
}

void PlayGame::onReadyReadStandardOutput() {
  QString output = m_process->readAllStandardOutput();
  qDebug() << "Output: " << output;
}

void PlayGame::setUsername(const QString &username) { m_username = username; }

void PlayGame::setExtensionSettings(const QStringList &extensionArgs) {

  m_extensionArgs = extensionArgs;
}

void PlayGame::setScreenMode(const QStringList &screenModeArgs) {
  m_screenModeArgs = screenModeArgs;
}

void PlayGame::setGamma(const QStringList &gammaArgs) {
  m_gammaArgs = gammaArgs;
}

void PlayGame::setSoundValue(const QString &soundValueArg) {
  m_soundValue = soundValueArg;
}

void PlayGame::setIPAddressAndPort(const QStringList &connectServerArgs) {
  m_connectServerArgs = connectServerArgs;
}

void PlayGame::setdMaxAndMinMemory(const std::tuple<int, int> &memoryUse) {
  m_setUseMemory = QStringList() << "-Xmx" << QString::number(std::get<0>(memoryUse)) << "-Xms"
                                 << QString::number(std::get<1>(memoryUse));
}

void PlayGame::setQuality(const QStringList &qualityArg) {
  m_qualityArgs = qualityArg;
}

void PlayGame::setVersionGame(const QString &t_versionGame) {
  versionGame = t_versionGame;
}

QString PlayGame::getAssetIndex() noexcept {
  if (versionGame == "1.19.4-rc1") {
    m_assetIndex = "3";
    return m_assetIndex;
  } else if (versionGame == "23w03a") {
    m_assetIndex = "2";
    return m_assetIndex;
  } else if (versionGame == "1.20-pre7") {
    m_assetIndex = "5";
    return m_assetIndex;
  } else if (versionGame == "1.20-pre4") {
    m_assetIndex = "5";
    return m_assetIndex;
  } else if (versionGame == "1.19.4-pre4") {
    m_assetIndex = "3";
    return m_assetIndex;
  } else if (versionGame == "23w17a") {
    m_assetIndex = "5";
    return m_assetIndex;
  }

  return QString();
}
