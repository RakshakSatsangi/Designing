#include "directorydialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    directoryDialog w;
    w.show();
    
    return a.exec();
}
