#include "path.hpp"


QString Path::launcherPath()
{
    return QCoreApplication::applicationDirPath();
}

QString Path::minecraftPath()
{
    QString path = QCoreApplication::applicationDirPath();
    path += QDir::toNativeSeparators("/../MineLaunch/backend/launcher/minecraft");
    return path;
}
