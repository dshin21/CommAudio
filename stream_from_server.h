#pragma once

#include <QAudioOutput>
#include <QObject>

class StreamFromServer : public QObject
{
    Q_OBJECT
public:
    explicit StreamFromServer(QObject *parent = nullptr);

    QAudioOutput *audio;
    bool start_stream;

private:

signals:

public slots:

};

