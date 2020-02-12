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

#include "src/system_tray_widget.h"

#include <QMenu>
#include <QAction>
#include <QApplication>

SystemTrayWidget::SystemTrayWidget(QWidget* parent) : QWidget(parent)
{
    m_systemTrayIcon = new QSystemTrayIcon(this);
    m_systemTrayIcon->setIcon(QIcon(":/dukto.ico"));
    connect(m_systemTrayIcon, &QSystemTrayIcon::activated, this, &SystemTrayWidget::systemTrayIconActivated);
    m_systemTrayIcon->show();

    QMenu* systemTrayContextMenu = new QMenu(this);
    m_systemTrayIcon->setContextMenu(systemTrayContextMenu);

    QAction* showAppAction = new QAction(tr("Show Dukto..."), systemTrayContextMenu);
    connect(showAppAction, &QAction::triggered, this, &SystemTrayWidget::showNormal);

    QAction* preferenceAction = new QAction(tr("Preference..."), systemTrayContextMenu);
    connect(preferenceAction, &QAction::triggered, this, &SystemTrayWidget::showPreferenceSignal);

    QAction* checkUpdatesAction = new QAction(tr("Check updates..."), systemTrayContextMenu);
    connect(checkUpdatesAction, &QAction::triggered, this, &SystemTrayWidget::showUpdatesCheckingSignal);

    QAction* aboutAction = new QAction(tr("About..."), systemTrayContextMenu);
    connect(aboutAction, &QAction::triggered, this, &SystemTrayWidget::showAboutSignal);

    QAction* quitAction = new QAction(tr("Quit Dukto"), systemTrayContextMenu);
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
