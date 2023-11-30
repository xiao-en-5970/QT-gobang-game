#include "setting.h"

Setting::Setting(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(1280,720);//窗口大小为1280*720
    this->setWindowTitle(QString("设置"));//设置标题
    this->setWindowIcon(QIcon(":/res-image/logo.ico"));//设置标题图标
    this->text_label = new QLabel;
    this->play_sound = new QSoundEffect;
    this->play_sound->setSource(QUrl::fromLocalFile(":/res-music/playing_01.wav"));
    init_text_label();
    init_depth_setting();
    init_music_setting();
    init_jinshou_setting();
    init_experimental_setting();
    init_return_btn();
}

void Setting::init_text_label()
{
    this->text_label->setParent(this);
    this->text_label->resize(375,150);
    this->title.load(":/res-image/setting-btn-1.png");
    this->text_label->setPixmap(this->title.scaled(1.5*this->title.width(),1.5*this->title.height()));
    this->text_label->move(this->width()*0.5-this->text_label->width()*0.5,30);
}

void Setting::init_depth_setting()
{
    if (this->text_depth==nullptr&&this->btn_depth==nullptr)
    {
        this->text_depth = new QLabel(this);
        this->text_depth->move(200,200);
        this->text_depth->resize(1280,100);
        this->text_depth->setFont(QFont("华文楷体",30,3,false));
        this->text_depth->setText("AI算法搜索深度增加到2【默认为1】");
        this->text_depth->setToolTip(QString("调至2可能会增加AI的思考时间，但可大幅提高AI下棋的胜率（大概）"));
        this->btn_depth = new Button(":/res-image/setting_no.png",":/res-image/setting_yes.png",1000,225,50,50,this,false,false);
        this->btn_depth->setToolTip(QString("打勾≠你同意【无端联想】"));
        connect(this->btn_depth,&Button::clicked,this,[this](){
            if (!this->btn_depth->now)
                {
                this->kill_depth_level = 1;
            }
            else
                {
                this->kill_depth_level = 2;
            }
            if (this->music_on_off)
                this->play_sound->play();
        });
    }
}

void Setting::init_music_setting()
{
    if (this->text_music==nullptr&&this->btn_music==nullptr)
    {
        this->text_music = new QLabel(this);
        this->text_music->move(200,300);
        this->text_music->resize(1280,100);
        this->text_music->setFont(QFont("华文楷体",30,3,false));
        this->text_music->setText("是否开启落子音效");
        this->text_music->setToolTip(QString("应该没人会觉得这音乐吵吧（"));
        this->btn_music = new Button(":/res-image/setting_no.png",":/res-image/setting_yes.png",1000,325,50,50,this,false,true);
        this->btn_music->setToolTip(QString("打勾≠你同意【无端联想】"));
        connect(this->btn_music,&Button::clicked,this,[this](){
            if (!this->btn_music->now)
            {
                this->music_on_off = false;
            }
            else
            {
                this->music_on_off = true;
            }
            if (this->music_on_off)
                this->play_sound->play();
        });
    }
}

void Setting::init_jinshou_setting()
{
    if (this->text_jinshou==nullptr&&this->btn_jinshou==nullptr)
    {
        this->text_jinshou = new QLabel(this);
        this->text_jinshou->move(200,400);
        this->text_jinshou->resize(1280,100);
        this->text_jinshou->setFont(QFont("华文楷体",30,3,false));
        this->text_jinshou->setText("是否开启禁手规则（其实这个我还没做）");
        this->text_jinshou->setToolTip(QString("开启禁手规则有利于黑白双方实力平衡"));
        this->btn_jinshou = new Button(":/res-image/setting_no.png",":/res-image/setting_yes.png",1000,425,50,50,this,false,false);
        this->btn_jinshou->setToolTip(QString("打勾≠你同意【无端联想】"));
        connect(this->btn_jinshou,&Button::clicked,this,[this](){
            if (!this->btn_jinshou->now)
            {
                this->jinshou = false;
            }
            else
            {
                this->jinshou = true;
            }
            if (this->music_on_off)
                this->play_sound->play();
        });
    }
}
void Setting::init_experimental_setting()
{
    if (this->text_experimental==nullptr&&this->btn_experimental==nullptr)
    {
        this->text_experimental = new QLabel(this);
        this->text_experimental->move(200,500);
        this->text_experimental->resize(1280,100);
        this->text_experimental->setFont(QFont("华文楷体",30,3,false));
        this->text_experimental->setText("是否开启实验性玩法（这个我也没开始做）");
        this->text_experimental->setToolTip(QString("你可以猜猜是哪些实验性功能"));
        this->btn_experimental = new Button(":/res-image/setting_no.png",":/res-image/setting_yes.png",1000,525,50,50,this,false,false);
        this->btn_experimental->setToolTip(QString("打勾≠你同意【无端联想】"));
        connect(this->btn_experimental,&Button::clicked,this,[this](){
            if (!this->btn_experimental->now)
            {
                this->experimental_function = false;
            }
            else
            {
                this->experimental_function = true;
            }
            if (this->music_on_off)
                this->play_sound->play();
        });
    }
}

void Setting::init_return_btn()
{
    if (this->btn_return==nullptr)
    {
        this->btn_return = new Button(":/res-image/return_1.png",":/res-image/return_2.png",50,25,150,100,this,true,false);
        this->btn_return->setToolTip(QString("返回主页面"));
        connect(this->btn_return,&Button::clicked,this,[this](){
            emit show_mainsence();
        });
        if (this->music_on_off)
            this->play_sound->play();
    }
}
