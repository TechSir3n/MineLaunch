#pragma once

#include "../../../frontend/include/handler_signals.hpp"
#include "../../../exception/exception.hpp"
#include "downloadAssetIndex.hpp"
#include "downloadClient.hpp"
#include "downloadLibraries.hpp"
#include "downloadResources.hpp"
#include "downloadVersion.hpp"
#include <QProgressDialog>
#include <QRunnable>
#include <QThreadPool>

class DownloadVersionTask : public QObject, public QRunnable {
public:
  explicit DownloadVersionTask(const QString &url);

  ~DownloadVersionTask();

  DownloadVersionTask(const DownloadVersionTask &) = delete;

  DownloadVersionTask(const DownloadVersionTask &&) = delete;

protected:
  void run() override;

private:
  QString m_url;
  HandlerSignals *m_handler;
  QProgressDialog *m_progress;
  DownloadVersion *m_version;
};

class DownloadClientTask : public QObject, public QRunnable {
public:
  explicit DownloadClientTask(const QString &version);

  ~DownloadClientTask();

  DownloadClientTask(const DownloadClientTask &) = delete;

  DownloadClientTask(const DownloadClientTask &&) = delete;

protected:
  void run() override;

private:
  QString m_version;
  HandlerSignals *m_handler;
  QProgressDialog *m_progress;
  DownloadClient *m_client;
};

class DownloadLibrariesTask : public QObject, public QRunnable {
public:
  explicit DownloadLibrariesTask(const QString &version);

  ~DownloadLibrariesTask();

  DownloadLibrariesTask(const DownloadLibrariesTask &) = delete;

  DownloadLibrariesTask(const DownloadLibrariesTask &&) = delete;

protected:
  void run() override;

private:
  QString m_version;
  HandlerSignals *m_handler;
  QProgressDialog *m_progress;
  DownloadLibraries *m_library;
};

class DownloadAssetIndexTask : public QObject, public QRunnable {
public:
  explicit DownloadAssetIndexTask(const QString &version);

  ~DownloadAssetIndexTask();

  DownloadAssetIndexTask(const DownloadAssetIndexTask &) = delete;

  DownloadAssetIndexTask(const DownloadAssetIndexTask &&) = delete;

protected:
  void run() override;

private:
  QString m_version;
  HandlerSignals *m_handler;
  QProgressDialog *m_progress;
  DownloadAssetIndex *m_index;

};

class DownloadResourcesTask : public QObject, public QRunnable {
public:
  explicit DownloadResourcesTask(const QString &version);

  ~DownloadResourcesTask();

  DownloadResourcesTask(const DownloadResourcesTask &) = delete;

  DownloadResourcesTask(const DownloadResourcesTask &&) = delete;

protected:
  void run() override;

private:
  QString m_version;
  HandlerSignals *m_handler;
  QProgressDialog *m_progress;
  DownloadResources *m_resources;
};
