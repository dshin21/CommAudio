#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QFile>

class MusicPlayer : public QObject
{
    Q_OBJECT
  public:
    QMediaPlayer *music_player;
    QString current_file;

    explicit MusicPlayer(QObject *parent = nullptr);
    ~MusicPlayer();

  public slots:
    void music_player_play();
    void music_player_pause();
};

#endif // MUSICPLAYER_H
