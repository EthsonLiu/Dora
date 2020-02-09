#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QDialog>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);

private slots:


private:

    void createPreferenceDialog();
    void createMenuBar();
    QWidget* createMainWidget();

private:

    QDialog* m_preferenceDialog;

};
#endif // MAINWINDOW_H
