#pragma once

#include "launcher.hpp"

class Updater : public Launcher {
public:
    Updater();

   virtual ~Updater();

    Updater(const Updater &) = delete;

    Updater &operator=(const Updater &) = delete;

private slots:
  void start() override;

  void stop() override;

};
