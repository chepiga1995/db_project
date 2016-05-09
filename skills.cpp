#include "skills.h"
#include <QSqlQueryModel>

//--------------constructor----------------

Skills::Skills()
{

}

//--------------destructor----------------

Skills::~Skills() {

}

//--------------custom methods--------------

QSqlQueryModel * Skills::getSkillsModel(){
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select name, description from skills");
    model->setHeaderData(0, Qt::Horizontal, tr("Назва"));
    model->setHeaderData(1, Qt::Horizontal, tr("Опис"));
    return model;
}

void Skills::refresh(){
    QSqlQueryModel *model = this->getSkillsModel();
    emit changeSkillsModel(model);
}


