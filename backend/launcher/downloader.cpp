#include "./include/downloader.hpp"

Downloader::Downloader()
    : handler(new HandlerSignals()), m_process(new QProcess()),
      m_lcdNumber(new QLCDNumber()) {

}

Downloader::~Downloader()
{

}

void Downloader::start() {

}

void Downloader::stop() {

}

