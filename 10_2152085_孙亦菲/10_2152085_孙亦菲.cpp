#include<iostream>
#include<ctime>
using namespace std;

void show(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}
template<class T>
class sortSystem
{
private:
	void menu();
	void message(char* str, int time, long long change, long long comp);
	long long change;
	long long comp;

	void bubbleSort(T arr[], int n);
	void selectSort(T arr[], int n);
	void insertSort(T arr[], int n);
	void shellSort(T arr[], int n);
	
	void quickSort(T arr[], int n,int low,int high);
	int partition(T arr[], int low, int high);

	void heapSort(T arr[], int n);
	void buildmaxheap(T arr[], int n);
	void headadjust(T arr[], int k, int n);

	void merge(T arr[],int n, int low, int mid, int high);
	void mergeSort(T arr[],int n, int low,int high, int firstflag);

	void radixSort(int arr[], int n);
public:
	void use();
};

template<class T>
void sortSystem<T>::menu()
{
	cout << "**                 排序算法比较                   **" << endl;
	cout << "====================================================" << endl;
	cout << "**                 1 --- 冒泡排序                 **" << endl;
	cout << "**                 2 --- 选择排序                 **" << endl;
	cout << "**                 3 --- 直接插入排序             **" << endl;
	cout << "**                 4 --- 希尔排序                 **" << endl;
	cout << "**                 5 --- 快速排序                 **" << endl;
	cout << "**                 6 --- 堆排序                   **" << endl;
	cout << "**                 7 --- 归并排序                 **" << endl;
	cout << "**                 8 --- 基数排序                 **" << endl;
	cout << "**                 9 --- 退出程序                 **" << endl;
	cout << "====================================================" << endl;
}

template<class T>
void sortSystem<T>::message(char*str,int time,long long change,long long comp)
{
	cout << endl;
	cout << str << "所用时间：\t" << time <<"\t毫秒" << endl;
	cout << str << "交换次数：\t" << change << "\t次" << endl;
	cout << str << "比较次数：\t" <<comp << "\t次" << endl;
}

template<class T>
void sortSystem<T>::bubbleSort(T arr[],int n)
{
	clock_t start,end;
	int flag ;
	start = clock();

	change = 0;
	comp = 0;

	for (int i = 0; i < n; i++)
	{
		flag = 1;
		for (int j = 0; j < n -1- i; j++)
		{
			comp++;
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = temp;
				flag = 0;
				change++;
			}
		}
		if (flag)
		{
			break;
		}
	}
	end = clock();
	char str[20] = "冒泡排序";
	message(str, end - start, change, comp);
}

template<class T>
void sortSystem<T>::selectSort(T arr[], int n)
{
	clock_t start, end;
	int minpl;
	 change = 0;
	 comp = 0;
	start = clock();
	for (int i = 0; i < n; i++)
	{
		minpl = i;
		for (int j = i + 1; j < n; j++)
		{
			comp++;
			if (arr[j] < arr[minpl])
			{
				minpl = j;
			}
		}
		int temp = arr[i];
		arr[i] = arr[minpl];
		arr[minpl] = temp;
		change++;
	}
	end = clock();
	char str[20] = "选择排序";
	message(str, end - start, change, comp);
}

template<class T>
void sortSystem<T>::insertSort(T arr[], int n)
{
	clock_t start, end;
	 change = 0;
	comp = 0;
	start = clock();
	for (int i = 1; i < n; i++)
	{
		int temp = arr[i];
		int j = i - 1;
		for ( ; j >= 0; j--)
		{
			comp++;
			if (temp < arr[j])
			{
				change++;
				arr[j + 1] = arr[j];
			}
			else
			{
				break;
			}
		}
		change++;
		arr[j + 1]= temp;
	}
	end = clock();
	char str[20] = "插入排序";
	message(str, end - start, change, comp);
}

template<class T>
void sortSystem<T>::shellSort(T arr[], int n)
{
	clock_t start, end;
	start = clock();
	change = 0;
	  comp = 0;
	for (int gap = n / 2; gap >= 1; gap = gap / 2)
	{
		for (int i = gap; i < n; i++)
		{
			int temp = arr[i];
			int j = i - gap;
			for (; j >= 0; j = j - gap)
			{
				comp++;
				if (temp < arr[j])
				{
					change++;
					arr[j + gap] = arr[j];
				}
				else
				{
					break;
				}
			}
			change++;
			arr[j + gap] = temp;
		}
	}

	end = clock();
	char str[20] = "希尔排序";
	message(str, end - start, change, comp);
}

template<class T>
int sortSystem<T>::partition(T arr[], int low, int high)
{
	T pivot = arr[low];
	while (low < high)
	{
		comp++;
		while (low < high && arr[high] >= pivot)
		{
			high--;
			comp++;
		}
		arr[low] = arr[high];
		comp++;
		while (low < high && arr[low] <= pivot)
		{
			low++;
			comp++;
		}
		arr[high] = arr[low];
		change++;
	}
	arr[low] = pivot;
	change++;
	return low;
}

//=快速排序
template<class T>
void sortSystem<T>::quickSort(T arr[], int firstflag_n,int low,int high)
{
	 clock_t begin, end;
	if (firstflag_n)
	{
		comp = 0;
		change = 0;
		low = 0;
		high = firstflag_n - 1;
		begin = clock();
	}
	if (low < high)
	{
		int pivot = partition(arr, low, high);
		quickSort(arr, 0,low, pivot - 1);
		quickSort(arr,0,pivot + 1, high);
	}
	if (firstflag_n)
	{
		end = clock();
		char str[20] = "快速排序";
		message(str, end - begin, change, comp);
	}
}

template<class T>
void sortSystem<T>::buildmaxheap(T arr[], int n)
{
	for (int i = (n - 1) / 2; i >= 0; i--)
	{
		headadjust(arr, i, n);
	}
}

//数组，需shiftdown的元素，当前元素个数
template<class T>
void sortSystem<T>::headadjust(T arr[], int k, int n)
{
	int temp = arr[k];
	for (int i = 2 * k+1; i < n; i = 2*k+1)
	{
		comp++;
		if (i + 1 < n && arr[i] < arr[i + 1])
		{
			i++;
		}
		comp++;
		if (temp > arr[i])
		{
			break;
		}
		change++;
		arr[k] = arr[i];
		k = i;
	}
	arr[k] = temp;
	change++;
}

template<class T>
void sortSystem<T>::heapSort(T arr[], int n)
{
	comp = 0;
	change = 0;
	clock_t begin, end;
	begin = clock();
	buildmaxheap(arr, n);
	for (int i = n - 1; i > 0; i--)
	{
		int temp = arr[0];
		arr[0]=arr[i];
		arr[i] = temp;
		change++;
		headadjust(arr, 0, i);		
	}
	end = clock();
	char str[20] = "堆排序";
	message(str, end - begin, change, comp);
}

template<class T>
void sortSystem<T>::merge(T arr[], int n,int low,int mid, int high)
{
	T* tarr = new T[n];
	for (int i = low; i <= high; i++)
	{
		tarr[i] = arr[i];
	}
	int i, j, k;
	for (i = low, j = mid + 1, k = low; i <= mid && j <= high; k++)
	{
		comp++;
		change++;
		if (tarr[i] <= tarr[j])
		{
			arr[k] = tarr[i];
			i++;
		}
		else
		{
			arr[k] = tarr[j];
			j++;
		}
	}
	while (i <= mid)
	{
		arr[k] = tarr[i];
		k++;
		i++;
		change++;
	}
	while (j <= high)
	{
		arr[k] = tarr[j];
		k++;
		j++;
		change++;
	}
	delete[]tarr;
}

template<class T>
void sortSystem<T>::mergeSort(T arr[], int n,int low, int high,int firstflag)
{
clock_t begin, end = 0;
if (firstflag)
{
	comp = 0;
	change = 0;
	begin = clock();
}
if (low < high)
{
	int mid = (low + high) / 2;
	mergeSort(arr, n, low, mid, 0);
	mergeSort(arr, n, mid + 1, high, 0);
	merge(arr, n, low, mid, high);
}
if (firstflag)
{
	end = clock();
	char str[20] = "归并排序";
	message(str, end - begin, change, comp);
}
}

template<class T>
void sortSystem<T>::radixSort(int arr[], int n)
{
	clock_t begin, end;
	comp = 0;
	change = 0;
	begin = clock();

	int radix = 2048;
	int move[3] = { 0,11,22 };
	int* temparr = new int[n];
	int* count = new int[radix];

	for (int i = 0; i < 3; i++)
	{
		for (int i = 0; i < radix; i++)
		{
			count[i] = 0;
		}
		for (int k = 0; k < n; k++)
		{
			count[(arr[k] >> move[i]) & 0x7ff]++;
		}
		for (int j = 1; j < radix; j++)
		{
			count[j] += count[j - 1];
		}
		for (int k = n-1; k >=0; k--)
		{
			int index = count[(arr[k] >> move[i]) & 0x7ff] - 1;
			temparr[index] = arr[k];
			count[(arr[k] >> move[i]) & 0x7ff] --;
		}
		for (int k = 0; k < n; k++)
		{
			change++;
			arr[k] = temparr[k];
		}
		//show(arr, n);
	}
	end = clock();
	delete[]temparr;
	delete[]count;
	char str[20] = "基数排序";
	message(str, end - begin, change, comp);
}

void buildrandomarr(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand();
	}
}



template<class T>
void sortSystem<T>::use()
{
	menu();
	int n;
	while (1)
	{
		cout << "请输入要产生的随机数个数:";
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
	int* oriarr = new int[n];
	buildrandomarr(oriarr, n);
	int* arr = new int[n];
	int op;
	//测试4.3使用
	//int tag = 1;
	
	while (1)
	{
		while (1)
		{
			cout << "\n请选择排序算法:";
			cin >> op;
			if(cin.good() && op > 0 && op < 10)
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
		if (op == 9)
		{
			break;
		}
		for (int i = 0; i < n; i++)
		{
			arr[i] = oriarr[i];
		}
		//show(arr, n);
		switch (op)
		{
			case 1:
				bubbleSort(arr, n);
				break;
			case 2:
				selectSort(arr, n);
				break;
			case 3:
				insertSort(arr, n);
				break;
			case 4:
				shellSort(arr, n);
				break;
			case 5:
				quickSort(arr, n,0,n-1);
				break;
			case 6:
				heapSort(arr, n);
				break;
			case 7:
				mergeSort(arr, n,0,n-1,1);
				break;
			case 8:
				radixSort(arr, n);
				break;
		}
		//show(arr, n);
		//测试4.3使用
		/*if (tag)
		{
			for (int i = 0; i < n; i++)
			{
				oriarr[i] = arr[i];
			}
			tag = 0;
		}*/
	}
	cout << "谢谢使用!" << endl;
	delete[]oriarr;
	delete[]arr;
}


int main()
{
	/* 生成伪随机数的种子，只需在程序开始时执行一次即可 */
	srand((unsigned int)(time(0)));

	sortSystem<int> T;
	T.use();
	return 0;
}