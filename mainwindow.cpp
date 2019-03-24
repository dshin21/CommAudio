#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    local_playback = new LocalPlayback;
    init_local_playback_ui();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_local_playback_ui()
{
    connect(ui->btn_select_music_file, &QPushButton::clicked, this, &MainWindow::slot_local_playback_onclick_choose_song);
    connect(ui->btn_play, &QPushButton::clicked, local_playback, &LocalPlayback::music_player_play);
    connect(ui->btn_pause, &QPushButton::clicked, local_playback, &LocalPlayback::music_player_pause);
}

void MainWindow::slot_local_playback_onclick_choose_song()
{
    local_playback->current_file = QFileDialog::getOpenFileName(this,
                                                              tr("Select a .wav file to listen"),
                                                              "./",
                                                                nullptr);
}
