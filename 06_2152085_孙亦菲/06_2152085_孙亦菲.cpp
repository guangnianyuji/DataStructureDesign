#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
using namespace std;
#define DefaultSize 20

class String
{
	friend istream& operator>>(istream&, String& Str);
	friend ostream& operator <<(ostream&, const String& Str);
private:
	int currentLength;
	int maxLength;
	char* ch;
public:
	String(int size = DefaultSize);

	String(const char* init);

	String(const String& ob);

	~String()
	{
		delete[]ch;
	}

	int length()const
	{
		return currentLength;
	}

	String operator()(int pos, int length);

	bool operator==(const String& ob)
	{
		return strcmp(ch, ob.ch) == 0;
	}

	bool operator!=(const String& ob)
	{
		return strcmp(ch, ob.ch) != 0;
	}

	String& operator=(const String& ob);

	String& operator+=(const String& ob);

	String& operator+=(const char c);

	char& operator[](int num)const;

	int fastFind(String& pat, int pos);


};
String::String(int size)
{
	maxLength = size;
	ch = new char[size + 1];
	if (ch == NULL)
	{
		cerr << "Allocation Error!\n";
	}
	currentLength = 0; ch[0] = '\0';
}
String::String(const char* init)
{
	int length = strlen(init);
	maxLength = length > DefaultSize ? length : DefaultSize;
	ch = new char[maxLength + 1];
	if (ch == NULL)
	{
		cerr << "Allocation Error!\n";
	}
	currentLength = length;
	strcpy(ch, init);
}
String::String(const String& ob)
{
	int length = ob.currentLength;
	maxLength = length > DefaultSize ? length : DefaultSize;
	ch = new char[maxLength + 1];
	if (ch == NULL)
	{
		cerr << "Allocation Error!\n";
	}
	currentLength = length;
	strcpy(ch, ob.ch);
}

String String::operator()(int pos, int length)
{
	String s;
	if (pos >= 0 && pos < currentLength && length>0 && pos + length - 1 < currentLength)
	{
		for (int i = 0; i < length; i++)
		{
			s.ch[i] = ch[pos + i];
		}
		s.ch[length] = '\0';
	}
	s.currentLength = strlen(s.ch);
	return s;
}

String& String:: operator=(const String& ob)
{
	if (this != &ob)
	{
		delete[]ch;
		ch = new char[ob.maxLength + 1];
		maxLength = ob.maxLength;
		currentLength = ob.currentLength;
		strcpy(ch, ob.ch);
	}
	return *this;
}
String& String::operator+=(const String& ob)
{
	char* temp = ch;
	int length = currentLength + ob.currentLength;
	maxLength = maxLength > length ? maxLength : length;
	ch = new char[maxLength + 1];
	if (ch == NULL)
	{
		cerr << "Allocation Error!\n";
		exit(1);
	}
	strcpy(ch, temp);
	strcat(ch, ob.ch);
	currentLength = length;
	delete[]temp;
	return *this;
}

String& String::operator+=(const char c)
{
	char* temp = ch;
	int length = currentLength + 1;
	maxLength = maxLength > length ? maxLength : length;
	ch = new char[maxLength + 1];
	if (ch == NULL)
	{
		cerr << "Allocation Error!\n";
		exit(1);
	}
	ch[currentLength] = c;
	currentLength = length;
	delete[]temp;
	return *this;
}
char& String::operator[](int num)const
{
	if (num < 0 || num >= currentLength)
	{
		cerr << "Out of Range!\n";
		exit(1);
	}
	return ch[num];
}
int String::fastFind(String& pat, int pos)
{
	int pLength = pat.length();
	int* next = new int[pLength];
	next[0] = -1;
	int j = 0, k = -1;
	while (j < pLength - 1)
	{
		if (k == -1 || ch[j] == ch[k])
		{
			j++; k++;
			next[j] = k;
		}
		else
		{
			k = next[k];
		}
	}
	int tPos = 0;
	int pPos = 0;
	while (tPos < currentLength && pPos < pLength)
	{
		if (pPos == -1 || ch[tPos] == ch[pPos])
		{
			tPos++;
			pPos++;
		}
		else
		{
			pPos = next[pPos];
		}
	}
	delete[]next;
	if (pPos < pLength)
	{
		return -1;
	}
	else
	{
		return tPos - pLength;
	}
}
istream& operator>>(istream& cin, String& Str)
{
	char* init = new char[DefaultSize * 5];
	cin >> init;
	int length = strlen(init);
	delete[]Str.ch;
	Str.ch = new char[length + 1];
	Str.currentLength = length;
	strcpy(Str.ch, init);

	return cin;
}

ostream& operator<<(ostream& cout, const String& Str)
{
	cout << Str.ch;

	return cout;
}

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
	LinkNode(const T item, LinkNode<T>* ptr = NULL)
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
	void setData(const T item)
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
		cerr << "Allocation Error!!";
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

template <class T>
class Tree;

template<class T>
class TreeNode
{
	friend class Tree<T>;
private:
	T data;
	TreeNode<T>* firstChild, * nextSibiling;
	TreeNode(T value, TreeNode<T>* fc=NULL, TreeNode<T>* ns=NULL)
		:data(value), firstChild(fc), nextSibiling(ns) {};
public:
	T getData()
	{
		return data;
	}
	void setData(T x)
	{
		data = x;
	}
};

template<class T>
class Tree
{
private:
	TreeNode<T>* root, * current;
	//从一个节点开始找，找到置current
	bool find(TreeNode<T>* p, T value);
	//移除一个子树
	void removeSubtree(TreeNode<T>*& p);
	//寻找双亲并置其为current
	bool findParent(TreeNode<T>* t, T x);
public:
	Tree()
	{
		root = current = NULL;
	}
	~Tree()
	{
		removeSubtree(root);
	}
	//置root为current
	bool Root()
	{
		if (root == NULL)
		{
			return false;
		}
		else
		{
			current = root;
			return true;
		}
	}
	//设置root
	void setRoot(T x)
	{
		TreeNode<T>* p = new TreeNode<T>(x);
		current=root = p;
	}
	//现在指向的是否是根
	bool isRoot()
	{
		return root == current;
	}
	//置current为目前current的双亲
	bool parent(T x)
	{
		return findParent(root, x);
	}
	//置current为目前current的长子
	bool firstChild();
	//置current为目前current兄弟
	bool nextSibling();
	//寻找值为x的节点，设为current
	bool find(const T x)
	{
		return find(root, x);
	}
	//添加孩子
	bool addChild(T parent, T child);
	//改变current的值
	void changeData(T x)
	{
		current->setData(x);
	}
	//移除一个子树
	void removeSubtree()
	{
		removeSubtree(current->firstChild);
	}
	//访问current的数据
	T visit()const
	{
		return current->getData();
	}
};

template<class T>
void Tree<T>::removeSubtree(TreeNode<T>*& p)
{
	if (p == NULL)
	{
		return;
	}
	TreeNode<T>* q = p->firstChild,*t;
	while (q != NULL)
	{
		t = q->nextSibiling;
		removeSubtree(q);
		q =t;
	}
	delete p;
	p = NULL;
}

template<class T>
bool Tree<T>::firstChild()
{
	if (current->firstChild != NULL)
	{
		current = current->firstChild;
		return true;
	}
	else
	{
		return false;
	}
}

template<class T>
bool Tree<T>::nextSibling()
{
	if (current->nextSibiling != NULL)
	{
		current = current->nextSibiling;
		return true;
	}
	else
	{
		return false;
	}
}

template<class T>
bool Tree<T>::addChild(T parent, T child)
{
	if (find(parent) == false)
	{
		return false;
	}
	TreeNode<T>* p = new TreeNode<T>(child);
	if (firstChild() == false)
	{
		TreeNode<T>* p = new TreeNode<T>(child);
		current->firstChild = p;
	}
	else
	{
		while (nextSibling() == true);
		current->nextSibiling = p;
	}
	return true;
}

template<class T>
bool Tree<T>::findParent(TreeNode<T>* p, T x)
{
	TreeNode<T>* q = p->firstChild;
	while (q != NULL)
	{
		if (q->getData() == x)
		{
			current = p;
			return true;
		}
		if (findParent(q, x))
		{
			return true;
		}
		q = q->nextSibiling;
	}
	return false;
}

template<class T>
bool Tree<T>::find(TreeNode<T>* p, T value)
{
	if (p->data == value)
	{
		current = p;
		return true;
	}
	TreeNode<T>* q = p->firstChild;
	while (q != NULL)
	{
		if (find(q, value))
		{
			return true;
		}
		q = q->nextSibiling;
	}
	return false;
}


class Genealogy
{
private:
	Tree<String> gTree;
	void menu();
public:
	Genealogy();
	//输出族长
	void getHeader();
	//输出s的所有子孙,按第几代分类输出
	void getChildren(String s);
	//组建家庭
	void bulidfamily();
	//添加子女
	void addChild();
	//解散家庭
	void disbandfamily();
	//改变姓名
	void changeName();
	//使用
	void use();
};

void Genealogy::getHeader()
{
	if (gTree.Root() == false)
	{
		cout << "此家族已不存在！" << endl;;
	}
	cout << "此家谱的祖先是：";
	 cout <<gTree.visit()<< endl;
}

void Genealogy::getChildren(String s)
{
	static const char str[][5] = { "一","二","三","四","五","六","七","八","九","十" };
	if (gTree.find(s) == false)
	{
		cout << "家族中无此人！" << endl;
		return;
	}
	if (gTree.firstChild() == false)
	{
		cout << "此人无子孙" << endl;
		return;
	}
	struct child
	{
		int gen;
		String name;
		child(int i=0, String s="")
		{
			gen = i;
			name = s;
		}
	};
	gTree.find(s);
	int nowgen = 0;
	LinkedQueue<child> q;
	q.Push(child(0, gTree.visit()));
	int tag = 0;
	while (!q.isEmpty())
	{
		child tc = q.Front();
		q.Pop();
		int gen = tc.gen;
		if (gen > nowgen)
		{
			nowgen = gen;
			if (tag)
			{
				cout << "\n";
			}
			cout << s << "的第";
			if (nowgen / 10)
			{
				cout << str[nowgen / 10 - 1];
			}
			if (1 + (nowgen - 1) % 10)
			{
				cout << str[(nowgen - 1) % 10];
			}
			cout << "代子孙是：";
		}
		if (tag)
		{
			cout << tc.name << " ";
		}
		tag = 1;
		gTree.find(tc.name);
			if (gTree.firstChild() == true)
			{
				q.Push(child(gen+1, gTree.visit()));
				while (gTree.nextSibling() == true)
				{
					q.Push(child(gen, gTree.visit()));
				}
			}
	}
	cout << "\n";
}

void Genealogy::bulidfamily()
{
	cout << "请输入要建立家庭的人的姓名：";
	String s;
	cin >> s;
	cin.ignore(1024, '\n');
	if (gTree.find(s) == false)
	{
		cout << "家族中无此人！" << endl;
		return;
	}
	if (gTree.firstChild() == true)
	{
		cout << "此人已建立家庭！" << endl;
		return;
	}
	int num = 0;
	while (1)
	{
		cout << "请输入" << s << "的儿女人数：";
		cin >> num;
		if (cin.good() && num > 0)
		{
			break;
		}
		cout << "输入有误，请重新输入" << endl;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
		}
	}
	cin.ignore(1024, '\n');
	cout << "请依次输入" << s << "的儿女的姓名：";
	for (int i = 0; i < num; i++)
	{
		String t;
		cin >> t;
		gTree.addChild(s, t);
	}
	cin.ignore(1024, '\n');
	getChildren(s);
}

void Genealogy::addChild()
{
	cout << "请输入要添加儿子（或女儿）的人的姓名：";
	String s;
	cin >> s;
	if (gTree.find(s) == false)
	{
		cout << "家族中无此人！" << endl;
		return;
	}
	if (gTree.firstChild() == false)
	{
		cout << "此人还没有组建家庭！" << endl;
		return;
	}
	cin.ignore(1024, '\n');
	gTree.find(s);
	cout << "请输入" << s << "要添加儿子（或女儿）的人的姓名：";
	String t;
	cin >> t;
	cin.ignore(1024, '\n');
	gTree.addChild(s, t);
	getChildren(s);
}

void Genealogy::disbandfamily()
{
	cout << "请输入要解散家庭的人的姓名：";
	String s;
	cin >> s;
	if (gTree.find(s) == false)
	{
		cout << "家族中无此人！" << endl;
		return;
	}
	
	cin.ignore(1024, '\n');
	cout << "要解散家庭的人是：" << s << endl;
	getChildren(s);
	gTree.find(s);

	gTree.removeSubtree();
}

void Genealogy::changeName()
{
	cout << "请输入要更改姓名的人的目前姓名：";
	String s;
	cin >> s;
	if (gTree.find(s) == false)
	{
		cout << "家族中无此人！" << endl;
		return;
	}
	cin.ignore(1024, '\n');
	cout << "请输入更改后的姓名：";
	String t;
	cin >> t;
	cin.ignore(1024, '\n');
	gTree.changeData(t);
	cout << s << "已更名为" << t << endl;
}

void Genealogy::use()
{
	int op;
	while (1)
	{
		cout << "\n请选择要执行的操作：";
		op = getchar();
		cin.ignore(1024, '\n');
		if (op < 'A' || op>'E')
		{
			cout << "没有此项操作！" << endl;
			continue;
		}
		if (op == 'E')
		{
			break;
		}
		switch (op)
		{
			case 'A':
				bulidfamily();
				break;
			case 'B':
				addChild();
				break;
			case 'C':
				disbandfamily();
				break;
			case 'D':
				changeName();
				break;
		}
	}
	cout << "谢谢使用！" << endl;
}

Genealogy::Genealogy()
{
	menu();
	cout << "首先建立一个家谱！\n";
	cout << "请输入祖先的姓名：";
	String s;
	cin >> s;
	cin.ignore(1024, '\n');
	gTree.setRoot(s);
	getHeader();
}


void Genealogy::menu()
{
	cout << "**                  家谱管理系统                  **" << endl;
	cout << "====================================================" << endl;
	cout << "**           请选择要执行的操作  ：               **" << endl;
	cout << "**                  A --- 完善家庭                **" << endl;
	cout << "**                  B --- 添加家庭成员            **" << endl;
	cout << "**                  C --- 解散局部家庭            **" << endl;
	cout << "**                  D --- 更改家庭成员姓名        **" << endl;
	cout << "**                  E --- 退出程序                **" << endl;
	cout << "====================================================" << endl;
}

int main()
{
	Genealogy g;
	g.use();
	return 0;
}
