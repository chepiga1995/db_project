#ifndef ADDPERSON_H
#define ADDPERSON_H
#include <QSqlQuery>
#include <QStringList>
#include <QDialog>

namespace Ui {
class AddPerson;
}

class AddPerson : public QDialog
{
    Q_OBJECT

public:
    explicit AddPerson(QWidget *parent = 0);
    QStringList skills;
    QString post;
    ~AddPerson();

public slots:
    void receiveSkills(QStringList &, QStringList &);
    void receivePost(QString &, QStringList &);

private slots:
    void on_addPerson_clicked();

    void on_personChooseSkills_clicked();

    void on_personChoosePost_clicked();

    void on_closePost_clicked();
signals:
    void personAdded();
private:
    Ui::AddPerson *ui;
    void executeInsert(QSqlQuery &);
};

#endif // ADDPERSON_H
