#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include <QSqlDatabase>
#include <QtSql>
#include <QSqlQuery>
#include <QMessageBox>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
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

        MainWindow *m = new MainWindow();
        m->show();
        this->hide();

        QSqlQuery query(db);
        query.exec("select * from skills ");
        query.next();
        QMessageBox::information(this,"Information", query.value("description").toString()) ;

     }
}
