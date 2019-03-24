#include "mainwindow.h"
#include "musicplayer.h"
#include <QDebug>

MusicPlayer::MusicPlayer(QObject *parent)
    : QObject(parent), music_player(new QMediaPlayer)
{
}

MusicPlayer::~MusicPlayer()
{
    delete music_player;
}

void MusicPlayer::music_player_play()
{
    QFile file_to_play(current_file);

    if (music_player->state() == QMediaPlayer::StoppedState)
    {
        if (file_to_play.open(QIODevice::ReadOnly))
        {
            music_player->setMedia(QUrl::fromLocalFile(current_file));
            music_player->play();
        }
        else
        {
            qDebug() << "Error: File not able to be played";
        }
    }
    else
    {
        music_player->play();
    }
}

void MusicPlayer::music_player_pause()
{
    music_player->pause();
}

//TODO: add volume control functionality
//TODO: add playback functionality (faster/slower)
