#include "about_widget.h"
#include "updates_checking_widget.h"
#include "system_tray_widget.h"
#include "dukto_widget.h"

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
    DuktoWidget duktoWidget;

    QObject::connect(&systemTrayWidget, &SystemTrayWidget::showAboutSignal, &aboutWidget, &AboutWidget::show);
    QObject::connect(&systemTrayWidget, &SystemTrayWidget::showUpdatesCheckingSignal, &updatesCheckingWidget, &UpdatesCheckingWidget::show);
    QObject::connect(&systemTrayWidget, &SystemTrayWidget::showPreferenceSignal, &duktoWidget, &DuktoWidget::showPreferenceWidget);

    duktoWidget.show();

    return a.exec();
}
