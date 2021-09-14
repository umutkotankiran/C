/*
	Yapıların Esnek Dizi öğeleri.
	Flexible Array
	
	NOT !!!!!
	STRUCT IÇERISINDE BU ARRAY HEM EN SON ÖĞE OLACAK HEMDE SIZE BELIRTILMEYECEK.
	DİZİNİN BOYUTU PROGRAMIN ÇALIŞMA ZAMANINDA BELLİ OLACAK. 
	AYRICA STRUCT SIZEOF DEĞERİNE DAHİL DEĞİL.

	struct Data{
		int x;
		double dval;
		int a[];
	};

	AŞAĞISI HATA ÇÜNKÜ ARRAY SON ELEMAN DEĞİL.

	struct Data {
	int x;
	int a[];
	double dval;
};

bu uyarıda çıktı hatta 
warning C4200: nonstandard extension used: zero-sized array in struct/union

ÖR:

struct Data {
	int x,y;
	char a[];
};

#define		SIZE		100

int main()
{
	char s[SIZE];
	printf("Yazi giriniz\n");
	(void)scanf("%s", s);

	struct Data* pd = (struct Data*)malloc(sizeof(struct Data) + strlen(s) + 1);
	pd->x = 10;
	pd->y = 20;
	strcpy(pd->a, s);

	printf("%d %d %s", pd->x, pd->y, pd->a);

	free(pd);

}

DİKKAT

Bu yapı nesnesine atanan başka bir nesne olduğunu düşün
mesela
struct Data mydata;
mydata = *pd; 

free(pd);

Bundan sonra puts(mydata->a); BU TANIMSIZ DAVRANIŞ.UNDEFINED BEHAVIOR

============================================================================

VARIADIC MACRO

__VA_ARGS__ şeklinde yazılıyor.

ÖR:
#define		eprintf(...)		fprintf(stderr,__VA_ARGS__)

int main()
{
	eprintf("%s dosyasinin %d. satirinda hata\n", __FILE__, __LINE__);
}

---------------------------------------

ÖR
//#define		mprintf(format,...)		fprintf(stdout,format,__VA_ARGS__)
#define		mprintf(format,...)		fprintf(stdout,format,##__VA_ARGS__)

int main()
{
	int x = 10;
	double dval = 20.2;
	char s[] = "umut";

	mprintf("%d %f %s\n", x, dval,s);
	//mprintf("Necati"); //diye çağırırsak fprintf(stdout,"Necati",); diye çağıracak ve bu hata

	//Çözümü
	// ##token ile birleştirmek. aşağıdaki gibi
	// #define		mprintf(format,...)		fprintf(stdout,format,##__VA_ARGS__)

}

=======================================================================================================
=======================================================================================================
=======================================================================================================
=======================================================================================================
=======================================================================================================
=======================================================================================================
=======================================================================================================




C DE DİNAMİN DİZİ IMPLEMENTASYONU
BUNA VECTOR DİYECEĞİZ.ÇÜNKÜ C++ TA BUNA VECTOR DENİYOR.
VECTOR.C VE VECTOR.H TANIMLANIP KODLARI YAZILDI.
İNCELE !



=======================================================================================================
=======================================================================================================
=======================================================================================================
=======================================================================================================
=======================================================================================================
=======================================================================================================
=======================================================================================================

INVALID POINTER KULLANIMI
BANA AİT OLMAYAN BELLEK BLOĞUNA ERİŞİM.

int* ptr;
*ptr = 56;  // bu pointer dereference edilemez. UNDEFINED BEHAVIOR.

-------------

char *p;
gets(p); // UNDEFINED BEHAVIOR. Burada bir pointer var bir dizi yok.

-------------

int x;
int *ptr = &x;
int y = *ptr;	// UNDEFINED BEHAVIOR. Garbage value olan x, y ye atanmış.

-------------

Dizi taşırma hataları

int a[10];
a[10] = 23; UNDEFINED BEHAVIOR.

&a[10]  geçerli/valid bir adres ama dereference edilemez. Dizinin bittiği yerin adresi burası.

*(a - 1) buda adresinden bir öncesi burada UnDEFINED BEHAVIOR var.Bittiği yerin adresi gibi değil.


-------------

int *p;
int main()
{
	*p; // NULL Pointer Dereference. UNDEFINED BEHAVIOR.
	*p = 10; // aynı şekilde UB		
}


-------------

Vector Örneği Üzerinden gidelim

typedef struct tagVector{
	size_t msize;
	DATATYPE* mp;
}Vector;


int main()
{
	vector v;
	vector u;
	
	v.msize = 10u;
	v.mp = malloc(sizeof(*v));
	
	u = v;

	free(v.mp);  // buradan hep v hemde u etlikenir. Buna shallow copy deniyor.
	u.mp kullanmak artık UNDEFINED BEHAVIOR.
}

-------------

int *func(int x)
{
	return x;		UNDEFINED BEHAVIOR.
}

--------------

int main()
{

	int *p;

	if(1)
	{
		int x = 1;
		p = &x;
		*p = 20;
	}
	printf("%d",*p); // BURASI UNDEFINED BEHAVIOR.
}

--------------

malloc ile bir bellek bloğunu büyütme girişimi. UNDEFINED BEHAVIOR
free ile dinamik olarak elde edilmemiş bloğu geri vermek.
free edilmiş bir bloğu tekrar free etmek.
free edilmiş bir pointerı tekrar atama yapmadan kullanmak.bu pointer invaliddir.
BİRSÜRÜ VAR.


*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vector.h"

void print(HVector vec)
{
	for (size_t i = 0; i < vec->msize; ++i)
	{
		printf("%d ", vec->mp[i]);
	}
	printf("\n----------------------------------------------------\n");
}


int main()
{
	int* ptr;
	*ptr = 56;



	HVector vec = create_vector_with_capacity(20);
	printf("size = %d\n", get_size(vec));
	printf("capacity = %d\n", get_cap(vec));
	print(vec);

	int a[] = { 1,2,3,5,16,16,16,16,7,99,16,111,16 };

	vec = create_vector_with_array(a, sizeof(a) / sizeof(*a));
	printf("size = %d\n", get_size(vec));
	printf("capacity = %d\n", get_cap(vec));
	print(vec);


	set_capacity(vec,25);
	printf("size = %d\n", get_size(vec));
	printf("capacity = %d\n", get_cap(vec));
	print(vec);


	push_back(vec, 5);
	printf("size = %d\n", get_size(vec));
	printf("capacity = %d\n", get_cap(vec));
	print(vec);

	push_back(vec, 15);
	push_back(vec, 25);
	push_back(vec, 35);
	printf("size = %d\n", get_size(vec));
	printf("capacity = %d\n", get_cap(vec));
	print(vec);

	insert(vec,8, 49);
	printf("size = %d\n", get_size(vec));
	printf("capacity = %d\n", get_cap(vec));
	print(vec);


	erase(vec, 5);
	printf("size = %d\n", get_size(vec));
	printf("capacity = %d\n", get_cap(vec));
	print(vec);

	size_t val= find(vec, 5);
	if (val != NOT_FOUND)
		printf("index = %zu\n", val);
	else
		printf("Sayi bulunamadi\n");

	printf("\n--------------------------------------------------------\n");

	bool b = erase_val(vec, 111);
	if (b)
		printf("Sayi silindi\n");
	else
		printf("Sayi silinemedi\n");

	printf("\n--------------------------------------------------------\n");

	erase_all(vec, 16);
	printf("size = %d\n", get_size(vec));
	printf("capacity = %d\n", get_cap(vec));
	print(vec);



}