#ifndef SRC_PLATFORM_H
#define SRC_PLATFORM_H

#include "src/config.h"

#include <QString>

class Platform
{
public:

    static QString getSystemUsername();
    static QString getPlatformName();
};

#endif /** SRC_PLATFORM_H */
