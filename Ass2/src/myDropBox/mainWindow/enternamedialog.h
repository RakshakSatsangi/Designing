#ifndef ENTERNAMEDIALOG_H
#define ENTERNAMEDIALOG_H

#include <QDialog>

namespace Ui {
class enterNameDialog;
}

class enterNameDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit enterNameDialog(QWidget *parent = 0);
    ~enterNameDialog();
    QString entry;
    bool isCancelled;
    
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::enterNameDialog *ui;
};

#endif // ENTERNAMEDIALOG_H
