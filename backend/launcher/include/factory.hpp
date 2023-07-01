#pragma once

#include "./assistance/defines.hpp"
#include "downloader.hpp"
#include "game.hpp"

class FactoryLauncher {
public:
  static Launcher *createLauncher(LauncherType type) {
    switch (type) {
    case LauncherType::Download:
        return new Downloader();
      break;

    case LauncherType::Play:
      return new PlayGame();
      break;

    default:
      return nullptr;
    }
  }
};
