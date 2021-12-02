#include "stdio.h"
#include "stdlib.h"
#include "time.h"

  
int BinSearch(int * mas, int l, int r, int key);
int recBinSearch (int * mas, int l, int r, int key);
#define N (int)1e8
//const int N = 1e8;
int arr[N];

void BubleSort (int * mas, int l, int r);
void MaxSelSort (int * mas, int l, int r);
int FindMaxIndex(int * mas, int l, int r);
void InsertSort (int * mas, int l, int r);
void Swap (int * a, int * b);
void Merge (int * mas, int * buf , int left, int right);
void MergeSort(int * mas, int * buf , int left, int right);
int Partition(int * mas, int left, int right);
void QuickSort(int * mas,  int left, int right);
void DownHeap(int * mas,  int cur, int right);
void MakeHeap(int * mas,  int left, int right);
void HeapSort(int * mas,  int left, int right);
int Lchild (int i ) {return 2*i+1;}
int Rchild (int i ) {return 2*i+2;}
int Parent (int i ) {return (i-1)/2;}




int main() {
	int mas[] = {1,5,6,4,2,3};
	HeapSort(mas,0,6);
	//int k = Partition(mas,2,6);
	//printf("%d\n\n",k);
	for (int i =0; i <6; i++) printf("%d ",mas[i]);
    return 0;
}

void HeapSort(int * mas,  int left, int right) // O(n log n),    o(n) 
//[12345] -> nlogn [54321] -> nlogn [12345]
// [111111111111111111111111111111111111] -> n -> [11111111111111111111111] -> n -> [11111111111111]
{
	MakeHeap(mas,left,right); // O(n log n)  o(n)
	for (int i = 0 ; i < right - left-1; i++) // n
	{
		Swap(mas+left, mas+right-1 - i); 
		DownHeap(mas,left, right-i-1); // log n
	}
}

void MakeHeap(int * mas,  int left, int right) // O(n log n)
{
	for (int i = (left+right)/2+1; i >=left; i--) 
		DownHeap(mas,i,right);
	return;
}

void DownHeap(int * mas,  int cur, int right) // O(log n)
{

	if (cur >= right) return;
	int Lch = Lchild(cur) , Rch = Rchild(cur);
	//printf("%d %d %d %d\n",cur,right,Lch,Rch);
	if (Lch >= right) return;
	if (Rch >= right)// есть только левый сын
	{		
		if (mas[Lch] > mas[cur]) Swap(mas+Lch,mas+cur);
	}
	else // есть и левый сын и правый сын
	{
		if (mas[Lch] < mas[Rch]) 
		{
			if (mas[Rch] > mas[cur]) 
			{
				Swap(mas+Rch,mas+cur);
				DownHeap(mas,Rch,right);
			}
		}
		else
		{
			if (mas[Lch] > mas[cur]) 
			{
				Swap(mas+Lch,mas+cur);
				DownHeap(mas,Lch,right);
			}
		}
	}
}

void QuickSort(int * mas,  int left, int right)
{
	if (right - left <= 1) return;
	int edge = Partition (mas,left,right);
	QuickSort(mas,left, edge);
	QuickSort(mas, edge, right);
	return;
}// T(n) = T (n1) + T(n2) + O(n), где n1+n2 = n
// n1 = n2 = n/2 -> T(n) = 2 (T/2) + O(n) = O (n log n)
// n1 = 1 n2 = n-1 -> T(n) = ?


int Partition(int * mas, int left, int right) // возврат индекса по которому проходит граница
{
	int pivot = mas[left]; // САМОЕ ВАЖНОЕ МЕСТО
	int i = left, j = right-1;
	while (i<j)
	{
		while ((mas[i] < pivot)&&(i<j)) i++;
		while ((mas[j] > pivot)&&(i<j)) j--;// Сюда мы попадаем если mas[i] > pivot > mas[j]
		if (i<j) Swap (mas+i,mas+j);
	}
	return j+1; // Возрат правого бегунка с +1
} // Точная асс. оценка n = right - left





void MergeSort(int * mas, int * buf , int left, int right)
{
	if (right-left <= 1) return;
	int med = (left+right)/2;
	MergeSort(mas,buf,left,med);
	MergeSort(mas,buf,med,right);
	Merge(mas,buf,left,right);
	return;
}

void Merge (int * mas, int * buf , int left, int right)
{
	int med = (left+right)/2; // Правая медиана
	//Сортированны отдельно куски с left до med-1 включительно
	// и от med до right - 1 включительно
	int i1 = left , i2 = med;
	int j = left;
	while (i1< med || i2 < right)
	{
		if (i1 == med) 
		{
			for (; i2<right; i2++, j++)
				buf[j] = mas[i2];
			break;
		}
		if (i2 == right)
		{
			for (; i1<med; i1++, j++)
				buf[j] = mas[i1];				
			break;
		}
		if (mas[i1]>=mas[i2])
		{
			buf[j] = mas[i2];
			i2++;
			j++;
		}
		else
		{
			buf[j] = mas[i1];
			i1++;
			j++;
		}
	}
	for (int i = left ; i < right ; i ++) mas[i] = buf[i];
	return;
}

int FindMaxIndex(int * mas, int l, int r)
{
	int maxIndex = l;
	for (int i =l; i < r ; i++)
		if (mas[i]>mas[maxIndex])
			maxIndex = i;
	return maxIndex;
}

void MaxSelSort (int * mas, int l, int r)
{
	for (int i = l ; i < r - 1; i++)
	{
		int maxIndex = FindMaxIndex(mas, l , r - (i-l)); //thetta (r-l)
		Swap (mas+maxIndex, mas + r - (i-l) - 1);
	}
	return;
}

void BubleSort (int * mas, int l, int r)
{
	for (int i = l; i < r; i++) // Количество прогонов
	{
		int numOfSwap = 0;
		for (int j = l ; j < r-1 - (i-l); j++) // Сравнение пар
		{
			if (mas[j]> mas[j+1]) 
			{
				Swap(mas+j, mas+j+1); // Swap (&mas[j], & mas[j+1]);
				numOfSwap++;
			}
		}
		if (numOfSwap == 0) return;
	}
}

void InsertSort (int * mas, int l, int r)
{
	for (int i = l+1; i <r; i++)
	{
		int cur = -1, buf = mas[i];
		for (int j = l; j < i; j++)
		{
			if (mas[j]> mas[i]) 
			{
				cur = j;
				break;
			}
		}
		for (int j = cur; j<= i; j++) Swap(mas+j, &buf);
	}
}

void Swap (int * a, int * b)
{
	int c = *a;
	*a = *b;
	*b = c;
	return;
}

int BinSearch(int * mas, int l, int r, int key) { // [L; R)
    while (r - l > 1) {
        int med_ind = (l + r) / 2;
        int med = mas[med_ind]; // правая медиана
        if (med <= key) l = med_ind;
        else r = med_ind;
    } 

    if (mas[l] == key) return l;
    return -1;
}

int recBinSearch (int * mas, int l, int r, int key)
{
    //if (r<=l) return -1;
    if (r-l == 1)
    {
        if (mas[l] == key) return l;
        else return -1;
    }
    int med_index = (l+r)/2;
    int med = mas[med_index]; // Правая медиана
    if (med == key) return med_index;
    if (key >= med) return recBinSearch(mas, med_index,r,key);
    if (key < med) return recBinSearch(mas, l , med_index ,key);
}