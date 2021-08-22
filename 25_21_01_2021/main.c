#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "nutility.h"
#include <ctype.h>

#define SIZE	100
#define INWORD		1
#define OUTWORD		0

// ben outword ve inword macrolarını kullanmadım.
int main()
{
	/*
	gets_s ->visual studio da bu fonksiyonu opsiyonel hale getirilmiş.
	bu sebeple hata veriyor.

	ödevlerin bir kısmı çözülecek.

	-------------------------------
	DİZİ KOPYALAMA

	char source[SIZE];
	char dest[SIZE];

	printf("bir metin girin :");
	//gets(source);C 99 da deprecate edildi ve daha sonrakilerde dilden kaldırıldı.

	sgets(source); // biz yazdık sgets fonksiyonunu.

	int i;
	for (i= 0; source[i] != '\0'; i++)
	{
		dest[i] = source[i];
	}

	dest[i] = '\0';
	printf("[%s]\n", source);
	printf("[%s]\n", dest);

	//for yerine aşağıdaki de yazılabilirdi
	//while(dest[i++] = source[i++])
	//	;

	

	---------------------------------------------------

	Metinden karakter silmek.İkinci dizi kullanarak

	char source[SIZE];
	char dest[SIZE];

	printf("bir metin girin :");
	sgets(source);

	int c;
	printf("silinecek karakteri girin");
	c = getchar();

	int i, k;
	for (i = 0, k = 0; source[i] != '\0'; i++)
	{
		if (source[i] != c)
		{
			dest[k++] = source[i];
		}
	}

	dest[k] = '\0';

	printf("[%s]\n",source);
	printf("[%s]\n",dest);

-------------------------------------------------------

	Metinden karakter silmek.
	2. dizi kullanmadan


	char source[SIZE];
	printf("bir metin girin :");
	sgets(source);

	int c;
	printf("silinecek karakteri girin");
	c = getchar();

	int idx_read = 0;
	int idx_write = 0;

	while (source[idx_read] != '\0')
	{
		if (source[idx_read] != c)
		{
			source[idx_write++] = source[idx_read];
		}

		idx_read++;
	}

	source[idx_write] = '\0';
	printf("[%s]", source);

	---------------------------------------------

	2 metnin karşılaştırılması


	char s1[SIZE];
	char s2[SIZE];
	printf("iki adet dizi giriniz\n");
	(void)scanf("%s%s", s1, s2);

	int i = 0;
	int flag = 0;

	while(s1[i] == s2[i])
	{
		if (s1[i] == '\0')
		{
			flag = 1;
			break;
		}
		i++;
	}

	if (flag)
		printf("diziler esit\n");
	else
		printf("diziler esit degil\n");


	---------------------------------------------

	yazıdaki kelimelerin sayılması.

	char str[SIZE];
	printf("yazi girin: ");
	sgets(str);

	int word_count= 0;
	int flag = 0;
	int i = 0;

	while (str[i] != '\0')
	{
		if (isspace(str[i]))
			flag = 0;
		else if (flag == 0)
		{
			flag++;
			word_count++;
		}
		i++;
	}
	printf("[%s]",str);
	printf("kelime sayisi %d",word_count);


	------------------------------------------------------------

	Palindrom sayı örneği yeni dizi ye kopyalayarak kolay oluyor.
	Yeni diziye kopyalamadan yapılanı ödev


	char str1[SIZE];
	char str2[SIZE];

	printf("metin girin : ");
	sgets(str1);

	int len = 0;
	for ( int k = 0; str1[k] != '\0'; k++)
	{
		if(isalpha(str1[k]))
			str2[len++] = str1[k];
	}
	str2[len] = '\0';

	int j;
	for (j = 0; j < len / 2; j++)
	{
		if (str2[j] != str2[len - 1 - j])
			break;
	}

	if (j == len / 2) // en son j bir artırıldı ve koşulu sağlamadığı için çıktı döngüden
	{					// yani j = len/2 oldu
		printf("Metin palindrom \n");
	}
	else
		printf("metin palindrom degil \n");


	=====================================================
	=====================================================
	=====================================================

	Derleyicinin yaptığı logic kontroller

	Burada tipik hatalar gösterildi.Herzaman karşılaştığım hatalar.
	bu sebeple yazmıyorum.

	geri dönüş değeri olan bir fonksiyonun 
	bilerek geri dönüş değerini kullanmak istemiyorsak (void) ile cast
	etmek gerekiyor. (c = (void)getchar();) bunun gibi.bu şekilde warning almayız.

	scanf in verdiği crt_secure_no_warnings yaz diyor.
	burada scanf pointer hatası oluşturabilir. bu yüzden scanf_s çağır diyor.
	eğer devam etmek istersem crt_secure_no_warnings i define ediyorum.
	zaten uyarıda da yukarıda belirtilenler yazıyor.

	----------------------

	Etkisiz kod

	5;
	a;
	a + 5; hepsi etkisiz kod. geçerli, hata yok ama etkisiz.
	a == 10; etkisiz. Code has no effect


	Aşağısı unreachable code

	int foo(int a)
	{
		if(a == 1)
			return 10;
		else
			return 100;
	
		return 1000;  // hiçbir zaman ulaşamayacak						
	}

	fonksiyon içersinde infinite loop durumu olabilir.
	derleyiciler bunla ilgili mesaj verebiliyor ama vermek zorunda da değil.

	Stack Overflow hatası
	recursive fonksiyonlarda meydana gelir.

	fonksiyon sürekli kendini çağırdığında, otomatik ömürlü değişkenler sürekli 
	stackten yer harcıyor ve yeni çağrılan fonksiyonlarında otomatik ömürlü 
	değişkenleri stackten yer harcıyor ve stackte yer kalmıyor.
	Buna stack overflow deniyor.

	Derleyiciler bu durumu her zaman olmasada anlayabiliyorlar.

	if (x)
		return x
	return 10    // bu duruma base case deniyor.durdurma mekanizması gibi.

	------------------------------------------------

	1.48 de donald knut un sorusunun cevabı var.

	------------------------------------------------

	Ödev
	1.55
	dizi için alt sequence lar aranıyor.
	
	1234243456567956  içimde 565 sequence aranıyor ama hem dizi hem sequence random.
	
	Ödev
	SIZE + 1 boyutundaki dizide SIZE a kadar tüm sayılar var ama
	bir sayıdan 2 tane var. bunu bulacağız.
	2:00
	algoritme karmaşıklığı nedir?

	---------------------------------------------

	Kod tekrarı felakettir.

	===================================================
	===================================================
	===================================================
	===================================================
	===================================================
	===================================================
	===================================================
	===================================================
	===================================================
	===================================================
	===================================================
	===================================================
	===================================================


	POINTERS

	pointer ==> address
	nesnelerin adresi runtime da nesnelerin nerede olduğunu tutuyor.

	Pointer
	--------
	1 - nesne adresleri (object pointers)
	2 - fonksiyon adresleri (function pointers)

	--------------------------------------------
	her ifadenin bir türü var
	int x     x in türü int

	int *x -> int türden değişkenin adresi
	double *x -> double türden deişkenşn adresi
	kaç tür varsa herbiri için birde adres türü var. yani x2 oldu tür sayısı.

	int *x;
	&x -> bu x in adresi anlamına gelir ve bunun türü int * türüdür. buna pointer deniyor.

	Pointer değişkenler değeri adres olan değişkenlerdir.
	SENTAKS
	Nasıl tanımlanır.

	int *ptr;  veya 
	int* ptr;  veya
	int * ptr;    
	ptr değişkenlerinin türü int *
	ptr değişkeni int türden değişkenlerin adresini tutar burada.

	int *ptr = adres; 
	buna pointer to int deniyor(int *)

	double *ptr;
	pointer to double (double *)

	aşağıdaki adres türlerinin hepsi aynı boyutta yer kaplar.
	int *
	double *
	char *
	bunlar sizeof(int *) sizeof(double *) sizeof(char *) sizeof(short *) .... hepsi aynı boyuttadır.


	bir pointer 
	global (dolayısıyla static) olabilir
	otomatik ömürlü local
	statik ömürlü local olabilir




	*/




}