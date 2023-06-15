#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDir>
#include <QStringList>
#include <QJsonObject>
#include <QCoreApplication>

class DownloadLibraries : public QObject{
public:
    DownloadLibraries(QObject *object = nullptr);

    ~DownloadLibraries();

    DownloadLibraries(const DownloadLibraries &) = delete;

    DownloadLibraries & operator=(const DownloadLibraries &) = delete;

public:
 void downloadLibraries(const QString &versionGame) noexcept;

private:
 QNetworkAccessManager *m_manager;

};
