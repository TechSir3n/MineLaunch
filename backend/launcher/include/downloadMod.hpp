#pragma once

#include "../../../exception/exception.hpp"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QFile>
#include <QFileInfo>
#include <QEventLoop>

constexpr inline const char ZIP[] = "application/zip";

constexpr inline const char JAR[] ="application/java-archive";

constexpr inline const char OCTET[] =  "application/octet-stream";

class DownloadMod : public QObject {
  Q_OBJECT
public:
  explicit DownloadMod(QObject *parent = nullptr);

    ~DownloadMod();

public slots:
  void setUrlAddressMod(const QString &url);

signals:
  void errorDownloadMod(const QString &errorStr);

private:
  QNetworkAccessManager *m_manager;
  QString m_url;
};
