#include "server.h"

Server::Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);

}

Server::~Server()
{
    delete ui;
}
