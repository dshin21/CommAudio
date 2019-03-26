#pragma once

#include <QTcpSocket>
#include <QWidget>

#include "local_playback.h"
#include "stream_from_server.h"
#include "ui_client.h"

namespace Ui
{
class Client;
}

class Client : public QWidget
{
    Q_OBJECT
public:
    QTcpSocket *tcp_socket;

    LocalPlayback *local_playback;
    StreamFromServer *stream_from_server;

    Client(QWidget *parent = nullptr);
    ~Client();

    //init ui
    void init_client_ui();
    void init_local_playback_ui();
    void init_stream_from_server_ui();

private:
    Ui::Client *ui;

signals:

public slots:
    void slot_client_connect_to_server();
    void slot_local_playback_onclick_choose_song();
    void slot_client_received_data_from_server();
};
