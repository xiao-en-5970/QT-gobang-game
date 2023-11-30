#ifndef PIECE_LABEL_H
#define PIECE_LABEL_H

#include <QWidget>
#include <QLabel>

class Piece_Label : public QLabel
{
    Q_OBJECT
public:
    explicit Piece_Label(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
signals:
    void start_piece();
};

#endif // PIECE_LABEL_H
