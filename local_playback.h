#pragma once

#include <QObject>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QFile>

class LocalPlayback : public QObject
{
    Q_OBJECT
  public:
    QMediaPlayer *music_player;
    QString current_file;

    explicit LocalPlayback(QObject *parent = nullptr);
    ~LocalPlayback();

  public slots:
    void music_player_play();
    void music_player_pause();
};
