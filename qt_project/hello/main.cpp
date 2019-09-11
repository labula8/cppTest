#include "mainwindow.h"
#include <QApplication>

#include <iostream>

using namespace std;

int t_main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

int main(int argc, char *argv[])
{
    /*
    return t_main(argc, argv);
    */
    cout << "Hello" << endl;
    cout << "argc=" << argc << endl;
    cout << "argv=" << argv[0] << endl;

    return 0;
}
