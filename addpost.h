#ifndef ADDPOST_H
#define ADDPOST_H
#include <QSqlQuery>

#include <QDialog>

namespace Ui {
class AddPost;
}

class AddPost : public QDialog
{
    Q_OBJECT

public:
    explicit AddPost(QWidget *parent = 0);
    QStringList skills;
    ~AddPost();

private slots:
    void on_addPost_clicked();


private:
    Ui::AddPost *ui;
    void executeInsert(QSqlQuery &);
};

#endif // ADDPOST_H
