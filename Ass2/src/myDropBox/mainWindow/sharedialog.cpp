#include "sharedialog.h"
#include "mainwindow.h"
#include "ui_sharedialog.h"
#include <QDebug>

void shareDialog::populateListWidget()
{
    sendmsg("Give Users List");
    while(1)
    {
        recievemsg();
        if(msgstr=="/No More Users/")
        {
            return;
        }
        else
        {
            if(msgstr!=this->username)
            {
                QListWidgetItem * new_user_item = new QListWidgetItem;

                new_user_item->setText(QString::fromStdString(msgstr));

                ui_core->listWidget->addItem(new_user_item);
            }
            sendmsg("User Item Recieved");
        }
    }

}

shareDialog::shareDialog(QWidget *parent) :
    QDialog(parent),
    ui_core(new Ui::shareDialog)
{
    qDebug()<< "object created";
    ui_core->setupUi(this);
    ui_core->specificradioButton->setChecked(true);
    this->on_specificradioButton_clicked();
    //ui_core->lineEdit->setText();
    QPixmap bkgnd("./download.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
        palette.setBrush(QPalette::Background, bkgnd);
        this->setPalette(palette);

}

shareDialog::~shareDialog()
{
    delete ui_core;

}

void shareDialog::showSharingFileName(QString filename)
{
    ui_core->pathlabel->setText(filename);
}

void shareDialog::on_publicradioButton_clicked()
{
    ui_core->listWidget->hide();
    ui_core->label->hide();
}

void shareDialog::on_specificradioButton_clicked()
{
    ui_core->listWidget->show();
    ui_core->label->show();
}

void shareDialog::on_okButton_clicked()
{
    if(ui_core->listWidget->selectedItems().empty() && ui_core->specificradioButton->isChecked())
    {
        qDebug()<<"Please select some user to share with!";
        return;
    }
    if(ui_core->publicradioButton->isChecked())
    {
        sendmsg("Share With Public");
        recievemsg();
        if(msgstr=="Send Path")
        {
            sendmsg(qstrtostr(ui_core->pathlabel->text()));
            this->close();
        }

        // write file path to my public folder
    }
    else if(ui_core->specificradioButton->isChecked())
    {
        string specific_user = qstrtostr(ui_core->listWidget->currentItem()->text()); // ensure that listwidget contains only other users
        sendmsg("Share With Specific User");
        recievemsg();
        if(msgstr=="Send Specific User")
        {
            sendmsg(specific_user);
            recievemsg();
            if(msgstr=="Send Path")
            {
                sendmsg(qstrtostr(ui_core->pathlabel->text()));
                recievemsg();
                if(msgstr=="Folder Or File?")\
                {
                    if(this->isFolder)
                    {
                        sendmsg("Folder");
                    }
                    else
                    {
                        sendmsg("File");
                    }
                    recievemsg();
                    if(msgstr=="Shared!")
                    {
                        this->close();
                    }
                }

            }
        }
        // write file path to shared-folder/specific-user
    }
}
