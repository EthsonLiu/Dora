#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QSystemTrayIcon>
#include <QCloseEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);

protected:

    virtual void closeEvent(QCloseEvent* event);

private slots:

    void systemTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void exitApplication();

private:

    void createUpdatesCheckingDialog();
    QWidget* createGeneralWidget();
    void createPreferenceDialog();
    void createAboutDialog();
    void createSystemTray();
    QWidget* createMainWidget();

private:

    QDialog* m_preferenceDialog;
    QDialog* m_aboutDialog;
    QDialog* m_updatesCheckingDialog;

};
#endif // MAINWINDOW_H
