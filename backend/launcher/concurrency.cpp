#include "./include/concurrency.hpp"

DownloadVersionTask::DownloadVersionTask(const QString &url)
    : m_handler(new HandlerSignals()), m_progress(new QProgressDialog()),
      m_version(new DownloadVersion(this)), m_url(url) {
  QObject::connect(m_version, &DownloadVersion::errorDownloadVersion, m_handler,
                   &HandlerSignals::onDownloadVersionError);

  m_progress->setLabelText(tr("Downloading..."));
  m_progress->setCancelButtonText(tr("Cancel"));
  m_progress->setRange(0, 100);
  m_progress->setMinimumDuration(0);
  m_progress->setWindowModality(Qt::WindowModal);
  m_progress->show();

  QObject::connect(m_version, &DownloadVersion::onFinished, m_progress,
                   &QProgressDialog::close);

  QObject::connect(m_version, &DownloadVersion::progressChanged, m_progress,
                   &QProgressDialog::setValue);
}

void DownloadVersionTask::run() {
  if (m_version != nullptr) {
    try {
      m_version->downloadVersion(m_url);
    } catch (const std::runtime_error &e) {
      qDebug() << "Exception Caught" << e.what();
    }
  } else {
    throw NullPointerException("DownloladVersionTask has null pointer");
  }
}

DownloadVersionTask::~DownloadVersionTask() {
  delete m_handler;
  delete m_progress;
}

DownloadClientTask::DownloadClientTask(const QString &version)
    : m_handler(new HandlerSignals()), m_client(new DownloadClient(this)),
      m_progress(new QProgressDialog()), m_version(version) {
  QObject::connect(m_client, &DownloadClient::errorDownloadClient, m_handler,
                   &HandlerSignals::onDownloadClientError);

  m_progress->setLabelText(tr("Downloading..."));
  m_progress->setCancelButtonText(tr("Cancel"));
  m_progress->setRange(0, 100);
  m_progress->setMinimumDuration(0);
  m_progress->setWindowModality(Qt::WindowModal);
  m_progress->show();

  QObject::connect(m_client, &DownloadClient::onFinished, m_progress,
                   &QProgressDialog::close);

  QObject::connect(m_client, &DownloadClient::progressChanged, m_progress,
                   &QProgressDialog::setValue);
}

void DownloadClientTask::run() {
  if (m_client != nullptr) {
    try {

      m_client->downloadClient(m_version);
    } catch (const std::runtime_error &e) {
      qDebug() << "Exception Caught" << e.what();
    }
  } else {
    throw NullPointerException("DownloladClientTask has null pointer");
  }
}

DownloadClientTask::~DownloadClientTask() {
  delete m_handler;
  delete m_progress;
}

DownloadLibrariesTask::DownloadLibrariesTask(const QString &version)
    : m_handler(new HandlerSignals()), m_progress(new QProgressDialog()),
      m_library(new DownloadLibraries(this)), m_version(version) {

  QObject::connect(m_library, &DownloadLibraries::errorDownloadLibraries,
                   m_handler, &HandlerSignals::onDownloadLibrariesError);

  m_progress->setLabelText(tr("Downloading..."));
  m_progress->setCancelButtonText(tr("Cancel"));
  m_progress->setRange(0, 100);
  m_progress->setMinimumDuration(0);
  m_progress->setWindowModality(Qt::WindowModal);
  m_progress->show();

  QObject::connect(m_library, &DownloadLibraries::onFinished, m_progress,
                   &QProgressDialog::close);

  QObject::connect(m_library, &DownloadLibraries::progressChanged, m_progress,
                   &QProgressDialog::setValue);
}

void DownloadLibrariesTask::run() {
  if (m_library != nullptr) {
    try {
      m_library->downloadLibraries(m_version);
    } catch (const std::runtime_error &e) {
      qDebug() << "Exception Caught" << e.what();
    }
  } else {
    throw NullPointerException("DownloladLibraryTask has null pointer");
  }
}

DownloadLibrariesTask::~DownloadLibrariesTask() {
  delete m_handler;
  delete m_progress;
}

DownloadAssetIndexTask::DownloadAssetIndexTask(const QString &version)
    : m_handler(new HandlerSignals()), m_progress(new QProgressDialog()),
      m_index(new DownloadAssetIndex(this)), m_version(version) {

  QObject::connect(m_index, &DownloadAssetIndex::errorDownloadAssetIndex,
                   m_handler, &HandlerSignals::onDownloadAssetIndexError);

  m_progress->setLabelText(tr("Downloading..."));
  m_progress->setCancelButtonText(tr("Cancel"));
  m_progress->setRange(0, 100);
  m_progress->setMinimumDuration(0);
  m_progress->setWindowModality(Qt::WindowModal);
  m_progress->show();

  QObject::connect(m_index, &DownloadAssetIndex::onFinished, m_progress,
                   &QProgressDialog::close);

  QObject::connect(m_index, &DownloadAssetIndex::progressChanged, m_progress,
                   &QProgressDialog::setValue);
}

void DownloadAssetIndexTask::run() {
  if (m_index != nullptr) {
    try {

      m_index->downloadAssetIndex(m_version);
    } catch (const std::exception &e) {
      qDebug() << "Exception Caught" << e.what();
    }
  } else {
    throw NullPointerException("DownloladAssetIndexTask has null pointer");
  }
}

DownloadAssetIndexTask::~DownloadAssetIndexTask() {
  delete m_handler;
  delete m_progress;
}

DownloadResourcesTask::DownloadResourcesTask(const QString &version)
    : m_handler(new HandlerSignals), m_progress(new QProgressDialog()),
      m_resources(new DownloadResources(this)), m_version(version) {

  QObject::connect(m_resources, &DownloadResources::errorDownloadResources,
                   m_handler, &HandlerSignals::onDownloadAssetResoucresError);

  m_progress->setLabelText(tr("Downloading..."));
  m_progress->setCancelButtonText(tr("Cancel"));
  m_progress->setRange(0, 100);
  m_progress->setMinimumDuration(0);
  m_progress->setWindowModality(Qt::WindowModal);
  m_progress->show();

  QObject::connect(m_resources, &DownloadResources::onFinished, m_progress,
                   &QProgressDialog::close);

  QObject::connect(m_resources, &DownloadResources::progressChanged, m_progress,
                   &QProgressDialog::setValue);
}

void DownloadResourcesTask::run() {
  if (m_resources != nullptr) {
    try {
      m_resources->downloadResources(m_version);
    } catch (const std::exception &e) {
      qDebug() << "Exception Caught" << e.what();
    }
  } else {
    throw NullPointerException("DownloladResourcesTask has null pointer");
  }
}

DownloadResourcesTask::~DownloadResourcesTask() {
  delete m_handler;
  delete m_progress;
}
