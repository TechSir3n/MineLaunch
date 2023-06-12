#pragma once

#include "./utils/defines.hpp"
#include "downloader.hpp".hpp"

class FactoryLauncher {
public:
  static Launcher *createLauncher(LauncherType type) {
    switch (type) {
    case LauncherType::Download:
        return new Downloader();
      break;
    case LauncherType::Update:
      break;

    case LauncherType::Play:

      break;

    default:
      return nullptr;
    }
  }
};
