#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQueryModel>
#include "skill.h"
#include "addpost.h"
#include <qDebug>

//-------------constructor----------

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    skill = new Skill;
    vacation_type = new VacationType;
    this->setupConnections();
}

//------------destructor-------------------

MainWindow::~MainWindow()
{
    delete ui;
}

//-------------custom slots--------------------

//skill

void MainWindow::setSkillModel(QSqlQueryModel *model){
    ui->tableViewSkill->setModel(model);
}

void MainWindow::clearSkillFields(){
    ui->lineEdit_2->clear();
    ui->textEdit->clear();
}

void MainWindow::showSkillAddError(){
    ui->label_4->show();
}

void MainWindow::changeSortFieldSkill(int i){
    int order = ui->tableViewSkill->horizontalHeader()->sortIndicatorOrder();
    skill->sort(i, order);
}

//vacation type

void MainWindow::setVacationTypeModel(QSqlQueryModel *model){
    ui->tableViewVacationType->setModel(model);
}

void MainWindow::clearVacationTypeFields(){
    ui->lineEdit_4->clear();
    ui->textEdit_2->clear();
}

void MainWindow::showVacationTypeAddError(){
    ui->label_8->show();
}

void MainWindow::changeSortFieldVacationType(int i){
    int order = ui->tableViewVacationType->horizontalHeader()->sortIndicatorOrder();
    vacation_type->sort(i, order);
}

//-------------custom methods----------------------

void MainWindow::setupConnections(){
    //skill
    connect(ui->tableViewSkill->horizontalHeader(), &QHeaderView::sectionClicked,
            this, &MainWindow::changeSortFieldSkill);
    connect(skill, &Skill::changeSkillModel, this, &MainWindow::setSkillModel);
    connect(skill, &Skill::clearNewSkillFields, this, &MainWindow::clearSkillFields);
    connect(skill, &Skill::raiseAddSkillError, this, &MainWindow::showSkillAddError);
    //vacation type
    connect(ui->tableViewVacationType->horizontalHeader(), &QHeaderView::sectionClicked,
            this, &MainWindow::changeSortFieldVacationType);
    connect(vacation_type, &VacationType::changeVacationTypeModel, this, &MainWindow::setVacationTypeModel);
    connect(vacation_type, &VacationType::clearNewVacationTypeFields, this, &MainWindow::clearVacationTypeFields);
    connect(vacation_type, &VacationType::raiseAddVacationTypeError, this, &MainWindow::showVacationTypeAddError);

    this->initSkill();
    this->initVacationType();
}

void MainWindow::initSkill(){
    skill->refresh();
    ui->label_4->hide();
}

void MainWindow::initVacationType(){
    vacation_type->refresh();
    ui->label_8->hide();
}



void MainWindow::on_addSkill_clicked()
{
    ui->label_4->hide();
    QString name = ui->lineEdit_2->text();
    QString description = ui->textEdit->toPlainText();
    skill->addSkill(name, description);
}

void MainWindow:: on_findSkill_clicked()
{
    QString name = ui->lineEdit->text();
    skill->search(name);
}


void MainWindow::on_addVacationType_clicked()
{
    ui->label_8->hide();
    QString name = ui->lineEdit_4->text();
    QString description = ui->textEdit_2->toPlainText();
    vacation_type->addVacationType(name, description);
}

void MainWindow::on_findVacationType_clicked()
{
    QString name = ui->lineEdit_3->text();
    vacation_type->search(name);
}

void MainWindow::on_pushButton_clicked()
{
    AddPost *add = new AddPost();
    add->setModal(true);
    add->show();
}
