#include "server.h"

#include <QNetworkInterface>

Server::Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);

    connect(ui->btn_select_music_folder, &QPushButton::clicked, this, &Server::slot_server_onclick_select_music_folder);
    connect(ui->btn_server_start_server, &QPushButton::clicked, this, &Server::slot_server_onclick_start_server);
}

Server::~Server()
{
    delete ui;
}

void Server::slot_server_onclick_select_music_folder()
{
    //get music folder
    QDir music_folder = QDir(QFileDialog::getExistingDirectory(nullptr,
                                                               "Select a Music Foler",
                                                               QDir::currentPath()));
    //get only .wav files
    QStringList filter("*.wav");
    music_folder.setNameFilters(filter);

    file_info_list = music_folder.entryInfoList();

    QStringListModel *ui_playlist_model= new QStringListModel(this);
    QStringList ui_playlist;

    for (int i = 0; i < file_info_list.size(); ++i){
        ui_playlist << file_info_list[i].fileName();
        playlist.append(file_info_list[i].absoluteFilePath());
    }


    ui_playlist_model->setStringList(ui_playlist);

    // bind combobox and listview to the playlist
    ui->server_playlist->setModel(ui_playlist_model);
    ui->comboBox->setModel(ui_playlist_model);
}

void Server::slot_server_onclick_start_server()
{
    tcp_server = new QTcpServer(this);

    if(!tcp_server->listen(QHostAddress::Any, 5000)){
        //TODO: make a generic dialog class
        qDebug() << "Server Error";
    }else{
        QString server_ip;
        QList<QHostAddress> all_ip = QNetworkInterface::allAddresses();

        for (int i = 0; i < all_ip.size(); ++i)
        {
            if (all_ip[i].toIPv4Address())
            {
                server_ip = all_ip.at(i).toString();
                break;
            }
        }

        ui->label_server_ip->setText(ui->label_server_ip->text().append(server_ip));
        ui->label_server_port->setText(ui->label_server_port->text().append(QString::number(tcp_server->serverPort())));

        connect(tcp_server, &QTcpServer::newConnection, this, &Server::slot_server_add_new_client);
    }
}

void Server::slot_server_add_new_client()
{
    qDebug() << "hihi";

    clients.append(tcp_server->nextPendingConnection());
    connect(clients.last(), &QAbstractSocket::disconnected, clients.last(), &QObject::deleteLater);
    connect(clients.last(), &QIODevice::readyRead, this, &Server::slot_server_received_data_from_client);

    QByteArray header = create_header();

    for (int i = 0; i < clients.size(); i++)
        clients[i]->write(qPrintable(header));

    qDebug() << "server:" << header;
}

QByteArray Server::create_header()
{
    QString temp("<");

    for(int i = 0; i < playlist.size(); ++i)
        temp.append(playlist[i] + ";");

    temp.append("|");

    for (int i = 0; i < clients.size(); ++i)
        temp.append(clients[i]->peerAddress().toString() + ";");

    temp.append('>');

    return temp.toUtf8();
}

void Server::slot_server_received_data_from_client()
{
    QTcpSocket *socket = new QTcpSocket(sender());

    if (socket ==  nullptr)
        return;

    QString received_data = socket->readAll();

    qDebug() << "data: " << received_data;
    if (received_data[0] == '2')
    {
        received_data = received_data.remove(0, 1);
        for (int i = 0; i < file_info_list.size(); i++)
        {
            if (file_info_list[i].absoluteFilePath().contains(received_data))
            {
                QFile *streamFile = new QFile(file_info_list[i].absoluteFilePath());
                if (!streamFile->isOpen())
                {
                    if (!streamFile->open(QIODevice::ReadOnly))
                    {
                        return;
                    }
                }
                dataStreamList.append(new QDataStream(socket));

                QByteArray content = streamFile->readAll();
                *dataStreamList.last() << content;
                streamFile->close();
                break;
            }
        }
    }
}
