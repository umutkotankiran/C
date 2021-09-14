#define _CRT_SECURE_NO_WARNINGS


/*
	DERSİN İLK 13-14 DAKİKASINI KAYDA ALMAYI UNUTTU HOCA

	#define			SIZE		5'000'000

	const char* const pdays[] = {
		"Pazar",
		"Pazartesi",
		"Sali",
		"Carsamba",
		"Persembe",
		"Cuma",
		"Cumartesi"
	};

	int main()
	{
		int day, mon, year;
		struct tm timeinfo;

		printf("bir tarih girin\n");
		scanf("%d%d%d", &day, &mon, &year);
		timeinfo.tm_year = year-1900;
		timeinfo.tm_mon = mon - 1; // sturct ta 0-11 arasıdı aylar o yüzden -1
		timeinfo.tm_mday = day;

		timeinfo.tm_hour = 0;
		timeinfo.tm_min = 0;
		timeinfo.tm_sec =	1;
		mktime(&timeinfo); // localtime ın tersini yapıyor.return değeri epoche tan geçen saniyedir.

		printf("%s\n", pdays[timeinfo.tm_wday]); // bu örnekte windows ayarlarında bir gariplik var.
												// burada yanlış gösterebiliyor bazen tarihi.

		// WEB de haftanın günlerini bulan bir kod var. onu yazmayacağım. Oneliner şeklinde
	}

	=====================================================================================
	=====================================================================================
	=====================================================================================
	=====================================================================================
	=====================================================================================
	=====================================================================================
	
	COMPLETE VE INCOMPLETE TYPES
	----------------------------
	Özellikle incomplete type derleyicinin verdiği bazı sentaks hatalarında karşımıza çıkar.

	Derleyici Örneğin bir yapı türünün varlığından haberdar ise ancak bu türün tam bildirimini
	henüz görmemişse bu tür bir incomplete type tır.

	ÖR:
	struct Data;	
	bu bir bildirim. Derleyici struct data isimli bir t ürün varlığını bildiriyor.
	Bu incomplete typetır.Belirli contextlerde kullanılır.

	// bundan bahsetmiyoruz. yukarıdakinden bahsediyoruz
	struct Data{ 
		int x, y, z;		
	};

	// bu noktada 1. yazdığımız (struct Data;) incomplete type tır 
	ve belirli durumlarda kullanılabilir.

	ÖR:
	Aşağısı sentaks hatası
	struct Data;

	int main()
	{
		struct Data mydata; // burası hata.
	}

	------------------------------------------------------------------
	------------------------------------------------------------------

	BIR INCOMPLETE TYPE ILE NELER YAPILABILIR.

	1 - tyepedef bildirimi yapılabilir.

	struct Data;
	typedef struct Data Data;
	typedef struct Data* DataPtr;

	2 - Fonksiyon bildirimlerinde kullanılabilir.

	struct Data; // bundan sonra aşağısı artık ok

	struct Data f1(struct Data);
	struct Data* f2(struct Data*);

	3 - Global değişkenler için extern bildirimi yapabiliriz.
	
	//tugrul.h
	struct Data;

	extern struct Data g;
	extern struct Data ga[];

	4 - Pointer Değişkenler tanımlayabilirim.
	
	struct Data;
	struct Data* foo(void);
	
	int main()
	{
		struct Data* ptr = NULL;
		ptr = foo();
		//
	}

	-----------------------------------------------------------------------------

	BIR INCOMPLETE TYPE ILE NELER YAPILAMAZ!! YANI COMPLETE TYPE OLMASI GEREKIR.

	1 - değişken tanımlayamayız

	struct Data;
	int main()
	{
		struct Data mydata;
	}


	2 -	Pointer dereferencing işlemleri.

	*ptr
	ptr[]
	ptr->x   bunlar yapılamaz.

	struct Data;
	struct data* f1(void);

	int main()
	{
		struct Data *px = f1(); // buraya kadar ok
		*px;	// burada artık sorun var
	}

	-------------------------
	2. örnek
	struct Data;
	struct data* f1(void);
	struct data* f2(void);

	int main()
	{
		struct Data *px = f1(); // buraya kadar ok
		struct Data *py = f2(); // buraya kadar ok
		*px = *py	// burada artık sorun var
	}


	3 - sizeof operatörünün operandı yapılamaz.

	struct Data;

	int main()
	{
		size_t sz = sizeof(struct Data); / burası hata struct Data * deseydik hata yoktu.
	}

	-------------------------------------------------
	-------------------------------------------------
	Yani bir struct data nın içerisine erişme durumu varsa burada incomplete type çalışmıyor.

	=========================================================
	=========================================================
	=========================================================

	Birsürü içiçe include edilmiş file lar olabilir.
	bizde bunları eklersek.
	bu olay bizi 50 yada 100 tane başlık dosyasını include etmeye götürür.

	compile time süresini uzatır bu.
	karman çorman bir durum oluşuyor.
	burada gereksiz bağımlılıklar oluşuyor.

	Neden bir başlık dosyası diğer başlık dosyasını include edebilir.

	başlık dosyasında bir yapı olabilir, elemanlarından biri de bir başka yapı türündendir.

	struct Ogu
	{
		struct Data mdata;  // sentaks hatası. bir yapı içerisindeki elemanı
	};						// incomplete type ile tanımlayamayız.normalde de yoktu zaten.
							// ama bazı yazılımcılar başlık dosyasını, incomplete type
							// ile yapabileceklerini bilmediği için fazladan ekliyorlar.

	ör:
	#include "data.h"
	#include "nec.h"

	struct Data func(struct Nec);

	bu include lar zorunlu değil. Bu başlık dosyalarını include etmek yerine
	struct nec ve struct data türlerini incomplete type olarak bildirmeliydi. 


	ör:
	//aşağıdaki gibi yapmalıydı.
	struct Data;
	struct Nec;

	struct Data func(struct Nec);

	Sonuç:
	Gereksiz bağımlılıklar oluşturmamak için, bir başlık dosyasını include etmeden,
	bu include a mecbur olup olunmadığı sorgulanır, ve bu bildirimler incomplete type 
	olabilir mi? diye sorgulanmalı.

	farklı şekilde de yapılıyor.

	extern struct Data x;

	int main()
	{

	}

	BURADA 2 - 2.5 SAAT LİK BİR LIVE CODING YAPILACAK.

	---------------------------------------------------------
	---------------------------------------------------------
	---------------------------------------------------------
	---------------------------------------------------------

	=======================================================================
	=======================================================================
	=======================================================================
	=======================================================================

	YAZI SAYI DÖNÜŞÜMLERİ
	---------------------

	#include <stdio.h>
	#include <time.h>
	#include "nutility.h"


	int main()
	{
		char str[100];

		printf("Bir yazi giriniz\n");
		sgets(str);				// 7654
		printf("[%s]\n", str);   // bana lazım olan string olan 7654 değil. int olan 7654

		//yazıdan sayı elde edecek primitive bir kod.
		//her durumda doğru çalışmaz. basit bir kod çünkü. 123ali düzgün çalışmaz mesela.
		int val = 0;
		for (int i = 0; str[i] != '\0'; ++i)
		{
			val = val * 10 + str[i] - '0'; // önceden yazmıştık
		}
		return val;

		// bunu yazmak yerine standart kütüphanenin kodunu çalıştırıyoruz.
		// bu fonksiyonun adı atoi.

	}

	-----------------------------------------------------------
	-----------------------------------------------------------

	ATOI

	int atoi(const char *p);
	alpha to int anlamında.

	int main()
	{
		char str[100];

		printf("Bir yazi giriniz\n");
		sgets(str);
		printf("[%s]\n", str);

		int val = atoi(str);
		printf("%d\n", val);

	}

	----------------------------------------------------------------

	int main()
	{
		char str[100];

		printf("bir tarih girin gg-aa-yyyy : ");
		sgets(str);
		printf("[%s]\n", str);

		//gün ay yılı ayrıştırmak istiyoruz.
		int day = atoi(str);
		int mon = atoi(str + 3);
		int year = atoi(str + 6);

		printf("%02d/%02d/%d", day, mon, year);

	}

	-------------------------------------------------------------
	-------------------------------------------------------------

	ATOL , ATOLL, ATOF
	atol long döndürür.
	atoll long long geri döndürür.
	atof double geri döndürür.

	int atol(const char *p);
	int atoll(const char *p);
	int atof(const char *p);


	ÖR:
	int main()
	{
		char str[100];

		printf("bir sayi girin: \n");
		sgets(str);				// 234.1234Ali gir
		printf("[%s]\n", str);

		int day = atoi(str);
		double mon = atof(str);

		printf("%d\n", day);
		printf("%f\n", mon);
	}

	-------------------------------------------------------------------------------
	-------------------------------------------------------------------------------

	Tamsayıdan Yazıya Dönüşüm
	char * _itoa(int val, char *pbuf, int radix);
	
	val = sayı
	pbuf = yazıya dönüştürülen sayının atanacağı dizi
	radix = sayı sistemi.

	-------------------------------------------------------------------
	-------------------------------------------------------------------
	-------------------------------------------------------------------

	#include <stdio.h>
	#include <time.h>
	#include "nutility.h"
	#include <stdlib.h>
	#include <string.h>

	int main()
	{
		char str[100];

		int x;
		printf("bir tamsayi girin : \n");
		scanf("%d", &x);
		int temp = x;

		// derleyiciler bunu genelde veriyor. _itoa fonksiyonu bunu yapıyor
		//_itoa(x, str, 10);

		//primitive kodu.en basit haliyle
		int idx = 0;
		while (temp)
		{
			str[idx++] = temp % 10 + '0';
			temp /= 10;
		}
		str[idx] = '\0';

		// ters çeviriyoruz. kod tersini yazıyor çünkü.
		_strrev(str);

		printf("[%s]\n", str);

	}

	----------------------------------------------------------------------

	Buda itoa ile

	int main()
	{
		char str[100];

		int x;
		printf("bir tamsayi girin : \n");
		scanf("%d", &x);		// 47802 güzel bir sayi.
		int temp = x;

		// derleyiciler bunu genelde veriyor. _itoa fonksiyonu bunu yapıyor
		_itoa(x, str, 10);	
		printf("decimal : [%s]\n", str);
		_itoa(x, str, 16);	
		printf("Hexadecimal : [%s]\n", str);
		_itoa(x, str, 2);	
		printf("Binary : [%032s]\n", str);
		_itoa(x, str, 8);	
		printf("Octal : [%s]\n", str);

		// %032s  = eğer varsa değeri yaz, yoksa yerine 0 yaz.

	}

	-------------------------------------------------------------------------
	-------------------------------------------------------------------------

	//bu kütüphaneye eklendi
	void bitprint(int val)
	{
		static char buffer[200];

		_itoa(val, buffer, 2);

		printf("%032s\n", buffer);

	}

	int main()
	{
		bitprint(25642);
	}


	=========================================================================
	=========================================================================
	=========================================================================

	BELLEK ÜZERİNDE OKUMA YAZMA İŞLEMLERİ

	Bazı durumlarda biz bizim bir ifadenin değerini ekrana yazdırmak yerine 
	onu bir yazı olarak	elde etmek isteyeceğiz.

	SPRINTF
	-------
	sprintf  --> printf ile tamamen aynı sadece bir tane parametre fazlası var.
	yazının nerede saklanacağı bilgisi bu.

	int sprintf(char *pbuf, const char *p, ...);

	int main()
	{
		char buffer[100];
		int d, m, y;

		printf("gun ay ve yil olarak tarih girin : ");
		scanf("%d%d%d", &d, &m, &y);
		printf("%02d-%02d-%02d\n",d,m,y);
	
		// bu formattaki yazıyı elde etmek için sprintf kullanılır
		sprintf(buffer,"%02d-%02d-%02d", d, m, y);

		puts(buffer);

	}

	-----------------------------------------------------------------------

	bir log file olsun ve adı o anki tarih zaman bilgisi olsun


	#define		SIZE	100

	char* get_log_file_name(void)
	{
		static char buf[SIZE];
		time_t timer;
		time(&timer);

		struct tm* p = localtime(&timer); // ayrıştırılmış zaman bilgsi
		sprintf(buf, "%d_%02d_%02d_%02d_%02d_%02d.log",
			p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);

		return buf;
	}

	3 temel printf var
	printf -> formatlı çıkışı konsola yapıyor
	sprintf -> çıkışı belleğe yapıyor
	fprintf -> çıkışı file a yapıyor.

	snprintf

	--------------------------------------------------------------------------------
	--------------------------------------------------------------------------------
	--------------------------------------------------------------------------------

	SSCANF
	------

	scanf -> değişken setting için std input bufferdan alıyor ihtiyaç duyduğu karakterleri alıyor.
	sscanf -> bellekte benim verdiğim adresten alır
	fscanf - > dosyadan alır.

	SCANF ile örnek yapılırsa
	-------------------------
	int main()
	{
		char buff[100];
		int id;
		double h_wage;
		char name[100];
		int grade;

		printf("id no, saat ucreti, isim ve not giriniz : ");
		scanf("%d%lf%s%d", &id, &h_wage, name, &grade);

		printf("id no = %d, saat ucreti = %f, isim = %s, not = %d",id,h_wage,name,grade);
	}


	SSCANF ile örnek yapılırsa
	--------------------------

	int main()
	{
		char buff[] = "123 2.6 alican 987";
		int id;
		double h_wage;
		char name[100];
		int grade;

		//printf("id no, saat ucreti, isim ve not giriniz : ");
		//scanf("%d%lf%s%d", &id, &h_wage, name, &grade);
		sscanf(buff,"%d%lf%s%d", &id, &h_wage, name, &grade); // buff tan okuyor !!

		printf("id no = %d, saat ucreti = %f, isim = %s, not = %d",id,h_wage,name,grade);
	}

	---------------------------------------------------------------------------

	SNPRINTF
	buna detaylı girmeyeceğiz.
	1. parametre yazının yazılacağı adres
	2. parametre dizinin boyutu
	3. paramtetre format stringi

	----------------------------------------------------------------------------

	STRTOD
	------
	float strtof(const char * restrict p,char ** restrict pend)
	double strtod(const char * restrict p,char ** restrict pend)
	long double strtold(const char *restrict p,char ** restrict pend)

	bunlarda yazıdan reel sayıya dönüşüm veya tamsayıya dönüşüm yaparlar.
	atof ve atoi den farkı. verdiğimiz değerin neresinde kaldığını gösterir 
	ör:
	123.32sdsd  burada  strtof kullanıldı. sdsd kısmını alamaz. sdsd nin baştaki s kısmı pend pointerının
	gösterdiği yer olur artık.


	int main()
	{
		char str[100] = "345.7845mehmet";
		char* pend;

		double dval = strtod(str, &pend); // mehmeti float a çevirmez ve pend e yazar
		printf("dval = %f\n", dval);
		printf("indis = %d\n",pend-str);
		puts(pend);

		//eğer 34.23 olsaydı puts birşey yazdırmayacaktı. pend NULL CHARACTER  gösterecekti. hocaya sordum.
	}

	======================================================================================================
	======================================================================================================
	======================================================================================================
	======================================================================================================
	======================================================================================================



	BURADAN SONRA ARTIK BİR SINIF ÇALIŞMASI YAPILIYOR.
	BİR MODÜL YAZILIYOR.
	BU İŞLEMLER TARİH İŞLEMLERİ İÇİN KULLANILACAK BİR MODÜL.
	MÜMKÜN OLDUĞU KADAR OOP TARZI BİR MODEL OLUŞTURULACAK.YANİ STRUCT ELEMANLARINI CLİENT KODDAN 
	GİZLEYECEĞİZ YADA CLİENT KOD BUNLARI KULLANMAYACAK. INCOMPLETE TYPE BURADA ÖNEMLİ.
	YAPININ ELEMANLARINI CLİENT KOD KULLANMAZSA, CLİENT KODLAR BUNU KULLANMADIĞI İÇİN KÜTÜPHANEDE
	DEĞİŞİKLİK YAPILINCA CLİENT KODLARDA BİR DEĞİŞİKLİK YAPMAYA GEREK KALMAYACAK.

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "date.h"
#include "nutility.h"



int main()
{
	Date today, future_date;
	
	set_date_today(&today);
	printf("bugun :");
	print_date(&today);

	for (int i = 0; i < 1'000'000'001; i *= 10)
	{
		printf("bugunden %d gun sonraki tarih", i);
		ndays_date(&future_date, &today, i);
	}
	
}