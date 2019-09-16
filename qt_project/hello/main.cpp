#include <iostream>
#include <vector>

#include "mainwindow.h"
#include <QApplication>

#include <QLabel>
#include <QPushButton>


using namespace std;

int t_main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

void t_label()
{
    QLabel *label = new QLabel("Hello, Yu");
    label->show();
}

void t_button(QApplication &app)
{
    QPushButton *button = new QPushButton("Quit");

    //定义按钮消息绑定
    QObject::connect(button, SIGNAL(clicked()), &app, SLOT(quit()));

    button->show();
}

int t_my_main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //t_label();
    t_button(app);

    return app.exec();
}

int t_console(int argc, char *argv[])
{
    cout << "Hello" << endl;
    cout << "argc=" << argc << endl;
    cout << "argv=" << argv[0] << endl;

    auto a = 888;
    cout << "a=" << a << endl;
    vector<int> vec = {1, 2, 8, 4, 5};
    for (auto elem : vec) {
        cout << "elem=" << elem << endl;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    //int ret = t_main(argc, argv);
    //int ret = t_my_main(argc, argv);
    t_console(argc, argv);

    /*
    return t_main(argc, argv);
    */

    return 0;
}
