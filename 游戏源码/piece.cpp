#include "piece.h"
#include <QPixmap>
#include <QMouseEvent>
#include <QDebug>
#include "piece_label.h"
Piece::Piece(QObject *parent)
    : QObject{parent}
{
    this->white.load(QString(":/res-image/white_piece.png"));
    this->black.load(QString(":/res-image/black_piece.png"));


}

//void Piece::mousePressEvent(QMouseEvent *event)
//{
//    if (event->button() == Qt::LeftButton)
//    {
//        qDebug()<<"点击了";
//    }
//}
