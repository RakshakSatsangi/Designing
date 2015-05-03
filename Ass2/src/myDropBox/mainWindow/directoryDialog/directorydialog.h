#ifndef DIRECTORYDIALOG_H
#define DIRECTORYDIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QFileSystemModel>

namespace Ui {
class directoryDialog;
}

class directoryDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit directoryDialog(QWidget *parent = 0);
    ~directoryDialog();
    
private:
    Ui::directoryDialog *ui;
    QFileSystemModel * dirmodel;
    QFileSystemModel * filemodel;
};

#endif // DIRECTORYDIALOG_H
