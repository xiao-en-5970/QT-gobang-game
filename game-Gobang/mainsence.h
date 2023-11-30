#ifndef MAINSENCE_H
#define MAINSENCE_H

#include <QMainWindow>
#include "gamesence.h"
#include "setting.h"
#include "button.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainSence; }
QT_END_NAMESPACE

class MainSence : public QMainWindow
{
    Q_OBJECT

public:
    MainSence(QWidget *parent = nullptr);
    void init_main();
    void game_start();
    void init_ai();
    //重写关闭按钮
    void closeEvent(QCloseEvent *event);
    Gamesence * game = nullptr;
    QMessageBox *close_dialog = nullptr;
    Setting * setting = new Setting;
    Button * player_player = nullptr;
    Button * player_computer = nullptr;
    Button * setting_btn = nullptr;
    ~MainSence();

private:
    Ui::MainSence *ui;
};
#endif // MAINSENCE_H
