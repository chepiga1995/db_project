#include "vacation_type.h"

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <qDebug>

//--------------constructor----------------

VacationType::VacationType()
{
    searchName = "";
    sortField = "name";
    sortOrder = "DESC";
}

//--------------destructor----------------

VacationType::~VacationType() {

}

//--------------custom methods--------------

QSqlQueryModel * VacationType::getVacationTypeModel(){
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT name, description FROM vacation_type WHERE name ~ :name ORDER BY " + sortField + " " + sortOrder);
    query.bindValue(":name", searchName);
    query.exec();

    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, tr("Назва"));
    model->setHeaderData(1, Qt::Horizontal, tr("Опис"));
    return model;
}

void VacationType::refresh(){
    QSqlQueryModel *model = this->getVacationTypeModel();
    emit changeVacationTypeModel(model);
}

void VacationType::addVacationType(QString & name, QString & description){
    QSqlQuery query;
    query.prepare("INSERT INTO vacation_type (name, description) "
                  "VALUES (:name, :description)");
    query.bindValue(":name", name);
    query.bindValue(":description", description);
    query.exec();

    if (query.numRowsAffected()) {
        refresh();
        emit clearNewVacationTypeFields();
    } else {
        emit raiseAddVacationTypeError();
    }
}

void VacationType::search(QString & name){
    searchName = name;
    refresh();
}

void VacationType::sort(int field, int order){
    QString fieldIndex[2] = {"name", "description"};
    QString sortIndex[2] = {"ASC", "DESC"};
    sortField = fieldIndex[field];
    sortOrder = sortIndex[order];
    refresh();
}
