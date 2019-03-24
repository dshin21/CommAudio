#include "server.h"

Server::Server(QWidget *parent) : QWidget(parent)
{
    ui->setupUi(this);

}

Server::~Server()
{
    delete ui;
}
