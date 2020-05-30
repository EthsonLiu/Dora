#include "src/about_widget.h"
#include "src/updates_checking_widget.h"
#include "src/system_tray_widget.h"
#include "src/dora_widget.h"

#include <QApplication>
#include <QtSingleApplication>

int main(int argc, char *argv[])
{
    /** check for single running instance */
    QtSingleApplication a(argc, argv);
    if (a.isRunning())
    {
        a.sendMessage("FOREGROUND");
        return 0;
    }

    a.setQuitOnLastWindowClosed(false);

    AboutWidget aboutWidget;
    UpdatesCheckingWidget updatesCheckingWidget;
    SystemTrayWidget systemTrayWidget;
    DoraWidget doraWidget;

    QObject::connect(&systemTrayWidget, &SystemTrayWidget::showAboutSignal, &aboutWidget, &AboutWidget::show);
    QObject::connect(&systemTrayWidget, &SystemTrayWidget::showUpdatesCheckingSignal, &updatesCheckingWidget, &UpdatesCheckingWidget::show);
    QObject::connect(&systemTrayWidget, &SystemTrayWidget::showPreferenceSignal, &doraWidget, &DoraWidget::showPreferenceWidget);

    doraWidget.show();

    return a.exec();
}
