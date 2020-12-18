#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "button.h"
#include "panel.h"
#include "panelbuttons.h"
#include "gameproperties.h"
#include "settingsdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showSettings();
    void reassignPanels();
    void on_buttonStart_clicked();
    void on_buttonStop_clicked();

private:
    Ui::MainWindow *ui;
    GameProperties *properties;
    SettingsDialog *settings;

    Panel *playerPanel;
    Panel *aiPanel;

};
#endif // MAINWINDOW_H
