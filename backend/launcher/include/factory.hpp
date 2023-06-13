#pragma once

#include "./utils/defines.hpp"
#include "downloader.hpp"
#include "updater.hpp"
#include "game.hpp"

class FactoryLauncher {
public:
  static Launcher *createLauncher(LauncherType type) {
    switch (type) {
    case LauncherType::Download:
        return new Downloader();
      break;

    case LauncherType::Update:
      return new Updater();
      break;

    case LauncherType::Play:
      return new PlayGame();
      break;

    default:
      return nullptr;
    }
  }
};
