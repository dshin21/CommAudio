#include "voice.h"

Voice::Voice(QObject *parent) : QObject(parent)
{
    format.setChannelCount(2);
    format.setSampleRate(44100);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);
}

void Voice::set_server(QTcpServer *tcp_server)
{
    voice_server = voice_server;
}

void Voice::start_server()
{
    if (!voice_server->listen(QHostAddress::Any, 8484)) return;
    connect(voice_server, &QTcpServer::newConnection, this, &Voice::incoming_connection_request);

}

void Voice::incoming_connection_request()
{
    if (voice_socket == nullptr)
    {
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

void Voice::slot_voice_onclick_connect()
{
    voice_in = new QAudioInput(format, this);
    voice_socket_out = new QTcpSocket(this);

    voice_socket_out->connectToHost(QHostAddress(combo_box_text), 5050, QIODevice::WriteOnly);
    voice_in->start(voice_socket_out);
}

void Voice::slot_get_voice_combo_box_text(const QString &text)
{
    combo_box_text = text;
}


