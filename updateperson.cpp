#include "updateperson.h"
#include "ui_updateperson.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QSqlRecord>

UpdatePerson::UpdatePerson(QWidget *parent, QString per) :
    QDialog(parent),
    ui(new Ui::UpdatePerson)
{
    ui->setupUi(this);
    person = per;
    QSqlQuery query;
    query.prepare("SELECT education, email, phone_number, skype "
                  "FROM persons WHERE person_id=:person_id;");
    query.bindValue(":person_id", person);
    query.exec();
    if(!query.isActive()) {
       return;
    }
    query.first();
    QSqlRecord data = query.record();
    ui->personEducation->setText(data.value(0).toString());
    ui->personEmail->setText(data.value(1).toString());
    ui->personPhone->setText(data.value(2).toString());
    ui->personskype->setText(data.value(3).toString());
}

UpdatePerson::~UpdatePerson()
{
    delete ui;
}

void UpdatePerson::on_addPerson_clicked()
{

    QSqlQuery query;
    query.prepare("UPDATE persons SET education=:education, email=:email, phone_number=:phone_number, skype=:skype "
                  "WHERE person_id=:person_id;");
    query.bindValue(":education", ui->personEducation->toPlainText());
    query.bindValue(":email", ui->personEmail->text());
    query.bindValue(":phone_number", ui->personPhone->text());
    query.bindValue(":skype", ui->personskype->text());
    query.bindValue(":person_id", person);
    executeUpdate(query);
}

void UpdatePerson::executeUpdate(QSqlQuery & query){
    query.exec();
    if(query.isActive()) {
        QMessageBox::information(this, "Fields", "Данні оновлено!!!") ;
        this->hide();
    } else {
        QString message = (query.lastError()).databaseText();
        int index = message.indexOf("\n");
        QMessageBox::critical(this, "Fields", message.left(index)) ;
    }
}

void UpdatePerson::on_closePost_clicked()
{
    this->close();
}
