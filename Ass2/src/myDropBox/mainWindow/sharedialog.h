#ifndef SHAREDIALOG_H
#define SHAREDIALOG_H

#include <QDialog>
#include <QDebug>
#include <string>
using namespace std;

namespace Ui {
class shareDialog;
}

class shareDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit shareDialog(QWidget *parent = 0);
    ~shareDialog();
    void showSharingFileName(QString filename);
    string username;
    void populateListWidget();
    bool isFolder = false;


private slots:
    void on_publicradioButton_clicked();

    void on_specificradioButton_clicked();

    void on_okButton_clicked();

private:
    Ui::shareDialog *ui_core;
};

#endif // SHAREDIALOG_H
