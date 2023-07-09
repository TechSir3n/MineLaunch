#include "./include/downloader.hpp"

Downloader::Downloader() : m_pool(new QThreadPool()) {
  m_IsDownloading = "downloading";
  m_pool->setMaxThreadCount(5);
}

Downloader::~Downloader() {
  //delete m_pool;
//  delete m_versionTask;
//  delete m_clientTask;
//  delete m_resourceTask;
//  delete m_assetIndexTask;
}

void Downloader::start() {
  if (versionStr == "1.19.4-rc1") {
    emit downloadError(tr("This version is already installed by default "));

  } else if (versionStr == "23w03a") {
    m_versionTask = new DownloadVersionTask(
        "https://piston-meta.mojang.com/v1/packages/"
        "45574762988fd2ad3b9478cabcbe4024cd7321cc/23w03a.json");
    m_pool->start(m_versionTask);

    m_clientTask = new DownloadClientTask("23w03a");
    m_pool->start(m_clientTask);

    m_libraryTask = new DownloadLibrariesTask("23w03a");
    m_pool->start(m_libraryTask);

    m_assetIndexTask = new DownloadAssetIndexTask("23w03a");
    m_pool->start(m_assetIndexTask);

    m_resourceTask = new DownloadResourcesTask("2");
    m_pool->start(m_resourceTask);

    m_pool->waitForDone();

  } else if (versionStr == "1.20-pre7") {
    m_versionTask = new DownloadVersionTask(
        "https://piston-meta.mojang.com/v1/packages/"
        "88efb6148f5b63d3c86135bee3a0f5cb9a36130b/1.20-pre7.json");
    m_pool->start(m_versionTask);

    m_clientTask = new DownloadClientTask("1.20-pre7");
    m_pool->start(m_clientTask);

    m_libraryTask = new DownloadLibrariesTask("1.20-pre7");
    m_pool->start(m_libraryTask);

    m_assetIndexTask = new DownloadAssetIndexTask("1.20-pre7");
    m_pool->start(m_assetIndexTask);

    m_resourceTask = new DownloadResourcesTask("5");
    m_pool->start(m_resourceTask);

    m_pool->waitForDone();
  } else if (versionStr == "1.20-pre4") {
    m_versionTask = new DownloadVersionTask(
        "https://piston-meta.mojang.com/v1/packages/"
        "c8c93a569f6c46bc5c2785911e3212250fc8933d/1.20-pre4.json");
    m_pool->start(m_versionTask);

    m_clientTask = new DownloadClientTask("1.20-pre4");
    m_pool->start(m_clientTask);

    m_libraryTask = new DownloadLibrariesTask("1.20-pre4");
    m_pool->start(m_libraryTask);

    m_assetIndexTask = new DownloadAssetIndexTask("1.20-pre4");
    m_pool->start(m_assetIndexTask);

    m_resourceTask = new DownloadResourcesTask("5");
    m_pool->start(m_resourceTask);

    m_pool->waitForDone();
  } else if (versionStr == "1.19.4-pre4") {
    m_versionTask = new DownloadVersionTask(
        "https://piston-meta.mojang.com/v1/packages/"
        "bfc041cde4125e6fb9da3fa1386ee881c663ca22/1.19.4-pre4.json");
    m_pool->start(m_versionTask);

    m_clientTask = new DownloadClientTask("1.19.4-pre4");
    m_pool->start(m_clientTask);

    m_libraryTask = new DownloadLibrariesTask("1.19.4-pre4");
    m_pool->start(m_libraryTask);

    m_assetIndexTask = new DownloadAssetIndexTask("1.19.4-pre4");
    m_pool->start(m_assetIndexTask);

    m_resourceTask = new DownloadResourcesTask("3");
    m_pool->start(m_resourceTask);

    m_pool->waitForDone();
  } else if (versionStr == "23w17a") {
    m_versionTask = new DownloadVersionTask(
        "https://piston-meta.mojang.com/v1/packages/"
        "f518509785dee0c0a7013f94f94b1423c732d298/23w17a.json");
    m_pool->start(m_versionTask);

    m_clientTask = new DownloadClientTask("23w17a");
    m_pool->start(m_clientTask);

    m_libraryTask = new DownloadLibrariesTask("23w17a");
    m_pool->start(m_libraryTask);

    m_assetIndexTask = new DownloadAssetIndexTask("23w17a");
    m_pool->start(m_assetIndexTask);

    m_resourceTask = new DownloadResourcesTask("5");
    m_pool->start(m_resourceTask);

    m_pool->waitForDone();
  }
}

void Downloader::setVersionGame(const QString &version) {
  versionStr = version;
}

bool Downloader::IsDownloading() const noexcept {
  return m_IsDownloading == "downloading" ? true : false;
}
