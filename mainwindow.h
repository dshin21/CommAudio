#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "local_playback.h"

#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    LocalPlayback *local_playback;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //init ui
    void init_local_playback_ui();

  private:
    Ui::MainWindow *ui;

public slots:
    void slot_local_playback_onclick_choose_song();

};

#endif // MAINWINDOW_H
