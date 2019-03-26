#include "mainwindow.h"
#include "local_playback.h"
#include <QDebug>

LocalPlayback::LocalPlayback(QObject *parent)
    : QObject(parent),
      local_player(new QMediaPlayer)
{

}

LocalPlayback::~LocalPlayback()
{
    delete local_player;
}

void LocalPlayback::play()
{
    QFile file_to_play(current_file);

    if (local_player->state() == QMediaPlayer::StoppedState)
    {
        if (file_to_play.open(QIODevice::ReadOnly))
        {
            local_player->setMedia(QUrl::fromLocalFile(current_file));
            local_player->play();
        }
        else
        {
            qDebug() << "Error: File not able to be played";
        }
    }
    else
    {
        local_player->play();
    }
}

void LocalPlayback::pause()
{
    local_player->pause();
}

//TODO: add volume control functionality
//TODO: add playback functionality (faster/slower)
