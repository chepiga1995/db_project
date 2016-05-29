#ifndef ADDPOST_H
#define ADDPOST_H

#include <QWidget>

namespace Ui {
class AddPost;
}

class AddPost : public QWidget
{
    Q_OBJECT

public:
    explicit AddPost(QWidget *parent = 0);
    ~AddPost();

private:
    Ui::AddPost *ui;
};

#endif // ADDPOST_H
