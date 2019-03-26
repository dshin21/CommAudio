#include "client.h"

#include <QNetworkInterface>

Client::Client(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::Client),
      local_playback(new LocalPlayback),
      stream_from_server(new StreamFromServer),
      download(new DownLoad),
      voice(new Voice)
{
    ui->setupUi(this);
    tcp_socket = new QTcpSocket(this);


    stream_from_server->set_socket(tcp_socket);
    download->set_socket(tcp_socket);
    voice->set_socket(tcp_socket);

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
}


void Client::init_local_playback_ui()
{
    connect(ui->btn_local_select_music_file, &QPushButton::clicked, this, &Client::slot_local_playback_onclick_choose_song);
    connect(ui->btn_local_play, &QPushButton::clicked, local_playback, &LocalPlayback::play);
    connect(ui->btn_local_pause, &QPushButton::clicked, local_playback, &LocalPlayback::pause);
}

void Client::init_stream_from_server_ui(QList<QString> received_playlist)
{
    connect(ui->btn_stream_play, &QPushButton::clicked, stream_from_server, &StreamFromServer::play);
    connect(ui->btn_stream_pause, &QPushButton::clicked, stream_from_server, &StreamFromServer::pause);
    connect(ui->stream_combo_box, QOverload<int>::of(&QComboBox::currentIndexChanged), stream_from_server, &StreamFromServer::slot_get_stream_combo_box_idx);
    connect(ui->toolBox, &QToolBox::currentChanged, stream_from_server, &StreamFromServer::slot_tab_idx_changed);

    for(int i = 0; i < received_playlist.size(); ++i)
        ui->stream_combo_box->addItem(received_playlist[i]);
}

void Client::init_download_ui(QList<QString> received_playlist)
{
    connect(ui->btn_download, &QPushButton::clicked, download, &DownLoad::slot_stream_onclick_download);
    connect(ui->download_combo_box, &QComboBox::currentTextChanged, download, &DownLoad::slot_combobox_changed);
    connect(ui->download_combo_box, QOverload<int>::of(&QComboBox::currentIndexChanged), download, &DownLoad::slot_get_stream_combo_box_idx);

    for(int i = 0; i < received_playlist.size(); ++i)
        ui->download_combo_box->addItem(received_playlist[i]);
}

void Client::init_voice_ui(QList<QString> received_ip_list)
{
    connect(ui->voice_combo_box, &QComboBox::currentTextChanged, voice, &Voice::slot_get_voice_combo_box_text);
    connect(ui->btn_voice_connect, &QPushButton::clicked, voice, &Voice::slot_voice_onclick_connect);
    connect(ui->toolBox, &QToolBox::currentChanged, voice, &Voice::slot_tab_idx_changed);

    //TODO:
    //    connect(ui->btn_voice_disconnect, &QPushButton::clicked, voice, &Voice::slot_voice_onclick_disconnect);
    qDebug() << received_ip_list;
    for(int i = 0; i < received_ip_list.size(); ++i)
        ui->voice_combo_box->addItem(received_ip_list[i]);
}

void Client::slot_local_playback_onclick_choose_song()
{
    local_playback->current_file = QFileDialog::getOpenFileName(this,
                                                                tr("Select a .wav file to listen"),
                                                                "./",
                                                                nullptr);
}

void Client::slot_client_connect_to_server()
{
    connect(tcp_socket, &QIODevice::readyRead, this, &Client::slot_client_received_data_from_server);
    connect(tcp_socket, &QIODevice::readyRead, download, &DownLoad::download);

    QString server_ip = ui->lineEdit_client_ip->text();
    quint16 server_port = quint16(ui->lineEdit_client_port->text().toShort());

    tcp_socket->connectToHost(QHostAddress(server_ip), server_port);
}

void Client::slot_client_received_data_from_server()
{
    QString received_data_string = tcp_socket->peek(1);
    if(received_data_string != '\u0002'){
        qDebug() << received_data_string;
        if(received_data_string == 'I'){
            //initial connect data
            received_data_string = QString(tcp_socket->readAll());
            QList<QString> received_data = remove_header_info(received_data_string);
            QList<QString> received_playlist = received_data[0].split(";");
            QList<QString> received_ip_list = received_data[1].split(";");

            init_stream_from_server_ui(received_playlist);
            init_download_ui(received_playlist);
            init_voice_ui(received_ip_list);
        }else if(received_data_string == 'V'){
            received_data_string = QString(tcp_socket->readAll());
            QList<QString> received_ip_list = received_data_string.split(":");
            qDebug() << received_ip_list[received_ip_list.size()-1];
        }
    }
}

QList<QString> Client::remove_header_info(QString received_data_string)
{
    QString temp = received_data_string;
    temp.remove(0,2);
    temp.remove(temp.size() - 2, 2);

    QList<QString> result = temp.split("|");
    result[0].remove(result[0].length()-1, 1);

    return result;
}

