#include "mainwindow.h"
#include <QFileDialog>
#include <QApplication>
#include <QtWidgets>
#include "Histogram.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.showMaximized();
    w.show();


    return a.exec();
}
