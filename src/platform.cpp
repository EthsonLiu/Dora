/**
 * DUKTO - A simple, fast and multi-platform file transfer tool for LAN users
 * Copyright (C) 2011 Emanuele Colombo
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

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
