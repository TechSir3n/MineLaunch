#include "path.hpp"

[[nodiscard]] QString Path::launcherPath() {
  return QCoreApplication::applicationDirPath();
}

[[nodiscard]] QString Path::minecraftPath() {

  return QDir::toNativeSeparators(launcherPath() +
                                  "/../MineLaunch/backend/launcher/minecraft");
}

[[nodiscard]] QString Path::librariesPath() {
  return QDir::toNativeSeparators(
      launcherPath() + "/../MineLaunch/backend/launcher/minecraft/libraries");
}

[[nodiscard]] QString Path::versionPath() {
  return QDir::toNativeSeparators(
      launcherPath() + "/../MineLaunch/backend/launcher/minecraft/versions");
}

[[nodiscard]] QString Path::logsPath() {
  return QDir::toNativeSeparators(launcherPath() +
                                  "/../MineLaunch/assistance/logs_files");
}

[[nodiscard]] QString Path::assetsPath() {
  return QDir::toNativeSeparators(
      launcherPath() + "/../MineLaunch/backend/launcher/minecraft/assets/objects");
}

[[nodiscard]] QString Path::assetIndexPath() {
  return QDir::toNativeSeparators(
      launcherPath() +
      "/../MineLaunch/backend/launcher/minecraft/assets/indexes");
}

[[nodiscard]] QString Path::modsPath() {
  return QDir::toNativeSeparators(
      launcherPath() + "/../MineLaunch/backend/launcher/minecraft/mods");
}

[[nodiscard]] QString Path::clientPath() {
  return QDir::toNativeSeparators(
      launcherPath() + "/../MineLaunch/backend/launcher/minecraft/versions");
}
