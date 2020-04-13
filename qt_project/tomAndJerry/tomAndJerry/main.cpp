#include <QCoreApplication>
#include <QDebug>

#include "tom.h"
#include "jerry.h"

void test()
{
    Tom tom;
    Jerry jerry;

    //QObject::connect(tom, Tom::siglMaio, jerry, Jerry::slot_RunAway());
    //QObject::connect(&tom, SIGNAL(&Tom::siglMaio), &jerry, SLOT(&Jerry::slot_RunAway)); //ERROR QObject::connect: Parentheses expected
    QObject::connect(&tom, SIGNAL(&Tom::sigl_Miao), &jerry, SLOT(&Jerry::slot_RunAway()));
    tom.miaoW();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() <<  "Hello World!";
    test();

    return a.exec();
}
