#include "./include/downloader.hpp"

Downloader::Downloader()
    : m_version(new DownloadVersion()), m_client(new DownloadClient()),
      m_library(new DownloadLibraries()), handler(new HandlerSignals()),
      m_progress(new QProgressDialog) {}

Downloader::~Downloader() {
  delete m_version;
  delete handler;
  delete m_process;
  delete m_client;
  delete m_library;
  delete m_progress;
}

void Downloader::start() {
  if (versionStr == "1.19.4-rc1") {
    emit downloadError("This version is already installed by default ");

  } else if (versionStr == "23w03a") {
    startProgressDialog();

    m_version->downloadVersion(
        "https://piston-meta.mojang.com/v1/packages/45574762988fd2ad3b9478cabcbe4024cd7321cc/23w03a.json");

    m_client->downloadClient("23w03a");

    m_library->downloadLibraries("23w03a1");

  } else if (versionStr == "1.20-pre7") {
    startProgressDialog();

    m_version->downloadVersion(
        "https://piston-meta.mojang.com/v1/packages/"
        "88efb6148f5b63d3c86135bee3a0f5cb9a36130b/1.20-pre7.json");

    m_client->downloadClient("1.20-pre7");

    m_library->downloadLibraries("1.20-pre7");

    stopProgressDialog();

  } else if (versionStr == "1.20-pre4") {
    startProgressDialog();

    m_version->downloadVersion(
        "https://piston-meta.mojang.com/v1/packages/"
        "c8c93a569f6c46bc5c2785911e3212250fc8933d/1.20-pre4.json");

    m_client->downloadClient("1.20-pre4");

    m_library->downloadLibraries("1.20-pre4");

    stopProgressDialog();

  } else if (versionStr == "1.19.4-pre4") {
    startProgressDialog();
    m_version->downloadVersion(
        "https://piston-meta.mojang.com/v1/packages/"
        "bfc041cde4125e6fb9da3fa1386ee881c663ca22/1.19.4-pre4.json");

    m_client->downloadClient("1.19.4-pre4");
    m_library->downloadLibraries("1.19.4-pre4");

    stopProgressDialog();
  } else if (versionStr == "23w17a") {

    startProgressDialog();
    m_version->downloadVersion(
        "https://piston-meta.mojang.com/v1/packages/"
        "f518509785dee0c0a7013f94f94b1423c732d298/23w17a.json");

    m_client->downloadClient("23w17a");
    m_library->downloadLibraries("23w17a");

    stopProgressDialog();
  }
}

void Downloader::stop() {}

void Downloader::startProgressDialog() {
  m_progress->setLabelText("Downloading...");
  m_progress->setCancelButtonText("Cancel");
  m_progress->setRange(0, 100);
  m_progress->setMinimumDuration(0);
  m_progress->setWindowModality(Qt::WindowModal);
  m_progress->show();

  QObject::connect(m_version, &DownloadVersion::progressChanged, m_progress,
                   &QProgressDialog::setValue);
  QObject::connect(m_client, &DownloadClient::progressChanged, m_progress,
                   &QProgressDialog::setValue);
  QObject::connect(m_library, &DownloadLibraries::progressChanged, m_progress,
                   &QProgressDialog::setValue);
}

void Downloader::stopProgressDialog() { m_progress->close(); }

void Downloader::getVersionGame(const QString &version) {
  versionStr = version;
}
