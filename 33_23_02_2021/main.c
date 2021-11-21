#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "nutility.h"

/*

	string literalleri derleyicilerin oluşturduğu char ve static ömürlü dizilerdir.
	salt okuma amaçlı kullanılmalıdır.

	1 - bir string literalini asla değiştirme. C ve C++ ta farklılık var.
	C++ ta bu bir const char dizi. C de ise char dizi ama değiştirilemiyor :)
	C de de string literalini const char ile tanımlamak mantıklı.
	char * p = "umut" ; C++ ta sentaks hatası C de geçerli ama değiştirilemiyor.Değiştirmek UB dir.
	C de de const char *p = "umut" ; mantıklı tanım

	2 - static ömürlü dizilerdir.programın başından sonuna hayatta kalır.

	3 - Özdeş string literallerinin memorydeki yeri Unspecified behavior.
	char *p1 = "ali"
	char *p2 = "ali"
	p1 ve p2 nin adresleri derleyiciye bağlı.
	Bazı derleyicilerin switchleri ile bu aynı olarak ayarlanabiliyor.
	
	----------------------------------
	----------------------------------

	"" -> string literalleri aslında karakter sabitleriyle değerini almış dizilerdir. 
	"burak" -> b nin kod no su, u nun kod nosu .... şeklinde gidiyor.

	mesela

	"\x42URS\x41" -> "BURSA" demektir. x42 B nin kodudur.
	burada U hexadecimal bir char eğil.
	puts("\x42ebe") burada hexadecimal digit gördüğü sürece dahil ediyor ve hata alınır burada.
	too big for character hatası alınır.
	puts("\101") -> burası octal sayı sisteminde yazılmış ve 3 karakter limiti var.hata oluşmuyor.
	puts("\10132") -> mesela 32 yi dahil etmedi çünkü 3 karakter limiti var.

	puts("\10132\10243") -> A32B43 yazar.


	" karakteri.String lit. sınırlandırıcı olarak kullanılır.Delimiter olarak kullanılır.
	\" şeklinde kullanırsak ekrana " yazdırabilir.
	puts("\"ayhan\""); ->  "ayhan" yazdırır.
	puts("\\ayhan\\"); ->  \ayhan\ yazdırır.

	path bilgisi girerkende çift \ kullanılmalı.
	"c:\\umut\\umut.txt"

	----------------------------------------
	----------------------------------------

	1 - char str[] = "burak";
	2 - char *p = "adnan";

	1. olan diziye değer atama sentaksı.her elemana değer atıyor.
	dizi boyutu burada 6, string boyutu ise 5 ve elemanlar değiştirilebilir.

	2. burada ise "adnan" string literalinin adresini p pointerına atıyoruz.
	burada memory deki static ve readonly "adnan" yazısının characterlerini değiştirmek
	UB oluşturur.Hocada hata vermedi ama bende write violation hatası geldi.

	yani p[0] = 'Z'; Bir UB dir.
	bu durumda char *p = "adnan"; şeklinde tanımlamak çok mantıklı dğeil.
	const char *p = "adnan"; şeklinde tanımlamak daha mantıklı.
	bu durumda direkt olarak sentaks hatası verir.

	==============================================
	==============================================
	==============================================

	POINTER ARRAYS / Pointer Dizileri

	sizeof ile strlen karıştırılıyor.
	sizeof bir compile time operatörü.
	strlen ise bir function.yazı uzunluğu verir.

	dizinin boyutu x tipi, ör: int[5] -> 4*5 = 20 byte yer kaplar.
	ikisininde türü size_t

	char str[] = "necati";
	printf("%zu",sizeof(str)); -> 7 verir. sondaki null char unutma.dizilerde tüm dizi boyutunu alıyor.
	printf("%zu",sizeof(*str)); -> 1 verir. *str nin türü char. sizeof char -> 1 dir.
	printf("%zu",strlen(str)); -> 6 verir. yazı uzunluğu.

	void foo(char *p)
	{
		printf("%zu",sizeof(p));
	}

	foo(str)  -> bu int * (pointer sizeof u yani)boyutunu verir. 4 byte. bazı derleyicilerde 8 byte.

	char * str[] = "necati","veli";
	char **p = str;

	printf("%zu\n",sizeof ++p); //unevaluated context.++ için kod üretilmez.
	printf("%zu\n",strlen(p));

	=====================================================================
	=====================================================================

	"bugun c dersi var"
	"devam eden C dersi"  bu şekilde alt alta yazılabilir.2. yöntem de var


	"bugun c dersi var\
	devam eden C dersi"	  bu da aynı şekilde.
		
	burada boşluklar var ama kodun layoutunu bozuyor.boşluklarda hesaba katıldığı için 
	sıkıntı çıkabiliyor

	char *p = "murat"
			"hasan"
			"veli"
			"ali";


	derleyici bunu "murathasanveliali" şeklinde birleştiriliyor.

	--------------------------------------------

	sıralı bir şekilde alt alta yazmak için 

		printf("1 kayit ekle\n"
		"2 kayit sil\n"
		"3 kayit guncelle\n"
		"3 cik\n");

	-------------------------------------------------------
	-------------------------------------------------------

	"" buna null string literal deniyor.
	dizinin uzunuluğu 1, yazının uzunluğu 0 .
	sadece null char dan oluşan bir dizi.
		
	printf("%zu\n", sizeof ""); -> 1  -> char 1 byte olduğu için sizeof kullanıyorum
	normalde asize macrosu mantıklı. mesela 5 elemanlı int türden bir dizi olsaydı 
	5 * int veri tiyi size olacaktı
	bu da 20 byte yapar.Ama 1 byte iken sorun yok.

	printf("%zu\n", strlen("")); -> 0. yazı uzunluğu bu. 0 zaten.


	parametresi char * tipten olan bir fonksiyona string literali gönderilmemeli.

	char *p ="ali";
	strcat(p,"veli"); -> burada char * ilk parametre ve sonuna veli eklenecek.
	bizim gönderdiğimiz ise string literali yani değiştirilemez bir nesne.
	biz ise strcat ile bu string literalini değiştirmeye çalışıyoruz. UB var.
	ikinci parametre zaten const char *, buraya string literali gönderilebilir.

	ama char str[100] = "ali"; desydik ve bunu gönderseydik. sıkıntı yoktu.

	========================================================
	========================================================
	========================================================


	POINTER ARRAYS / GÖSTERİCİ DİZİLERİ
	-----------------------------------

	int a[10]; a, elemanları int türden 10 elemanlı bir dizi.
	int *a[10] ; a, elemanları int *(pointer) türden 10 elemanlı bir dizi.

	printf("%zu\n", asize(a)); // dizi boyutu bilgisi -> 10
	printf("%zu\n", sizeof a); // dizi nin memorydeki toplam size değeri -> 40. 

	NOT
	tüm ptr türleri eşit yer kaplyor.
	int *
	double *
	char * ...

	--------------------

	ör:

	int *p[10];
	int x = 10;
	int y = 20;

	p[0] = &x; elemanların hepsi bir ptr, yani adres ile eşitlenebilir.
	p[1] = &y;

	*p[0] = 333;   içerik op 2. sırada. index ise 1. bu dizinin ilk elemanını dereference eder
	ilk eleman &x idi. bunu (dereference)*&x yaparsak x i elde ederiz. x = 333 yapıldı.
	printf("x = %d",x);

	*p[1] = 465;
	printf("y = %d",y);

	==========================================================
	==========================================================


	Bir soru soruldu cevabı aşağıda

	scanf fonksiyonu çalıştıktan sonra std inputun bufferında \n karakterini bırakır.
	daha sonrasında sgets fonksiyonu ile veri almaya çalışınca \n a denk geldiği için 
	hiçbir yazıyı almaz. clear input buffer function çağrılarak bu ortadan kaldırılır.

	Bu ileride görülecek.


	int x = 10;
	int y = 20;
	int z = 30;

	int *p[] = {&x,&y,&z};

	for (size_t i = 0; i < asize(p); i++)
	{
		++* p[i];
	}
	printf("x = %d\n",x); 11
	printf("y = %d\n",y); 21
	printf("z = %d\n",z); 31	hepsinin değerini 1 artırdık


	-----------------------------

	int *p[] = {&x,&y,&z};

	printf("%zu\n",sizeof(p)); -> 12 byte. tüm array.int * lardan oluşan bir array her biri 4 byte
	printf("%zu\n",sizeof(*p)); -> 4 byte. ilk eleman 

	----------------------------

	int *p[3];
	int a[] = {20,40,60};

	p[1] = a; 

	p[1][2] -> 60 tır. bunu *p ile de açabiliriz. (*(p + 1))[2] şekilde yazılabilir.

	-----------------------------

	int a[3] = { 10,11,12 };
	int b[3] = { 20,21,22 };
	int c[3] = { 30,31,32 };

	int* p[] = { a,b,c };
	++p[1];		//bu b nin 2. elemanını göstermesini sağladık.p[1] artık b nin 2. elemanından başlıyor.
	++* p[1];	//burada da 21 +1 yapıldı.

	// b yukarıda duruyor yazdırırsak 20 22 22 yazar
	print_array(b, 3);


	=================================================

	char *p[5] = {"Ali","Veli","Hasan","Huseyin","Mert"};
	*p[1] = 'X'; Burası UB çünkü string literali değiştirilmeye çalışılmış.

	buraya const char *p[5] şeklinde tanımlansaydı artık sentaks hatası görülürdü.
	const ile tanımlamak daha mantıklı.

	ÇOK ÖNEMLİ !!!!!!!
	----------
	Burayı az önce telegramdan hocaya sordum.
	Burayı kim okuyorsa dikkatli okusun. Çok aşırı önemli.

	char *p[5] = {"Ali","Veli","Hasan","Huseyin","Mert"};
	*p[1] = 'X';  çünkü zaten string literalleri değişemez.
	 ama
	 p[1] = "Zubeyde"; burada hiçbir sorun yok.UB değil.
	 dizinin bu öğesinde başka bir str. literali olacak.

	Eğer!!
	char * const p[5] = {"Ali","Veli","Hasan","Huseyin","Mert"}; olsaydı(elemanları const bir dizi olsaydı)
	p[1] = "Zubeyde"; Burası Sentaks hatası olacaktı. çünkü "Zubeyde" aslında bir adres
	char * const tanımında ise adresler değişemiyor.

	Eğer !!
	const char * p[5] = {"Ali","Veli","Hasan","Huseyin","Mert"}; şeklinde tanımlansaydı.
	Burada ise dizi adreslerindeki elemanlar/değerler değiştirilemiyor. Zaten değişmemesi lazım.
	String literalleri zaten değişmiyor.
	*p[1] = 'X'; burası Sentaks hatası olur. Eğer const yapılmazsa zaten UB.

	KISACA
	* ın sağ tarafında olan const 
	adreslerin değişmemesi için
	* ın sol tarafında olan const ise değerlerin değişmemesi için.

	========================================================================

	const char const pdays[] = {
		"Pazartesi",
		"Sali",
		"Carsamba",
		"Persembe",
		"Cuma",
		"Cumartesi",
		"Pazar"	,
	}
bu tip dizilere lookup table deniyor.


	int n;
	printf("haftanın kacinci gunu :");
	(void)scanf("%d", &n);

	printf("%s", pdays[n -1]);

	haftanın geçerli bir günü olup olmadığı gösterek kodd yazdı basit bir kod.yazmıyorum.

	================================================================

	çok büyük bir array yazdı 333 boyutlu.Önceden hazırlanmış.
	Onunla ilgili kodlar yazacak.

	const char const* pdays[] = {
	"Pazartesi",
	"Sali",
	"Carsamba",
	"Persembe",
	"Cuma",
	"Cumartesi",
	"Pazar"
	};

	for (size_t i = 0; i < asize(pdays);i++)
	{
		printf("%-16s%zu\n", pdays[i],strlen(pdays[i]));
	}

	//sadece ilk harflerini yazdıran kod
	for (size_t i = 0; i < asize(pdays); i++)
	{
		printf("%c\n",*pdays[i]);
	}

	//son karakterleri yazdır.
	for (size_t i = 0; i < asize(pdays); i++)
	{
		printf("%c\n", pdays[i][strlen(pdays[i]) - 1]);
	}

	int ch;
	puts("bir karakter girin");
	ch = getchar();
	//içinde belli bir char olan tüm isimleri yazdıracak
	for (size_t i = 0; i < asize(pdays); i++)
	{
		if (strchr(pdays[i],ch))
			printf("%s\n", pdays[i]);
	}


	// içinde hangi karakterden ne kadar olduğunu bulacak
	for (int c = 'a'; c < 'z'; c++)
	{
		int count = 0;
		printf("\nicinde %c char olanlar\n", c);
		for (size_t i = 0; i < asize(pdays); i++)
		{
			if (strchr(pdays[i], c))
			{	
				count++;
				printf("%s ", pdays[i]);
			}
			
		}
		printf("\n%d isimde %c karakteri var\n", count, c);
		
	}

	------------------

	char entry[40];
	printf("bir yazi giriniz\n");
	(void)scanf("%s", entry);

	//dizi içinde yazı içeren kelimeler
	for (size_t i = 0; i < asize(pdays); i++)
	{
		if (strstr(pdays[i], entry))
		{
			printf("%s\n", pdays[i]);
		}
	}

	------------------------

	char entry[40];

	printf("bir yazi giriniz\n");
	(void)scanf("%s", entry);
	//karkaterlerden herhangibirini içeren kelimeler
	for (size_t i = 0; i < asize(pdays); i++)
	{
		if (strpbrk(pdays[i], entry))
		{
			printf("%s\n", pdays[i]);
		}
	}

	------------------------------------------------

	const char const* pdays[] = {
	"Pazartesi",
	"Sali",
	"Carsamba",
	"Persembe",
	"Cuma",
	"Cumartesi",
	"Pazar",
	"Ali","veli","ugur","zubeyde","berkan","hakan","Can","baran"
	};

	//diziyi alfabetik sıraya göre yazmak.//küçükten büyüğe
	for (size_t i = 0; i < asize(pdays); i++)
	{
		for (size_t j = 0; j < asize(pdays) - i - 1; j++)
		{
			if (strcmp(pdays[j], pdays[j + 1]) > 0)
			{
				const char* temp = pdays[j];
				pdays[j] = pdays[j + 1];
				pdays[j + 1] = temp;
			}
		}
	}



	// yazı uzunluklarına göre sırala.
	//Aynı zamanda alfabetik sıralama olacak aynı uzunlukta olanlar arasında
	for (size_t i = 0; i < asize(pdays); i++)
	{
		for (size_t j = 0; j < asize(pdays) - i - 1; j++)
		{
			size_t len1 = strlen(pdays[j]);
			size_t len2 = strlen(pdays[j+1]);

			if (len1 > len2 || len1 == len2 &&strcmp(pdays[j], pdays[j+1]) > 0)
			{
				const char* temp = pdays[j];
				pdays[j] = pdays[j + 1];
				pdays[j + 1] = temp;
			}
		}
	}


	for (size_t i = 0; i < asize(pdays); i++)
	{
		printf("%s ", pdays[i]);
	}

	----------------------------------------------------------------
	----------------------------------------------------------------
	----------------------------------------------------------------

	İdiyomlar

	// 1
	const char const* pdays[100] = {
	"Pazartesi",
	"Sali",
	"Carsamba",
	"Persembe",
	"Cuma",
	"Cumartesi",
	"Pazar",
	"Ali","veli","ugur","zubeyde","berkan","hakan","Can","baran"
	};

	//100 elemanlı dizide ilk değer verilmeyen öğeler null pointer olur.
	// ptr dizisi değilde tamsayı dizisi olsaydı 0 olurdu.

	// ---------------------------

	// 2
	//designated initializator
	char* p[100] = { [5] = "Ali",[12] = "Mehmet" };
	// ilk değer verilmeyenler null ptr olur.


	// 3
	static char* p[5];
	// bütün elemanlar Null Pointer.

	// 4
	// en sona NULL ptr koymak.null ptr olmadığı sürece dönen dizi.
	const char * pdays[100] = {
	"Pazartesi",
	"Sali",
	"Carsamba",
	"Persembe",
	"Cuma",
	"Cumartesi",
	"Pazar",
	"Ali","veli","ugur","zubeyde","berkan","hakan","Can","baran", NULL
	};

	int i = 0;
	while (p[i])
		printf("%s ",p[i++]);

	// 5
	// pointer dizilerinde yapılan çok kritik hata
	// tanımda virgül işaretini koymamak.
	// uğur ile zübeyde birleştirilip tek yazı gibi görünür.
	// bu da en son null ptr yazar.buda UB dir.NULL ptr dereference etmek UB dir çünkü.

	const char* pdays[100] = {
	"Pazartesi",
	"Sali",
	"Carsamba",
	"Persembe",
	"Cuma",
	"Cumartesi",
	"Pazar",
	"Ali","veli","ugur" "zubeyde","berkan","hakan","Can","baran"
	};


	// 6
	// ilk gün ün indexi 1 olması için, "" yazıldı.

	const char* pdays[100] = {
	"",
	"Pazartesi",
	"Sali",
	"Carsamba",
	"Persembe",
	"Cuma",
	"Cumartesi",
	"Pazar"
	};

	// 7 bir string literalini dğeiştirmeye çalışınca UB olan bir örnek.


*/

int main()
{
	// Ödev hocanın verdiği dizinin elemanlarının gösteridiği isimlerden içerisinde
	// her harfi unique olanları yazdırınız.
		
}
