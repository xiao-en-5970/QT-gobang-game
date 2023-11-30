#ifndef BUTTON_H
#define BUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QPixmap>
#include <QMouseEvent>

class Button : public QPushButton
{
    Q_OBJECT
public:
    explicit Button(QWidget *parent = nullptr);
    //未触发图片
    QPixmap normal;
    //触发后图片
    QPixmap later;
    //按钮开关状态
    bool now = false;
    //按钮的几何
    int x,y,width,height;
    //按钮的构造函数
    Button(QString nor_str,QString sel_pre,int x,int y,int width,int height,QWidget *parent = nullptr,bool s_or_p = false,bool default_yes = false);
    //按钮按下事件
    void mousePressEvent(QMouseEvent *event);
    //按钮松开事件
    void mouseReleaseEvent(QMouseEvent *event);
    //鼠标进入事件
    void enterEvent(QEnterEvent *event);
    //鼠标离开
    void leaveEvent(QEvent *);
    //表示这个按钮是移动触发还是点击触发换图片
    bool select_or_press;
signals:

};

#endif // BUTTON_H
