#include "piece_label.h"
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
Piece_Label::Piece_Label(QWidget *parent)
    : QLabel{parent}
{

}

void Piece_Label::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton)
    {
        emit start_piece();
    }
}
