#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include <QSql>
#include <QSqlQuery>
#include <qDebug>

extern QSqlQuery mainUser;

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->tempDB = QSqlDatabase::addDatabase("QPSQL", "tempConnection");
    this->tempDB.setHostName("52.31.46.192");
    this->tempDB.setDatabaseName("db_project");
    this->tempDB.setUserName("admin");
    this->tempDB.setPassword("1230");
    this->init();
}

Login::~Login()
{
    delete ui;
}

void Login::init()
{
    bool ok = this->tempDB.open();
    if(ok != true)
    {
        this->initFaild();
    }
    else
    {
        this->initSuccess();
    }
}

void Login::initFaild()
{
    ui->label_3->show();
    ui->pushButton_2->show();
    ui->label->hide();
    ui->label_2->hide();
    ui->label_4->hide();
    ui->lineEdit->hide();
    ui->lineEdit_2->hide();
    ui->pushButton->hide();
}

void Login::initSuccess()
{
    ui->label_3->hide();
    ui->pushButton_2->hide();
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
    QSqlQuery query(this->tempDB);
    query.prepare("SELECT * FROM persons WHERE login=:login and password=:password "
                  "and (access_type='manager' or access_type='hr');");
    query.bindValue(":login", login);
    query.bindValue(":password", password);
    query.exec();
    if(!query.isActive() || query.size() != 1)
    {
        ui->label_4->show();
    }
    else
    {
        query.first();
        mainUser = query;
        this->setupMainConnection();
    }
}

void Login::on_pushButton_2_clicked()
{
    this->init();
}

void Login::setupMainConnection()
{
    QSqlDatabase mainConnection = QSqlDatabase::addDatabase("QPSQL");
    mainConnection.setHostName("52.31.46.192");
    mainConnection.setDatabaseName("db_project");
    mainConnection.setUserName("admin");
    mainConnection.setPassword("1230");
    qDebug() << mainUser.value("login").toString();
    bool ok = mainConnection.open();
    if(ok != true)
    {
        this->initFaild();
    }
    else
    {
        MainWindow *m = new MainWindow();
        m->show();
        this->hide();
    }
}
