#include "post.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <qDebug>
#include <QMessageBox>
#include <QSqlError>

Post::Post()
{
    searchName = "";
    sortField = "name";
    sortOrder = "DESC";
}

Post::~Post()
{

}

QSqlQueryModel * Post::getPostModel(){
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM complete_posts WHERE name ~ :name ORDER BY " + sortField + " " + sortOrder);
    query.bindValue(":name", searchName);
    query.exec();

    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, tr("Назва"));
    model->setHeaderData(2, Qt::Horizontal, tr("Опис"));
    model->setHeaderData(3, Qt::Horizontal, tr("Мін. зарплата"));
    model->setHeaderData(4, Qt::Horizontal, tr("Мак. зарплата"));
    model->setHeaderData(5, Qt::Horizontal, tr("Кількість місць"));
    model->setHeaderData(6, Qt::Horizontal, tr("Занято місць"));

    return model;
}

void Post::refresh(){
    QSqlQueryModel *model = this->getPostModel();
    emit changePostModel(model);
}

void Post::search(QString & name){
    searchName = name;
    emit refreshPostPage();
}

void Post::sort(int field, int order){
    QString fieldIndex[7] = {"post_id", "name", "description", "min_salary", "max_salary", "amount", "work"};
    QString sortIndex[2] = {"ASC", "DESC"};
    sortField = fieldIndex[field];
    sortOrder = sortIndex[order];
    emit refreshPostPage();
}

void Post::changeAmount(QString &amount, QWidget *ui){
    QSqlQuery query;
    query.prepare("SELECT update_post(:amount, :post_id)");
    query.bindValue(":amount", amount);
    query.bindValue(":post_id", selected_id);
    query.exec();
    if(query.isActive()) {
        QMessageBox::information(ui, "Fields", "Кількість змінена");
        emit refreshPostPage();
    } else {
        QString message = (query.lastError()).databaseText();
        int index = message.indexOf("\n");
        QMessageBox::critical(ui, "Fields", message.left(index)) ;
    }
}

void Post::closePost(QWidget *ui){
    QSqlQuery query;
    query.prepare("SELECT close_post(:post_id)");
    query.bindValue(":post_id", selected_id);
    query.exec();
    if(query.isActive()) {
        QMessageBox::information(ui, "Fields", "Посада закрита");
        emit refreshPostPage();
    } else {
        QString message = (query.lastError()).databaseText();
        int index = message.indexOf("\n");
        QMessageBox::critical(ui, "Fields", message.left(index)) ;
    }
}
