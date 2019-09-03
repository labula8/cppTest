//multimap�����ظ��ļ�ֵ��������
//        **********************************************************    
//        * pairֻ����һ����ֵ:pair<int,char>                       *
//        * map��һ���������ͣ���Զ�����ź���ģ�                   *
//  pair  * mapÿһ����Ա����һ��pair,���磺map<int,char>           *
//        * map��insert()���԰�һ��pair������Ϊmap�Ĳ���,����map<p> *
//        ***********************************************************
//#pragma warning(disable:4786)
#include <map>
#include <iostream>
using namespace std;

int main(void)
{
    multimap<int,char*> m;
    //multimap�Ĳ���ֻ����insert()����������
    m.insert(pair<int,char*>(1,"apple"));
    m.insert(pair<int,char*>(1,"pear"));//apple��pear�ļ�Ǯ��ȫ�п�����һ����
    m.insert(pair<int,char*>(2,"banana"));
    
    //multimap�ı���ֻ���õ�������ʽ����������
    std::cout<<"***************************************"<<std::endl;
    multimap<int,char*>::iterator i,iend;
    iend=m.end();
    for(i=m.begin();i!=iend;i++)
    {
        std::cout << (*i).second << "�ļ�Ǯ��" << (*i).first << "Ԫ/��" << std::endl;
    }
    std::cout<<"***************************************"<<std::endl;
    
    //Ԫ�صķ������
    multimap<int,char*>::reverse_iterator j,jend;
    jend=m.rend();
    for(j=m.rbegin(); j!=jend; j++)
    {
        std::cout<<(*j).second<<"�ļ�Ǯ��" <<(*j).first<<"Ԫ/��" << std::endl;
    }
    std::cout<<"***************************************"<<std::endl;
    
    //Ԫ�ص�����find(),pair<iterator,iterator>equal_range(const key_type &k)const
    //��multiset���÷�һ��
    multimap<int,char*>::iterator s;
    s=m.find(1);//find()ֻҪ�ҵ�һ�������ˣ�Ȼ���������ء�
    std::cout << (*s).second << "    " << (*s).first << std::endl;
    std::cout << "��ֵ����1��Ԫ�ظ����� " << m.count(1) << std::endl;
    std::cout << "��ֵ����2��Ԫ�ظ����� " << m.count(2) << std::endl;
    std::cout << "��ֵ����3��Ԫ�ظ����� " << m.count(3) << std::endl;
    std::cout << "***************************************" << std::endl;
    
    //ɾ�� erase(),clear()
    std::cout << "m.size=" << m.size() << std::endl;
    m.erase(1);
    //m.erase(2);
    std::cout << "m.size=" << m.size() << std::endl;
    for(i=m.begin();i!=iend;i++)
    {
        std::cout << (*i).second << "�ļ�Ǯ��" << (*i).first << "Ԫ/��" << std::endl;
    }
    std::cout << "m.size=" << m.size() << std::endl;
    
    return 0;
}