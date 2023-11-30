#include "button.h"

Button::Button(QWidget *parent)
    : QPushButton{parent}
{

}

Button::Button(QString nor_str,QString sel_pre,int x,int y,int width,int height,QWidget *parent,bool s_or_p,bool default_yes)
{
    this->normal = QPixmap(nor_str);
    this->move(x,y);
    this->resize(width,height);
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->select_or_press = s_or_p;
    this->later = QPixmap(sel_pre);
    if (default_yes)
    {
        this->setIcon(this->later);
        this->now = true;
    }
    else
    {
        this->setIcon(this->normal);
        this->now = false;
    }
    this->setIconSize(QSize(width,height));
    this->setParent(parent);
    this->setStyleSheet("QPushButton { border: none; }");
    this->show();
}

//鼠标点击
void Button::mousePressEvent(QMouseEvent *)
{
    if (!this->select_or_press)
    {
        if (!this->now)
        {
            this->setIcon(this->later);
            this->setIconSize(QSize(width,height));
            this->now = true;
        }
        else
        {
            this->setIcon(this->normal);
            this->setIconSize(QSize(width,height));
            this->now = false;
        }
    }
    emit clicked();
}
//鼠标释放
void Button::mouseReleaseEvent(QMouseEvent *)
{
//    if (!this->select_or_press && this->now != &this->normal)
//    {
//        this->setIcon(this->normal);
//        this->setIconSize(QSize(width,height));
//        this->now = &this->normal;
//    }
}
//鼠标进入事件
void Button::enterEvent(QEnterEvent *)
{

    if (this->select_or_press && !this->now)
    {
        this->setIcon(this->later);
        this->setIconSize(QSize(width,height));
        this->now = true;
    }
}
//鼠标离开
void Button::leaveEvent(QEvent *)
{
    if (this->select_or_press && this->now)
    {
        this->setIcon(this->normal);
        this->setIconSize(QSize(this->width,this->height));
        this->now = false;
    }
}
