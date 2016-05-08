#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQueryModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select * from persons");
    model->setHeaderData(0, Qt::Horizontal, tr("Name"));
    model->setHeaderData(1, Qt::Horizontal, tr("Salary"));
    ui->tableView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}
