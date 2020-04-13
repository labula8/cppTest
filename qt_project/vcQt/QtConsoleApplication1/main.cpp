#include <QtCore/QCoreApplication>
#include <qdebug.h>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	qDebug() << "Hello!";
	return a.exec();
}
