#include "main_window.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Dukto");

    createPreferenceDialog();
    createAboutDialog();
    createMenuBar();
    setCentralWidget(createMainWidget());
}

void MainWindow::createPreferenceDialog()
{
    m_preferenceDialog = new QDialog(this);
    m_preferenceDialog->setWindowTitle(tr("Preference"));
}

void MainWindow::createAboutDialog()
{
    m_aboutDialog = new QDialog(this);
    m_aboutDialog->setWindowTitle(tr("About"));
}

void MainWindow::createMenuBar()
{
    QMenu* duktoMenu = menuBar()->addMenu(tr("Dukto"));

    QAction* preferenceAction = new QAction(tr("Preference"), duktoMenu);
    connect(preferenceAction, &QAction::triggered, m_preferenceDialog, &QDialog::exec);

    QAction* aboutAction = new QAction(tr("About"), duktoMenu);
    connect(aboutAction, &QAction::triggered, m_aboutDialog, &QDialog::exec);

    duktoMenu->addAction(preferenceAction);
    duktoMenu->addSeparator();
    duktoMenu->addAction(aboutAction);
}

QWidget* MainWindow::createMainWidget()
{
    QWidget* mainWidget = new QWidget(this);

    return mainWidget;
}


