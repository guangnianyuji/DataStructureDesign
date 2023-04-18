#include<iostream>
using namespace std;


template<class T>
class LinkNode
{
private:
	T data;

public:
	LinkNode<T>* link;
	//已知Link初始化LinkNode
	LinkNode(LinkNode<T>* ptr = NULL)
	{
		link = ptr;
	}
	//已知data Link 初始化LinkNode
	LinkNode(const T& item, LinkNode<T>* ptr = NULL)
	{
		data = item;
		link = ptr;
	}
	//得到LinkNode的Data
	T getData()
	{
		return data;
	}
	//设置LinkNode的Data
	void setData(const T& item)
	{
		data = item;
	}

};

template<class T>
class LinkedQueue
{
private:
	LinkNode<T>* first, * front, * rear;
public:
	LinkedQueue();

	~LinkedQueue();

	void makeEmpty();

	bool isEmpty()
	{
		return first->link == NULL;
	}

	bool Push(const T x);

	T Front()
	{
		return front->getData();
	}

	void Pop();
};

template<class T>
LinkedQueue<T>::LinkedQueue()
{
	first = new LinkNode<T>;
	front = rear = NULL;
}

template<class T>
LinkedQueue<T>::~LinkedQueue()
{
	makeEmpty();
	delete first;
}

template<class T>
void LinkedQueue<T>::makeEmpty()
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
bool LinkedQueue<T>::Push(const T x)
{
	LinkNode<T>* current = new LinkNode<T>(x);
	if (current == NULL)
	{
		//
		return false;
	}
	if (front == NULL)
	{
		front = rear = current;
		first->link = front;
		return true;
	}
	rear->link = current;
	rear = current;
	return true;
}

template<class T>
void LinkedQueue<T>::Pop()
{
	LinkNode<T>* p = front;
	front = front->link;
	first->link = front;
	delete p;
}

int main()
{
	int n;
	while (1)
	{
		cin >> n;
		if (cin.good() && (n > 0 && n <= 1000))
		{
			break;
		}
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
		}
		cout << "error,input again" << endl;
	}
	LinkedQueue<int> Qa, Qb;
 
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		if (x % 2)
		{
			Qa.Push(x);
		}
		else
		{
			Qb.Push(x);
		}
	}
	int tg = 0;
	while (!Qa.isEmpty() || !Qb.isEmpty())
	{
		int a = 2, b = 1;//A窗口每处理完2个顾客是，B窗口处理完1个顾客
		while (a-- && !Qa.isEmpty())
		{
			int x = Qa.Front();
			Qa.Pop();
			if (tg)
			{
				cout << " ";
			}
			cout << x ;
			tg = 1;
		}
		while (b-- && !Qb.isEmpty())
		{
			int x = Qb.Front();
			Qb.Pop();
			if (tg)
			{
				cout << " ";
			}
			cout << x;
			tg = 1;
		}
	}
	cout<<endl;
	return 0;
}
