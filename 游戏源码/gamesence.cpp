#include "gamesence.h"
#include "piece.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include <piece_label.h>
#include <QDialog>
#include <QMessageBox>
#include <QAbstractButton>
#include <QCloseEvent>
#include <text_message.h>
#include "ui_text_message.h"
//#include <QAbstractScrollArea>
#include <QScrollArea>
#include <QScrollBar>
#include "move.h"
#include <QTimer>


Gamesence::Gamesence(QWidget *parent)
    : QMainWindow{parent}
{   
    //初始化游戏窗口
    init_game();
    //创建菜单栏
    this->game_bar = create_menubar();
    //初始化菜单栏的一些选项
    init_bar();
    //初始化“游戏”子菜单项
    init_bar_game();
    //初始化标签
    init_label();
    //初始化胜利对话框
    init_win_dialog();
    //设置悔棋/认输按钮
    init_undo_button();
    //初始化返回按钮
    init_return_button();
    //初始化最新棋子
    init_now_label();
    //输赢判定
    connect(this,&Gamesence::black_win,this,&Gamesence::black_win_dialog);
    connect(this,&Gamesence::white_win,this,&Gamesence::white_win_dialog);
    //子菜单初始化
    //newgame
    connect(this->newgame,&QAction::triggered,this,&Gamesence::new_game);
    //quit
    connect(this->quit,&QAction::triggered,this,[this](){
        emit close_mainsence();
        exit(0);
    });
    //re_main
    connect(this->re_main,&QAction::triggered,this,[this](){
        emit show_mainsence();
    });
    //undo
    connect(this->undo,&QAction::triggered,this,[this](){
        if (this->computer)
        {do_undo(true);}
        else
        {do_undo();}
    });
    //悔棋机制触发
    connect(this->undo_btn,&QPushButton::clicked,this,[this](){
        if (this->computer)
        {do_undo(true);}
        else
        {do_undo();}
    });
    //返回机制触发
    connect(this->btn_return,&Button::clicked,this,&Gamesence::do_return);
}

void Gamesence::init_game()
{
    this->setFixedSize(1280,720);//窗口大小为1280*720
    this->setWindowTitle(QString("五子棋程序"));//设置标题
    this->setWindowIcon(QIcon(":/res-image/logo.ico"));//设置标题图标
    //初始化下棋声音
    this->play_sound->setSource(QUrl::fromLocalFile(":/res-music/playing_01.wav"));
    this->play_sound->play();
}

QMenuBar * Gamesence::create_menubar()
{
    //创建菜单栏
    game_bar = new QMenuBar(this);
    this->setMenuBar(game_bar);
    game_bar->addSeparator();
    return game_bar;
}
void Gamesence::init_bar()
{
    //创建菜单项
    this->game = new QMenu("游戏",this->game_bar);
    game_bar->addMenu(game);
    this->edit = new QMenu("编辑",game_bar);
    game_bar->addMenu(edit);
    this->setting = new QMenu("设置",game_bar);
    game_bar->addMenu(setting);
    this->help = new QMenu("帮助",game_bar);
    game_bar->addMenu(help);
}

void Gamesence::init_bar_game()
{
    this->newgame = new QAction("新游戏",game);
    this->game->addAction(newgame);
    this->undo = new QAction("悔棋",game);
    this->game->addAction(undo);
    this->re_main = new QAction("返回主页面",game);
    this->game->addAction(re_main);
    this->quit = new QAction("退出",game);
    this->game->addAction(quit);

}


void Gamesence::paintEvent(QPaintEvent *)
{
    QPixmap background_image(background);
    background_image=background_image.scaled(600,600);
    QPainter painter1(this);
    painter1.drawPixmap(50,50,background_image);
    return;
}

void Gamesence::init_label()
{
    for (int i = 2;i<=16;i++)
    {
        for (int j = 2;j<=16;j++)
        {
            this->piece[i][j].pos_x = (i-1)*37.8+53;
            this->piece[i][j].pos_y = (j-1)*38.5+15;
//            this->piece[i][j].label.setPixmap(QPixmap(":/res-image/black_piece.png"));
            this->piece[i][j].label.move(this->piece[i][j].pos_x,this->piece[i][j].pos_y);
            this->piece[i][j].label.resize(25,25);
            this->piece[i][j].label.setParent(this);
            this->piece[i][j].numlabel.move(this->piece[i][j].pos_x+8,this->piece[i][j].pos_y);
            this->piece[i][j].numlabel.resize(25,25);
            this->piece[i][j].numlabel.setParent(this);
            this->piece[i][j].numlabel.setAttribute(Qt::WA_TransparentForMouseEvents,true);
            //对每一篇落子区域进行下棋判定
            connect(&this->piece[i][j].label,&Piece_Label::start_piece,this,[=]()
            {
                start_playing(i,j);
            });

        }
    }
}

//下棋判定
void Gamesence::start_playing(int i,int j,bool must)
{
    if (this->computer&&((this->amount+1)%2)==this->ai_prior&&!must)
    {
        return;
    }
    if(!this->piece[i][j].id)
    {
        if (this->setting_page->music_on_off)
            this->play_sound->play();
        this->amount++;
        if (this->amount%2)
        {
            this->piece[i][j].label.setPixmap(QPixmap(":/res-image/black_piece.png"));
            this->piece[i][j].numlabel.setStyleSheet("QLabel { color : white; }");
            this->piece[i][j].numlabel.setNum(amount);
            this->piece[i][j].id = amount;
            update_text(QString("【黑方】在%1:%2处落子\n").arg(QChar(i+63)).arg(17-j));
        }
        else
        {
            this->piece[i][j].label.setPixmap(QPixmap(":/res-image/white_piece.png"));
            this->piece[i][j].numlabel.setStyleSheet("QLabel { color : black; }");
            this->piece[i][j].numlabel.setNum(amount);
            this->piece[i][j].id = amount;
            update_text(QString("【白方】在%1:%2处落子\n").arg(QChar(i+63)).arg(17-j));

        }
        this->x = i;
        this->y = j;
        this->now_piece_label->move(this->piece[i][j].label.x(),this->piece[i][j].label.y());
        //每次下完一步就判定
        check_win();
        if (this->computer&&((this->amount+1)%2)==this->ai_prior)
        {
            update_text(QString("AI正在思考......\n"));
            QTimer::singleShot(500,this,&Gamesence::ai_playing);
        }

    }

}

void Gamesence::init_now_label()
{
    this->now_piece_label->setPixmap(QPixmap(":/res-image/now_piece.png"));
    this->now_piece_label->setParent(this);
    this->now_piece_label->resize(25,25);
    this->now_piece_label->move(-100,-100);
    this->now_piece_label->setAttribute(Qt::WA_TransparentForMouseEvents,true);
}
//胜利判定
void Gamesence::check_win()
{
    for (int i = 2;i<=16;i++)
    {
        for (int j = 2;j<=16;j++)
        {
            if(this->piece[i][j].id%2 && this->piece[i-1][j].id%2 && this->piece[i-2][j].id%2 && this->piece[i+1][j].id%2 && this->piece[i+2][j].id%2&&
                this->piece[i][j].id && this->piece[i-1][j].id && this->piece[i-2][j].id && this->piece[i+1][j].id && this->piece[i+2][j].id)
            {
                emit black_win();//五连横-黑色赢
                return;
            }
            else
            if (this->piece[i][j].id%2 && this->piece[i][j-1].id%2 && this->piece[i][j-2].id%2 && this->piece[i][j+1].id%2 && this->piece[i][j+2].id%2&&
                this->piece[i][j].id && this->piece[i][j-1].id && this->piece[i][j-2].id && this->piece[i][j+1].id && this->piece[i][j+2].id)
            {
                emit black_win();//五连纵-黑色赢
                return;
            }
            else
            if (this->piece[i][j].id%2 && this->piece[i-1][j-1].id%2 && this->piece[i-2][j-2].id%2 && this->piece[i+1][j+1].id%2 && this->piece[i+2][j+2].id%2&&
                this->piece[i][j].id && this->piece[i-1][j-1].id && this->piece[i-2][j-2].id && this->piece[i+1][j+1].id && this->piece[i+2][j+2].id)
            {
                emit black_win();//五连斜-黑色赢
                return;
            }
            else
            if (this->piece[i][j].id%2 && this->piece[i+1][j-1].id%2 && this->piece[i+2][j-2].id%2 && this->piece[i-1][j+1].id%2 && this->piece[i-2][j+2].id%2&&
                this->piece[i][j].id && this->piece[i+1][j-1].id && this->piece[i+2][j-2].id && this->piece[i-1][j+1].id && this->piece[i-2][j+2].id)
            {
                emit black_win();//五连斜-黑色赢
                return;
            }
            else
            if(!(this->piece[i][j].id%2) && !(this->piece[i-1][j].id%2) && !(this->piece[i-2][j].id%2) && !(this->piece[i+1][j].id%2) && !(this->piece[i+2][j].id%2)&&
                this->piece[i][j].id && this->piece[i-1][j].id && this->piece[i-2][j].id && this->piece[i+1][j].id && this->piece[i+2][j].id)
            {
                emit white_win();//五连横-白色赢
                return;
            }
            else
            if (!(this->piece[i][j].id%2) && !(this->piece[i][j-1].id%2) && !(this->piece[i][j-2].id%2) && !(this->piece[i][j+1].id%2) && !(this->piece[i][j+2].id%2)&&
                this->piece[i][j].id && this->piece[i][j-1].id && this->piece[i][j-2].id && this->piece[i][j+1].id && this->piece[i][j+2].id)
            {
                emit white_win();//五连纵-白色赢
                return;
            }
            else
            if (!(this->piece[i][j].id%2) && !(this->piece[i-1][j-1].id%2) && !(this->piece[i-2][j-2].id%2) && !(this->piece[i+1][j+1].id%2) && !(this->piece[i+2][j+2].id%2)&&
                this->piece[i][j].id && this->piece[i-1][j-1].id && this->piece[i-2][j-2].id && this->piece[i+1][j+1].id && this->piece[i+2][j+2].id)
            {
                emit white_win();//五连斜-白色赢
                return;
            }
            else
            if (!(this->piece[i][j].id%2) && !(this->piece[i+1][j-1].id%2) && !(this->piece[i+2][j-2].id%2) && !(this->piece[i-1][j+1].id%2) && !(this->piece[i-2][j+2].id%2)&&
                this->piece[i][j].id && this->piece[i+1][j-1].id && this->piece[i+2][j-2].id && this->piece[i-1][j+1].id && this->piece[i-2][j+2].id)
            {
                emit white_win();//五连斜-白色赢
                return;
            }
        }
    }
    return;
}

//初始化胜利对话框
void Gamesence::init_win_dialog()
{
    this->win_dialog->setWindowTitle("游戏结束");
    this->win_dialog->setWindowIcon(QIcon(":/res-image/main_sence_icon.jpg"));
    this->win_dialog->setStandardButtons(QMessageBox::Yes|QMessageBox::No|QMessageBox::Close);
    this->win_dialog->button(QMessageBox::Yes)->setText(QString("再来一局"));
    this->win_dialog->button(QMessageBox::No)->setText(QString("返回主页面"));
    this->win_dialog->button(QMessageBox::Close)->setText(QString("关闭游戏"));
}

void Gamesence::black_win_dialog()
{
    qDebug()<<"黑棋赢了";
    update_text(QString("【系统：恭喜黑棋五子连珠获得胜利】\n"));
    this->win_dialog->setText(QString("恭喜黑棋五子连珠获得胜利！"));
    this->win_dialog->setInformativeText(QString("是否再来一局？"));
    this->win_choice = this->win_dialog->exec();
    win_next();
}

void Gamesence::white_win_dialog()
{
    qDebug()<<"白棋赢了";
    update_text(QString("【系统：恭喜白棋五子连珠获得胜利】\n"));
    this->win_dialog->setText(QString("恭喜白棋五子连珠获得胜利！"));
    this->win_dialog->setInformativeText(QString("是否再来一局？"));
    this->win_choice = this->win_dialog->exec();
    win_next();
}

void Gamesence::win_next()
{
    if(this->win_choice == QMessageBox::Yes)
    {
        qDebug()<<"再来一局";
        new_game();
    }
    else if (this->win_choice == QMessageBox::No)
    {
        qDebug()<<"返回主页面";
        this->computer = false;
        new_game();
        this->win_choice = -1;
        emit show_mainsence();
    }
    else if (this->win_choice == QMessageBox::Close)
    {
        qDebug()<<"关闭游戏";
        emit close_mainsence();
        exit(0);
    }
}

void Gamesence::new_game()
{
    this->amount = 0;
    for (int i = 2;i<=16;i++)
    {
        for (int j = 2;j<=16;j++)
        {
            this->piece[i][j].id = 0;
            this->piece[i][j].label.clear();
            this->piece[i][j].numlabel.clear();
        }
    }
    init_text_message();
}

void Gamesence::init_undo_button()
{
    if (this->undo_btn==nullptr)
    {
        this->undo_btn = new Button(":/res-image/undo_1.png",":/res-image/undo_2.png",800,550,150,100,this,true,false);
    }
}
void Gamesence::init_return_button()
{
    if (this->btn_return == nullptr)
    {
        this->btn_return = new Button(":/res-image/return_1.png",":/res-image/return_2.png",1000,550,150,100,this,true,false);
        this->btn_return->setToolTip(QString("返回主页面"));

    }
}

void Gamesence::do_return()
{
    if (this->setting_page->music_on_off)
        this->play_sound->play();
    emit show_mainsence();
}
void Gamesence::do_undo(bool reverse)
{
    if (!this->amount)
    {
        qDebug()<<"棋盘为空";
        return;
    }
    int i,j,a = 0;

    for (i = 2;i<=16;i++)
    {
        for(j = 2;j<=16;j++)
        {
            if(this->piece[i][j].id == this->amount)
            {
                this->piece[i][j].label.clear();
                this->piece[i][j].numlabel.clear();
                this->piece[i][j].id = 0;
                a = this->amount;
                this->amount--;
                if (a&&a%2)
                {
                    update_text(QString("【黑方】在%1:%2处进行悔棋\n").arg(QChar(i+63)).arg(17-j));
                }
                else if (a&&!(a%2))
                {
                    update_text(QString("【白方】在%1:%2处进行悔棋\n").arg(QChar(i+63)).arg(17-j));
                }
                if (reverse)
                {
                    do_undo(false);
                }
                if (this->setting_page->music_on_off)
                    this->play_sound->play();
                return;
            }
        }
    }

}

void Gamesence::closeEvent(QCloseEvent *event)
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

void Gamesence::init_text_message()
{
    this->t_m->show();
    this->t_m->resize(400,400);
    this->t_m->move(800,150);
    this->text_lines.clear();
    this->text_lines_num = 0;
    update_text(QString("系统：游戏成功运行！！！\n"));
    update_text(QString("五子棋系统v2.0.11.....\n"));
    update_text(QString("作者：小奀\n"));
    if(!this->computer)
    {
        update_text(QString("模式：玩家对战\n"));
    }
    else
    {
        update_text(QString("模式：人机对战\n"));
    }
    update_text(QString("系统：棋盘初始化完毕！！！\n"));
    update_text(QString("————————————————————\n"));

}

void Gamesence::update_text(QString text)
{
    this->text_lines.append(text);
    this->t_m->ui->label->setText(this->text_lines);
    this->text_lines_num++;
    if (text_lines_num>=18)
    {
        this->t_m->ui->scrollArea->verticalScrollBar()->setValue((text_lines_num-18)*19);
    }
}

void Gamesence::init_choose_dialog()
{
    this->choose_dialog->setText(QString("人机模式"));
    this->choose_dialog->setInformativeText(QString("请你选择执黑棋还是白棋？"));
    this->choose_dialog->setWindowTitle("选择黑白");
    this->choose_dialog->setWindowIcon(QIcon(":/res-image/main_sence_icon.jpg"));
    this->choose_dialog->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    this->choose_dialog->button(QMessageBox::Yes)->setText(QString("AI执黑先手，你执白后手"));
    this->choose_dialog->button(QMessageBox::No)->setText(QString("AI执白后手，你执黑先手"));
    this->choose_p_ai = this->choose_dialog->exec();
    this->new_game();
    choose_next();
}

void Gamesence::choose_next()
{
    if(this->choose_p_ai == QMessageBox::Yes)
    {
        qDebug()<<"AI执黑";
        this->ai_prior = 1;
        ai_playing();
    }
    else if (this->choose_p_ai == QMessageBox::No)
    {
        qDebug()<<"AI执白";
        this->ai_prior = 0;
    }
}

int Gamesence::get_piece(int i,int j)
{
    if (this->piece[i][j].id==0)
    {
        return 0;
    }
    return this->piece[i][j].id%2 == this->ai_prior?1:2;
}

void Gamesence::set_piece(int i,int j)
{
    this->amount++;
    this->piece[i][j].id = this->amount;
}

void Gamesence::unset_piece(int i,int j)
{
    this->amount--;
    this->piece[i][j].id = 0;
}

void Gamesence::ai_playing()
{
    if (!this->amount&&this->ai_prior)
    {
        start_playing(9,9,true);
        return;
    }
    else if (this->amount==1&&!this->ai_prior)
    {
        start_playing(this->x+1,this->y+1,true);
        return;
    }
    if (this->computer&&((this->amount+1)%2)==this->ai_prior)
    {
        this->t_m->ui->label->setText(this->text_lines);
        this->result_move = maxmin_alpha_beta(-1e+6,1e+6,this->setting_page->kill_depth_level,true);
        int i = this->result_move.x;
        int j = this->result_move.y;
        start_playing(i,j,true);
    }
    //每次下完一步就判定
}

int Gamesence::max(int a,int b)
{
    return a>b?a:b;
}
int Gamesence::min(int a,int b)
{
    return a<b?a:b;
}

void Gamesence::evaluate()
{
    this->total_score = evaluate_hen()+evaluate_shu()+evaluate_xie1()+evaluate_xie2()-
                        (evaluate_hen(true)+evaluate_shu(true)+evaluate_xie1(true)+evaluate_xie2(true));
}

int Gamesence::evaluate_hen(bool reverse)
{
    int score = 0;
    if (reverse)
    {
        for (int j = 2;j<=16;j++)
        {
            this->game_line.clear();
            for (int i = 2;i<=16;i++)
            {
                if (this->get_piece(i,j)==0)
                {
                    this->game_line.append('_');
                }
                else if (this->get_piece(i,j)==2)
                {
                    this->game_line.append('1');
                }
                else if (this->get_piece(i,j)==1)
                {
                    this->game_line.append('2');
                }
            }
            score+=calcu_score_2();
        }
    }
    else
    {
        for (int j = 2;j<=16;j++)
        {
            this->game_line.clear();
            for (int i = 2;i<=16;i++)
            {
                if (this->get_piece(i,j)==0)
                {
                    this->game_line.append('_');
                }
                else if (this->get_piece(i,j)==1)
                {
                    this->game_line.append('1');
                }
                else if (this->get_piece(i,j)==2)
                {
                    this->game_line.append('2');
                }
            }
            score+=calcu_score();
        }
    }
    return score;
}
int Gamesence::evaluate_shu(bool reverse)
{
    int score = 0;

    if (reverse)
    {
        for (int i = 2;i<=16;i++)
        {
            this->game_line.clear();
            for (int j = 2;j<=16;j++)
            {
                if (this->get_piece(i,j)==0)
                {
                    this->game_line.append('_');
                }
                else if (this->get_piece(i,j)==2)
                {
                    this->game_line.append('1');
                }
                else if (this->get_piece(i,j)==1)
                {
                    this->game_line.append('2');
                }
            }
            score+=calcu_score_2();
        }
    }
    else
    {
        for (int i = 2;i<=16;i++)
        {
            this->game_line.clear();
            for (int j = 2;j<=16;j++)
            {
                if (this->get_piece(i,j)==0)
                {
                    this->game_line.append('_');
                }
                else if (this->get_piece(i,j)==1)
                {
                    this->game_line.append('1');
                }
                else if (this->get_piece(i,j)==2)
                {
                    this->game_line.append('2');
                }
            }
            score+=calcu_score();
        }
    }
    return score;
}
int Gamesence::evaluate_xie1(bool reverse)
{
    int score = 0;
    if (reverse)
    {
        for (int i = 2;i<=16;i++)
        {
            this->game_line.clear();
            for (int j = 2;j<=18-i;j++)
            {
                if (this->get_piece(j+i-2,j)==0)
                {
                    this->game_line.append('_');
                }
                else if (this->get_piece(j+i-2,j)==2)
                {
                    this->game_line.append('1');
                }
                else if (this->get_piece(j+i-2,j)==1)
                {
                    this->game_line.append('2');
                }
            }
            score+=calcu_score_2();
        }
    }
    else
    {
        for (int i = 2;i<=16;i++)
        {
            this->game_line.clear();
            for (int j = 2;j<=18-i;j++)
            {
                if (this->get_piece(j+i-2,j)==0)
                {
                    this->game_line.append('_');
                }
                else if (this->get_piece(j+i-2,j)==1)
                {
                    this->game_line.append('1');
                }
                else if (this->get_piece(j+i-2,j)==2)
                {
                    this->game_line.append('2');
                }
            }
            score+=calcu_score();
        }
    }
    return score;
}
int Gamesence::evaluate_xie2(bool reverse)
{
    int score = 0;
    if (reverse)
    {
        for (int i = 2;i<=16;i++)
        {
            this->game_line.clear();
            for (int j = 2;j<=18-i;j++)
            {
                if (this->get_piece(j,20-j-i)==0)
                {
                    this->game_line.append('_');
                }
                else if (this->get_piece(j,20-j-i)==2)
                {
                    this->game_line.append('1');
                }
                else if (this->get_piece(j,20-j-i)==1)
                {
                    this->game_line.append('2');
                }
            }
            score+=calcu_score_2();
        }
    }
    else
    {
        for (int i = 2;i<=16;i++)
        {
            this->game_line.clear();
            for (int j = 2;j<=18-i;j++)
            {
                if (this->get_piece(j,20-j-i)==0)
                {
                    this->game_line.append('_');
                }
                else if (this->get_piece(j,20-j-i)==1)
                {
                    this->game_line.append('1');
                }
                else if (this->get_piece(j,20-j-i)==2)
                {
                    this->game_line.append('2');
                }
            }
            score+=calcu_score();
        }
    }
    return score;
}

int Gamesence::calcu_score()
{
    int score = 0;
    score+=WIN5*this->game_line.count(QString("11111"));
    score+=ALIVE4*this->game_line.count(QString("_1111_"));
    if (this->game_line.count(QString("__111__"))>=2)
    {
        score+=DOUBLEALIVE3;
    }
    this->total_score+=DIE4*(this->game_line.count(QString("21111_"))+this->game_line.count(QString("_11112")));
    if ((this->game_line.count(QString("21111_"))+this->game_line.count(QString("_11112")))>=2)
    {
        score+=DOUBLEDIE4;
    }
    if ((this->game_line.count(QString("21111_"))+this->game_line.count(QString("_11112")))>=1&&this->game_line.count(QString("__111__"))>=1)
    {
        score+=DIE4ALIVE3;
    }
    score+=LOWDIE4*(this->game_line.count(QString("2111_1"))+this->game_line.count(QString("1_1112")));
    score+=LOWDIE4*(this->game_line.count(QString("211_11"))+this->game_line.count(QString("11_112")));
    score+=ALIVE3*this->game_line.count(QString("__111__"));
    score+=JUMPLIVE3*(this->game_line.count(QString("_11_1_"))+this->game_line.count(QString("_1_11_")));
    score+=ALIVE2*this->game_line.count(QString("__11__"));
    score+=DOUBLEALIVE2*this->game_line.count(QString("__11__"))/2;
    score+=LOWALIVE2*this->game_line.count(QString("__1_1__"));
    score+=DIE3*(this->game_line.count(QString("2111__"))+this->game_line.count(QString("__1112")));
    score+=DIE2*(this->game_line.count(QString("211__"))+this->game_line.count(QString("__112")));
    score+=ALIVE1*this->game_line.count(QString("__1__"));
    score+=DIE1*(this->game_line.count(QString("21__"))+this->game_line.count(QString("__12")));
    score+=NOTHING*this->game_line.count(QString("___"));
    return score;
}

int Gamesence::calcu_score_2()
{
    int score = 0;
    score+=WIN5_2*this->game_line.count(QString("11111"));
    score+=ALIVE4_2*this->game_line.count(QString("_1111_"));
    if (this->game_line.count(QString("__111__"))>=2)
    {
        score+=DOUBLEALIVE3_2;
    }
    this->total_score+=DIE4_2*(this->game_line.count(QString("21111_"))+this->game_line.count(QString("_11112")));
    if ((this->game_line.count(QString("21111_"))+this->game_line.count(QString("_11112")))>=2)
    {
        score+=DOUBLEDIE4_2;
    }
    if ((this->game_line.count(QString("21111_"))+this->game_line.count(QString("_11112")))>=1&&this->game_line.count(QString("__111__"))>=1)
    {
        score+=DIE4ALIVE3_2;
    }
    score+=LOWDIE4_2*(this->game_line.count(QString("2111_1"))+this->game_line.count(QString("1_1112")));
    score+=LOWDIE4_2*(this->game_line.count(QString("211_11"))+this->game_line.count(QString("11_112")));
    score+=ALIVE3_2*this->game_line.count(QString("__111__"));
    score+=JUMPLIVE3_2*(this->game_line.count(QString("_11_1_"))+this->game_line.count(QString("_1_11_")));
    score+=ALIVE2_2*this->game_line.count(QString("__11__"));
    score+=DOUBLEALIVE2_2*this->game_line.count(QString("__11__"))/2;
    score+=LOWALIVE2_2*this->game_line.count(QString("__1_1__"));
    score+=DIE3_2*(this->game_line.count(QString("2111__"))+this->game_line.count(QString("__1112")));
    score+=DIE2_2*(this->game_line.count(QString("211__"))+this->game_line.count(QString("__112")));
    score+=ALIVE1_2*this->game_line.count(QString("__1__"));
    score+=DIE1_2*(this->game_line.count(QString("21__"))+this->game_line.count(QString("__12")));
    score+=NOTHING_2*this->game_line.count(QString("___"));
    return score;
}

Move Gamesence::maxmin_alpha_beta(int alpha,int beta,int max_depth,bool is_Ai)
{
    Move better_move;
    Move this_move;
    if (max_depth)
    {
        if (is_Ai)
        {
            better_move.score = -1e+6;
            for (int i = 2;i<=16;i++)
            {
                for (int j = 2;j<=16;j++)
                {
                    if (this->get_piece(i,j) != 0)
                    {
                        continue;
                    }
                    this->set_piece(i,j);
                    this_move=maxmin_alpha_beta(alpha,beta,max_depth-1,!is_Ai);
                    this_move.x = i;
                    this_move.y = j;
                    this->unset_piece(i,j);
                    if(better_move.score < this_move.score)
                    {
                        better_move.score = this_move.score;
                        better_move.x = this_move.x;
                        better_move.y = this_move.y;
                    }
                    alpha = max(better_move.score,alpha);
                    if (alpha>=beta)
                    {
                        qDebug()<<better_move.x << " " << better_move.y << " " << better_move.score;
                        return better_move;
                    }

                }
            }
            qDebug()<<better_move.x << " " << better_move.y << " " << better_move.score;
            return better_move;
        }
        else
        {
            better_move.score = +1e+6;
            for (int i = 2;i<=16;i++)
            {
                for (int j = 2;j<=16;j++)
                {
                    if (this->get_piece(i,j) != 0)
                    {
                        continue;
                    }
                    this->set_piece(i,j);
                    this_move = maxmin_alpha_beta(alpha,beta,max_depth-1,!is_Ai);
                    this_move.x = i;
                    this_move.y = j;
                    if(better_move.score > this_move.score)
                    {
                        better_move.score = this_move.score;
                        better_move.x = this_move.x;
                        better_move.y = this_move.y;
                    }
                    this->unset_piece(i,j);
                    beta = min(better_move.score,beta);
                    if (alpha>=beta)
                    {
                        qDebug()<<better_move.x << " " << better_move.y << " " << better_move.score;
                        return better_move;
                    }
                }
            }
            qDebug()<<better_move.x << " " << better_move.y << " " << better_move.score;
            return better_move;
        }
    }
    else
    {
        evaluate();
        better_move.score = this->total_score;
        qDebug()<<better_move.x << " " << better_move.y << " " << better_move.score;
        return better_move;
    }
}
