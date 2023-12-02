#ifndef TEXT_MESSAGE_H
#define TEXT_MESSAGE_H

#include <QWidget>

namespace Ui {
class Text_message;
}

class Text_message : public QWidget
{
    Q_OBJECT

public:
    explicit Text_message(QWidget *parent = nullptr);
    Ui::Text_message *ui;
    ~Text_message();


private:

};

#endif // TEXT_MESSAGE_H
