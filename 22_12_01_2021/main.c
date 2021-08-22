/*dizinin boyutunu belirten ifade sabit olmalı
değişkene bağlı bir ifade olamaz.

dizi boyutunu verirken 
sabit ifadesi olmalı
0 dan büyük olacak
0 da olmayacak

symbolic constants macro kullanılabiliyor dizi boyutu verirken.

int a[100]; -> "a, 100 elemantlı int türden bir dizi " şeklinde okunur

bir fonksiyonun parametre değişkeni dizi olamaz. pointer olur
bir fonksiyonun geri dönüş değeri bir array türü olamaz. pointer olur.


n adımlı bir dizi varsa O(n) algoritma karmaşıklığındadır.

for
	for     ise O(n2) dir karmaşıklığı.

Bubble sort -> O(n2) dir.

reverse için -> öğe sayısının yarısı kadar dönen döngü. baştan birinci sondan birinci, ikinciye ikinci, üçüncüye üçüncü...

algoritma karışıklığında
worst case
best case
average senaryolar var. aksi söylenmedikçe varsayılan average senaryo.

time complexity - space complexity
space : algoritmayı çalıştırmak için ne kadar alana ihtiyaç var.bezen yer sıkıntısı da olabiliyor.

dizi tanımında
int x  = 10
int dizi[x] -> olamaz
int dizi[10 * 5 - 3] -> olur.
int dizi[0] veya dizi[-1] olamaz

macro tanıma girebilir
#define SIZE 23

int dizi[SIZE] -> geçerli.

otomotik ömürlü int x[4]; bunu çöp değerler ile kullanmak hata.UB.
statik ömürlü olsaydı 0 ile başlardı.
static int x[4];  o ile başlar.

ÖNEMLİ

bir fonksiyonun parametre değişkeni dizi olamaz.Pointer olur.
bir fonksiyonun geri dönüş değeri türü değişkeni dizi olamaz.Pointer olur.İleride görülecek detaylı.
statik ömürlü yerel değişkenler neden kullanılır. ? ileride görülecek kullanım temaları var.
dizinin elemanları memory de ard arda bulunur.

array elemanlarına erişmek için index yada subscript operatörü kullanılır.
Hem dizinin adresi olur hemde dizinin elemanlarının adresi var.dizi adresi dizinin ilk elemanınn adresi demektir.

dizinin bir indisli elemanı demekle dizinin birinci elemanı farklı anlamdadır.

dizi[1] -> dizinin bir indisli elemanı
dizi[0] -> dizinin birinci elemanı.

ÖNEMLİ

int a[10];
a[15] = 30; -> bu sentaks hatası değil.compile time hatası değil runtime hatası ve tanımsız davranış.

dizinin elemanlarına değer girmek

for(int i = 0 ; i<10;i++)
{
	a[i] = i;
}


ve erişmek

for(int i = 0 ; i<10;i++)
{
	printf("a[%d] = %d\n",i,a[i]);
}

diziyi dolaşmaya traverse deniyor.array traversal.

=========================================================
=========================================================

ARRAY INITIALIZATION

int a[10] =  {3, 7, 9, 2,2, 5, 6, 7, 8, 2} 10 elemanlı diziye 11 tane vermek istesem sentaks hatası.
daha az verilebilir.

int a[10] =  {3, 7, 9, 2};  burada diğer elemanlarını 0 ile başlatır.4 initializator var.6 tanesi 0 olacak.

int a[10] = {0} bu ise ilk değere 0 diğerlerini de zaten 0 yapacak.Hepsi 0 olur.

int a[1] = {}; sentaks hatası C ve C++ arasında arraylerde ciddi farklılıklar var.


int a[4] =  {3, 7, 9, 2,}; bu şekilde sonda virgül olabilir.semantik olarak hiçbir fark yok. 
buna trailing comma deniyor.

int a[]; geçersiz
int a[] = {1,3,5,6}; -> geçerli  runtime da dizinin boyutu 5 ten 6 ya çıkamaz.
bunu dymamic memory management aracı yapıyor.malloc calloc realloc.


//Designated initializator.

int a[25] = {[5] = 17, [13] = 25};
int a[25] = {[13] = 25},[5] = 17};   bu da olur 
int a[25] = {[13] = 25},[5] = 17, 60, 70}   bu da olur.çok kullanılmıyor. 6 ve 7 indisli elemanı 60 ve 70 olur.
int a[] = {[13] = 25,[5] = 17, 60, 70} bu da geçerli.

x =10, y = 5,z = 26;
int a[] = {x,y,z , x+y}; -> standart C de yok ama extension ile mümkün oluyor.

-------------------------------------------------------

int a[5] = {1,3,5,7,9};
int b[5];

b = a ; sentaks hatası.

diziler atama operatörünün sol operandı olamaz.Lvalue expression olamazlar.

int x = 10;
&x =   // adres operatörü ile olutşrulan ifade c de sağ taraf değeridir.sol taraf değeri değildir.

Array Decay
Array to pointer conversion

kodda a yazılırsa aslında derleyici tarafından bir ifade içinde kullanıldığında &a[0] ifadesine dönüştürür.buna array decay veya
array to pointer conversion denir.

mesela

scanf("%d",a); -> demek  scanf("%d",&a[0]) aynıdır.

bir diziyi diğerine kopyalamak için memcpy veya for döngüsü kullanılır

for(int i = 0; i<5;i++)
{
	b[i] = a[i] ;
}




*/

// aşağıdakiler yoksa eğer nutility.c ye eklenecek.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>



void randomize(void)
{
	srand((unsigned)time(0));
}

void print_array(const int* p, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (i && i % 20 == 0)
			printf("\n");
		printf("%3d ", p[i]);
	}
	//putchar koy
	printf("\n---------------------------------------------------------------------------------------------\n");
}

void	set_random_array(int* p, int size)
{
	for (int i = 0; i < size; i++)
	{
		p[i] = rand() % 1000;
	}
}



#define		SIZE	100






int main()
{
	int a[SIZE];

	randomize();

	set_random_array(a, SIZE);
	print_array(a, SIZE);

	//ortalaması
	int sum = 0;
	for (int i = 0; i < SIZE; i++)
	{
		sum += a[i];
	}
	printf("average : %f\n", (double)sum / SIZE);

	// tek yani odd olanlarının aritmetik ortalaması 
	int odd_sum = 0;
	int odd_count = 0;
	for (int i = 0; i < SIZE; i++)
	{
		if(a[i] % 2)
		{
			odd_sum += a[i];
			odd_count++;
		}
		
	}
	
	if (odd_count)
	{
		printf("odds average : %f\n", (double)odd_sum / odd_count);  //burada hiç tek olmazsa 0 a bölmeden dolayı UB oluşur.bu sebepte if ile
																	// kontrol ediliyor
	}																// halen tanımsız davranış olabilir.sum toplamı 2.147 milyarı geçebilir.
	else															// 4 milyar olabilir. işaretli türlerde taşma tanımsız davranıştır.
		printf("dizide hiç tek sayı yok.\n");						// bunuda kontrol etmek gerekir ama yapmadık bunu.
	

	//aynı şekilde çiftlerin de toplamı bulunabilir.O(n) karmaşıklığında bu kod.



	//----------------------------------------------------------------------------
	
	//MAX ELEMENT ALGORITMASI
	// ilk eleman max yapılır ya da min yapılır.
	int max = a[0];
	for (int i = 1; i < SIZE; i++)	//O(n) karmaşıklığında
		if (a[i] > max)
			max = a[i];

	printf("max : %d\n", max);
	
	
	// indisi ile birlikte bulmak için

	max = a[0];
	int max_id = 0;
	for (int i = 1; i < SIZE; i++)	//O(n) karmaşıklığında
		if (a[i] > max)
		{
			max = a[i];
			max_id = i;
		}
			

	printf("max value : %d   max index : %d\n", max,max_id);

	//------------------------------------------------------------------------------

	//hem max hemde min bulunacak

	max = a[0];
	int min = a[0];

	for (int i = 0; i < SIZE; i++)
	{
		if (a[i] > max)
			max = a[i];
		else if (a[i] < min)
			min = a[i];
	}

	printf("max = %d     min = %d\n", max, min);

	//------------------------------------------------------------------------------

	//runner-up yani en büyük ikinci değeri bulmak

	max = a[0];
	int runner_up = a[1];

	if (a[1] > a[0])
	{
		max = a[1];
		runner_up = a[0];
	}

	for (int i = 2; i < SIZE; i++)
	{
		if (a[i] > max)
		{
			runner_up = max;
			max = a[i];
		}
		else if (a[i] != max && a[i] > runner_up)
			runner_up = a[i];
	}

	printf("runner up = %d      max = %d", runner_up, max);

	//-----------------------------------------------------------------------------

	// ÖDEV
	// dizideki unique değerleri ekrana yazıran kod.
	// yazılan algoritmanın karmaşıklığını yaz.
	// unique olanları sırasız yazma olanağı olsa karmaşıklık azalır mıydı ?

	// -----------------------------------------------------------------------------

	// Reverse algoritması.

	int temp;
	for (int i = 0; i < SIZE / 2; i++)
	{
		temp = a[i];				// 100 elemanlı bir dizi.[0-99]
		a[i] = a[SIZE - 1 - i];		// a[0] için a[100 -1 -0]  // a[1] için a[100 -1 -1]  
		a[SIZE - 1 - i] = temp;		//					99						98
	}
	printf("\n");
	print_array(a, SIZE);

	// Reverse copy ise ödev
	// tersini başka bir diziye kopyalama ödevi.

	// ------------------------------------------------------------------

	//Linear search 

	int sval;
	int i;
	int flag = 0;
	printf("aranan degeri giriniz\n");

	(void)scanf("%d", &sval);

	for (i = 0; i < SIZE; i++)
	{
		if (a[i] == sval)
		{
			flag = 1;
			break;
		}
	}

	if (flag)
		printf("aranan deger dizinin %d indisli elemani\n", i);
	else
		printf("%d bulunamadi\n", sval);

	// yada döngüdeki flag kaldırılır aşağıdaki if e i < SIZE yazılır.Sonuçta bulunduysa break ile çıkılır ve i < SIZE sağlanır.
	// if içinden de i < SIZE koşulu sağlanırsa bulundu demektir.

	// profesyonel seviyuede daha farklı yazılıyor.

	for (i = 0; i < SIZE && a[i] != sval; i++)
		;

	if (i < SIZE)
		printf("aranan deger dizinin %d indisli elemani\n", i);
	else
		printf("%d bulunamadi\n", sval);

	//video 2:20 lerde bir soru var. Donald Knut sorusu. Ödev.

	//----------------------------------------------------------------------
	//----------------------------------------------------------------------

	// SIRALAMA ALGORİTMASI.

	// sıralama algoritması işin nasıl yapılacağını tarif ediyor.
	// sıralama kriteri hangi koşullar altında yapacağını söylüyor.

	// bazı algoritmaları ezbere bilmek mantıklı.
		
	// bubble sort,quick sort, insertion sort, selection sort, merge sort, shell sort...
	//quick sort çok kullanılıyor.
	//radix sort, index sort... çok var.

	// bizi ilgilendirenler
	// time complexity
	// space coplexity

	// sıralama algoritmaları stable yada unstable olabilir.

	
	/*
		aşağıdaki elemanları sıralarsak
		ahmet	12
		hasan	24	
		mehmet	55
		naci	47	
		huseyin	34
		mehmet	30
		mehmet	21

		eğer aşağıdaki gibi izafi olarak mehmetlerin sıralaması değişirse bu unstable algo. olur
		ahmet	12
		hasan	24
		huseyin	34
		mehmet	21
		mehmet	30
		mehmet	55
		naci	47
		
		eğer aşağıdaki gibi olursa stable algoritma olur. mehmetlerin kendi içindeki sıralaması aynen kaldığı için.
		ahmet	12
		hasan	24
		huseyin	34
		mehmet	55
		mehmet	30
		mehmet	21
		naci	47

	*/

	

	return 0;
}