#include <iostream>
#include<cstring>
#define MAZESIZE 7
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

	bool insertAtTail(T x);//insert item at tail

	bool remove(int num, T& x);//删除第num个数据，x得到该数据

	bool remove(T& x);//删除为x的数据

	bool removeAtTail();//remove item at tail

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
bool List<T>::insertAtTail(T x)
{
	LinkNode<T>* tail = getTail();
	//cout << tail->getData(); cout << endl;
	LinkNode<T>* newnode = new LinkNode<T>(x, NULL);
	tail->link = newnode;
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
bool List<T>::removeAtTail()
{
	if (isEmpty())
	{
		return false;
	}
	LinkNode<T>* current = first;
	while (current->link != NULL && current->link->link != NULL)
	{
		current = current->link;
	}
	current->link = NULL;

	return true;
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
		LinkNode<T>* newNode = new LinkNode<T>(srcptr.data);
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
			//
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

class point
{
	friend ostream& operator<<(ostream& cout, const point& p);
private:
	int row, col;
public:
	point() {};
	point(int r, int c)
	{
		row = r;
		col = c;
	}
	int getRow()const
	{
		return row;
	}
	int getCol()const
	{
		return col;
	}
};

ostream& operator<<(ostream& cout, const point& p)
{
	cout << "(" << p.row << "," << p.col << ")";
	return cout;
}

class Maze
{
private:
	char map[MAZESIZE][MAZESIZE] =
	{
		{'#','#','#','#','#','#','#'},
		{'#','S','#','0','0','0','#'},
		{'#','0','#','0','#','#','#'},
		{'#','0','#','0','#','0','#'},
		{'#','0','0','0','0','0','#'},
		{'#','0','#','0','#','E','#'},
		{'#','#','#','#','#','#','#'},
	};

	char pathmap[MAZESIZE][MAZESIZE];

	int visit[MAZESIZE][MAZESIZE] = { 0 };

	int move[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };

	List<point> pathList;	
	//展示地图上的路径
	void showpathMaze();
	//找通路
	bool findPath(const point& start);
	//输出路径坐标
	void showPath(const point& start);
	//初始化地图
	void initpathmap();
public:
	//展示地图
	void showMaze();

	//统一解决问题
	void solve();
};

void Maze::initpathmap()
{
	for (int i = 0; i < MAZESIZE; i++)
	{
		for (int j = 0; j < MAZESIZE; j++)
		{
			pathmap[i][j] = map[i][j];
		}
	}
}

void Maze::showMaze()
{
	//output table-header
	cout << "迷宫地图(#代表不可通行，0代表可以通行，S为起点，E为终点):\n\n";
	cout << "\t";
	for (int j = 0; j < MAZESIZE; j++)
	{
		cout << j << "列\t";
	}
	cout << endl;
	for (int i = 0; i < MAZESIZE; i++)
	{
		cout << i << "行\t";
		for (int j = 0; j < MAZESIZE; j++)
		{
			cout << map[i][j] << "\t";
		}
		cout << endl << endl;
	}
}

void Maze::showpathMaze()
{
	cout << "行走地图如下(X代表走的路径);\n";
	//output table-header
	cout << "\t";
	for (int j = 0; j < MAZESIZE; j++)
	{
		cout << j << "列\t";
	}
	cout << endl;
	for (int i = 0; i < MAZESIZE; i++)
	{
		cout << i << "行\t";
		for (int j = 0; j < MAZESIZE; j++)
		{
			cout << pathmap[i][j] << "\t";
		}
		cout << endl << endl;
	}
}

bool Maze::findPath(const point& start)
{
	point currentPos = start;
	int row = currentPos.getRow();
	int col = currentPos.getCol();
	visit[row][col] = 1;
	pathList.insertAtTail(point(row, col));
	pathmap[row][col] = 'X';
	if (map[row][col] == 'E')
	{
		return true;
	}

	bool flag = false;
	for (int i = 0; i < 4; i++)
	{
		int nxtrow = row + move[i][0];
		int nxtcol = col + move[i][1];
		if (nxtrow <= 0 || nxtcol <= 0 || nxtrow >= MAZESIZE || 
			nxtcol >= MAZESIZE || visit[nxtrow][nxtcol] || map[nxtrow][nxtcol] == '#')
		{
			continue;
		}
		if (findPath(point(nxtrow, nxtcol)))
		{
			flag = true;
		}
	}
	if (!flag)
	{
		pathmap[row][col] = '0';
		pathList.removeAtTail();
		visit[row][col] = 0;
	}
	return flag;
}

void Maze::showPath(const point& start)
{
	if (findPath(start))
	{
		showpathMaze();
		cout << "迷宫路径\n";
		LinkNode<point>* current = pathList.getHead()->link;
		cout << current->getData();
		current = current->link;
		while (current != NULL)
		{
			cout << " ---> " << current->getData();
			current = current->link;
		}
		cout << "\n\n";
		return;
	}
	else
	{
		pathmap[start.getRow()][start.getCol()] = 'S';
		showpathMaze();
		cout << "从当前位置无法走到迷宫出口！" << endl;
		return;
	}
}

void Maze::solve()
{
	cout << "按任意键显示路径" << endl;
	getchar();
	for (int i = 0; i < MAZESIZE; i++)
	{
		for (int j = 0; j < MAZESIZE; j++)
		{
			if (map[i][j] == 'S')
			{
				memset(visit, 0, sizeof(visit));
				pathList.makeEmpty();
				initpathmap();
				showPath(point(i, j));
			}
		}
	}
}

int main()
{
	Maze maze;
	maze.showMaze();
	maze.solve();

	return 0;
}
