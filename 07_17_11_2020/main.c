#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int max(int a, int b)
{
	return a > b ? a : b;
}


int main()
{
	int x, y, z, t;
	printf("4 sayi giriniz\n");
	(void)scanf("%d%d%d%d", &x, &y, &z, &t);
	
	int ival = max(max(x, y),max(z,t));
	printf("ival = %d\n",ival);
	printf("test\n");
}
