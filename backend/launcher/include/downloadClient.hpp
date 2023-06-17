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
<<<<<<< HEAD
=======
   Q_OBJECT
>>>>>>> 21eb63f (commit)
public:
    DownloadClient(QObject *object = nullptr);

    ~DownloadClient();

    DownloadClient(const DownloadClient&)  = delete;

    DownloadClient & operator=(const DownloadClient &) = delete;

public:
    void downloadClient(const QString &versionClient);

<<<<<<< HEAD
=======
signals:
    void errorDownloadClient();

    void progressChanged(int progress);

private:
    void onStandardOutput();

    void onStandardErrorOutput();

>>>>>>> 21eb63f (commit)
private:
    QNetworkAccessManager *m_manager;
    QProcess *m_process;

};
