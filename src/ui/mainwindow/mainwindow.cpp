#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      project(),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_Management_triggered()
{
    SecuritiesManagementDialog *dialog = new SecuritiesManagementDialog(&this->project.rootSecurityCategory);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    ui->mdiArea->addSubWindow(dialog);
    dialog->show();
}


void MainWindow::on_action_Save_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Project", "", "Database files (*.db)");

}

