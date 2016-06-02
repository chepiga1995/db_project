#ifndef SELECTPOST_H
#define SELECTPOST_H
#include <QStringList>
#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class SelectPost;
}

class SelectPost : public QDialog
{
    Q_OBJECT

public:
    explicit SelectPost(QWidget *parent = 0);
    void init(QString &);
    ~SelectPost();
signals:
    void selectPost(QString &, QStringList &);
private slots:
    void on_select_clicked();

    void on_cancel_clicked();

private:
    Ui::SelectPost *ui;
    QSqlQueryModel *model;
};

#endif // SELECTPOST_H
