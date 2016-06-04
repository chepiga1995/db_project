#include "skill.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

//--------------constructor----------------

Skill::Skill()
{
    searchName = "";
    sortField = "name";
    sortOrder = "DESC";
}

//--------------destructor----------------

Skill::~Skill() {

}

//--------------custom methods--------------

QSqlQueryModel * Skill::getSkillModel(){
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

void Skill::refresh(){
    QSqlQueryModel *model = this->getSkillModel();
    emit changeSkillModel(model);
}

void Skill::addSkill(QString & name, QString & description, QWidget* ui){
    if(name.length() > 100) {
        QMessageBox::critical(ui, "Fields", "Назва занадто довга!!") ;
        return;
    }
    QSqlQuery query;
    query.prepare("INSERT INTO skills (name, description) "
                  "VALUES (:name, :description)");
    query.bindValue(":name", name);
    query.bindValue(":description", description);

    query.exec();
    if(query.isActive()) {
        QMessageBox::information(ui, "Fields", "Вміння додано!!!") ;
        refresh();
        emit clearNewSkillFields();
    } else {
        QString message = (query.lastError()).databaseText();
        int index = message.indexOf("\n");
        QMessageBox::critical(ui, "Fields", message.left(index)) ;
    }
}

void Skill::search(QString & name){
    searchName = name;
    refresh();
}

void Skill::sort(int field, int order){
    QString fieldIndex[2] = {"name", "description"};
    QString sortIndex[2] = {"ASC", "DESC"};
    sortField = fieldIndex[field];
    sortOrder = sortIndex[order];
    refresh();
}
