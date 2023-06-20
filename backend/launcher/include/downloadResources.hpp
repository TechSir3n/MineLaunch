#pragma once

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class DownloadResources : public QObject {
  Q_OBJECT
public:
  DownloadResources(QObject *parent = nullptr);

  ~DownloadResources();

  DownloadResources(const DownloadResources &) = delete;

  DownloadResources &operator=(const DownloadResources &) = delete;

public slots:
  void stopIsDownloadingResources();

signals:
  void errorDownloadResources(const QString &errorStr);

  void progressChanged(int progress);

  void onFinished();

private:
  QNetworkReply *getReply(QNetworkReply *reply = nullptr) noexcept;

private:
  QNetworkAccessManager *m_manager;
};
