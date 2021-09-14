// code file / implementation file
#define _CRT_SECURE_NO_WARNINGS
#include "nutility.h"
#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


const int primes[] = { 0,2,3,5,7,11 };

static int icmp(const void* vp1, const void* vp2);

const int sbc_[] = { // mesela 0 ın 0 tane 1 i var. 15 in 4 tane biri var demek bu dizi
0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
};




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

//gsort fonksiyonu türden bağımsız olarak bir diziyi bubble sort algoritması ile sıralar.
void gbsort(void* vpa, size_t size, size_t sz, int (*fp)(const void*, const void*)) // 100 tane eleman var her biri sizeof(int) kadar.
{
	char* pa = (char*)vpa;
	for (size_t i = 0; i < size - 1; i++)
	{
		for (size_t j = 0; j < size - 1 - i; j++)
		{
			if (fp(pa + j * sz, pa + (j + 1) * sz) > 0)
			{
				gswap(pa + j * sz, pa + (j + 1) * sz, sz);
			}
		}
	}
}

//---------------------------------------------------------
//---------------------------------------------------------


void bitprint(int val)
{
	static char buffer[200];

	_itoa(val, buffer, 2);

	printf("%032s\n", buffer);
	// NOT : %032s varsa değeri yaz yoksa 0 koy demekti.
}

//---------------------------------------------------------
//---------------------------------------------------------

char* get_log_file_name(void)
{
	static char buf[100];
	time_t timer;
	time(&timer);

	struct tm* p = localtime(&timer); // ayrıştırılmış zaman bilgsi
	sprintf(buf, "%d_%02d_%02d_%02d_%02d_%02d.log",
		p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);

	return buf;
}


const char* rname(void)
{
	const char* const pnames[] = {
		"yilmaz","ali","veli","deli","delmez","coskun","uckun","meric",
		"gelmez","begenmez"
	};

	return pnames[rand() % asize(pnames)];
}



const char* rsurname(void)
{
	const char* const pfnames[] = {
		"at","kalk","mat","ran","man","aslan","tektas","cifttas","coktas","bestas"
	};
	return pfnames[rand() % asize(pfnames)];
}


const char* rtown(void)
{
	const char* const ptowns[] = {
		"Istanbul","Ankara","Izmir","Antalya","Mugla","Aydin","Denizli","Canakkale","Kars",
		"Ardahan"
	};
	return ptowns[rand() % asize(ptowns)];
}