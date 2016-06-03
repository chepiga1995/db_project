#ifndef POST_H
#define POST_H
#include <QSqlQueryModel>

#include <QtCore>
#include <QString>
class Post: public QObject {
    Q_OBJECT
public:
    ~Post();
    Post();
    void refresh();
    QString selected_id;
    void search(QString &);
    void sort(int, int);
signals:
    void changePostModel(QSqlQueryModel *);
    void refreshPostPage();
private:
    QSqlQueryModel * getPostModel();
    QString searchName;
    QString sortField;
    QString sortOrder;
};

#endif // POST_H
