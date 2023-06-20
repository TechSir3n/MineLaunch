#include "./include/downloadResources.hpp"

DownloadResources::DownloadResources(QObject *parent)
    : QObject(parent), m_manager(new QNetworkAccessManager()) {}

void DownloadResources::downloadResources(const QString &versionGame)
{

}

void DownloadResources::stopIsDownloadingResources() {
  auto reply = getReply();
  reply->abort();
}

DownloadResources::~DownloadResources() { delete m_manager; }

QNetworkReply *DownloadResources::getReply(QNetworkReply *reply) noexcept {
  return reply;
}
