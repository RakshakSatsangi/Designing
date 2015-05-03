#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <string.h>
#include <ctype.h>
using namespace std;




string qstrtostr(QString qstr)
{
    return (qstr.toUtf8().constData());
}

char* stringtocharp(string s)
{
    int i;
    char* aux=new char [s.size()];
    for(int i=0;i<s.size();i++)
    {
        aux[i]=s[i];
    }
    //aux[i]='\0';
    return aux;
}


void recievemsg()
{
    char x[256]={0};
  //  memset(x, '0', sizeof(x));
    int bread=SSL_read(ssl,x,256);
    while(bread<0)
    {
        bread=SSL_read(ssl,x,256);
        qDebug()<<"Error receiving";
    }
    cout<<"Bytes recd "<<bread<<endl;
    msgstr=x;
    cout<<"Message recieved: "<<msgstr<<endl;
}
void sendmsg(string str)
{
    //for(int i=0;i<1000000;i++)
    //{
    //    int xyz=3;
    //}
    char* abc = stringtocharp(str);
    cout<<"SENDING"<<str<<endl;
    int bsent = SSL_write(ssl,abc,str.size());
    while(bsent<0)
    {
        bsent = SSL_write(ssl,abc,str.size());
        cout<<"Trying to send"<<endl;
    }
    cout<<"BYTES SENT: "<<bsent<<endl;
    cout<<"message sent: "<<abc<<endl;

}



int connectS(const char* ip_addr1)
{
    memset(recvBuff, '0', sizeof(recvBuff));
    struct hostent *server;
       server = gethostbyname(ip_addr1);
         if (server == NULL) {
              fprintf(stderr,"ERROR, no such host\n");
              return -1;

          }
    /* Create a socket first */
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
        qDebug()<<("\n Error : Could not create socket \n");
        return -1;
    }

    /* Initialize sockaddr_in data structure */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portNumber); // port

    bcopy((char *)server->h_addr,
                  (char *)&serv_addr.sin_addr.s_addr,
                  server->h_length);

    /* Attempt a connection */
    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    {
        qDebug()<<("\n Error : Connect Failed \n");
        return -1;
    }
    return 0;

}
/*
void write(QString filename)
{
    QFile myFile(filename);
    if(!myFile.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "could not open file for writing";
        return;
    }

    QTextStream out(&myFile);
    out<<"Hello";

    myFile.flush();
    myFile.close();


}*/

void MainWindow::clearLineEdits()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd("./download.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
        palette.setBrush(QPalette::Background, bkgnd);
        this->setPalette(palette);

}

MainWindow::~MainWindow()
{
    delete ui;
    //connect(ui->pushButton, SIGNAL(accepted()), this, SLOT(accept()));
    //connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void MainWindow::on_createAccButton_clicked()
{
    QString userName = ui->lineEdit_4->text();
    QString password = ui->lineEdit_5->text();
    QString re_password = ui->lineEdit_6->text();

    if(password!=re_password)
    {
        ui->statusBar->showMessage("Passwords don't match!", 2000);
        qDebug() << "Passwords don't match!";
        clearLineEdits();
        return;
    }
    if(userName.isEmpty())
    {
        ui->statusBar->showMessage("Empty UserName field!", 2000);
        qDebug()<<"Empty UserName field!";
        clearLineEdits();
        return;
    }
    if(password.isEmpty())
    {
        ui->statusBar->showMessage("Empty Password field!", 2000);
        qDebug()<<"Empty Password field!";
        clearLineEdits();
        return;
    }
    sendmsg("Signup");
    recievemsg();
    if(msgstr=="Give Username")
    {
        sendmsg(qstrtostr(userName));
    }
    recievemsg();
    if(msgstr=="Give Password")
    {
        sendmsg(qstrtostr(password));
    }
    recievemsg();
    if(msgstr=="UserName already exists")
    {
        ui->statusBar->showMessage("UserName alredy exists!", 2000);
        qDebug() << "UserName already exists!";
        clearLineEdits();
        return;
    }
    else if(msgstr=="Registered")
    {
        ui->statusBar->showMessage("Successfully Registered...Login to Continue!", 2000);
        qDebug() << "Successfully Registered...Login to Continue!";

    }
    clearLineEdits();
}

void MainWindow::on_logInButton_clicked()
{
    QString userName = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    sendmsg("Login");
    recievemsg();
    if(msgstr=="Give Username")
    {
        sendmsg(qstrtostr(userName));
    }
    recievemsg();
    if(msgstr=="Give Password")
    {
        sendmsg(qstrtostr(password));
    }
    //sendmsg(qstrtostr(userName));
    //sendmsg(qstrtostr(password));
    //msg = userName.toUtf8().constData();
    //write(sockfd,msg,sizeof(msg));
    //msg = password.toUtf8().constData();
    //write(sockfd,msg,sizeof(msg));
    recievemsg();
    if(msgstr=="Successful Login")
    {
        this->hide();
        loggedInWindow = new loginSuccessWindow();
        loggedInWindow->username = qstrtostr(userName);
        loggedInWindow->setWelcomeMessage();
        loggedInWindow->show();
        ui->statusBar->showMessage("Successful Login!", 2000);
        qDebug()<<"Successgul login!";
    }
    else if(msgstr=="Incorrect password")
    {
        ui->statusBar->showMessage("Incorrect Password!", 2000);
        qDebug()<<"Incorrect Password!";
    }
    else if(msgstr=="No such user")
    {
        ui->statusBar->showMessage("No such user exist!", 2000);
        qDebug()<<"No such user exist!";
    }
    clearLineEdits();
}

void MainWindow::on_connectButton_clicked()
{
    if(ui->connectButton->text()=="CONNECT")
    {
        QString ip_addr_qstr = ui->lineEdit_7->text();
        string ip_addr1 = ip_addr_qstr.toUtf8().constData();
        ip_addr = ip_addr1.c_str();
        QString port_qstr = ui->lineEdit_8->text();
        string port_str1 = port_qstr.toUtf8().constData();
        const char* port_str = port_str1.c_str();
        portNumber = atoi(port_str);
        if(connectS(ip_addr)==0)
        {

            qDebug()<<"server Connection established!";
            ui->statusBar->showMessage("Connection Established.",2000);
            ui->connectButton->setText("DISCONNECT");
            ssl = SSL_new(ctx);      /* create new SSL connection state */
            SSL_set_fd(ssl, sockfd);    /* attach the socket descriptor */

            if ( SSL_connect(ssl) == FAIL )   /* perform the connection */
            ERR_print_errors_fp(stderr);

            ShowCerts(ssl);
        }
        else
        {
            ui->statusBar->showMessage("Connection Failed!!!",2000);
            qDebug()<<"Connection failed!!!";
        }

    }
    else
    {
        sendmsg("Disconnect");
        ui->connectButton->setText("CONNECT");
    }
    clearLineEdits();
}
