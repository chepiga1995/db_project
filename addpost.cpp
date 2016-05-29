#include "addpost.h"
#include "ui_addpost.h"

AddPost::AddPost(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddPost)
{
    ui->setupUi(this);
}

AddPost::~AddPost()
{
    delete ui;
}
