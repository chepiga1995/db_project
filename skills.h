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
signals:
    void changeSkillsModel(QSqlQueryModel *);
private:
    QSqlQueryModel * getSkillsModel();

};

#endif // SKILLS_H
