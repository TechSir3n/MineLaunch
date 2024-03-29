#pragma once

#include <QCoreApplication>
#include <QDir>
#include <QString>

class Path {
public:
  [[nodiscard]] static QString launcherPath();

  [[nodiscard]] static QString minecraftPath();

  [[nodiscard]] static QString librariesPath();

  [[nodiscard]] static QString versionPath();

  [[nodiscard]] static QString logsPath();

  [[nodiscard]] static QString assetsPath();

  [[nodscard]] static QString assetIndexPath();

  [[nodiscard]] static QString modsPath();

  [[nodiscard]] static QString clientPath();
};
