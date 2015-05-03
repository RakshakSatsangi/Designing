#include "loginsuccesswindow.h"
#include "sharedialog.h"

#include "mainwindow.h"
#include "enternamedialog.h"
#include "askdialog.h"
#include <QString>
#include <iostream>
#include <QDebug>
MainWindow * w1;

int get_file_size(std::string filename) // path to file
{
    FILE *p_file = NULL;
    p_file = fopen(filename.c_str(),"rb");
    fseek(p_file,0,SEEK_END);
    int size = ftell(p_file);
    fclose(p_file);
    return size;
}


QString getFilenameLessExt(QString path)
{
    int indexdot=0;
    for(int i=0; i<path.length(); i++)
    {
        if(path[i]=='.')
        {
            indexdot = i+1;
            break;
        }
    }
    QString filename;
    for(int i=0; i<indexdot-1; i++)
    {
        filename+=path[i];
    }
    return filename;
}

QString getFileExt(QString path)
{
    int indexdot=0;
    for(int i=0; i<path.length(); i++)
    {
        if(path[i]=='.')
        {
            indexdot = i+1;
            break;
        }
    }
    QString filename;
    for(int i=indexdot-1; i<path.length(); i++)
    {
        filename+=path[i];
    }
    return filename;
}

QString getFilename(QString path)
{
    int indexSlash=0;
    for(int i=0; i<path.length(); i++)
    {
        if(path[i]=='/')
        {
            indexSlash = i+1;
        }
    }
    QString filename;
    for(int i=indexSlash; i<path.length(); i++)
    {
        filename+=path[i];
    }
    return filename;
}

void loginSuccessWindow::sendFileC2S(string filename)
{
    cout<<"=======sending file to server begins"<<endl;
    //cout<<"sending file"<<endl;
    FILE *fp = fopen(filename.c_str(),"rb");
    //cout<<"sending file"<<endl;
    int filesize;
    if(fp==NULL)
    {
        sendmsg("File Opening Error");
        recievemsg();
        cout<<"File opening error"<<endl;
        return;
    }
    else
    {
        sendmsg("File Opened Successfully");
        recievemsg();
        if(msgstr=="Cannot Open File On Server")
        {
            return;
        }
        filesize= get_file_size(filename);
        ui->progressBar->setMaximum(filesize);
        //stringstream filesize_str;
        //filesize_str << filesize;
    }
    //cout<<"sending file"<<endl;
    int filesize_rcvd=0;
    ui->progressBar->setValue(filesize_rcvd);
    while(1)
    {
        /* First read file in chunks of 256 bytes */
        unsigned char buff[256]={0};
        //cout<<"sending file"<<endl;
        int nread = fread(buff,1,256,fp);

        //cout<<nread<<endl;
        //printf("Bytes read %d \n", nread);

        /* If read was success, send data. */
        if(nread >= 0)
        {
            filesize_rcvd+=256;
            ui->progressBar->setValue(filesize_rcvd);
            //recievemsg();
            //if(msgstr=="Send Buffer")
            //{
                SSL_write(ssl, buff, nread);
                //cout<<"sending file"<<endl;
            //}
        }

        /*
        * There is something tricky going on with read ..
        * Either there was error, or we reached end of file.
        */
        if (nread < 256)
        {
            if (feof(fp))
            {
                ui->progressBar->setValue(filesize);
                printf("End of file\n");
            }
            if (ferror(fp))
                printf("Error reading\n");
            break;
        }
    }
    cout<<"=========file sent to server!!!"<<endl;

}

void loginSuccessWindow::rcvFilefromServer(string filename)
{
    cout<<"===============recieving file from server begins"<<endl;
    recievemsg();
    if(msgstr=="File Opening Error")
    {
        sendmsg("OK. Returning...");
        cout<<"File reading error at server. File might have been deleted on server"<<endl;
        ui->statusbar->showMessage("File reading error at server. File might have been deleted on server",2000);
        return;
    }
    else
    {
        int filesize = atoi(msgstr.c_str());
        cout<<"FILE SIZE: "<< filesize<<endl;

        ui->progressBar->setMaximum(filesize);
        sendmsg("Cool! Send me then!");
    }
    FILE *fp;
    cout<<"filename: "<<filename<<endl;
    cout<<filename.c_str()<<endl;
    fp = fopen(filename.c_str(), "wb");
    cout<<"recieving file"<<endl;
    int filesize_rcvd = 0;
    ui->progressBar->setValue(filesize_rcvd);

    if(fp == NULL)
    {
        cout<<"Error opening file"<<endl;
        return;
    }

    //sendmsg("Send Buffer");
    bytesReceived = SSL_read(ssl, recvBuff, 256);
    /* Receive data in chunks of 256 bytes */
    while(bytesReceived == 256)
    {

        //printf("Bytes received %d\n",bytesReceived);
        // recvBuff[n] = 0;
        //cout<<"recvBuff: "<<recvBuff<<endl;
        fwrite(recvBuff, 1,bytesReceived,fp);
        filesize_rcvd+=bytesReceived;
        ui->progressBar->setValue(filesize_rcvd);
        //cout<<"next bytesReceived: ";
        //sendmsg("Send Buffer");
        bytesReceived = SSL_read(ssl, recvBuff, 256);

        //cout<<bytesReceived<<endl;
        // printf("%s \n", recvBuff);
    }
    //printf("Bytes received %d\n",bytesReceived);
    // recvBuff[n] = 0;
    //cout<<"recvBuff: "<<recvBuff<<endl;
    fwrite(recvBuff, 1,bytesReceived,fp);
    filesize_rcvd+=bytesReceived;
    ui->progressBar->setValue(filesize_rcvd);


    if(bytesReceived < 0)
    {
        printf("\n Read Error \n");
    }

    fclose(fp);
    cout<<"===============recieving file from server ends"<<endl;
}
void getDirSturc(QTreeWidgetItem * root_item)
{
    sendmsg("Is Dir Null");
    recievemsg();
    if (msgstr == "Dir Not Null") {
        root_item->setText(1,"Folder");
        QList<QTreeWidgetItem*> items;

        /* print all the files and directories within directory */
        while (1) {
            sendmsg("Is Dir Completed");
            recievemsg();
            if(msgstr=="Dir Completed")
            {
                cout<<"No more files/folder.."<<endl;
                break;
            }
            else if(msgstr=="parent/root")
            {
                continue;
            }

            else
            {
                //msgstr will give the ent->d_name
                QTreeWidgetItem * item = new QTreeWidgetItem;
                QString msgstr_qstr = msgstr.c_str();
                item->setText(0, msgstr_qstr);\
                item->setText(2,root_item->text(2)+"/"+msgstr_qstr);
                items.push_back(item);
                getDirSturc(item);
            }


        }
        root_item->addChildren(items);
    }
    else
    {
        root_item->setText(1,"File");
    }
}

void deleteDatabaseFiles(QTreeWidgetItem * root_item)
{
    cout<<"======root_item child count======: "<<root_item->childCount()<<endl;
    for(int i=0; i<root_item->childCount(); i++)
    {
        if(root_item->child(i)->text(0)=="Shared_files")
            delete root_item->child(i);
    }
    cout<<"======root_item child count======: "<<root_item->childCount()<<endl;
    for(int i=0; i<root_item->childCount(); i++)
    {
        if(root_item->child(i)->text(0)=="Public_files")
            delete root_item->child(i);
    }
}

void getSharedStruc(QTreeWidgetItem * root_item)
{
    cout<<"====================shared Struc starts"<<endl;
    QList<QTreeWidgetItem*> items;
    while (1) {
        sendmsg("Is Dir Completed");
        recievemsg();
        if(msgstr=="Dir Completed")
        {
            cout<<"No more files/folder.."<<endl;
            break;
        }
        else
        {
            //msgstr will give the ent->d_name
            QTreeWidgetItem * item = new QTreeWidgetItem;
            QString msgstr_qstr = msgstr.c_str();
            item->setText(0, msgstr_qstr);
            item->setText(1,"Folder");


            sendmsg("Give Files List");
            while(1)
            {
                recievemsg();
                if(msgstr=="/No More Files/")
                {
                    break;
                }
                else
                {
                    QTreeWidgetItem * new_file_item = new QTreeWidgetItem;
                    new_file_item->setText(2,msgstr.c_str());
                    new_file_item->setText(1,"File");
                    int i=msgstr.length()-1;
                    string file_rcvd;
                    while(1)
                    {
                        if(msgstr[i]=='/')
                            break;
                        file_rcvd = msgstr[i]+file_rcvd;
                        i--;
                    }
                    new_file_item->setText(0,QString::fromStdString(file_rcvd));

                    sendmsg("File Item Recieved");
                    item->addChild(new_file_item);
                }
            }
            sendmsg("Give Folders List");
            while(1)
            {
                recievemsg();
                if(msgstr=="/No More Folders/")
                {
                    break;
                }
                else
                {
                    QTreeWidgetItem * new_folder_item = new QTreeWidgetItem;
                    new_folder_item->setText(2,msgstr.c_str());
                    new_folder_item->setText(1,"Folder");
                    int i=msgstr.length()-1;
                    string file_rcvd;
                    while(1)
                    {
                        if(msgstr[i]=='/')
                            break;
                        file_rcvd = msgstr[i]+file_rcvd;
                        i--;
                    }
                    new_folder_item->setText(0,QString::fromStdString(file_rcvd));


                    getDirSturc(new_folder_item);
                    sendmsg("Folder Item Recieved");
                    item->addChild(new_folder_item);
                }
            }
            items.push_back(item);
        }
    }
    root_item->addChildren(items);
    cout<<"====================shared Struc ends"<<endl;
}

void getPublicStruc(QTreeWidgetItem * root_item)
{
    cout<<"============public struc begins"<<endl;
    QList<QTreeWidgetItem*> items;
    //sendmsg("Give Users List");
    while(1)
    {
        recievemsg();
        if(msgstr=="/No More Users/")
        {
            break;
        }
        else
        {
            QTreeWidgetItem * new_user_item = new QTreeWidgetItem;
            new_user_item->setText(0,QString::fromStdString(msgstr));

            sendmsg("Give Files List");
            while(1)
            {
                recievemsg();
                if(msgstr=="/No More Files/")
                {
                    break;
                }
                else
                {
                    QTreeWidgetItem * new_file_item = new QTreeWidgetItem;
                    new_file_item->setText(2,QString::fromStdString(msgstr));
                    new_file_item->setText(1,"File");
                    int i=msgstr.length()-1;
                    string file_rcvd;
                    while(1)
                    {
                        if(msgstr[i]=='/')
                            break;
                        file_rcvd = msgstr[i]+file_rcvd;
                        i--;
                    }
                    new_file_item->setText(0,QString::fromStdString(file_rcvd));

                    new_user_item->addChild(new_file_item);
                    sendmsg("File Item Recieved");
                }
            }
            items.push_back(new_user_item);

        }
    }
    cout<<"items length: "<<items.length()<<endl;
    root_item->addChildren(items);
    cout<<"============public struc ends"<<endl;
}


string loginSuccessWindow::getFilePath(QTreeWidgetItem * item)
{
    cout<<"========get File path begins"<<endl;
    if(item->text(0)=="/root")
        return this->username;
    string path = qstrtostr(item->text(0));
    item = item->parent();
    //cout<<path<<endl;
    while(item->text(0)!="/root")
    {
        //cout<<"pasjsaksasa "<<path<<endl;
        path = qstrtostr(item->text(0)) +"/"+ path;
        item=item->parent();
    }
    path = this->username + "/"+path;


    cout<<path<<endl;
    cout<<"========get File path ends"<<endl;
    return path;

}

string loginSuccessWindow::getFilePath_1(QTreeWidgetItem * item)
{
    cout<<"========get File path_1 begins"<<endl;
    if(item->text(0)=="Shared_files")
        return "Shared_files";
    string path = qstrtostr(item->text(0));
    item = item->parent();
    //cout<<path<<endl;
    while(item->text(0)!="Shared_files")
    {
        //cout<<"pasjsaksasa "<<path<<endl;
        path = qstrtostr(item->text(0)) +"/"+ path;
        item=item->parent();
    }
    path = "Shared_files/"+path;


    cout<<path<<endl;
    cout<<"========get File path_1 ends"<<endl;
    return path;
}

void MakeDirectories(string str)
{
    cout<<"==========Make Directory begins"<<endl;
    vector<int> indexslashes;
    for(int i=0;i<str.length();i++)
    {
        if(str[i]=='/')
        {
            indexslashes.push_back(i+1);
        }

    }
    vector<string> names;
    for(int i=0;i<indexslashes.size();i++)
    {
        string tempst;
        for(int j=0; j<indexslashes[i]; j++)
        {
            tempst+=str[j];
        }
        names.push_back(tempst);
    }
    for(int i=0;i<names.size();i++)
    {
        cout<<"Creating directory :"<<names[i]<<endl;
        if(mkdir(names[i].c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)<0)
        {
            cout<<"error making directory"<<endl;
        }
    }
    cout<<"==========Make Directory ends"<<endl;
}

void loginSuccessWindow::hideOtherButtons()
{
    ui->uploadButton->hide();
    ui->dldButton->hide();
    ui->createFolderButton->hide();
    ui->deleteButton->hide();
    ui->shareButton->hide();
    ui->openButton->hide();
    ui->uploadNewEditionButton->hide();
}
void loginSuccessWindow::showAllButtons()
{
    ui->uploadButton->show();
    ui->dldButton->show();
    ui->createFolderButton->show();
    ui->deleteButton->show();
    ui->shareButton->show();
    ui->openButton->show();
    ui->uploadNewEditionButton->show();
}

void loginSuccessWindow::setWelcomeMessage()
{
    string welcome = "Hi, "+ this->username;
    ui->welcomeLabel->setText(QString::fromStdString(welcome));
}


loginSuccessWindow::loginSuccessWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::loginSuccessWindow)
{
    ui->setupUi(this);
    this->on_myfileradioButton_clicked();
    ui->progressBar->hide();
    hideOtherButtons();
    //QTreeWidgetItem * root_item = new QTreeWidgetItem;
    //root_item->setText(0,"root");
    root_item_permanent = ui->dirTreeWidget->topLevelItem(0);
    getDirSturc(this->root_item_permanent);
    deleteDatabaseFiles(this->root_item_permanent);
    getSharedStruc(ui->sharedTreeWidget->topLevelItem(0));
    getPublicStruc(ui->publicTreeWidget->topLevelItem(0));
    //getPublicStruc();
    qDebug()<<"struct ends...";
    //ui->dirTreeWidget->addTopLevelItem(root_item);
    QPixmap bkgnd("./download.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
        palette.setBrush(QPalette::Background, bkgnd);
        this->setPalette(palette);

}

loginSuccessWindow::~loginSuccessWindow()
{
    delete ui;
}


void loginSuccessWindow::on_uploadButton_clicked()
{
    QTreeWidgetItem * newFile= new QTreeWidgetItem;
    QTreeWidgetItem * selItem = ui->dirTreeWidget->currentItem();

    QString filename_qstr = QFileDialog::getOpenFileName(
                this,
                tr("Upload File"),
                "LocalFolder",
                "All Files(*.*)"
                );
    if(filename_qstr==NULL)
    {
        QMessageBox::information(this, tr("File Name"), "No File Selected!" );
        return;
    }
    ui->progressBar->show();
    QMessageBox::information(this, tr("File Name"), filename_qstr);
    // Either this if you use UTF-8 anywhere
    std::string filename = filename_qstr.toUtf8().constData();
    std::cout<< filename;
    newFile->setText(0,getFilename(filename_qstr));
    newFile->setText(1,"File");
    if(selItem->text(1)=="Folder")
    {
        ui->dirTreeWidget->currentItem()->addChild(newFile);
    }
    else
    {
        ui->dirTreeWidget->currentItem()->parent()->addChild(newFile);
    }

    sendmsg("Upload");
    recievemsg();

    if(msgstr=="Give Filepath")
    {
        sendmsg(getFilePath(newFile));
        sendFileC2S(filename);
      //  getDirSturc(ui->dirTreeWidget->topLevelItem(0));
    }
    //sleep(1);
    ui->progressBar->hide();


}

void loginSuccessWindow::downloadFile(string path ,string recv_path)
{
    sendmsg("Download");
    recievemsg();
    if(msgstr=="Send File Name")
    {
        sendmsg(path);
        /*
        string recv_path;
        if(mode == 0)
        {
            recv_path = "ClientDownloads/"+path;
        }

        else if(mode == 1)
        {
            sendmsg(path);
            string file_to_rcv;
            int i=path.length()-1;
            while(1)
            {
                if(path[i]=='/')
                {
                    break;
                }
                file_to_rcv = path[i] + file_to_rcv;
                i--;
            }
            i=0;
            string source_user;
            while(1)
            {
                if(path_to_send[i]=='/')
                {
                    break;
                }
                source_user+=path_to_send[i];
                i++;
            }
            this->lastDownloadLocation = "ClientDownloads/Shared_files/"+source_user+"/"+file_to_rcv;
            recv_path = this->lastDownloadLocation;
        }*/
        MakeDirectories(recv_path);
        rcvFilefromServer(recv_path);
        //??????????????
    }

}

void loginSuccessWindow::downloadFolder(QTreeWidgetItem* folder_item, string path, string recv_path)
{
    if(folder_item->childCount()==0)
    {
        MakeDirectories(recv_path);
        mkdir(recv_path.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
    for(int i=0; i<folder_item->childCount(); i++)
    {
        string add_path = "/"+qstrtostr(folder_item->child(i)->text(0));
        if(folder_item->child(i)->text(1)=="File")
        {
            downloadFile(path+add_path, recv_path+add_path);
        }
        else
        {
            downloadFolder(folder_item->child(i), path+add_path, recv_path+add_path);
        }
    }
}

void loginSuccessWindow::on_dldButton_clicked()
{
    ui->progressBar->show();

    if(ui->myfileradioButton->isChecked())
    {
        this->lastDownloadLocation = getFilePath(ui->dirTreeWidget->currentItem());
        if(ui->dirTreeWidget->currentItem()->text(1)=="Folder")
        {
            downloadFolder(ui->dirTreeWidget->currentItem(), this->lastDownloadLocation, "ClientDownloads/"+this->lastDownloadLocation);
        }
        else
        {
            downloadFile(this->lastDownloadLocation, "ClientDownloads/"+this->lastDownloadLocation);
        }
        this->lastDownloadLocation = "ClientDownloads/"+this->lastDownloadLocation;
        ui->statusbar->showMessage("Download Complete!", 2000);
        //QList<QTreeWidgetItem*> selItems = ui->dirTreeWidget->selectedItems();


        //for(int i=0; i<selItems.length(); i++)
        //{
        //    recievemsg();
        //    if(msgstr=="Send File Name") // also make it for folder
        //    {
        //        string path = getFilePath(selItems.at(i));
        //        path = this->username + "/" + path;
        //        sendmsg(path);
        //        recievemsg();
        //    }
        //}
        //ui->dirTreeWidget->SelectedClicked
    }
    else if(ui->sharedradioButton->isChecked())
    {
        /*
        if(ui->sharedTreeWidget->currentItem()->text(1)=="Folder")
        {
            ui->statusbar->showMessage("Cannot Download a Folder", 2000);
            return;
        }
        sendmsg("Download");
        recievemsg();
        if(msgstr=="Send File Name")
        {
        */
            //string path = getFilePath(ui->sharedTreeWidget->currentItem(););
            //string path1 = this->username + "/" + path;
            string path_to_send = qstrtostr(ui->sharedTreeWidget->currentItem()->text(2));
            string file_to_rcv = getFilePath_1(ui->sharedTreeWidget->currentItem()); // get file path of this
            /*sendmsg(path_to_send);
            int i=0;
            string source_user;
            while(1)
            {
                if(path_to_send[i]=='/')
                {
                    break;
                }
                source_user+=path_to_send[i];
                i++;
            }
            */
            //this->lastDownloadLocation = "ClientDownloads/Shared_files/"+source_user+"/"+file_to_rcv;
            this->lastDownloadLocation = "ClientDownloads/"+file_to_rcv;


            if(ui->sharedTreeWidget->currentItem()->text(1)=="Folder")
            {
                downloadFolder(ui->sharedTreeWidget->currentItem(), path_to_send, this->lastDownloadLocation);
            }
            else
            {
                downloadFile(path_to_send, this->lastDownloadLocation);
            }
            //MakeDirectories(this->lastDownloadLocation);
            //rcvFilefromServer(this->lastDownloadLocation);
            //??????????????
        //}
        ui->statusbar->showMessage("Download Complete!", 2000);
    }
    else if(ui->publicradioButton->isChecked())
    {
        if(ui->publicTreeWidget->currentItem()->text(1)=="Folder")
        {
            ui->statusbar->showMessage("Cannot Download a Folder", 2000);
            return;
        }
        sendmsg("Download");
        recievemsg();
        if(msgstr=="Send File Name")
        {
            //string path = getFilePath(ui->sharedTreeWidget->currentItem(););
            //string path1 = this->username + "/" + path;
            string path_to_send = qstrtostr(ui->publicTreeWidget->currentItem()->text(2));
            string file_to_rcv = qstrtostr(ui->publicTreeWidget->currentItem()->text(0));
            sendmsg(path_to_send);
            int i=0;
            string source_user;
            while(1)
            {
                if(path_to_send[i]=='/')
                {
                    break;
                }
                source_user+=path_to_send[i];
                i++;
            }
            this->lastDownloadLocation = "ClientDownloads/Public_files/"+source_user+"/"+file_to_rcv;
            MakeDirectories(this->lastDownloadLocation);
            rcvFilefromServer(this->lastDownloadLocation);
            //??????????????
        }
        ui->statusbar->showMessage("Download Complete!", 2000);
    }
    //sleep(1);
    ui->progressBar->hide();

}

void loginSuccessWindow::on_dirTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    // show all the options/actions possible for an item
    showAllButtons();
}

void loginSuccessWindow::on_sharedTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    bool a = true;
    if(ui->sharedTreeWidget->currentItem()==ui->sharedTreeWidget->topLevelItem(0))
    {
        a = false;
        hideOtherButtons();
        return;
    }
    for(int i=0; i<ui->sharedTreeWidget->topLevelItem(0)->childCount(); i++)
    {
        if(ui->sharedTreeWidget->currentItem()==ui->sharedTreeWidget->topLevelItem(0)->child(i))
        {
            a = false;
            break;
        }
    }
    if(a)
    {
        ui->dldButton->show();
        ui->openButton->show();
    }
    else
    {
        hideOtherButtons();
    }
}

void loginSuccessWindow::on_publicTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    bool a = true;
    if(ui->publicTreeWidget->currentItem()==ui->publicTreeWidget->topLevelItem(0))
    {
        a = false;
        hideOtherButtons();
        return;
    }
    for(int i=0; i<ui->publicTreeWidget->topLevelItem(0)->childCount(); i++)
    {
        if(ui->publicTreeWidget->currentItem()==ui->publicTreeWidget->topLevelItem(0)->child(i))
        {
            a = false;
            break;
        }
    }
    if(a)
    {
        ui->dldButton->show();
        ui->openButton->show();
    }
    else
    {
        hideOtherButtons();
    }
}

bool checkForSlash(string s)
{
    for(int i=0; i<s.length(); i++)
    {
        if(s[i]=='/')
        {
            return true;
        }
    }
    return false;
}

void loginSuccessWindow::on_createFolderButton_clicked()
{
    QTreeWidgetItem * location;
    if(ui->dirTreeWidget->currentItem()->text(1)=="Folder")
    {
        location = ui->dirTreeWidget->currentItem();
    }
    else
    {
        location = ui->dirTreeWidget->currentItem()->parent();
    }
    //QTreeWidgetItem * newfolderItem;
    QString name_entered;
    bool a = true;
    //int index_newfolder;
    while(a)
    {
        enterNameDialog * enterName = new enterNameDialog;
        enterName->setModal(true);
        enterName->exec();
        if(enterName->isCancelled)
            return;
        name_entered = enterName->entry;
        qDebug()<< name_entered;
        cout<<qstrtostr(name_entered)<<endl;
        if(name_entered=="")
        {
            ui->statusbar->showMessage("Please Enter Something",2000);
            continue;
        }
        if(checkForSlash(qstrtostr(name_entered)))
            continue;

        a = false;
        for(int i=0; i<location->childCount(); i++)
        {
            if(location->child(i)->text(0)==name_entered && location->child(i)->text(1)=="Folder")
            {
                qDebug()<<"folder name already exists!!!";
                ui->statusbar->showMessage("folder name already exists!", 2000);
                a = true;
                break;
            }
        }
    }

    sendmsg("Create Folder");
    recievemsg();
    if(msgstr=="Send Path")
    {
        QTreeWidgetItem * new_folder_item = new QTreeWidgetItem;
        new_folder_item->setText(0,name_entered);
        new_folder_item->setText(1,"Folder");
        location->addChild(new_folder_item);
        string path = getFilePath(new_folder_item);
        sendmsg(path);
        recievemsg();
        if(msgstr=="Error Creating Directory")
        {
            delete new_folder_item;
            cout<<location->childCount()<<endl;
            qDebug()<<"Error Creating Folder";
            ui->statusbar->showMessage("Error Creating Folder",2000);
            return;
        }
        else if(msgstr=="Directory Successfully Created")
        {

            qDebug()<<"Folder Successfully Created";
            ui->statusbar->showMessage("Folder Successfully Created",2000);
        }
    }
    /*
    hideOtherButtons(ui->createFolderButton);
    if(ui->createFolderButton->text()=="Create Folder")
    {
        //string path;
        //path = getFilePath(ui->dirTreeWidget->currentItem()->parent());
        QTreeWidgetItem * newFolder = new QTreeWidgetItem;
        newFolder->setText(0,"New Folder");
        newFolder->setText(1,"Folder");
        if(ui->dirTreeWidget->currentItem()->text(1)=="Folder")
        {
            ui->dirTreeWidget->currentItem()->addChild(newFolder);
        }
        else
        {
            ui->dirTreeWidget->currentItem()->parent()->addChild(newFolder);
        }
        ui->lineEdit->show();
        ui->lineEdit->setPlaceholderText("New Folder");
        //ui->lineEdit->setText("New Folder");
        //ui->lineEdit->selectAll();
        //ui->lineEdit->cursor();

        ui->createFolderButton->setText("OK");
    }
    else if(ui->createFolderButton->text()=="OK")
    {
        QTreeWidgetItem * newfolderItem;
        QString folder_name;
        int index_newfolder;
        if(ui->lineEdit->text()==NULL)
        {
            folder_name = ui->lineEdit->placeholderText();
        }
        else
        {
            folder_name = ui->lineEdit->text();
        }
        QTreeWidgetItem * location;
        if(ui->dirTreeWidget->currentItem()->text(1)=="Folder")
        {
            location = ui->dirTreeWidget->currentItem();
        }
        else
        {
            location = ui->dirTreeWidget->currentItem()->parent();
        }
        for(int i=0; i<location->childCount(); i++)
        {
            if(location->child(i)->text(0)==folder_name && location->child(i)->text(1)=="Folder")
            {
                qDebug()<<"folder name already exists!!!";
                ui->statusbar->showMessage("folder name already exists!", 2000);
                return;
            }
        }
        index_newfolder=location->childCount()-1;
        newfolderItem = location->child(index_newfolder);
        newfolderItem->setText(0,folder_name);
        sendmsg("Create Folder");
        recievemsg();
        if(msgstr=="Send Path")
        {
            string path = this->username +"/"+ getFilePath(newfolderItem);
            sendmsg(path);
        }


        ui->lineEdit->setText(NULL);
        ui->lineEdit->hide();
        ui->createFolderButton->setText("Create Folder");
        showAllButtons();
    }
    */
}


void loginSuccessWindow::on_logoutButton_clicked()
{
    sendmsg("Logout Now");
    this->hide();
    w1 = new MainWindow;
    w1->show();
    //SSL_free(ssl);
}

void loginSuccessWindow::on_deleteButton_clicked()
{
    if(ui->dirTreeWidget->currentItem()->text(0)=="/root")
    {
        qDebug()<<"Cannot Delete root";
        ui->statusbar->showMessage("cannpt delete root", 2000);
        return;
    }
    if(ui->dirTreeWidget->currentItem()->text(1)=="File")
    {
        sendmsg("Delete File");

    }
    else
    {
        sendmsg("Delete Folder");
    }
    recievemsg();
    string path = getFilePath(ui->dirTreeWidget->currentItem());
    sendmsg(path);
    ui->dirTreeWidget->currentItem()->parent()->removeChild(ui->dirTreeWidget->currentItem());
    ui->statusbar->showMessage("Deleted!!!", 2000);

}

void loginSuccessWindow::on_myfileradioButton_clicked()
{
    ui->dirTreeWidget->show();
    ui->sharedTreeWidget->hide();
    ui->publicTreeWidget->hide();
    hideOtherButtons();
    ui->label->show();
    ui->lineEdit->show();
}

void loginSuccessWindow::on_sharedradioButton_clicked()
{
    ui->dirTreeWidget->hide();
    ui->sharedTreeWidget->show();
    ui->publicTreeWidget->hide();
    hideOtherButtons();
    ui->label->hide();
    ui->lineEdit->hide();
}

void loginSuccessWindow::on_publicradioButton_clicked()
{
    ui->dirTreeWidget->hide();
    ui->sharedTreeWidget->hide();
    ui->publicTreeWidget->show();
    hideOtherButtons();
    ui->label->hide();
    ui->lineEdit->hide();
}

void loginSuccessWindow::on_shareButton_clicked()
{
    /*
    if(ui->dirTreeWidget->currentItem()->text(1)=="Folder")
    {
        cout<<"Please select a file. To share a folder first compress it!"<<endl;
        ui->statusbar->showMessage("Please select a file. To share a folder first compress it!", 2000);
        return;
    }
    */
    shareDialog_obj = new shareDialog;
    if(ui->dirTreeWidget->currentItem()->text(1)=="Folder")
        shareDialog_obj->isFolder = true;
    string s_str = getFilePath(ui->dirTreeWidget->currentItem());
    QString s_qstr = QString::fromStdString(s_str);
    shareDialog_obj->showSharingFileName(s_qstr);
    shareDialog_obj->username=this->username;
    shareDialog_obj->populateListWidget();
    shareDialog_obj->setModal(true);
    shareDialog_obj->exec();
    cout<<"working"<<endl;
}




void loginSuccessWindow::on_uploadNewEditionButton_clicked()
{
    QTreeWidgetItem * newFile= new QTreeWidgetItem;
    QTreeWidgetItem * selItem = ui->dirTreeWidget->currentItem();

    QString filename_qstr = QFileDialog::getOpenFileName(
                this,
                tr("Upload File"),
                "LocalFolder",
                "All Files(*.*)"
                );
    if(filename_qstr==NULL)
    {
        QMessageBox::information(this, tr("File Name"), "No File Selected!" );
        return;
    }
    ui->progressBar->show();
    QMessageBox::information(this, tr("File Name"), filename_qstr);
    // Either this if you use UTF-8 anywhere
    std::string filename = filename_qstr.toUtf8().constData();

    std::cout<< filename;
    QString auxstr=getFilename(filename_qstr);
    QString filess=auxstr;
    newFile->setText(0,getFilename(filename_qstr));
    newFile->setText(1,"File");
    if(selItem->text(1)=="Folder")
    {
        int ab=1;
        bool isExist=1;
        while(isExist==1)
        {
            isExist=0;
            for(int y=0;y<(ui->dirTreeWidget->currentItem()->childCount());y++)
            {
                if(ui->dirTreeWidget->currentItem()->child(y)->text(0)==auxstr&&ui->dirTreeWidget->currentItem()->child(y)->text(1)=="File")
                {
                    isExist=1;
                    break;
                }
            }
            if(isExist==1)
            {
                auxstr=getFilenameLessExt(filess)+"_edited("+QVariant(ab).toString()+")"+getFileExt(filess);
                ab++;
            }
        }
        newFile->setText(0,auxstr);

        ui->dirTreeWidget->currentItem()->addChild(newFile);
    }
    else
    {
        int ab=1;
        bool isExist=1;
        while(isExist==1)
        {
            isExist=0;
            for(int y=0;y<(ui->dirTreeWidget->currentItem()->parent()->childCount());y++)
            {
                if(ui->dirTreeWidget->currentItem()->parent()->child(y)->text(0)==auxstr&&ui->dirTreeWidget->currentItem()->parent()->child(y)->text(1)=="File")
                {
                    isExist=1;
                    break;
                }
            }
            if(isExist==1)
            {
                auxstr=getFilenameLessExt(filess)+"_edited("+QVariant(ab).toString()+")"+getFileExt(filess);
                ab++;
            }
        }
        newFile->setText(0,auxstr);



        ui->dirTreeWidget->currentItem()->parent()->addChild(newFile);
    }

    sendmsg("Upload");
    recievemsg();

    if(msgstr=="Give Filepath")
    {
        sendmsg(getFilePath(newFile));
        sendFileC2S(filename);
      //  getDirSturc(ui->dirTreeWidget->topLevelItem(0));
    }
    //sleep(1);
    ui->progressBar->hide();

}

void loginSuccessWindow::on_refreshButton_clicked()
{
    sendmsg("Refresh");
    recievemsg();
    if(msgstr=="Give Username")
    {
        sendmsg(this->username);
        recievemsg();
        loginSuccessWindow * loggedInWindow1;
        loggedInWindow1 = new loginSuccessWindow();
        loggedInWindow1->username = (this->username);
        loggedInWindow1->setWelcomeMessage();
        loggedInWindow1->show();
        this->close();

        /*
        //this->on_myfileradioButton_clicked();
        hideOtherButtons();

        getDirSturc(ui->dirTreeWidget->topLevelItem(0));
        deleteDatabaseFiles(this->root_item_permanent);
        getSharedStruc(ui->sharedTreeWidget->topLevelItem(0));
        getPublicStruc(ui->publicTreeWidget->topLevelItem(0));
        */

    }
    /*cout<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    loginSuccessWindow * loggedInWindow1;
    loggedInWindow1 = new loginSuccessWindow();
    loggedInWindow1->username = (this->username);
    this->hide();
    loggedInWindow1->show();

    this->on_myfileradioButton_clicked();
    hideOtherButtons();
    //ui->lineEdit->hide();
    //QTreeWidgetItem * root_item = new QTreeWidgetItem;
    //root_item->setText(0,"root");

    getDirSturc(ui->dirTreeWidget->topLevelItem(0));
    getSharedStruc(ui->sharedTreeWidget->topLevelItem(0));
    getPublicStruc(ui->publicTreeWidget->topLevelItem(0));
    */
}

void loginSuccessWindow::on_openButton_clicked()
{
    this->on_dldButton_clicked();
    string cmd =  "xdg-open "+this->lastDownloadLocation;
    system(cmd.c_str()); // for folder it opens the last downloaded file!! correct it!!
}

void searchitem(QTreeWidgetItem * fold,const QString &arg11)
{
    for(int i=fold->childCount()-1;i>=0;i--)
    {
        if(fold->child(i)->text(0).contains(arg11,Qt::CaseInsensitive))
        {
            fold->child(i)->setSelected(1);
            fold->child(i)->setHidden(0);
        }
        else
        {
            fold->child(i)->setHidden(1);
        }
    }
}


void loginSuccessWindow::on_lineEdit_textEdited(const QString &arg1)
{
    if(ui->dirTreeWidget->currentItem()->text(1)=="File")
        {
            searchitem(ui->dirTreeWidget->currentItem()->parent(),arg1);
        }
        else
        {
            searchitem(ui->dirTreeWidget->currentItem(),arg1);
        }
}

void loginSuccessWindow::on_SyncButton_clicked()
{
    ui->dirTreeWidget->setCurrentItem(ui->dirTreeWidget->topLevelItem(0));
    this->on_dldButton_clicked();
}
