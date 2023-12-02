#include "mainsence.h"
#include "ui_mainsence.h"
#include "gamesence.h"
#include <QCloseEvent>
MainSence::MainSence(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainSence)
{
    init_main();
    //点击玩家-玩家对战后
    connect(this->player_player,&Button::clicked,this,[this]()
            {
        if (this->game == nullptr)
        {
            this->game = new Gamesence;

        }
        this->game->show();
        this->hide();
        this->game->computer = false;

        //初始化文本框
        this->game->init_text_message();
        this->game->setting_page = this->setting;
        game_start();
    });
    //点击玩家-电脑对战后
    connect(this->player_computer,&Button::clicked,this,[this]()
            {
        if (this->game == nullptr)
        {
            this->game = new Gamesence;
        }
        this->game->setting_page = this->setting;
        this->game->show();
        this->game->computer = true;
        this->hide();
        //初始化文本框
        this->game->init_text_message();
        ///【人机模式】///
        if(this->game->computer)
        {
            this->game->init_choose_dialog();
        }
        game_start();
    });
    //点击游戏设置后
    connect(this->setting_btn,&Button::clicked,this,[this](){
        this->setting->show();
        this->hide();
    });
    if (this->close_dialog == nullptr)
    {this->close_dialog = new QMessageBox;}
}

void MainSence::init_main()
{
    ui->setupUi(this);
    this->setFixedSize(1280,720);//窗口大小为1280*720
    this->setWindowTitle(QString("主页面"));//设置标题
    this->setWindowIcon(QIcon(":/res-image/logo.ico"));//设置标题图标
//    QLabel *main_label = new QLabel(this);
//    main_label->setPixmap(QPixmap(":/res-image/content.png"));
//    main_label->resize(500,720);
//    main_label->move(0.5*this->width()-0.5*main_label->width(),0);
//    main_label->setStyleSheet("border-image:url(:/res-image/content.png)");
    this->player_player = new Button(":/res-image/player-player-1.png",":/res-image/player-player-2.png",480,150,250,100,this,true);
    this->player_computer = new Button(":/res-image/player-computer-1.png",":/res-image/player-computer-2.png",480,310,250,100,this,true);
    this->setting_btn = new Button(":/res-image/setting-btn-1.png",":/res-image/setting-btn-2.png",480,470,250,100,this,true);
    //设置三个按钮居中
    this->player_player->move(this->width()*0.5-this->player_player->width*0.5,this->player_player->y);
    this->player_computer->move(this->width()*0.5-this->player_computer->width*0.5,this->player_computer->y);
    this->setting_btn->move(this->width()*0.5-this->setting_btn->width*0.5,this->setting_btn->y);
    connect(this->setting,&Setting::show_mainsence,this,[this](){
        qDebug()<<"主窗口显示";
        this->show();
        this->setting->hide();
    });
}

void MainSence::game_start()
{
    //游戏结束后返回主页面
    connect(this->game,&Gamesence::show_mainsence,this,[this](){
        qDebug()<<"主窗口显示";
        this->show();
        this->game->hide();
        this->game->computer = false;
        this->game->new_game();
    });
    //游戏结束后关闭游戏
    connect(this->game,&Gamesence::close_mainsence,this,[this](){
        this->close();
        this->game->hide();
//        this->game->close();
    });
}

void MainSence::closeEvent(QCloseEvent *event)
{
    this->close_dialog->setWindowTitle("退出游戏");
    this->close_dialog->setWindowIcon(QIcon(":/res-image/main_sence_icon.jpg"));
    this->close_dialog->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    this->close_dialog->setText(QString("退出游戏"));
    this->close_dialog->setInformativeText(QString("你确认要退出吗？"));
    this->close_dialog->button(QMessageBox::Yes)->setText(QString("确认"));
    this->close_dialog->button(QMessageBox::No)->setText(QString("取消"));



    if (this->close_dialog->exec() == QMessageBox::Yes)
    {
        event->accept(); // 确认退出
    }
    else
    {
        event->ignore(); // 取消退出
    }
}



MainSence::~MainSence()
{
    delete ui;
}

