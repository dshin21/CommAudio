#pragma once

#include <QObject>
#include <QtNetwork>
#include <QAudioInput>
#include <QAudioOutput>
#include <QTcpServer>

class Voice : public QObject
{
    Q_OBJECT
public:
    explicit Voice(QObject *parent = nullptr);

    QTcpSocket *tcp_socket;

    QTcpServer *voice_server = nullptr;
    QTcpSocket *voice_socket = nullptr;
    QTcpSocket *voice_socket_out = nullptr;

    QAudioFormat format;
    QAudioInput *voice_in;
    QAudioOutput *voice_out;

    QString voice_server_ip;
    QString combo_box_text;

    void send_header();
    void set_socket(QTcpSocket *client_socket);


signals:

public slots:
    void start_server();
    void incoming_connection_request();
    void ready_voice();
    void slot_voice_onclick_connect();
    void slot_voice_onclick_disconnect();
    void slot_get_voice_combo_box_text(const QString &text); //TODO: refact all these to get combo_box_idx
    void slot_tab_idx_changed(int idx);

};
