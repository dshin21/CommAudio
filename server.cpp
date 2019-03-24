#include "server.h"

Server::Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);

    QLabel *label = new QLabel(this);
    label->setText("1. test");
    label->setText(label->text().append("\n\n2. hi"));

    ui->scrollArea->setWidget(label);
}

Server::~Server()
{
    delete ui;
}
