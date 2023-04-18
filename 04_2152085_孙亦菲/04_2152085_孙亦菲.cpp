#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdlib>
#include<cstring>
#define DefaultSize 20
using namespace std;

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
    s.currentLength=strlen(s.ch);
    return s;
}

String& String:: operator=(const String& ob)
{
    if (this != &ob)
    {
        delete[]ch;
        ch = new char[ob.maxLength+ 1] ;
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
    cin.getline(init, DefaultSize * 5, '\n');
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

//节点类
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
class Stack
{
private:
    LinkNode<T>* top;
public:
    Stack() :top(NULL) {};
    ~Stack()
    {
        makeEmpty();
        delete top;
    }
    Stack(const Stack<T>& s);

    Stack<T>& operator=(const Stack<T>& s);

    void makeEmpty();

    void Push(const T x);

    bool Pop();

    bool isEmpty()const
    {
        return top == NULL;
    }
    T getTop()
    {
        return top->getData();
    }
    int getSize()const;

    Stack<T> reverse()const;

    void output()const;

};

template<class T>
 Stack<T>::Stack(const Stack<T>& s)
{
    top = NULL;
    makeEmpty();

    T memory[10 * DefaultSize];
    int cnt = -1;
    LinkNode<T>* p = s.top;
    while (p != NULL)
    {
        memory[++cnt] = p->getData();
        p = p->link;
    }
    for (int i = cnt; i >= 0; i--)
    {
        Push(memory[i]);
    }
}

 template<class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& s)
 {
     makeEmpty();

     T memory[10 * DefaultSize];
     int cnt = -1;
     LinkNode<T>* p = s.top;
     while (p != NULL)
     {
         memory[++cnt] = p->getData();
         p = p->link;
     }
     for (int i = cnt; i >= 0; i--)
     {
         Push(memory[i]);
     }
     return *this;
 }


template<class T>
void Stack<T>::makeEmpty()
{
    LinkNode<T>* p;
    while (top != NULL)
    {
        p = top;
        top = top->link;
        delete p;
    }
}

template<class T>
void Stack<T>::Push(const T x)
{
    top = new LinkNode<T>(x, top);
    if (top == NULL)
    {
        cerr << "Allocation Error!\n";
        exit(1);
    }
}

template<class T>
bool Stack<T>::Pop()
{
    if (isEmpty())
    {
        return false;
    }
    LinkNode<T>* p = top;
    top = top->link;
  
    delete p;
    return true;
}

template<class T>
int Stack<T>::getSize()const
{
    int k = 0;
    LinkNode<T>* p = top;
    while (p != NULL)
    {
        k++;
        p = p->link;
    }
    return k;
}

template<class T>
Stack<T> Stack<T>::reverse()const
{
    Stack<T> s;
    LinkNode<T>* p = top;
    while (p != NULL)
    {
        s.Push(p->getData());
        p = p->link;
    }
    return s;
}

template<class T>
void  Stack<T>::output()const
{
    LinkNode<T>* p = top;
    while (p!=NULL)
    {
        cout << p->getData();
        p = p->link;
        if (p != NULL)
        {
            cout << " ";
        }
    }
}


int priorLevel(char c)
{
    switch (c)
    {
        case '(':
            return 0;
            break;
        case '+':
            return 1;
            break;
        case '-':
            return 1;
            break;
        case '*':
            return 2;
            break;
        case '/':
            return 2;
            break;
        default:
            return -1;
    }
}

inline void error()
{
    cout << "中缀表达式输入有误，程序结束！" << endl;
    exit(0);
}

bool numCheck(const String& s)
{
    bool pointflag = 0;//此时是否能出现小数点
    bool existpointflag = 0;//此时是否已经有过小数点
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            pointflag = 1;
            continue;
        }
        else if (s[i] == '.')
        {
            if (!pointflag||existpointflag)
            {
                return false;
            }
            existpointflag = 1;
            continue;
        }
        else 
        {
            return false;
        }
    }
    return true;
}

void spaceRecord(int spaceplace[], const String& s, int& spacecnt)
{
    spaceplace[0] = -1;

    int sum = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == ' ')
        {
            spaceplace[++spacecnt] = i;
            continue;
        }
        sum++;
        if (sum > DefaultSize)
        {
            error();
        }

    }
    spaceplace[++spacecnt] = s.length();
}

int main()
{
    Stack<String> ansStack;//答案栈
    Stack<String> operatorStack;//运算符栈
    int operatorflag = 0;//当前是否能输入运算符
    int numberflag = 1;//当前是否能输入数字
    int leftparentheseNum = 0;//左括号个数

    String InputString;
    cin >> InputString;

    int spaceplace[20] = {0};
    int spacecnt = 0;
    
    //记录空格位置
    spaceRecord(spaceplace, InputString, spacecnt);

    String nowS;
    for(int i=0;i<spacecnt&&i<DefaultSize;i++)
    { 
        //取两空格间字符串
        nowS = InputString(spaceplace[i] + 1, spaceplace[i + 1] - spaceplace[i] - 1);
        if (nowS.length() == 0)
        {
            continue;
        }
        //cout << nowS << endl;

        bool flag = 1;
        char ch = nowS[0];
        //输入了左括号
        if (ch == '(')
        {
            if (nowS.length() > 1)
            {
                flag = 0;
            }
            else
            {
                operatorStack.Push(nowS);
                leftparentheseNum++;
                operatorflag = 0;
                numberflag = 1;
            }
        }
        //输入了右括号
        else if (ch == ')')
        {
            if (!leftparentheseNum)
            {
                flag = 0;
            }
            else
            {
                leftparentheseNum--;
                while (1)
                {
                    String temp = operatorStack.getTop();
                    operatorStack.Pop();
                    if (temp == "(")
                    {
                        break;
                    }
                    ansStack.Push(temp);
                }
                operatorflag = 1;
                numberflag = 0;
            }
         }
        //输入了数字
        else if (numberflag&&ch >= '0' && ch <= '9')
        {
            flag = numCheck(nowS);
            ansStack.Push(nowS);
            operatorflag = 1;
            numberflag = 0;
        }
        //输入了带符号的数字
        else if (numberflag && (ch == '+' || ch == '-') && nowS.length() > 1)
        {
            flag = numCheck(nowS(1, nowS.length()-1));
            if (ch == '+')
            {
                ansStack.Push(nowS(1, nowS.length() - 1));
            }
            else
            {
                ansStack.Push(nowS);
            }
            operatorflag = 1;
            numberflag = 0;
        }
        //输入了运算符
        else if (operatorflag &&(ch == '+' || ch == '-'|| ch == '*' || ch == '/') && nowS.length() ==1)
        {
                flag = 1;
                operatorflag = 0;
                while (!operatorStack.isEmpty())
                {
                    if (priorLevel(ch) > priorLevel(operatorStack.getTop()[0]))
                    {
                        break;
                    }
                    else
                    {
                        ansStack.Push((operatorStack.getTop()));
                        operatorStack.Pop();
                    }
                }
                operatorStack.Push(nowS);
                operatorflag = 0;          
                numberflag = 1;
        }
        //以上情况都不符，错误
        else
        {
            flag = 0;
        }
        //如果有错误情况，进入error
        if (!flag)
        {
            error();
        }
    }
    //将运算符栈中剩余运算符进入答案栈
    while (!operatorStack.isEmpty())
    {
        String temp = operatorStack.getTop();
        operatorStack.Pop();
        ansStack.Push(temp);
    }
    //如果左括号剩余/还需输入数字/答案栈为空 ,则error
    if (leftparentheseNum||numberflag||ansStack.isEmpty())
    {
        error();
    }

    //翻转栈
    ansStack = ansStack.reverse();
    //输出栈
    ansStack.output();
   cout<<endl;
    return 0;
}