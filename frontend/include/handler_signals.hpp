#pragma once

#include <QMessageBox>
#include <QObject>
#include <QPoint>
#include <QString>
#include <QToolTip>

class HandlerSignals : public QObject {
public slots:
  void onGameLauncherError(int exitCode) {
    QMessageBox::critical(nullptr, "Error",
                          "Startup error,exit code: " +
                              QString::number(exitCode));
  }

  void onDownloadClientError(const QString &errorStr) {
    QMessageBox::critical(nullptr, "Error download", errorStr);
  }

  void onDownloadLibrariesError(const QString &errorStr) {
    QMessageBox::critical(nullptr, "Error download", errorStr);
  }

  void onDownloadVersionError(const QString &errorStr) {
    QMessageBox::critical(nullptr, "Error download", errorStr);
  }

  void onDownloadAssetIndexError(const QString &errorStr) {
    QMessageBox::critical(nullptr, "Error download", errorStr);
  }

  void onDownloadAssetResoucresError(const QString &errorStr) {
    QMessageBox::critical(nullptr, "Error download", errorStr);
  }
};
