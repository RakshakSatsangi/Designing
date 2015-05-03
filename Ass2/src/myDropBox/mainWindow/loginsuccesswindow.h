#ifndef LOGINSUCCESSWINDOW_H
#define LOGINSUCCESSWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <QDebug>
#include "global.h"
#include <dirent.h>
#include "ui_loginsuccesswindow.h"
#include "sharedialog.h"
#include "string"

using namespace std;

namespace Ui {
class loginSuccessWindow;
}

class loginSuccessWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit loginSuccessWindow(QWidget *parent = 0);
    ~loginSuccessWindow();
    string username;
    void setWelcomeMessage();
    string lastDownloadLocation;
    
private slots:
    void on_uploadButton_clicked();

    void on_dldButton_clicked();

    void on_dirTreeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_createFolderButton_clicked();

    void hideOtherButtons();

    void showAllButtons();

    void on_logoutButton_clicked();

    void on_deleteButton_clicked();

    void on_myfileradioButton_clicked();

    void on_sharedradioButton_clicked();

    void on_publicradioButton_clicked();

    void on_shareButton_clicked();

    void on_sharedTreeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_publicTreeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_uploadNewEditionButton_clicked();

    void on_refreshButton_clicked();

    void on_openButton_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_SyncButton_clicked();

private:
    Ui::loginSuccessWindow *ui;
    shareDialog * shareDialog_obj;
    void downloadFile(string path ,string recv_path);
    void downloadFolder(QTreeWidgetItem* folder_item, string path, string recv_path);
    string getFilePath(QTreeWidgetItem * item);
    string getFilePath_1(QTreeWidgetItem * item);
    void sendFileC2S(string filename);
    void rcvFilefromServer(string filename);
    QTreeWidgetItem* root_item_permanent;

};

#endif // LOGINSUCCESSWINDOW_H
