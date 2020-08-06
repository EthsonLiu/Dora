#ifndef SRC_PROJECT_H
#define SRC_PROJECT_H

#include "src/config.h"

#include <QString>

class Project
{
public:

    static QString getApplicationVersion();
    static QString getApplicationReleasedDate();
    static QString getApplicationDirPath();
    static QString getApplicationPreferenceIniFile();
};

#endif /** SRC_PROJECT_H */
