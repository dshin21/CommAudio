#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init_main_ui();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_main_ui()
{
    connect(ui->btn_client, &QPushButton::clicked, this, [&](){
        client = new Client;
        client->show();
        this->hide();
    });

    connect(ui->btn_server, &QPushButton::clicked, this, [&](){
        server = new Server;
        server->show();
        this->hide();
    });
}



