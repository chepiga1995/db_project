#ifndef LOGIN_H
#define LOGIN_H
#include <QSqlDatabase>
#include <QDialog>
#include <QString>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
private:
    void initSuccess();
private slots:
    void on_pushButton_clicked();


private:
    Ui::Login *ui;
    void loadUser(QString);
};

#endif // LOGIN_H
