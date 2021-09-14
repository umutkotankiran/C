/*

	DOSYA İŞLEMLERİNE DEVAM

	EOF FLAG
	BİLDİĞİMİZ EOF DEĞİL BU.
	DOSYANIN SONUNA GELMİŞ FİLE POİNTER BİR OKUMA DAHA YAPMAYA ÇALIŞIRSA BAŞARISIZ OLUR.
	BU DURUMDA ARKA PLANDA LOW LEVELDA BİR BAYRAK SET EDİLECEK.BUNA EOF FLAG DENİYOR.
	EOF FLAG TRUE DURUMA GEÇER.FEOF TA BUNA BAKIYOR.

	OKUMA YAPAN FONKSİYONLAR ÖNCE EOF BAYRAĞI SET EDİLMİŞ Mİ DEĞİL Mİ BUNA BAKIYOR.
	ZATEN BİTSEL SEVİYEDE YAPILIYOR BU.SADECE BİR BİTE BAKIYOR.

	EĞER EOF BAYRAĞI SET EDİLMİŞSE VE TEKRAR OKUMA YAPMAK İSTENİYORSA, FİLE POİNTER TEKRAR
	SET EDİLMELİ.
	NOT: HEM OKUMA HEMDE YAZMA YAPMAK İÇİNDE FILE POINTER SET EDİLMELİYDİ !

	FEOF = EOF FLAG SET EDİLMİŞ Mİ(YANİ BAŞARISIZ OKUMA OLMUŞ MU) BUNA BAKIYOR.
	int feof(FILE *F);
	return değeri boolean int. set edilmişse 1, edilmemişse 0 döndürür.

	NOT: DOSYADA SON BYTE I OKUDUK, OKUNACAK BYTE KALMADI, FEOF TRUE DÖNDÜRMEZ,
	FALSE DÖNDÜRÜR.FEOF, FİLE POİNTER DOSYANIN SONUNDA MI KONTROLÜNÜ YAPMIYOR.
	EOF BAYRAĞININ SET EDİLİP EDİLMEDİĞİNE BAKIYOR.SET EDİLMESİ İÇİNDE BAŞARISIZ OKUMA GEREKİYOR.

	ÖR:

	int main()
{

	FILE* f = fopen("asal1000.dat", "rb");
	if (!f)
	{
		fprintf(stderr, "dosya acilamadi\n");
		return 1;
	}

	if (feof(f)) // set edilmemiş çıkacak bu burada
	{
		printf("eof bayragi set edilmis\n");
	}
	else
	{
		printf("eof bayragi set edilmemis\n");
	}

	fseek(f, 0L, SEEK_END); // dikkat

	if (feof(f)) // yine set edilmemiş çıkacak burada çünkü henüz başarısız okuma olmadı.
	{
		printf("eof bayragi set edilmis\n");
	}
	else
	{
		printf("eof bayragi set edilmemis\n");
	}

	//dikkat
	int c = fgetc(f);
	printf("c = %d\n", c);

	if (feof(f)) // yukarıda sonda iken okuma yapılmaya çalışılmış.okuma yapılamamış.EOF FLAG TRUE OLDU
	{
		printf("eof bayragi set edilmis\n"); //buraya girer
	}
	else
	{
		printf("eof bayragi set edilmemis\n");
	}

}

------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------


int main()
{
	// mülakat sorusu
	char str[100];// line tutabilecek kadar büyük dizi.
	FILE* f = fopen("temp.txt", "r");
	if (!f)
	{
		fprintf(stderr, "dosya acilamadi\n");
		return 1;
	}

	while (!feof(f))
	{
		fgets(str, 100, f); // son turda okumaya çalıştı hata verdi flag 1 oldu ama str bir önceki turdaki
		puts(str);			// değerinde duruyor.bunu tekrar yazdırdı. bir sonraki turda da feof 1 değerini verir
	}						// !feof 0 dır. while dan çıkar. 
							//Bunu test ettim şu durumda yaptı.
	fclose(f);				// dosyaya yazıları alt alta yazdıktan sonra enter ile newline verip save edince gördüm.
}							// öbür türlü vermedi bunu.


--------------------------------------------------------------
--------------------------------------------------------------

FERROR
Sistemden kaynaklanan hatalardan ötürü bur hatayı verebilir.

if(ferror(f))
{
	fprintf(stderr,"sistemsel hata olustu\n");
	return 1;
}

feof veya ferror dışında bir şey varsa format uyumsuzluğu vardır.

NOT : ERROR BAYRAĞI VEYA EOF BAYRAĞI SET EDİLMİŞSE, BUNU RESET ETMEK İÇİN FİLE POİNTER TEKRAR SET EDİLMELİ.
FSETPOS REWIND FSEEK HEPSİ OLUR.VEYA BAŞKA BİR FUNCTION DAHA VAR.

EOF BAYRAĞI ÖRNEĞİNDE DENENEBİLİR. BEN YAZMADIM.

-----------------------------------------------------------------------------------------------------

BU HATA BAYRAKLARINI FİLE POİNTER SET ETMEDEN DE SET EDEBİLİYORUZ.

CLEARERR
void clearerr(FILE *f);

F ILE ILGILI HANDLE BAYRAĞI TRUE OLMUŞSA BURADAN CLEARERR ILE TÜM BAYRAKLARI FALSE HALE GETIREBILIRIM.

=====================================================================================================
=====================================================================================================
=====================================================================================================
=====================================================================================================
=====================================================================================================
=====================================================================================================

STDIN STDOUT STDERR
-------------------


STDOUT
------
BUNLAR IDENTIFIER YANİ İSİM.
BİR C PROGRAMINDA BUNLARIN 3 Ü OTOMOTİK OLUŞTURULUYOR.
BUNLAR KEYWORD DEĞİL VE FİLE * OLARAK KULLANILACAKLAR.

ÖR: PARAMETRESİ FİLE * OLAN OKUMA FONKSİYONUNA STDİN İ ARGÜMAN OLARAK VEREBİLİR.
	PARAMETRESİ FİLE * OLAN YAZMA FONKSİYONUNA STDOUT U ARGÜMAN OLARAK VEREBİLİR.

ÖR: 	fprintf(stdout, "Bugun C kursunun 53. dersi\n"); bir file yerine stdout kullanıldı.
ÖR: 	printf("Bugun C kursunun 53. dersi\n"); Aynı ifade
		fputc('X', stdout); buda benzer işi yapıyor.

Ama fprintf i neden stdout ile çağıralım?

Çünkü bu bir çıkış kodu olsun. bu kod stdout veya isteğe göre bir file a yapabilsin diye yapılıyor.

void myprint(FILE *f,int n)
{
	for (int i = 0; i < n; i++)
	{
		fprintf(f,"%d ", i);
	}
	fprintf(f, "\n");
}

int main()
{

	FILE* f = fopen("temp.txt", "w");
	//kontrol

	myprint(f, 20);
	myprint(stdout, 20); //dosya yerine ekrana yazdırmak

	fclose(f);
}

Date i yazdırırken stdout kullanmak için printdate kodunu değiştirdi. ben yazmıyorum
çünkü aynı mantık.

--------------------------------------------------------------------

STDERR
------
BUDA DEFAULT OLARAK KONSOLA BAĞLI.
fprintf(stderr,"hata hata hata"); buda ekrana yazdırır.

NEDEN KULLANILIYOR?
STD OUTPUT U BAŞKA BİR DOSYAYA YÖNLENDİREBİLİRİZ.
DIRECTION DENİYOR BUNA. 
EĞER HATA MESAJLARINI STD OUTPUTA YAZDIRIRSAK HATA MESAJLARIDA DOSYAYA GİDECEK AMA BU MESAJLAR İNSANIN
GÖRMESİ İÇİN VAR.BURADA ŞU ÖNEMLİ. STANDART OUTPUT DOSYAYA YÖNLENDİRİLSE BİLE, STD ERROR HALEN EKRANA YAZACAK.
YÖNLENDİRME SONUCUNDA BİLE HATANIN EKRANA ÇIKTIĞINDAN EMİN OLACAĞIZ.
YANİ STD ÇIKIŞ AKIMI DOSYAYA YÖNLENDİRİLSEDE, STD HATA AKIMI EKRANA YAZIDRMAYA DEVAM EDİYOR.


ÖR:

int main()
{
	for (int i = 0; i < 100; ++i)
	{
		printf("%d ", i);
	}

	//BURASI ÇALIŞSAYDI EKSİK OLURDU
	// printf("bellek yetersiz devam etmek icin bir tusa basin\n"); //böyle olunca aşağıdaki kurallar geçerli
	// int c = getchar();

	// a.exe > a.txt
	//windows ta std ouptput yönlendire işleim
	//burada program çalışıyor ama bellek yetersiz ekranda çıkmıyor.
	// bunu dosyaya yazmış. dosyaya yazmak istemiyoruz.
	//düzeltilmiş hali aşağıdaki gibi olsaydı


	// BURASI OLMASI GEREKEN DURUM
	fprintf(stderr,"bellek yetersiz devam etmek icin bir tusa basin\n");
	int c = getchar(); // yazıyı okumak için beklettik.
	//build et
	//a.exe	> a.txt
	// bellek yetersizi ekrana yazdı. a.txt nin içerisine de sayıları yazdı.
}


--------------------------------------------------------------------------------

STDIN
-----

int main()
{
	int c;
	printf("bir karakter girin\n");
	//c = getchar();
	c = fgetc(stdin); //aynı şey oldu :D

	printf("%c karakterinin kodu %d\n", c, c);
}

-----------------------------------------------------------

ÖR:

int main()
{
	int x, y;
	printf("iki tamsayi girin\n");

	//scanf("%d%d", &x, &y);

	fscanf(stdin, "%d%d", &x, &y); // yukarıdaki ile aynı şey oldu artık.

	printf("x = %d\n", x);
	printf("x = %d\n", y);
}

-----------------------------------------------------------

BAŞKA KULLANIM TEMASI ISE 
BIR DIZIYI BOŞLUKLAR DAHIL TAŞIRMAMAK IÇIN YAZI ALMAK IÇIN KULLANILIR.

int main()
{
	char str[10];
	printf("bir yazi girin\n");

	//scanf("%s",str); // burada taşma riski var

	fgets(str, 10, stdin); // yukarıdaki ile aynı şey oldu artık ve taşma riski yok.
							// 9 karakter alır 10. karakter '\n' veya '\0' char.fgets böyle çalışıyordu.
	printf("%s", str);
}


HATIRLATMA!!!
NOT: ÇOK ÖNEMLİ !!!!!!!
	EĞER BUFFER SİZE DAN DAHA KÜÇÜK BİR KARAKTER OKURSA, DATAYI OKUR BUFFERA YAZAR VE SONUNA \n DEĞİL \0 KOYAR.
	KISACA, \n KARAKTERİNE KADAR OKURSA BUNUDA ALIR, AMA \n KARAKTERİ YOKSA VE BUFFER DOLDUYSA SONA \0 KOYAR.


-------------------------------------------------

ÖR:

int main()
{
	char name[10];
	printf("bir isim girin\n");

	fgets(name,10,stdin);		//burada şu var.fgets okurken fputs yazarken sonuna \n karakteri koyuyor.
								// yazı eşit çıkmıyor böyle kıyaslarsak.

	char* p;
	if(p= strchr(name, '\n')) //artık \n \0 hale geldi
		*p = '\0';


	if (!strcmp(name, "umut"))
	{
		printf("Hosgeldin Umut\n");
	}
	else
	{
		printf("Biz Umutu bekliyorduk sen kimsin\n");
	}

}

================================================================================
================================================================================
================================================================================
================================================================================
================================================================================




BUFFER
------

OKUMA VEYA YAZMA AMAÇLI KULLANILAN BİR BELLEK ALANI.
BUNUN KONTROLÜNÜ BİZDE ALABİLİYORUZ.

BUFFER BÜYÜKLÜĞÜ BUFSIZ İLE BELİRLENİYOR.
printf("%zu",BUFSIZ);

DEFAULT 512 BYTE
BU KADAR HIZLI OKUMA YAZMA YAPILMASININ SEBEBİDE ZATEN BU BUFFERIN OLMASI.

YAZMA IŞLEMI YAPILDIĞI SANILAN IŞLEMLER BUFFERA YAZILIYOR.FIILEN DOSYAYA YAZILDIĞI ZAMAN ISE
FLUSH EDILDIĞI ZAMAN.

NE ZAMAN FLUSH İŞLEMİ YAPILIYOR ?

SİSTEMDEN SİSTEME DEĞİŞİR AMA GENEL OLARAK AŞAĞIDAKİ GİBİDİR

1 - BUFFER DOLDUĞUNDA
2 - DOSYA KAPATILDIĞINDA
3 - PROGRAM NORMAL ŞEKİLDE SONLANDIĞINDA. "NORMAL TERMİNATE" YANİ EXİT ÇAĞRILDIĞINDA.(abortta yok - abnormal terminate)
4 - FFLUSH FONKSİYONU ÇAĞRILMASIYLA OLUR.

	int fflush(FILE *f);
	return değeri başarı int.
	
	cppreference : Returns zero on success. 
				   Otherwise EOF is returned and the error indicator of the file stream is set.

5 - STANDART OUTPUT PROGRAMIN BAŞINDA OTOMOTİK OLARAK STANDART İNPUTA BAĞLANIR (TIE)
	YANİ STD İNPUTTAN OKUMA YAPAN FONKSİYON ÇAĞRILDIĞINDA ÖNCE, FUNCTİON STD OUTPUTUN BUFFERINI
	FLUSH EDİYOR.BÖYLECE ARTIK PROMPT KULLANICI TARAFINDAN GÖRÜLEBİLİYOR.
	BUNU BİZİM YAPMAMIZA GEREK YOK ÇÜNKÜ BU OTOMOTİK OLARAK FLUSH EDİLİYOR.


ÇOK SIK SORULAN SORU?
PRİNTF İLE YAZDIRIYORUM AMA EKRANA HİÇBİR ŞEY ÇIKMIYOR.
NEDEN ? 

STANDART OUTPUTTA BİR STREAM VE AYNI BUFFERLAMA STD OUT İÇİNDE VAR.
BİRÇOK SİSTEMDE 

printf("merhaba\n");
sleep(1000000);
printf("ali\n");

MERHABA ÇIKMIYOR BİR SÜRE.AYARLAR İLE İLGİLİ DEĞİŞEBİLİR.ÇIKADABİLİR.

BUNUN ÇIKMAMASININ SEBEBİ STD OUTPUTUN BUFFERINA YAZDI.
BUFFER FLUSH EDİLMEDİKÇE EKRANDA GÖRMEYECEĞİZ.
BURADA BİRÇOK SİSTEMDE fflush(stdout) demek gerekiyor.

NOT !!!!!
FFLUSH(NULL) ÇAĞRI YAPILIRSA
AÇIK OLAN TÜM DOSYALARIN BUFFERLARI FLUSH EDİLİR.


----------------------------------------------------------------------------------
----------------------------------------------------------------------------------
----------------------------------------------------------------------------------

BUFFERI KENDİ KONTROLÜMÜZE ALABİLİRİZ
SETVBUF

int setvbuf(FILE *f, char *pbuf, int mode,size_t size);
pbuf = OKUMA YAZMA IŞLEMLERINDE KULLANILACAK DIZI ADRESI.
		NULL geçilirse kendisi yapıyor bunu.Okuma yazma yapmadan ilgili handle a ait buffer alanı ayarlıyor.

mode = Bunlar macro. 
_IOFBF = input output full buffering. Bufferlama tam olarak yapılıyor.Default zaten bu şekilde çalışıyor.
_IOLBF = input output line buffering. Line buffering yapıyor. yani \n gördüğü zaman flush eder.
_IONBF = input output no buffering. Hiçbir bufferlama yok.

size = BUFFER BOYUTU.
f = BU BUFFERLAMANIN GEÇERLI OLACAĞI HANDLE ISMI.

BUNUN GEÇERLİ OLMASI İÇİN HİÇ OKUMA YAZMA YAPMADAN SETVBUF ÇAĞRILMALI.


ÖR:

#define BUFFER_SIZE		1024

int main()
{
	char buffer[BUFFER_SIZE]
	FILE* f = fopen("deneme.txt", "w");
	//kontrol

	// setvbuf(f, buffer, _IOFBF,BUFFER_SIZE); // full buffer ve benim dizim kullanılacak

	// setvbuf(f, NULL, _IOFBF,BUFFER_SIZE); // Sadece buffer size editliyorum. onun dışında kendi bufferın kullanacak
											// buffer size 2 nin katları şeklinde isteniyor.800 versek 1024 kullanacaktı.

	setvbuf(f, NULL, _IONBF, BUFFER_SIZE); // no buffer için
}

--------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------

int main()
{
	char buffer[BUFFER_SIZE];
	setvbuf(stdout, NULL, _IONBF, BUFSIZ); // stdout için no buffering yapıldı.
}

--------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------

SETBUF

void setbuf(FILE *, char *pbuf);
sadece buffer verebiliyoruz.

pbuf NULL geçilirse, sistem kendi bufferını kullanıyor.

int main()
{
	char buffer[BUFFER_SIZE];
	setbuf(stdout, NULL); // bufferlama yok. IONBF e eşdeğer. cppreference den bakılabilir.
}

--------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------

TEMPFILE
--------

FILE * tmpfile(void);

WB+ MODDA GEÇİCİ DOSYA OLUŞTURUYOR.
FCLOSE ÇAĞRIULDIĞINDA DOSYA HEM KAPANIR HEMDE SİLİNİR.
AMAÇ BU DOSYALARI KULLANICIYA VERMEK DEĞİL. PROGRAM İŞİNİ YAPARKEN BUNLARI KULLANIYOR.
İŞİNİ BİTİRDİKTEN SONRADA SİLİYOR. 
BU DOSYAYA HEM OKUMA HEMDE YAZMA YAPILABİLİR. HEM READ HEMDE WRİTE
YANİ WB+ MODDA AÇIYOR DOSYAYI.


=======================================================================================================
=======================================================================================================
=======================================================================================================
=======================================================================================================
=======================================================================================================

		VARIADIC FUNCTIONS
		------------------

int foo(int a, ...);
... = ellipsis

BİR FONKSİYONA İSTENİLDİĞİ KADAR ARGÜMAN GEÇİLEBİLMESİNİ SAĞLIYOR.
C++ TA ÇOK DAHA GELİŞMİŞ.

VARİADİC PARAMETREDEN SONRA BİR PARAMETRE OLMAYACAK
VE BAŞTA DA EN AZ 1 TANE PARAMETRE OLACAK.

int foo(int a, ...);
foo(10);
foo(10,1);
foo(10,1,2);
foo(10,1,2,3);  hepsi geçerli

C NİN BİR HEADER FİLE INI İNCLUDE ETMEK GEREKİYOR.
STDARG.H
BURADAKİ MACROLAR KULLANILACAK.

C DE VARIADIC FUNCTIONLAR BIRAZ EKSİK
BİRŞEKİLDE KAÇ ARGÜMAN GÖNDERDİĞİMİZİ GÖNDERMEMİZ GEREKİYOR.


---------------------------------------------------------------

ÖR:

void func(int x,int y, ...)
{
	va_list list; //va_list bir tür. bu türden bir değişken tanımladık.
	va_start(list, y); // va_list türünden değişken ve variadicten önceki sonr parametrenin adını yaz.

	while ()
	{
		int a = va_arg(list, int); // liste tekrar geçiliyor ve gönderilen argümanın türü.
									// burada her seferinde kendisi bir sonraki argümana erişiyor.
									// tür kontrolü yok. int yerine double değer gönderilseydi UB olacaktı
									// conversion specifierlar ile bu türü anlayacağız.
	}

	va_end(list); // bu çok önemli değil ama yapılsa iyi olur.YAPTIĞI PEK BİR İŞ YOK.
}

--------------------------------------------------------------------------------------------------

ÖR:

int sum(int n, ...)
{
	va_list list;
	va_start(list, n);
	int sum = 0;

	while (n--)
	{
		sum += va_arg(list, int);
	}
	return sum;
}

int main()
{
	int x = 10, y = 20, z = 45;
	int result = sum(3, x, y, z);
	printf("%d\n", result);
}

--------------------------------------------------------------------------------------------------

ÖR:

#define BUFFER_SIZE		1024

void nprintf(const char* pfm, ...)
{
	va_list list; // list sadece verdiğim isim.
	va_start(list, pfm);

	while (*pfm != '\0')
	{
		int c = toupper(*pfm);
		if (c == 'I')
			printf("%d\n", va_arg(list, int));       // print kullandık kkolay olsun diye. 
		else if (c == 'D')								// kendi print func. yazabilirdik.
			printf("%lf\n", va_arg(list, double));
		else if (c == 'L')
			printf("%ld\n", va_arg(list, long int));
		else if (c == 'S')
			printf("%s\n", va_arg(list, char *));
		pfm++;
	}

	va_end(list);
}

// int ==> i I
// double ==> d D
// long ==> l L
// char * ==> s S
int main()
{
	int x = 10;
	double dval = 12.32;
	long lval = 123L;
	char* ptr = "maho";

	nprintf("idls", x, dval, lval, ptr);
}


ÖNEMLİ !!!!!!!
İNT TÜRÜNDEN DAHA KÜÇÜK TÜRLERDEN ARGÜMANLAR İNT TÜRÜNE DÖNÜŞTÜRÜLEREK GÖNDERİLİRLER.
FLOAT ARGÜMANDA DOUBLE A DÖNÜŞTÜRÜLEREK GÖNDERİLİR.KURAL BU 

-----------------------------------------------------------------------------------------------

GETMAX ÖRNEĞİNİ YAPTI BEN YAPMAYACAĞIM ONU. 1. TEKNİK İLE YAPTI.
MAX = INT_MIN MACROSU İLE VERDİ İLK DEĞERİ. DAHA FARKLIDA YAPILABİLİR.

-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------


ÖR: SON ARGÜMANA ÖZEL BİR DEĞERDE GEÇİLEBİLİR.

void myprint(const char* p, ...)
{
	va_list list;
	va_start(list, p);

	if(!p)
		return;

	const char* ptr;

	while ((ptr = va_arg(list, const char*)) != NULL)
	{
		printf("%s\n", ptr);
	}

	va_end(list);
}

int main()
{
	myprint("deniz", "tayfun", "hakan", "elif", NULL);
	myprint("deniz", "tayfun", "hakan", "elif", "necati","umut", NULL);
}


--------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------
















*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "nutility.h"
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>

char* concat(const char* p, ...)
{
	if (p == NULL)
		return NULL;

	// bu kısım dinamik bellek aralığının ne kadar olacağını belirlemek için.Birazcık uzun sürdü.
	va_list list;
	va_start(list, p);
	size_t total_len = strlen(p); // ilk elemanda bir string literal.zorunlu olduğumuz için en az bir tane yazılıyor.
	const char* ptr;

	while ((ptr = va_arg(list, const char*)) != NULL)
	{
		total_len += strlen(ptr);
	}

	char* pd = (char*)malloc(total_len + 1); // sizeof(char) a gerek yok çünkü zaten char 1 byte :D:D 
												// +1 de '\0' için
	if (!pd)
	{
		fprintf(stderr, "bellek hatasi\n");
		return NULL;
	}

	va_end(list);

	// tekrar aynı liste başlatılacak.bellek bloğu büyüklüğü belirlendi.
	va_start(list, p);
	strcpy(pd, p);

	while ((ptr = va_arg(list, const char*)) != NULL)
	{
		strcat(pd, ptr);
	}

	va_end(list);
	return pd;

}



int main()
{
	// mülakat sorusu
	char str[100];// line tutabilecek kadar büyük dizi.
	FILE* f = fopen("temp.txt", "r");
	if (!f)
	{
		fprintf(stderr, "dosya acilamadi\n");
		return 1;
	}

	while (!feof(f))
	{
		fgets(str, 100, f); // son turda okumaya çalıştı hata verdi flag 1 oldu ama str bir önceki turdaki
		puts(str);		// değerinde duruyor.bunu tekrar yazdırdı. bir sonraki turda da feof 1 değerini verir
	}						// !feof 0 dır. while dan çıkar.
		

	fclose(f);
}