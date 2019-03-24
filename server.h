#pragma once

#include <QWidget>
#include <QLabel>
#include "ui_server.h"

namespace Ui
{
class Server;
}

class Server : public QWidget
{
    Q_OBJECT
public:
    explicit Server(QWidget *parent = nullptr);
    ~Server();

private:
    Ui::Server *ui;

signals:

public slots:
};

