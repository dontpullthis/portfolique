#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , project()
    , ui(new Ui::MainWindow)
    , securitiesManagementDialog(&this->project.rootSecurityCategory, nullptr)


{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_Management_triggered()
{
    securitiesManagementDialog.show();
}

