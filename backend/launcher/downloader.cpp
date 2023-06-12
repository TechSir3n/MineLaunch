#include "./include/downloader.hpp"

Downloader::Downloader()
    : handler(new HandlerSignals()), m_process(new QProcess()),
      m_lcdNumber(new QLCDNumber()) {

}

void Downloader::start() {

}

void Downloader::stop() {
  m_process->kill();
  IsStopped = true;
  emit downloadStopped();
}

