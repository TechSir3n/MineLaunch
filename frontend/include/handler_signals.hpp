#pragma once

#include <QMessageBox>
#include <QObject>
#include <QPoint>
#include <QToolTip>
#include <QString>

class HandlerSignals : public QObject {
public slots:
  void onGameLauncherError(int exitCode) {
    QMessageBox::critical(nullptr, "Error",
                          "Startup error,exit code: " +
                              QString::number(exitCode));
  }
};
