#ifndef SRC_SYSTEM_TRAY_WIDGET_H
#define SRC_SYSTEM_TRAY_WIDGET_H

#include "src/config.h"

#include <QWidget>
#include <QSystemTrayIcon>

/**
 * A widget to show system tray.
 */
class SystemTrayWidget : public QWidget
{
    Q_OBJECT

public:

    SystemTrayWidget(QWidget* parent = nullptr);

signals:

    void showPreferenceSignal();
    void showUpdatesCheckingSignal();
    void showAboutSignal();

private slots:

    void systemTrayIconActivated(QSystemTrayIcon::ActivationReason reason);

private:

    QSystemTrayIcon* m_systemTrayIcon;
};

#endif /** SRC_SYSTEM_TRAY_WIDGET_H */
