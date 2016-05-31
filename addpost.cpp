#include "addpost.h"
#include "ui_addpost.h"
#include "selectskill.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

AddPost::AddPost(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPost)
{
    ui->setupUi(this);
    ui->postMinSalary->setValidator( new QIntValidator(0, 100000, this) );
    ui->postMaxSalary->setValidator( new QIntValidator(0, 100000, this) );
    ui->amountOfpalces->setValidator( new QIntValidator(1, 100, this) );

}

AddPost::~AddPost()
{
    delete ui;
}

void AddPost::on_addPost_clicked()
{
    QString min_salary = ui->postMinSalary->text();
    QString max_salary = ui->postMaxSalary->text();
    QString amount = ui->amountOfpalces->text();
    if(min_salary.length() == 0 || max_salary.length() == 0 || amount.length() == 0){
        QMessageBox::critical(this, "Fields", "Заповніть всі поля!!!") ;
        return;
    }
    QSqlQuery query;
    query.prepare("SELECT create_post(:name, :description, :min_salary, :max_salary,"
                  " :amount, ARRAY[" + skills.join(",") + "])");
    query.bindValue(":name", ui->postName->text());
    query.bindValue(":description", ui->postDescription->toPlainText());
    query.bindValue(":min_salary", min_salary);
    query.bindValue(":max_salary", max_salary);
    query.bindValue(":amount", amount);
    executeInsert(query);
}

void AddPost::executeInsert(QSqlQuery & query){
    query.exec();
     if(query.isActive()) {
         QMessageBox::information(this, "Fields", "Посада додана!!!") ;
        this->hide();
     } else {
        QString message = (query.lastError()).databaseText();
        int index = message.indexOf("\n");
        QMessageBox::critical(this, "Fields", message.left(index)) ;
     }
}

void AddPost::on_postChooseSkills_clicked()
{
    SelectSkill *select = new SelectSkill(0);
    select->init(skills);
    select->setModal(true);
    connect(select, &SelectSkill::selectSkills, this, &AddPost::receiveSkills);
    select->show();
}

void AddPost::receiveSkills(QStringList &ids, QStringList &names){
    skills = ids;
    ui->label_14->setText("Вибрані вміння: " + names.join(", "));
}
