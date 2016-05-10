#ifndef SKILLS_H
#define SKILLS_H
#include <QSqlQueryModel>

#include <QtCore>

class Skills: public QObject {
    Q_OBJECT
public:
    Skills();
    ~Skills();
    void refresh();
    void search(QString &);
    void sort(int, int);
    void addSkill(QString &, QString &);
signals:
    void changeSkillsModel(QSqlQueryModel *);
    void clearNewSkillFields();
    void raiseAddSkillError();
private:
    QSqlQueryModel * getSkillsModel();
    QString searchName;
    QString sortField;
    QString sortOrder;
};

#endif // SKILLS_H
