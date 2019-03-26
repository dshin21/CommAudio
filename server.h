#pragma once

#include <QWidget>
#include <QLabel>
#include <QAbstractItemView>
#include <QStringList>
#include <QFileDialog>
#include <QFileInfoList>
#include <QStringListModel>
#include <QTcpServer>
#include <QtNetwork>


#include "ui_server.h"

#include <QDebug>

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
    QTcpServer *tcp_server;
    QFileInfoList file_info_list;
    QList<QString> playlist_abs;
    QList<QString> playlist_rel;
    QList<QTcpSocket *> clients;
    QList<QDataStream *> dataStreamList;


    QByteArray create_initial_header();
    void create_download_header(QFile *client_requested_stream_file, QTcpSocket *socket);

signals:

public slots:
    void slot_server_onclick_select_music_folder();
    void slot_server_onclick_start_server();
    void slot_server_add_new_client();
    void slot_server_received_data_from_client();

};
