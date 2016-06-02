#include "post.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <qDebug>


Post::~Post()
{

}

QSqlQueryModel * Post::getPostModel(){
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM posts");
    query.exec();

    model->setQuery(query);

    return model;
}

void Post::refresh(){
    QSqlQueryModel *model = this->getPostModel();
    emit changePostModel(model);
}

void Post::search(QString & name){

}
