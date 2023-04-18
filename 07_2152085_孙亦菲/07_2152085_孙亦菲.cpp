#include<iostream>
using namespace std;
#define DefaultSize  10005

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
	void show()
	{
		for (int i = 0; i < currentSize; i++)
		{
			cout << arr[i] << " ";
		}
		cout << endl;
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
		if (temp > arr[i])
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

int main()
{
	int N;
	while (1)
	{
		cin >> N;
		if (cin.good() && N > 0)
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
	PQueue<int> pQ;
	for (int i = 0; i < N; i++)
	{
		int temp;
		cin >> temp;
		pQ.Push(temp);
	}
	int ans = 0;
	while (pQ.Size() > 1)
	{
		int t1 = pQ.Front();
		pQ.Pop();
		int t2 = pQ.Front();
		pQ.Pop();
		ans += t1 + t2;
		pQ.Push(t1 + t2);
	}
	cout << ans<<endl;
	return 0;
}
 