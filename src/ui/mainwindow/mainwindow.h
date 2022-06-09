#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include "src/project/project.h"
#include "src/ui/securities_management/securitiesmanagementdialog.h"

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
    void on_action_Management_triggered();

    void on_action_Save_triggered();

private:
    Project project;

    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
