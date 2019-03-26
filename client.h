#pragma once

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
    LocalPlayback *local_playback;
    StreamFromServer *stream_from_server;

    Client(QWidget *parent = nullptr);
    ~Client();

    //init ui
    void init_local_playback_ui();
    void init_stream_from_server_ui();

private:
    Ui::Client *ui;

signals:

public slots:
    void slot_local_playback_onclick_choose_song();
};
