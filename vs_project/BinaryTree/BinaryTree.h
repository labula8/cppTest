#pragma once 

#include <stack>
#include <assert.h>
#include <queue>
#include <map>
#include <iostream>

//#define _DEBUG

using namespace std;

//定义一个二叉树节点
template<typename T>
struct BinaryTreeNode {
    int _index;  //下标
	T _data;    //数据
	BinaryTreeNode<T> *_left;//左孩子
	BinaryTreeNode<T> *_right;//右孩子
    BinaryTreeNode<T> *_father;//父节点

	BinaryTreeNode(const T& x)//节点的构造函数
		:_index(0),_data(x)
		, _left(NULL)
		, _right(NULL) {}
};

//定义二叉树
template<typename T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;//重命名为Node

public:

	BinaryTree() :_root(NULL) {}
	BinaryTree(T* arr, const size_t size,const T& invalid = T()) {
		assert(arr);
		size_t index = 0;
		_root = CreateTree(arr, size, index, invalid);
	}

    BinaryTree(T* arr, const size_t size, int arr_edge_index[][2], const size_t edge_size, const T& invalid = T()) {
        assert(arr);
        size_t index = 0;
        _root = createBtree(arr, size, index, arr_edge_index, edge_size, invalid);
    }

	//拷贝构造函数
	BinaryTree(const BinaryTree& b) {
		_root = Copy(b._root);
	}

	//赋值运算符重载
	BinaryTree&operator=(BinaryTree t) {
		if (this != &t) {
			std::swap(t._root, _root);
		}
		return *this;
	}

	//析构函数
	~BinaryTree() {
		if (_root != NULL) {
			Destory(_root);
			_root = NULL;
		}
	}

	//先序遍历，中序遍历，后序遍历
	void PrevOrder() {
        cout << "前：" << __FUNCTION__ << endl;
		//采用递归方法，调用protected内部的_PrevOrder函数，中序和后序也是一样
		_PrevOrder(_root);
		cout << endl;
	}
	void InOrder() {
        cout << "中："  << __FUNCTION__ << endl;
		_InOrder(_root);
		cout << endl;
	}
	void PostOrder() {
        cout << "后：" << __FUNCTION__ << endl;
		_PostOrder(_root);
		cout << endl;
	}

	//三种遍历方式的非递归形式
	void PrevOrderNonR() {
        cout << "前：" << __FUNCTION__ << endl;
		//定义一个栈和一个指针变量
		stack<Node*> s;
		Node* cur = _root;

		//在cur,或者栈为空时
		while (cur || !s.empty()) {
			//递归遍历左字数
			while (cur) {
				//访问元素
				cout << cur->_data << " ";
				
				//进行压栈
				s.push(cur);
				
				//指向左孩子
				cur = cur->_left;
			}
			//一路向左，此时cur为空

			//取栈顶元素
			Node* top = s.top();
			//出栈
			s.pop();
			//访问右孩子
			cur = top->_right;
		}
		cout << endl;
	}

	//中序遍历的非递归，只用把压栈访问元素的位置改到出栈的时候访问即可
	void InOrderNonR() {
        cout << "中：" << __FUNCTION__ << endl;
		//定义一个栈和指针变量cur
		Node* cur = _root;
		stack<Node*> s;

		//判断是否结束
		while (cur || !s.empty()) {
			//循环压入左字数
			while (cur) {
				s.push(cur);

				//中序，先不要访问元素
				cur = cur->_left;
			}
			Node* top = s.top();
			s.pop();

			//此时再访问元素
			cout << top->_data << " ";
			cur = top->_right;
		}
        cout << endl;
	}

	//后序非递归遍历
	void PostOrderNonR() {
        cout << "后：" << __FUNCTION__ << endl;
		//与中序，先序相比，多定义了一个prev指针，保存上一个访问的元素
		Node* prev = NULL;

		//定义一个栈s和指向节点的临时变量cur
		Node* cur = _root;
		stack<Node*> s;

		//判断是否结束
		while (cur || !s.empty()) {
			//递归压入左子树
			while (cur) {
				//依旧不访问元素
				s.push(cur);
				cur = cur->_left;
			}

			//取栈顶元素进行判断
			Node* top = s.top();

			//如果站定元素的右子树为空  或者  右子树已经被访问
			if (top->_right == NULL || top->_right == prev)	{
				//打印根
				cout << top->_data << " ";
				
				//将刚刚访问过的元素让prev保存起来
				prev = top;

				//出栈
				s.pop();
			}
			//右子树不为空 并且 还没有被访问
			else
			{
				//访问右字数
				cur = top->_right;
			}
		}
        cout << endl;
	}

	//层序遍历
	void LevelOrder() {
        cout << "层：" << __FUNCTION__ << endl;
        if (_root == NULL) { return; }		

		//利用队列来存储每一层的节点
		queue<Node*> q;
		//压入根节点
		q.push(_root);

		//队列为空，访问结束
		while (q.empty() == false) {
			//取队头元素，进行访问
			Node* tmp = q.front();
			cout << tmp->_data << " ";

			//弹出队列的首元素
			q.pop();

			//哪个孩子不为空，就压入该孩子
            if (tmp->_left != NULL) {
                q.push(tmp->_left);
            }
				
            if (tmp->_right != NULL) {
                q.push(tmp->_right);
            }
		}
		cout << endl;
	}

	//求二叉树的节点个数
	size_t Size() {
		return _Size(_root);
	}

	//求二叉树的深度
	size_t Depth() {
		return _Depth(_root);
	}

	//求二叉树的叶子节点
	size_t GetLeafSize() {
		size_t count = 0;
		_GetLeafSize(_root,count);
		return count;
	}

	//求第K层节点的个数
	size_t GetKLevelSize(size_t k) {
		assert(k > 0);
		return _GetKLevelSize(_root,k);
	}

    //节点值总和
    T SumTree() {
#ifdef _DEBUG
        cout << __FUNCTION__ << endl;
#endif
        return _SumTree(_root);
    }

    //左边节点值总和
    T SumTree_Left() {
#ifdef _DEBUG
        cout << __FUNCTION__ << endl;
#endif
        return _SumTree(_root->_left);
    }

    //右边节点值总和
    T SumTree_Right() {
#ifdef _DEBUG
        cout << __FUNCTION__ << endl;
#endif
        return _SumTree(_root->_right);
    }

    //左右节点差值
    T SumTree_Dis() {
        T t_left = SumTree_Left();
        T t_right = SumTree_Right();
        return t_left > t_right ? (t_left - t_right) : (t_right - t_left);
    }

protected:

	Node* CreateTree(T* arr,const size_t size, size_t& index,const T& invalid = T()) {
		if (index < size && arr[index]!=invalid) {
			Node* root = new Node(arr[index]);
			root->_left = CreateTree(arr,size,++index,invalid);
			root->_right = CreateTree(arr, size, ++index, invalid);
			return root;
		}
		return NULL;
	}

    Node * createBtree(T* arr, const size_t size, int index, int arr_edge_index[][2], const size_t edge_size, const T& invalid = T())
    {
        Node* root = NULL; //根节点
        std::map<int, T> map1;
        addNode_by_index(&root, arr, index, map1);

        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < edge_size; j++) {
                int index_a = arr_edge_index[j][0];
                int index_b = arr_edge_index[j][1];

                if (isInMap(index_a, map1) && !isInMap(index_b, map1)) {
                    Node *pNode_a = findNode_index(root, index_a);
                    if (pNode_a != NULL) {
                        if (addNode_by_index(&pNode_a, arr, index_b, map1)) {
#ifdef _DEBUG
                            cout << "addNode index_a=" << index_a << " index_b =" << index_b << endl;
#endif
                        }                        
                    }
                }
                
                if (isInMap(index_b, map1) && !isInMap(index_a, map1)) {
                    Node *pNode_b = findNode_index(root, index_b);
                    if (pNode_b != NULL) {
                        if (addNode_by_index(&pNode_b, arr, index_a, map1)) {
#ifdef _DEBUG
                            cout << "addNode index_b=" << index_b << " index_a =" << index_a << endl;
#endif
                        }
                    }
                }                             
            }
        }

        return root;
    }

    Node * findNode_index(Node *root, const int &i) {
        Node *pNode = root;
        if (pNode == NULL) {
            return NULL;
        }

        if (i == pNode->_index) {
            return pNode;
        }
        else {
            Node *pNode_left = NULL;
            Node *pNode_right = NULL;

            if (pNode->_left != NULL) {
                pNode_left = findNode_index(pNode->_left, i);
                if (pNode_left != NULL) {
                    return pNode_left;
                }
            }

            if (pNode->_right != NULL) {
                pNode_right = findNode_index(pNode->_right, i);
                if (pNode_right != NULL) {
                    return pNode_right;
                }
            }
        }

        return NULL;
    }

    /*
    Node * findNode(Node *root, const T &t) {
        Node *pNode = root;
        if (pNode == NULL) {
            return NULL;
        }

        if (t == pNode->_data) {
            return pNode;
        }
        else {
            Node *pNode_left = NULL;
            Node *pNode_right = NULL;

            if (pNode->_left != NULL) {
                pNode_left = findNode(pNode->_left, t);
                if (pNode_left != NULL) {
                    return pNode_left;
                }
            }

            if (pNode->_right != NULL) {
                pNode_right = findNode(pNode->_right, t);
                if (pNode_right != NULL) {
                    return pNode_right;
                }
            }
        }

        return NULL;
    }
    */

    //查找map中是否存在index下标映射
    bool isInMap(int index, std::map<int, T> &map1) {
        std::map<int, T>::iterator iter = map1.find(index);
        if (iter != map1.end()) {
            return true;
        }
        else {
            return false;
        }
    }

    //通过index下标，增加节点
    bool addNode_by_index(Node **root, T* arr, int index, std::map<int, T> &map1) {
        if (!isInMap(index, map1))
        {
            Node *tmp = new Node(arr[index]);
            tmp->_index = index;
            bool add_node = addNode(root, tmp);
            if (!add_node)
            {
                delete[] tmp;
                tmp = NULL;
            }
            else
            {
                map1[index] = arr[index];
#ifdef _DEBUG
                cout << "addNode_by_index ok, index=" << index << endl;
#endif
                return true;
            }
        }
#ifdef _DEBUG
        cout << "addNode_by_index fail, index=" << index << endl;
#endif
        return false;
    }    

    //增加父节点的子节点
    bool addNode(Node **fa, Node *son)
    {
        if(son == NULL) {
            return false;
        }

        if ((*fa) == NULL) {
            //创建根节点
            (*fa) = son;
            return true;
        }

        if ((*fa)->_left != NULL) {
            if ((*fa)->_right != NULL) {
                return false;
            }
            else {
                (*fa)->_right = son;
                son->_father = (*fa);
            }
        }
        else {
            (*fa)->_left = son;
            son->_father = (*fa);
        }

        return true;
    }

    //销毁节点
	void Destory(Node* root) {
		assert(root);
        if (root->_left != NULL) {
            Destory(root->_left);
        }
			
		root->_left = NULL;
        if (root->_right != NULL) { 
            Destory(root->_right); 
        }
			
		root->_right = NULL;

		delete[] root;
		root = NULL;
		return;
	}

    //递归拷贝构造节点
	Node* Copy(Node* root)
	{
        if (root == NULL) { return NULL;  }
			
		Node* newnode = new Node(root->_data);
		newnode->_left = Copy(root->_left);
		newnode->_right = Copy(root->_right);
		return newnode;
	}
    //递归先序遍历
	void _PrevOrder(Node* root)
	{
        if (root == NULL) { return; }
			
		cout << root->_data << " ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}
    //递归中序遍历
	void _InOrder(Node* root)
	{
        if (root == NULL) { return; }
			
		_InOrder(root->_left);
		cout << root->_data << " ";
		_InOrder(root->_right);
	}
    //递归后序遍历
	void _PostOrder(Node* root)
	{
        if (root == NULL) { return; }
			
		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout << root->_data << " ";
	}
    //递归获取节点数目
	size_t _Size(Node* root)
	{
        if (root == NULL) { return 0; }
			
		return _Size(root->_left) + _Size(root->_right) + 1;
	}
    //递归获取节点深度
	size_t _Depth(Node* root)
	{
        if (root == NULL) { return 0; }
			
		size_t leftDepth = _Depth(root->_left);
		size_t rightDepth = _Depth(root->_right);

		return leftDepth > rightDepth ? leftDepth + 1: rightDepth + 1;
	}
    //递归获取叶子节点数目
	void _GetLeafSize(Node* root,size_t &count)	{
		if (root->_left == NULL && root->_right == NULL) {
			count++;
			return;
		}
        if (root->_left != NULL) {
            _GetLeafSize(root->_left, count);
        }			
        if (root->_right != NULL) {
            _GetLeafSize(root->_right, count);
        }			
	}
    //递归获取，某层节点数目
	size_t _GetKLevelSize(Node* root, size_t k)	{
        if (root == NULL) { return 0; }
			
        if (k == 1) {
            return 1;
        }
		return _GetKLevelSize(root->_left,k-1) + _GetKLevelSize(root->_right,k-1);
	}

    //递归获取节点总值
    T _SumTree(Node *root) {
        if (root == NULL) {
            T t = T();
            return t;
        }
        T sum_left = _SumTree(root->_left);
        T sum_right = _SumTree(root->_right);
        return sum_left + root->_data + sum_right;
    }

protected:

	Node* _root;
};

void Test_edge(int arr[], int arr_size, int arr_edge[][2], int arr_edge_size) {
#ifdef _DEBUG
    cout << "arr_size=" << arr_size << endl;
    cout << "arr_edge_size=" << arr_edge_size << endl;
#endif

    BinaryTree<int> t(arr, arr_size, arr_edge, arr_edge_size);

#ifdef _DEBUG
    t.PrevOrder();
    t.InOrder();
    t.PostOrder();

    t.PrevOrderNonR();
    t.InOrderNonR();
    t.PostOrderNonR();

    t.LevelOrder();

    //求二叉树的节点个数
    int t_size = t.Size();
    cout << "t_size=" << t_size << endl;

    //求二叉树的深度
    int t_depth = t.Depth();
    cout << "t_depth=" << t_depth << endl;

    //求二叉树的叶子节点
    int t_leaf_size = t.GetLeafSize();
    cout << "t_leaf_size=" << t_leaf_size << endl;

    //求第K层节点的个数
    for (int i = 1; i < t_depth + 1; i++) {
        int t_get_level_size = t.GetKLevelSize(i);
        cout << i << " # t_get_level_size=" << t_get_level_size << endl;
    }
#endif

    int t_sum = t.SumTree();
    int t_sum_l = t.SumTree_Left();
    int t_sum_r = t.SumTree_Right();
    int t_sum_dis = t.SumTree_Dis();

#ifdef _DEBUG
    cout << "t_sum=" << t_sum << endl;
    cout << "t_sum_l=" << t_sum_l << endl;
    cout << "t_sum_r=" << t_sum_r << endl;
    cout << "t_sum_dis=" << t_sum_dis << endl;
#endif

    cout << "输出：" << endl;
    cout << t_sum_dis << endl;    

    //BinaryTree<int> t2 = t;
    //t2.LevelOrder();
}

void TestBinaryTree()
{
    //int arr[6] = { 1, 2, 3, '#', '#', 4 };
	//int arr[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	//int arr[] = { 1, 2, '#', 3, '#','#', 4,5, '#', 6 ,'#', 7,'#','#',8};
    //int arr[] = { 10, 7, '#', '#', 8, 6 };

	//BinaryTree<int> t(arr,sizeof(arr)/sizeof(arr[0]),'#');
    int arr[] = {10, 6, 7, 8};
    int arr_edge[][2] = { { 2, 0 }, { 3, 0 }, { 1, 3 } };
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    int arr_edge_size = sizeof(arr_edge) / sizeof(arr_edge[0]);
    
    Test_edge(arr, arr_size, arr_edge, arr_edge_size);

    int arr2[] = { 61, 80};
    int arr_edge2[][2] = { { 0, 1 } };
    int arr_size2 = sizeof(arr) / sizeof(arr[0]);
    int arr_edge_size2 = sizeof(arr_edge) / sizeof(arr_edge[0]);

    Test_edge(arr2, arr_size2, arr_edge2, arr_edge_size2);

    int arr3[] = { 30, 13, 41};
    int arr_edge3[][2] = { { 0, 1 }, { 1, 2 } };
    int arr_size3 = sizeof(arr) / sizeof(arr[0]);
    int arr_edge_size3 = sizeof(arr_edge) / sizeof(arr_edge[0]);

    Test_edge(arr3, arr_size3, arr_edge3, arr_edge_size3);

    int arr4[] = { 33, 72, 19, 54 };
    int arr_edge4[][2] = { { 0, 2 }, { 1, 3 }, { 1, 2 } };
    int arr_size4 = sizeof(arr) / sizeof(arr[0]);
    int arr_edge_size4 = sizeof(arr_edge) / sizeof(arr_edge[0]);

    Test_edge(arr4, arr_size4, arr_edge4, arr_edge_size4);
}

void TestBinaryTree_Input()
{
    int n = 0;
    cout << "输入节点数：";
    cin >> n;
    //printf("You input n=%d \n", n);
    if (n < 1)
    {
        return;
    }

    int * arr = new int[n];

    int t_tmp = 0;
    int i = 0;
    while (i < n) {        
        cin >> t_tmp;
        arr[i++] = t_tmp;
        //printf("You input num=%d \n", t_tmp);
    }

#ifdef _DEBUG
    for (i = 0; i < n; i++) {
        printf("arr[%d]=%d \n", i, arr[i]);
    }
#endif

    cout << "输入节点边 (Ctrl+Z结束):" << endl;

    int edge_a = 0;
    int edge_b = 0;
    int j = 0;
    const int max_edges = 100;
    int arr_edge[100][2];
    int count_ch = 0;
    while (cin >> edge_a >> edge_b)
    {  
#ifdef _DEBUG
        cout << "You input edge_a=" << edge_a << ", edge_b=" << edge_b << endl;
#endif
        if (j < max_edges) {
            arr_edge[j][0] = edge_a;
            arr_edge[j][1] = edge_b;
            j++;
        }
        else {
            cout <<  "input edges too much. max_edges=" << max_edges << endl;
            break;
        }
    }

    int arr_size = n;
    int arr_edge_size = j;

    Test_edge(arr, arr_size, arr_edge, arr_edge_size);

    if (arr) {
        delete arr;
        arr = NULL;
    }
}