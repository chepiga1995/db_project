#ifndef UPDATEPERSON_H
#define UPDATEPERSON_H
#include <QSqlQuery>
#include <QStringList>
#include <QDialog>

namespace Ui {
class UpdatePerson;
}

class UpdatePerson : public QDialog
{
    Q_OBJECT

public:
    explicit UpdatePerson(QWidget *parent = 0, QString per = QString("0"));
    QString person;
    ~UpdatePerson();

private slots:
    void on_addPerson_clicked();

    void on_closePost_clicked();

private:
    Ui::UpdatePerson *ui;
    void executeUpdate(QSqlQuery &);
};

#endif // UPDATEPERSON_H
