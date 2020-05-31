#include "src/system_tray_widget.h"

#include <QMenu>
#include <QAction>
#include <QApplication>

SystemTrayWidget::SystemTrayWidget(QWidget* parent) : QWidget(parent)
{
    m_systemTrayIcon = new QSystemTrayIcon(this);
    m_systemTrayIcon->setIcon(QIcon(":/dora.png"));
    connect(m_systemTrayIcon, &QSystemTrayIcon::activated, this, &SystemTrayWidget::systemTrayIconActivated);
    m_systemTrayIcon->show();

    QMenu* systemTrayContextMenu = new QMenu(this);
    m_systemTrayIcon->setContextMenu(systemTrayContextMenu);

    QAction* showAppAction = new QAction(tr("Show Dora..."), systemTrayContextMenu);
    connect(showAppAction, &QAction::triggered, this, &SystemTrayWidget::showNormal);

    QAction* preferenceAction = new QAction(tr("Preference..."), systemTrayContextMenu);
    connect(preferenceAction, &QAction::triggered, this, &SystemTrayWidget::showPreferenceSignal);

    QAction* checkUpdatesAction = new QAction(tr("Check updates..."), systemTrayContextMenu);
    connect(checkUpdatesAction, &QAction::triggered, this, &SystemTrayWidget::showUpdatesCheckingSignal);

    QAction* aboutAction = new QAction(tr("About..."), systemTrayContextMenu);
    connect(aboutAction, &QAction::triggered, this, &SystemTrayWidget::showAboutSignal);

    QAction* quitAction = new QAction(tr("Quit Dora"), systemTrayContextMenu);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);

    systemTrayContextMenu->addAction(showAppAction);
    systemTrayContextMenu->addSeparator();
    systemTrayContextMenu->addAction(preferenceAction);
    systemTrayContextMenu->addAction(checkUpdatesAction);
    systemTrayContextMenu->addSeparator();
    systemTrayContextMenu->addAction(aboutAction);
    systemTrayContextMenu->addSeparator();
    systemTrayContextMenu->addAction(quitAction);
}

void SystemTrayWidget::systemTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::DoubleClick:
    {
        show();
        break;
    }
    default:
        break;
    }
}
