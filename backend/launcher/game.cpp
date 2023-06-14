#include "./include/game.hpp"

PlayGame::PlayGame() : m_process(new QProcess()), signal(new HandlerSignals()) {

  QObject::connect(this, &PlayGame::gameLaunchError, signal,
                   &HandlerSignals::onGameLauncherError);

}


PlayGame::~PlayGame() { delete m_process; }

void PlayGame::start() {
  QStringList arguments;

  const QString classpath =
      "/home/ruslan/Documents/MineLaunch/backend/launcher/minecraft/libraries/"
      "*:/home/ruslan/Documents/MineLaunch/backend/launcher/minecraft/versions/1.19.4-rc1/"
      "client.jar";

  const QString token =
      "eyJraWQiOiJhYzg0YSIsImFsZyI6IkhTMjU2In0."
      "eyJ4dWlkIjoiMjUzNTQ0Nzc0NTA0NjIxNiIsImFnZyI6IkFkdWx0Iiwic3ViIjoiZGRlMzU0"
      "ZWEtOWI1Zi00MDgzLWFiMDYtNDA4OTI5OWIyOWZmIiwiYXV0aCI6IlhCT1giLCJucyI6ImRl"
      "ZmF1bHQiLCJyb2xlcyI6W10sImlzcyI6ImF1dGhlbnRpY2F0aW9uIiwiZmxhZ3MiOlsidHdv"
      "ZmFjdG9yYXV0aCIsIm1pbmVjcmFmdF9uZXQiLCJvcmRlcnNfMjAyMiJdLCJwbGF0Zm9ybSI6"
      "IlVOS05PV04iLCJ5dWlkIjoiNjAzZWM3N2ViZDc4NWNmMzJjNDUxMGRlMThhMDA0MDQiLCJu"
      "YmYiOjE2ODY1OTM3ODAsImV4cCI6MTY4NjY4MDE4MCwiaWF0IjoxNjg2NTkzNzgwfQ."
      "p5rNp0OsaZHu2MRXmgD5PN-ss5ndr-xXUXGJUe4PZuw";

  arguments << "-cp" << classpath << "net.minecraft.client.main.Main"
            << "--accessToken" << token << "--username"
            << "Ruslan"
            << "--version"
            << "1.19.4-rc1";

  m_process->startDetached("java", arguments);

  QObject::connect(m_process, &QProcess::finished, this,
                   &PlayGame::onProcessFinished);

  QObject::connect(m_process, &QProcess::readyReadStandardError, this,
                   &PlayGame::onReadyReadStandardError);

  QObject::connect(m_process, &QProcess::readyReadStandardOutput, this,
                   &PlayGame::onReadyReadStandardOutput);

  if (!m_process->waitForFinished()) {
    qDebug() << "Error process: " << m_process->errorString();
  } else {
    qDebug() << "Process started successfully";
  }
}

bool PlayGame::gameIsRunning() const
{
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
