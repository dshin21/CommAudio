#include "client.h"

#include <QNetworkInterface>

Client::Client(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::Client),
      tcp_socket(new QTcpSocket(this)),
      local_playback(new LocalPlayback),
      stream_from_server(new StreamFromServer)
{
    ui->setupUi(this);

    init_client_ui();
}

Client::~Client()
{
    delete ui;
}

void Client::init_client_ui()
{
    connect(ui->btn_client_go, &QPushButton::clicked, this, &Client::slot_client_connect_to_server);

    init_local_playback_ui();
    init_stream_from_server_ui();
}

void Client::slot_client_connect_to_server()
{
    connect(tcp_socket, &QIODevice::readyRead, this, &Client::slot_client_received_data_from_server);
    qDebug() << "hi";
    QString server_ip = ui->lineEdit_client_ip->text();
    quint16 server_port = quint16(ui->lineEdit_client_port->text().toShort());

    tcp_socket->connectToHost(QHostAddress(server_ip), server_port);

//    QString client_ip;
//    QList<QHostAddress> all_ip = QNetworkInterface::allAddresses();

//    for (int i = 0; i < all_ip.size(); ++i)
//    {
//        if (all_ip[i].toIPv4Address())
//        {
//            client_ip = all_ip.at(i).toString();
//            break;
//        }
//    }
}

void Client::init_local_playback_ui()
{
    connect(ui->btn_local_select_music_file, &QPushButton::clicked, this, &Client::slot_local_playback_onclick_choose_song);
    connect(ui->btn_local_play, &QPushButton::clicked, local_playback, &LocalPlayback::music_player_play);
    connect(ui->btn_local_pause, &QPushButton::clicked, local_playback, &LocalPlayback::music_player_pause);
}

void Client::slot_local_playback_onclick_choose_song()
{
    local_playback->current_file = QFileDialog::getOpenFileName(this,
                                                              tr("Select a .wav file to listen"),
                                                              "./",
                                                                nullptr);
}

void Client::init_stream_from_server_ui()
{

}

void Client::slot_client_received_data_from_server()
{
    QByteArray received_data = tcp_socket->readAll();

}


