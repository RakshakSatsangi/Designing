#ifndef ASKDIALOG_H
#define ASKDIALOG_H

#include <QDialog>
#include <string>
#include <string.h>
using namespace std;

namespace Ui {
class askDialog;
}

class askDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit askDialog(QWidget *parent = 0);
    ~askDialog();
    string prompt;
    
private:
    Ui::askDialog *ui;
};

#endif // ASKDIALOG_H
