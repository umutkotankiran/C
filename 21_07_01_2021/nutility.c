// code file / implementation file
#include "nutility.h"
#include <Windows.h>
#include <stdio.h>



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
	printf("\n-----------------------------------------\n");
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


