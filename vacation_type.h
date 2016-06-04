#ifndef VACATION_TYPE_H
#define VACATION_TYPE_H
#include <QSqlQueryModel>

#include <QtCore>

class VacationType: public QObject {
    Q_OBJECT
public:
    VacationType();
    ~VacationType();
    void refresh();
    void search(QString &);
    void sort(int, int);
    void addVacationType(QString &, QString &, QWidget *);
signals:
    void changeVacationTypeModel(QSqlQueryModel *);
    void clearNewVacationTypeFields();
private:
    QSqlQueryModel * getVacationTypeModel();
    QString searchName;
    QString sortField;
    QString sortOrder;
};

#endif // VACATION_TYPE_H
