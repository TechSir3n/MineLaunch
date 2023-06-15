#include "./include/downloadLibraries.hpp"

DownloadLibraries::DownloadLibraries(QObject *object) : QObject(object),m_manager(new QNetworkAccessManager())
{

}

DownloadLibraries::~DownloadLibraries()
{
    delete m_manager;
}


void DownloadLibraries::downloadLibraries(const QString &versionGame) noexcept
{
    const QString path = QCoreApplication::applicationDirPath() + "/../" + "/MineLaunch/backend/launcher/minecraft/versions";
    QDir dir(path);

    QStringList dirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    if(dirs.contains(versionGame)) {
            //QFile file("");

    }

}

