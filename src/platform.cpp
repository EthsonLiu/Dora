#include "src/platform.h"

#include <QtGlobal>

#if defined(Q_OS_MACOS)
#   include <QTemporaryFile>
#   include <CoreServices/CoreServices.h>
#endif

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

QString Platform::getSystemUserAvatarPath()
{
    static QString path;

    if (path.isEmpty() == false)
        return path;

#if defined (Q_OS_WIN)

#elif defined (Q_OS_MACOS)
    static QTemporaryFile temporaryAvatarFile;
    QByteArray byteArray;
    CSIdentityQueryRef query = CSIdentityQueryCreateForCurrentUser(kCFAllocatorSystemDefault);
    CFErrorRef error;

    if (CSIdentityQueryExecute(query, kCSIdentityQueryGenerateUpdateEvents, &error))
    {
        CFArrayRef foundIds = CSIdentityQueryCopyResults(query);
        if (CFArrayGetCount(foundIds) == 1)
        {
            void* ref = const_cast<void*>(CFArrayGetValueAtIndex(foundIds, 0));
            CSIdentityRef userId = static_cast<CSIdentityRef>(ref);

            CFDataRef data = CSIdentityGetImageData(userId);
            byteArray.resize(static_cast<int>(CFDataGetLength(data)));
            CFDataGetBytes(data, CFRangeMake(0, CFDataGetLength(data)), reinterpret_cast<UInt8*>(byteArray.data()));
        }
    }

    CFRelease(query);

    temporaryAvatarFile.open();
    temporaryAvatarFile.write(byteArray);
    temporaryAvatarFile.close();
    return temporaryAvatarFile.fileName();
#elif defined (Q_OS_LINUX)

#endif

    return path;
}
