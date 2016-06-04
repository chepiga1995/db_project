#include "changeperson.h"
#include "ui_changeperson.h"
#include "selectpost.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

ChangePerson::ChangePerson(QWidget *parent, QString per) :
    QDialog(parent),
    ui(new Ui::ChangePerson)
{
    ui->setupUi(this);
    ui->personSalary->setValidator( new QIntValidator(0, 100000, this) );
    post = "";
    person = per;
}

ChangePerson::~ChangePerson()
{
    delete ui;
}

void ChangePerson::on_addPerson_clicked()
{
    QString salary = ui->personSalary->text();
    if(salary.length() == 0 || post.length() == 0){
        QMessageBox::critical(this, "Fields", "Заповніть всі поля!!!") ;
        return;
    }
    QSqlQuery query;
    query.prepare("SELECT change_person(:salary, :post_id, :person_id)");
    query.bindValue(":salary", ui->personSalary->text());
    query.bindValue(":post_id", post);
    query.bindValue(":person_id", person);
    executeInsert(query);
}

void ChangePerson::executeInsert(QSqlQuery & query){
    query.exec();
    if(query.isActive()) {
        QMessageBox::information(this, "Fields", "Працівник переведений!!!") ;
        this->hide();
        emit personAdded();
    } else {
        QString message = (query.lastError()).databaseText();
        int index = message.indexOf("\n");
        QMessageBox::critical(this, "Fields", message.left(index)) ;
    }
}


void ChangePerson::on_personChoosePost_clicked()
{
    SelectPost *select = new SelectPost(0);
    select->init(post);
    select->setModal(true);
    connect(select, &SelectPost::selectPost, this, &ChangePerson::receivePost);
    select->show();
}

void ChangePerson::receivePost(QString &id, QStringList &data){
    post = id;
    ui->label_17->setText("Посада: " + data[0]);
    ui->label_18->setText("Мінімальна зарплата: " + data[1]);
    ui->label_19->setText("Максимальна зарплата: " + data[2]);
}



void ChangePerson::on_closePost_clicked()
{
    this->close();
}
