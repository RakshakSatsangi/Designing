#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream> // for converting int to string
#include <string>
#include <sys/stat.h>
#include <dirent.h>
#include <resolv.h>
#include "openssl/ssl.h"
#include "openssl/err.h"
#include <malloc.h>

#define FAIL    -1

using namespace std;

const char* fileName = "database.txt";
int listenfd = 0;
    int connfd = 0;
    struct sockaddr_in serv_addr;
    char recvBuff[256];
    char sendBuff[1025];
    int bytesReceived = 0;
    int numrv;

    char message[256];
    string msgstr;

SSL* ssl;

SSL_CTX* InitServerCTX(void)
{   SSL_METHOD *method;
    SSL_CTX *ctx;

    OpenSSL_add_all_algorithms();  /* load & register all cryptos, etc. */
    SSL_load_error_strings();   /* load all error messages */ /* create new server-method instance */
    ctx = SSL_CTX_new(SSLv3_server_method());   /* create new context from method */
    if ( ctx == NULL )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}

void LoadCertificates(SSL_CTX* ctx, char* CertFile, char* KeyFile)
{
    /* set the local certificate from CertFile */
    if ( SSL_CTX_use_certificate_file(ctx, CertFile, SSL_FILETYPE_PEM) <= 0 )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    /* set the private key from KeyFile (may be the same as CertFile) */
    if ( SSL_CTX_use_PrivateKey_file(ctx, KeyFile, SSL_FILETYPE_PEM) <= 0 )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    /* verify private key */
    if ( !SSL_CTX_check_private_key(ctx) )
    {
        fprintf(stderr, "Private key does not match the public certificate\n");
        abort();
    }
}

void ShowCerts(SSL* ssl)
{   X509 *cert;
    char *line;

    cert = SSL_get_peer_certificate(ssl); /* Get certificates (if available) */
    if ( cert != NULL )
    {
        printf("Server certificates:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("Subject: %s\n", line);
        free(line);
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("Issuer: %s\n", line);
        free(line);
        X509_free(cert);
    }
    else
        printf("No certificates.\n");
}


int get_file_size(std::string filename) // path to file
{
    FILE *p_file = NULL;
    p_file = fopen(filename.c_str(),"rb");
    fseek(p_file,0,SEEK_END);
    int size = ftell(p_file);
    fclose(p_file);
    return size;
}

string getFilename(string path)
{
	int indexSlash=0;
	for(int i=0; i<path.length(); i++)
	{
		if(path[i]=='/')
		{
			indexSlash = i+1;
		}
	}
	string filename;
	for(int i=indexSlash; i<path.length(); i++)
	{
		filename+=path[i];
	}
	return filename;
}

char* stringtocharp(string s)
{
	char* aux=new char [s.size()+1];
	int i;
	for(i=0;i<s.size();i++)
	{
		aux[i]=s[i];
	}
	aux[i] = '\0';
	return aux;
}

void recievemsg()
{
	char x[256]={0};
	//memset(x, '0', sizeof(x));
    int readb=SSL_read(ssl,x,256);
    while(readb<0)
    {
        readb=SSL_read(ssl,x,256);
        //cout<<"error reading"<<endl;\
        exit(0);
    }
    //cout<<"Bytes recieved"<<readb<<endl;
    
    msgstr=x;
    #ifdef DEBUG
    cout<<"Message recieved: "<<msgstr<<endl;
    #endif
}
void sendmsg(string str)
{
	//for(int i=0;i<1000000;i++)
	//{
	//	int abc=3;
	//}
	char* abc = stringtocharp(str);
    int bsent=SSL_write(ssl,abc,str.size());
	while(bsent<0)
	{
        bsent = SSL_write(ssl,abc,str.size());
		//cout<<"Writing......"<<endl;
	}

	//cout<<"bytes sent: "<<bsent<<endl;
	#ifdef DEBUG
	cout<<"message sent: "<<abc<<endl;
	#endif
	
}

bool checkUserName(string UserName, string* password){
    ifstream myFile;
    myFile.open(fileName, std::ifstream::in);
    string tmp;
    while(myFile.good()){
        myFile >> tmp;
        if(tmp==UserName){
            myFile >> (*password);
            return true;
        }
        myFile>>tmp;
    }
    myFile.close();

    return false;

}

void give_users_list()
{
    ifstream myFile;
    myFile.open(fileName, std::ifstream::in);
    string tmp;
    myFile >> tmp;
    while(!myFile.eof()){

        sendmsg(tmp);
        recievemsg();
        myFile>>tmp;
        myFile >> tmp;


    }
    sendmsg(("/No More Users/"));
    myFile.close();

}

void getDirSturc(char* foldname)
{
    recievemsg();
    if(msgstr=="Is Dir Null")
    {
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir (foldname)) != NULL) {
            sendmsg("Dir Not Null");
     
   	       string parent = ".";
    	        string root = "..";
            while(1)
            {
                recievemsg();
                if(msgstr=="Is Dir Completed")
                {

                    ent = readdir(dir);
                    if(ent==NULL)
                    {
                        
                        sendmsg("Dir Completed");
                        break;
                    }
                    else if(ent->d_name==parent || ent->d_name==root)
                    {
                        
                        sendmsg("parent/root");
                        continue;
                    }
                    else
                    {
                        
                        sendmsg(ent->d_name);
                        char * subfold = new char[256];
                        string foldname_str = foldname;
                        string slash_str = "/";
                        string ent_str = ent->d_name;
                        string subfold_str = foldname_str + slash_str + ent_str;
                        strcpy(subfold, subfold_str.c_str());
                        getDirSturc(subfold);
                    }

                }
            }
            closedir (dir);
        }
        else
        {
            closedir (dir);
            sendmsg("Dir Null");
        }
    }

}

void getSharedStruc(char* dir_name)
{

    cout<<"================Shared struct begins..."<<endl;

    DIR *dir;
    struct dirent *ent;
    dir = opendir(dir_name);
    ent = readdir(dir); // parent .
    ent = readdir(dir); // root ..
    while(1)
    {
        recievemsg();
        if(msgstr=="Is Dir Completed")
        {

            ent = readdir(dir);
            if(ent==NULL)
            {
                sendmsg("Dir Completed");
                break;
            }
            else
            {
                sendmsg(ent->d_name);
                recievemsg();
                ifstream myFile;
                string str_path(dir_name);
                str_path+='/';
                str_path+=ent->d_name;
                str_path+="/shared_files.txt";
                cout<<str_path<<endl;
                myFile.open(str_path.c_str(), std::ifstream::in);
                char* tmp = new char[256]; // check...path can't be larger than 256 characters
                myFile.getline(tmp,256);
                while(!myFile.eof()){
                    cout<<"reading from file:"<<tmp<<endl;
                    string tmp_str(tmp);
                    sendmsg(tmp_str);
                    recievemsg();
                    myFile.getline(tmp,256);
                }
                myFile.close();
                sendmsg(("/No More Files/"));

                // for folders
                recievemsg();
                //ifstream myFile;
                string str_path1(dir_name);
                str_path1+='/';
                str_path1+=ent->d_name;
                str_path1+="/shared_folders.txt";
                cout<<str_path1<<endl;
                myFile.open(str_path1.c_str(), std::ifstream::in);
                char* tmp1 = new char[256]; // check...path can't be larger than 256 characters
                myFile.getline(tmp1,256);
                while(!myFile.eof()){

                    string tmp_str(tmp1);
                    sendmsg(tmp_str);

                    getDirSturc(tmp1);
                    recievemsg();

                    myFile.getline(tmp1,256);
                }
                myFile.close();
                sendmsg(("/No More Folders/"));
            }

        }
    }
    closedir (dir);

    cout<<"================Shared struct ends..."<<endl;

}

void getPublicStruc()
{
    cout<<"================Public struct begins..."<<endl;
    //recievemsg();
    ifstream myFile;
    myFile.open(fileName, std::ifstream::in);
    char* tmp = new char[256]; // check...username can't be larger than 256 characters
    myFile.getline(tmp,256);
    while(!myFile.eof()){



        
        string tmp_str(tmp);
        sendmsg(tmp_str);
        myFile.getline(tmp,256);
        myFile.getline(tmp,256);
        recievemsg();

        ifstream myFile1;
        string str_path = tmp_str+"/Public_files/public_files.txt";
        cout<<str_path<<endl;
        FILE * fp = fopen(str_path.c_str(),"r");
        if (fp==NULL)
        {
            sendmsg(("/No More Files/"));
            continue;
        }

        myFile1.open(str_path.c_str(), std::ifstream::in);

        char* tmp1 = new char[256]; // check...path can't be larger than 256 characters
        //myFile1.getline(tmp1,256);
        while(!myFile1.eof()){
            myFile1.getline(tmp1,256);
            string str_tmp(tmp1);
            sendmsg(str_tmp);
            recievemsg();

        }
        sendmsg(("/No More Files/"));
        myFile1.close();




    }
    sendmsg(("/No More Users/"));
    myFile.close();

    cout<<"================Public struct ends..."<<endl;

}


void remove_dir(char *path)
{
        struct dirent *entry = NULL;
        DIR *dir = NULL;
        dir = opendir(path);
        while(entry = readdir(dir))
        {
                DIR *sub_dir = NULL;
                FILE *file = NULL;
                char abs_path[100] = {0};
                if(*(entry->d_name) != '.')
                {
                        sprintf(abs_path, "%s/%s", path, entry->d_name);
                        if(sub_dir = opendir(abs_path))
                        {
                                closedir(sub_dir);
                                remove_dir(abs_path);
                        }
                        else
                        {
                                if(file = fopen(abs_path, "r"))
                                {
                                        fclose(file);
                                        remove(abs_path);
                                }
                        }
                }
        }
        remove(path);
}


void remove_file (char* path)
{
  if( remove( path ) != 0 )
    perror( "Error deleting file" );
  else
    puts( "File successfully deleted" );
}

void Login()
{
	#ifdef DEBUG
    cout<<"Logging in"<<endl;
    #endif
    sendmsg("Give Username");
    recievemsg();
    string usern=msgstr;
    sendmsg("Give Password");
    recievemsg();
    string passent=msgstr;
    string passw;
    if(checkUserName(usern,&passw))
    {
    	
    	
    	if(passw==passent)
    	{
    		#ifdef DEBUG
    		cout<<"Successful Login"<<endl;
    		#endif
    		sendmsg("Successful Login");
            getDirSturc(stringtocharp(usern));
            getSharedStruc(stringtocharp(usern + "/Shared_files"));
            getPublicStruc();
    		// continue
    	}
    	else
    	{
    		#ifdef DEBUG
    		cout<<"Incorrect password"<<endl;
    		#endif
    		sendmsg("Incorrect password");
    		// convey
    	}
    }
    else
    {
    	sendmsg("No such user");
    	#ifdef DEBUG
    	cout<<"UserName does not exist"<<endl;
    	#endif
    }

}

void Signup()
{
    sendmsg("Give Username");
    recievemsg();
    string usern=msgstr;
    sendmsg("Give Password");
    recievemsg();
    string passw;
    string passent=msgstr;
    if(!checkUserName(usern,&passw))
    {
    	
    	ofstream myFile;
    	myFile.open(fileName, ios::app);
    	
    	myFile << usern << endl;
        myFile << passent << endl;
        myFile.close();
    	//for(int i=0;i<1000000;i++)
    	//{
        //	int xyz=3;
    	//}
    	sendmsg("Registered");
    	mkdir(usern.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        string shared_path = usern+"/Shared_files";
        mkdir(shared_path.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        string public_path = usern +"/Public_files";
        mkdir(public_path.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);


    	//
    }
    else
    {
    	sendmsg("UserName already exists");
    	//
    }
}
void rcvFilefromClient(string filename)
{
    recievemsg();
    if(msgstr=="File Opening Error")
    {
        sendmsg("OK. Rerturning");
        return;
    }


	FILE *fp;
	cout<<"filename: "<<filename<<endl;
	#ifdef DEBUG
	cout<<filename.c_str()<<endl;
	#endif
    fp = fopen(filename.c_str(), "wb");
    cout<<"recieving file"<<endl;

    if(fp == NULL)
    {
        sendmsg("Cannot Open File On Server");
        cout<<"Error opening file"<<endl;
        return;
    }
    else
    {
        sendmsg("OK. Send Me File");
    }

	//sendmsg("Send Buffer");
    bytesReceived = SSL_read(ssl, recvBuff, 256);
    /* Receive data in chunks of 256 bytes */
    while(bytesReceived == 256)
    {
        fwrite(recvBuff, 1,bytesReceived,fp);
        bytesReceived = SSL_read(ssl, recvBuff, 256);
    }
    fwrite(recvBuff, 1,bytesReceived,fp);
    if(bytesReceived < 0)
    {
        printf("\n Read Error \n");
    }
	fclose(fp);

}

void sendFiletoClient(string filename)
{
    //cout<<"sending file"<<endl;
    FILE *fp = fopen(filename.c_str(),"rb");
    //cout<<"sending file"<<endl;

    if(fp==NULL)
    {
        cout<<"File Opening Error"<<endl;
        sendmsg("File Opening Error");
        recievemsg();
        return;
    }
    //cout<<"File SIZE: "<< get_file_size(filename)<<endl;
    int filesize = get_file_size(filename);
    stringstream filesize_str;
    filesize_str << filesize;
    sendmsg(filesize_str.str());
    recievemsg();
    //cout<<"sending file"<<endl;

    while(1)
    {
        /* First read file in chunks of 256 bytes */
        unsigned char buff[256]={0};
        //cout<<"sending file"<<endl;
        int nread = fread(buff,1,256,fp);

        /* If read was success, send data. */
        if(nread >= 0)
        {
                SSL_write(ssl, buff, nread);
        }

        /*
        * There is something tricky going on with read ..
        * Either there was error, or we reached end of file.
        */
        if (nread < 256)
        {
            if (feof(fp))
                printf("End of file\n");
            if (ferror(fp))
                printf("Error reading\n");
            break;
        }
    }
    cout<<"file sent!!!"<<endl;

}

void share_public(string path)
{
    string username="";
    int i=0;
    while(1)
    {
        if(path[i]=='/')
            break;
        username+=path[i];
        i++;
    }
    string fileCreated = username+"/Public_files/public_files.txt";
    ofstream myFile;
    myFile.open(fileCreated.c_str(), ios::app);
    myFile<<path<<endl;
    myFile.close();

}

void share_specific(string specific_user, string path)
{
    string username="";
    int i=0;
    while(1)
    {
        if(path[i]=='/')
            break;
        username+=path[i];
        i++;
    }
    sendmsg("Folder Or File?");
    recievemsg();
    string fileCreated = specific_user+"/Shared_files/"+username;
    mkdir(fileCreated.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if(msgstr=="Folder")
    {
        fileCreated+="/shared_folders.txt";
    }
    else
    {
        fileCreated+="/shared_files.txt";
    }
    ofstream myFile;
    myFile.open(fileCreated.c_str(), ios::app);
    myFile<<path<<endl;
    myFile.close();
    sendmsg("Shared!");
}

int main(int argc,char *argv[])
{
    int pid;
    SSL_CTX *ctx;

    SSL_library_init();

    ctx = InitServerCTX();        /* initialize SSL */
    LoadCertificates(ctx, "mycert.pem", "mycert.pem"); /* load certs */

    memset(message, '0', sizeof(message));
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    printf("Socket retrieve success\n");

    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    int yes=1;

    // lose the pesky "Address already in use" error message
    if (setsockopt(listenfd, SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
    perror("setsockopt");
    exit(1);
    }
    else
    {
        printf("done \n");
    }

    int abc=bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
    if(abc==-1)
    {
        printf("bad port");
        exit(1);
    }


    if(listen(listenfd, 10) == -1)
    {
        printf("Failed to listen\n");
        return -1;
    }


    while(1)
    {
    	cout<<"while(1)"<<endl;
        connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL);
        cout<<"connection establish"<<endl;
        ssl=SSL_new(ctx);
        SSL_set_fd(ssl,connfd);
        if ( SSL_accept(ssl) == FAIL )     /* do SSL-protocol accept */
        {
            cout<<"SSL_accept(ssl)==FAIL"<<endl;
            ERR_print_errors_fp(stderr);
            break;
        }
        pid=fork();
        if(pid==0)
        {
            close(listenfd);
            int sd;



            ShowCerts(ssl);        /* get any certificates */



            while(1)
            {
                recievemsg();
                if(msgstr=="Login")
                {
                    cout<<"msgstr==Login"<<endl;
                    Login();
                }
                else if(msgstr=="Signup")
                {
                    Signup();
                }
                else if(msgstr=="Upload")
                {
                    sendmsg("Give Filepath");
                    recievemsg();
                    cout<<msgstr<<endl;
                    rcvFilefromClient(msgstr);
                }
                else if(msgstr == "Download")
                {
                    sendmsg("Send File Name");
                    recievemsg();
                    cout<<"File path"<<msgstr<<endl;
                    sendFiletoClient(msgstr);

                }
                else if(msgstr=="Create Folder")
                {
                    sendmsg("Send Path");
                    recievemsg();

                    if(mkdir(msgstr.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)<0)
                        sendmsg("Error Creating Directory");
                    else
                        sendmsg("Directory Successfully Created");

                }
                else if(msgstr=="Logout Now")
                {
                    continue;
                }
                else if(msgstr=="Delete File")
                {
                    sendmsg("Send Path");
                    recievemsg();
                    remove_file(stringtocharp(msgstr));
                }
                else if(msgstr=="Delete Folder")
                {
                    sendmsg("Send Path");
                    recievemsg();
                    remove_dir(stringtocharp(msgstr));
                }
                else if(msgstr=="Give Users List")
                {
                    give_users_list();
                }
                else if(msgstr=="Share With Public")
                {
                    sendmsg("Send Path");
                    recievemsg();
                    share_public(msgstr);
                }
                else if(msgstr=="Share With Specific User")
                {
                    sendmsg("Send Specific User");
                    recievemsg();
                    string specific_user = msgstr;
                    sendmsg("Send Path");
                    recievemsg();
                    share_specific(specific_user,msgstr);
                }
                else if(msgstr=="Refresh")
                {
                    sendmsg("Give Username");
                    recievemsg();
                    string username_rcvd = msgstr;
                    sendmsg("Username Recieved");
                    getDirSturc(stringtocharp(username_rcvd));
                    getSharedStruc(stringtocharp(username_rcvd + "/Shared_files"));
                    getPublicStruc();

                }
                else
                {break;} // no connection found
            }
            sd=SSL_get_fd(ssl);
            SSL_free(ssl);
            close(sd);
            exit(0);


        }



        else
        {
            SSL_free(ssl);
            close(connfd);
        }

        

        sleep(1);

    }
    close(listenfd);
    SSL_CTX_free(ctx);

    return 0;

}
//openssl req -x509 -nodes -days 365 -newkey rsa:1024 -keyout mycert.pem -out mycert.pem
// gcc -o ssl-server SSL-Server.c -L/usr/lib -lssl -lcrypto
