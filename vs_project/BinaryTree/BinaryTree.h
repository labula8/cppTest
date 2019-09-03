#pragma once 

#include <stack>
#include <assert.h>
#include <queue>
#include <map>
#include <iostream>
#include <stdio.h>

//#define _DEBUG

using namespace std;

//����һ���������ڵ�
template<typename T>
struct BinaryTreeNode {
    int _index;  //�±�
	T _data;    //����
	BinaryTreeNode<T> *_left;//����
	BinaryTreeNode<T> *_right;//�Һ���
    BinaryTreeNode<T> *_father;//���ڵ�

	BinaryTreeNode(const T& x)//�ڵ�Ĺ��캯��
		:_index(0),_data(x)
		, _left(NULL)
		, _right(NULL) {}
};

//���������
template<typename T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;//������ΪNode

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

	//�������캯��
	BinaryTree(const BinaryTree& b) {
		_root = Copy(b._root);
	}

	//��ֵ���������
	BinaryTree&operator=(BinaryTree t) {
		if (this != &t) {
			std::swap(t._root, _root);
		}
		return *this;
	}

	//��������
	~BinaryTree() {
		if (_root != NULL) {
			Destory(_root);
			_root = NULL;
		}
	}

	//�������������������������
	void PrevOrder() {
        cout << "ǰ��" << __FUNCTION__ << endl;
		//���õݹ鷽��������protected�ڲ���_PrevOrder����������ͺ���Ҳ��һ��
		_PrevOrder(_root);
		cout << endl;
	}
	void InOrder() {
        cout << "�У�"  << __FUNCTION__ << endl;
		_InOrder(_root);
		cout << endl;
	}
	void PostOrder() {
        cout << "��" << __FUNCTION__ << endl;
		_PostOrder(_root);
		cout << endl;
	}

	//���ֱ�����ʽ�ķǵݹ���ʽ
	void PrevOrderNonR() {
        cout << "ǰ��" << __FUNCTION__ << endl;
		//����һ��ջ��һ��ָ�����
		stack<Node*> s;
		Node* cur = _root;

		//��cur,����ջΪ��ʱ
		while (cur || !s.empty()) {
			//�ݹ����������
			while (cur) {
				//����Ԫ��
				cout << cur->_data << " ";
				
				//����ѹջ
				s.push(cur);
				
				//ָ������
				cur = cur->_left;
			}
			//һ·���󣬴�ʱcurΪ��

			//ȡջ��Ԫ��
			Node* top = s.top();
			//��ջ
			s.pop();
			//�����Һ���
			cur = top->_right;
		}
		cout << endl;
	}

	//��������ķǵݹ飬ֻ�ð�ѹջ����Ԫ�ص�λ�øĵ���ջ��ʱ����ʼ���
	void InOrderNonR() {
        cout << "�У�" << __FUNCTION__ << endl;
		//����һ��ջ��ָ�����cur
		Node* cur = _root;
		stack<Node*> s;

		//�ж��Ƿ����
		while (cur || !s.empty()) {
			//ѭ��ѹ��������
			while (cur) {
				s.push(cur);

				//�����Ȳ�Ҫ����Ԫ��
				cur = cur->_left;
			}
			Node* top = s.top();
			s.pop();

			//��ʱ�ٷ���Ԫ��
			cout << top->_data << " ";
			cur = top->_right;
		}
        cout << endl;
	}

	//����ǵݹ����
	void PostOrderNonR() {
        cout << "��" << __FUNCTION__ << endl;
		//������������ȣ��ඨ����һ��prevָ�룬������һ�����ʵ�Ԫ��
		Node* prev = NULL;

		//����һ��ջs��ָ��ڵ����ʱ����cur
		Node* cur = _root;
		stack<Node*> s;

		//�ж��Ƿ����
		while (cur || !s.empty()) {
			//�ݹ�ѹ��������
			while (cur) {
				//���ɲ�����Ԫ��
				s.push(cur);
				cur = cur->_left;
			}

			//ȡջ��Ԫ�ؽ����ж�
			Node* top = s.top();

			//���վ��Ԫ�ص�������Ϊ��  ����  �������Ѿ�������
			if (top->_right == NULL || top->_right == prev)	{
				//��ӡ��
				cout << top->_data << " ";
				
				//���ոշ��ʹ���Ԫ����prev��������
				prev = top;

				//��ջ
				s.pop();
			}
			//��������Ϊ�� ���� ��û�б�����
			else
			{
				//����������
				cur = top->_right;
			}
		}
        cout << endl;
	}

	//�������
	void LevelOrder() {
        cout << "�㣺" << __FUNCTION__ << endl;
        if (_root == NULL) { return; }		

		//���ö������洢ÿһ��Ľڵ�
		queue<Node*> q;
		//ѹ����ڵ�
		q.push(_root);

		//����Ϊ�գ����ʽ���
		while (q.empty() == false) {
			//ȡ��ͷԪ�أ����з���
			Node* tmp = q.front();
			cout << tmp->_data << " ";

			//�������е���Ԫ��
			q.pop();

			//�ĸ����Ӳ�Ϊ�գ���ѹ��ú���
            if (tmp->_left != NULL) {
                q.push(tmp->_left);
            }
				
            if (tmp->_right != NULL) {
                q.push(tmp->_right);
            }
		}
		cout << endl;
	}

	//��������Ľڵ����
	size_t Size() {
		return _Size(_root);
	}

	//������������
	size_t Depth() {
		return _Depth(_root);
	}

	//���������Ҷ�ӽڵ�
	size_t GetLeafSize() {
		size_t count = 0;
		_GetLeafSize(_root,count);
		return count;
	}

	//���K��ڵ�ĸ���
	size_t GetKLevelSize(size_t k) {
		assert(k > 0);
		return _GetKLevelSize(_root,k);
	}

    //�ڵ�ֵ�ܺ�
    T SumTree() {
#ifdef _DEBUG
        cout << __FUNCTION__ << endl;
#endif
        return _SumTree(_root);
    }
    T SumTree_Left() {
#ifdef _DEBUG
        cout << __FUNCTION__ << endl;
#endif
        return _SumTree(_root->_left);
    }
    T SumTree_Right() {
#ifdef _DEBUG
        cout << __FUNCTION__ << endl;
#endif
        return _SumTree(_root->_right);
    }

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
        Node* root = NULL; //���ڵ�
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

    bool isInMap(int index, std::map<int, T> &map1) {
        std::map<int, T>::iterator iter = map1.find(index);
        if (iter != map1.end()) {
            return true;
        }
        else {
            return false;
        }
    }

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

    bool addNode(Node **fa, Node *son)
    {
        if(son == NULL) {
            return false;
        }

        if ((*fa) == NULL) {
            //�������ڵ�
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
	Node* Copy(Node* root)
	{
        if (root == NULL) { return NULL;  }
			
		Node* newnode = new Node(root->_data);
		newnode->_left = Copy(root->_left);
		newnode->_right = Copy(root->_right);
		return newnode;
	}
	void _PrevOrder(Node* root)
	{
        if (root == NULL) { return; }
			
		cout << root->_data << " ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}
	void _InOrder(Node* root)
	{
        if (root == NULL) { return; }
			
		_InOrder(root->_left);
		cout << root->_data << " ";
		_InOrder(root->_right);
	}
	void _PostOrder(Node* root)
	{
        if (root == NULL) { return; }
			
		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout << root->_data << " ";
	}
	size_t _Size(Node* root)
	{
        if (root == NULL) { return 0; }
			
		return _Size(root->_left) + _Size(root->_right) + 1;
	}
	size_t _Depth(Node* root)
	{
        if (root == NULL) { return 0; }
			
		size_t leftDepth = _Depth(root->_left);
		size_t rightDepth = _Depth(root->_right);

		return leftDepth > rightDepth ? leftDepth + 1: rightDepth + 1;
	}
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
	size_t _GetKLevelSize(Node* root, size_t k)	{
        if (root == NULL) { return 0; }
			
        if (k == 1) {
            return 1;
        }
		return _GetKLevelSize(root->_left,k-1) + _GetKLevelSize(root->_right,k-1);
	}

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

    //��������Ľڵ����
    int t_size = t.Size();
    cout << "t_size=" << t_size << endl;

    //������������
    int t_depth = t.Depth();
    cout << "t_depth=" << t_depth << endl;

    //���������Ҷ�ӽڵ�
    int t_leaf_size = t.GetLeafSize();
    cout << "t_leaf_size=" << t_leaf_size << endl;

    //���K��ڵ�ĸ���
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

    cout << "�����" << endl;
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
    cout << "����ڵ�����";
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

    //for (i = 0; i < n; i++) {
    //    printf("arr[%d]=%d \n", i, arr[i]);
    //}

    cout << "����ڵ�� (Ctrl+Z����):" << endl;

    int edge_a = 0;
    int edge_b = 0;
    int j = 0;
    const int max_edges = 100;
    int arr_edge[100][2];
    int count_ch = 0;
    while (cin >> edge_a >> edge_b)
    {  
        //printf("You input edge_a=%d, edge_b=%d \n", edge_a, edge_b);
        if (j < max_edges) {
            arr_edge[j][0] = edge_a;
            arr_edge[j][1] = edge_b;
            j++;
        }
        else {
            //printf("input edges too much. max_edges=%d \n", max_edges);
            break;
        }
        /* Ctrl + Z
        if (cin.get() == '\n' && cin.get() == '\n') {
            break;
        }
        */
    }

    int arr_size = n;
    int arr_edge_size = j;

    Test_edge(arr, arr_size, arr_edge, arr_edge_size);

    if (arr) {
        delete arr;
        arr = NULL;
    }

}