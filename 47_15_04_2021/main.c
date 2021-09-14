#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>
#include "nutility.h"
#include <string.h>
#include <stdint.h>
#include "date.h"
#include <stdlib.h>
#include <conio.h>


/*


PADDİNG BYTELAR DİKKATE ALINMALI.ELEMANA ERİŞECEĞİM DERKEN UB DURUMLARINA DÜŞEBİLİRİZ.

OFFSETOFF MACROSU İLE DE ELDE EDİLEBİLİYOR STRUCT İÇİNDEKİ NESNENİN YERİ.

typedef struct {
	char cx;
	int ival;
	char cy;
}Data;


int main()
{
	printf("%zu\n", offsetof(Data, ival));
}

------------------------------------------------

typedef struct {
	char cx;
	int ival;
	char cy;
}Data;


int main()
{
	Data dx = {12,7587,54};
	Data dy = {12,7587,54};

	//NOT : YAPI OPERATÖRLERİ KARŞILAŞTIRMA OPERATÖRLERİNİN OPERANDI OLAMAZLAR.
	// dx.x == dy.x && dx.ival && dy.ival && .... diye gidiyor. böyle olabilir. ama okumak ve yazmak baya zahmetli.

	// bu durumda memcmp türden bağımsız karşılaştırma yapıyor.

	if (!memcmp(&dx, &dy, sizeof(Data)))
		printf("Esit\n");
	else
		printf("Esit degil\n");

	//eşit çıkmayabilir.(release modda edit değil çıkıyor.debugda eşit çıktı)
	// padding bytelar var burada. bu bytelar garbage / indetermined value durumunda.
	// eşit olmayabilir bu padding bytelar. o yüzden eşit çıkmayabilir.
}

-----------------------------------------

typedef struct {
	char cx;
	int ival;
	char cy;
}Data;


int main()
{

	// eğer illaha memcmp kullanılacaksa
	Data dx;
	Data dy;

	// Data dx,dy; den sonra
	memset(&dx,0,sizeof(dx));
	memset(&dy,0,sizeof(dy)); //yapılır ki padding bytelar 0 olsun.

	dx.cx = 10;
	dy.cx = 10;


	dx.cy = 15;
	dy.cy = 15;

	dx.ival = 1234;
	dy.ival = 1234;


	if (!memcmp(&dx, &dy, sizeof(Data)))
		printf("Esit\n");
	else
		printf("Esit degil\n");

}

------------------------------------------------------------------------


#define		clear_struct(x)				memset(&x,0,sizeof(x)) // macro yapılabilir.

typedef struct {
	char cx;
	int ival;
	char cy;
}Data;


int main()
{

	// eğer illaha memcmp kullanılacaksa
	Data dx;
	Data dy;

	// Data dx,dy; den sonra
	memset(&dx,0,sizeof(dx));
	memset(&dy,0,sizeof(dy)); //yapılır ki padding bytelar 0 olsun.

	dx.cx = 10;
	dy.cx = 10;


	dx.cy = 15;
	dy.cy = 15;

	dx.ival = 1234;
	dy.ival = 1234;


	if (!memcmp(&dx, &dy, sizeof(Data)))
		printf("Esit\n");
	else
		printf("Esit degil\n");

}


=========================================================================================
=========================================================================================
=========================================================================================
=========================================================================================
=========================================================================================

UNIONS
------

Tüm sentaks kuralları yapılarla aynı.
Farklı olan noktalara değinilecek burada, birliklerin varlık nedenleride bu farklılıklar zaten.


union data {
	int a, b;
	char c;
};

typedef union {
	int a, b;
	char c;
}Data2;

int main()
{
	// tüm sentaks  structlar ile aynı.
	union data mydata;
	Data2 my;
	Data2* box;
	box->a;

}

----------------------------------

NOT!!!!!!!!!!!!!!
FARKI

union içindeki sizeof değeri en yüksek olan eleman, union un size ını belirler.

union data {
	int a, b;
	double dval;
	double dx;
	char str[16];
};

union data nın sizeof değeri 16 byte tır. Çünkü en büyük olan char str[16] nın sizeof değeridir.

SONUC:
Birliklerin elemanları aynı bellek alanını paylaşıyor.Yani memory den tasarruf var burada.

İçerideki elemanları nasıl anlamlandırdığımız ile alakalı bir durum bu.


------------------------------------------------------------------------------------

typedef union {
	int a, b;
	double dval;
	char str[16];
}UData;


int main()
{
	// tüm sentaks  structlar ile aynı.
	UData mydata;

	//elemanların adreslerinin hepsinin aynı olduğu görülüyor.
	// bunun böyle olması garanti.Güvenerek kod yazılabilir.
	//birlikler böyle çalışıyor.

	printf("mydata.a = %p\n", &mydata.a); // hepsinin adresi aynıdır.
	printf("mydata.b = %p\n", &mydata.b);
	printf("mydata.dval = %p\n", &mydata.dval);
	printf("mydata.str = %p\n", mydata.str);

}

------------------------------------------------------------------------------------


typedef union {
	int a, b;
	double dval;
	char str[16];
}UData;


int main()
{
	//unionda her elemana ilk değer vermek sentaks hatası.Sadece 1 tanesine verilebilir.
	//UData mydata = { 1,2,3.4,"ali" }; burası hata

	// burada birliğin a elemanı 345 oldu.
	UData mydata = { 345 };

	//yada designated initializer ile istediğimize bir değer verebiliriz.
	UData mydata2 = { .dval = 54.23 };
}

NOT: SADECE 1 INITIALIZER KULLANILABILIR.
NOT: unionda her elemana ilk değer vermek sentaks hatası.Sadece 1 tanesine verilebilir.


------------------------------------------------------------------------------------------

typedef struct {
	uint16_t min;
	uint16_t sec;
}Duration;

//
typedef union {
	uint32_t uval; // 4 byte unsigned int
	Duration duration;
}UDur;

int main()
{
	printf("sizeof(Duration) %zu\n", sizeof(Duration)); // hepsi 4 çıkar.
	printf("sizeof(uint32_t) %zu\n", sizeof(uint32_t));
	printf("sizeof(UDur) %zu\n", sizeof(UDur));

	// union türlerde en max olanın size bilgisi union size bilgisidir.
	// burada uint32_t 4 byte. union size bilgisi de 5 byttır.

}


--------------------------------------------------------------------------------


typedef struct {
	uint16_t min;
	uint16_t sec;
}Duration;

//
typedef union {
	uint32_t uval; // 4 byte unsigned int
	Duration duration;
}UDur;

int main()
{
	UDur x = { .duration = {234,5873} }; // {234} yazarakta deneyebilirim.
	printf("x.uval = %u\n", x.uval);  // burada birbirleriyle aynı alanda olduklarını gösteriyor.

}


--------------------------------------------------------------------------------



typedef union {
	uint32_t uval;
	struct {
		uint16_t min;
		uint16_t sec;
	};
}UDur;

int main()
{
	UDur mydur = { 98798798 };
	printf("%u\n", mydur.min); // taştı veriler ama sorun değil.Amaç erişilebildiğini göstermek.
	printf("%u\n", mydur.sec);
}


--------------------------------------------------------------------------------


UNION lar bitsel işlemlerde çok kullanılıyor.

----------------------------------------------------------
----------------------------------------------------------


// öyle durumlar var ki yapının iki elemanı aynı ayda kullanılmayacak.
// ya birinci ya diğerleri kullanılacak. burada bunları birliğin elemanı olarak tanıtmak mantıklı oluyor.
//


typedef struct {
	int status;
	char place[20];
	int id;
}Mildata; // askerlik bilgisi

typedef struct {
	char name[24];
	int no;
	double wage;
	Mildata mdata; // burada askerlik bilgisi var
	char maiden_name[24]; // burada da kızlık soyadı
	// senaryoya göre asker ise kızlık soyada olamaz çünkü bu birey erkek
	// kadın ise, kızlık soyadı olur, bu durumda da erkek olamaz.
	// ikisinden biri olmayacak.yani aynı bellek alanını paylaşacaklar.
	// union olacak burası
}Person;



//En son hali aşağıdaki gibi.

typedef struct {
	char name[24];
	int no;
	double wage;
	union {
		char maiden_name[24]; // kadınlar için
		struct { // erkekler için
			int status;
			char place[20];
			int id;
		};
	};
}Person;


int main()
{
	printf("sizeof(person) = %zu\n", sizeof(Person));
}

--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------


ETİKETLENMİŞ BİRLİK / TAGGED UNION
----------------------------------

Hazır araç yok kendimiz yazacağız.

nec = 4;
nec = 3.4;
nec = mydate;  bunların hepsini tutacak şekilde bir nesne tanımlayacağız.
				biraz farklı bir tema.


dümdüz şekilde bir union ve içerisine bunları yaz şeklinde olmayacak
türü belirten bir şey daha olmalı.


----------------------------------------

ÖR:


typedef union {
	Date date;
	double dval;
	int ival;
	char c;
}Data;




int main()
{
	Data mydata;
	mydata.ival = 2523;
	mydata.dval = 234.231;
	//burada eksik olan hangi elemanını set ettiğimizin bilgisi yok.
}

YUKARISI EKSİK.

------------------------------------------------------------------
------------------------------------------------------------------
------------------------------------------------------------------

Doğru hali burada
-----------------

#define		DATE	0
#define		DOUBLE	1
#define		INT		2
#define		CHAR	3



typedef struct {
	union {
		Date date;
		double dval;
		int ival;
		char c;
	};
	int type;	// burası hangi elemanıın kullandığını gösteriyor.Bunun içinde yukarıdan macro yazdık.
}Data;


void set_random_data(Data* p)
{
	p->type = rand() % 4;
	switch (p->type){
	case DATE: set_date_random(&p->date); break;
	case DOUBLE: p->dval = (double)rand() / RAND_MAX; break;
	case INT: p->ival = rand() / RAND_MAX; break;
	case CHAR: p->c = rand() / 26 + 'A'; break;

	}
}

void print_data(const Data* p)
{
	switch (p->type) {
	case DATE: print_date(&p->date);  break;
	case DOUBLE: printf("%lf\n", p->dval); break;
	case INT: printf("%d\n", p->ival); break;
	case CHAR: printf("%c\n", p->c); break;

	}
}

int main()
{
	// Aşağıdaki gibi yapılabilir. bu şekilde tür bilgiside belirtiliyor.
	// Data mydata = { .type = INT, .ival = 234};
	Data mydata;
	randomize();

	for (;;)
	{
		set_random_data(&mydata);
		print_data(&mydata);
		(void)_getch();
	}
}

===========================================================================================
===========================================================================================
===========================================================================================
===========================================================================================
===========================================================================================
===========================================================================================



ENUMERATIONS
------------

structures
unions
enumerations

içindeki verilerin tamsayı karşılıklarını tutuyor.
Her dil için verilen destek bu konuda farklı.

C de bu destek az.

Bune alternatif olarak macrolarda kullnılabilir.tabi farkları üstünlükleri var.

----------------------------------------------------------------------

enum Day{
	Sunday, Monday, Tuesday, Wednesday, Friday, Saturday
};

// Sunday burada bir sabit.Constant. bir değer verilmezse ilk eleman 0 dan başlar ve +1 diye devam eder.
// NOT: VERİ TİPİ BELİRTMİYORUM.


int main()
{
	Sunday; // 0 olduğu görülür. Bir switch in case i olarak kullanılma şekli çok yaygın.

	// sabit olduğundan hata yok
	int a[Friday] = { 0 };

	// türün ismi burada enum Day, Yapılar ve birliklerle aynı.
	// typedef edilebilir.

	enum Day weekday;

	// #define friday   5 de denebilirdi.
	// bu durumda friday macrosunu kullanınca derleyici bir isim görmüyor.
	// ör:
	// bunu bir function scope ta yazabiliriz.sadece o func kullanır. Globalde herkes kullanır.
	//

	weekday = Tuesday; //denebilir.


	---------------------------------------------------------------------------------------



typedef enum {
	White = 120,
	Yellow = 543,
	Purple,		 // Numara vermezsek eğer bir öncekinin 1 fazlasıdır
	Green = -40,
	Blue
}Color;

// enumda c ve c++ arasında çok farklılık var

int main()
{
	printf("while = %d\n", White);
	printf("Yellow = %d\n", Yellow);
	printf("Purple = %d\n", Purple);
	printf("Green = %d\n", Green);
	printf("Blue = %d\n", Blue);

	// NOT : C de enumeration içerisindeki isimleri kullandığımız yerde kullandığı tür İŞARETLİ İNT tir.

	// sizeof(color)  ile sizeof(int)   eşit olmak zorunda. C++ ta böyle değil.


	Color mycolor = Blue;
	printf("mycolor = %d", mycolor);

	// NOT: enum türü sistemdeki int türünün store ihtiyacı kadardır.
	// içindekiler constant çünkü, yapı elemanı gibi değil.ELEMAN DEĞİL CONSTANT.

}

--------------------------------------------------------------------------------------


//card.h nin içi
#define POKER

#ifdef POKER
	typedef enum {Club,Diamond,Spade,Heart}Suit;
#else
	typedef enum {Club,Diamond,Heart,Spade}Suit;
#endif


--------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------

typedef enum {Club,Diamond,Spade,Heart}Suit;
//aşağıdaki gibide olabilir.Kart dağıtmada falan kullanılabilir.
typedef enum { two = 2,three = 3,four = 4,five = 5,six = 6,seven = 7,
			   eight = 8,nine = 9,ten = 10,jack = 10,queen = 10,king = 10,ace = 11};



int main()
{
	const char* const asuits[] = {
		[Club] = "Sinek",   // Club bir constant. enumdan 0 değeri ile gelir ve dizinin 0. indisine
		[Diamond] = "Karo", // designated initilaze ile değerler atanır.
		[Heart] = "Kupa",
		[Spade] = "Maca",
	};
}

----------------------------------------------------------------------
----------------------------------------------------------------------

C DE EKSIK OLARAK GÖRÜLEN ÖZELLIKLER

1.Sorun
typedef enum { Club, Diamond, Spade, Heart }Suit;

int main()
{

	Suit s;
	s = 23; // yanlış ama geçerli. C++ ta sentaks hatası
	s = 2; // yanlış, geçerli ve kötü.
	s = Club; // burada herşey ok. yani numaralandırma türüne int muamelesi yapıyor

}

-----------------

2.Sorun
int türü 2 byte olsun.

enum color {whike = 56576}; 56576 2 bytelık bir int türe sığmıyor.

-----------------

3. sorun

#include "screen.h"
typedef enum {										screen.h den gelen bildirim
white, gray, blue, magenta, brown, red, black
}ScreenColor;										

#include "traffic.h"
typedef enum {										traffic.h den gelen bildirim
yellow,green,red
}TrafficLight; 


BURADA İKİ ADET RED VAR.ENUM İÇİN AYRI BİR SCOPE/KAPSAM YOK.
ENUM KAPSAMI NEYSE ENUMERATORLERDE/ENUM CONSTANT BU KAPSAMDA BİLİNİYOR.
red BURADA İKİ YERDE DE ENUMERATOR/ENUM CONSTANT OLARAK KULLANILMIŞ
AYNI SCOPE TA AYNI İSİMİ BİRDEN FAZLA VARLIĞA VEREMEYİZ.
BURASI SENTAKS HATASI.

BURADA GENELDE YAPILAN ŞEY ENUM ADINI DEĞİŞKEN ADININ BAŞINA EKLİYORLAR
AŞAĞIDAKİ GİBİ.

#include "screen.h"
typedef enum {						
ScreenColorwhite, ScreenColorgray, ScreenColorblue, ScreenColormagenta, ScreenColorbrown, ScreenColorred, ScreenColorblack
}ScreenColor;

#include "traffic.h"
typedef enum {									
TrafficLightyellow,TrafficLightgreen,TrafficLightred
}TrafficLight;



NOT!!!!!!!!!!!!!!!!!!!!!!!!!!

BİR USER DEFİNED OBJE LOCAL SCOPE TA DA BİLDİRİLEBİLİR.
STRUCT ENUM VEYA UNİON OLABİLİR BU.
AMA LOCAL SCOPE TA KULLANILMIŞ OLUR.
BÖYLE OLURSA HERYERDE KULLANILAMAZ SADECE KENDI SCOPE UNDA KULLANILIR


===================================================================================
===================================================================================
===================================================================================

İDİYOMLAR
---------

1. BUNU GÖRDÜK DAHA ÖNCE

typedef enum {Club,Diamond,Spade,Heart}Suit;

int main()
{
	const char* const asuits[] = {
		[Club] = "Sinek",   // Club bir constant. enumdan 0 değeri ile gelir ve dizinin 0. indisine
		[Diamond] = "Karo", // designated initilaze ile değerler atanır.
		[Spade] = "Kupa",
		[Spade] = "Maca",
	};
}


----------------------------------------

2.

void func(void)
{
	enum {SIZE = 500};
}

hata yok.
	a - user defined type local scope ta olabilir.
	b - etiket ismi olması zorunlu değil.
	c - numaralandırma sabiti sayısı 1 adet olabilir.

----------------------------------------

3.
typedef enum { white, gray, blue, magenta, brown, red, black,NoOfColors }Color;

int main()
{
	for (Color c = white; c < NoOfColors; ++c)
		printf("%d", c);
}

----------------------------------------

4.

typedef enum { Club, Diamond, Spade, Heart }Suit;
typedef enum {
	two = 2, three = 3, four = 4, five = 5, six = 6, seven = 7,
	eight = 8, nine = 9, ten = 10, jack = 10, queen = 10, king = 10, ace = 11
}Face;

typedef struct {
	Suit s;
	Face f;
}Card;

int main()
{
	Card mycard = { .s = Spade,.f = nine };
}

=============================================================================
=============================================================================
=============================================================================
=============================================================================
=============================================================================
=============================================================================
=============================================================================

BUNDAN SONRA BITWISE OPERATIONS VAR


*/

typedef enum { Club, Diamond, Spade, Heart }Suit;
typedef enum {
	two = 2, three = 3, four = 4, five = 5, six = 6, seven = 7,
	eight = 8, nine = 9, ten = 10, jack = 10, queen = 10, king = 10, ace = 11
}Face;

typedef struct {
	Suit s;
	Face f;
}Card;

int main()
{
	Card mycard = { .s = Spade,.f = nine };
}