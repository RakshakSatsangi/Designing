#include "directorydialog.h"
#include "ui_directorydialog.h"

directoryDialog::directoryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::directoryDialog)
{
    ui->setupUi(this);
    QString rootPath = "Documents/myDropBox/LocalFolder";
    dirmodel = new QFileSystemModel(this);
    dirmodel->setRootPath(rootPath);
    ui->treeView->setModel(dirmodel);
}

directoryDialog::~directoryDialog()
{
    delete ui;
}
