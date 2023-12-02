#include "text_message.h"
#include "ui_text_message.h"

Text_message::Text_message(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Text_message)
{
    ui->setupUi(this);
}

Text_message::~Text_message()
{
    delete ui;
}
