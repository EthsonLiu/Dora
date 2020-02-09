#include "main_window.h"

#include <QApplication>
#include <QtSingleApplication>

int main(int argc, char *argv[])
{
    /** Check for single running instance */
    QtSingleApplication a(argc, argv);
    if (a.isRunning())
    {
        a.sendMessage("FOREGROUND");
        return 0;
    }

    MainWindow w;
    w.show();
    return a.exec();
}
