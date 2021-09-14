
/*

	if(x & 1) bu sayının 0. biti 1 mi diye soruyor.
	
	--------

	16 bitlik bir tamsayının ortasındaki 8 bitlik bir tamsayıyı nasıl elde ederiz ? 
	bu sayı bir unsigned int olsun.

	1010 1100 1100 1010		 x 
	1100 1100 1100 0000		 x << 4
	0000 1100 1100 1010		 x >> 4

	1. bunları ve işlemine sokarsam olur 
	x >> 4 & x << 4 ortadaki 8 bit elde edilir.

	2. yol
	x << 4 >> 8; buda olur.Hatta bu daha iyi bir idiyom.

	--------------------------------------------------------

	Geçen ders verilen ödev
	swap ödevi  AB CD EF GH -----> GH EF CD AB olacak
	
	NOT
	0x000000FF bu 255 yani 00000000000...11111111
	
	Buradaki mantık şu,
	1. aşamada 24 bit sağa kaydırılır ve son 8 bitini 11111111 (FF) ile & işlemine sokulur.
	24 neden kaydırıldı çünkü yer değiştiriyoruz aynı zamanda
	
	2. aşamada sayı 8 bit sağa kaydırıldı, bu sayede ortanın solundaki bit ortanın sağına geldi.
	Bizde bu ortanın sağını FF ile & işlemine sokarız. aşağıdaki macroda nasıl yapıldığu mevcut

	3. aşamada sayı 8 bit sağa kaydırıldı ve ortanın sağındaki bitler ortanın soluna geldiler.
	Buradan sonra da FF ile & işlemine sokulur.

	4. aşamada en sağdakini en sola getirmek için 24 bit kayıdrıldı ve 0xFF000000 ile & işlemine soktuk
	ve tüm sonuçları birleştirmek için | işlemine soktuk.





#define		Swap4Bytes(x)		((((x) >> 24) & 0x000000FF) | \
								(((x) >> 8) & 0x0000FF00) | \
								(((x) << 8) & 0x00FF0000) | \
								(((x) << 24) & 0xFF000000))





-----------------------------------------------------------
-----------------------------------------------------------
-----------------------------------------------------------

kullanılan temalardan biri, bir tamsayının bitlerinin, bir boolean dizi olarak kullanılması.
1 yada 0

1 bytta 8 adet boolean saklanır çünkü 8 bit.
Birçok kütüphane bunu kullanıyor.

ör:
NOT: Gerçek anlamda çalışna bir kod değil. olayı göstermek için yazıldı aşağısı

#define		DIRECTORY		1
#define		ARCHIVE			2 // 1 << 1 şeklinde de yazılabilirdi
#define		READONLY		4
#define		HIDDEN			8
#define		SYSTEM			16



struct fileprop{
	char name[20];
	size_t len;
	//
	unsigned fa; //bitlerin özelliklerini tutacak bu ama nasıl tutacak ? Macrolar ile tutacak.yukarıya tanımladık.
};				// Bu macrolar 2 nin katları şeklinde

int main()
{

	struct fileprop* pf;
	//dosya mesela readonly mi diye sorgulamak istesem if(pf->fa & READONLY) derim
	// çünkü readonly ye denk gelen biti, fa barındırıyorsa cevap evettir.

	//dosya readonly olsun istersem
	pf->fa |= READONLY;  //set

	//readonly olmasın istersem
	pf->fa &= ~READONLY;  // reset

	// readonly olma özelliğini tersine çevirmek için 1 ise 0, 0 ise 1 yapmak
	pf->fa ^= READONLY; // flip

}

----------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------


KENDİ CTYPE KÜTÜPHANEMİZİ YAZACAĞIZ.
BİR TAMSAYININ BİTLERİNİ KULLANACAĞIZ BUNU YAPARKEN.
1010 0001 HER BİR BİT BİR ÖZELLİĞE İŞARET EDECEK.
MESELA

int c = 65;
int a[200];
a[c]  = a nın 65 indexli elemanını verir. bununda özellikleri 1001 1000 olsun, bu da zaten = 152 yapıyor.
		o zaman a[65] = 152 oldu (yada 1001 1000). sonrasında ISUPPER 0000 1000 ile gösteriliyor olsun & işlemine sokarsak
		a[c] & ISUPPER = eğer true ise c büyük harflidir.



--------------------------------------
--------------------------------------
--------------------------------------
--------------------------------------
--------------------------------------

BURADA MYCTYPE MODÜLÜNÜ YAZIYORUZ.

Aşağıdaki kod ile her karantere denk gelen bitleri set ettik.

#define		UPPER			1
#define		LOWER			2 // 1 << 1 şeklinde de yazılabilirdi
#define		DIGIT			4
#define		XDIGIT			8
#define		SPACE			16
#define		PUNCT			32
#define		PRINT			64
#define		CNTRL			128

	for (int i = 0; i < 128; ++i)
	{
		unsigned int x = 0;
		if(i && i % 8 == 0)
			putchar('\n');

		if (isupper(i))
			x |= UPPER; // eğer Uppercase ise karakter, x i bitsel anlamda değiştirdik. 0000 0001 ile veya yaptık yani.
		if (islower(i))
			x |= LOWER;
		if (isdigit(i))
			x |= DIGIT;
		if (isxdigit(i))
			x |= XDIGIT;
		if (isspace(i))
			x |= SPACE;
		if (ispunct(i))
			x |= PUNCT;
		if (isprint(i))
			x |= PRINT;
		if (iscntrl(i))
			x |= CNTRL;

		printf("%d, ", x); // buradan elde ettiğim kodu alıp myctype.c ye koyacağım.

	}

	--------------------------------------------------------------------------------
	--------------------------------------------------------------------------------
	--------------------------------------------------------------------------------

	Ör:

	int main()
{

	int ch;
	printf("bir karakter girin : ");
	ch = getchar();

	if (is_upper(ch))
		printf("buyuk harf\n");
	else
		printf("buyuk harf degil\n");

	if (is_alpha(ch))
		printf("alpha\n");
	else
		printf("alpha degil\n");


	if (is_punct(ch))
		printf("punct char\n");
	else
		printf("punct char degil\n");

}

=======================================================================================
=======================================================================================
=======================================================================================
=======================================================================================

BİR TAMSAYININ BİT ALANLARINI FARKLI DEĞİŞKENLER OLARAK KULLANABİLİR MİYİZ ? 

variable

int 2 byte olsun

int a = 9;

---- ---- xxxx zyyy

xxxx leri farklı bir değişken olarak kullanacağım
ilk önce xxxx i sıfırlamam lazım

---- ---- xxxx zyyy
1111 1111 0000 1111  ve işlemi
------------------------------
---- ---- 0000 zyyy   

a nın bu 4 bite sığacak boyutta olmalı. bizde a = 9 
a << 4 yapıyoruz ki 2. 4 bite kaysın.
sonra da yukarıda sıfırladığımız sayı ile a yı veyalayacağız.


AMA BUNLARI NEDEN YAPIYORUZ ?

Hem değişkenleri birarada tutmak hemde yerden tasarruf hemde işlemlerin hızlı yapılması için.
bitsel işlemler çok hızlı yapılıyor.

Gömülü tarafta çok kullanılıyor

BU İŞLEMLERLE BİZ UĞRAŞMAYACAĞIZ.
BU KONUDA HAZIR BİR ARAÇ VAR.


BİT FİELDS / BİT ALANLARI
--------------------------


typedef struct {
	//Yapının x isimli elemanı 4 bitlik alanda tutulacak demek.
	unsigned int x : 4;
}Data;


int main()
{

	Data mydata;
	mydata.x = 5; // derleyici burada x i 4 bitlik bir alanda tutacak. Bunu bitsel operatör kullanarak yapmıyoruz.
					// compiler bizim için yapıyor.Çok zahmetli oluyor zaten bitsel operatörlerle.
					//birde compiler her zaman daha iyi kod yazıyor zaten.Optimizasyon ....

	Data* p = &mydata;
	p->x = 4;

}

------------------------------------

Yapının elemanları birden fazla olabilir. genelde böyle zaten.
bitfield elemanlarla olmayan elemanlar aynı yerde olabilir.


typedef struct {
	int a,b;
	double d;
	unsigned int x : 4;
	unsigned int y : 3;
	unsigned int z : 2;
	unsigned int t : 5;
}Data;


---------------

Böyle durumlarda yapının sizeof u işlemcinin kelimesinin katları şeklinde büyüyor
buna storage unit deniyor.
mesela 4 byte = 32 bit storage unit demek.
sadece int yazdığımızda diğer heryerden farklı olarak, 
bunun unsigned mı yoksa signed int mi olacağı IMPLEMENTATION DEFINED.


	32 bite kadar 4 byte kaplar
	typedef struct {
	unsigned int x : 4;
	unsigned int y : 3;
	unsigned int z : 2;
	unsigned int t : 5;
}Data;

burası ise 8 byte
typedef struct {
	unsigned int x : 7;
	unsigned int y : 7;
	unsigned int z : 7;
	unsigned int t : 7;
	unsigned int a : 5;
}Data;

----------------------------

CPPREFERENCE ÖRNEKLERI

struct S {
	// will usually occupy 4 bytes:
	// 5 bits: value of b1
	// 11 bits: unused
	// 6 bits: value of b2
	// 2 bits: value of b3
	// 8 bits: unused
	unsigned b1 : 5, : 11, b2 : 6, b3 : 2;
};
int main(void)
{
	printf("%zu\n",sizeof(struct S)); // usually prints 4
}

--------------------------

struct S {
	// will usually occupy 8 bytes:
	// 5 bits: value of b1
	// 27 bits: unused
	// 6 bits: value of b2
	// 15 bits: value of b3
	// 11 bits: unused
	unsigned b1 : 5;
	unsigned :0; // start a new unsigned int
	unsigned b2 : 6;
	unsigned b3 : 15;
};
int main(void)
{
	printf("%zu\n", sizeof(struct S)); // usually prints 8
}

mesela x burada bit alanı içinde nerede tutulacağı implementation defined.
manuel yapmak riskli. ok veya nokta operatörü ile erişip yaptırmak mantıklı.

----------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------

Dersin 22 dakikalık kısmını kaydetmeyi unuttuk.
burada 16 bitlik sistemlerde saniyenin neden 2 şer 2 şer gittiği konuşuldu. 
Çünkü 60 saniyeyi tutacak alan yok, 30 saniye tutulup 2 ile çarpılıyor.
bunu bizim Date kütüphanesi ile kullandı sanırım.


typedef union {
	uint32_t uval;
	struct {
		unsigned int day : 5; // 31 gün tutuyor
		unsigned int mon : 4; // 12 ay gereniyor ve 15 tutabiliyor 4 bit
		unsigned int year : 7; // ...
		unsigned int hour : 5;
		unsigned int min : 5;
		unsigned int sec : 5;
	};
}DateTime;




int main()
{
	DateTime dt = {
		.day = 22,
		.mon = 4,
		.year = 2021 - 1980,
		.hour = 22,
		.min = 4,
		.sec = 56 / 2
	};

	printf("tamsayi degeri : %u", dt.uval); // unionda tüm elemanlar aynı yeri kullandığından bu özellik kullnılabilir.
	//nonstandart extension durumu yok. standart hale geldi bu.
}

------------

Data sonra bu şekilde geri dönebiliriz.


int main()
{
	DateTime dt = {
		.uval = 1888899734u
	};

	printf("tamsayi degeri : %02u-%02u-%02u %02u:%02u:%02u", dt.day,dt.mon,dt.year +1980,dt.hour,dt.min,dt.sec);

}

-----------------------------------------------------
-----------------------------------------------------
-----------------------------------------------------

typedef union {
	uint32_t uval;
	struct {
		unsigned int bit0 : 1;
		unsigned int bit1 : 1;
		unsigned int bit2 : 1;
		unsigned int bit3 : 1;
		unsigned int bit4 : 1;
		unsigned int bit5 : 1;
		unsigned int bit6 : 1;
		unsigned int bit7 : 1;
		unsigned int bit8 : 1;
		unsigned int bit9 : 1;
		unsigned int bit10 : 1;
		unsigned int bit11 : 1;
		unsigned int bit12 : 1;
		unsigned int bit13 : 1;
		unsigned int bit14 : 1;
		unsigned int bit15 : 1;
		unsigned int bit16 : 1;
		unsigned int bit17 : 1;
		unsigned int bit18 : 1;
		unsigned int bit19 : 1;
		unsigned int bit20 : 1;
		unsigned int bit21 : 1;
		unsigned int bit22 : 1;
		unsigned int bit23 : 1;
		unsigned int bit24 : 1;
		unsigned int bit25 : 1;
		unsigned int bit26 : 1;
		unsigned int bit27 : 1;
		unsigned int bit28 : 1;
		unsigned int bit29 : 1;
		unsigned int bit30 : 1;
		unsigned int bit31 : 1;
	};
}Mint;

int main()
{
	printf("%zu", sizeof(Mint)); // 4 bytte yer kaplar çünkü 32 adet 1 bitlik struct var. o da 4 byte diğerdeğişkende 4 byte.
									// ve aynı bellek alanlarını kullanıyorlar.
}

--------------------------------------------

int main()
{
	printf("%zu\n", sizeof(Mint)); // 4 bytte yer kaplar çünkü 32 adet 1 bitlik struct var. o da 4 byte diğerdeğişkende 4 byte.
	Mint x = { .uval = 761987u };
	printf("%u\n", x.bit5);
	printf("%u\n", x.bit0);

	x.bit3 = 1;
	x.bit5 = 1;
	x.bit7 = 1;
	x.bit17 = 1;
	x.bit23 = 1;
	printf("%u\n", x.uval);
}

=================================================================================================================
=================================================================================================================
=================================================================================================================
=================================================================================================================
=================================================================================================================
=================================================================================================================
=================================================================================================================


KOMUT SATIRI ARGÜMANLARI - COMMENT LINE ARGUMENTS
-------------------------------------------------

BİR AYAR YAPILACAK.
PROJECT->PROPERTIES->
					OUTPUT DIR -> EXENİN OLUŞTURULACAĞI DİRECTORY	
					TARGET NAME -> EXENİN ADI


birçok program komutsatırından çağrılıyor ve argüman veriyoruz
copy.exe ali.txt veli.txt  gibi 



MAINI ŞU ŞEKILDE TANIMLIUYORUZ.

main(int argc,char **argv)
{
}

argc -> komut satırını kullanırken yazdığım argüman sayısı + komutun sayısı(1) (copy ali veli   --> argc 3 oldu mesela)
argv -> gönderilen stringlerin adresleri(char * ptr[] gibi, bunu fonksiyona gönderirken char **p diye göndermek yaygın)
bu ikisi keyword değil.sadece isim.Genelde bu isimler veriliyor.

argc ===> Argument Count
argv ===> Argument Vector



HATIRLATMA !!!!!!!!!!!
void func(int p[])  veya   void func(int* p) aynı şey
void func(int (*p)[])  veya   void func(int p[][]) aynı şey, 
HATIRLATMA!!!!!
AMA void func(int **p) bunlarla aynı değil. Bu en çok yapılan hata.


ÖRNEK: 
int main(int argc, char **argv)
{
	printf("argc = %d\n", argc);

	for (int i = 0; i < argc; ++i)
	{
		printf("argv[%d] = %s\n", i, argv[i]);
	}

	//buradan sonra projeyi build ediyoruz ve oluşan exeyi rename ettikten sonra çalıştırıyorum powershell den.
	// .\Nec.exe ali hakan veli 234 123.2
	// argv[0] = D:\CSD\49_22_04_2021\49_22_04_2021\Nec.exe
	// argv[1] = ali
	//	argv[2] = hakan
	//	argv[3] = veli
	//	argv[4] = 234
	//	argv[5] = 123.2

}

----------------------------------------------
----------------------------------------------

Eğer argc değeri belliyse bunu sınayıp hata verdirebiliriz.

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "dogru kullanim <kopyala> <kaynak dosya> <hedef dosya>\n");
		return 1;
	}

	printf("%s isimli dosyanin %s isimli kopyasi olusturuldu\n",argv[1],argv[2]);
	//build et
}

PS D:\CSD\49_22_04_2021\49_22_04_2021> .\kopyala.exe ali
dogru kullanim <kopyala> <kaynak dosya> <hedef dosya>
PS D:\CSD\49_22_04_2021\49_22_04_2021> .\kopyala.exe ali veli
ali isimli dosyanin veli isimli kopyasi olusturuldu
PS D:\CSD\49_22_04_2021\49_22_04_2021>

--------------------------------------------------

ÖRNEKLER:

günü yazdıran program

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		fprintf(stderr, "kullanim : <negubu> <gun> <ay> <yil>\n");
		return 1;
	}

	Date mydate;
	//argv[0] programın kendi adı
	set_date(&mydate, atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
	print_date(&mydate);
	//build et
}


PS D:\CSD\49_22_04_2021\49_22_04_2021> .\negunu.exe 12 3 2015
12 Mart 2015 Persembe
PS D:\CSD\49_22_04_2021\49_22_04_2021>


-----------------------------------------------------------------------------------

ÖRNEK:

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "kullanim : <primes> <kucuk sayi> <buyuk sayi>\n");
		return 1;
	}

	int low = atoi(argv[1]);
	int high = atoi(argv[2]);
	int cnt = 0;

	for (int i = low; i <= high; ++i)
	{
		if (isprime(i))
		{
			++cnt;
			printf("%d ", i);
		}
	}
		printf("\n%d adet asay sayi bulundu\n",cnt);
	//build et
}

PS D:\CSD\49_22_04_2021\49_22_04_2021> .\primes.exe 175 777
179 181 191 193 197 199 211 223 227 229 233 239 241 251 257 263 269 271 277 281 283 293 307 311 313 317 331 337 347 349 353 359 367 373 379 383 389 397 401 409 419 421 431 433 439 443 449 457 461 463 467 479 487 491 499 503 509 521 523 541 547 557 563 569 571 577 587 593 599 601 607 613 617 619 631 641 643 647 653 659 661 673 677 683 691 701 709 719 727 733 739 743 751 757 761 769 773
97 adet asay sayi bulundu


-------------------------------------------------------------------------------------

BASİT BİR HESAP MAKİNASI

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		fprintf(stderr, "usage : <hesapla> <left operand> <operator * / + - > <right operand>\n");
			return 1;
	}

	char islem = *argv[2]; // string gelir. indirection/dereference yaparak char a erişirim
	int left_operand = atoi(argv[1]);
	int right_operand = atoi(argv[3]);

	switch (islem)
	{
	case '*':
		printf("%d * %d = %d", left_operand, right_operand, left_operand * right_operand);
		break;
	case '/':
		if (right_operand != 0)
			printf("%d * %d = %f", left_operand, right_operand, (float)left_operand / right_operand);
		else
			printf("0 a bolme hatasi\n");
		break;
	case '+':
		printf("%d * %d = %d", left_operand, right_operand, left_operand + right_operand);
		break;
	case '-':
		printf("%d * %d = %d", left_operand, right_operand, left_operand - right_operand);
		break;
	default:
		printf("gecersiz islem operatoru yazildi\n");
		break;
	}

	//build et
}


PS D:\CSD\49_22_04_2021\49_22_04_2021> .\hesapla.exe 54 * 87
54 * 87 = 4698
PS D:\CSD\49_22_04_2021\49_22_04_2021> .\hesapla.exe 5477 / 87
5477 * 87 = 62.954021
PS D:\CSD\49_22_04_2021\49_22_04_2021> .\hesapla.exe 57 - 87
57 * 87 = -30
PS D:\CSD\49_22_04_2021\49_22_04_2021> .\hesapla.exe 57 + 87
57 * 87 = 144
PS D:\CSD\49_22_04_2021\49_22_04_2021>

---------------------------------------------------------
---------------------------------------------------------
---------------------------------------------------------

ÖNEMLİ BİR NOT

argc[argc] = NULL POINTER OLMAK ZORUNDA. Buna güvenerek kod yazılabilir.

int i = 0;
while(argv[i] != NULL)
{
	.....
	++i;
}


---------------------------------------------------------
---------------------------------------------------------
---------------------------------------------------------


int main(int argc, char *argv[])
{
	char source_name[80];
	char dest_name[80];

	if (argc != 3)
	{
		printf("source filename:");
		scanf("%s", source_name);
		printf("dest filename:");
		scanf("%s", dest_name);
	}
	else
	{
		strcpy(source_name, argv[1]); // aslında strcpy(source,dest); gibi birşey yazılmalı bence ama mantığını anlamak önemli.
		strcpy(dest_name, argv[2]);
	}
	printf("%s dosyasinin %s isimli kopyasi oluşturuldu\n",source_name,dest_name);


//build et
}


---------------------------------------------------------
---------------------------------------------------------
---------------------------------------------------------

BURADA VERİLKEN ARGÜMANLARI SIRALAYACAĞIZ.

SİRALA ALİ VELİ HASAH HUSEYIN MAHMUT MEHMET

int scmp(const void* vp1, const void* vp2)
{
	return strcmp(*(char**)vp1,*(char**)vp2);
}


int main(int argc, char *argv[])
{
	char** pd = (char**)malloc((argc - 1) * sizeof(char*));

	int i = 1; // ilk(0. ıncı) eleman komutun adı.bu yüzden 1 den başladı
	while (argv[i] != NULL)
	{
		pd[i -1] = argv[i]; // buraya dikkat
		++i;
	}

	qsort(pd, argc - 1, sizeof(*pd), &scmp);

	for (int j = 0; j < argc-1; ++j) // komutun adını çıkarmıştık
		puts(pd[j]);

	free(pd);

//build et
}


PS D:\CSD\49_22_04_2021\49_22_04_2021> .\sirala.exe ali veli hasan huseyin mumtaz hakan
ali
hakan
hasan
huseyin
mumtaz
veli



*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "date.h"
#include "nutility.h"
#include <string.h>

int scmp(const void* vp1, const void* vp2)
{
	return strcmp(*(char**)vp1,*(char**)vp2);
}


int main(int argc, char *argv[])
{
	char** pd = (char**)malloc((argc - 1) * sizeof(char*));
	
	int i = 1; // ilk(0. ıncı) eleman komutun adı.bu yüzden 1 den başladı
	while (argv[i] != NULL)
	{
		pd[i -1] = argv[i]; // buraya dikkat
		++i;
	}

	qsort(pd, argc - 1, sizeof(*pd), &scmp);

	for (int j = 0; j < argc-1; ++j) // komutun adını çıkarmıştık
		puts(pd[j]);

	free(pd);

//build et
}