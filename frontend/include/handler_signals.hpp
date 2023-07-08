#pragma once

#include <QMessageBox>
#include <QObject>
#include <QPoint>
#include <QString>
#include <QToolTip>

class HandlerSignals : public QObject {
public slots:
  void onGameLauncherError(int exitCode) {
      QMessageBox::critical(nullptr, tr("Error"),
                            tr("Startup error,exit code: ") +
                              QString::number(exitCode));
  }

  void onDownloadClientError(const QString &errorStr) {
      QMessageBox::critical(nullptr, tr("Error download"), errorStr);
  }

  void onDownloadLibrariesError(const QString &errorStr) {
      QMessageBox::critical(nullptr, tr("Error download"), errorStr);
  }

  void onDownloadVersionError(const QString &errorStr) {
      QMessageBox::critical(nullptr, tr("Error download"), errorStr);
  }

  void onDownloadAssetIndexError(const QString &errorStr) {
      QMessageBox::critical(nullptr, tr("Error download"), errorStr);
  }

  void onDownloadAssetResoucresError(const QString &errorStr) {
      QMessageBox::critical(nullptr, tr("Error download"), errorStr);
  }
};
