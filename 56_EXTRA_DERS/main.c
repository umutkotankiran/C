/*

Variadic macro

1. Örnek
#define eprintf(...)	fprintf(stderr,__VA_ARGS__)
int main()
{
	eprintf("hata : %s dosyasi %s fonksiyonu %d. inci satir\n", __FILE__,__func__,__LINE__);
}

2. Örnek
// aşağıda ## yapılması bunun sadece virgülün gözardı edilmesini sağlıyor.
// Bu birleştirme operatörü ile alakalı değil.
//Bazı compilerlar gözardı ediyor, bazıları ise etmeyip hata verebiliyor.

#define eprintf(fmt,...)	fprintf(stderr,fmt,##__VA_ARGS__)
int main()
{
	eprintf("hata");
}

===========================================================================================================

DESIGNATED INITIALIZER
----------------------
typedef struct {
	int x, y, z;
}Point;

typedef struct {
	int x, y, z;
	int a[4];
}Data;

typedef union {
	int x;
	double d;
	char str[12];
	int a[3];
}Data2;

int main()
{

	int a[100] = { [2] = 4, [5] = 12, [7] = 24,}; // sondaki virglde trailing comma

	int b[] = { [2] = 4, [5] = 12, [7] = 24,}; // dizi boyutu 8 burada

	Point P[10] = { [0] = {4,5,6},[1] = {7,8,9},[2] = {.x = 23, .y = 44, .z = 124} }; // hem dizi hemde struct için
																					// designated init kullanıldı.
	Data ar[] = { [3] = {1,2,3,{55,66,77}},[5] = {.x= 4, .y = 5, .z = 6, .a ={234,567,876}} };

	int c[3][5] = { [0] = {1,1,1,1,1},[1] = {2,2,2,2,2} };

	Data2 d = { .str = "Ali" };

}

===========================================================================================================

COMPOUND LITERALS
-----------------

typedef struct {
	int no;
	char name[20];
	double wage;
}Person;

void func(int* p, int size);
void foo(const Person *p);

int main()
{
	int a[] = { 1,2,3,4,5 }; //
	func(a, 5); // Buradan sonrada a hayatta.Scope leakage

	Person per = { 1234,"Ali",23 };
	foo(&per); // Aynı şekilde per yine hayatta.

	//Compound Literal bir nesne oluşturup bizim istediğimiz gibi kullanmamıza olanak veriyor.

	func((int[5]) { 1, 2, 3, 4, 5 }, 5); // Undefined behavior yok.Nesne blok sonuna kadar aslında hayatta.
	func((int[10]) {1,2,3},10);
	func((int[]) {1,2,3},3);
	func((int[20]) {[5] = 1,[7] = 2,[14] = 3},3);
	func((int[]) {[5] = 1,[7] = 2,[14] = 3},3);
}

---------------------------------------

typedef struct {
	int no;
	char name[20];
	double wage;
}Person;

void func(int* p, int size);
void foo(const Person *p);

int main()
{

	(Person) {12,"veli",2 }; // Bu person türden bir nesne aslında.
	foo(&(Person) {12,"veli",2 }); // Bu person türden bir nesne aslında.

	Person pa[5];
	pa[0] = (Person){ 254,"Ahmet",45.76 };
	//ÇOK ÖNEMLİ !!!
	// Undeifned behavior yok. Compound lit ile üretilen ifade bir nesne
	// scope sonuna kadar yaşar.

	Person Per;
	Per = (Person){ 547,"MEHMET",98.23 }; // UB yok.Yukarıdaki gibi.

	//SABİT İFADESİ İLE DEĞER VERMEK ZORUNLU DEĞİL.
	int x = 2123;
	double dval = 432.23;
	Per = (Person){ x,"KUDRET",dval };
}


-----------------------------------------

int main()
{
	// 3 değişken scanf ile oku, diziye değer verir gibi 1 2 3 yerine yaz.Buda olur

	int* p = (int[3]){ 1,2,3 };
	p[1] = 22;

	//const ilede yapılabilir.
	const int* p2 = (const int[3]){ 1,2,3 };
	p2[1] = 22; // SENTAKS HATASI.
}

----------------------------------------------------

typedef struct {
	int x , y, z;
}Data;

int main()
{

	Data* p = &(Data){ 1,2,3 };
	p->y = 23; // OK
}

-----------------------------------------

typedef struct {
	int x , y, z;
}Data;

int func(void) { return 10; }

int main()
{
	localtime(&(time_t) { time(NULL) }); //GEÇERLİ.

	int* p;
	if (1)
	{
		p = &(int) { func() }; // burada blok bitene kadar compound literal ile oluşturulan nesne hayatta


	}	// P buraya kadar valid pointer

	*p; // artık burada p bir invalid/dangling pointer. gcc eklenti veriyormuş ama STANDART DEĞİL.
}	//ÇOK TEHLİKELİ BURASI.

===========================================================================================================

FLEXIBLE ARRAY MEMBER
---------------------

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
	int no;
	int dept;
	int grades[];
}Student;

int main()
{

	int n;

	printf("kac elemanli dizi\n");
	scanf("%d", &n);
	Student* pd = (Student*)malloc(sizeof(Student) + n * sizeof(int));

	if (!pd)
	{
		fprintf(stderr, "Memory cannot allocated\n");
		return 1;
	}
	pd->no = 234;
	pd->dept = 5;

	for (int i = 0; i < n; i++)
	{
		pd->grades[i] = 0;
	}
	free(pd);
}

İki	yapı nesnesi birbirine atandığında(kopyalandığında) esken dizi öğeleri birbirine kopyalanmaz.


=======================================================================================================

RECURSIVE FUNCTIONS
-------------------

Bir fonksiyon nasıl başka bir fonksiyonu çağırabiliyorsa, bir fonksiyon kendisinede çağrı yapabilir.
Doğru kullanıldığında runtime da risk içermiyor. Baya da kullanışlı.

void foo(int x)
{
	//code
	foo(x - 1);

}

Değişen bir şey yok. Tekrar kendini çağırdığında, argüman parametreye kopyalanacak, otomatik ömürlü
yerel deişkenler varsa onların bir kopyası daha çıkarılacak,static ömrülü varsa 1 tane olacak zaten.
Burada func kendini çağırır, kendini çağıran diğerini çağırır ....
Bu durdurulmalı, yoksa runtime hatasına dönüşür.(Stack Overflow). Her yeni çağrı stackte daha fazla
alan kullanımına yol açar, öyle bir noktaya gelirki stackte yer kalmaz.Buna stack taşması deniyor yani
Stack Overflow.

Neden Bir Fonksiyon Kendisini çağırsın?
Bazı algoritmalar bu şekilde implemente edilebiliyor hemde kendisini çağırmayan biçimdede implemente edilebiliyor.
Döngü ile olabiliyor.Döngü ile olanlara iterative implementasyon. kendisini çağıranlara ise recursive implementasyon deniyor.

Recursive çözüm iterative göre avantaj sağlamıyorsa her zaman iterative tercih edilmeli.
Çünkü testi, debugı kolay ve hata yapma ihtimali daha düşük

Recursive ne  zaman tercihedilir?
İterative çözümü yoksa
Recursive kodlaması daha kolay ise
Maliyeti daha küçükse,  recursive tercih edilir


Hoca bu recursive kodların iterative halini de yazdı ama ben yazmıyorum.

EN KLASİK MÜLAKAT SORUSU
------------------------

Recursive yazmak daha malliyetli.Ama tercih aşağıda.

FACTORIAL FUNCTION

#include <stdio.h>

int factorial(int x)
{
	if (x < 2)
		return 1;

	return x * factorial(x - 1);
	// factorial(5);
	// 5 * factorial(4);
	// 5 * 4 * factorial(3);
	// 5 * 4 * 3 * factorial(2);
	// 5 * 4 * 3 * 2 * factorial(1);

	//Burada dikkat edilmesi gereken. factorial(1) çağrıldı 2 den küçük olduğu için 1 return etti Artık factorial(1) yerine 1 yazacak compiler.
}

int main()
{
	printf("%d",factorial(5));
}

DAHA ŞIK HALİ

int factorial(int x)
{
	return x < 2 ? 1 : x * factorial(x - 1);
}

NOT : 13! 4 BYTELIK İNT SINIRINI TAŞIRIYOR. 21! DE 8 BYTLIK TAMSAYIYI TAŞIRIYOR.


HANGİSİ DAHA MANTIKLI ?????????????  CEVAP: HİÇBİRİ
LOOKUP TABLE KULLAN

const static long long fact[] = {1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 
			  479001600, 6227020800, 87178291200, 1307674368000, 20922789888000, 
			  355687428096000, 6402373705728000, 121645100408832000, 2432902008176640000,};


#include <stdio.h>

long long factorial(int x)
{
	const static long long fact[] = { 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800,
			  479001600, 6227020800, 87178291200, 1307674368000, 20922789888000,
			  355687428096000, 6402373705728000, 121645100408832000, 2432902008176640000, };

	return fact[x - 1];
}

int main()
{
		printf("%lld\n", factorial(5));
}

-----------------------

ÖR:
FİBONACCİ SERİSİNDE RECURSİVE ÇÖZÜM TAM BİR FELAKET.
İTERATİF ÇÖZÜM TERCİH EDİMELİ.
LOOKUP TABLE TABİKİ EN İYİ ÇÖZÜM YİNE.


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int fibo(int n)
{
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;

	return fibo(n - 1) + fibo(n - 2);

}


int main()
{
	int n;
	printf("Kacinci terim\n");
	scanf("%d", &n);
	printf("serinin %d. terimi %d\n",n,fibo(n));
}

-----------------------------------------------------------

ÖR:
Adresi gönderilen yazıyı tersten yazdırmak.







*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int fibo(int n)
{
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;

	return fibo(n - 1) + fibo(n - 2);

}


int main()
{
	int n;
	printf("Kacinci terim\n");
	scanf("%d", &n);
	printf("serinin %d. terimi %d\n",n,fibo(n));
}