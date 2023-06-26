#pragma once

#include "./assistance/path.hpp"
#include <QDir>
#include <QFile>
#include <QStringList>

class ClearLogs {
public slots:
  void clearLogs() noexcept {
    QDir logsDir(QDir::cleanPath(Path::launcherPath() + "/../" +
                                 "/MineLaunch/utils/logs_files/"));

    QStringList filters;
    filters << "*.log";
    logsDir.setNameFilters(filters);
    logsDir.setFilter(QDir::Files | QDir::NoDotAndDotDot);

    for (const auto &file : logsDir.entryList()) {
      QFile::remove(logsDir.absoluteFilePath(file));
    }
  }
};
