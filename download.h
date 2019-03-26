#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QFile>
#include <QObject>
#include <QTcpSocket>
#include <QDir>
#include <QFileDialog>

class DownLoad : public QObject
{
    Q_OBJECT
public:
    explicit DownLoad(QObject *parent = nullptr);

    QTcpSocket *tcp_socket;
    QFile *download_file;
    QString file_name;
    int combo_box_idx;
    bool started_download;

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
