#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "nutility.h"
#include <stdlib.h>
#include <string.h>

/*

	REALLOC
	-------

	void *realloc(void *vp, size_t newsize);
	*vp --> burada bellek bloğu adresi
	 newsize --> burada bu adresin olması istenilen değeri yazacak.
	 ör: 100 byte yer var bunu 200 istersek bu değer 200 olacak.

	re allocation anlamında kullanılıyor. Bir bellek bloğunu hem büyütüp
	hemde küçültebiliyor. Daha çok büyütme amaçlı kullanılıyor.

	Burada 3 ihtimal var.
	--------------------
	1 - realloc fiziksel olarak var olan bellek bloğunu büyütecek şekilde yapabilir.
	yani eski adresi ile yeni adresi aynı olabilir, var olan bloğu uzatabilir.

	2 - Yeni bir bellek bloğu allocate etti. eski bellek bloğundakileri 
	yeniye kopyaladı, eski bloğu free edip yenisini return etti.

	NOT: Önce 1 i dener olmazsa, sonra 2. yi dener diye birşey yok.
	Burada bir algoritma var ve o karar veriyor neyi nasıl yapacağına.

	3 - Büyütmede başarısız olunması. bu durumda NULL ptr döner ama eldeki
	bellek bloğunuda geri vermiyor. Büyüteyim derken eldekini kaybettim riski yok.
	yani geri dönüş değeri ile ilk parametre aynı adres olmayabilir.

	-----------------------------------------------------------------------------

	Dinamik bellek bloğu ile elde edilmemiş bir alanı realloc ile büyütmeye veya
	küçültmeye çalışmamalıyız. UNDEFINED BAHAVIOR.

	ÖR:

	int main()
	{

		size_t n;
		size_t n_add;

		int* pd;

		printf("kac tamsayi \n");
		scanf("%zu", &n);
		// static kod analizi yapan programlar var. Bunlar kod kalitesi için analiz
		// yapıyor. Microsoftun da kendi analiz programı var. Bu herşeye uyarı verebilir.
		//kapatmak mantıklı olabilir.

		pd = (int*)malloc(n * sizeof(int));
		if (!pd)
		{
			fprintf(stderr, "bellek uyarisi\n");
			return 1;
		}

		randomize();
		set_random_array(pd, n);
		print_array(pd, n);

		printf("kac eleman eklenecek\n");
		scanf("%zu", &n_add);

		pd = (int *)realloc(pd, (n + n_add) * sizeof(int));
		if (!pd)
		{
			fprintf(stderr, "Bellek Uyarisi\n");
			return 1;
		}

		set_random_array(pd + n, n_add);
		print_array(pd, n + n_add);


		free(pd);
	}
	--------------------------------------------------------------------
	--------------------------------------------------------------------

	realloc ya diziyi büyütür ya da yeni bir yerde büyütülmüş boyutta bir
	dizi yaratıp adres verir.

	Bunun örneği

	int main()
{
	size_t n;
	size_t n_add;
	int* pd;

	printf("kac tamsayi \n");
	scanf("%zu", &n);
	// static kod analizi yapan programlar var. Bunlar kod kalitesi için analiz
	// yapıyor. Microsoftun da kendi analiz programı var. Bu herşeye uyarı verebilir.
	//kapatmak mantıklı olabilir.

	pd = (int*)malloc(n * sizeof(int));
	if (!pd)
	{
		fprintf(stderr, "bellek uyarisi\n");
		return 1;
	}

	printf("ilk elde edilen bellek blogunun adresi : %p\n",pd);
	printf("kac eleman eklenecek\n");
	scanf("%zu", &n_add); // küçük ve büyük alan ekleyerek dene.

	pd = (int*)realloc(pd, (n + n_add) * sizeof(int));
	if (!pd)
	{
		fprintf(stderr, "Bellek Uyarisi\n");
		return 1;
	}

	printf("ilk elde edilen bellek blogunun adresi : %p\n", pd);

	free(pd);

}

-----------------------------------------------------------------------------
-----------------------------------------------------------------------------

REALLOC ile küçültme Örneği

	int main()
	{
		size_t n;
		size_t new_size;
		int* pd;

		printf("kac tamsayi \n");
		scanf("%zu", &n);
		// static kod analizi yapan programlar var. Bunlar kod kalitesi için analiz
		// yapıyor. Microsoftun da kendi analiz programı var. Bu herşeye uyarı verebilir.
		//kapatmak mantıklı olabilir.

		pd = (int*)malloc(n * sizeof(int));
		if (!pd)
		{
			fprintf(stderr, "bellek uyarisi\n");
			return 1;
		}

		randomize();
		set_random_array(pd, n);
		print_array(pd, n);
		printf("ilk elde edilen bellek blogunun adresi : %p\n",pd);

		printf("Son halde kac eleman olacak\n");
		scanf("%zu", &new_size);
		pd = (int*)realloc(pd,new_size * sizeof(int));
		if (!pd)
		{
			fprintf(stderr, "Bellek Uyarisi\n");
			return 1;
		}


		set_random_array(pd, new_size);
		print_array(pd, new_size);
		printf("ilk elde edilen bellek blogunun adresi : %p\n", pd);
		free(pd);

	}

	-----------------------------------------------------------------------------
	-----------------------------------------------------------------------------

	İki adet bilgi var.
	1 - Reallocation takes time ! 
	Maaliyetli bir işlem yani zaman alıyor demektir bu.
	mesela 100mb veriyi 10byte büyütmek için muhtemelen başka bir veri bloğu yaratıp dataları yeni yere kopyalayıp
	eski memory bloğunu free edecek. Maliyeti büyük.

	sürekli realloc yapmak demek bunu sürekli yapmak demek, ciddi performans problemleri ortaya çıkabilir.

	2 - Realocation invalidates pointers!
	realloc free işlemi yaptığı için, varolan pointerı invalid hale getiriyor.
	bizde buraya erişme girişiminde bulunursak UB oluşur.

	Bunu bilinçli olarak biz yapmıyoruz

	ÖR:
	int *pd = create_Array(100); bu dinamik bir dizi oluşturan fonksiyon.
	int *p = pd + 56;

		increase_array_size(pd,300); uydurma fonksiyon. mesela bu dizinin boyutunu 300 e çıkardı.

	artık p inceki dizinin 56 indisli elemanını göstermiyor. Çünkü dizi muhtemelen taşındı.
	p muhtemelen dangling/invalid hale geldi.
	------------

	ÖNEMLİ
	------
	1- realloc(pd,100) -> pd = NULL ise, bu UB değil.well-defined behavior.
	reallocun 1. parametresine NULL ptr geçersek bu artık malloc gibi davranır.yani malloc(100) e eşdeğerdir.

	2- realloc(pd,n)  -> n = 0 ise UB değil. Implementation Defined. Benim derleyicide free(pd) gibi davranr.

	burada normalde döngü dışında malloc yazıp, sonra döngü içinde realloc yazmak yerine direkt döngü içinde realloc ile
	devam edilebilir.bu sayede döngü dışındaki malloca gerek kalmadan realloc ilk seferinde malloc işlevi yapar ve realloc ile
	diğer turlarda devam eder.döngü dışındaki başka koda bağımlı hale gelmez

	Öbür türlü eksiltme işlemlerinde ise en son turda free çalışır.azalta azalta 0 a gelir çünkü.
	Döngü dışındaki başka koda bağımlı hale gelmez.


	GÜZEL BİR ÖRNEK
	---------------


	int c;
	int val;
	int* pd = NULL;
	int size= 0;

	randomize();

	for (;;)
	{

		printf("tamsayi girecek misiniz (e) (h) : ");
		while ((c = _getch()) != 'e' && c != 'h')
			;

		printf("%c\n",c);
		if (c == 'h')
			break;

		printf("tamsayiyi girin : ");
		val = rand() % 1000;
		printf("%d\n", val);

		pd = (int*)realloc(pd,(size + 1) * sizeof(int));
		
		if (!pd)
		{
			fprintf(stderr, "Bellek hatasi\n");
			return 1;
		}

		pd[size++] = val;
	}


	if (!size)
		printf("Hic deger girilmedi\n");
	else
	{
		printf("%d adet sayi girildi\n", size);
		print_array(pd, size);
		(void)getchar();
		printf("siralanmis hali\n");
		bsort(pd, size);
		print_array(pd, size);
		free(pd);
	}

	---------------------------------------------------------------------------------
	---------------------------------------------------------------------------------
	---------------------------------------------------------------------------------

	ÖDEV

	isim girilecek (e) (h) 
	isim girin : Ali

	isim girilecek (e) (h)
	isim girin : veli

	isim girilecek (e) (h)
	isim girin : MEHMET

	isim girilecek (e) (h)
	isim girin : Ali     -> bu isim daha önce girildi yeniden deneyin

	---------------------------

	toplam x adet isim girdiniz. Girilen isimler alfabetik sırada yazılacak.

	geri verilmemiş bellek bloğuda kalmayacak.


	===============================================================================
	===============================================================================
	===============================================================================
	===============================================================================

	Tipik hatalar
	
	1- Dinamik bellek bloğunu geri vermemek.memory leak
	2- Dinamik bellek bloğu free edildi.sonrada bu ptr nin gösteridği nesneye erişilmeye çalışıldı.
	Dereference etmek. UNDEFINED BEHAVIOR
	3- Dİnamik bellek bloğunun adresini başka fonksionlara kopyaladık, free ettik ama diğer kodların 
	bundan haberleri yokken 
		a - invalid pointerı kullandılar. UB
		b - onlarda free etti.	UB
	4- Dinamik bellek bloğunu realloc ile büyütmeye çalıştık, sanki aynı yerde büyüyecek gibi yazdık kodu,
	ama dizi başka bir yere taşınınca UB oluştu.
	5- Dinamik olmayan bellek bloğunu realloc ile büyütmeye çalışmak UB.

	Bazı programlarda heapten alınarak kullanmış bir alan olsun, free ile geri versek bile oradaki byte lar
	orada duruyor olabilir.Bu da güvenlik açığı oluşturabilir. bu memory bloğunun free etmeden önce clear
	edilmesi(memset(pd,0,size * sizeof(int))) gerekir, sonra free edilir.



	===============================================================================
	===============================================================================
	===============================================================================
	===============================================================================
	===============================================================================

	DİNAMİK DİZİ / DYNAMIC ARRAY DATA STRUCTURE
	-------------------------------------------

	Mantıksal ilişkideki veriler, herzaman memoryde tutuluyorlar.
	Bu verilerin memory de nasıl tutulacağı bilgisine data structure deniyor.

	dynamic array 
	linked list
		-singly linked list
		-doubly linked list
		-rotating linked list
	trees
		binary search tree
	hash tables
		hash-maps
		hash-set

	yurtdışı mülakatlarda çok önemli.

	Bunlardan en önemlisi halen daha dynamic array.Çünkü %70 bu kullanılıyor.
	C++ ta bunu yöneten sınıfa vector deniyor.

	Avantajı index bilgisiyle verilere erişebiliyoruz.

	Bu tür dizilere sondan eleman eklemek constant time O(1) karmaşıklığında.
	Araya eleman ekleme ise O(n) karmaşıklığında çünkü kaydırma yapmak gerekiyor.

	bizim önceki kodda constant time değil çnkü her döngüde realloc çağrılıyor.
	habire bellek kopyalanıyor biryerden başka bir yere.

	dinamik dizide bunun O(1) karmaşıklığında olabilmesinin sebebi birer birer allocate etmiyor.
	bir seferde %50 fazlasını allocate edip ona göre işlem yapıyor.
	eleman yazıldığında ise tekrar büyütmeye ihtiyaç kalmıyor.

	Yani
	dizi boyutu Capacity
	dizideki eleman sayısı Size 

	capacity sürekli size dan çok daha büyük tutuluyor.size, capacity ye eşit olana kadar realloc yok.

	size = 19 capacity = 20
	size = 20 capacity = 20
	reallocation
	size 21 capacity 40
	...

	bu şekilde gider.Olayı sürekli realloc yapmamak.fazla artırıyorki habire yapmasın diye.
	reallocta baya maliyetli çünkü. dinamik dizi veri yapısında amortised constant time diye geçiyor.

	KENDİ DYNAMIC ARRAY KODUNU YAZDI HOCA, BEN YAZMIYORUM. 1.30

	Caching de programlamada çok önemli bir mekanizma.cpu cache memory ye göre çok daha hızlı.
	erişilmek istenen nesne cache de ise buna cache hit deniyor.Cache hit oranı dinamik dizide 
	daha yüksek olması sebebiyle de tercih ediliyor.

	cache hitin tersi cache miss.

	c++ ta cache mekanizması hazır.C de yok :D
	kendimiz yazacağız.


	===========================================================================
	===========================================================================
	===========================================================================
	===========================================================================
	===========================================================================
	===========================================================================


	STORAGE CLASS SPECIFIERS AND TYPE MODIFIERS

	//storage class specifiers
	auto
	register
	static
	extern

	//type modifiers
	const
	restrict (C99)
	volatile

	------------------------------------

	auto -> C de kullanımdan düşmüş bir keyword. C++ ta kullanılıyor.
			Yerel değişkenler otomatik veya static ömürlü olabilir. auto otomatik ömürlü olduğunu gösteriyor.
			Artık auto ile nitelenmemiş bir bildirim, otomatik olarak tanımlanır. 
			
			int main(){
				int x = 10; int burada static ömürlü olur
				//auto int x = 10; hiçbir fark yok yukarısı ile
			}

			global değişken otomatik ömürlü olamayacağı için global scope ta tanımlanırsa sentaks hatası verir.

			Ayrıca fonksiyonların parametre değişkenleri otomatik ömürlü olduğu için  burada da auto kullanmaya 
			gerek yok.

			int func(auto int x) //auto olsada olur olmasada olur.


	register -> auto kadar olmasa da kullanımdan düşmüş. spesifik bir mikroişlemci varsa belki kullanılabilir.
				eski kodlarda kullanılıyordu.

				türkçesi yazmaç demek. işlemci üzerinde bununan ve işlemcideki işlemlerin 
				fiilen yapıldığı bellek alanıdır.
				
				32 bit işlemcilerin yazmacı 32 bit, 64 bitin yazmaçları 64 bit.
				Cache ile karıştırmamak lazım.

				Aşağıdaki tanım bir ricadır.Çünkü yerine getirmek compilera bağlıdır.
		  Rica: Derleyici senin içinde uygunsa x i işlemcinin yazmacında tutacak şekilde kod üret.
				register int x = 10;
				rica dememizin sebebi, böyle yazsak bile compiler uygun görmezse bunu registerda tutmayabilir.


		  a - Neden ? işlemcinin işlemi yapması için bu değeri yazmaca alması gerekiyor. Eğer x i yazmaca zaten alırsa
					x i memory den yazmaca tekrar çekmesine gerek kalmayacak. Bu da maaliyet zaten.Bu maliyeti ortadan
					kaldırıyor.

		  b - Neden kullanımdan düştü ? 
			  compiler zaten en iyi optimizasyonu kendi yapıyor. 
			  İnsandan çok çok daha iyi yapıyor. 

			  for(register int i = 0; i < 1000000; i++)
			  {}

			  Derleyici bu kodu görse, ağzı dili olsa, dalga geçermiş :D
			  sen bırak bu register işlerini bana, sen kodunu yaz demek istiyor.
			  Senden çok daha iyi yaparım ben kimi registera alacağımı diyor :D

			  NOT : Register int x = 10; yazılsa bile compiler bunu yapmayabilir.

			  NOT : Global değişkenleri register ile tanımlamak sentaks hatası
					yine eski bir microişlemci kullanılırsa burada da dökümantasyonda
					kullanılacağı yazıyorsa, kullanılabilir.


					register adreslenebilir bir bellek alanı değil.
					
					register int x = 10;
					int *ptr = &x;
					Bu sentaks hatası


				C++ ta register'ın kullanımı resmi olarak dilden kaldırıldı.



	static -> C de overload edilmiş. Birden fazla anlamı var.
				global scope ta tanımlanırsa eğer private gibi, sadece aynı file dan erişilebilir.
				local scope ta tanımlanırsa bu nesne static ömürlü olur.Programın başından sonuna kadar
				hayatını sürdürür.


	
	*/


int main()
{
	
	
}