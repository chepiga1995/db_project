#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include <QSql>
#include <QSqlQuery>


extern QSqlQuery mainUser;

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->initSuccess();
}

Login::~Login()
{
    delete ui;
}


void Login::initSuccess()
{
    ui->label->show();
    ui->label_2->show();
    ui->label_4->hide();
    ui->lineEdit->show();
    ui->lineEdit_2->show();
    ui->pushButton->show();
}

void Login::on_pushButton_clicked()
{
    ui->label_4->hide();
    QString login = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    QSqlDatabase mainConnection = QSqlDatabase::addDatabase("QPSQL");
    mainConnection.setHostName("52.31.46.192");
    mainConnection.setDatabaseName("db_project");
    mainConnection.setUserName(login);
    mainConnection.setPassword(password);
    bool ok = mainConnection.open();
    if(ok != true)
    {
        ui->label_4->show();
    }
    else
    {
        MainWindow *mainWindow = new MainWindow();
        mainWindow->show();

        this->hide();
    }
}



