#ifndef POST_H
#define POST_H
#include <QSqlQueryModel>

#include <QtCore>
#include <QObject>
class Post: public QObject {
    Q_OBJECT
public:
    ~Post();
    void refresh();
    void search(QString &);
signals:
    void changePostModel(QSqlQueryModel *);
private:
    QSqlQueryModel * getPostModel();
};

#endif // POST_H
