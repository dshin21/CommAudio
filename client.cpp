#include "client.h"

Client::Client(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::Client),
      local_playback(new LocalPlayback),
      stream_from_server(new StreamFromServer)
{
    ui->setupUi(this);

    init_local_playback_ui();
    init_stream_from_server_ui();
}

Client::~Client()
{
    delete ui;
}

void Client::init_local_playback_ui()
{
    connect(ui->btn_local_select_music_file, &QPushButton::clicked, this, &Client::slot_local_playback_onclick_choose_song);
    connect(ui->btn_local_play, &QPushButton::clicked, local_playback, &LocalPlayback::music_player_play);
    connect(ui->btn_local_pause, &QPushButton::clicked, local_playback, &LocalPlayback::music_player_pause);
}

void Client::init_stream_from_server_ui()
{

}

void Client::slot_local_playback_onclick_choose_song()
{
    local_playback->current_file = QFileDialog::getOpenFileName(this,
                                                              tr("Select a .wav file to listen"),
                                                              "./",
                                                                nullptr);
}


