#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "nutility.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "mylib.h"

/*
FONKSİYON GÖSTERİCİLERİ

C dilinde adresler iki ayrı kategoriye ayrılır:
Nesne adresleri (Object pointers)
Fonksiyon adresleri (function pointers)
Bir fonksiyonun adresi o fonksiyonun makine kodlarının yerleştiği 
bellek bloğunun adresi olarak görülebilir. C dilinde bir fonksiyonun adresi, 
fonksiyon göstericisi (function pointer) denen özel bir gösterici değişkende saklanabilir.
Bir fonksiyon adresi başka bir fonksiyona argüman olarak gönderilebilir. 
Bir fonksiyonun geri dönüş değeri bir fonksiyon adresi olabilir. 
Elemanları fonksiyon adresleri olan diziler oluşturulabilir. 
Fonksiyon adresleri C ve C++ dillerinde en sık kullanılan araçlar arasındadır.


C / C++ ta fonksiyonların adresi kullanılabilir.
bu adresleri değişkenlerde tutulabilir, argüman olarak gönderilebilir ve
geri dönüş değeri olabilir.

bir fonksiyon adresini
&func veya func diye yazabiliriz.

func -> function to pointer conversion yaparak implicit olarak fonksiyon adresine dönüştürür.

Bütün fonksiyon adresleri aynı değil.
türü paramtetrik yapısı ... herşey önemli.

mesela aşağıdaki fonksiyonun adres türü
int foo(int,int); ---------->  int (*)(int, int) olarak belirtilir.

ve burada bir değişken tanımlarsak  int (*fp)(int, int) = &func;  diyebiliriz.
burada fp geldi. ismi fp olan func pointer değişkeni.

fp = func; denebilir artık



FONKSİYON ÇAĞRISI

func()
veya
(&func)() -> öncelikten ötürü paranteze alındı

void (*fp)(void) = func;

fp(); bu da aynı fonksiyonu çağırır.

Özet
func()
(&func)()
fp()
hepsi ok çalışır.

void fp1(void)
{
	printf("func1 cagrildi")
}
void fp2(void)
{
	printf("func2 cagrildi")
}
void fp3(void)
{
	printf("func3 cagrildi")
}

int main()
{
	void (*fp)(void); // f1 de denebilir. ben & kullanıyorum.
	fp = &f1; 
	fp(); // f1 i çağırır.
	fp = &f2;
	fp(); // f2 yi çağırır
	fp = &f3;
	fp(); // f3 ü çağırır

}

fonksiyon pointer değişkenleri memory de aynı miktarda yer kaplar.

void (*fp)(void) = f1;
*fp demeke fp nin gösterdiği fonksiyon demektir bu. diğer pointer işlemleri gibi
(*fp)() fonksiyon bu şekilde de çağrılır.fonksiyon pointerı olduğu vurgusu için bu şekilde yapılabilir.
fp() bu şekilde de çağrılır.

neden yanlış aşağısı. Fonksiyon pointer olduğu için yanlış.
Mesela 2. sıradaki doğru 
(&fp)() == (*fp)() == fp()  yanlış.
(&func)() == (*func)() == func()  Doğru.çünkü burası ptr değil, function.

func. ptr söz konusu olunca.
fp() ile (*fp)() aynı şey olarak görülebilir ama (&fp)() değil.
pointerlarda olduğu gibi.
mesela 

&fp nin türü nedir?
void (**)(void) 

void (*fptr)(void) = f1;
void (**fp)(void) = &f1; -> pointer to function pointer

burada
(*fptr)() ile yine f1 çağrılır.

Pointerlar sözkonusu olunca hepsi birbirine eşit olmuyor bunu ispatladık.

----------------------------------------------------------------------------
----------------------------------------------------------------------------
----------------------------------------------------------------------------


FONKSİYON GÖSTERİCİLERİ VE TYPEDEF BİLDİRİMLERİ

function ptr türleri karmaşık
strcmp nin adres türü

int (*)(const char *, const char *)

int (*fptr)(const char *, const char *) = &strstr;
int (**fpp)(const char *, const char *) = &fptr;

Elemanları fptr olan bir dizi

char *f1(const char *, const char *)
char *f2(const char *, const char *)
char *f3(const char *, const char *)

Elemanları fptr gibi pointer olan bir dizi tanımı.

int (*fa[3])(const char *, const char *) = {&f1,&f2,&f3};

-----------------------------------------
-----------------------------------------

öyle bir fonksiyon olsun ki parametresi fptr gibi değişken olsun.Çok uzun

char* (*foo(char* (*fp1)(const char*, const char*), char* (*fp2)(const char*, const char*)))(const char*, const char*);
Bu normal insan işi değilmiş. :D



typedef ile daha kısa hale gelecek.

char * (*fp)(const char *,const char * ); 
typedef char * (*FPTR)(const char *, const char *); yapılacak

strstr gibi	fonksiyonların adresi olan türe FPTR eş ismini veriyoruz.

typedef char * (*FPTR)(const char *, const char *);


	FPTR fpx = f1;
	FPTR fpa, fpb, fpc;

	//------------------------------------------------
	FPTR f = &strstr; // karşılığı char* (*fptr)(const char*, const char*) = &strstr;
	//f nin adresini tutan değişken

	char* (**fpp)(const char*, const char*) = &f; //bunuda aşağıdaki gibi yazabiliriz.
	FPTR* fp = &f; // yukarıda ** var.adres türü FPTR olan bir pointer bu.

	//--------------------------------------------------

	int (*fa[3])(const char*, const char*) = { &f1,&f2,&f3 };
	//aşağıdaki gibi tanımlanır
	FPTR fa[3] = { &f1,&f2,&f3 };

	//Çok uzun fonksiyonu tanımlayalım.
	char* (*foo(char* (*fp1)(const char*, const char*), char* (*fp2)(const char*, const char*))((const char*, const char*));

	FPTR foo(FPTR, FPTR); // türünde tanımlanabilir.

	// ----------------------------------------------------

	=====================================================
	=====================================================
	=====================================================

	FONKSİYON POİNTERLARI NE İŞE YARAYACAK

	Callback, bir fonksiyona bir fonksiyonu argüman olarak olarak gönderiyoruz, çağırdığım 
	fonksiyonun benim gönderdiğim fonksiyonu çağırmasını isteyeceğiz.

	yani fonksiyonu başka bir fonksiyona çağırtacağız.

	bir fonksiyona argüman olarak fonksiyon göndererek yapıyor bu işi.
	Çağırdığım fonksiyon benim gönderdiğimi çağırıyor.



	void f1(void)
	{
		printf("func1 cagrildi\n");
	}

	void f2(void)
	{
		printf("func2 cagrildi\n");
	}
	void f3(void)
	{
		printf("func3 cagrildi\n");
	}


	void foo(void (*fptr)(void))
	{
		printf("Foo cagrildi\n");
		fptr(); // (*fptr)() şeklindede çağrılabilirdi.
	}

	int main()
	{

		foo(&f1); // hepsi geçerli.
		foo(f2);
		foo(&f3);

	}

	-----------------------------------------------------------
	-----------------------------------------------------------

	ÖR:

	void print_test(const char* fname, int (*fp)(int))
	{
		printf("%s testinden gecenler\n", fname);
		for (size_t i = 0; i < 128; i++)
		{
			if (fp(i))
				putchar(i);
		}
		putchar('\n');
	}

	int main()
	{
		print_test("islower", &islower); // islower da yazılabilirdi.adres gönderdiğim belli
											// olsun diye &islower gönderdim.

		print_test("isupper", &isupper);
		print_test("ispunct", &ispunct);
	}

	------------------------------------------------------------
	------------------------------------------------------------
	------------------------------------------------------------

	qsort fonksiyonu

	Çok önemli kesin bilmek gerekiyor.

	void qsort(void *vpa,size_t size, size_t sz, int (*fp)(const void *, const void *));

	vpa -> sıralanacak bellek bloğu/dizi adresi.türden bağımsız
	size -> sıralanacak dizinin/alanın boyutu.
	sz -> bir elemanın ne kadar yer kapladığı.
	int (*fp)(int) -> 2 eleman karşılaştırılacağı zaman bu fonksiyona çağrı yapıp 
	karşılaştırma yapılacak.Bu arada bu bir fonksiyon adresi.
	burası strcmp gibi çalışıyor.birinci büyükse pozitif ikinci büyükse negatif, eşitse 0.
	


	#define		SIZE	100

//4. parametre
	int mycmp(const void * vp1, const void *vp2)
	{
		const int* p1 = (const int*)vp1; // gelen data int bu sebeple int e cast edildi.
		const int* p2 = (const int*)vp2;// memcpy, memseti memmove .. gibi functionlarda char * a cast etmiştik.

		if (*p1 > *p2) // büyükten küçüğe istenseydi bu yöndeğiştirirdi.
			return 1;
		else if (*p1 < *p2)
			return -1;
		else
			return 0;

	}

	int main()
	{
		int a[SIZE];
		randomize();
		set_random_array(a, SIZE);
		print_array(a, SIZE);

		//stdlib include edilmeli.
		printf("Siralama bitti\n");
		qsort(a, SIZE, sizeof *a, &mycmp);
		print_array(a, SIZE);

		//qsort nlogn karmaşıklığında
	}


------------------------------------------------------------------
------------------------------------------------------------------
------------------------------------------------------------------



#define		SIZE	100

int dcmp(const void* vp1, const void* vp2)
{
	
	//const double* p1 = (const double*)vp1;
	//const double* p2 = (const double*)vp2;

	//if (*p1 > *p2)
		//return 1;
	//else if (*p1 < *p2)
		//return -1;
	//else
		//return 0;

	//Aşağısı daha güzel yazılmış

	if (*(const double*)vp1 > *(const double*)vp2)
	return 1;
	else if (*(const double*)vp1 < *(const double*)vp2)
		return -1;

	return 0;
	}


	int main()
	{
		double a[] = { 4.5,25.55,32.68,6.7,8.9,8.1,25,50,34.87,12.21 };
		qsort(a, asize(a), sizeof(double), &dcmp);
		for (size_t i = 0; i < asize(a); i++)
		{
			printf("%lf\n", a[i]);
		}
	}
		

	-------------------------------------------------------------------
	-------------------------------------------------------------------
	-------------------------------------------------------------------

	Print array türden bağımsız hale nasıl gelir?

	
	#define		SIZE		100

	void print_array1(const void* vpa, size_t size,size_t sz, void (*fp)(const void* vp))
	{
		const char* p = (const char*)vpa;
		for (size_t i = 0; i < size; i++)
		{
			fp(p);
			p += sz;
		}
	}

	void iprint(const void* vp)
	{
		printf("%d ", *(const int*)vp);
	}

	int main()
	{
		randomize();
		int a[SIZE];
		set_random_array(a, SIZE);
		sort_array(a, SIZE);

		print_array1(a, SIZE, sizeof(*a), &iprint);
	}

	--------------------------------------------------
	--------------------------------------------------
	--------------------------------------------------

	QSORT yazacağız ama qsort algoritması ile değil, bubblesort ile yazacağız.

	#define		SIZE		100

	//gsort fonksiyonu türden bağımsız olarak bir diziyi bubble sort algoritması ile sıralar.
	void gsort(void* vpa, size_t size, size_t sz, int (*fp)(const void*, const void*)) // 100 tane eleman var her biri sizeof(int) kadar.
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


	int main()
	{
		randomize();
		int a[SIZE];
		set_random_array(a, SIZE);
		print_array(a, SIZE);
		gsort(a, SIZE, sizeof * a, &icmp);
		print_array(a, SIZE);

	}


	--------------------------------------------------
	--------------------------------------------------
	--------------------------------------------------
	
	bsearch  yani binary search. Standart kütüphanenin fonksiyonu.Sıralı dizide arama yapıyor.Kodunu yazmıştık.
	void *(const void *pkey,const void vpa,size_t size,size_t sz, int(*fp)(const void *, const void *));
	

	int main()
	{
		int a[SIZE];
		int ival;
		int* ptr;

		randomize();
		set_random_array(a, SIZE);
		qsort(a, SIZE, sizeof(*a), &icmp);
		print_array(a, SIZE);
		printf("aranacak degeri girin\n");
		(void)scanf("%d", &ival);

		ptr = (int*)bsearch(&ival, a, SIZE, sizeof(int), &icmp);

		if (ptr)
			printf("Bulundu. Dizinin %d indisli elemani\n", ptr - a);
		else
			printf("Bulunamadi\n");

	}

	---------------------------------------------------------------------
	---------------------------------------------------------------------
	---------------------------------------------------------------------
	
	int (*fp)(int) == NULL;
	fonksiyon pointerlarına NULL pointer atanabilir.



	=====================================================================
	=====================================================================
	=====================================================================
	=====================================================================


	FUNCTION POINTER ARRAYS
	-----------------------

	int *p[10] demek int *ptr den 10 tane var demek.

	Bunu uyarlarsak

	int (*fptr[10])(int);  typedef ile de tanımlanabilir bu daha kısa olur hatta.

	#define		SIZE		100


	int f1(int x)
	{
		printf("f1 cagrildi x = %d\n", x);
		return x * x;
	}

	int f2(int x)
	{
		printf("f1 cagrildi x = %d\n", x);
		return x * x;
	}

	int f3(int x)
	{
		printf("f1 cagrildi x = %d\n", x);
		return x * x;
	}


	int main()
	{

		int (*fpa[3])(int) = { &f1,&f2,&f3 }; // {f1,f2,f3}; şeklinde de yazılabilir.
	
		for (int i = 0; i < 3; i++)
		{
			int val = fpa[i](i);
			printf("val = %d\n",val);
		}

	}

	---------------------------------------------------
	---------------------------------------------------
	---------------------------------------------------

	Typedef ile yaparsak proddan örnek verirsek

	typedef int (*FPTEST)(int);

	int main()
	{
		FPTEST fa[] = { &isupper,&islower,&isalpha,&isalnum,&isdigit,&isxdigit,&ispunct,&isspace,&isblank,&isprint,
		&isgraph,&iscntrl };

		const char *p[] = { "isupper","islower","isalpha","isalnum","isdigit","isxdigit","ispunct",
			"isspace","isblank","isprint","isgraph","iscntrl" };

		int ch;
		printf("bir karakter girin :");
		ch = getchar();

		for (size_t i = 0; i < asize(fa); i++)
		{
			if (fa[i](ch))
				printf("%s	OK\n",p[i]);
			else
				printf("%s  Not Ok\n",p[i]);
		}


	}

	------------------------------------------------------------
	------------------------------------------------------------
	------------------------------------------------------------

	Bir örnek daha yapıyor. hangi fonksiyon çağrılsın
	isalnum bunun *p[] den indexini bulup  fa[] dan indexi verip çağırıyor.


	FPTEST fa[] = { &isupper,&islower,&isalpha,&isalnum,&isdigit,&isxdigit,&ispunct,&isspace,&isblank,&isprint,
		&isgraph,&iscntrl };

	const char* p[] = { "isupper","islower","isalpha","isalnum","isdigit","isxdigit","ispunct",
		"isspace","isblank","isprint","isgraph","iscntrl" };

	int ch;
	char fname[40] = {0};
	printf("bir karakter girin :");
	ch = getchar();

	printf("hangi test fonksiyonu cagrilsin\n");
	(void)scanf("%s",fname);

	size_t i;
	for (i = 0; i < asize(fa); i++)
	{
		if (!strcmp(fname, p[i]))
			break;
	}

	if (i == asize(fa))
		printf("function gecersiz\n");
	else if (fa[i](ch))
		printf("%c karakteri icin %s testi sonucu OK \n",ch,fname);
	else
		printf("%c karakteri icin %s testi sonucu Not OK \n",ch,fname);


	sonrasında daha basit örnekler yapıyor.Bunları yazmadım.
	2.03 ten sonrasına bakılabilir

	-----------------------------------------------------------------
	-----------------------------------------------------------------
	-----------------------------------------------------------------


	ÇOK GÜZEL ÖRNEK

	void g(void)
	{
		printf("g cagrildi\n");
	}

	int main()
	{
		// bu örnekte mylib .h ve .c yi create etti.
		func();//default davranışı foo fonksiyonunu çağırmak

		FPTR f = setfunc(g); // setfunc a hangi fonksiyonun adresini geçersek func artık o fonkisyonu çağıracak.
		// geri dönüş değeri ilk fonksiyonun adresi yani g nin adresi.

		func(); // artık g yi çağıracak.

		setfunc(f);// artık func eski davranışına geri döndü.

		func(); // tekrar f yi çağıracak
	}


*/

#define		SIZE		100

void g(void)
{
	printf("g cagrildi\n");
}

int main()
{
	// bu örnekte mylib .h ve .c yi create etti.
	func();//default davranışı foo fonksiyonunu çağırmak

	FPTR f = setfunc(g); // setfunc a hangi fonksiyonun adresini geçersek func artık o fonkisyonu çağıracak.
	// geri dönüş değeri ilk fonksiyonun adresi yani g nin adresi.

	func(); // artık g yi çağıracak.

	setfunc(f);// artık func eski davranışına geri döndü.

	func(); // tekrar f yi çağıracak
	
}