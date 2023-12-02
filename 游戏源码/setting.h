#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include <QLabel>
#include <QFont>
#include "button.h"
#include <QSoundEffect>

class Setting : public QWidget
{
    Q_OBJECT
public:
    explicit Setting(QWidget *parent = nullptr);
    QLabel *text_label = nullptr;
    //各个功能的文字部分
    QLabel *text_depth = nullptr;
    QLabel *text_music = nullptr;
    QLabel *text_jinshou = nullptr;
    QLabel *text_experimental = nullptr;
    //各个功能的按钮部分
    Button *btn_depth = nullptr;
    Button *btn_music = nullptr;
    Button *btn_jinshou = nullptr;
    Button *btn_experimental = nullptr;
    Button *btn_return = nullptr;
    //标题图片
    QPixmap title;
    //函数
    void init_text_label();
    void init_depth_setting();
    void init_music_setting();
    void init_jinshou_setting();
    void init_experimental_setting();
    void init_return_btn();
    //选项
    int kill_depth_level = 1;
    bool music_on_off = true;
    bool jinshou = false;
    bool experimental_function = false;
    //音乐
    QSoundEffect * play_sound = nullptr;
signals:
    void show_mainsence();

};

#endif // SETTING_H
