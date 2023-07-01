#include "custom.hpp"


Custom::Custom(QObject *parent) : QObject(parent)
{

}

void Custom::setLanguage(const char* language)
{
    m_language = language;
}

[[nodiscard]] QString Custom::getLanguage() const noexcept
{
    return  QLocale::system().name();
}
