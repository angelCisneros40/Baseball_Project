#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // clearOutputFile();
    testReadToWriteFile();
    printOutputTxt();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    return 0;
}
