#include "selectpost.h"
#include "ui_selectpost.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QDebug>
#include <QStringList>

SelectPost::SelectPost(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectPost)
{
    ui->setupUi(this);
    model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT post_id, name, min_salary, max_salary FROM posts");
    query.exec();

    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, tr("Назва"));
    model->setHeaderData(2, Qt::Horizontal, tr("Мінімальна зарплата"));
    model->setHeaderData(3, Qt::Horizontal, tr("Максимальна зарплата"));

    ui->tableViewPost->setModel(model);
}

void SelectPost::init(QString & default_selected){
    int size = model->rowCount();
    for (int i = 0; i < size; ++i) {
        QString val = (model->record(i)).field("post_id").value().toString();
        if(default_selected == val){
            ui->tableViewPost->selectRow(i);
        }
    }
}

SelectPost::~SelectPost()
{
    delete ui;
}

void SelectPost::on_select_clicked()
{
    QItemSelectionModel *select = ui->tableViewPost->selectionModel();
    QStringList data;
    QString id;
    int select_size = select->selectedRows().size();
    if(select_size > 0) {
        id = select->selectedRows(0)[0].data().toString();
        data << select->selectedRows(1)[0].data().toString();
        data << select->selectedRows(2)[0].data().toString();
        data << select->selectedRows(3)[0].data().toString();
    } else {
        id = "";
        data << "" << "" << "";
    }
    emit selectPost(id, data);
    this->close();
}

void SelectPost::on_cancel_clicked()
{
    this->close();
}
