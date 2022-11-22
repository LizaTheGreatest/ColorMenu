//#include "mainwindow.h"
#include "searchfilter.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    SearchFilter w;
    w.show();
    return a.exec();
}
