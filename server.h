#pragma once

#include <QWidget>
#include <QLabel>
#include <QAbstractItemView>
#include <QStringList>

#include <QStringListModel>
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
    QStringListModel *model;


signals:

public slots:
    void ItemClicked (QModelIndex& index );

};

