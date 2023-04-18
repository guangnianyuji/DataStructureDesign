#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <limits>

#define DefaultSize 32

using namespace std;

//自定义实现String类
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

	int length()
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

	String& operator=(const char* ch);

	String& operator+=(const String& ob);

	char operator[](int num);

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
	return s;
}

String& String:: operator=(const String& ob)
{
	if (this != &ob)
	{
		delete[]ch;
		ch = new char[ob.maxLength + 1];
		if (ch == NULL)
		{
			cerr << "Allocation Error!\n";
		}
		maxLength = ob.maxLength;
		currentLength = ob.currentLength;
		strcpy(ch, ob.ch);
	}
	return *this;
}

String& String::operator=(const char* init)
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
char String::operator[](int num)
{
	if (num < 0 || num >= currentLength)
	{
		cerr << "out of range!\n";
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
	cin >> Str.ch;

	return cin;
}

ostream& operator<<(ostream& cout, const String& Str)
{
	cout << Str.ch;

	return cout;
}


//学生类
class Student
{
	friend istream& operator>>(istream&, Student&);
	friend ostream& operator<<(ostream&, const Student&);
private:
	String m_ID;
	String m_Name;
	String m_Sex;
	int m_Age;
	String m_Category;

public:
	Student(String id = "", String name = "", String sex = "", int age = 0, String category = "");

	Student& operator=(const Student& Stu);

	bool operator==(const Student& Stu)
	{
		return m_ID == Stu.m_ID;
	}

	String getID()
	{
		return m_ID;
	}

};

Student::Student(String id, String name, String sex, int age, String category) :
	m_ID(id), m_Name(name), m_Sex(sex), m_Age(age), m_Category(category) {}

Student& Student::operator=(const Student& Stu)
{
	m_ID = Stu.m_ID;
	m_Name = Stu.m_Name;
	m_Sex = Stu.m_Sex;
	m_Age = Stu.m_Age;
	m_Category = Stu.m_Category;
	return *this;
}

istream& operator>>(istream& cin, Student& Stu)
{
	cin >> Stu.m_ID >> Stu.m_Name >> Stu.m_Sex >> Stu.m_Age >> Stu.m_Category;

	return cin;
}

ostream& operator<<(ostream& cout, const Student& Stu)
{
	cout << Stu.m_ID << '\t' << Stu.m_Name << '\t' << Stu.m_Sex << '\t' << Stu.m_Age << '\t' <<
		Stu.m_Category;

	return cout;
}

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

	List(List<T>& L);

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

	List<T>& operator=(List<T>& L);

	void inputFront(T endTag);//前插输入Link，endTag为结束符号

	void inputFront(const int& num);//前插输入Link，有效节点num个

	void inputRear(T endTag);//后插输入Link，endTag为结束符号

	void inputRear(const int& num);//后插输入Link，有效节点num个
};

template<class T>
List<T>::List()
{
	first = new LinkNode<T>;
}

template<class T>
List<T>::List(List<T>& L)
{
	LinkNode<T>* srcptr = L.getHead();
	LinkNode<T>* desptr = first = new LinkNode<T>;
	while (srcptr->link != NULL)
	{
		desptr->link = new LinkNode<T>(srcptr->link->data);
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
	while (current != NULL)
	{
		cout << current->getData() << "\n";
		current = current->link;
	}
}

template<class T>
List<T>& List<T>::operator=(List<T>& L)
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
void List<T>::inputFront(const int& num)
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
void List<T>::inputRear(const int& num)
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

class TestRegistrationSystem
{
private:
	List<Student> StudentList;
public:
	TestRegistrationSystem();

	LinkNode<Student>* findById(const String& id);//按考号查找考生

	bool appendStudent();

	bool popStudent();

	bool findStudent();

	bool changeStudent();

	void displayStudents();

};

TestRegistrationSystem::TestRegistrationSystem()
{
	cout << "首先请建立考生信息系统\n";
	cout << "请输入考生人数：";
	int num;
	cin >> num;
	while (cin.fail() || num < 1)
	{
		cout << "输入人数有误，请重新输入!\n";
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "请输入考生人数：";
		cin >> num;
	}
	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！\n";
	StudentList.inputRear(num);
	displayStudents();
}

LinkNode<Student>* TestRegistrationSystem::findById(const String& id)
{
	Student stu = Student(id);
	return StudentList.search(stu);
}

bool TestRegistrationSystem::appendStudent()
{
	cout << "请输入你要插入的考生位置:";
	int position = 0;
	cin >> position;
	while (cin.fail() || position<1 || position>StudentList.length() + 1)
	{
		cout << "输入非法（插入位置应为正整数，且不超过当前人数+1）" << endl;
		cout << "请重新输入插入位置:";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> position;
	}
	Student stu;
	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;

	cin >> stu;

	while (findById(stu.getID()) != NULL)
	{
		cout << "插入失败，该考号已被使用，请重新输入" << endl;
		cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> stu;
	}
	if (StudentList.insert(position, stu))
	{
		cout << "插入成功！" << endl;
		displayStudents();
		return true;
	}
	return false;
}

bool TestRegistrationSystem::popStudent()
{
	String id = "";
	cout << "请输入要删除的考生的考号:" << endl;
	cin >> id;
	while (findById(id) == NULL)
	{
		cout << "该考生号对应的考生不存在，请重新输入考生号" << endl;
		cin >> id;
	}
	LinkNode<Student>* node = findById(id);
	cout << "你删除的考生信息是:" << node->getData() << endl;
	Student stu = Student(id);
	if (StudentList.remove(stu))
	{
		cout << "删除成功！" << endl;
		displayStudents();
		return true;
	}
	cout << "删除失败！" << endl;
	return false;
}

bool TestRegistrationSystem::findStudent()
{
	String id;
	cout << "请输入要查找的考生的考号:" << endl;
	cin >> id;
	if (findById(id) == NULL)
	{
		cout << "该考生号对应的考生不存在!" << endl;
		return false;
	}
	LinkNode<Student>* node = findById(id);
	cout << "你查找的考生信息是:" << "考号\t姓名\t性别\t年龄\t报考类别\t" <<
		node->getData() << endl;
	return true;
}

bool TestRegistrationSystem::changeStudent()
{
	String id;
	cout << "请输入要修改的考生的考号:" << endl;
	cin >> id;
	if (findById(id) == NULL)
	{
		cout << "该考生号对应的考生不存在!" << endl;
		return false;
	}
	LinkNode<Student>* node = findById(id);
	cout << "查找成功，请依次输入修改后的考号，姓名，性别，年龄及报考类别:" << endl;
	Student stu;
	cin >> stu;
	if (findById(stu.getID()) != NULL)
	{
		cout << "修改失败，该考生考号已存在！" << endl;
		return false;
	}
	node->setData(stu);
	cout << "修改成功！" << endl;
	displayStudents();
	return true;

}

void TestRegistrationSystem::displayStudents()
{
	cout << "考号\t姓名\t性别\t年龄\t报考类别\t" << endl;
	StudentList.output();
	cout << endl;
}

int main()
{
	TestRegistrationSystem system;
	cout << "请输入你要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << endl;
	int option = 0;
	do
	{
		cout << "请输入你要进行的操作:";
		cin >> option;
		switch (option)
		{
			case 1:
				system.appendStudent();
				break;
			case 2:
				system.popStudent();
				break;
			case 3:
				system.findStudent();
				break;
			case 4:
				system.changeStudent();
				break;
			case 5:
				system.displayStudents();
				break;
		}
	} while (option);
	cout << "谢谢使用！" << endl;
}
