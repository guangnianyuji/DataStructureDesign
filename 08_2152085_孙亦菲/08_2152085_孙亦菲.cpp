#include<iostream>
using namespace std;
#define DefaultVertices 100

template <class T>
class PQueue
{
private:
	T* arr;
	int maxSize;
	int currentSize;
	void shiftdown(int k);
	void shiftup(int k);
public:
	PQueue(int sz = 10005);
	~PQueue();
	bool Push(T x);
	bool Pop();
	bool isEmpty()const
	{
		return currentSize == 0;
	}
	T Front()const
	{
		return arr[0];
	}
	int Size()const
	{
		return currentSize;
	}
};

template<class T>
PQueue<T>::PQueue(int sz)
{
	arr = new T[sz];
	currentSize = 0;
	maxSize = sz;
}

template<class T>
PQueue<T>::~PQueue()
{
	delete[]arr;
}

template <class T>
void PQueue<T>::shiftdown(int k)
{
	T temp = arr[k];
	for (int i = 2 * k + 1; i < currentSize; i = 2 * i + 1)
	{
		if (i + 1 < currentSize && arr[i + 1] < arr[i])
		{
			i++;
		}
		if (temp < arr[i])
		{
			break;
		}
		arr[k] = arr[i];
		k = i;
	}
	arr[k] = temp;
}

template<class T>
void PQueue<T>::shiftup(int k)
{
	T temp = arr[k];
	int i = k;
	while (i > 0)
	{
		i = (i - 1) / 2;
		if (arr[i]<temp)
		{
			break;
		}
		arr[k] = arr[i];
		k = i;
	}
	arr[k] = temp;
}

template<class T>
bool PQueue<T>::Push(T x)
{
	if (currentSize + 1 > maxSize)
	{
		return false;
	}
	arr[currentSize] = x;
	currentSize++;
	shiftup(currentSize - 1);
	return true;
}

template<class T>
bool PQueue<T>::Pop()
{
	if (currentSize == 0)
	{
		return false;
	}
	arr[0] = arr[currentSize - 1];
	currentSize--;
	shiftdown(0);
	return true;
}

template<class T, class E>
class Graph
{
public:
	Graph(int sz = DefaultVertices) {};
	virtual ~Graph() {};
	bool GraphEmpty()const
	{
		return numEdges == 0;
	}
	bool GraphFull()const
	{
		return numVertices == maxVertices || numEdges == (maxVertices) * (maxVertices - 1) / 2;
	}
	int NumberOfVertices()
	{
		return numVertices;
	}
	int NumberOfEdges()
	{
		return numEdges;
	}

	virtual int getFirstNeighbor(int v) = 0;
	virtual int getNextNeighbor(int v, int w) = 0;
	virtual bool insertVertex(const T vertex) = 0;
	virtual bool insertEdge(int v1, int v2, E cost) = 0;
	//virtual bool removeVertex(int v);
	virtual bool removeEdge(int v1, int v2) = 0;
	virtual int getVertexPos(T vertex) = 0;

protected:
	int maxVertices;
	int numEdges;
	int numVertices;
};



template<class T, class E>
class  Edge
{
public:
	int fr;
	int dest;
	E cost;
	Edge<T, E>* link;
	Edge() {};
	Edge(int num, E weight) :dest(num), cost(weight), link(NULL) {};
	bool operator!=(Edge<T, E>& R)const
	{
		return dest != R.dest;
	}
	bool operator<(Edge<T, E>& R)const
	{
		return this->cost < R.cost;
	}
};

template<class T, class E>
class Vertex
{
public:
	T data;
	Edge<T, E>* adj;
};

template<class T, class E>
class Graphlnk :public Graph<T, E>
{
public:
	Graphlnk(int sz = DefaultVertices);
	~Graphlnk();
	//第一个邻接顶点
	int getFirstNeighbor(int v);
	//下一个邻接顶点
	int getNextNeighbor(int v, int w);
	//编号为i的顶点的值
	T getValue(int i);
	//顶点v1,v2间边的权值
	E getWeight(int v1, int v2);
	//指向顶点v1,v2间边的指针
	Edge<T, E>* getEdge(int v1, int v2);
	//插入顶点
	bool insertVertex(T vertex);
	//无向图移除顶点
	bool undirremoveVertex(int v);
	//有向图移除顶点
	bool dirremoveVertex(int v);
	//插入边
	bool insertEdge(int v1, int v2, E weight);
	//移除边
	bool removeEdge(int v1, int v2);
	//得到某元素在图中的位置
	int getVertexPos(const T vertex)
	{
		for (int i = 0; i < this->maxVertices; i++)
		{
			if (NodeTable[i].data == vertex)
			{
				return i;
			}
		}
		return -1;
	}
private:
	Vertex<T, E>* NodeTable;
};


template<class T, class E>
Graphlnk<T, E>::Graphlnk(int sz)
{
	this->maxVertices = sz; this->numVertices = 0; this->numEdges = 0;
	NodeTable = new Vertex<T, E>[this->maxVertices];
	for (int i = 0; i < this->maxVertices; i++)
	{
		NodeTable[i].adj = NULL;
	}
}

template<class T, class E>
Graphlnk<T, E>::~Graphlnk()
{
	for (int i = 0; i < this->maxVertices; i++)
	{
		Edge<T, E>* p = NodeTable[i].adj;

		while (p != NULL)
		{
			NodeTable[i].adj = p->link;
			delete p;
			p = NodeTable[i].adj;
		}
	}
	delete[]NodeTable;
}

template<class T, class E>
T Graphlnk<T, E>::getValue(int i)
{
	return NodeTable[i].data;
}

template<class T, class E>
int Graphlnk<T, E>::getFirstNeighbor(int v)
{
	if (v < 0 || v >= this->numVertices)
	{
		return -1;
	}
	if (NodeTable[v].adj != NULL)
	{
		return NodeTable[v].adj->dest;
	}
	else
	{
		return -1;
	}
}

template<class T, class E>
int Graphlnk<T, E>::getNextNeighbor(int v, int w)
{
	if (v < 0 || v >= this->numVertices)
	{
		return -1;
	}
	Edge<T, E>* p = NodeTable[v].adj;
	while (p != NULL && p->dest != w)
	{
		p = p->link;
	}
	if (p != NULL && p->link != NULL)
	{
		return p->link->dest;
	}
	return -1;
}

template<class T, class E>
Edge<T, E>*  Graphlnk<T, E>::getEdge(int v1, int v2)
{
	Edge < T, E>* p = NodeTable[v1].adj;
	while (p != NULL && p->dest != v2)
	{
		p = p->link;
	}
	return p;
}

template<class T, class E>
E Graphlnk<T, E>::getWeight(int v1, int v2)
{
	Edge < T, E>* p = NodeTable[v1].adj;
	while (p != NULL && p->dest != v2)
	{
		p = p->link;
	}
	if (p != NULL)
	{
		return p->cost;
	}
	return 0;
}

template<class T, class E>
bool Graphlnk<T, E>::insertVertex(T vertex)
{
	if (this->numVertices == this->maxVertices)
	{
		return false;
	}
	for (int i = 0; i < this->numVertices; i++)
	{
		if (vertex == NodeTable[i].data)
		{
			return false;
		}
	}
	NodeTable[this->numVertices].data = vertex;
	this->numVertices++;
	return true;
}

/*无向图的办法*/
template<class T, class E>
bool Graphlnk<T, E>::undirremoveVertex(int v)
{
	if (v < 0 || v >= this->numVertices)
	{
		return false;
	}
	Edge<T, E>* p, * s, * t;
	int  k;
	while (NodeTable[v].adj != NULL)
	{
		p = NodeTable[v].adj; k = p->dest;
		s = NodeTable[k].adj;
		t = NULL;
		while (s != NULL && s->dest != v)
		{
			t = s; s = s->link;
		}
		if (s != NULL)
		{
			if (t == NULL)
			{
				NodeTable[k].adj = s->link;
			}
			else
			{
				t->link = s->link;
			}
			delete s;
		}
		NodeTable[v].adj = p->link;
		delete p;
		this->numEdges--;
	}
	this->numVertices--;
	NodeTable[v].data = NodeTable[this->numVertices].data;
	p = NodeTable[v].adj = NodeTable[this->numVertices].adj;
	while (p != NULL)
	{
		s = NodeTable[p->dest].adj;
		while (s != NULL)
		{
			if (s->dest == this->numVertices)
			{
				s->dest = v;
				break;
			}
			else
			{
				s = s->link;
			}
		}
		p = p->link;
	}
	return true;
}

/*有向图的办法*/
template<class T, class E>
bool Graphlnk<T, E>::dirremoveVertex(int v)
{
	if (v < 0 || v >= this->numVertices)
	{
		return false;
	}
	Edge<T, E>* p, * q;
	p = NodeTable[v].adj;
	while (p != NULL)
	{
		NodeTable[v].adj = p->link;
		delete p;
		p = NodeTable[v].adj;
	}
	for (int i = 0; i < this->numVertices; i++)
	{
		if (i == v)
		{
			continue;
		}
		p = NodeTable[i].adj;
		q = p;
		while (p != NULL)
		{
			if (p->dest == v)
			{
				q->link = p->link;
				delete p;
				p = q->link;
			}
			else
			{
				q = p;
				p = p->link;
			}
		}
	}
	this->numVertices--;
	NodeTable[v].data = NodeTable[this->numVertices].data;
	p = NodeTable[v].adj = NodeTable[this->numVertices].adj;
	while (p != NULL)
	{
		Edge<T, E>* s = NodeTable[p->dest].adj;
		while (s != NULL)
		{
			if (s->dest == this->numVertices)
			{
				s->dest = v;
				break;
			}
			else
			{
				s = s->link;
			}
		}
		p = p->link;
	}
	return true;
}

template<class T, class E>
bool Graphlnk<T, E>::insertEdge(int v1, int v2, E weight)
{
	if (v1 < 0 || v1 >= this->numVertices || v2 < 0 || v2 >= this->numVertices)
	{
		return false;
	}
	Edge<T, E>* p = NodeTable[v1].adj;
	while (p != NULL && p->dest != v2)
	{
		p = p->link;
	}
	if (p != NULL)
	{
		return false;
	}
	p = new Edge<T, E>;
	p->dest = v2; p->cost = weight; p->link = NodeTable[v1].adj; NodeTable[v1].adj = p;
	this->numEdges++;
	return true;
}

template<class T, class E>
bool Graphlnk<T, E>::removeEdge(int v1, int v2)
{
	if (v1 < 0 || v1 >= this->numVertices || v2 < 0 || v2 >= this->numVertices)
	{
		return false;
	}
	Edge<T, E>* p = NodeTable[v1].adj, * q = NULL;
	while (p != NULL && p->dest != v2)
	{
		q = p; p = p->link;
	}
	if (p == NULL)
	{
		return true;
	}
	else
	{
		if (q == NULL)
		{
			NodeTable[v1].adj = p->link;
		}
		else
		{
			q->link = p->link;
		}
		delete p;
	}
	return true;
}

class PowerGridSystem
{
private:
	Graphlnk<char, int> G;//存储电网信息的图
	Edge<char,int>* mintreeedge;//存放最小生成树边的mintreeedge数组
	//菜单
	void menu();
	//建立顶点
	void buildvertex();
	//增加边
	void addedge();
	//用Prin算法生成最小生成树
	void buildmintreebyprim();
	//展示最小生成树
	void showmintreebyprim();

public:
	PowerGridSystem()
	{
		mintreeedge = NULL;
	}
	~PowerGridSystem()
	{
		if (mintreeedge != NULL)
		{
			delete[]mintreeedge;
		}
	}
	//使用系统
	void use();
};

void PowerGridSystem::menu()
{
	cout << "**                  电网造假模拟系统              **" << endl;
	cout << "====================================================" << endl;
	cout << "**                  A --- 创建电网顶点            **" << endl;
	cout << "**                  B --- 添加电网的边            **" << endl;
	cout << "**                  C --- 构造最小生成树          **" << endl;
	cout << "**                  D --- 显示最小生成树          **" << endl;
	cout << "**                  E --- 退出程序                **" << endl;
	cout << "====================================================" << endl;
}

void PowerGridSystem::buildvertex()
{
	int n;
	while (1)
	{
		cout << "请输入顶点的个数:";
		cin >> n;
		if (cin.good() && n > 0)
		{
			break;
		}
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
		}
		cout << "输入有误，请重新输入" << endl;
	}
	cout << "请依次输入电网各顶点的名称:" << endl;
	for (int i = 0; i < n; i++)
	{
		char c;
		cin >> c;
		if (G.getVertexPos(c) != -1)
		{
			cout << "顶点" << c << "重复输入" << endl;
			continue;
		}
		G.insertVertex(c);
	}
	cin.ignore(1024, '\n');
}
void PowerGridSystem::addedge()
{
	int n;
	while (1)
	{
		cout << "请输入添加边的个数:";
		cin >> n;
		if (cin.good() && n > 0)
		{
			break;
		}
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
		}
		cout << "输入有误，请重新输入" << endl;
	}
	for (int i = 0; i < n; i++)
	{
		char c1, c2;
		int v1, v2, co;
		while (1)
		{
			cout << "请输入两个顶点及边:";
			cin >> c1 >> c2 >> co;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(1024,'\n');
				cout << "输入有误，请重新输入" << endl;
			}
			else
			{
				break;
			}
		}
		v1 = G.getVertexPos(c1);
		v2 = G.getVertexPos(c2);
		if (v1 == -1 || v2 == -1)
		{
			cout << "顶点不存在！" << endl;
			continue;
		}
		if (co < 0)
		{
			cout << "边权值不合理！" << endl;
			continue;
		}
		if (G.insertEdge(v1, v2, co) == 0)
		{
			cout << "该两顶点间已存在边！" << endl;
			continue;
		}
		G.insertEdge(v2, v1, co);
	}
}

bool check(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		if (arr[i] == 0)
		{
			return false;
		}
	}
	return true;
}


void PowerGridSystem::buildmintreebyprim()
{
	char c;
	int fr;
	while (1)
	{
		cout << "请输入起始顶点:" ;
		cin >> c;
		fr = G.getVertexPos(c);
		if (fr == -1)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "顶点不存在！" << endl;
		}
		else
		{
			break;
		}
	}
	if (mintreeedge != NULL)
	{
		delete[]mintreeedge;
	}
	int size = G.NumberOfVertices();
	size = size * (size - 1) / 2;
	mintreeedge = new Edge<char,int>[size];
	int cnt = -1;

	int* connected = new int[size];
	for (int i = 0; i < size; i++)
	{
		connected[i] = 0;
	}
	connected[fr] = 1;
	
	PQueue<Edge<char,int>> pQ;
	for (int i = G.getFirstNeighbor(fr); i != -1; i = G.getNextNeighbor(fr, i))
	{
		Edge<char, int>* ptr = G.getEdge(fr, i);
		ptr->fr = fr;
		pQ.Push(*ptr);
	}
	int to;
	Edge<char, int> e;
	while (!pQ.isEmpty())
	{	
		int endflag = 1;
		while (!pQ.isEmpty())
		{
				e = pQ.Front();
				pQ.Pop();
				to = e.dest;
				if (connected[to] == 0)
				{
					endflag = 0;//如果此时有边可以被加入，则不结束
					break;
				}
		}
		if (endflag)
		{
			break;
		}
		connected[to] = 1;	
		fr = to;
		mintreeedge[++cnt] = e;
		if (check(connected, G.NumberOfVertices()))
		{
			break;
		}
		for (int i = G.getFirstNeighbor(fr); i != -1; i = G.getNextNeighbor(fr, i))
		{
			Edge<char, int>* ptr = G.getEdge(fr, i);
			ptr->fr = fr;
			pQ.Push(*ptr);
		}
	}

	if (check(connected, G.NumberOfVertices()))
	{
		cout << "生成Prim最小生成树！" << endl;
	}
	else
	{
		cout << "生成Prim最小生成树失败！" << endl;
		delete[] mintreeedge;
		mintreeedge = NULL;
	}
	delete[]connected;

}

void  PowerGridSystem::showmintreebyprim()
{
	if (mintreeedge == NULL)
	{
		cout << "无最小生成树" << endl;
		return;
	}
	cout << "最小生成树的顶点及边为:" << endl;
	int size = G.NumberOfVertices()-1;
	for (int i = 0; i < size; i++)
	{
		Edge<char, int> e = mintreeedge[i];
		int v1 = e.fr;
		int v2 = e.dest;
		char c1 = G.getValue(v1);
		char c2 = G.getValue(v2);
		int co = e.cost;
		cout << c1 << "-<" << co << ">-" << c2 << "\t";
	}
	cout << endl;
}

void  PowerGridSystem::use()
{
	menu();
	char op;
	while (1)
	{
		while (1)
		{
			cout << "\n请选择操作:";
			cin >> op;
			if (op >= 'A' && op <='E')
			{
				break;
			}
			cout << "输入有误，请重新输入" << endl;
		}
		if (op == 'E')
		{
			break;
		}
		switch (op)
		{
			case 'A':
				buildvertex();
				break;
			case 'B':
				addedge();
				break;
			case 'C':
				buildmintreebyprim();
				break;
			case 'D':
				showmintreebyprim();
				break;
		}
	}
	cout << "谢谢使用！" << endl;
}

int main()
{
	PowerGridSystem sys;
	sys.use();
	return 0;
}

/*
a b 8
b c 7
c d 5
d a 11
a c 18
b d 12

*/