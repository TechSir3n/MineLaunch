#include "custom.hpp"

Custom::Custom(QObject *parent)
    : QObject(parent), m_settings("./MineLaunch.ini", QSettings::IniFormat) {}

void Custom::setLanguage(const char *language) { m_language = language; }

void Custom::setExtensionGame(const QStringList &extension) {
  m_settings.setValue("extension", extension);
}

void Custom::setQualityGraphic(const QStringList &graphic) {
  m_settings.setValue("graphic", graphic);
}

void Custom::setSound(const QStringList &sound) {
  m_settings.setValue("sound", sound);
}

void Custom::setBrightness(const QStringList &brightness) {
  m_settings.setValue("brightness", brightness);
}

void Custom::setScreenMode(const QStringList &screenMode) {
  m_settings.setValue("screenMode", screenMode);
}

void Custom::setLanguage(const QStringList &language) {
  m_settings.setValue("language", language);
}

void Custom::setMaxAndMinMemory(const QStringList &memory) {
  m_settings.setValue("memory", memory);
}

[[nodiscard]] QString Custom::getLanguage() const noexcept {
  return QLocale::system().name();
}

[[nodiscard]] QStringList Custom::getExtension() const noexcept {
  return m_settings.value("extension").toStringList();
}

[[nodiscard]] QStringList Custom::getQualityGraphic() const noexcept {
  return m_settings.value("graphic").toStringList();
}

[[nodiscard]] QStringList Custom::getSound() const noexcept {
  return m_settings.value("sound").toStringList();
}

[[nodiscard]] QStringList Custom::getBrightness() const noexcept {
  return m_settings.value("brightness").toStringList();
}

[[nodiscard]] QStringList Custom::getScreenMode() const noexcept {
  return m_settings.value("screenMode").toStringList();
}

[[nodiscard]] QStringList Custom::getLanguageGame() const noexcept {
  return m_settings.value("language").toStringList();
}

[[nodiscard]] QStringList Custom::getUseMemory() const noexcept {
  return m_settings.value("memory").toStringList();
}
