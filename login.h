#ifndef LOGIN_H
#define LOGIN_H
#include <QSqlDatabase>
#include <QDialog>

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
    void init();
    void initFaild();
    void initSuccess();
    void setupMainConnection();
    QSqlDatabase tempDB;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
