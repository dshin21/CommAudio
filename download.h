#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QFile>
#include <QObject>
#include <QTcpSocket>

class DownLoad : public QObject
{
    Q_OBJECT
public:
    explicit DownLoad(QObject *parent = nullptr);

    QFile *download_file;
    bool started_download;
    QString file_name;
    int combo_box_idx;
    QTcpSocket *tcp_socket;


    void send_header();
    void set_socket(QTcpSocket *client_socket);


signals:

public slots:
    void slot_stream_onclick_download();
    void slot_combobox_changed(const QString &text);
    void slot_get_stream_combo_box_idx(int idx);
    void download();


};

#endif // DOWNLOAD_H
