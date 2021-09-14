#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "nutility.h"
#include <string.h>
#include <ctype.h>

#define		SIZE	100


int my_strcmp(const char* p1, const char* p2)
{
	while (*p1 == *p2) // iki değerde birbirine eşitse
	{
		if (p1 == '\0') // bu değerlerden biri null chr ise diğeride null chr dir.
			return 0; // return 0 strcmp nin kullanım şekli.eşitse 0.
		p1++;
		p2++;
	}
	
	return *p1 - *p2; // diyelimki eşit değiller. p1 büyükse pozitif değer. diğeri büyükse
}						// negatif değer. biri bitmişse bile sondaki '\0'ın değeri 0 dır.
						// ve işlemler değer - 0 veya 0 - değer şeklinde olabilir.çok mantıklı.


int my_stricmp(const char* p1, const char* p2)
{
	while (toupper(*p1) == toupper(*p2)) // iki değerde birbirine eşitse
	{
		if (p1 == '\0') // bu değerlerden biri null chr ise diğeride null chr dir.
			return 0; // return 0 strcmp nin kullanım şekli.eşitse 0.
		p1++;
		p2++;
	}

	return toupper(*p1) - toupper(*p2); // diyelimki eşit değiller. 
}					  // p1 büyükse pozitif değer. diğeri büyükse.



int is_at_end(const char* p1, const char* p2) // p1 adresinin sonunda p2 var mı?
{
	size_t p1_len = strlen(p1);
	size_t p2_len = strlen(p2);
	
	if (p2_len > p1_len)
		return 0;

	return !strcmp(p1 + p1_len - p2_len, p2);
}

char* my_strpbrk(const char* p1, const char* p2)
{
	while (*p1)
	{
		if (strchr(p2, *p1)) // ilk eşleşeni return eder.p1 ile p2 nin sırasına dikkat.
			return (char*)p1; 
		p1++;
	}

	return NULL;
}


int main()
{

	/*

	strcmp fonksiyonundan devam
	>0 ise birinci yazı büyük
	<0 ise ikinci yazı büyük
	== 0 ise ikiside eşit

	if(strcmp(s1,s2) == 0) girer ise eşit
	if(!strcmp(s1,s2)) ise yine eşit

	if(strcmp(s1,s2)) ise farklı
	if(strcmp(s1,s2) != 0) ise yine farklı

	if(strcmp(s1,s2) > 0) ise s1 büyük
	if(strcmp(s1,s2) < 0) ise s2 büyük

	yüzü büyüklük küçüklük kavramı
	sadece yazı değil veriyapı karşılaştırmasında da lexicograpohical
	algoritma kullanılıyor.

	1 3 7 40  bu dizi daha büyük
	1 3 7

	1 5 7 9
	1 6		Bu daha büyük


	1 200 300 400 600 700
	2	bu daha büyük.

	ali ata bak
	veli		bu daha büyük.Asci deki yerine göre

	BU BİR YAZIDIR
	ali			bu daha büyük.Ascideki karşılığı daha büyük.

	!ali < ?ali
	================================================
	================================================

	char s1[SIZE] = {0};
	char s2[SIZE] = {0};

	printf("iki adet isim girin : ");
	(void)scanf("%s%s", s1, s2);

	int cmp_result = strcmp(s1, s2);

	if (cmp_result > 0) // herhangibir pozitif değer 1 değil
		printf("%s > %s", s1, s2);
	else if (cmp_result < 0) // herhangibir negatif değer -1 değil
		printf("%s < %s", s1, s2);
	else
		printf("%s = %s", s1, s2);

	Kendimiz strcmp nin kodunu yazalım.
	-------------------------------------
	-------------------------------------

	int my_strcmp(const char* p1, const char* p2)
{
	while (*p1 == *p2) // iki değerde birbirine eşitse
	{
		if (p1 == '\0') // bu değerlerden biri null chr ise diğeride null chr dir.
			return 0; // return 0 strcmp nin kullanım şekli.eşitse 0.
		p1++;
		p2++;
	}

	return *p1 - *p2; // diyelimki eşit değiller. p1 büyükse pozitif değer. diğeri büyükse
}						// negatif değer. biri bitmişse bile sondaki '\0'ın değeri 0 dır.
						// ve işlemler değer - 0 veya 0 - değer şeklinde olabilir.çok mantıklı.

------------------------------------------------------------------------
------------------------------------------------------------------------

birde stricmp fonksiyonu var. buradaki i, insensitive anlamında
büyük küçük harf hassasiyeti yok. Kodunu yazalım.


int my_stricmp(const char* p1, const char* p2)
{
	while (toupper(*p1) == toupper(*p2)) // iki değerde birbirine eşitse
	{
		if (p1 == '\0') // bu değerlerden biri null chr ise diğeride null chr dir.
			return 0; // return 0 strcmp nin kullanım şekli.eşitse 0.
		p1++;
		p2++;
	}

	return toupper(*p1) - toupper(*p2); // diyelimki eşit değiller.
}					  // p1 büyükse pozitif değer. diğeri büyükse.


test

	char s1[SIZE] = {0};
	char s2[SIZE] = {0};

	printf("iki adet isim girin : ");
	(void)scanf("%s%s", s1, s2);

	int cmp_result = my_stricmp(s1, s2);

	if (cmp_result > 0) // herhangibir pozitif değer 1 değil
		printf("%s > %s", s1, s2);
	else if (cmp_result < 0) // herhangibir negatif değer -1 değil
		printf("%s < %s", s1, s2);
	else
		printf("%s = %s", s1, s2);

	-------------------------------------------------------------------
	-------------------------------------------------------------------

	int is_at_end(const char* p1, const char* p2) // p1 adresinin sonunda p2 var mı?
	{
		size_t p1_len = strlen(p1);
		size_t p2_len = strlen(p2);

		if (p2_len > p1_len)
			return 0;

		return !strcmp(p1 + p1_len - p2_len, p2);
	}



	char s1[SIZE] = {0};
	char s2[SIZE] = {0};

	printf("birinciyi girin :");
	sgets(s1);
	printf("ikinci girin :");
	sgets(s2);

	if (is_at_end(s1, s2))
		printf("evet var\n");
	else
		printf("hayir yok\n");


	----------------------------------------------------------
	----------------------------------------------------------

	genelde insanlar s1 ile s2 eşit mi diye bakmak için
	if(s1 == s2) diyor
	burası tamamen hatalı. burada 2 adres karşılaştırılıyor aslında
	memory de farklı yerde farklı iki dizi hiçbir zaman eşit olmuyor.
	herzaman false
	Kullanılması gereken strcmp fonksiyonudur.

	=========================================================================
	=========================================================================
	=========================================================================

	strpbrk --> Bir yazı içersinde "klm" harflerinden birinin ilk
	geçtiği yer hangisi ise onu buluyor.
	strstr den farkı, strstr string içinde
	bir string arıyor. strpbrk ise string içerisinde bir ya da bir kaç
	karakterden birini arıyor.

	char *strpbrk(const char *p1, const char *p2)


	----------------------
	----------------------
	char s1[SIZE] = {0};
	char s2[SIZE] = {0};
	char* p;
	printf("birinciyi girin :");
	sgets(s1);
	printf("ikinci girin :");
	sgets(s2);

	printf("%s yazisinda %s karakterlerinden biri araniyor\n", s1, s2);

	p = strpbrk(s1, s2);
	if (p == NULL)
		printf("%s yazisinda %s karanterlerinden biri bulunamadi\n",s1,s2);
	else
	{
		printf("bulundu. index = %d\n", p - s1);
		puts(p);
	}

	------------------------------------------------------------------
	------------------------------------------------------------------

	kodunu yazalım

	char* my_strpbrk(const char* p1, const char* p2)
	{
		while (*p1)
		{
			if (strchr(p2, *p1)) // ilk eşleşeni return eder.p1 ile p2 nin sırasına dikkat.
				return (char*)p1;
			p1++;
		}

		return NULL;
	}

	---------------------
	---------------------

	char s1[SIZE] = {0};
	char s2[SIZE] = {0};
	char* p;
	printf("birinciyi girin :");
	sgets(s1);
	printf("ikinci girin :");
	sgets(s2);

	printf("%s yazisinda %s karakterlerinden biri araniyor\n", s1, s2);

	p = my_strpbrk(s1, s2);
	if (p == NULL)
		printf("%s yazisinda %s karanterlerinden biri bulunamadi\n",s1,s2);
	else
	{
		printf("bulundu. index = %d\n", p - s1);
		puts(p);
	}


	ÖDEV
	char *strprepen(char *pdest,const char * psource)
	pdest in başına psource u ekliyor. bunu yaz. umut kotankiran -> kotankiran umut yazacak

	========================================================================
	========================================================================
	========================================================================

	Birde fonksiyonların n li hali var.fonksiyon bildiriminde fazladan n parametresi var.

	strcpy için strncpy  -> source adresteki yazının ilk n karakterini dest e kopyalar.
	strcat için strncat  -> source adresteki yazının ilk n karakterini dest in sonuna ekler
	strcmp için strncmp  -> source adresteki yazının ilk n karakterini dest ile kıyaslar.

	NOT:
	strncpy nin yanlış kullanımı çok yaygın.

	---------------------------------
	---------------------------------

	char source[SIZE]; // 0 a eşitleseydim olmazdı.Ama dikkat edilecek yer bu değil.
	char dest[SIZE];	// kopyalanan yazının sonundaki \0 da kopyalanmalı.Yoksa UB olur.
	int n;				// odak noktası bu.

	printf("isim girin :");
	sgets(source);

	printf("birde tamsayi giriniz \n");
	(void)scanf("%d", &n);

	//source adresteki n karakter dest e kopyalanacak
	//DİKKAT strncpy ÇOK TEHLİKELİ BİR FUNC.

	//strncpy(dest, source, n); //UB
	//printf("%s\n", dest); //UB yi görürüz

	//sebebi. Eğer 3. parametreye geçilen tamsayı kaynak yazının uzunluğundan
	//küçük veya eşit ise null char kopyalanmıyor. ya manuel kopyalanmalı yada
	// n karakteri doğru girilmeli.
	//ör: strncpy(dest, source, n);
	// source = "umut" n = 3		UB.
	// source = "umut" n = 4		UB.
	// source = "umut" n = 5		Defined Behavior.Sorun yok.

	// eğer n sayısı kopyalanacak yazıdan kısa veya eşitse, dest[n] = '\0' yazılır.
	// yani manuel olarak yapılır bu işlem.
	// idiyom olarakta aşağıdaki var
	// strncpy(dest, source, n)[n] = '\0';

	//--------------------------------
	//--------------------------------

	char source[SIZE] = "kayhan";
	char s[] = "gurcan";
	strncpy(source, s, 3); // gurcan ın gur ünü alır kayhanın ilk üçüne yazdırır. sonuc gurhan
	printf("%s", source); // kayhanın sonda '\0' olduğu için ub de oluşmaz artık.source boş olsaydı
							// o zaman olurdu.


	ÖDEV
	BUNUN KODUNU YAZ.

	=======================================================================
	=======================================================================
	=======================================================================

	strncat
	bir yazının sonuna istenilen uzunlukta başka bir yazıyı ekler.
	Çok güzel mantıklı bir func.


	char s1[SIZE] = "mustafa";
	char s2[SIZE] = "1234567890";
	strncat(s1, s2 , 5); // strncat(s1, s2 +2, 5); yazsaydım. 4 ten sonrasını birleştirecekti.
	printf("%s", s1);

	======================================================================
	======================================================================
	======================================================================

	strncmp  ->   iki adet yazının n kadar karakterini karşılaştırıyor.


	char s1[SIZE] = "handan";
	char s2[SIZE] = "kayhan";

	// mesela birinin son ücü ile diğerinin ilk içi eşit mi ?
	// indis ile karakter sayısını karıştırma sakın.s1 0. indisten 3 karakter alacak yani han
	// s2 3. indisten 3 karakter alacak yani yine han.

	if (!strncmp(s1, s2 + 3, 3))
		printf("yazilar esit\n");
	else
		printf("yazilar esit degil\n");

		YAZILARA SIKICI OLMAMASI İÇİN BİR SÜRE ARA VERİLDİ. 
		ZATEN BAYA BİR KOD GÖRÜLDÜ AMA YİNE GÖRÜLECEK
		SIRA EN ZOR KONULARIN OLDUĞU KISIM. 
		BU KISIMLAR MİLLETİN FATAL ERROR VERDİĞİ YERLER.

	===============================================================================================
	===============================================================================================
	===============================================================================================
	===============================================================================================
	===============================================================================================
	===============================================================================================
	===============================================================================================
	===============================================================================================
	===============================================================================================
	===============================================================================================
	===============================================================================================
	===============================================================================================
	===============================================================================================

	STRING LITERALS
	POINTER ARRAYS
	POINTER TO POINTERS
	VOID POINTERS
	FUNCTION POINTERS
	MULTI-DIMENSIONAL ARRAYS
	DYNAMIC MEMORY MANAGEMENT

	--------------------------


	STRING LITERALS(YAZI SABİTLERİ)

	"UMUT KOTANKIRAN" bu bir token.bu şekilde oluşturulan tokenlara string literali denir.
	
	Bir string literali derleyici tarafından oluşturulan elemanları char türden olan dizidir.
	Bu dizinin boyutu literaldeki karakter sayısı + 1 dir.

	"kaya"  boyutu 5 olan bir dizi. Yazı uzunluğu 4 
	"can"	boyutu 4 olan bir dizi .Yazı uzunluğu 3

	bir dizinin ismini ifade içinde kullandığımızda array decay yapılıyor.
	aynısı strling literalleri içinde geçerli.
	"ali" -> bunu dizinin ilk elemanının adresine dönüştürür.burada da array decay var yani.

	"kaya" 5 elemanlı char dizi. yazının uzunluğu 4

	putchar(*"kaya"); ->   k yazar. ilk elemanı dereference etti aslında.
	putchar("alican"[2]);  - >    i yazdırır.

	printf("%zu : ",strlen("umut")); -> 4 yazar. ama tutulduğu dizi 5 elemanlı sondaki '\0' dan ötürü.
	printf("%zu : ",sizeof("umut")); -> 5 yazar.dizi 5 elemanlı çünkü..

	------------------

	char *p = "Melisa Aydogan";
	puts(p); yukarıdakini yazdırır

	printf("uzunluk : %zu\n",strlen(p)); -> uzunluk 14 yazar.

	Bunlar doğal durumlar.

	-------------------

	C de string literallerinin türü char dizidir.
	
	char *p = "Melisa Aydogan";
	p[4] = h;  yazmak UNDEFİNED BEHAVİOR. ÇÜnkü p pointerı bir dizi değil. Bir string literalinin
	başlangıç adresini tutuyor ve string literalleri static ömürlü ve değiştirilemez nesnelerdir.
	meliha yazsa bile bu bir UB.

	C de bir strling literalini değiştirmeye yönelik kodlar tanımsız davranıştır.

	-C dilinde string literaller türü char diziler iken(ama const gibi davranıyor, değiştirmeye 
	çalışmak tanımsız davranış).aslında read only.
	
	-C++ ta ise türü const chardır.

	ör:
	char *p = "maya";
	*p = 'K';   // BURASI UB. EN sık yapılan hata.Runtime hatası.

	madem değiştirilemiyor o zaman
	daha iyi daha okunur kod yazma ilkesi olarak, bir string literalini bir pointer değişken 
	ya da ilk değer olarak vereceksek bunu const char * ile vermek mantıklı.

	const char * = "maya"; yazmak daha mantıklı.
	*p = 'C'; yazarsak artık compile time hatası alırız.

	--------------------------
	--------------------------

	soru
	1. char p[] = "maya";  UB mi
	2. char * ptr = "maya";  UB mi


	1. char diziye ilk değer verme sentaksının bileşeni.yani buradaki mert yazısı bellekte ayrı bir
	dizide tutulmayacak.Ayrıca derleyici tarafından oluşturulan bir dizi yok.
	yani burada p[0] = 'K'; yapılabilir. UB YOK.

	2. burada iki ayrı değişken var aslında.Az önce diziyi değiştirmek UB değil dedik ama
	burada ptr bir string literalini gösterdiği için bu yazıyı(string literalini) değiştirmek UB dir.
	Ayrıca "maya" yazısı(yani str literali) programın başından sonuna kadar memoryde kalacak.

	String Literalleri bir istisna hariç / yukarıdaki hariç yani
	------------------------------------------------------------

	1 compile time da static olarak bakılınca türü char olan dizilerdir.

	2 bu dizilerin set amaçlı kullanılması UB dir.

	3 bu diziler static ömürlü dizilerdir.


	ÖNEMLİ

	printf("UMUT"); 
	bu yazının yani str literalini yazmaktaki amaç ekrana umut yazdırmak
	bu string literali programın başından sonuna kadar bellekte kalacak.
	Bunu benim 1 kere çağırmam başka bir durum ama bellekte programın başından 
	sonuna kadar kalıyor bu string literali.
	
	Static Ömürlü olmasının bizi ilgilendiren kısımları var.
	normalde otomatik ömürlü değişkenlerin adresini return edemezdik.Bu UB

	string literalini ise döndürebiliriz.UB oluşturmaz.
	Çünkü static ömürlü.

	char * get_month_name(int m)
	{
		switch(m)
			{
				case 1: return "ocak";
				case 2: return "subat";
				....
				....
				....
				case 12: return "aralik";
			
			}
		return "";
	}

	mesela yukarıdaki kodda UB yok.
	çünkü string literalleri static ömürlü.

	string literallerinin dezavantajı ise,
	öyle bir sistemde çalışmış olalımki, static verilere ayrılmış bellek alanı çok kısıtlı olsun.
	bu durumda sürekli string literali kullanamayız.


	NOT:
	string literalleri değiştirilemez.
	static ömürlüdür.
	programın başından souna kadar varlığını devam ettirirler.



	-------------------------

	SORU

	printf("umut");


	puts("umut");


	char *ptr = "umut";

	buradaki tüm umut yazıları aynı yerdemi tutuluyor yoksa ayrı mı?
	yani derleyici tüm umut lar için aynı dizileri mi yoksa ayrı dizi mi kullanıyor?
	CEVAP :  Unspecified behavior. Derleyiciye bağlı ama dökümante edilmiyor.

	------------------------
	------------------------
	------------------------

	char *p1 = "emre";
	char *p2 = "emre";

	if(p1 == p2)
		printf("evet esit\n");			
	else
		printf("hayir degil\n");

	Evette yanlış
	hayırda yanlış

	Unspecified behavior.belirsiz davranış.

	Birçok derleyicide evet yada yanlış olması durumunu seçebiliyoruz.


	-----------------
	ör
	char *psw = "black book";

	if(psw == "black book")
	{
		// burada muhbtemelen kastedilen psw nin içeriği "black book" mu.
		// aslında strcmp çağrılmalı.
		// Ayrıca,
		// burada psw black book a eşit mi?
		// olabilirde olmayabilirde. unspecified behavior.
	}

	-----------------

	NEDEN Kullanılıyor ?

	Okuması ve yazması kolay oluyor.

	mesela
	char str[100];

	strcpy(str,"ali"); koda bakarak belli oluyor.

	----------------------------------------------------------------------
	----------------------------------------------------------------------

	GÜzel örnekler

	char old_file_name[SIZE];
	char new_file_name[SIZE];
	
	printf("Dosya ismini girin \n");
	sgets(old_file_name);

	//tasklar aşağıda şimdi.

	// dosya ismini new file name e kopyala.
	strcpy(new_file_name, old_file_name); 
	printf("(%s) ---> (%s)\n", old_file_name, new_file_name);

	// dosyanın uzantısı yoksa uzantısını txt yap.
	// dosya uzantısı jpg ise dosya uzantısını gif olarak değiştirin
	// Eğer dosyanın uzantısı .xls ise uzantısı silinecek.
	// diğer tüm durumlarda uzantıyı .dat yapınız.

	char *p = strrchr(new_file_name, '.'); // son nokta önemli çünkü dosya adında da . olabilir.
	
	if (!p)
		strcat(new_file_name, ".txt");

	else if (!strcmp(p, ".jpg"))
		strcpy(p, ".gif");

	else if (!strcmp(p, ".xls"))
		*p = '\0';  // strcmp(p,"") te olurdu

	else
		strcpy(p, ".dat");

	printf("(%s) ---> (%s)\n", old_file_name, new_file_name);

	
	--------------------------------------------------------
	--------------------------------------------------------
	--------------------------------------------------------
	--------------------------------------------------------

	puts("Ayhan\n"); -> ayhan yazar ve newline bırakır.
	puts("Ayhan\tnecati\thasan"); tab bırakır.
	mesela

	"mustafa" yazdırmak istiyorum
	puts("\"mustafa\"");
	
	başa ve sona \ işareti koymak istersek
	puts("\\ahmet\\");

	puts("\\\\\"jale\"\\\\\n");

	file path yazarkende
	(void)fopen("c:\\files\\file.txt","r");




	*/
	puts("\"mustafa\"");
	puts("\\ahmet\\");
	puts("\\\\\"jale\"\\\\\n");
	(void)fopen("c:\\files\\file.txt","r");







	
}