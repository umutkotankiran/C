#include <stdio.h>

int sum(int x, int y)
{
	return x + y;
}

int max(int a, int b, int c)
{
	int max = a;

	if (b > a)
	{
		max = b;
	}

	if (c > max)
	{
		max = c;
	}
	
	return max;
}

int abs(int a)
{
	if (a < -1)
	{
		return -a;
	}
	
	return a;
}

int ndigit(int x)
{
	int digit_count = 0;

	if (x == 0)
		return 1;

	while (x != 0)
	{
		digit_count++;
		x /= 10;
	}

	return digit_count;

}


int main()
{
	printf("%d\n", sum(5,6));
	printf("%d\n", max(5, 6, 9));
	printf("%d\n", abs(-2));
	printf("%d\n", abs(3));
	printf("%d", ndigit(2579));
   	
}