#include "mainwindow.h"
#include <QApplication>
#include <QSqlQuery>
#include "login.h"

QSqlQuery mainUser;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login *login = new Login();
    login->show();
    return a.exec();
}
