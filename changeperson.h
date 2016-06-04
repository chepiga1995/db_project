#ifndef CHANGEPERSON_H
#define CHANGEPERSON_H
#include <QSqlQuery>
#include <QStringList>
#include <QDialog>

namespace Ui {
class ChangePerson;
}

class ChangePerson : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePerson(QWidget *parent = 0, QString per = QString("0"));
    QString post;
    QString person;
    ~ChangePerson();
public slots:
    void receivePost(QString &, QStringList &);
signals:
    void personAdded();
private slots:
    void on_personChoosePost_clicked();

    void on_addPerson_clicked();

    void on_closePost_clicked();

private:
    Ui::ChangePerson *ui;
    void executeInsert(QSqlQuery &);
};



#endif // CHANGEPERSON_H
