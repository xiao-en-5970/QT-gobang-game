#ifndef PIECE_H
#define PIECE_H

#include <QObject>
#include <QPixmap>
#include <QString>
#include <QLabel>
#include "piece_label.h"

class Piece : public QObject
{
    Q_OBJECT
public:
    explicit Piece(QObject *parent = nullptr);
//    void mousePressEvent(QMouseEvent *event)

//    int color = 0;//1为黑棋，-1为白棋，默认为0
    int pos_x = 0;//x轴位置
    int pos_y = 0;//y轴位置
    int id = 0;//第几颗
    Piece_Label label;
    QLabel numlabel;
    QPixmap white;
    QPixmap black;
signals:

};

#endif // PIECE_H
