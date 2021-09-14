#define _CRT_SECURE_NO_WARNINGS
#include "nutility.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

/*
	void * malloc(size_t name);
	runtime da dnamik bellek bloğu ayırıp bunun adresini return ediyor.
	kesinlikle verecek diye birşey yok.size çok büyükse veremeyebilir.
	bu durumda da NULL pointer veriyor.

	Malloc ile bellek ayrılan alana heap deniyor.
	C++ ta free store deniyor.

	Malloc un geri dönüş değeri mutlaka test edilmeli
	Malloc bellek bloğunu garbage value lar ile veriyor.
	daha sonrasında memset ile datalar 0 lanabilir.

	eğer tüm veriler 0 yazılı halde verilsin istenirse
	calloc çağrılabilir.

	ÖR:

	int main()
{
	int* pd;
	int n;

	printf("kac adet tamsayi: ");
	(void)scanf("%d", &n);

	if (!(pd = (int*)malloc(sizeof(int) * n)))
	{
		fprintf(stderr, "Yetersiz bellek alani!\n");
	}

	(void)memset(pd, 0, n*sizeof(int)); // memset yapılmazsa garbage value görülür.
	set_random_array(pd, n);
	print_array(pd, n);

}

------------------------------------------------------------
------------------------------------------------------------
------------------------------------------------------------
	
	Sıksık malloc çağrılacaksa içine mallocu yazdığımız ve bu işi yapan 
	bir fonksiyon yazmak gerekir.

	bu tip fonksiyonlara wrapper deniyor.

	void func(void);

	void foo(void)
	{
		//code
		func();
		//code
	}

	------------------------------------------------------------
	------------------------------------------------------------
	------------------------------------------------------------

	void func(int x, int y, double d);

	void sfunc(double d, int x, int y)
	{
		func(x,y,d); //bu şekilde de parametreleri istediğimiz sırada 
						// çağırabiliriz.
	}

	-------------------------------------------------------------

	veya aşağıdaki gibi parametreleri azaltarakta çağrılabilir.

	void func(int x, int y, int z);
	void wfunc(int x, int y)
	{
		func(x,y,0);
	}

	-------------------------------------------------------------

	NOT: Malloc ile çağrılmış bellek blokları ard arda gelecek diye bir şey yok.
	malloc ile daha önce yaratılan bellek bloğu büyütülmez, realloc ile büyütülür.
	
	void* checked_malloc(size_t n)
	{
		void* vp = malloc(n);
		if (!vp)
		{
			fprintf(stderr, "bellek yetersiz\n");
			exit(EXIT_FAILURE);
		}

		return vp;
	}


	int main()
	{
		int* pd;
		int n;

		printf("kac adet tamsayi: ");
		(void)scanf("%d", &n);

		pd = checked_malloc(n * sizeof(int));

	}

	-------------------------------------------------
	-------------------------------------------------
	-------------------------------------------------

	ÇOK ÖNEMLİ

	malloc ile bellek alanları ayrılabilir.Bu dinamik memory metodu ile ayrılan
	blokları bir şekilde bir veri yapısında kaydı tutulmalı. Bu veri yapısı da 
	heapten alan harcar. 

	mesela 1500 byte lık alan allocate ettim. birde 24 byte lık bir veri yapısı 
	olsun. totalde 1524 byte yer kullanılmış oldu.

	Bu alana METABLOCK veya HEADER denir.
	burada ilgili blok ile ilgili bilgiler var.
	ne kadar çok ufak alanlar elde edilirse, o kadar da kendi veri yapısı
	için alan harcanıyor. Çok sayıda bellek alanı, az sayıda memory alanına
	göre daha fazla header alanı kaplıyor.

	bir pointer hatası yapılırsa, yani bana ait olmayan bir alana bir bloğa
	veri aktarılırsa, sistemin kullandığı header kısmına veri yazılmış olabiliriz.
	bu durumda dynamic memory management tamamen çöker.Corrupt olur, bozulur.

	Heap Alanının Fragmantation Durumu
	Heap ten çok fazla alan alındığında, ardışık olarak 50.000 byte olmayabilir 
	ama 50.000 byte toplamda yer olabilir. burada alan fragmante oluyor.

	Sisteme yer verilene kadar, o alanı başka birinin kullanması mümkün değil.
	bu geri verme işlemine free ya da deallocate deniyor.

	free edilmezse memory, memory leak oluşuyor.Yani bellek sızıntısı.
	bu oluşursa memory de işi yapabilmek için yer kalmıyor artık.

	Programın işi bitti kapandı ama alınmış alanları free etmedik diyelim.
	Program tekrar çalışırsa o bellek alanları sanki hiç alınmamış gibi 0 km olarak
	bize ait ve kullanılabilir. 

	-------------------------------------------------------------------
	-------------------------------------------------------------------
	-------------------------------------------------------------------
	-------------------------------------------------------------------

	FREE FONKSİYONU

	void free(void *vp)
	Daha önce dinamik olarak alınmış bloğu free ile geri verebiliriz.
	free ye sadece adres geri verilir.Büyüklüğü header/metablock içinde tutulur.

	int main()
	{
		int* pd;
		size_t n;

		printf("kac adet tamsayi: ");
		(void)scanf("%zu", &n);

		pd = (int *)checked_malloc(n * sizeof(int));
		set_random_array(pd, n);
		print_array(pd, n);
		free(pd);
	}

	--------------------------------------------------------------
	--------------------------------------------------------------

	FREE FUNCTION İLE İLGİLİ UNDEFINED BEHAVIOR DURUMLARI ve TİPİK HATALAR.

	1- free fonksiyonuna dinamik olarak elde dedilmemiş adres bloğu göndermek
		UNDEFINED BEHAVIOR
		
		int a[10];
		free(a); // UB

	2- free ile geri verilen bellek bloğunun adresi geçersiz/invalid bir adrestir.
		Böyle bir pointer değişkeni ona yeni atama yapmadan asla kullanmamalıyız.
		Artık buna dangling pointer deniyor.Bir nesneyi gösteriyordu ama artık
		o nesne öldü, bu sebeple bu bir dangling pointerdır
		free den sonra sonra pd geri verildi. adres aynı değişmedi ama artık
		geri verildi.Artık geçersiz bir pointer.
		Evde kiracısın ama kontrat bitmiş.başına ne gelir kim bilir :D
		print_array(pd,n); dereference et yada etme. Her durumda UNDEFINED BEHAVIOR.
	
		pd = (int *)checked_malloc(n * sizeof(int));
		int *p = pd;

		free(pd); -> burada hem pd hemde p dangling pointer haline geldi.
		hem p hemde pd yi kullanmak UNDEFINED BEHAVIOR.çünkü ikiside aynı adresi
		kullanıyor.
	
		Burada yapılan şey free edildikten sonra
		pd = NULL; yapılır. Dereference etmemek gerekir tabi.
		bu sayede dangling pointer olmaktan çıkarır.
		NULL hiçbiryeri göstermeyen geçerli pointer dangling ise geçersiz.
		pd = &x; yapılabilir. Bunu telegramda hocaya sordum.

	3- Dinamik bellek bloğunun adresi free den sonra geçersiz bir adres.
	bu adresi tekrar free etmek te geçersiz. UB

		pd = (int *)checked_malloc(n * sizeof(int));
		int *p = pd;

		free(p);
		//code
		free(p);  // buna double deletion deniyor.


	4- malloc ile elde edilen bellek bloğunu free işlemi ile küçültme girişimi.
		free(pd + n/2); burası kesinlikle UNDEFINED BEHAVIOR örneği


		int main()
		{
			int* pd;
			int n;

			printf("kac adet tamsayi: ");
			(void)scanf("%d", &n);

			if (!(pd = (int*)malloc(sizeof(int) * n)))
			{
				fprintf(stderr, "Yetersiz bellek alani!\n");
				return 1;
			}
			randomize();
			set_random_array(pd, n);
			print_array(pd, n);
			free(pd); // burada sorun yok ama bazıları 
			//free(pd + n/2); burası kesinlikle UNDEFINED BEHAVIOR
			// print_array(pd,n/2); burasıda UNDEFINED BAHAVIOR oluyor artık.
		}


	5- malloc ile elde edilen bellek bloğunu geri vermemek yanlış.(memory leak)
		Elde ettiğimiz dinamik bellek bloğunu programın sonuna kadar
		free etmemeniz memory leak değildir.Çünkü memory kalmadı artık program bitti :D

		a - kodu okuyanlar için
		b - test işlemleri için
		c - static kod analizi yapan programlar için
		d - dinamik kod analizi yapan programlar için
		
		Elde ettiğimiz tüm bellek bloklarını geri vermeliyiz.
		alışkanlık haline getirmek lazım.
		zaten program bitiminde free memory boşaltılıyor.
		Sorun oluşturabilecek durumlar oluşabilir bu sebeple free ile
		vermek gerekir.

		
		NOT: free function a NULL pointer geçilmesi tanımsız davranış değildir.
		Tanımlı davranıştır. Defined behavior.

		pd = NULL;
		free(pd); UB değil

		void my_free(void *vp)
		{
			if(vp == NULL)
				return ;
		}

		Eğer malloc fonksiyonuna 0 değeri ile çağrı yapılırsa
		malloc(0) -> UB DEĞİL ama ne olacağı UNSPECIFIED BEHAVIOR

		a- Derleyici NULL döndürtebilir 
		b- Bir adresi döndürtebilir.
		
		Dereference edilmemelidir.
		Free ye göndermek UB değildir.

			pd = NULL;
		free(pd); UB değil

		void my_free(void *vp)
		{
			if(vp == NULL)
				return ;
		}
		free(vp); //UB değil.

		 
	NOT:	int x = 10; 
			int *vp = &x;
			
			*vp; burası hata değil.İngnç bir şekilde standartlarda yazıyor.
			     ama etkisiz kod. normalde void * türünü dereference edip 
				 bir operatörün operandı yapınca sentaks hatası.
			
			*vp = 56; burası hata 	 

	-------------------------------------------------------------
	-------------------------------------------------------------
	-------------------------------------------------------------
	-------------------------------------------------------------
	-------------------------------------------------------------

	FABRİKA FONKSİYONLARI
	Nesne oluşturan fonksiyon demek.
	Bir kod kendisini çağıran kod için dinamik ömürlü bir nesne oluşturur.
	Bu nesneye değer yükler ve bu nesnenin adresini döndürür.

	ÖR:
	_strdup fonksiyonu.standart değil.string.h de olacak derleyici veriyorsa.
	char *_strdup(const char *p);

	bir fonksiyonun dinamik ömürlü nesne adresini döndürdüğünü dökümantasyondan
	anlayacağız. başka türlü değil.

	EĞER Bir fonksiyonun geri dönüş değeri adres ise
	------------------------------------------------
	1 - static ömürlü nesne döndürüyor olabilir.
		a - global bir nesne adresi olabilir
		b - static local bir nesne adresi olabilir
		c - String literali olabilir.
	2 - dinamik ömürlü bir nesne adresi döndürüyor olabilir.
	3 - çağıran fonksiyondan aldığı adresi geri döndürüyor olabilir.
	
	mesela strchr bunlardan 3. olana uyuyor.
	ama _strdup 2. olana uyuyor çünkü return deüeri dinamik ömürlü nesne adresi.


	void* my_strdup(const char* p)
	{
		char* pd = (char*)malloc(strlen(p) + 1);
		if (!pd)
		{
			fprintf(stderr, "bellek yetersiz\n");
			exit(EXIT_FAILURE);
		}
	
		return strcpy(pd, p);
	}

	int main()
	{
		char str[100];
		char* pd;
		printf("bir cumle giriniz\n");

		sgets(str);
		pd = my_strdup(str);

		printf("(%s) (%s)\n", str, pd);
		_strrev(str);
		printf("(%s) (%s)\n", str, pd);

		free(pd); // bunu yazmasak memory leak olacaktı.biz malloc kullanmadık ama
				// strdup yazının kopyası için malloca çağrı yapması gerekiyor.
				// bizde bunu sonlandırıyoruz. Yani malloc çağıran fonksiyonlarıda
				// bilmek lazım

	}


	----------------------------------------------------------------------
	----------------------------------------------------------------------

	ÖRNEKTEKİ LOGIC HATAYA DİKKAT.

	char* get_name(void)
	{
		static char name[100];
		printf("bir isim giriniz :");
		(void)scanf("%s", name);
		return name; // her seferinde adres gönderir ve adres hep aynı.
	}				// en son bu adrese yazılan isim ne ise hepsine de onu yazar.
					// fonksiyonda hata yok.çağıranda hata var.


	int main()
	{
		char* pa[5];

		for (size_t i = 0; i < 5; i++)
			pa[i] = get_name();


		printf("\n\nKaydedilen isimler\n");
		for (size_t i = 0; i < 5; i++)
			printf("%s",pa[i]);
	}

	AŞAĞIDAKİ GİBİ YAZILIRSA DAHA MANTIKLI OLABİLİR.

	int main()
	{
		char *p;

		for(int i = 0; i < 5; i++)
		{
			p = get_name();
			puts(p);
		}
	
	}

	------------------------------------------------------------

	EĞER DİNAMİK BELLEK YÖNETİMİ İLE YAPARSAK
	Tüm sorunu ortadan kaldırmış oluyoruz.

	cchar* get_name(void)
	{
		static char name[100] = {0}; // malloc taki uyarıyı kaldırmak için 0 yaptım
		printf("bir isim giriniz :");
		(void)scanf("%s", name);

		char* pd = (char*)malloc(strlen(name) + 1); // bunun sayesinde artık tüm veriler
		if (!pd)								// malloc ile elde edilmiş ayrı bir bellek
		{										// alanının adresini tutuyor.diğeri gibi tüm elemanlar aynı adresi göstermeyecek.
			fprintf(stderr, "Bellek yetersiz\n");
			exit(EXIT_FAILURE);
		}

		return strcpy(pd, name);
	}

	int main()
	{
		char* pa[5];

		for (size_t i = 0; i < 5; i++)
			pa[i] = get_name();


		printf("\n\nKaydedilen isimler\n");
		for (size_t i = 0; i < 5; i++)
			printf("%s ",pa[i]);


		// burada da her fonksiyon çağrısından elde ettiğimiz char * türündeki
		// memory adresini free ile geri vermemiz gerekir.
		for (size_t i = 0; i < 5; i++)
			free(pa[i]); // burası olmasaydı memory leak olacaktı.

	}

	--------------------------------------------------------------
	--------------------------------------------------------------

	// aşağıdaki fonksiyon iki adet yazı adresini alıp bunu dinammik bir bellek
	alanında birleştirip adresini geri döndürecek

	char* concat(const char* p1, const char* p2)
	{
		char* pd = (char*)malloc(strlen(p1) + strlen(p2) + 1);
		if (!pd)
		{
			fprintf(stderr, "Bellek hatasi\n");
			exit(EXIT_FAILURE);
		}
		return strcat(strcpy(pd, p1),p2);

	}


	int main()
	{
		char s1[100];
		char s2[100];
		char* pd;

		printf("birinci yazi \n");
		sgets(s1);
		printf("ikinci yazi \n");
		sgets(s2);

		pd = concat(s1, s2);

		printf("(%s) + (%s) = (%s)\n", s1, s2, pd);
		_strupr(pd);
		printf("(%s) + (%s) = (%s)\n", s1, s2, pd);

		free(pd); // memory leak olmasın diye 

	}


	-------------------------------------------------------------------------------
	-------------------------------------------------------------------------------
	-------------------------------------------------------------------------------
	-------------------------------------------------------------------------------
	-------------------------------------------------------------------------------
	-------------------------------------------------------------------------------

	CALLOC FONKSİYONU

	void *calloc(size_t n, size_t sz);
	calloc memory allocate edip bir de 0 yazıyor hepsine
	birde calloc ta iki parametre değişkeni var.
	sz -> byte size bilgisi
	n -> adet bilgisi.

	malloc(n*sizeof(int))
	calloc(n,sizeof(int))  çağrılırken aradaki tek fark bu.


	ÖR:

	int main()
{
	size_t n;
	int* pd;

	printf("Kac tamsayi \n");
	(void)scanf("%d", &n);

	randomize();
	//pd = (int*)malloc(sizeof(int)*n);
	pd = (int*)calloc(n,sizeof(int));

	if (!pd)
	{
		fprintf(stderr, "Bellek hatasi\n");
		return 1;
	}

	//memset(pd, 0, n * sizeof(int)); // malloc ile memory allocate edilip memset ile 0 yazılabilirdi.
	print_array(pd, n);

}

----------------------------------------------------------------------------------------------

	Eğer int* p[n] gibi bir diziyi dinamik olarak allocate edersek aşağıdaki gibi yazarız.

	int **pd = (int**)malloc(n * sizeof(int *));

	Eğer matris oluşturacalsak ve satır sütun sayısı runtime da belli olacak.

	ÖNEMLİ ÖRNEK:

	int main()
	{

		int row, col;
		int** pd;
		printf("matrisin satir ve sutun sayilarini girin : \n");
		(void)scanf("%d%d", &row, &col);

		pd = (int**)malloc(row * sizeof(int*)); // dizinin elemanlı bir ptr dizisi bu aslında
		if (!pd)
		{
			fprintf(stderr, "bellek yetersiz\n");
			exit(EXIT_FAILURE);
		}

		for (int i = 0; i < row; i++)
		{
			pd[i] = (int*)malloc(col * sizeof(int)); // bu sefer int** değil. zaten o dizinin içindeyiz.
			if (!pd[i])
			{
				fprintf(stderr, "bellek yetersiz\n");
				exit(EXIT_FAILURE);
			}
		}											// burada dizinin elemanı olan diziler için yer ayırıyoruz.


		randomize();

		for (int i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col; j++)
				pd[i][j] = rand() % 10;	// buradaki matris elemanları ardışık değil.
		}								// dinamik bellek yönetiminde ardışık adres garantisi yok.


		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
				printf("%d ", pd[i][j]);
			printf("\n");
		}

		// elemanların ardışık olmasının garanti olmadığının ispatı
		int* p = pd[0];
		int n = row * col;
		while (n--)
		{
			printf("%d ",*p++);
			_getch();

		}


		for (int i = 0; i < row; i++)
		{
			free(pd[i]); // memory leak olmasın diye ilk önce içerisindekileri free ettik.
		}
		free(pd); // sonra burayı.
}

---------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------

int main()
{

	// tek bir bellek bloğu ile yapılacak ama [] operatörünü 2 kere kullanamayız.
	// tek boyutlu diziyi iki boyutlu gibi düşünüp hareket etti.


	int row, col;
	int* pd;
	printf("matrisin satir ve sutun sayilarini girin : \n");
	(void)scanf("%d%d", &row, &col);

	pd = (int*)malloc(row * col * sizeof(int));
	if (!pd)
	{
		printf("Bellek yetersiz \n");
		return 1;
	}

	// tek boyutlu dizi ama 2 boyutlu dizi gibi kullanacak
	for (int i = 0; i < row; i++)
	{
		for (int k = 0; k < col; k++)
		{
			pd[i * col + k] = rand() % 10; //daha öncede bu yazılmıştı.
		}
	}

	// kodlar
	// kodlar

	for (int i = 0; i < row; i++) // i < row*col ile de yapılabilirdi.ama matris formunda olsun diye
	{								// bu formatta yazdı.
		for (int k = 0; k < col; k++)
		{
			printf("%d ", pd[i * col + k]); //daha öncede bu yazılmıştı.
		}
		printf("\n");
	}

	while (n--)
	{
		printf("%d ", *p++);
		_getch();
	}

	free(pd);
}


------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------

int main()
{

	// 3. teknikte var.Bu da şu. Tek boyutlu dizi oluşturduk
	// ama bir tanede ptr dizisi oluşturuyoruz.



	int row, col;
	int* pd;
	printf("matrisin satir ve sutun sayilarini girin : \n");
	(void)scanf("%d%d", &row, &col);

	pd = (int*)malloc(row * col * sizeof(int));
	if (!pd)
	{
		printf("Bellek yetersiz \n");
		return 1;
	}

	// tek boyutlu dizi ama 2 boyutlu dizi gibi kullanacak
	for (int i = 0; i < row * col; i++)
	{
			pd[i] = rand() % 10;
	}

	int** pp = (int**)malloc(row * sizeof(int*));
	//control kodu

	for (int i = 0; i < row; i++)
		pp[i] = pd + i * col; // dizin içindeki oluşturulmuş satır adreslerini verdi.

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			printf("%d ", pp[i][j]);
		}
		printf("\n");
	}

	free(pd);
	free(pp);

}





*/


void* checked_malloc(size_t n)
{
	void* vp = malloc(n);
	if (!vp)
	{
		fprintf(stderr, "bellek yetersiz\n");
		exit(EXIT_FAILURE);
	}

	return vp;
}




void* my_strdup(const char* p)
{
	char* pd = (char*)malloc(strlen(p) + 1);
	if (!pd)
	{
		fprintf(stderr, "bellek yetersiz\n");
		exit(EXIT_FAILURE);
	}

	return	strcpy(pd, p);
}


char* get_name(void)
{
	static char name[100] = {0}; // malloc taki uyarıyı kaldırmak için 0 yaptım
	printf("bir isim giriniz :");
	(void)scanf("%s", name);

	char* pd = (char*)malloc(strlen(name) + 1); // bunun sayesinde artık tüm veriler
	if (!pd)								// malloc ile elde edilmiş ayrı bir bellek
	{										// alanının adresini tutuyor.diğeri gibi tüm elemanlar aynı adresi göstermeyecek.
		fprintf(stderr, "Bellek yetersiz\n");
		exit(EXIT_FAILURE);
	}

	return strcpy(pd, name);
}


char* concat(const char* p1, const char* p2)
{
	char* pd = (char*)malloc(strlen(p1) + strlen(p2) + 1);
	if (!pd)
	{
		fprintf(stderr, "Bellek hatasi\n");
		exit(EXIT_FAILURE);
	}
	return strcat(strcpy(pd, p1),p2);

}



int main()
{
	
	
		
}