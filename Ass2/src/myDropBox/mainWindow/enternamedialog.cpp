#include "enternamedialog.h"
#include "ui_enternamedialog.h"
#include <QDebug>

enterNameDialog::enterNameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::enterNameDialog)
{
    ui->setupUi(this);
    isCancelled = true;
    QPixmap bkgnd("./download.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
        palette.setBrush(QPalette::Background, bkgnd);
        this->setPalette(palette);
}

enterNameDialog::~enterNameDialog()
{
    delete ui;
}

void enterNameDialog::on_buttonBox_accepted()
{
    isCancelled = false;
    if(ui->lineEdit->text()=="")
    {
        qDebug()<<"NULL entered";        
    }
    else
    {
        this->entry = ui->lineEdit->text();
    }
}

void enterNameDialog::on_buttonBox_rejected()
{
    isCancelled = true;
}
