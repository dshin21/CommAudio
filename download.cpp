#include "download.h"

DownLoad::DownLoad(QObject *parent)
    : QObject(parent),
      started_download(false)
{

}

void DownLoad::slot_stream_onclick_download()
{
    send_header();
    started_download = true;
}

void DownLoad::slot_combobox_changed(const QString &text)
{
    file_name = text;
}

void DownLoad::send_header()
{
    QString header = "download;";
    header.append(QString::number(combo_box_idx));
    tcp_socket->write(qPrintable(header));
}

void DownLoad::slot_get_stream_combo_box_idx(int idx)
{
    combo_box_idx = idx;

    if(started_download){
        started_download = false;
        tcp_socket->readAll();
    }
}

void DownLoad::set_socket(QTcpSocket *client_socket)
{
    tcp_socket = client_socket;
}

void DownLoad::download()
{
    if(started_download){
        QDir folder = QFileDialog::getExistingDirectory(nullptr, ("Please Select a Folder"), QDir::currentPath());
        download_file = new QFile(folder.absolutePath() + "//" + file_name);

        if (!download_file->isOpen())
            if (!download_file->open(QIODevice::WriteOnly | QIODevice::Append))
                return;

        QByteArray data = tcp_socket->readAll();
        download_file->write(data);
        download_file->close();
    }
}
