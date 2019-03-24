#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "musicplayer.h"

#include <QFile>
#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MusicPlayer *music_player;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void onclick_btn_select_file();
    void onclick_btn_save_file();

  private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
