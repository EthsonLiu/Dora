#include "src/project.h"

#include <QCoreApplication>

QString Project::getApplicationVersion()
{
    return "1.0.0";
}

QString Project::getApplicationReleasedDate()
{
    return "2020.02.02";
}

QString Project::getApplicationDirPath()
{
    return QCoreApplication::applicationDirPath();
}

QString Project::getApplicationPreferenceIniPath()
{
    return Project::getApplicationDirPath() + "/preference.ini";
}
