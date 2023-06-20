#pragma

#include <QString>

#ifdef Q_OS_WIN
constexpr const QString getSysName() noexcept { return "windows"; }

#elif defined(Q_OS_MACOS)
constexpr const QString getSysName() noexcept { return "macos"; }

#elif defined(Q_OS_LINUX)
constexpr const QString getSysName() noexcept { return "linux"; }

#endif
