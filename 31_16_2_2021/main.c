#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "nutility.h"
#include <string.h>

#define		SIZE	100

void my_puts(const char* p)
{
	while (*p) // null değil demek.
		putchar(*p++); //elemanı ekrana yazdırıp adresi bir artırıyor

	putchar('\n');
}

char* my_gets(char* p) // dizinin boyutu alınmadı ve UB yada pointer hatası riski var
{					// çünkü taşırabiliriz boyutunu.Yeterince büyük olduğunu varsaydık.
	int c;
	char* ptemp = p; // dizinin adresini döndürüyor.aşağıda dizi adresi hep bir artırıldı
					// bu sebeple p yi return etsek null char return eder.çünkü p en son
					// null charı gösteriyor :D

	while ((c = getchar()) != '\n' && c != EOF) //eof= std giriş akımının bufferı boşsa yine girmeyecek.
		*p++ = (char)c; // adres burada hep bir artıyor

	*p = '\0'; // p yukarıda arttı ama while içinden çıktı.
			 //null char da girilmesi lazım
	
	return ptemp; // dizinin ilk değeri burası return edildi.
}

size_t my_strlen(const char* p)
{
	size_t len = 0;
	
	while (*p++) // *p != NULL denebilirdi.diziye erişim olarak yazmazdım ama
		len++;	 // uzunluk belirttiğim için yazıyorum.çünkü index te bittiği yerin  
					// adresini gösteriyor.
	return len;
}



void rputs(const char* p)
{
	int len = strlen(p);
	
	for (int i = len - 1; i >= 0; i--)
		putchar(p[i]);

	putchar('\n');
}

void rputs1(const char* p)
{
	const char* ptemp = p;
	while (*p++) // dizinin bittiği yerin adresi.Null chardan 1 sonrası yani.
		;
	while (--p >= ptemp)
		putchar(*p);
}

char* my_strchr(const char* p, int val)
{
	while (*p)
	{
		if (*p == val)
			return (char*)(p);
		
		p++;
	}

	return NULL;
}

char* my_strrchr(const char * p, int c)
{
	// 2 yol var. birincisi kötü. yazının sonuna gidip. sonra geri gelirken 
	// ilk bulunan yerde return edilir. ama dezavantaja. çok büyük ise yazı.
	// en sona gitmek geri gelmek çok maaliyetli.

	// verimli yol aşağıda.

	const char* pfound = NULL;

	while (*p) 
	{
		if (*p == c) // burada 10 kerede denk gelse en son denk gelenin indisini tutar
			pfound = p; 
		++p;
	}

	if (c == '\0') // eğer c null char ise zaten artırılmış olan p yi return eder.
		return (char*)p;	// çünkü p buraya geldiyse en son olan '\0'tedir.

	return (char*)pfound;

}

char* my_strcpy(char* pdest, const char* psource)
{
	char* ptemp = pdest;
	while (*pdest++ = *psource++) // hiçbirşeye gerek yok. Süper bir idiyom.
		;
	// normalde null da *pdest = '\0' olarak ekledim fakat yukarıda onuda yapıp çıkıyor
	return ptemp;
}

char* my_strcat(char* pdest, const char* psource)
{

	char* ptemp = pdest;
	while (*pdest) // bunun yerine strcpy(pdest + strlen(pdest),psource); yazarak hepsi yapılabilir.
		pdest++;		// tek satırda hepsi yapılabiir yani.

	while (*pdest++ = *psource++)
		;

	return ptemp;
}


int main()
{
	/*
	*	Totalde 20 civarı string fonksiyonu var.
		Bugünkü derste 7 Adet String fonksiyonu anlatılacak.
		string.h kütüphanesi içerisindeler. Herbirinin fonksiyonu hem manuel 
		yazılacak hemde kütüphaneleri kullanaran işlenecek.
		Buradaki örnekler baya iyi.

		C içerisinde büyük bir yazıyı daha küçük bir array e kopyalamak UB.

		C de sonu _s ile biten fonksiyonlar var. Secure dan geliyor.
		Farkı dizi boyutunu alıyor ve taşma hatasını oluşturmuyor.
		Maliyeti de var. Sonuçta kontrol ediyor dizi bittimi bitmedimi diye.

		===================================================================
		===================================================================

	void my_puts(const char* p)
	{
	while (*p) // null değil demek.
		putchar(*p++); //elemanı ekrana yazdırıp adresi bir artırıyor

	putchar('\n');
	}

	char* my_gets(char* p) // dizinin boyutu alınmadı ve UB yada pointer hatası riski var
	{					// çünkü taşırabiliriz boyutunu.Yeterince büyük olduğunu varsaydık.
	int c;
	char* ptemp = p; // dizinin adresini döndürüyor.aşağıda dizi adresi hep bir artırıldı
					// bu sebeple p yi return etsek null char return eder.çünkü p en son
					// null charı gösteriyor :D

	while ((c = getchar()) != '\n' && c != EOF) //eof= std giriş akımının bufferı boşsa yine girmeyecek.
		*p++ = (char)c; // adres burada hep bir artıyor

	*p = '\0'; // p yukarıda arttı ama while içinden çıktı.
			 //null char da girilmesi lazım

	return ptemp; // dizinin ilk değeri burası return edildi.
	}

	===================================================================
	===================================================================
	
	bazı string fonksiyonları
	strlen
	strchr
	strstr
	strcpy
	strcat
	strrchr
	strcmp
	strspn
	strcspn
	strncpn
	strncat
	strncmp


===========================================

	size_t strlen(const char *p);
	bir yazının uzunluğunu buluyor.Yazı adresi alıyor .
	bu fonksiyona NULL ptr geçmek UB.

	Geri dönüş değerini de aynı şekilde saklamak mantıklı.
	size_t len = strlen(str);
	mesela bende Unsigned int ten typedef edilmiş size_t.
	
	size_t yi printf ile yazdırırken %zu conversion specifier kullanmak mantıklı
	size_t len = strlen(str);
	printf("%zu\n",len);
	Kodunu manuel olarak aşağıdaki gibi yazılır.

	===============================================================
	===============================================================
	
	size_t my_strlen(const char* p)
	{
	size_t len = 0;

	while (*p++) // *p != NULL denebilirdi.diziye erişim olarak yazmazdım ama
		len++;	 // uzunluk belirttiğim için yazıyorum.çünkü index te bittiği yerin
					// adresini gösteriyor.
	return len;
	}

	Alternatif
	size_t my_strlen1(const char* p) // başka alternatif for ilede yazılabilir.
	{
	const char * ptemp;

	while (*p) // *p != NULL denebilirdi.diziye erişim olarak yazmazdım ama
	 	p++;	 // uzunluk belirttiğim için yazıyorum.çünkü index te bittiği yerin
					// adresini gösteriyor.
	return (size_t)(p - ptemp);
	}

	===============================================================
	===============================================================

	Eğer standart kütüphanede var olan bir fonksiyon varsa bunu tekrar manuel olarak
	yazmaya gerek yok. Zaten en optimize halini standart kütüphanede buluruz.

	===============================================================
	===============================================================

	void rputs(const char* p) // bu ödev. Farklı biçimlerde yazmaya çalış.
	{
	int len = (int)strlen(p);

	for (int i = len - 1; i >= 0; i--)
		putchar(p[i]);

	putchar('\n');
	}

	void rputs1(const char *p)
	{
		const char * ptemp = p;
		while(*p++) // dizinin bittiği yerin adresi
			;
		while(--p >= ptemp)
			putchar(*p);
	}

	

	===============================================================
	===============================================================

	strchr -> bu bir yazı içerisinde bir karakter arıyor.

	char* my_strchr(const char* p, int c)
	{
		while (*p)
		{
			if (*p == c)
				return (char*)(p);

			p++;
		}

		if(c == '\0')
			return (char *)p;

	return NULL;
	}

	---------------------------------

	char a;
	a = (char)getchar(); // veya (void)scanf("%c", &a);

	char *p = my_strchr(str, a);

	if (p)
	{
		printf("%d indisli eleman  - > %p  =   %c\n",p-str, p, *p);
		*p = '!';
		my_puts(str);
	}
	else
		printf("bulunamadi");


	p = strchr(str,'\0');
	*p++ = 'X';
	*p = '\0';
	puts(str);

	===========================================================
	===========================================================

	NULL						'\0'
	------------------------|--------------------	
	symbolic constant		|	character constant
	pointer degiskenlere	|	s[i] = '\0';


	Bu ikisinin bir arada kullanıldığı yer

	if(ptr != NULL && *ptr != '\0')
	burada eğer pointer null değilse demek istiyor ilk ifadede
	ikincisinde ise dereference edilen pointer değeri null character değilse demektir

	aşağıdaki gibide yazılabilir.
	if(ptr && *ptr)

	Tam tersi - de morganı hatırla
	if(!ptr || !*ptr)    -> ptr null ise veya *ptr null character ise.
	uzunda yazılabilir.short circuit te olabilir.

	====================================================================
	====================================================================

	strrchr -> yazıda karaterin geçtiği son yeri bulur.
	char * strrchr(const char *p, int ch);


	----------------------
	ör:

	char str[SIZE];
	char* p;
	printf("bir yazi giriniz\n");
	my_gets(str);

	printf("bir karakter girin\n");
	char c = getchar();
	printf("arama strrchr ile yapiliyor.\n");
	p = strrchr(str, c);

	if (p)
	{
		printf("yazinin bulundugu %d indisli karakteri\n", p - str);
		*p = '*';
		puts(str);
	}
	else
		printf("bulunamadi\n");

	--------------------------------------------------
	--------------------------------------------------

	kodu aşağıda

	char* my_strrchr(const char * p, int c)
	{
		// 2 yol var. birincisi kötü. yazının sonuna gidip. sonra geri gelirken
		// ilk bulunan yerde return edilir. ama dezavantaja. çok büyük ise yazı.
		// en sona gitmek geri gelmek çok maaliyetli.

		// verimli yol aşağıda.

		const char* pfound = NULL;

		while (*p)
		{
			if (*p == c) // burada 10 kerede denk gelse en son denk gelenin indisini tutar
				pfound = p;
			++p;
		}

		if (c == '\0') // eğer c null char ise zaten artırılmış olan p yi return eder.
			return (char*)p;	// çünkü p buraya geldiyse en son olan '\0'tedir.

		return (char*)pfound;


	char str[SIZE];
	char* p;
	printf("bir yazi giriniz\n");
	my_gets(str);

	printf("bir karakter girin\n");
	char c = getchar();
	printf("arama strrchr ile yapiliyor.\n");
	p = my_strrchr(str, c);

	if (p)
	{
		printf("yazinin bulundugu %d indisli karakteri\n", p - str);
		*p = '*';
		puts(str);
	}
	else
		printf("bulunamadi\n");

	}


	=================================================================
	=================================================================

	strcpy()
	kopyalama fonksiyonu. String copy.
	yazıların atama operatörü gibi.

	char * strcpy(char *pdest, const char *psource) 
	genelde C de dest ilk başta, sonrada source geliyor.
	yada yazma amaçlı olarak kullanılan ptr, okuma amaçlı kullanılan
	ptr den daha önce geliyor.

	Eğer bir fonksiyon:
	a - bir adrese bir yazı yerleştiriyor ise
	b - bir adresteki yazıyı yerleştiriyor ise

	tipik olarak aldığı adresi döndürür.

	yani strcpy(s1,s2);
	geri dönüş değeri s1 dir.

	--------------

	char dest[SIZE];
	char source[SIZE];

	printf("bir yazi girin");
	sgets(source);
	strcpy(dest, source);
	printf("(%s)\n", source);
	printf("(%s)\n", dest);


	char s1[SIZE];
	char s2[SIZE];
	char s3[SIZE];

	strcpy(s3,s1);

	strcpy(s3 + strlen(s3),s2); -> bu 1. yazının sonuna 2. yazıyı ekler.

	//strcpy(strcpy(s3,s1) + strlen(s3),s2); //bu s3 = s1 + s2 yapar.

	printf("(%s) + (%s)  =  (%s)\n",s1,s2,s3);

	çalışıyor.

	Kodunuda yazacağız.

	--------------------------------
	--------------------------------

	char* my_strcpy(char* pdest, const char* psource)
	{
		char* ptemp = pdest;
		while (*pdest++ = *psource++) // hiçbirşeye gerek yok.Süper bir idiyom.
			;
		// normalde null da *pdest = '\0' olarak ekledim fakat yukarıda onuda yapıp çıkıyor
		return ptemp;
	}

	--------

	char dest[SIZE];
	char source[SIZE];

	printf("bir yazi girin\n");
	sgets(source);
	my_strcpy(dest, source);
	printf("(%s)\n", source);
	printf("(%s)\n", dest);




	ÇOK ÖNEMLİ BİR HATA.
	strcpy koduna std c fonksiyonunun dökümantasyonuna bakarsak
	içinde birsürü UB durumu var.mesela

	strcpy(a+5,a) ;  a[5] ten sonra a ya, a yı kopyala. UNDEFINED BEHAVIOR.


	char str[SIZE] = "Mehmet";
	strcpy(str + 3, str);  // UB Oluşturuyor.Overlaps blocks. çünkü source arrayde
	puts(str);				// kopyalarken değişiyor ve çakılıyor bunlar.

	Bunun yerine ileride görülecek memmove kullanılacak.
	bir yazıyı bulunduğu bellek alanından kopyalayıp geri oraya kopyalayacaksak 
	yani hem okuma hemde yazma amaçlı kullanılacaksa bir block,
	burada memmove kullanılır.

	=================================================================
	=================================================================


	aşağıdakiler char array de char charactere öteler mi?
	while(p*)
		p++;

	while(*p != '\0')
		p++;

	while(*p++) bu olmaz. null characterin de bir sonrasına gider.Bittiği yer yani.
		;

	birde 
	str + strlen(str) -> bu da null characterin adresini elde eder.

	veya 
	strchr(str,'\0') ;   -*> buda aynı şekilde null char adresini verir.

	=======================================================================
	=======================================================================
	=======================================================================

	strcat() -> concatanate 
	bir yazının sonuna başka bir yazı ekler.concat ediyor.ya da birleştiriyor.

	cont *strcat(char *pdest,const char *psource);

	------------------------------------------------------------------
	------------------------------------------------------------------

	char* my_strcat(char* pdest, const char* psource)
	{

		char* ptemp = pdest;
		while (*pdest)   // bunun yerine strcpy(pdest + strlen(pdest),psource); yazarak hepsi yapılabilir.
			pdest++;

		while (*pdest++ = *psource++)
			;

		return ptemp;
	}

	-------------------------------

	char s1[SIZE] = { 0 }; // warning verdiği için {0 } a eşitledim.
	char s2[SIZE] = { 0 };

	printf("iki isim girin :");

	(void)scanf("%s%s", s1, s2); //ahmet aksoy
	size_t len = strlen(s1);
	puts(s1);
	*(s1 + len) = ' '; // alttaki ile birlikte bunu koymazsam bitişik yazar.
	*(s1 + len + 1) = '\0';

	(void)my_strcat(s1, s2);
	puts(s1);

	------------------------------------
	------------------------------------

	char s1[SIZE] = { 0 };
	char s2[SIZE] = { 0 };
	char s3[SIZE] = { 0 };

	printf("İki adet isim girin\n");
	(void)scanf("%s%s", s1, s2); //ahmet aksoy

	// bunları s3 e kopyalayacağım.

	strcpy(s3, s1);
	strcat(s3, s2);
	printf("(%s)  ve (%s) = (%s)", s1, s2, s3);

	// veya aşağıdaki gibi yazılabilir.
	strcat(strcpy(s3, s1), s2);
	puts(s3);

	===========================================================
	===========================================================
	===========================================================

	ÖDEV 
	strstr yi yaz.

	char * strstr(const char *p1, const char * p2);

	char s1[SIZE] = { 0 };
	char s2[SIZE] = { 0 };
	char* p;

	printf("arama yapilacak yaziyi girin\n");
	sgets(s1);

	printf("aranacak diziyi girin\n");
	sgets(s2);

	p = strstr(s1, s2);

	if (p)
		printf("bulundu, %d indisli karakter  ->   %s\n", p - s1, p);
	else
		printf("bulunamadi\n");

	--------------
	--------------
	--------------

	ARANAN kelime yerine * yazdırmak

	if (p)
	{
		size_t len = strlen(s2);
		while (len--)
			*p++ = '*';
	}

	puts(s1);

	=======================================================
	=======================================================
	=======================================================

	YAZILARIN KARŞILAŞTIRILMASI.

	6 adet operator var
	== 
	!=
	<
	<=
	>
	>=

	int retval = compare(a,b)

	retval > 0 ise a > b
	retval < 0 ise a < b
	retval == 0  ise a = b

	Bunu yapan 

	int strcmp(const char *p1, const char *p2)
	return değeri pozitif ise p1 deki p2 dekinden daha büyük
	negatif ise p1 deki p2 den küçük
	0 ise eşitler


	idiyom
	if(!strcmp(s1,s2))  eşitse 0 döndüreceğinden burada if e girer. 

	yazıların büyüklük küçüklüğünü kıyaslayan algoritmaya
	lexicographical compare denir.


	*/
	
	
	
	char s1[SIZE] = { 0 };
	char s2[SIZE] = { 0 };
	char* p;

	printf("arama yapilacak yaziyi girin\n");
	sgets(s1);

	printf("aranacak diziyi girin\n");
	sgets(s2);
	
	p = strstr(s1, s2);
	
	if (p)
		printf("bulundu, %d indisli karakter  ->   %s\n", p - s1, p);
	else
		printf("bulunamadi\n");

	if (p)
	{
		size_t len = strlen(s2);
		while (len--)
			*p++ = '*';
	}

	puts(s1);

	


}