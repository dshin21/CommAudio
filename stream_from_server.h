#pragma once


#include <QObject>

class StreamFromServer : public QObject
{
    Q_OBJECT
public:
    explicit StreamFromServer(QObject *parent = nullptr);

private:
    void stream_populate_combo_box();
signals:

public slots:

};

