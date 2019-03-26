#pragma once

#include <QAudioOutput>
#include <QObject>
#include <QTcpSocket>

class StreamFromServer : public QObject
{
    Q_OBJECT
public:
    explicit StreamFromServer(QObject *parent = nullptr);

    QAudioOutput *streamer;
    bool started_stream;
    bool data_ready;
    int combo_box_idx;
    QTcpSocket *tcp_socket;

    void start();
    void set_socket(QTcpSocket *client_socket);

private:

signals:
public slots:
    void play();
    void pause();
    void send_header();
    void slot_get_stream_combo_box_idx(int idx);
};

