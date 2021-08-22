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
	int is_val_prime = 1;
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

void	print_array(const int* p, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (i && i % 20 == 0)
			printf("\n");

		printf("%3d ", p[i]);
	}
	putline();
}


//-------------------------------------------------
//-------------------------------------------------

void set_random_array(int* p, int size)
{

	for (int i = 0; i < size; i++)
	{
		p[i] = rand() % 1000;
	}


}



//-------------------------------------------------
//-------------------------------------------------

void sort_array(int* p, int size)
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
//---------------------------------------------------------

void sgets(char* p)
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
		*p++ = c;

	*p = '\0';

}