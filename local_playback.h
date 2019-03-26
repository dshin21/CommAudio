#pragma once

#include <QObject>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QFile>

class LocalPlayback : public QObject
{
    Q_OBJECT
  public:
    QMediaPlayer *local_player;
    QString current_file;

    explicit LocalPlayback(QObject *parent = nullptr);
    ~LocalPlayback();

  public slots:
    void play();
    void pause();
    //change streamer into this style
};
