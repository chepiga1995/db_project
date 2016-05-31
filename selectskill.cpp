#include "selectskill.h"
#include "ui_selectskill.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QDebug>
#include <QStringList>

SelectSkill::SelectSkill(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectSkill)
{
    ui->setupUi(this);
    model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT skill_id, name FROM skills");
    query.exec();

    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, tr("Назва"));

    ui->tableViewSkill->setModel(model);

//
}

void SelectSkill::init(QStringList & default_selected){
    int size = model->rowCount();
    for (int i = 0; i < size; ++i) {
        QString val = (model->record(i)).field("skill_id").value().toString();
        if(default_selected.contains(val)){
            ui->tableViewSkill->selectRow(i);
        }
    }
}

SelectSkill::~SelectSkill()
{
    delete ui;
}

void SelectSkill::on_select_clicked()
{
    QItemSelectionModel *select = ui->tableViewSkill->selectionModel();
    QStringList ids, names;
    int select_size = select->selectedRows().size();
    for (int i = 0; i < select_size; ++i) {
        ids << select->selectedRows(0)[i].data().toString();
        names << select->selectedRows(1)[i].data().toString();
    }
    emit selectSkills(ids, names);
    this->close();
}

void SelectSkill::on_cancel_clicked()
{
    this->close();
}
