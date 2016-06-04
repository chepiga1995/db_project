#ifndef ADDVACATION_H
#define ADDVACATION_H
#include <QStringList>
#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class AddVacation;
}

class AddVacation : public QDialog
{
    Q_OBJECT

public:
    explicit AddVacation(QWidget *parent = 0, QString per = QString("0"));
    QString person;
    ~AddVacation();
signals:
    void vacationAdded();
private slots:
    void on_addVacation_clicked();

    void on_cancel_clicked();

private:
    Ui::AddVacation *ui;
    void executeInsert(QSqlQuery &);
};

#endif // ADDVACATION_H
