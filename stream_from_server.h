#pragma once


#include <QObject>

class StreamFromServer : public QObject
{
    Q_OBJECT
public:
    explicit StreamFromServer(QObject *parent = nullptr);

signals:

public slots:
};

