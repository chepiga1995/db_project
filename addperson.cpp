#include "addperson.h"
#include "ui_addperson.h"
#include "selectskill.h"
#include "selectpost.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

AddPerson::AddPerson(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPerson)
{
    ui->setupUi(this);
    ui->personSalary->setValidator( new QIntValidator(0, 100000, this) );
    post = "";
}

AddPerson::~AddPerson()
{
    delete ui;
}

void AddPerson::on_addPerson_clicked()
{
    QString salary = ui->personSalary->text();
    if(salary.length() == 0 || post.length() == 0){
        QMessageBox::critical(this, "Fields", "Заповніть всі поля!!!") ;
        return;
    }
    QSqlQuery query;
    QString array_text = "array[]::int[])";
    if (skills.length() > 0){
       array_text =  "ARRAY[" + skills.join(",") + "])";
    }
    query.prepare("SELECT create_person(:first_name, :last_name, :education, :salary, :login,"
                  " :email, :skype, :phone, :access_type, :birthday, :post_id," + array_text);
    query.bindValue(":first_name", ui->personName->text());
    query.bindValue(":education", ui->personEducation->toPlainText());
    query.bindValue(":last_name", ui->personSecondName->text());
    query.bindValue(":salary", ui->personSalary->text());
    query.bindValue(":login", ui->personLogin->text());
    query.bindValue(":email", ui->personEmail->text());
    query.bindValue(":skype", ui->personskype->text());
    query.bindValue(":phone", ui->personPhone->text());
    query.bindValue(":access_type", ui->personAccessType->currentText());
    query.bindValue(":birthday", ui->personBirthday->date().toString());
    query.bindValue(":post_id", post);
    executeInsert(query);
}

void AddPerson::executeInsert(QSqlQuery & query){
    query.exec();
    if(query.isActive()) {
        QMessageBox::information(this, "Fields", "Працівник доданий!!!") ;
        this->hide();
        emit personAdded();
    } else {
        QString message = (query.lastError()).databaseText();
        int index = message.indexOf("\n");
        QMessageBox::critical(this, "Fields", message.left(index)) ;
    }
}

void AddPerson::on_personChooseSkills_clicked()
{
    SelectSkill *select = new SelectSkill(0);
    select->init(skills);
    select->setModal(true);
    connect(select, &SelectSkill::selectSkills, this, &AddPerson::receiveSkills);
    select->show();
}

void AddPerson::receiveSkills(QStringList &ids, QStringList &names){
    skills = ids;
    ui->label_14->setText("Вибрані вміння: " + names.join(", "));
}

void AddPerson::on_personChoosePost_clicked()
{
    SelectPost *select = new SelectPost(0);
    select->init(post);
    select->setModal(true);
    connect(select, &SelectPost::selectPost, this, &AddPerson::receivePost);
    select->show();
}

void AddPerson::receivePost(QString &id, QStringList &data){
    post = id;
    ui->label_17->setText("Посада: " + data[0]);
    ui->label_18->setText("Мінімальна зарплата: " + data[1]);
    ui->label_19->setText("Максимальна зарплата: " + data[2]);
}

void AddPerson::on_closePost_clicked()
{
    this->close();
}
