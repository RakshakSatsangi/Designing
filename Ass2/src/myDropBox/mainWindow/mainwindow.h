#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <stdlib.h>
#include "loginsuccesswindow.h"
#include "global.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <resolv.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <malloc.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:

    void on_createAccButton_clicked();

    void on_logInButton_clicked();

    void on_connectButton_clicked();

private:
    Ui::MainWindow *ui;
    loginSuccessWindow * loggedInWindow;
    void clearLineEdits();
};

void recievemsg();
void sendmsg(string str);
char* stringtocharp(string s);
string qstrtostr(QString qstr);

#endif // MAINWINDOW_H
