#include "voice.h"

Voice::Voice(QObject *parent) : QObject(parent)
{
    format.setChannelCount(2);
    format.setSampleRate(44100);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    voice_server = new QTcpServer(this);
    QList<QHostAddress> all_ip = QNetworkInterface::allAddresses();

    for (int i = 0; i < all_ip.size(); ++i)
    {
        if (all_ip[i].toIPv4Address())
        {
            voice_server_ip = all_ip.at(i).toString();
            break;
        }
    }
}

void Voice::set_server(QTcpServer *tcp_server)
{
    //    voice_server = voice_server;


}

void Voice::slot_get_voice_combo_box_text(const QString &text)
{
    combo_box_text = text;
}

void Voice::slot_voice_onclick_connect()
{
    start_server();
    voice_in = new QAudioInput(format, this);
    voice_socket_out = new QTcpSocket(this);

    voice_socket_out->connectToHost(QHostAddress(combo_box_text), 5151, QIODevice::WriteOnly);
    voice_in->start(voice_socket_out);
}


void Voice::start_server()
{
    if (!voice_server->listen(QHostAddress::Any, 5151))
        return;
    connect(voice_server, &QTcpServer::newConnection, this, &Voice::incoming_connection_request);
    qDebug("The client server is running on\n\nIP: %s\nport: %d\n\n", qPrintable(voice_server_ip), voice_server->serverPort());
}

void Voice::incoming_connection_request()
{
    if (voice_socket == nullptr)
    {
        qDebug()<<"new connection";

        voice_socket = voice_server->nextPendingConnection();
        voice_out = new QAudioOutput(format, this);
        connect(voice_socket, &QIODevice::readyRead, this, &Voice::ready_voice);
    }
}

void Voice::ready_voice()
{
    if ((voice_out->state() == QAudio::IdleState || voice_out->state() == QAudio::StoppedState))
    {
        voice_out->start(voice_socket);
    }
}





