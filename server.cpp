#include "server.h"

#include <QStringListModel>

#include <QAbstractItemView>
#include <QDebug>


Server::Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);

    QStringListModel *model;

    // Create model
    model = new QStringListModel(this);

    // Make data
    QStringList List;
    List << "Clair de Lune" << "Reverie" << "Prelude";

    // Populate our model
    model->setStringList(List);

    // Glue model and view together
    ui->server_playlist->setModel(model);
    ui->comboBox->setModel(model);

}

Server::~Server()
{
    delete ui;
}

void Server::ItemClicked(QModelIndex &index)
{
    qDebug()<< index;
}
