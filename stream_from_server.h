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
    QAudioFormat format;
    QTcpSocket *tcp_socket;

    bool started_stream;
    bool data_ready;
    int combo_box_idx;

    void set_socket(QTcpSocket *client_socket);

private:

signals:
public slots:
    void play();
    void pause();
    void send_header();
    void slot_get_stream_combo_box_idx(int idx);
    void slot_tab_idx_changed(int idx);
};

