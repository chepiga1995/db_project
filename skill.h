#ifndef SKILLS_H
#define SKILLS_H
#include <QSqlQueryModel>

#include <QtCore>

class Skill: public QObject {
    Q_OBJECT
public:
    Skill();
    ~Skill();
    void refresh();
    void search(QString &);
    void sort(int, int);
    void addSkill(QString &, QString &, QWidget *);
signals:
    void changeSkillModel(QSqlQueryModel *);
    void clearNewSkillFields();
private:
    QSqlQueryModel * getSkillModel();
    QString searchName;
    QString sortField;
    QString sortOrder;
};

#endif // SKILLS_H
