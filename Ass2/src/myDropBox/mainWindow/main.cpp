#include "mainwindow.h"
#include <QApplication>
#include "loginsuccesswindow.h"
#include "global.h"
#include "sharedialog.h"
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    mkdir("ClientDownloads",S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    SSL_library_init();
    ctx=InitCTX();


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
