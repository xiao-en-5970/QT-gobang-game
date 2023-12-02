#ifndef GAMESENCE_H
#define GAMESENCE_H

#include <QMainWindow>
#include <QLabel>
#include "piece.h"
#include <QDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QSoundEffect>
#include <QScrollArea>
#include <QLabel>
#include <text_message.h>
#include "move.h"
#include "score.h"
#include <piece_label.h>
#include "setting.h"
#include "button.h"

class Gamesence : public QMainWindow
{
    Q_OBJECT
public:
    explicit Gamesence(QWidget *parent = nullptr);
    //一些函数
    //初始化游戏窗口
    void init_game();
    //初始化各种菜单
    void init_bar();
    //初始化游戏子菜单
    void init_bar_game();
    //重写绘图事件
    void paintEvent(QPaintEvent *event);
    //初始化下棋标签
    void init_label();
    //点击下棋函数
    void start_playing(int i,int j,bool must = false);
    //检测是否胜利
    void check_win();
    //初始化胜利对话框（再来一局，返回主页面，退出游戏）
    void init_win_dialog();
    //黑棋赢了
    void black_win_dialog();
    //白棋赢了
    void white_win_dialog();
    //赢了下一步（再来一局，返回主页面，退出游戏）
    void win_next();
    //清理战场（再来一局）
    void new_game();
    //初始化悔棋按钮
    void init_undo_button();
    //初始化返回按钮
    void init_return_button();
    //悔棋功能
    void do_undo(bool reverse = false);
    //返回功能
    void do_return();
    //重写关闭按钮
    void closeEvent(QCloseEvent *event);
    //初始化文本框
    void init_text_message();
    //便捷更新文本框的文本
    void update_text(QString text);
    //初始化最新棋子
    void init_now_label();
    //【人机模式】-函数
    //【人机模式】选择先后对话框初始化
    void init_choose_dialog();
    //【人机模式】选择黑白下一步
    void choose_next();
    //是否为电脑对局
    bool computer = false;
    //【人机模式】AI的先后手
    int ai_prior;
    //【人机模式】得到落子信息
    int get_piece(int i,int j);
    //【人机模式】模拟落子
    void set_piece(int i,int j);
    //【人机模式】取消模拟落子
    void unset_piece(int i,int j);
    //【人机模式】AI下棋
    void ai_playing();
    //评估分数的函数
    void evaluate();
    //评估横方向
    int evaluate_hen(bool reverse = false);
    //评估竖方向
    int evaluate_shu(bool reverse = false);
    //评估斜（捺）方向
    int evaluate_xie1(bool reverse = false);
    //评估斜（撇）方向
    int evaluate_xie2(bool reverse = false);
    //计算一条线的分数
    int calcu_score();
    //计算人类一条线的分数
    int calcu_score_2();
    //博弈树（极大极小-alpha-beta剪枝）
    Move maxmin_alpha_beta(int alpha,int beta,int max_depth,bool is_Ai);
    //设置
    Setting * setting_page = nullptr;
private:
    //创建新菜单栏
    QMenuBar *create_menubar();
    //菜单栏
    QMenuBar * game_bar;
    //菜单
    QMenu * game;
    QMenu * edit;
    QMenu * setting;
    QMenu * help;
    //子菜单
    QAction * newgame;
    QAction * quit;
    QAction * re_main;
    QAction * undo;
    //音乐
    QSoundEffect * play_sound = new QSoundEffect();
    //棋子
    Piece piece[20][20];
    QMessageBox *win_dialog = new QMessageBox;
    QMessageBox *close_dialog = new QMessageBox;
    QMessageBox *choose_dialog = new QMessageBox;
    //文本框显示
    Text_message * t_m = new Text_message(this);
    //背景图片路径
    QString background = ":/res-image/gameboard.jpeg";
    //游戏按钮
    //悔棋
    Button * undo_btn = nullptr;
    //返回按钮
    Button * btn_return = nullptr;
    //现在下到哪里了
    QLabel *now_piece_label = new QLabel;

    //普通变量
    int amount = 0;//下棋次数，奇数为黑棋下，偶数为白棋下
    int win_choice = -1;//胜利对话框后的选择
    QString text_lines;//初始化文本框的文字
    int text_lines_num = 0;//对文字行数的记录
    //【人机模式】选择人还是ai
    int choose_p_ai;
    //【人机模式】算出来的最终理想一步
    Move result_move;
    //【人机模式】将游戏分成横竖撇捺
    QString game_line;
    //评估总分
    long long total_score = 0;
    //求最大值函数
    int max(int a,int b);
    //求最小值函数
    int min(int a,int b);
    //最新棋子的坐标
    int x;
    int y;


signals:
    void white_win();
    void black_win();
    void show_mainsence();
    void close_mainsence();
};

#endif // GAMESENCE_H
