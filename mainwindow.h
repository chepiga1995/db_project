#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "skill.h"
#include "person.h"
#include "vacation_type.h"
#include "post.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, QString access = QString("none"));
    void initSkill();
    void initVacationType();
    void initPost();
    void initPerson();
    ~MainWindow();

public slots:
//Skill
    void setSkillModel(QSqlQueryModel *);
    void changeSortFieldSkill(int);
    void clearSkillFields();
    void showSkillAddError();
//vacation type
    void setVacationTypeModel(QSqlQueryModel *);
    void changeSortFieldVacationType(int);
    void clearVacationTypeFields();
    void showVacationTypeAddError();
//post
    void postSelectedChanged(const QItemSelection &, const QItemSelection &);
    void refreshPostPage();
    void changeSortFieldPost(int);
    void setPostModel(QSqlQueryModel *);
//person
    void personSelectedChanged(const QItemSelection &, const QItemSelection &);
    void refreshPersonPage();
    void changeSortFieldPerson(int);
    void setPersonModel(QSqlQueryModel *);
private slots:
    void on_addSkill_clicked();

    void on_findSkill_clicked();

    void on_addVacationType_clicked();

    void on_findVacationType_clicked();

    void on_addPerson_clicked();

    void on_addPost_clicked();

    void on_postSearch_clicked();

    void on_postApplyNewAmount_clicked();

    void on_postClose_clicked();

    void on_personGenerateReport_clicked();

    void on_personSearch_clicked();

    void on_personChangePost_clicked();

    void on_personFired_clicked();

    void on_personUpdate_clicked();

    void on_personStartVacation_clicked();

    void on_personEndVacation_clicked();

private:
    Ui::MainWindow *ui;
    Skill *skill;
    Post *post;
    Person *person;
    VacationType *vacation_type;
    void setupConnections();

};

#endif // MAINWINDOW_H
