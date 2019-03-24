#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    music_player = new MusicPlayer;
    connect(ui->btn_select_file, &QPushButton::clicked, this, &MainWindow::onclick_btn_select_file);
    connect(ui->btn_save_file, &QPushButton::clicked, this, &MainWindow::onclick_btn_save_file);
    connect(ui->btn_play, &QPushButton::clicked, music_player, &MusicPlayer::music_player_play);
    connect(ui->btn_pause, &QPushButton::clicked, music_player, &MusicPlayer::music_player_pause);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onclick_btn_select_file()
{
    music_player->current_file = QFileDialog::getOpenFileName(this,
                                                              tr("Select a .wav file to listen"),
                                                              "./",
                                                              nullptr);
}

void MainWindow::onclick_btn_save_file()
{
    //TODO: save streaming music
}
