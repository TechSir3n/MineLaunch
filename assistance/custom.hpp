#pragma once

#include <QLocale>
#include <QObject>
#include <QSettings>
#include <QString>

class Custom : public QObject {
  Q_OBJECT
public:
  explicit Custom(QObject *parent = nullptr);

  ~Custom() = default;

public slots:
  void setLanguage(const char *language);

public:
  void setExtensionGame(const QStringList &extension);

  void setQualityGraphic(const QStringList &graphic);

  void setSound(const QStringList &sound);

  void setBrightness(const QStringList &brightness);

  void setScreenMode(const QStringList &screenMode);

  void setLanguage(const QStringList &language);

  void setMaxAndMinMemory(const QStringList &memory);

public:
  [[nodiscard]] QString getLanguage() const noexcept;

  [[nodiscard]] QStringList getExtension() const noexcept;

  [[nodiscard]] QStringList getQualityGraphic() const noexcept;

  [[nodiscard]] QStringList getSound() const noexcept;

  [[nodiscard]] QStringList getBrightness() const noexcept;

  [[nodiscard]] QStringList getScreenMode() const noexcept;

  [[nodiscard]] QStringList getLanguageGame() const noexcept;

  [[nodiscard]] QStringList getUseMemory() const noexcept;

private:
  QSettings m_settings;
  QString m_language;
};
