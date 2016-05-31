#ifndef SELECTSKILL_H
#define SELECTSKILL_H
#include <QStringList>
#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class SelectSkill;
}

class SelectSkill : public QDialog
{
    Q_OBJECT

public:
    explicit SelectSkill(QWidget *parent = 0);
    void init(QStringList &);
    ~SelectSkill();
signals:
    void selectSkills(QStringList &, QStringList &);
private slots:
    void on_select_clicked();

    void on_cancel_clicked();

private:
    Ui::SelectSkill *ui;
    QSqlQueryModel *model;
};

#endif // SELECTSKILL_H
