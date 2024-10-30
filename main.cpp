#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet("QStatusBar::item {border: 0px solid black};");
    MainWindow w;
    w.show();
    return a.exec();
}
