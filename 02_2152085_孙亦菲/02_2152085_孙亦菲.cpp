#include <iostream>

using namespace std;

//节点类
template<class T>
class LinkNode
{
private:
	T data;

public:
	LinkNode<T>* link;

	LinkNode(LinkNode<T>* ptr = NULL)//已知Link初始化LinkNode
	{
		link = ptr;
	}

	LinkNode(const T& item, LinkNode<T>* ptr = NULL)//已知data Link 初始化LinkNode
	{
		data = item;
		link = ptr;
	}

	T getData()//得到LinkNode的Data
	{
		return data;
	}

	void setData(const T& item)
	{
		data = item;
	}

};


template<class T>
class List
{
private:
	LinkNode<T>* first;
public:
	List();

	List(const List<T>& L);

	~List();

	void makeEmpty();//

	LinkNode<T>* getHead()const
	{
		return first;
	}

	LinkNode<T>* getTail()const;

	int length()const;//get valid length

	void setHead(LinkNode<T>* p);//set firsr LinkNode

	LinkNode<T>* search(T& x);//

	LinkNode<T>* locate(int& num);

	bool getData(int num, T& x);//x得到第num个数据，成功返回true,失败返回false

	bool setData(int num, const T& x);//x设置第num个数据，成功返回true,失败返回false

	bool insert(int num, T& x);//第num个数据后插入x,成功返回true,失败返回false

	bool remove(int num, T& x);//删除第num个数据，x得到该数据

	bool remove(T& x);//删除为x的数据

	bool isEmpty()const//Link是否为空
	{
		return first->link == NULL ? true : false;
	}

	bool isFull()const//Link是否为满
	{
		return false;
	}

	void output();//输出整个Link数据

	List<T>& operator=(List<T> L);

	void inputFront(T endTag);//前插输入Link，endTag为结束符号

	void inputFront(const unsigned int& num);//前插输入Link，有效节点num个

	void inputRear(T endTag);//后插输入Link，endTag为结束符号

	void inputRear(const unsigned int& num);//后插输入Link，有效节点num个

	List<T> getIntersection(const List<T>& l2);//求与另一个链表的交集
};

template<class T>
List<T>::List()
{
	first = new LinkNode<T>;
}

template<class T>
List<T>::List(const List<T>& L)
{
	LinkNode<T>* srcptr = L.getHead();
	LinkNode<T>* desptr = first = new LinkNode<T>;
	while (srcptr->link != NULL)
	{
		desptr->link = new LinkNode<T>(srcptr->link->getData());
		desptr = desptr->link;
		srcptr = srcptr->link;
	}
}

template<class T>
List<T>::~List()
{
	makeEmpty(); delete first;
}

template<class T>
void List<T>::makeEmpty()
{
	LinkNode<T>* current;
	while (first->link != NULL)
	{
		current = first->link;
		first->link = current->link;
		delete current;
	}

}

template<class T>
LinkNode<T>* List<T>::getTail()const
{
	LinkNode<T>* last = first;
	LinkNode<T>* current = first;
	while (current != NULL)
	{
		last = current;
		current = current->link;
	}
	return last;
}

template<class T>
int List<T>::length()const
{
	int i = 0;
	LinkNode<T>* current = first;
	while (current->link != NULL)
	{
		i++;
		current = current->link;
	}
	return i;
}

template<class T>
void List<T>::setHead(LinkNode<T>* p)
{
	if (first->link != NULL)
	{
		p->link = first->link;
	}
	first = p;
}

template<class T>
LinkNode<T>* List<T>::search(T& x)
{
	LinkNode<T>* current = first->link;
	while (current != NULL)
	{
		if (current->getData() == x)
		{
			break;
		}
		current = current->link;
	}
	return current;
}

template<class T>
LinkNode<T>* List<T>::locate(int& num)
{
	int i = 0;
	LinkNode<T>* current = first;
	while (current != NULL && i < num)
	{
		i++;
		current = current->link;
	}
	return current;
}

template<class T>
bool List<T>::getData(int num, T& x)
{
	if (x <= 0)
	{
		return false;
	}
	int i = 0;
	LinkNode<T>* current = first;
	while (current != NULL && i < x)
	{
		i++;
		current = current->link;
	}
	if (current == NULL)
	{
		return false;;
	}
	x = current->getData();
}

template<class T>
bool List<T>::setData(int num, const T& x)
{
	if (num <= 0)
	{
		return false;
	}
	int i = 0;
	LinkNode<T>* current = first;
	while (current != NULL && i < num)
	{
		i++;
		current = current->link;
	}
	if (current == NULL)
	{
		return false;
	}
	current->data = x;
	return true;
}

template<class T>
bool List<T>::insert(int num, T& x)
{
	if (num <= 0)
	{
		//
		return false;
	}
	int i = 1;
	LinkNode<T>* last = first;
	while (last != NULL && i < num)
	{
		i++;
		last = last->link;
	}
	if (last == NULL)
	{
		//
		return false;
	}
	LinkNode<T>* next = last->link;
	LinkNode<T>* newNode = new LinkNode<T>(x, next);
	last->link = newNode;
	return true;
}

template<class T>
bool List<T>::remove(int num, T& x)
{
	if (num < 0)
	{
		//
		return false;
	}
	LinkNode<T>* last = first;
	LinkNode<T>* current = first;
	int i = 0;
	while (current != NULL && i < num)
	{
		i++;
		last = current;
		current = current->link;
	}
	if (current == NULL)
	{
		//
		return false;
	}
	x = current->data;
	last->link = current->link;
	delete current;
	return true;
}

template<class T>
bool List<T>::remove(T& x)
{
	bool flag = false;
	LinkNode<T>* last = first;
	LinkNode<T>* current = first;
	while (last->link != NULL)
	{
		current = last->link;
		if (current->getData() == x)
		{
			last->link = current->link;
			flag = true;
		}
		last = last->link;
	}
	return flag;
}

template<class T>
void List<T>::output()
{
	LinkNode<T>* current = first->link;
	if (current != NULL)
	{
		cout << current->getData();
		current = current->link;
	}

	while (current != NULL)
	{
		cout << " " << current->getData();
		current = current->link;
	}
}

template<class T>
List<T>& List<T>::operator=(List<T> L)
{
	makeEmpty();
	LinkNode<T>* srcptr = L.getHead()->link;
	LinkNode<T>* desptr = first = new LinkNode<T>;
	while (srcptr != NULL)
	{
		LinkNode<T>* newNode = new LinkNode<T>(srcptr->data);
		srcptr = srcptr->link;
		desptr->link = newNode;
		desptr = desptr->link;
	}
	return *this;
}

template<class T>
void List<T>::inputFront(T endTag)
{
	makeEmpty();
	LinkNode<T>* newNode;
	T val;
	cin >> val;
	while (!(val == endTag))
	{
		newNode = new LinkNode<T>(val);
		if (newNode == NULL)
		{
			//
			exit(1);
		}
		newNode->link = first->link;
		first->link = newNode;
		cin >> val;
	}
}

template<class T>
void List<T>::inputFront(const unsigned int& num)
{
	makeEmpty();
	LinkNode<T>* newNode;

	for (int i = 1; i <= num; i++)
	{
		T val;
		cin >> val;
		newNode = new LinkNode<T>(val);
		if (newNode == NULL)
		{
			//
			exit(1);
		}
		newNode->link = first->link;
		first->link = newNode;
	}
}

template<class T>
void List<T>::inputRear(T endTag)
{
	makeEmpty();
	LinkNode<T>* newNode;
	LinkNode<T>* last = first;
	T val;
	cin >> val;
	while (!(val == endTag))
	{
		newNode = new LinkNode<T>(val);
		if (newNode == NULL)
		{
			//
			exit(1);
		}
		last->link = newNode;
		last = newNode;
		cin >> val;
	}
}

template<class T>
void List<T>::inputRear(const unsigned int& num)
{
	makeEmpty();
	LinkNode<T>* newNode;
	LinkNode<T>* last = first;

	for (int i = 1; i <= num; i++)
	{
		T val;
		cin >> val;
		newNode = new LinkNode<T>(val);
		if (newNode == NULL)
		{
			cerr << "Allocation Error!";
			exit(1);
		}
		last->link = newNode;
		last = newNode;
	}

}

template<class T>
List<T> List<T>::getIntersection(const List<T>& l2)
{
	List<T> l3;
	LinkNode<T>* currentnode1 = first->link;
	LinkNode<T>* currentnode2 = l2.first->link;
	LinkNode<T>* currentnode3 = l3.first;
	while (currentnode1 != NULL && currentnode2 != NULL)
	{
		if (currentnode1->getData() == currentnode2->getData())
		{
			currentnode3->link = new LinkNode<T>(currentnode1->getData());
			currentnode1 = currentnode1->link;
			currentnode2 = currentnode2->link;
			currentnode3 = currentnode3->link;
		}
		else if (currentnode1->getData() < currentnode2->getData())
		{
			currentnode1 = currentnode1->link;
		}
		else
		{
			currentnode2 = currentnode2->link;
		}
	}
	return l3;
}

int main()
{
	List<int> l1, l2;
	l1.inputRear(-1);
	l2.inputRear(-1);
	List<int> l3 = l1.getIntersection(l2);

	if (l3.isEmpty())
	{
		cout << "NULL\n";
	}
	else
	{
		l3.output();
	}

	return 0;
}