#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QtSql>
#include <QSqlQuery>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_clicked()
{
    QString login = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
            db.setHostName("52.31.46.192");
            db.setDatabaseName("db_project");
            db.setUserName(login);
            db.setPassword(password);

     bool ok = db.open();
     if(ok != true)
     {
         QMessageBox::information(this,"Connection","Connection Failed!") ;
     }
     else
     {
         QMessageBox::information(this,"Connection","Connection OK!") ;


        QSqlQuery query(db);
        query.exec("select * from skills ");
        query.next();
        QMessageBox::information(this,"Information", query.value("description").toString()) ;

     }
}
