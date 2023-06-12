#pragma once

#include <QMessageBox>
#include <QObject>
#include <QPoint>
#include <QToolTip>


class HandlerSignals : public QObject {
public slots:
  void onDownloadError() {
          qDebug() << "Process download is running1";
    QMessageBox::critical(nullptr, "Error", "Failed to download");
  }

  void onDownloadStopped() {
        qDebug() << "Process download is running2";
    QToolTip::showText(QPoint(), "Download is stopped");
  }

  void onDownloadFinished() {
        qDebug() << "Process download is running3";
    QMessageBox::information(nullptr, "Information",
                            "Minecraft success downloaded");
  }
};
