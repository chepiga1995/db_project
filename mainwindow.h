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
    void refresh();
    ~MainWindow();

public slots:
    void setSkillsModel(QSqlQueryModel *);

private:
    Ui::MainWindow *ui;
    Skills *skills;
    void setupConnections();

};

#endif // MAINWINDOW_H
