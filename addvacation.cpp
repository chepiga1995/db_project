#include "addvacation.h"
#include "ui_addvacation.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QStringList>

AddVacation::AddVacation(QWidget *parent, QString per) :
    QDialog(parent),
    ui(new Ui::AddVacation)
{
    ui->setupUi(this);
    person = per;
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT vacation_type_id, name, description FROM vacation_type");
    query.exec();

    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, tr("Назва"));
    model->setHeaderData(2, Qt::Horizontal, tr("Опис"));

    ui->tableViewVacationType->setModel(model);
}

AddVacation::~AddVacation()
{
    delete ui;
}

void AddVacation::on_addVacation_clicked()
{
    QItemSelectionModel *select = ui->tableViewVacationType->selectionModel();
    QString id;
    int select_size = select->selectedRows().size();
    if(select_size > 0) {
        id = select->selectedRows(0)[0].data().toString();
    } else {
        QMessageBox::critical(this, "Fields", "Виберіть тип відпустки!!!") ;
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT create_vacation(:vacation_type_id, :person_id)");
    query.bindValue(":vacation_type_id", id);
    query.bindValue(":person_id", person);
    executeInsert(query);
}

void AddVacation::executeInsert(QSqlQuery & query){
    query.exec();
    if(query.isActive()) {
        QMessageBox::information(this, "Fields", "Відпустка додана!!!") ;
        this->hide();
        emit vacationAdded();
    } else {
        QString message = (query.lastError()).databaseText();
        int index = message.indexOf("\n");
        QMessageBox::critical(this, "Fields", message.left(index)) ;
    }
}

void AddVacation::on_cancel_clicked()
{
    this->close();
}
