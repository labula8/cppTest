#include <QtCore/QCoreApplication>

//#include <qdebug.h>
#include <QDebug>
#include <QString>
#include <QVector>
#include <QList>
#include <QStack>
#include <QQueue>
#include <QSet>
#include <QMap>
#include <QMultiMap>
#include <QHash>
#include <QMultiHash>

void show_list(QList<QString>& list)
{
	qDebug() << "List size=" << list.size();
	for (int i = 0; i < list.size(); ++i) {
		qDebug() << "List[" << i << "]" << list.at(i);
	}
}
void t_list()
{
	QList <QString> list;
	list << "aa" << "bb" << "cc";

	show_list(list);

	if ("bb" == list[1]) {
		list[1] = "ab";
		show_list(list);
	}

	list.replace(2, "bc");
	show_list(list);

	list.append("dd");
	show_list(list);

	list.prepend("mm");
	show_list(list);

	QString str = list.takeAt(2);
	qDebug() << "after take at(2) item :" << str;
	show_list(list);

	list.insert(2, "mm");
	qDebug() << "after insert(2, \"mm\")";
	show_list(list);

	list.swap(1, 3);
	qDebug() << "after swap(1, 3)";
	show_list(list);

	qDebug() << "contains mm ?" << list.contains("mm");
	qDebug() << "the mm counts:" << list.count("mm");
	qDebug() << "the first mm index:" << list.indexOf("mm");
	qDebug() << "indexOf(\"mm\", 1) the second mm index:" << list.indexOf("mm", 1);
	qDebug() << "indexOf(\"mm\", 2) the second mm index:" << list.indexOf("mm", 2);
	qDebug() << "indexOf(\"mm\", 3) the second mm index:" << list.indexOf("mm", 3);
}

void show_map(QMap<QString, int> &map)
{
	qDebug() << "Map size=" << map.size();
	for (QMap<QString, int>::iterator it = map.begin(); it != map.end(); ++it) {
		QString first = it.key();
		int second = it.value();
		qDebug() << "Map[" << first << "]" << second;
	}
}
void t_map()
{
	QMap<QString, int> map;
	map["one"] = 1;
	map["three"] = 3;
	show_map(map);

	map.insert("seven", 7);
	qDebug() << "after insert(\"seven\", 7)";
	show_map(map);
}

void t_pt()
{
	char ch1 = 'a';
	char ch2 = 'b';
	char ch3 = 'c';
	char ch4 = 'd';

	//����ָ�룬ָ������ָ��
	//ָ�볣����ָ��Ϊ������ָ��λ�ò��ܸ��£�ָ��ָ�����ݿ��޸�

	const  char* pCh1 = &ch1;//�����޸�ָ�룬ָ�����ݵ�����,�����޸�ָ��ָ���ĵط�->����ָ��
	//*pCh1 = '1';
	pCh1 = &ch2;
	//const* char ch11 = &ch1;
	char * const pCh2 = &ch2;//�����޸�ָ��ָ���ĵط��������޸�ָ�����ݵ�����-��ָ�볣��
	//pCh2 = pCh1;
	*pCh2 = '2';
	char   const * pCh3 = &ch3;//�ȼ��� char  * const  pCh3 = &ch3��ָ�볣��
	//*pCh3 = '3';//error
	pCh3 = &ch2;
	const char* const pCh4 = &ch4;//�����޸�ָ�룬ָ���ĵط���Ҳ���ܣ��޸�ָ�����ݵ����ݡ�����ָ������ָ�볣��
	//pCh4 = pCh1;
	//*pCh4 = '4';

	printf("Ch1=[%x, %c]\n", &ch1, ch1);
	printf("Ch2=[%x, %c]\n", &ch2, ch2);
	printf("Ch3=[%x, %c]\n", &ch3, ch3);
	printf("Ch4=[%x, %c]\n", &ch4, ch4);

	printf("pCh1=[%x, %c]\n", pCh1, *pCh1);
	printf("pCh2=[%x, %c]\n", pCh2, *pCh2);
	printf("pCh3=[%x, %c]\n", pCh3, *pCh3);
	printf("pCh4=[%x, %c]\n", pCh4, *pCh4);
}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	qDebug() << "Hello!";

	//t_list();
	//t_map();
	t_pt();

	qDebug() << "End";

	return a.exec();
}
