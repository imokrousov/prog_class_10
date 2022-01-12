#include <iostream>
#include <cmath>

using namespace std;

int sum (int l, int r, int * mas, int n, int *b, int m,int size);

int main ()
{
	int n;
	cin>>n;
	int mas[n];
	for (int i = 0; i < n; i ++) cin >> mas[i]; 
	int m = sqrt (n)+1;
	int r = (n+m-1)/(m);
	int b [m]; // Это работает на неточных квадратах
	for (int i =0; i < m ; i ++) b[i] =0; 	
	int k = 0;
	for (int i =0 ; i < n; i++)
	{
		b[i/r] += mas[i]; 
	}
	for (int i = 0; i < n; i ++) cout<< mas[i] << ' '; 
	cout<<endl;
	for (int i = 0; i < m; i ++) cout<< b[i] << ' '; 
	cout<<endl<<endl;
	cout<< sum(0,n/2,mas,n,b,m,r)<<endl;
	cout<< sum(1,2,mas,n,b,m,r)<<endl;
	cout<< sum(1,7,mas,n,b,m,r)<<endl;
}


int sum (int l, int r, int * mas, int n, int * b, int m, int size)
{
	int ans = 0;
	for (int i = l; i < r; )
	{
		if (i%size == 0 && r - i >=size ) 
		{
			ans += b[i/size];
			i+=size;
			continue;
		}
		ans += mas[i];
		i++;
	}
	return ans;
}













