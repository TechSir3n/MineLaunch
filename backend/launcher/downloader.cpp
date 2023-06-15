#include "./include/downloader.hpp"

Downloader::Downloader()
    : handler(new HandlerSignals()), m_process(new QProcess()),
      m_lcdNumber(new QLCDNumber()), version(new DownloadVersion()),
      libraries(new DownloadLibraries()) {}

Downloader::~Downloader() {
  delete version;
  delete m_lcdNumber;
  delete handler;
  delete m_process;
}

void Downloader::start() {
  if (m_version == "1.19.4-rc1") {
      emit downloadError("This version is already installed by default ");

  } else if (m_version == "23w03a") {
    version->downloadVersion(
        "https://piston-meta.mojang.com/v1/packages/"
        "45574762988fd2ad3b9478cabcbe4024cd7321cc/23w03a.json");

      libraries->downloadLibraries(m_version);
  } else if (m_version == "1.20-pre7") {
    version->downloadVersion(
        "https://piston-meta.mojang.com/v1/packages/"
        "88efb6148f5b63d3c86135bee3a0f5cb9a36130b/1.20-pre7.json");

  } else if (m_version == "1.20-pre4") {
    version->downloadVersion(
        "https://piston-meta.mojang.com/v1/packages/"
        "c8c93a569f6c46bc5c2785911e3212250fc8933d/1.20-pre4.json");

  } else if (m_version == "1.19.4-pre4") {
    version->downloadVersion(
        "https://piston-meta.mojang.com/v1/packages/"
        "bfc041cde4125e6fb9da3fa1386ee881c663ca22/1.19.4-pre4.json");

  } else if (m_version == "23w17a") {
    version->downloadVersion(
        "https://piston-meta.mojang.com/v1/packages/"
        "f518509785dee0c0a7013f94f94b1423c732d298/23w17a.json");
  }
}

void Downloader::stop() {}

void Downloader::getVersionGame(const QString &version) { m_version = version; }
