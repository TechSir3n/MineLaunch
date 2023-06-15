#pragma once

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QByteArray>
#include <QFile>
#include <QJsonArray>
#include <QEventLoop>
#include <QObject>
#include <QDir>
#include <QCoreApplication>

class DownloadVersion : public QObject{
   Q_OBJECT
public:
    DownloadVersion(QObject *parent = nullptr);

    virtual ~DownloadVersion();

    DownloadVersion(const DownloadVersion &) = delete;

    DownloadVersion & operator=(const DownloadVersion &) = delete;

public:
    void downloadVersion(const QString &versionGame) noexcept;

private:
    QNetworkAccessManager *m_manager;
};
