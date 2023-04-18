#include<iostream>
using namespace std;
#define DefaultVertices 100

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
	bool removeEdge(int v1, int v2);//得到某元素在图中的位置
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
Edge<T, E>* Graphlnk<T, E>::getEdge(int v1, int v2)
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


class AOE
{
private:
	Graphlnk<int, int>G;
	//入度数组 
	int* incount;
	//出度数组
	int* outcount;
	//拓扑排序检验有无环存在
	int TopologicalSort();
public:
	AOE();
	~AOE()
	{
		if (incount != NULL)
		{
			delete[]incount;
		}
	}
	//求关键路径
	void CriticalPath();
};

AOE::AOE()
{
	int n;
	cin >> n;
	//插入顶点
	for (int i = 1; i <= n; i++)
	{
		G.insertVertex(i);
	}
	
	incount = new int[n];
	for (int i = 0; i < n; i++)
	{
		incount[i] = 0;
	}

	outcount = new int[n];
	for (int i = 0; i < n; i++)
	{
		outcount[i] = 0;
	}

	int m;
	cin >> m;
	//插入边
	for (int i = 0; i < m; i++)
	{
		int fr, to, co;
		cin >> fr >> to >> co;
		//每个编号代表顶点的下标位置恰好为编号减1
		G.insertEdge(fr - 1, to - 1, co);
		outcount[fr - 1]++;
		incount[to - 1]++;
	}
}
int AOE::TopologicalSort()
{
	int size = G.NumberOfVertices();

	int top = -1;//栈顶

	int* count = new int[size];//复制入度数组兼入度为0顶点栈

	for (int i = 0; i < size; i++)
	{
		count[i] = incount[i];
		if ( count[i] == 0)
		{
			 count[i] = top;
			top = i;
		}
	}

	int u, v;

	for (int cnt = 0; cnt < size; cnt++)
	{
		if (top == -1)//提前栈空，有结点从没进来过，存在环
		{
			delete[]count;
			return false;
		}
		else
		{
			u = top;
			top =  count[top];
			for (v = G.getFirstNeighbor(u); v != -1; v = G.getNextNeighbor(u, v))
			{
				 count[v]--;
				if ( count[v] == 0)//压入入度为0的栈
				{
					 count[v] = top;
					top = v;
				}
			}
		}
	} 
	delete[]count;
	return true;
}
void AOE::CriticalPath()
{
	if (TopologicalSort() == 0)
	{
		cout << "0";
		return;
	}

	int n = G.NumberOfVertices();
	int* Ve = new int[n];//某节点最早开始时间
	int* Vl = new int[n];//某节点最晚开始时间

	for (int i = 0; i < n; i++)
	{
		Ve[i] = 0;
		Vl[i] = 0x7fffffff;
	}

	//将正向遍历时的队列看作一个容器，反向遍历时当作一个栈来反向弹栈即可
	int* vqueue = new int[n];
	int hptr=0,tptr =0;//队列头，队列尾
	

	for (int i = 0; i < n; i++)
	{
		if (incount[i] == 0)
		{
			vqueue[tptr++] = i;
		}
	}

	for (int i = 0; i < n; i++)
	{
		int u = vqueue[hptr++];
		for (int v = G.getFirstNeighbor(u); v != -1; v = G.getNextNeighbor(u, v))
		{
			int co = G.getWeight(u, v);
			if (Ve[u] + co > Ve[v])
			{
				Ve[v] = Ve[u] + co;
			}
			incount[v]--;
			if (incount[v] == 0)
			{
				vqueue[tptr++] = v;
			}
		}
	}
	//得到最早结束时间，总时间
	int time = 0;
	for (int i = 0; i < n; i++)
	{
		if (outcount[i] == 0)
		{
			if (Ve[i] > time)
			{
				time = Ve[i];
			}
		}
	}
	cout << time << endl;
	//所有汇点的Vl为time
	for (int i = 0; i < n; i++)
	{
		if (outcount[i] == 0)
		{
			Vl[i] = time;
		}
	}
	//根据相反的入队顺序遍历AOE图
	while(tptr--)
	{
		int u = vqueue[tptr];
		for (int v = G.getFirstNeighbor(u); v != -1; v = G.getNextNeighbor(u, v))
		{
			int co = G.getWeight(u, v);
			if (Vl[v] -co < Vl[u])
			{
				Vl[u] = Vl[v] - co;
			}
		}
	}
	delete[]vqueue;
	class path
	{
		public:
			int u, v;
			path() {};
			path(int uu, int vv)
			{
				u  = uu; v = vv;
			}
			bool operator<(path& p)
			{
				return this->u < p.u;
			}

	};

	path* p = new path[n];
	int pcnt = 0;

	for (int i = 0; i < n; i++)
	{
		int u = i;
		for (int v = G.getFirstNeighbor(u); v != -1; v = G.getNextNeighbor(u, v))
		{
			int Ae = Ve[u];
			int Al = Vl[v] - G.getWeight(u, v);
			if (Ae == Al)
			{
				p[pcnt++] = path(u, v);
			}
		}
	}

	//简单冒泡排序，保证起点编号小的在前且稳定
	for (int i = 0; i < pcnt ; i++)
	{
		for (int j = 0; j < pcnt -1- i; j++)
		{
			if (p[j + 1] < p[j])
			{
				path tp = p[j + 1];
				p[j + 1] = p[j];
				p[i] = tp;
			}
		}
	}

	for (int i = 0; i < pcnt; i++)
	{
		cout << p[i].u+1 << "->" << p[i].v+1 << endl;
	}

	delete[]p;
	delete[]Ve;
	delete[]Vl;
}

int main()
{
	AOE A;
	A.CriticalPath();
	return 0;
}