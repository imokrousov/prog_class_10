#include "stdio.h"

int linSearch (int * mas, int l, int r, int key);
// В mas находит ключ key начиная с позиции l до позиции r не включительно
// Если ключа нет то функция возращает -1
int recBinSearch (int * mas, int l, int r, int key);


int main()
{
	int a[] = {1,2,2,4};
	printf("%d\n",linSearch (a,0,3,2));
	printf("%d\n",linSearch (a,0,3,4));
	printf("%d\n",recBinSearch (a,0,4,1));
	printf("%d\n",recBinSearch (a,0,4,2));
	printf("%d\n",recBinSearch (a,0,4,3));
	printf("%d\n",recBinSearch (a,0,4,4));
	printf("%d\n",recBinSearch (a,0,4,5));
	return 0;
}

int linSearch (int * mas, int l, int r, int key)
{
	for (; l<r; l++)
		if (mas[l]== key) 
			return l;
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



















