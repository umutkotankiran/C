#include "nutility.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#define		SIZE		100
#define		URAND_MAX	10

// bu normalde burada olmayacak.aşağıda çağrıldığı için ekledim.
//nutility.c de private olarak var.
static int icmp(const void* vp1, const void* vp2)
{
	return *(const int*)vp1 - *(const int*)vp2;
}


int urand(void)
{
	static int a[URAND_MAX] = { 0 }; // mesela a[5] == 1 ise daha önce üretilmiştir 0 ise üretilmemiştir.
	//static ömürlü olmalı çünkü fonksiyondan her çıkıldığında değerlerini kaybetmemeli.
	// ya static anahtar sözcüğü ile tanımlanmalı veya global scope ta yazılır.global scopeta yazılırsa 
	// herkese açık olur ama onu istemiyoruz.bu şekilde daha güvenli.
	static int count = 0; // kaç rasgele sayı üretildiğinin bilgisi.static ömürlü yerel dizi
	int val;

	if (count == URAND_MAX) // maximum 100 defa çağrılmalı zaten. Değilse -1 çevirir.
		return -1;
	for (;;) // unique değeri bulana kadar for çalıştırıyor.
	{
		val = rand() % URAND_MAX;
		if (a[val] == 0)
			break;
	}

	a[val] = 1; // artık ilgili indis 1 oldu. yani 25 için a[25] = 1, 25 üretildi artık.
	count++;
	return val;
}

int main()
{
	//bazı algoritmalar ilave yer kullanırken bazıları kullanmaz.	
	
	// stable sort algoritmalarda, mesela 3 tane umut var. sıraladıktan sonra da bu umutlar kendi arasında eski sıralamaya
	// sahipse, buna stable sort deniyor.

	// kursun sonuna kadar bubble sort kolay olduğu için kullanacağız.arada bir quick sort.
	// yüksek değerlerde 100'000 veya üzeri değerlerde quick sort aşırı büyük fark atıyor.
	// nlogn ile n2 karmaşıklığı arasındaki fark aşırı yüksek oluyor.biri 1 saniye sürmezken diğeri saatler günler sürüyor.

	int a[SIZE];

	randomize();
	set_random_array(a,SIZE);
	print_array(a, SIZE);

	//Necati hoca çok sık yazılarak yapılan ezberin kötü olmadığını söylüyor. Ezberleyin :D
	//bubble sortta (n-1) * (n-1) sıralama gerekiyor.

	for (int i = 0; i < SIZE - 1; i++)
	{
		for (int j = 0; j < SIZE -1 - i; j++) // sıralananları bir daha sıralamaması için
		{
			if (a[j] > a[j + 1]) // küçükten büyüğe.buyukten küçüğe için a[i] < a[i + 1] yazmak gerekir.
			{
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1]  = temp;			
			}
		}
	}

	print_array(a, SIZE);


	// sıralama kriteri ile sıralama algoritması farklı şeyler. sıralama kriteri sayının nasıl sıralanacağı.

	// bir soru vardı.if içerisine öyle bir ifade yazılacakki.bir diziye ilk önce tekler sonra çiftler sıralı şekilde yazılacak.

	//SORU/CEVAP :
	/*for (int i = 0; i < SIZE - 1; i++)
	{
		for (int j = 0; j < SIZE - 1 - i; j++) 
		{
			if(1) // ??????????????????????????????????????? if içerisine öyle ifade yazılmalı ki
			{		// ilk ciftler, sonra da tekler sıralı şekilde yazılsın. 
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}*/

	// cevap a[k] çift ve a[k+1] tek ise mutlaka takas yapılmalı.
	// a[k] % 2 != 0 && a[k+1] % 2 == 0 . bu tekleri başa çiftleri sona alır.çünkü her teki çift ile yer değiştirir bu ifade.
	// sonraki adımda kendi içlerinde de sıralı olmasını sağlamak gerekiyor.
	// a[k] % 2 != 0 && a[k+1] % 2 == 0 || (a[k] % 2 == a[k+1]%2) && a[k] > a[k+1]) 
	// || den sonr ayazılan ise hem bakılan hemde bir sonraki eleman tek veya çift ise ve bakılan, bir sonrakinden büyükse demek.

	for (int i = 0; i < SIZE - 1; i++)
	{
		for (int j = 0; j < SIZE - 1 - i; j++)
		{
			if (a[j] % 2 != 0 && a[j + 1] % 2 == 0 || (a[j] % 2 == a[j + 1] % 2) && (a[j] > a[j + 1]))
			{		// ilk ciftler, sonra da tekler sıralı şekilde yazılsın. 
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
	printf("tekler ve ciftler siralamasi\n");
	print_array(a, SIZE);

	//==========================================================
	//==========================================================

	// Bubble sort ile Quick sort karşılaştırılıyor.

	//bunlar sonra görülecek

	

#undef SIZE
#define SIZE 10'000


	int* p = (int*)malloc(SIZE * sizeof(int));
	if (!p)
	{
		fprintf(stderr, "Bellek yetersiz! \n");
		return 1;
	}
	
	
	set_random_array(p, SIZE);
	
	clock_t start = clock();

	for (int i = 0; i < SIZE -1 ; i++)
	{
		for (int j = 0; j < SIZE - 1 - i; j++)
		{
			if (p[j] > p[j + 1])
			{
				int temp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = temp;
			}
		}
	}

	clock_t end = clock();
	printf("bubble sort ile  %d elemani %f sn de yapiyor.\n",SIZE, (float)(end - start)/CLOCKS_PER_SEC);
	// 100'000 elemanı ise 20 sn de yapıyor. işlem 10 katına çıkınca, zaman (20 / 0.18) kadar artıyor yani çok daha hızlı artıyor.
	//quick sorta bakarsak
	// bu fonksiyon leride görülecek. stdlib.h d geçen qsort .

	
	start = clock();

	qsort(p, SIZE, sizeof(*p), icmp);

	end = clock();

	printf("Quick sort ile  %d elemani %f sn de yapiyor.\n", SIZE, (float)(end - start) / CLOCKS_PER_SEC);
	printf("Arada cok fark var. SIZE 10'000'000 olsa biri saniyeler digeri gunler bekli aylar sure tutar\n");

	//=============================================================
	//=============================================================

	// bir ödev çözümü yapılıyor burada. Unique dğerleri yazdırıyor. çözümü yazmadım.
	// ödevde farklı bir teknikte var. Fred baptiste yazmıştı daha önce. ++count[a[i]]
	// bu sayede belirtilen indisteki eleman 1 artılıyor ve döngü bitince 1 ise unique tir.

	// subsequence ödevi var. dizi içerisindeki alt dizilerden toplamı en yüksek olanı bul. 1:04 te test kodu var.
	// seed degeri 14012021. Algoritma karmaşıklığı best case O(n)
	// O(n2) de kabul.

	//=============================================================

	
	// Unique random number generator.
	// fonksiyon en fazla 100 kere çağrılabilir.hata olursa -1 üretecek.

	// randomize çalıştırılmıştı.
	printf("\n");

	for (int i = 0; i < URAND_MAX; i++)
	{
		printf("%d ", urand());
	}
	printf("\n");
	printf("%d ", urand()); // -1
	printf("\n\n");
	//===============================================================
	//===============================================================

	// sizeof OPERATÖRÜ

	// operatör olarak kullanılan tek keyword. Operatör öncelik tablosunda 2. sırada
	// Bu bir compile time operatörü.
	// sizeof ile oluşturulan ifade bir sabit ifadesidir.
	// Sequence pointi iptal ediyor. printf("%zu\n", sizeof(x++)); burada x++ yı iptal ediyor.Alında kod üretmiyor.
	// bir tür için storage ihtiyacının kaç byte olduğunu gösterir.
	// Ürettiği değer işaretsiz tamsayı türü. u int, u long, u long long olabilir.
	// size_t ile tutuluyor.

	// Aşağıdaki durum unevaluated context tir.C++ ta çok var.
	int x = 5;
	printf("%zu\n", sizeof(x++)); // sequence point gitti.sizeof operatörünün operandı olan ifade için 
	printf("%d\n", x);					// compiler işlem kodu üretmez. 

	// sizeof(int) kullanımı.
	printf("sizeof(char) = %zu\n", sizeof (char)); // burada sizeof char parantez olmadan hata verir burada.
	printf("sizeof(int) = %zu\n", sizeof(int));
	printf("sizeof(long) = %zu\n", sizeof(long));
	printf("sizeof(double) = %zu\n", sizeof(double));   // diğerleride yazılabilir.

	x = 10;
	// normalde int a[x] = {} hata verir.
	// ama aşağıdaki gibi yazınca sorun yok.
	int a1[sizeof(double)] = { 0 };

	//sizeof exp
	//sizeof(exp)
	x = 10;
	double dval = 21.21;
	printf("%zu\n", sizeof x);// expression gelince paranteze gerek yok.
	printf("%zu\n", sizeof(x));
	
	//------------------------------------
	putline();

	printf("%zu\n", sizeof 'A');  // char int olarak tutuluyor.
	printf("%zu\n", sizeof 'A' + 5);
	printf("%zu\n", sizeof ('A' + 5));
	
	putline();
	//TEKRAR

	// Aşağıdaki durum unevaluated context tir
	x = 10;
	printf("%zu\n", sizeof(x++)); // sequence point gitti.sizeof operatörünün operandı olan ifade için 
	printf("%d\n", x);					// compiler işlem kodu üretmez. 

	// tanımsız davranış olsa bile işlem kodu üretmez.
	int asd;
	sizeof(asd + 1.2); // tanımsız davranış olsa bile kod üretmez.

	int k[10] = { 0 };
	printf("%zu\n", sizeof k); // array decay yok. array değişkenini yazınca ilk elamanının adres değerini yazmaktı aslında.
									// yukarıda ise size ı verir. 40

	printf("ilk eleman %zu\n", sizeof k[0]); // ilk elemanın size bilgisi
 	printf("dizi eleman sayisi %zu\n", sizeof k / sizeof k[0]); // dizi eleman sayısını verir.baya kullanışlı.


	putline();

	int l[300] = { 0 };
	printf("%zu\n", sizeof l);
	printf("ilk eleman %zu\n", sizeof l[0]); 
	printf("dizi eleman sayisi %zu\n", sizeof l / sizeof l[0]); 


	int k1[10] = { 4,5,67,8,76,5,4,3,2,6 };

	for (int i = 0; i < sizeof(k1) / sizeof(k1[0]); i++)
		printf("%d ",k1[i]);
	
	// asize diye bir macro yazdım.
	printf("\n");
	
	for (int i = 0; i < asize(k1); i++)
		printf("%d ", k1[i]);

	putline();



	// ÇOK ÖNEMLİ
	int c[] = { 4,6,2,6,1,5,9,7,8 };

	/*
	for (int i = -2; i < asize(c) - 2; i++) // burada asize unsigned int. karşılaştırılmış. i de type casting işlemine sokulur.
		printf("%d ", c[i+2]);				// -2 olduğu için unsigned int e çevrilince değeri 4.2 milyar küsür olur.döngüye girmez.
	*/									

	int c1[asize(c) * 2] = {0};  // diğer dizinin boyutuna göre yapılandırılabilir.
	int c2[asize(c) * 3 / 2] = {0};

	x = 5;
	int y = 5;
	printf("%d", sizeof ++x + ++y); // int olduğu için 4. işleme sokulmadı ++. ikincideise sokulur. 4+6 = 10

	putline();
	printf("\n");

	//============================================================
	//============================================================
	//============================================================


	// MERGE, SIRALI BİRLEŞTİRME O(n) karmaşıklığında.

#undef	 SIZE
#define		SIZE	 10

	a[SIZE];
	int b[SIZE];
	int merged[2 * SIZE];

	// randomize çalıştırıldı en yukarıda zaten.gerek yok.
	set_random_array(a, SIZE);
	set_random_array(b, SIZE);
	sort_array(a, SIZE);
	sort_array(b, SIZE);

	print_array(a, SIZE);
	print_array(b, SIZE);

	
	// iki arrayi C arrayinde sıralı bir şekilde birleştirmek istiyoruz.
	int idx_a = 0;
	int idx_b = 0;

	for (int i = 0; i < 2 * SIZE; i++)
	{
		if (idx_a == SIZE)
			merged[i] = b[idx_b++];

		else if (idx_b == SIZE)
			merged[i] = a[idx_a++];

		else if (a[idx_a] < b[idx_b])
			merged[i] = a[idx_a++];

		else
			merged[i] = b[idx_b++];
	}

	print_array(merged, 2 * SIZE);


	//------------------------------------
	//------------------------------------

	printf("\n");
	
	int r[10] = { 5,3,2,5,6,7,1,9,7,8 };

	for (int i = 0; i < 10; i++)
	{
		printf("%d ", i[a]);  // bu legal.Pointerlarda görülecek.a[i] ile i[a] arasında fark yok.
	}

	return 0;
}