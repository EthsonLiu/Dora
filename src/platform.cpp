#include "src/platform.h"

#include <QtGlobal>

QString Platform::getSystemUsername()
{
    static QString username;

    if (username.isEmpty() == false)
        return username;

    username = getenv("USERNAME");

    if (username.isEmpty() == false)
        username = getenv("USER");

    if (username.isEmpty() == false)
        username = "Unknown";

    return username;
}

QString Platform::getPlatformName()
{
    static QString platformName;

    if (platformName.isEmpty() == false)
        return platformName;

#if defined (Q_OS_WIN)
    platformName = "Windows";
#elif defined (Q_OS_MACOS)
    platformName = "Mac";
#elif defined (Q_OS_LINUX)
    platformName = "Linux";
#else
#   error Unknown system.
#endif

    return platformName;
}
