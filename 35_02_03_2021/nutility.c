// code file / implementation file
#include "nutility.h"
#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int ndigit(int val)
{
	int digit_count = 0;
	if (val == 0)
	{
		return 1;
	}

	while (val)
	{
		++digit_count;
		val /= 10;
	}

	return digit_count;
}

//-------------------------------------------------
//-------------------------------------------------

int isprime(int val)
{
	if (val == 0 || val == 1)
		return 0;

	if (val % 2 == 0)
		return val == 2;

	if (val % 3 == 0)
		return val == 3;

	if (val % 5 == 0)
		return val == 5;

	else
		for (int i = 7; i * i <= val; i += 2)
			if (val % i == 0)
				return 0;

	return 1;
}

//-------------------------------------------------
//-------------------------------------------------

void sleep(int millisecond)
{
	Sleep(millisecond);
}

//-------------------------------------------------
//-------------------------------------------------

void putline(void)
{
	printf("\n-------------------------------------------------------------------------------\n");
}

//-------------------------------------------------
//-------------------------------------------------

void clear_input_buffer(void)
{
	int c;
	while ((c = getchar()) != '\n' && c != 'EOF')
		;

}

//-------------------------------------------------
//-------------------------------------------------


void randomize()
{
	srand((unsigned)time(0));
}

//-------------------------------------------------
//-------------------------------------------------

void	print_array(const int* p, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		if (i && i % 20 == 0)
			printf("\n");

		printf("%3d ", p[i]);
	}
	putline();
}


//-------------------------------------------------
//-------------------------------------------------

void set_random_array(int* p, size_t size)
{

	for (size_t i = 0; i < size; i++)
	{
		p[i] = rand() % 1000;
	}


}



//-------------------------------------------------
//-------------------------------------------------

void sort_array(int* p, size_t size)
{
	qsort(p, size, sizeof(*p), icmp);
}


//-------------------------------------------------
//-------------------------------------------------

static int icmp(const void* vp1, const void* vp2)
{
	return *(const int*)vp1 - *(const int*)vp2;
}


//---------------------------------------------------------

void sgets(char* p)
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
		*p++ = (char)c;

	*p = '\0';

}

//---------------------------------------------------------
//---------------------------------------------------------

void swap(int* p1, int* p2)
{
	int temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}


//---------------------------------------------------------
//---------------------------------------------------------

void reverse_array(int* p, size_t size)
{
	for (size_t i = 0; i < size / 2; i++)
	{
		swap(p + i, p + size - 1 - i);
	}
}

//---------------------------------------------------------
//---------------------------------------------------------

int get_max(const int* p, size_t size)
{
	int max = *p;
	for (size_t i = 1; i < size; i++)
	{
		if (max < *(p + i))
			max = *(p + i);
	}

	return max;
}

//---------------------------------------------------------
//---------------------------------------------------------

int get_min(const int* p, size_t size)
{
	int min = *p; 
	for (size_t i = 1; i < size; i++)
	{
		if (min > *(p + i))
			min = *(p + i);
	}

	return min;
}

//---------------------------------------------------------
//---------------------------------------------------------

void get_min_max(const int* p, size_t size, int* pmax, int* pmin)
{
	*pmax = *pmin = *p;
	for (size_t i = 1; i < size; i++)
	{
		if (*pmin > *(p + i))
			*pmin = *(p + i);
		if (*pmax < *(p + i))
			*pmax = *(p + i);
	}
}

//---------------------------------------------------------
//---------------------------------------------------------

void bsort(int* p, size_t size)
{
	for (size_t i = 0; i < size - 1; i++)
		for(size_t j = 0; j < size - 1 - i; j++)
			if (p[j] > p[j + 1])
			{
				//swap(&p[j],&p[j+1]); buda çalışır fakat alttakini tercih ettik
				swap(p + j , p + j + 1);
			}
}

//---------------------------------------------------------
//---------------------------------------------------------

void copy_array(int* pdest, const int* psource, int n)
{
	while (n--)
		*pdest++ = *psource++;
}

//---------------------------------------------------------
//---------------------------------------------------------

void gswap(void* vp1, void* vp2, size_t size)
{
	char* p1 = (char*)vp1;
	char* p2 = (char*)vp2;

	while (size--)
	{
		char ptemp = *p1;
		*p1++ = *p2;
		*p2++ = ptemp;
	}
}

//---------------------------------------------------------
//---------------------------------------------------------

