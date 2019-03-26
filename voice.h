#ifndef VOICE_H
#define VOICE_H

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

    QTcpServer *voice_server = nullptr;
    QTcpSocket *voice_socket = nullptr;
    QTcpSocket *voice_socket_out = nullptr;
    QString voice_server_ip;
    QAudioFormat format;
    QAudioInput *voice_in;
    QAudioOutput *voice_out;
    QString combo_box_text;


    void set_server(QTcpServer *tcp_server);

signals:

public slots:
    void start_server();
    void incoming_connection_request();
    void ready_voice();
    void slot_voice_onclick_connect();
    void slot_get_voice_combo_box_text(const QString &text); //TODO: refact all these to get combo_box_idx
};

#endif // VOICE_H
