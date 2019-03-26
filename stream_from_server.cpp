#include "stream_from_server.h"

#include <QDebug>

StreamFromServer::StreamFromServer(QObject *parent)
    : QObject(parent)
{
    QAudioFormat format;
    format.setSampleRate(96000);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

//    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
//    if (!info.isFormatSupported(format))
//    {
//        qWarning() << "Default format not supported - trying to use nearest";
//        format = info.nearestFormat(format);
//    }

    audio = new QAudioOutput(format, this);
}
