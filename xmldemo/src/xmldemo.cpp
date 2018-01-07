#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>

#define ID_STR_LEN        16
#define NAME_STR_LEN         32
#define TEL_STR_LEN         16
#define ADDR_STR_LEN         128

#ifndef SAFE_DELETE
#define SAFE_DELETE(x) { if(x) { delete (x); (x) = NULL; } }
#endif

#ifndef SAFE_FREE_DOC
#define SAFE_FREE_DOC(x) { if(x) { xmlFreeDoc(x); (x) = NULL; } }
#endif

using namespace std;

//电话通讯录结构体
typedef struct phone_t {
	int id;              //编号
	char name[NAME_STR_LEN];     //姓名
	char tel[TEL_STR_LEN];       //电话
	char address[ADDR_STR_LEN];  //地址
}phone;

bool new_xmldoc(const xmlChar * doc_name, xmlDocPtr doc)
{
        //创建一个xml 文档
        doc = xmlNewDoc(doc_name);
        if (doc == NULL)
        {
                fprintf(stderr, "Failed to new doc.\n");
                return false;
        }

	printf("%s, ok.\n", __FUNCTION__);

        return true;
}

//设置通讯录项
void set_phone_item(phone *phone_item)
{
	cout << __FUNCTION__ << endl;

	assert(phone_item);

	phone_item->id = 10;
	snprintf(phone_item->name, NAME_STR_LEN, "%s", "Anker");
	snprintf(phone_item->tel, TEL_STR_LEN, "%s", "13223246599");
	snprintf(phone_item->address, ADDR_STR_LEN, "%s", "Shenzheng");
}

//创建phone节点
xmlNodePtr create_phone_node(const phone *phone_item)
{
	assert(phone_item);
	
	char id[ID_STR_LEN] = {0};
	xmlNodePtr phone_node = NULL;
	
	phone_node = xmlNewNode(NULL, BAD_CAST"phone");
	if (phone_node == NULL) {
	fprintf(stderr, "Failed to create new node.\n");
	return NULL;
	}
	//设置属性
	snprintf(id, ID_STR_LEN, "%d", phone_item->id);
	xmlNewProp(phone_node, BAD_CAST"id", (xmlChar*)id);

	xmlNewChild(phone_node, NULL, BAD_CAST"name", (xmlChar *)phone_item->name);
	xmlNewChild(phone_node, NULL, BAD_CAST"tel", (xmlChar *)phone_item->tel);
	xmlNewChild(phone_node, NULL, BAD_CAST"address", (xmlChar *)phone_item->address);

	return phone_node;
}

//向根节点中添加一个phone节点
int add_phone_node_to_root(xmlNodePtr root_node)
{
	cout << __FUNCTION__ << endl;

	xmlNodePtr phone_node = NULL;
	phone *phone_item = NULL;

	//创建一个新的phone
	phone_item = (phone *)malloc(sizeof(phone));
	if (phone_item == NULL) {
		fprintf(stderr, "Failed to malloc memory.\n");
		return -1;
	}
	set_phone_item(phone_item);

	//创建一个phone节点
	phone_node = create_phone_node(phone_item); 
	if (phone_node == NULL) {
		fprintf(stderr, "Failed to create phone node.\n");
		if (phone_item) {
			free(phone_item);
		}
		return -1;
	}

	//根节点添加一个子节点
	xmlAddChild(root_node, phone_node);
	SAFE_DELETE(phone_item);

	return 0;
}

//创建phone_books
int create_phone_books(const char *phone_book_file)
{
	cout << __FUNCTION__ << endl;
	cout << "phone_book_file: " << phone_book_file << endl;

	assert(phone_book_file);

	xmlDocPtr doc = NULL;
	xmlNodePtr root_node = NULL;

	//创建一个xml 文档
	xmlChar* doc_name = BAD_CAST"1.0";	
	if(!new_xmldoc( doc_name, doc))
	{
		return -1;
	}

	//创建根节点
	root_node = xmlNewNode(NULL, BAD_CAST"phone_books");
	if (root_node == NULL) {
		fprintf(stderr, "Failed to new root node.\n");
		SAFE_FREE_DOC(doc);
		return -1;
	}
	//将根节点添加到文档中
	xmlDocSetRootElement(doc, root_node);

	if (add_phone_node_to_root(root_node) != 0) {
		fprintf(stderr, "Failed to add a new phone node.\n");
		SAFE_FREE_DOC(doc);
		return -1;
	}
	//将文档保存到文件中，按照utf-8编码格式保存
	xmlSaveFormatFileEnc(phone_book_file, doc, "UTF-8", 1);
	//xmlSaveFile("test.xml", doc);
	SAFE_FREE_DOC(doc);

	return 0; 
}

int add_phone_node(const char *phone_book_file)
{
	assert(phone_book_file);

	xmlDocPtr doc = NULL;
	xmlNodePtr root_node = NULL;
	xmlNodePtr phone_node = NULL;
	phone *phone_item = NULL;
	
	doc = xmlParseFile(phone_book_file);
	if (doc == NULL) {
		fprintf(stderr, "Failed to parser xml file:%s\n", phone_book_file);
		return -1;
	}

	root_node = xmlDocGetRootElement(doc);
	if (root_node == NULL) {
		fprintf(stderr, "Failed to get root node.\n");
		SAFE_FREE_DOC(doc);
		return -1;
	}
	
	if (add_phone_node_to_root(root_node) != 0) {
		fprintf(stderr, "Failed to add a new phone node.\n");
		SAFE_FREE_DOC(doc);
		return -1;
	}
	//将文档保存到文件中，按照utf-8编码格式保存
	xmlSaveFormatFileEnc(phone_book_file, doc, "UTF-8", 1);
	SAFE_FREE_DOC(doc);

	return 0;
}




int main(int argc, char *argv[])
{

	//std::string sTemp = (char*)(BAD_CAST"1.2");
	//std::cout << sTemp << std::endl;
	//return 0;
	
	std::string phone_book_file = "phone_book.xml";

	if (argc == 2) {
		phone_book_file = argv[1];
	}

	if (access(phone_book_file.c_str(), F_OK) == 0) {
		//文件存在，添加一个新的phone节点
		add_phone_node(phone_book_file.c_str());
	}
	else {
		//文件不存在，创建一个信息的phone book
		int ret = create_phone_books(phone_book_file.c_str());
		cout << "ret: " << ret << endl;
	}

	return 0;
}


/*
int main()
{
	cout << "hello!" << endl;
	return 0;
}
*/
