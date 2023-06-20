#include "./include/downloader.hpp"

Downloader::Downloader()
    : m_version(new DownloadVersion()), m_client(new DownloadClient()),
      m_library(new DownloadLibraries()), handler(new HandlerSignals()),
      m_progress(new QProgressDialog), m_index(new DownloadAssetIndex()),
      m_resources(new DownloadResources()) {
  m_IsDownloading = "downloading";

  QObject::connect(m_version, &DownloadVersion::errorDownloadVersion, handler,
                   &HandlerSignals::onDownloadVersionError);

  QObject::connect(m_library, &DownloadLibraries::errorDownloadLibraries,
                   handler, &HandlerSignals::onDownloadLibrariesError);

  QObject::connect(m_client, &DownloadClient::errorDownloadClient, handler,
                   &HandlerSignals::onDownloadClientError);

  QObject::connect(m_index, &DownloadAssetIndex::errorDownloadAssetIndex,
                   handler, &HandlerSignals::onDownloadAssetIndexError);

  QObject::connect(m_resources, &DownloadResources::errorDownloadResources,
                   handler, &HandlerSignals::onDownloadAssetResoucresError);

  m_progress->close();
}

Downloader::~Downloader() {
  delete m_version;
  delete handler;
  delete m_process;
  delete m_client;
  delete m_library;
  delete m_resources;
  delete m_progress;
  delete m_index;
}

void Downloader::start() {
  if (versionStr == "1.19.4-rc1") {
    emit downloadError("This version is already installed by default ");

  } else if (versionStr == "23w03a") {
    startProgressDialog();

    m_version->downloadVersion(
        "https://piston-meta.mojang.com/v1/packages/"
        "45574762988fd2ad3b9478cabcbe4024cd7321cc/23w03a.json");

    m_client->downloadClient("23w03a");

    m_library->downloadLibraries("23w03a1");

    m_index->downloadAssetIndex("23w03a1");

    stopProgressDialog();
  } else if (versionStr == "1.20-pre7") {
    startProgressDialog();

    m_version->downloadVersion(
        "https://piston-meta.mojang.com/v1/packages/"
        "88efb6148f5b63d3c86135bee3a0f5cb9a36130b/1.20-pre7.json");

    m_client->downloadClient("1.20-pre7");

    m_library->downloadLibraries("1.20-pre7");
    m_index->downloadAssetIndex("1.20-pre7");

    stopProgressDialog();

  } else if (versionStr == "1.20-pre4") {
    startProgressDialog();

    m_version->downloadVersion(
        "https://piston-meta.mojang.com/v1/packages/"
        "c8c93a569f6c46bc5c2785911e3212250fc8933d/1.20-pre4.json");

    m_client->downloadClient("1.20-pre4");

    m_library->downloadLibraries("1.20-pre4");

    m_index->downloadAssetIndex("1.20-pre4");

    stopProgressDialog();

  } else if (versionStr == "1.19.4-pre4") {
    startProgressDialog();

    m_version->downloadVersion(
        "https://piston-meta.mojang.com/v1/packages/"
        "bfc041cde4125e6fb9da3fa1386ee881c663ca22/1.19.4-pre4.json");

    m_client->downloadClient("1.19.4-pre4");

    m_library->downloadLibraries("1.19.4-pre4");

    m_index->downloadAssetIndex("1.19.4-pre4");

    stopProgressDialog();

  } else if (versionStr == "23w17a") {
    startProgressDialog();
    m_version->downloadVersion(
        "https://piston-meta.mojang.com/v1/packages/"
        "f518509785dee0c0a7013f94f94b1423c732d298/23w17a.json");

    m_client->downloadClient("23w17a");

    m_library->downloadLibraries("23w17a");

    m_index->downloadAssetIndex("23w17a");

    stopProgressDialog();
  }
}

void Downloader::stop() {
  emit stopDownloading();
  QObject::connect(this, &Downloader::stopDownloading, m_version,
                   &DownloadVersion::stopIsDownloadingVersion);
  QObject::connect(this, &Downloader::stopDownloading, m_client,
                   &DownloadClient::stopIsDownloadingClient);
  QObject::connect(this, &Downloader::stopDownloading, m_library,
                   &DownloadLibraries::stopIsDownloadingLibraries);
  QObject::connect(this, &Downloader::stopDownloading, m_index,
                   &DownloadAssetIndex::stopIsDownloadingAssetIndex);
  QObject::connect(this, &Downloader::stopDownloading, m_resources,
                   &DownloadResources::stopIsDownloadingResources);
}

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
  QObject::connect(m_index, &DownloadAssetIndex::progressChanged, m_progress,
                   &QProgressDialog::setValue);
  QObject::connect(m_resources, &DownloadResources::progressChanged, m_progress,
                   &QProgressDialog::setValue);
}

void Downloader::stopProgressDialog() {
  QObject::connect(m_library, &DownloadLibraries::onFinished, m_progress,
                   &QProgressDialog::close);
  QObject::connect(m_version, &DownloadVersion::onFinished, m_progress,
                   &QProgressDialog::close);
  QObject::connect(m_client, &DownloadClient::onFinished, m_progress,
                   &QProgressDialog::close);

  QObject::connect(m_index, &DownloadAssetIndex::onFinished, m_progress,
                   &QProgressDialog::close);
  QObject::connect(m_resources, &DownloadResources::onFinished, m_progress,
                   &QProgressDialog::close);
}

void Downloader::getVersionGame(const QString &version) {
  versionStr = version;
}

bool Downloader::IsDownloading() const noexcept {
  return m_IsDownloading == "downloading" ? true : false;
}
