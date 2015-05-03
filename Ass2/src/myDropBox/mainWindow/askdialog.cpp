#include "askdialog.h"
#include "ui_askdialog.h"
#include <iostream>
askDialog::askDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::askDialog)
{
    ui->setupUi(this);
    //QString prompt_str = this->prompt;
    cout<<"raesd23432: "<<prompt<<endl;
    ui->textEdit->setText("asdffa");
}

askDialog::~askDialog()
{
    delete ui;
}
