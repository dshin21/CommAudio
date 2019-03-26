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
    //TODO: remove for prod.
    music_folder = QDir("C:/Users/danie/Music");

    //get only .wav files
    QStringList filter("*.wav");
    music_folder.setNameFilters(filter);

    file_info_list = music_folder.entryInfoList();

    QStringListModel *ui_playlist_model= new QStringListModel(this);
    QStringList ui_playlist;

    for (int i = 0; i < file_info_list.size(); ++i){
        ui_playlist << file_info_list[i].fileName();
        playlist_abs.append(file_info_list[i].absoluteFilePath());
        playlist_rel.append(file_info_list[i].fileName());
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
    clients.append(tcp_server->nextPendingConnection());
    connect(clients.last(), &QAbstractSocket::disconnected, clients.last(), &QObject::deleteLater);
    connect(clients.last(), &QIODevice::readyRead, this, &Server::slot_server_received_data_from_client);

    QByteArray header = create_initial_header();

    for (int i = 0; i < clients.size(); i++){
        clients[i]->write(qPrintable(header));
    }
}

QByteArray Server::create_initial_header()
{
    QString temp("I<");

    for(int i = 0; i < playlist_rel.size(); ++i)
        temp.append(playlist_rel[i]+ ";");

    temp.append("|");

    for (int i = 0; i < clients.size(); ++i)
        temp.append(clients[i]->peerAddress().toString() + ";");

    temp.append('>');

    return temp.toUtf8();
}

void Server::create_download_header(QFile *client_requested_stream_file, QTcpSocket *socket)
{
    while (!client_requested_stream_file->atEnd())
    {
        QByteArray temp = client_requested_stream_file->readLine();
        socket->write(temp);
    }

    client_requested_stream_file->close();
}

void Server::slot_server_received_data_from_client()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());

    if (socket !=  nullptr){
        QList<QString> received_data_string = QString(socket->readAll()).split(";");

        if(received_data_string[0] == "stream"){
            int file_idx = received_data_string[1].toInt();
            QFile *client_requested_stream_file = new QFile(playlist_abs[file_idx]);

            if (!client_requested_stream_file->isOpen() &&
                    !client_requested_stream_file->open(QIODevice::ReadOnly)) return;

            dataStreamList.append(new QDataStream(socket));

            QByteArray content = client_requested_stream_file->readAll();
            *dataStreamList.last() << content;
            client_requested_stream_file->close();
        }

        if(received_data_string[0] == "download"){
            int file_idx = received_data_string[1].toInt();
            QFile *client_requested_stream_file = new QFile(playlist_abs[file_idx]);
            if (!client_requested_stream_file->open(QIODevice::ReadOnly)) return;

            create_download_header(client_requested_stream_file, socket);
        }
    }
}
