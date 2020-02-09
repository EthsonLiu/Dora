#include "main_window.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Dukto 7.0.0");

    createPreferenceDialog();
    createMenuBar();
    setCentralWidget(createMainWidget());
}

void MainWindow::createPreferenceDialog()
{
    m_preferenceDialog = new QDialog(this);
    m_preferenceDialog->setWindowTitle(tr("Preference"));
}

void MainWindow::createMenuBar()
{
    QMenu* fileMenu = menuBar()->addMenu(tr("File"));
    QAction* preferenceAction = new QAction(tr("Preference"), fileMenu);
    fileMenu->addAction(preferenceAction);
    connect(preferenceAction, &QAction::triggered, m_preferenceDialog, &QDialog::exec);
}

QWidget *MainWindow::createMainWidget()
{
    QWidget* mainWidget = new QWidget(this);

    return mainWidget;
}


