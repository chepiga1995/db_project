#include "skills.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <qDebug>

//--------------constructor----------------

Skills::Skills()
{
    searchName = "";
    sortField = "name";
    sortOrder = "DESC";
}

//--------------destructor----------------

Skills::~Skills() {

}

//--------------custom methods--------------

QSqlQueryModel * Skills::getSkillsModel(){
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT name, description FROM skills WHERE name ~ :name ORDER BY " + sortField + " " + sortOrder);
    query.bindValue(":name", searchName);
    query.exec();

    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, tr("Назва"));
    model->setHeaderData(1, Qt::Horizontal, tr("Опис"));
    return model;
}

void Skills::refresh(){
    QSqlQueryModel *model = this->getSkillsModel();
    emit changeSkillsModel(model);
}

void Skills::addSkill(QString & name, QString & description){
    QSqlQuery query;
    query.prepare("INSERT INTO skills (name, description) "
                  "VALUES (:name, :description)");
    query.bindValue(":name", name);
    query.bindValue(":description", description);
    query.exec();

    if (query.numRowsAffected()) {
        refresh();
        emit clearNewSkillFields();
    } else {
        emit raiseAddSkillError();
    }
}

void Skills::search(QString & name){
    searchName = name;
    refresh();
}

void Skills::sort(int field, int order){
    QString fieldIndex[2] = {"name", "description"};
    QString sortIndex[2] = {"ASC", "DESC"};
    sortField = fieldIndex[field];
    sortOrder = sortIndex[order];
    refresh();
}

