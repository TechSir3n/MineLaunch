#pragma once

#include <QObject>
#include <QDir>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QProcess>

class DownloadClient : public QObject {
public:
    DownloadClient(QObject *object = nullptr);

    ~DownloadClient();

    DownloadClient(const DownloadClient&)  = delete;

    DownloadClient & operator=(const DownloadClient &) = delete;

public:
    void downloadClient(const QString &versionClient);

private:
    QNetworkAccessManager *m_manager;
    QProcess *m_process;

};
