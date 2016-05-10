#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "skills.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void initSkills();
    ~MainWindow();

public slots:
    void setSkillsModel(QSqlQueryModel *);
    void changeSortFieldSkills(int);
    void clearSkillFields();
    void showSkillsAddError();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();


private:
    Ui::MainWindow *ui;
    Skills *skills;
    void setupConnections();

};

#endif // MAINWINDOW_H
