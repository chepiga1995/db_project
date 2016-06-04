#ifndef PERSON_H
#define PERSON_H

#include <QSqlQueryModel>

#include <QtCore>
#include <QString>
class Person: public QObject {
    Q_OBJECT
public:
    ~Person();
    Person();
    QSqlQueryModel * model;
    void refresh();
    QString selected_id;
    void search(QString &, QString &);
    void sort(int, int);
    void personFired(QWidget *);
    void endVacation(QWidget *);
signals:
    void changePersonModel(QSqlQueryModel *);
    void refreshPersonPage();
private:
    QSqlQueryModel * getPersonModel();
    QString searchName;
    QString searchLastName;
    QString sortField;
    QString sortOrder;
};


#endif // PERSON_H
