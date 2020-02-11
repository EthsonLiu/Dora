#include "main_window.h"

#include <QApplication>
#include <QMenu>
#include <QAction>
#include <QIcon>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QTabWidget>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Dukto");

    createPreferenceDialog();
    createAboutDialog();
    createUpdatesCheckingDialog();
    createSystemTray();
    setCentralWidget(createMainWidget());
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    hide();
    event->ignore();
}

void MainWindow::systemTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
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

void MainWindow::createUpdatesCheckingDialog()
{
    m_updatesCheckingDialog = new QDialog(this);
    m_updatesCheckingDialog->setWindowTitle(tr("Check updates"));
}

QWidget* MainWindow::createGeneralWidget()
{
    QWidget* generalWidget = new QWidget;

    return generalWidget;
}

void MainWindow::createPreferenceDialog()
{
    m_preferenceDialog = new QDialog(this);
    m_preferenceDialog->setWindowTitle(tr("Preference"));

    QTabWidget* tabWidget = new QTabWidget(m_preferenceDialog);
    tabWidget->addTab(createGeneralWidget(), tr("General"));

    QHBoxLayout* hLayout = new QHBoxLayout(m_preferenceDialog);
    hLayout->addWidget(tabWidget);
    m_preferenceDialog->setLayout(hLayout);
}

void MainWindow::createAboutDialog()
{
    m_aboutDialog = new QDialog(this);
    m_aboutDialog->setWindowTitle(tr("About"));
}

void MainWindow::createSystemTray()
{
    QSystemTrayIcon* systemTrayIcon = new QSystemTrayIcon(this);
    systemTrayIcon->setIcon(QIcon(":/dukto.ico"));
    connect(systemTrayIcon, &QSystemTrayIcon::activated, this, &MainWindow::systemTrayIconActivated);
    systemTrayIcon->show();

    QMenu* systemTrayContextMenu = new QMenu(this);
    systemTrayIcon->setContextMenu(systemTrayContextMenu);

    QAction* showAppAction = new QAction(tr("Show Dukto"), systemTrayContextMenu);
    connect(showAppAction, &QAction::triggered, this, &MainWindow::show);

    QAction* preferenceAction = new QAction(tr("Preference"), systemTrayContextMenu);
    connect(preferenceAction, &QAction::triggered, m_preferenceDialog, &QDialog::exec);

    QAction* checkUpdatesAction = new QAction(tr("Check updates..."), systemTrayContextMenu);
    connect(checkUpdatesAction, &QAction::triggered, m_updatesCheckingDialog, &QDialog::exec);

    QAction* aboutAction = new QAction(tr("About"), systemTrayContextMenu);
    connect(aboutAction, &QAction::triggered, m_aboutDialog, &QDialog::exec);

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

QWidget* MainWindow::createMainWidget()
{
    QWidget* mainWidget = new QWidget(this);

    return mainWidget;
}


