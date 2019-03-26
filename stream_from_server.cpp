#include "client.h"
#include "stream_from_server.h"

#include <QDebug>

StreamFromServer::StreamFromServer(QObject *parent)
    : QObject(parent),
      started_stream(false)
{
    QAudioFormat format;
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    //deafult
    format.setSampleRate(96000);
    format.setChannelCount(1);
    format.setSampleSize(16);

    streamer = new QAudioOutput(format, this);
}

void StreamFromServer::start()
{
//    if ((streamer->state() == QAudio::StoppedState ||
//         streamer->state() == QAudio::IdleState)){
//        streamer->start(tcp_socket);
//        pause();
//    }
}

void StreamFromServer::set_socket(QTcpSocket *client_socket)
{
    tcp_socket = client_socket;
}

void StreamFromServer::play()
{
//    if(!started_stream){
//        send_header();
//    }

//    if(data_ready && !started_stream){
        streamer->start(tcp_socket);
        started_stream = true;
//    }

//    if(started_stream){
//        streamer->resume();
//    }
}

void StreamFromServer::pause()
{
    if (started_stream)
        streamer->suspend();
}

void StreamFromServer::send_header()
{
    QString header = "stream;";
    header.append(QString::number(combo_box_idx));
    tcp_socket->write(qPrintable(header));
}

void StreamFromServer::slot_get_stream_combo_box_idx(int idx)
{
    combo_box_idx = idx;
    send_header();

    //    if(started_stream){
    //        streamer->stop();
    //        streamer->reset();
    //        tcp_socket->flush();
    //        started_stream = false;
    //    }
}
