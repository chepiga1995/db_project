#include "person.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <qDebug>
#include <QMessageBox>
#include <QSqlError>

Person::Person()
{
    searchName = "";
    searchLastName = "";
    sortField = "person_id";
    sortOrder = "DESC";
}

Person::~Person()
{

}

QSqlQueryModel * Person::getPersonModel(){
    model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM complete_person"
                  " WHERE first_name ~ :name and last_name ~ :last_name ORDER BY " + sortField + " " + sortOrder);
    query.bindValue(":name", searchName);
    query.bindValue(":last_name", searchLastName);
    query.exec();

    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, tr("Імя"));
    model->setHeaderData(2, Qt::Horizontal, tr("Прізвище"));
    model->setHeaderData(3, Qt::Horizontal, tr("Логін"));
    model->setHeaderData(4, Qt::Horizontal, tr("Тип доступу"));
    model->setHeaderData(5, Qt::Horizontal, tr("Дата народження"));
    model->setHeaderData(6, Qt::Horizontal, tr("Посада"));
    model->setHeaderData(7, Qt::Horizontal, tr("У відпустці"));

    return model;
}

void Person::refresh(){
    QSqlQueryModel *model = this->getPersonModel();
    emit changePersonModel(model);
}

void Person::search(QString & name, QString & last_name){
    searchName = name;
    searchLastName = last_name;
    emit refreshPersonPage();
}

void Person::sort(int field, int order){
    QString fieldIndex[8] = {"person_id", "first_name", "last_name", "login", "access_type", "birthday", "is_work", "is_vacation"};
    QString sortIndex[2] = {"ASC", "DESC"};
    sortField = fieldIndex[field];
    sortOrder = sortIndex[order];
    emit refreshPersonPage();
}


