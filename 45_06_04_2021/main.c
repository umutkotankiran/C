

/*

	YAZARKEN KULLANDIĞIMIZ TESTLER.

	Date mydate;
	set_date(&mydate, 03, 04, 1990);
	print_date(&mydate); 

	set_date_today(&mydate);
	print_date(&mydate); 

	print_date(&mydate); 
	set_date_from_str(&mydate, "12-10-2010");

	set_date_from_str(&mydate, "07-04-2021");
	printf("%d\n", get_week_day(&mydate)); // 0 pazar , 1 pazartesi, 2 Salı. 2 döndürüyor.

	Date mydate;
	randomize();

	for (;;)
	{
		set_date_random(&mydate);
		print_date(&mydate);
		(void)getchar();
	}

	*/

	/*

	İKİNCİ TEST KODU

	Date date;
	printf("dogum tarihinizi girin\n");
	scan_date(&date);
	print_date(&date);

	*/

	/*

	ÜÇÜNCU TEST KODU

	Date date;
	randomize();

	for (int i = 0; i < 10; ++i)
	{
		set_date_random(&date);
		print_date(&date);
		printf("yil : %d\n", get_year(&date));
		printf("ay : %d\n", get_month(&date));
		printf("Ay gunu : %d\n", get_month_day(&date));
		printf("hafta gunu : %d\n", get_week_day(&date));
		system("pause");
		system("cls");
	}
	*/

	/*
	
	 ÜÇÜNCÜ TEST KODU
	 
	int dcmp(const void* vp1, const void* vp2)
	{
		return cmp_date((const Date*)vp1, (const Date*)vp2);
	}

	void set_date_array(Date* pa, size_t size)
	{
		while (size--)
			set_date_random(pa++);
	}

	void print_date_array(const Date* p, size_t size)
	{
		while (size--)
			print_date(p++);
	}


	int main()
	{
		int n;

		printf("kac tarihi: ");
		(void)scanf("%d", &n);

		Date* pd = (Date*)malloc(n * sizeof(Date));
		if (!pd)
		{
			printf("Yetersiz memory\n");
			return 1;
		}

		randomize();
		set_date_array(pd, n);
	
		printf("siralama basliyor\n");
		clock_t start = clock();	
		qsort(pd, n, sizeof *pd, &dcmp);
		clock_t end = clock();	
		printf("siralama bitti\n");

		printf("islem suresi = %lf", (double)(end - start) / CLOCKS_PER_SEC);
		clear_input_buffer();
		(void)getchar(); // scanf in new line ını aldığı için durmuyor.buffer boşaltıyoruz yukarıda.
		print_date_array(pd, n);
		free(pd);	

	}
	
	*/

	/*
		
		DÖRDÜNCÜ TEST KODU

		Date today, birth_Date;

		printf("Dogum tarihinizi girin: \n");
		scan_date(&birth_Date);
		print_date(&birth_Date);

		set_date_today(&today);
		print_date(&today);
		printf("bu rezil dunyada yasadigimiz %d. gun\n",date_diff(&today,&birth_Date));


	*/

/*

	BEŞİNCİ TEST KODU

	Date today, future_date;

	set_date_today(&today);
	printf("Bugun\n");
	print_date(&today);

	for (int i = 1; i < 1'000'000'001; i *= 10)
	{
		printf("bugunden %d gun sonraki tarih : ", i);
		ndays_date(&future_date, &today, i);
		print_date(&future_date);
	}



*/


#pragma pack(1) // açıklanacak sonraki ders

typedef struct {
	int a, b;
	double d;
	char str[20];
}Member;

typedef struct {
	int x, y;
	Member m;
}Nec;

typedef struct {
	int x, y;
	Member *mp;
}Nec1;

/*
	NOTLAR
	------

	BİRLEŞİK NESNELER / COMPOSITION

	printf("sizeof(member) = %zu\n", sizeof(Member));
	printf("sizeof(Nec) = %zu\n", sizeof(Nec));
	//her nec içinde member var.

	Nec nec;
	nec.m.a = 10;
	// karşımıza a.b.c.d gibi bir eleman çıkabilir.

	Nec* np = &nec;
	++np->m.a;

	// yapının elemanı member değilde member türden pointer olsun.
	Nec1 nec1;
	//kodlar
	nec1.mp->b = 20;
	++nec1.mp->b;


	// ----------------------------------------------------------

	// birden fazla ok operatör de olabilir.
	Nec1 anec;
	Nec1* necptr = &anec;

	necptr->mp->b = 30;

	//-----------------------------------------

	// hata olan durum var

	//Yapının elemanı kendi türünden olamaz. Hem C hemde C++ ta böyle

	/*struct Nec {
		int a;
		struct Nec nec; // nec uses undefined struct nec hatası verir
	};

	//------------------------------------------------------

	//Ama pointer türden olabilir.
	// çünkü pointer size bilgisi belli.

	// bir yapının elemanı kendisinin pointerı türünden olabilir.
	// ama kendisi türünden olamaz.	

struct Nec {
	int a;
	struct Nec* pnec; // böyle yapılara self referencial structure deniyor. 
};						// veriyapılarında sıksık kullanılıyor.

//----------------------------------------------------

// bir struct elemanı struct ise bunu initialize edebiliyoruz

typedef struct {
	int a, b;
	double d;
	char str[20];
}Member;

typedef struct {
	int x, y;
	Member m;
	int z;
}Nec;

//main içinden aşağıdaki gibi devam edilir.
Nec nec = { 1,2,{1,2,3.54,"alican"},2 };

// yada designated initializer 
Nec nec1 = { .x = 2, .y = 20, .m = {1,2,3.4,"alihan"},.z = 30 };



*/

/*

	Sonraki örnek

	Employee emp;
	randomize();
	for (;;)
	{
		set_employee_random(&emp);
		print_employee(&emp);
		_getch();
	}

	*/

	/*
	
	Sonraki Örnek
	-------------

	int n;
	printf("Kac calisan\n");
	(void)scanf("%d", &n);

	Employee* pd;

	if (!(pd = (Employee*)malloc(n * sizeof(*pd)))) // *pd yerine Employee de yazılabilir.
	{
		fprintf(stderr, "Bellek yetersiz\n");
		return 1;
	}

	for (int i = 0; i < n; ++i)
	{
		set_employee_random(pd + i);
	}
	

	// qsort(pd, n, sizeof(*pd), &cmp_employee_by_no_); deniyorum o yüzden yorum yaptım
	//qsort(pd, n, sizeof(*pd), &cmp_employee_by_name_); 
	qsort(pd, n, sizeof(*pd), &cmp_employee_by_town_); // diğer kalanlarda yapılabilir.
	(void)getchar();
	for (int i = 0; i < n; ++i)
	{
		print_employee(pd + i);
	}

	free(pd);
	

	*/

/*

	SONRAKİ

	int n;

	Employee* pd;

	// burası önemli
	const CMPFUNC fa[] = { &cmp_employee_by_no_,&cmp_employee_by_name_,&cmp_employee_by_surname_,
	&cmp_employee_by_town_,&cmp_employee_by_date_ };

	printf("Kac calisan\n");
	(void)scanf("%d", &n);

	if (!(pd = (Employee*)malloc(n * sizeof(*pd)))) // *pd yerine Employee de yazılabilir.
	{
		fprintf(stderr, "Bellek yetersiz\n");
		return 1;
	}

	for (int i = 0; i < n; ++i)
	{
		set_employee_random(pd + i);
	}

	for (size_t i = 0; i < asize(fa); ++i) // tüm sıralama kriterlerine göre burada
	{										// sıralama yapıyor. ad soyad şehir...
		qsort(pd, n, sizeof(*pd), fa[i]);
		for (int k = 0; k < n; ++k)
		{
			print_employee(pd + k);
		}
		(void)_getch();
		system("cls");
	}

	(void)getchar();

	free(pd);


*/


/*
	SONRAKI GÜZEL ÖRNEK

	void print_menu(void)
{
	printf(" 1 - numaraya gore sirala\n"
		" 2 - isme gore sirala\n"
		" 3 - soyisme gore sirala\n"
		" 4 - sehire gore sirala\n"
		" 5 - dogum tarihe gore sirala\n\n");

	printf("secenegi girin :\n");
}

void  print_employee_array(const Employee* p,size_t size)
{
	while (size--)
		print_employee(p++);
}

int main()
{
	
	int n;
	Employee* pd;

	// burası önemli
	const CMPFUNC fa[] = { NULL,&cmp_employee_by_no_,&cmp_employee_by_name_,&cmp_employee_by_surname_,
	&cmp_employee_by_town_,&cmp_employee_by_date_ };

	printf("Kac calisan\n");
	(void)scanf("%d", &n);

	if (!(pd = (Employee*)malloc(n * sizeof(*pd)))) // *pd yerine Employee de yazılabilir.
	{
		fprintf(stderr, "Bellek yetersiz\n");
		return 1;
	}

	for (int i = 0; i < n; ++i)
	{
		set_employee_random(pd + i);
	}

	for (;;)
	{
		print_menu();
		int option;
		(void)scanf("%d", &option);
		qsort(pd,n,sizeof(Employee),fa[option]);	
		print_employee_array(pd, n);
		_getch();
		system("cls");
	}

	free(pd);


}

*/





#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "nutility.h"
#include "date.h"
#include <time.h>
#include "Employee.h"
//yukarıda pragma pack1 de tanımı
#include <conio.h>


/*
	burada cmp employee functionları void ile yazacağız.
	qsort türden bağımsız karşılaştırma fonksiyonları ile implemente ediliyor.
	var olanların sonuna _ koyup void ile yazacağız

*/


int cmp_employee_by_no_(const void*vp1, const void*vp2)
{
	return cmp_employee_by_no((const Employee*)vp1, (const Employee*)vp2);
}

int cmp_employee_by_name_(const void* vp1, const void* vp2)
{
	return cmp_employee_by_name((const Employee*)vp1, (const Employee*)vp2);
}

int cmp_employee_by_surname_(const void* vp1, const void* vp2)
{
	return cmp_employee_by_surname((const Employee*)vp1, (const Employee*)vp2);
}

int cmp_employee_by_town_(const void* vp1, const void* vp2)
{
	return cmp_employee_by_town((const Employee*)vp1, (const Employee*)vp2);
}

int cmp_employee_by_date_(const void* vp1, const void* vp2)
{
	return cmp_employee_by_date((const Employee*)vp1, (const Employee*)vp2);
}


typedef int (*CMPFUNC)(const void*, const void*);


// NOT: C STANDARTLARINA GÖRE FUNCTION ADRESLERİ ARASINDA TÜR DÖNÜŞÜMÜ YAPMAK
// UNDEFINED BEHAVIOR AMA DEREYİCİLER BUNA İZİN VERİYOR.DOĞRU KOD ÜRETİYOR.
// ÖZELLİKLE CONST VOİD* PARAMETRELERİ SÖZKONUSU OLDUĞUNDA.

// BU DURUMDA CMP FUNCTIONLARIN SONUNA _ KOYDUĞUMUZ VOID TÜRÜNDEN FUNCTIONLARI YAZMAYA 
// GEREK KALMIYOR ARTIK
// AŞAĞIDA ÖRNEĞİ VAR

/*

const CMPFUNC fa[] = { NULL,
				(CMPFUNC)&cmp_employee_by_no,
				(CMPFUNC)&cmp_employee_by_name,
				(CMPFUNC)&cmp_employee_by_surname,
				(CMPFUNC)&cmp_employee_by_town,
				(CMPFUNC)&cmp_employee_by_date };

//ÖNCEKİ ÖRNEKTE &cmp_employee_by_no YERİNE &cmp_employee_by_no_ İSİMLİ FONKSİYON
// YAZILMIŞTI VOID TÜRDEN PARAMETRELİ OLARAK.AMA BU CASTING SAYESİNDE YENİ FUNCTION YAZMAYA
// GEREK YOK.
// STANDARTLARA GÖRE UNDEFINED BEHAVIOR FAKAT COMPILERLAR DOĞRU KODA İZİN VERİYOR.
// BİZ WRAPPER YAZDIK. BİRÇOĞU BU ŞEKİLDE CASTİNG YAPIYOR.

*/

