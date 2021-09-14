#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
	ERRNO.H 
	-------
HATA İŞLEME FONKSİYONU.
STANDART OLAN VE OLMAYAN FONKSİYONLAR BELİRLİ DURUMLARDA GLOBAL BİR DEĞİŞKENİ SET EDİYORLAR.

2 FARKLI HATA İLETME BİÇİMİ VAR.
MALLOC FOPEN GİBİ FONKSİYONLAR İŞİNİ YAPAMAZSA NULL POİNTER DÖNDÜRÜYOR.
BIR DE ŞUANDA BAHSEDİLEN 2. DURUM VAR.

BU GLOBAL DEĞİŞKEN BİR MACRO. ERRNO MACROSU
MACRO TAMSAYI MACROSU VE BİR LVALUE XPR.
PROGRAM BAŞLADIĞINDA DEĞERİ 0.

printf("%d", errno);   ile yazdırılır.

-------------------------------------------------------------------

BİR HATA DURUMU OLUŞTURUP YAZDIRIRSAK

#include <errno.h>

int main()
{
	FILE *f = fopen("asd.txt", "r");
	printf("%d", errno);  // 2 YAZDIRIR.
}

İŞİNİ YAPAMADIĞI İÇİN ERRNOYU BİR TAMSAYI DEĞİŞKEN İLE SET ETTİ.
BU KONTROL EDİLEBİLİR.0 DEĞİLSE HATA DURUMU OLUŞULDUĞU ANLAŞILABİLİR.

BU 0 2 3 4 LERİN NE ANLAMA GELDİĞİNİ ERRNO.H NİN İÇİNDE GÖREBİLİRİZ.

-----------------------
-----------------------

// Error codes
#define EPERM           1
#define ENOENT          2
#define ESRCH           3
#define EINTR           4
#define EIO             5
#define ENXIO           6
#define E2BIG           7
#define ENOEXEC         8
#define EBADF           9
#define ECHILD          10
#define EAGAIN          11
#define ENOMEM          12
#define EACCES          13
#define EFAULT          14
#define EBUSY           16
#define EEXIST          17
#define EXDEV           18
#define ENODEV          19
#define ENOTDIR         20
#define EISDIR          21
#define ENFILE          23
#define EMFILE          24
#define ENOTTY          25
#define EFBIG           27
#define ENOSPC          28
#define ESPIPE          29
#define EROFS           30
#define EMLINK          31
#define EPIPE           32
#define EDOM            33
#define EDEADLK         36
#define ENAMETOOLONG    38
#define ENOLCK          39
#define ENOSYS          40
#define ENOTEMPTY       41

-------------------------------------
-------------------------------------

BU HATA KODLARINDA YOLA ÇIKARAK HATANIN NE OLDUĞU NASIL ÖĞRENİLİR.

STRİNG.H DE STRERROR VAR. HATA KODU OLAN TAMSAYININ ADRESİNİ DÖNDÜRÜYOR.
BUNUDA PRINTF VEYA PUTS İLE YAZDIRIRSAK

puts(strerror(errno));  // No such file or directory   BU HATAYI GÖSTERİR.

LİNUXTAKİ POSİX FONKSİYONLARIDA KENDİ İLAVE HATALARINI KOYMUŞ OLABİLİR.

HEPSİNİ BU ŞEKİLDE YAZDIRABİLİRİM.

int main()
{
	for (int i = 0; i < 42; ++i)
	{
		printf("Hata kodu %2d : %s\n", i, strerror(i));
	}
}


==================================================================
==================================================================

PERROR
stdio.h nin içerisinde yer alıyor.

#include <errno.h>
#include <string.h>

int main()
{
	FILE* f = fopen("asd.txt", "r");
	perror("hata olustu ");			/// hata olustu : No such file or directory
}
 
KENDISI YAZIYOR HATAYI BU SEFER
hata olustu : No such file or directory

---------------------------
NOT!!!!!
ERRNO KENDİ KENDİNE SIFIRLANMIYOR.
ERRNOYU HER FONKSİYON ÇAĞRISINDAN SONRA KULLANMAK MANTIKLI.
HANGİSİNDE HATA OLDUĞUNU BULABİLMEK İÇİN.

int main()
{
	FILE* f = fopen("asd.txt", "r");
	perror("hata olustu ");  burada yazar
	errno = 0;
	perror("hata olustu "); burada 0 olduğu için hata yok.
}

================================================================================
================================================================================

X MACROSU
---------

#define		XCOLOR		X(WHITE) X(YELLOW) X(RED) X(BROWN) X(BLUE) X(BLACK)

enum color {
#define X(a)	a,
	XCOLOR // ilk önce macroyu açar X(WHITE) X(YELLOW) X(RED) X(BROWN) X(BLUE) X(BLACK)
			// sonra x(a) olan yere a, yazar WHITE,YELLOW,RED,BROWN,BLUE,BLACK
			// bunlarda enum içerisinde olduğu için 0 dan başlayıp artırarak devam eder.
#undef X
};

int main()
{
	enum color mycolor = RED;
	// veya aşağıdaki gibi kullanabilirim.
	printf("%d %d %d", WHITE,YELLOW,RED);


}

----------------------------------------------------------

#define		XCOLOR		X(WHITE) X(YELLOW) X(RED) X(BROWN) X(BLUE) X(BLACK)

enum color {
#define X(a)	a,
	XCOLOR // ilk önce macroyu açar X(WHITE) X(YELLOW) X(RED) X(BROWN) X(BLUE) X(BLACK)
			// sonra x(a) olan yere a, yazar WHITE,YELLOW,RED,BROWN,BLUE,BLACK
			// bunlarda enum içerisinde olduğu için 0 dan başlayıp artırarak devam eder.
#undef X
};

//BUNLARDAN BİRDE ARRAY OLUŞTURACAĞIM.
#define X(a)	#a,
const char* const pcolors[] = { XCOLOR };
#undef X

int main()
{
	enum color mycolor = RED;
	// veya aşağıdaki gibi kullanabilirim.
	printf("%d %d %d\n", WHITE, YELLOW, RED);

	printf("%s\n", pcolors[YELLOW]);

	// Bir switch deyimi yazılırsa
	enum color mycolor1 = BLUE;
	switch (mycolor1)
	{
	#define		X(a)	case a: printf("%s\n",pcolors[a]);break;
		XCOLOR
	#undef X

	}

	// NE FAYDASI VAR ?
	// KODDA BİR DEĞİŞİKLİK YAPILACAĞI ZAMAN SADECE MACRO İÇERİSİNDEN BUNU DEĞİŞTİREREK
	// TÜM İŞ HALLEDİLİR.

}

====================================================================================
====================================================================================

ASSERT.H BAŞLIK DOSYASI VE ASSERT BAŞLIK DOSYASI.
COMPİLERDAN DEBUG MODA AÇILMALI.

PROGRAMIN ÇALIŞMA ZAMANINDAKİ HATALAR 2 YE AYRILABİLİR.
-------------------------------------------------------
1 YANLIŞ KOD YAZILDIĞI İÇİN OLUŞAN HATALAR VE BUNLARADA PROGRAMMING ERRORS DENİYOR.
ÖR: AÇILACAK BİR DOSYA İSMİ YANLIŞ OLUŞTURULDUĞU İÇİN DOSYA AÇILAMAMIŞ OLABİLİR.

2 PROGRAMA BAĞLI DIŞ KOMPONENTLERDEN BİR TANESİNDE SORUN VARSA HATA OLUŞABİLİR.
ÖR: DATABASE SERVER KAPANDI.PROGRAM ERİŞİP YAZAMIYOR.BURADA DA HATA VAR.

----------------------------------------------------------------------------------

ÖR:
void func(int x)
{
	int a;
	// kodlar kodlar

	if (x == 0)
	{
		fprintf(stderr, "hata");
		abort();
	}
	a /= x;
}

ÇOK ÖNEMLİ!!!!!!!!!!!!!!!!!!!!!!!!!
BURADA HATAYI YAKALAMAK IÇIN HERYERDE BUNLARI YAZMAK GEREKIYOR.
YAZMAK ZAHMETLI.KAYNAK KODU BÜYÜTÜYOR.MAALIYET UNSURU BUNLAR.
ASSERTIONDA İSE
KODDAN ÇIKARTILACAĞI ZAMAN TEK TEK SILMEK YOK. NDEGUB MACROSU DEFINE EDILECEK
BUNU YAPINCADA KAYNAK KODDAN ÇIKARILMIŞ OLACAK.
ASSERT MACROSU BURADA DEVREYE GIRIYOR.
ASSERT MACROSUNU BOL BOL KULLANABİLİRİZ.

#include <assert.h>

void func(int x)
{
	int a = 23;
	// kodlar kodlar

	assert(x != 0);
	a /= x;

}

int main()
{
	func(0); //Assertion failed: x != 0, file ... diye bir hata verdi.
}

------------------------------------------------------------------------------------

DEBUG DEĞİLDE RELEASE SÜRÜMÜNE GEÇİNCE ASSERTIONLARI DEVRE DIŞI BIRAKMAK LAZIM.
assert include etmeden önce NDEBUG define edilir.
burada conditional compiling devreye giriyor. visual studio da tanımlanan kodlara bakılacak.

#define NDEBUG
#include <assert.h>

bu durumda artık release olacağı zaman program, bu şekilde assertionları çıkarrıR koddan.


//aşağıdaki gibir bir durum var. hoca derste baktı içine.
#ifdef NDEBUG

#define assert(expr) (void)0
#else

#endif

yani NDEBUG define edildiyse artık (void)0 gibi etkisiz bir kod çalışıyor assert yerine.

assert.h de var bunun içeriği

-------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------

DYNAMIC/RUNTIME ASSERTION bu bizim yapığımız asseriton
birde STATIC ASSERTION var.buda compile time da koda bakacak sağlaması gereken koşul sağlanmazsa
sentaks hatası verecek.Bunun için değişkenin compile time da sınanması gerekiyor.

ÖR:
a[sizeof(int) == 2] mesela burası yanlış, int 4 byte ve a[0] oldu ama a[0] da sentaks hatasıdır.


C de 2011 de eklendi
_Static_assert(sizeof(int) == 2,"Yeterli değil");
NOT: static_assert olabilir C++ taki gibi.

C++ ta
static_assert(sizeof(int) == 2,"Yeterli değil");
içerisindeki ifade sabit ifadesi olmalı.

===================================================================================
===================================================================================
===================================================================================

C99 STANDARTLARIYLA GELEN YENİLİKLER
---------------------------------------

Açıklama satırı C99 da geldi
// 

-----------------------------------------------------------------------------------------

for içerisinde değişken tanımlamak C99 da geldi.
for(int i = 0 ...)  

NOT:
for(int i = 0 ...)
{
	int i = 20;
	{
		yazılan kodlar böyle bir blokta yer alıyor ve bu görünmeyen bir blok aslında.
		yani yukarıdaki tanım geçerli oluyor ve bu blok içinde gibi yorumlanıyor.
		iç bloktaki i, dışarıdaki i yi maskeliyor.
		C++ ta geçersiz.
	}
}

-----------------------------------------------------------------------------------------

Designated initializer C99 da geldi

int a[10] = {[2] = 3, [5] = 11, [8] = 43}; diğer öğelerde 0 oluyor.
dizi boyutu yazılmasıda oluyor.

Bu C++20 standartlarında dile eklendi.
C++ ta sıralama küçükten büyüğe olması gerekiyor.
C de gerek yok.

-----------------------------------------------------------------------------------------

COMPOUND LITERALS / BİRLEŞİK SABİTLER

BİR DEĞİŞKEN YARATMADAN İHTİYACIMIZ OLAN DEĞİŞKENİ KULLANMAYA DENİYOR.
BU BAYA İYİ BİR ÖZELLİK.

(Veri Tipi){Verilmek istenen değer yada değerler}

SCOPE LEAKAGE I ENGELLİYOR.

int main()
{

	printf("%d\n",(int) { 5 });
	puts((char[10]) { "Veli" });

	int* ptr = &(int) { 5 }; // bu da olur.Otomotik ömürlü bir değişken
							// oluşturuyor ve scope sonuna kadar kullanılabilir.

	int x, y, z;
	printf("3 tamsayi girin:");
	(void)scanf("%d%d%d", &x, &y, &z);
	int* p = (int[3]){ x,y,z };  // buda gayet doğal.Array decay de var.

	(int[]){[3] = 43,[8] = 44,[5] = 27}; //geçerli

}

-----------------------------------------------------------------------------------------
 
 VLA - Variable Lenght Array
 ---------------------------

 C99 da dile getirildi ama C11 de opsiyonel hale getirildi.
 Güvensiz olduğu düşünülüyor.Stackten alan harciyor.VLA initialization yok.
 Dizi boyutunu runtime da büyütebiliyor bu özellik.
 Visual Studio buna izin vermiyor.Gcc ile derlenebilir.

 Yani dizi boyutu sabit ifadesi olmak zorunda değil burada.
 int x = 10;
 int a[x]; bu VLA de mümkün.

 printf("boyut girin");
 scanf("%d",&x);
 int a[x]; burası mümkün.

 GCC ile derlenebilir.

 BAZI SALDIRILAR VAR DİZİYİ TAŞIRIP ERİŞMEMESİ GEREKEN BÖYLEYE ERİŞEBİLEN KİŞİLER OLUNCA OPSİYONEL HALE
 GELDİ. 


 ÖRNEK:

 void func(int x)
 {
	int a[x];

	for(int i = 0 ; i < x ; ++i)
	{
		a[i] = rand() % 100;
	}
 
	for(int i = 0 ; i < x ; ++i)
	{
		printf("%d ",a[i]);
	}
 
 }
 int main()
 {
	func(15);
 }


 HOCA 15-20 DK KAYDETMEYİ UNUTTU BURADA AMA VLA İLE İLGİLİ KONUŞTU YİNE.
 get_median örneği yapıldı sanırım.

 ------------------------------------------------------------------------------------


 FLEXIBLE ARRAY MEMBER 
 ---------------------
 C99 da gelen diğer araç

 struct Data{
	int x;
	int a[];
 }

 --------------------------------------------------------------

 ÖRNEK

 struct Data {
	int x, y;
	int a[]; // incomplete array type. Yapı içinde yer kaplamıyor.
};

int main()
{
	printf("%zu", sizeof(struct Data)); // 8 çıkar

	int size;
	printf("esnek dizi ogesi boyutu ");
	scanf("%d", &size);

	//artık burada dinamik ömürlü nesne yaratırken.
	struct Data* pd = (struct Data*)malloc(sizeof(struct Data) + size * sizeof(int));

	for (int i = 0; i < size; ++i)
	{
		pd->a[i] = i;
	}
}

*/

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


struct Data {
	int x, y;
	int a[]; // incomplete array type. Yapı içinde yer kaplamıyor.
};

int main()
{
	printf("%zu", sizeof(struct Data)); // 8 çıkar

	int size;
	printf("esnek dizi ogesi boyutu ");
	scanf("%d", &size);

	//artık burada dinamik ömürlü nesne yaratırken.
	struct Data* pd = (struct Data*)malloc(sizeof(struct Data) + size * sizeof(int));

	for (int i = 0; i < size; ++i)
	{
		pd->a[i] = i;
	}
}