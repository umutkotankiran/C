#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "nutility.h"

/*

	TEKRAR EDELİM

	Storage Class Specifiers
	------------------------
	auto
	register
	static
	extern


	Type Modifiers
	--------------
	const
	volatile
	restrict
	
	--------------------------------------------
	--------------------------------------------
	--------------------------------------------


	void func(void)
	{
		static int x = 10;
	}
	
	staticte nasıl tanımlandıysa ve değer en son fonksiyondan çıkarken değeri ne ise o şekilde memory de kalır.

	Burada urand örneği vardı 100 defa dönen 101 de ise -1 return eden bir kod vardı.
	onun üzerinden static i açıklıyor.

	Ben bu sefer yazmayacağım.

	--------------------------------------------------
	--------------------------------------------------

	bazı fonksiyonlar ilk kez çağrıldığını nasıl anlar.

	#include <stdbool.h>

	void func(void)
	{
		static bool first_call_flag = true; // memory de kalır ve aşağıda false a girince artık false yani ilk kez çağrılmamış demektir.
		if (first_call_flag)				// bir sonraki çağırmada girmez if e.ilk kez de çağrılmadığını anlar.
		{
			printf("ilk kez cagrildi\n");
			first_call_flag = false;
		}

		printf("Diger islemler\n");
	}

	int main()
	{
		for (int i = 0; i < 10; i++)
			func();
	}


	---------------------------------------------------------------------------------
	---------------------------------------------------------------------------------
	---------------------------------------------------------------------------------


#define		BUFFER_SIZE			100
#define		MAX_LEN			12
#define		MIN_LEN			8
#include <ctype.h>
#include <stdlib.h>

int get_random_char(void)
{
	int c;
	while (!isalnum(c = rand() % 128))
		;
	return c;
}


char* create_password(void)
{
	static char buf[BUFFER_SIZE];	// memory de kalıyor çünkü static ömürlü. bu dökümantasyonda belirtilmeli.
									// dinamik ömürlü bir dizi sanıp free ederse UB olur.
									// yada farklı ptr değişkenlerde saklarsa daha önce gördük, hepsi son değerin adresini tutar.
									// bu da hep aynı yazıyı yazdırır.
	int len = rand() % (MAX_LEN - MIN_LEN + 1) + MIN_LEN;

	for (int i = 0; i < len; i++)
	{
		buf[i] = (char)get_random_char();
	}

	buf[len] = '\0';
	return buf;
	}

	int main()
	{
	for (int i = 0; i < 10; i++)
		printf("%s\n", create_password());

	

	//BURASI YUKARIDA BAHSEDİLEN SÜREKLİ AYNI ADRESİ DİZİYE YAZDIRDIĞINI GÖSTEREN KOD
	char* pa[10];
	for (int i = 0; i < 10; i++)
		pa[i] = create_password(); // dizi static olarak tanımlanmış. adresi hep aynı. en son hangi yazı tutuluyorsa hepsine
									// o yazı girilir.
	for (int i = 0; i < 10; i++)
		printf("%s\n", pa[i]);

	
}

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------



Dökümantasyon okumak önemli.
fonksiyon static mi dinamikmi geri dönüş değerine sahip yada
başarısızlık durumunda null ptr mı döndürüyor.

Eğer fonksiyon içerisinde otomotik ömürlü değişkenler varsa bunların her seferinde ilk değer ile hayata getirme maliyeti var.

void func(void)
{
	int primes[] = {2,3 ................} ;
	
}

function her çağrıldığında dizi yeniden hayata gelecek. yani stackte ki alana bunların yazılması gerekiyor.
bu maliyetten kaçmak için static ile nitelenebilir.


void func(void)
{
	static int primes[] = {2,3 ................} ;

}

NOT:
function içerisindeki lookup table olarak kullanılan dziler static ömürlü olursa maliyet kısılır.
automatic ömürlü olursa her function call da ilk değer verme maliyeti oluşur.

----------------------------------------------------------------------
----------------------------------------------------------------------
----------------------------------------------------------------------

Ödev olarak strtok yapılacak

char *strtok(char *p,const char *psep);
bir yazıyı belirli kurallara uyan substringlere bölüyor.
split function gibi.

char str[100];
	printf("bir yazi girin: ");
	sgets(str);

	char *p = strtok(str, ".,!?;:");  // eğer return değeri NULL ptr değilse ilk yazının adresini verecek.
	if (p)
		printf("%s", p);


//BURADAN SONRASI TUHAF.
//İlk çağrıda dizinin adresi girilir.Daha sonrasında ise birinci parametreye NULL PTR GÖNDERİLİYOR.

-----------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------

int main()
{
	char str[100];
	printf("bir yazi girin: ");
	sgets(str);


	//İlk çağrıda dizinin adresi girilir.Daha sonrasında ise birinci parametreye NULL PTR GÖNDERİLİYOR.

	char* p = strtok(str, " .,!?;:");  // eğer return değeri NULL ptr değilse ilk yazının adresini verecek.
										// burada adres olarak str verildi.ikinci parametrede boşlukta var.DİKKAT!!!
	while (p)
	{
		puts(p);	// Dİkkat! ilk sefer yazıldı
		p = strtok(NULL, " .,!?;:"); // burada ise artık NULL ptr yazıldı ve döngünün her turunda NULL ptr mi diye kontrol etti.
	}

	// bir yazi girin: ali, hasan.huseyin?veli geldi mi?
		//ali
		//hasan
		//huseyin
		//veli
		//geldi
		//mi

}

bu işi yaparken yazıyıda değştiriyor.

ali, hasan.huseyin?veli geldi    mi? 
ali\0 hasan\0huseyin\0veli\geldi\0   mi\0	bu hale getiriyor

İSPATI

	for (int i = 0; i < 30; i++)
		printf("%d", str[i]);	// burada 0 ile yazılanlar null character.

		BUNUN KODU ÖDEV


=====================================================================================
=====================================================================================
=====================================================================================
=====================================================================================
=====================================================================================



EXTERN ve STATIC IN GLOBAL ALANLARDA KULLANIMI.

bir c yada cpp programı her zaman birden fazla kaynak dosyalardan oluşur.

ali.c			veli.c			hasan.c
								int x = 10;
								void foo(void)
								{}



ömer.c x i kullanabilecek veya veli.c foo yu kullanabilecek hale getirebilir.
isterse de diğer modüllere kullanım hakkı vermeyebilir.
Object oriented dillerdeki public ve private kullanımı gibi.

Linkage
-------
Eğer bir isim aynı projeyi oluşturan birden fazla kaynak dosyada kullanıldığında, aynı varlığa işaret ediyorsa
böyle isimlerin bağlantı kategorisi external linkage dır.

Eğer bir isim aynı projeyi oluşturan birden fazla kaynak dosyada kullanıldığında, farklı varlığa işaret ediyorsa
böyle isimlerin bağlantı kategorisi internal linkage dır.

Eğer bir isim kendi kaynak dosyasında bile kullanılamıyorsa no linkage denir. Bunlar local nesnelerdir.


------------

Eğer bir global değişkenin/fonksiyonun projeyi oluşturan diğer kaynak dosyalarda da kullanılmasını istiyorsam 
bu değişkeni(ismi) dış bağlantıya koymam lazım.

sadece kendisi kullanacaksa iç bağlantıya koymak gerekir.


DIŞ BAĞLANTI / EXTERNAL
-----------------------
Hiçbir şey yapmaya gerek yok.
default olarak dış bağlantı.

int x = 10; // dış bağlantıya ait

void foo(int x) // dış bağlantıya ait
{ }


İÇ BAĞLANTI / INTERNAL
----------------------

İç bağlantıya almak için tanımda static keyword kullanılacak

static y = 56; // iç bağlantıya ait
static void foo(void) // iç bağlantıya ait
{ }



------------------------------------------------------------------
------------------------------------------------------------------
------------------------------------------------------------------
------------------------------------------------------------------
------------------------------------------------------------------


//derleyici sen bunun için yer ayırma.
//Bunun projeyi oluşturan başka bir dosyada global değişken olduğunu bil.
extern int x;

-----------
IMPLEMENTASYON AŞAĞIDAKİ GİBİ OLMALI.

ali.h						ali.c		
extern int x;				int x = 10;
extern int a[];				int a[20] = {0};
//içine 20 yazmasakta olur

extern void(func)(int);		void func(int x)  // fonksiyonlar sözkonusu olduğunda extern koysakta,
							{}					// koymasakta extern kabul ediliyor.



EĞER erişim istemezsek.
Sadece kod file a yani .c uzantılı file a static ile bildirim yapılır

ali.h						ali.c
bildirim yok				static int g = 20;
Bildirim yok				static void func(void)
							{ }


Soru?
statici koymasak ama başlıkta da gerek yok diye bildirim yapmasak olmaz mı?
olmuyor.Linker time da hata alırız.AYNI İSİMLİ GLOBAL DEĞİŞKEN VEYA FONKSİYON KULLANILIRSA HATA OLUR.
YADA UNDEFİNED BAHAVİOR.

ÖRNEK ÜZERİNDE BAKALIM

nutility.c içinde print_array var

ben main içinde void print_array(...) benzer birşey tanımlayıp çalıştırsam
linker time da hata alırız veya UB oluşur.
ÇÜNKÜ DIŞ BAĞLANTIYA AİT İSİMLER TEK OLMALI.!!!!!!!!!!!!!!!!

FONKSİYONU ASLA STATIC İLE HEADER FİLE DA BİLDİRME !!!
HİÇBİR ANLAMI YOK.YANLIŞ. HEADER FİLE DA STATİC İLE BİLDİRİM VEYA TANIMLAMA YAPMA.

KURAL
DIŞARIYA AÇIKSA EXTERN İLE HEADER FİLE A BİLDİRİM YAP
DIŞARIYA AÇIK DEĞİLSE CODE FİLE DA STATİC İLE BİLDİR.

burada bir sorun oluşuyor.
global namespace pollution problem
global isim alanı kirlenmesi problemi.

dış bağlantıya açık isimler özelleştiriliyor.önüne bir ek veya bir alt tire falan konuluyor.

C++ ta namespace ler var. BU çakışmaları engelliyor.

-----------------------------------------------------------------

ÖRNEK:

nutility.c
const int primes[] = {0,2,3,5,7 ...............}; // rakamla eşlemek için başa 0 koydu

nutility.h 
extern const int primes[];


main.c
#include ....
#include "nutility.h"

int main()
{
	int n;
	printf("kacinci asal :");
	scanf("%d",&n);

	printf("%d. asal sayi %d",n,primes[n]); // copiler primes ı aradı nutility.h den gelen bildirim ile eşledi.
											// bunun başka bir dizide olan global bir değişken olduğunu anladı ve ona göre 
											// hareket etti.yani primes ı obje koda / amaç koda linkerın göreceği bir
											// isim olarak yazdı.
}


macro olarakta yazılabiliyor.

#define		nthprime(x)			(primes[x])

EĞER

private hale getirmek isteseydim yani dışarıya kapatmak isteseydim,
başına static koyup, nutility.h den de silecektim bildirimi.


NOT:
Nutility.h deki fonk. bildirimlerine extern koyulabilir ama fonksiyonlarda zaten extern koyulmuş gibi işlem görüyor.
gerek yok.bizde hiçbirine extern koymadık zaten.

--------------------------------------------------------------------------
--------------------------------------------------------------------------
--------------------------------------------------------------------------

şöyle bir case olabilir. nutility.c deki icmp fonksiyonu sadece iç bağlantı olarak kullanıma sunulmuş.
nutility.h den de icmp static olduğu için silindi artık.

AMA QUICK_SORT YUKARIDA ICMP DE AŞAĞIDA. NUTİLİTY.H DE ARTIK BİLDİRİMDE YOK.
BURADA NUTİLİTY.C DE QUCIK_SORTUN YUKARISINA ICMP NİN BİLDİRİMİNİ YAZMAK LAZIM YA DA 
İCMP Yİ YUKARI QUICK_SORT UN YUKARISINA TAŞIMAK GEREKİR.BEN BİLDİRİM YAZACAĞIM.


nutility.c

static int icmp(const void* vp1, const void* vp2); // bildirimde vp1 veya vp2 yazmaya gerek te yok.

void quick_sort(int*p, size_t size)
{
	qsort(p,size,sizeof(*p),&icmp);
}

static int icmp(const void* vp1, const void* vp2)
{
	return *(const int*)vp1 - *(const int*)vp2;
}


========================================================================================================
========================================================================================================
========================================================================================================
========================================================================================================
========================================================================================================
========================================================================================================

TYPE MODIFIERS
--------------

Volatile her mülakatta çıkıyor. C++ ta var

const c++ ta var

restrict c99 da eklendi ve C++ ta yok.


CONST
-----

Bildiğimiz const
Bir değişkenin değerinin değişmemesi gerektiğini belirtiyor.

const int ile int const aynı.
Sadece const olarak verilirse const int olarak çalışır.

const int x = 10;
const int a[5] = {3,5,7,9,11};

//x = 98; hata

const ile dizi tanımlanırsa bunun hiç değişmeyeceğini söylüyoruz.lookup table aslında.
aynı zamanda compiler daha iyi optimizasyon yapar const ile.

const correctness 
C programının kalitesini belirliyor bu.
Kullanılması gereken yerlerde kullanacağız.

int x = 10;
const int *ptr = &x;
low lovel const - pointer to const int
*ptr = 56; hata


int y = 20;
int * const ptr = &x;  const pointer to int
top level const
ptr = &y; hata


const int * const ptr = &x;  const pointer to const int.
ptr = &y hata
*ptr = y; hata

BU kısımda fonksiyon pointerları kısmına girdi hoca.
geri dönüş değeri fonksiyon olan fonksiyonların bildirimini yaptı.Şu çok karmaşık olanları.
ben geçen baya bakmıştım ve anlamıştım.
yazma ihtiyacı duymuyorum.

Sadece birini yazayım

int foo(int,int)  -> geri dönüş değeri bu func olan bir fonksiyon yazacağım.

??? func(int)
{	}

?? yerine ne gelir.

fonksiyon adresi = int (*fp)(int,int),   geri dönüş değeri bu olacak bunu yazıyorum ve
functa yazan int x parametresini buradaki fp ye ekliyorum

int (*fp(int x))(int,int)

typedef ile de kısaltılıyor.

----------

int x = 10;
int y = 20;
int *p = &x;
int *q = &y;

int ** ptr = &p;
ptr = &q;
*ptr = &x;
**ptr = 100;  hepsi legal

Const durumuna görede değiştirilemiyor. daha önce yapmıştık o yüzden yazmıyorum.


typedef int *PTR;

int x = 10;
int y = 10;
const PTR p = &x;  burada	int * const p = &x; demek aslında

------------------------------------------------------------
------------------------------------------------------------
------------------------------------------------------------

VOLATILE
--------

değişkenler 2 farklı yapıda oluyor.
program dışı kaynakları tarafından değiştirilen nesneler.
mesela bir kod var ve dışarıdan bir aygıtın bu bellek alanını set edebileceğini biliyoruz.
burada volatile kullanılır.

dış kaynaklar tarafından değiştirilebilen varlıklar,
memory mapped file olabilir.
birtakım cihazların registerları olabilir.
interruptlarla ilgili olabilir ...

bu tip örnekler ile ilgili derleyicinin optimizasyon problemi var.

DİKKAT!!!!
Aşağıda compiler g yi registerlara alır.registerlara almasının sebebi, memory den erişim maliyeti
registerlardan erişime göre çok fazla.g nin de değişmediğini görünce her seferinde registerlardan
veriyi işleme sokar.çünkü daha maliyetsiz.
AMA
Dış dünyadan başka bir cihaz, g nin değerini değiştirirse bunu anlayamadan tekrar cpu registerdan
değeri okuyup işlemlere soktuğu zaman hata ile karşılaşma şansımız çok yüksek.
Aşağıda bunun örneği var

int g = 20;

int main()
{
	if(g == 20)
	{
		
	}
}

(NOT: g++; olsaydı değiştiğini anlayacaktı. ama değişmemiş zannedip buna göre optimizasyon yapıyor.
volatile ile bu optimizasyonu iptal ediyoruz.yine memory den her durumda değeri çekiyor.)

Bunu engellemek için volatile keyword kullanılır.
volatile her seferinde veriyi memory den oku demektir.
Değiştirilirse de oradan okuduğunda anlayacak.
Burada bir optimizasyon yapmaktan kaçacak compiler.

yani volatile ile nitelenen değişken her zaman memory den okunacak, registerdan değil.
Optimizasyonu iptal ediyor.

örnek:

int flag = 1;

int main()
{
	while(flag)		// bir interrupt gelip flagi 0 yapıyor ama döngü halen dönmeye devam ediyor.
	{				// çünkü optimizasyon açıkregisterdan okundu değer.
					// volatile int flag = 1 ile tanımlanmalıydı.
	// code
	// code
	}
}

doğru olan

volatile int flag = 1;

int main()
{
	while(flag)		
	{				
		// code
		// code
	}
}

-----------------------

--------------------------------------------------------------------|
								    |
NOT!!!!!! DÖKÜMANTASYONDAN ALDIM				    |
Volatile değişkeni,volatile olmayan bir lvalue değişken ile	    |
read/write yapmak UNDEFINED BAHAVIOR.				    |
								    |
volatile int n = 1; // object of volatile-qualified type	    |
int* p = (int*)&n;						    |
int val = *p; // undefined behavior.				    |
								    |
--------------------------------------------------------------------|


-----------------------


volatile int x = 123;

int main()
{
	volatile int *ptr = &x;
	*ptr;		// bu her çağırıldığında memory den tekrar okur değerini.Registerdan değil. 

	Eğer
	int * volatile ptr; // dersek bu seferde ptr ye her eriştiğimde optimizs. yapmayacak. Memoryden okuyacak.

	
	volatile int * volatile ptr = &x; // dersek *ptr ve ptr volatile oldu.
}

--------------------------------

#define		XREG		(int)0x1ac4

int main()
{
	volatile int *ptr = XREG; derleyici her seferinde bu adresi memory den dereference etmek zorunda.
}

---------------------------------

diğer keyworklerle kullnılabilir.

const volatile int t = 10;
volatile int z = 20;
const int a = 30;


ÇOK ÖNEMLİ !!!!!!!
const volatile int t = 10;  
t nin değeri değişmeyecek ama program dışı varlıklar const a rağmen t yi değiştirebilir.
const program içi kaynaklar tarafından değeri değişmeyecek demek.

--------------------------------
--------------------------------

AŞIRI GARİP BİR ÖRNEK.
BURADAKİ HATA TUHAF

int main()
{
	int a[10] = {0};
	volatile int i;
	
	for(i = 0; i <= 10; i++) // burada UB var ama olan olay şu.
		a[i] = 0;			// dizinin memory deki yeri bittikten hemen sonra, 
							// i nin değeri gelebiliyor.Yani a[9] son eleman, a[10] ise 
							// ub ama compiler a[10] adresini i nin adresi olarak atayabiliyor.
							// o zamanda a[10] = 0; demek i = 0; demek oluyor.
							// infinite loop :D:D:D:D:D
							// bunu volatile yapıyor her seferinde memory den okuduğu için :D:D
							// birçok derleyicide sonsuz göndüye girebiliyor.Garantisi yok.
}








	*/

#include <string.h>

int main()
{
	printf("%d", primes[4]);


}
