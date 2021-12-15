#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"

 
int * FindAllSubstr (const char * str, const char * substr);
int *  prefix_function (const char * s);
int  KMP (const char * str, const char * substr);


int main() {
//	int * a = FindAllSubstr("abccabc", "abc");
//	for (int i =0 ;i< 7; i++) printf("%d",a[i]);
	printf("%d", KMP("abqcabc", "abc"));
    return 0;
}

int  KMP (const char * str, const char * substr)
{
	int l1 = strlen(str), l2 = strlen(substr);
	char * cur_str = (char *) calloc (l1+l2+2,1);
	strcat(cur_str,substr);
	strcat(cur_str,"#");
	strcat(cur_str,str);
	int l3 = strlen(cur_str); 
	int * pi = prefix_function(cur_str);
	for (int i = l2+1; i < l3; i++)
	{
		if (pi[i] == l2) return i - l2 - l2 ;
	}
	return -1;
}

int *  prefix_function (const char * s) {
	int n = strlen(s);
	int * pi = (int *)calloc(n, sizeof(int));
	for (int i=1; i<n; ++i) {
		int j = pi[i-1];
		while (j > 0 && s[i] != s[j])
			j = pi[j-1];
		if (s[i] == s[j])  ++j;
		pi[i] = j;
	}
	return pi;
}

int * FindAllSubstr (const char * str, const char * substr)
{
	int l1 = strlen(str);
	int l2 = strlen(substr);
	int * answer = (int * ) calloc (l1 , sizeof(int));
	for (int i =0; i<= l1 - l2; i++ )
	{
		int flag = 1;
		for (int j = 0 ; j < l2; j++)
		{
			if (str[i+j] != substr[j])
			{
				flag = 0;
				break;
			}
		}
		answer [i] = flag;
	}
	return answer;
}

