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

void MainWindow::clearSkillFields(){
    ui->lineEdit_2->clear();
    ui->textEdit->clear();
}

void MainWindow::showSkillsAddError(){
    ui->label_4->show();
}

void MainWindow::changeSortFieldSkills(int i){
    int order = ui->tableView_2->horizontalHeader()->sortIndicatorOrder();
    skills->sort(i, order);
}

//-------------custom methods----------------------

void MainWindow::setupConnections(){
    connect(ui->tableView_2->horizontalHeader(), &QHeaderView::sectionClicked, this, &MainWindow::changeSortFieldSkills);
    connect(skills, &Skills::changeSkillsModel, this, &MainWindow::setSkillsModel);
    connect(skills, &Skills::clearNewSkillFields, this, &MainWindow::clearSkillFields);
    connect(skills, &Skills::raiseAddSkillError, this, &MainWindow::showSkillsAddError);
    this->initSkills();
}

void MainWindow::initSkills(){
    this->skills->refresh();
    ui->label_4->hide();
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->label_4->hide();
    QString name = ui->lineEdit_2->text();
    QString description = ui->textEdit->toPlainText();
    skills->addSkill(name, description);
}

void MainWindow::on_pushButton_clicked()
{
    QString name = ui->lineEdit->text();
    skills->search(name);
}

