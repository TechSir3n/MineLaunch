#pragma once

#include "launcher.hpp"

class Updater : public Launcher {
private:
  void start() override;

  void stop() override;

public:
  Updater() = default;

  ~Updater() = default;

  Updater(const Updater &) = delete;

  Updater &operator=(const Updater &) = delete;
};
