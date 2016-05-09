#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQueryModel>
#include "skills.h"
#include <qDebug>

//-------------constructor----------

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    skills = new Skills();
    this->setupConnections();
}

//------------destructor-------------------

MainWindow::~MainWindow()
{
    delete ui;
}

//-------------custom slots--------------------

void MainWindow::setSkillsModel(QSqlQueryModel *model){
    ui->tableView_2->setModel(model);
}

//-------------custom methods----------------------

void MainWindow::setupConnections(){
    connect(skills, &Skills::changeSkillsModel, this, &MainWindow::setSkillsModel);
    this->refresh();
}

void MainWindow::refresh(){
    this->skills->refresh();
}


