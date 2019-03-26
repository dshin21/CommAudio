#pragma once

#include <QMainWindow>

#include "client.h"
#include "server.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  private:
    Ui::MainWindow *ui;

    Client *client;
    Server *server;

public slots:
    void init_main_ui();

};
