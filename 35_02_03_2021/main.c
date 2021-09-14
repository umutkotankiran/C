#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "nutility.h"
#include <string.h>
#include <stdlib.h>

#define		SIZE		20

void* my_memset(void* vp, int val, size_t n)
{
	char* p = (char*)vp;
	
	while (n--)
		*p++ = (char)val; // p char dizi olduğu için içine atanacak değeride char a cast ettik.
	return vp;
}


void* my_memcpy(void* vpdest, const void* vpsource, size_t n)
{
	char *pdest = (char*)vpdest;
	const char *psource = (const char*)vpsource;

	while (n--)
		*pdest++ = *psource++;
	
	return vpdest;
}


char* strprepend(char* pdest, const char* psource)
{
	size_t len_source = strlen(psource);
	size_t len_dest = strlen(pdest);
	memmove(pdest + len_source, pdest, len_dest + 1); //aslında dizinin başından kopyalayacağım
													// yazı kadar kaydırıyor elemanları
													// boşalan yere source yazısını koyacak.
													//overlapped block ama UB yok.

	memcpy(pdest, psource, len_source); // kaydırdığım yere de source u kopyaladı.
	return pdest;
}

void* my_memchr(const void* vp, int val, size_t n)
{
	const char* p = (const char*)vp;
	while (n--)
	{
		if (*p == val) // integral promotion. char türünden *p karşılaştırınca, int türüne promote edecek.
			return (char *)p; // ben burada void * a cast etmiştim ama hoca char * cast etti, 
		p++;					// sonrada otomatik olarak void * a dönüştürülecek dedi.
	}							// iki şekilde de denedim ve çalıştı.

	return NULL;
}

int my_memcmp(const void* vp1, const void* vp2, size_t n)
{
	const unsigned char* p1 = (const unsigned char*)vp1; // unsigned olarak kıyasladığını söylemiştik.
	const unsigned char* p2 = (const unsigned char*)vp2; // unsigned olarak kıyasladığını söylemiştik.

	while (n--)
	{
		if (*p1 != *p2) 
		{
			return *p1 > *p2 ? 1 : -1; // buradaki büyüklük, değerlerin büyüklüğü değil,
		}								// byteların kıyaslaması sonucu oluşan büyüklük.
		++p1, ++p2;						// Notlarda aşağıda yani var açıklaması.
	}

	return 0;

}

void* greverse(void* vpa, size_t size, size_t sz)// size = Gönderilen dizinin kaç elemanlı olduğunu söyler.Toplam bellek sizeof değeri değil.
{												// sz = tek bir elemanın sizeof bilgisi.			
	char* p = (char*)vpa;

	for (size_t i = 0; i < size / 2; i++)
	{
		//p + i * sz; // ÇOK ÖNEMLİ. int dizi ise . i, 1 olsun. 1*4 = 4 adresi, double ise 8
					// yani her seferinde verinin türüne bağlı olarak, o kadar bellek alanı
					// ileri gidiliyor.türünü bilseydik p++ derdik.Ama türü yok.
					// bellekte ne kadar gideceğini fonksiyona gelen veri türünden çıkarıyoruz.
		// p + (SIZE -i -1)*sz; de reverse edilirken kullanılan indis değeri.

		gswap(p + i * sz, p + (size - i - 1) * sz, sz);
		// yukarıdaki fonksiyon normalde 2 adet veriyi alır ve bir de veri size ını alır ve
		// bunları türden bağımsız olarak takas eder.
	}

	return vpa;
}		

void* gsearch(const void* vpa, size_t size, size_t sz, const void* vpkey)
{
	const char* p1 = (const char*)vpa;

	while (size--)
	{
		if (!memcmp(p1, vpkey, sz)) // memcpy nin de parametreleri zaten const void *
			return (char*)p1; // const char * dan char * a dönüştürelim. 
								// compilerda void * a otomotik dönüştürür.
		
		p1 += sz; // çünkü adam int ise 4 byttır. p++ demek char pointer da 1 byte ilerlemek demek
	}				// sz int ise 4 byte. bir bellek bloğu ilerlemek için p +1 yetersiz
					// p + sz dmeek lazım. Bu da zaten p + 4 demek.double olsaydı p + 8 di.

	return NULL;

}


void func(void)
{
	printf("func cagrildi\n");
}




int main()
{
	/*
	void pointers generic functionlarda kullanılıyor.
	Yani tür bilgisi belirtilmeyen fonksiyonlarda kullanılır.

	geçen ders yazdığımız fonksiyonu tekrar yazayım.
	
	void gswap(void* vp1, void* vp2, size_t size)
	{
		char* p1 = (char*)vp1; // otomatik dönüşüm zaten var ama C++ hata, burada da açık açık yazdık
		char* p2 = (char*)vp2;	// c++ uyumlu olsun diye.

		while (size--) // byte byte işleme sokuyor aslında.Char da 1 byte zaten.
		{
			char* ptemp = p1;
			*p1++ = *p2;
			*p2++ = *ptemp;
		}
	}
	BUNU NUTİLİTY ye ekliyorum.Std C library de bu fonksiyon yok.Kendimiz yazıyoruz.

	Şimdi test ediyorum
	int x = 10;
	int y = 20;
	printf("x = %d  y = %d\n", x, y);
	gswap(&x, &y, sizeof(int));
	printf("x = %d  y = %d\n", x, y); // yer değiştirdiğini görüyoruz

	double d1 = 54.51;
	double d2 = 8687.51;
	printf("d1 = %f  d2 = %f\n", d1, d2);
	gswap(&d1, &d2, sizeof(double));
	printf("d1 = %f  d2 = %f\n", d1, d2); // Aynı şekilde yer değiştirdiğini görüyoruz


	------------
	Diğer örnek

	int a[5] = { 1,2,3,4,5 };
	int b[5] = { -1,-2,-3,-4,-5 };
	gswap(a, b, sizeof(a)); // array boyutu kadar değişim yapacak.4*5 = 20 Byte. 20 kere
							// dönen bir döngü olacak ve char 1 byte olduğu için her seferinde
							// 1 er 1 er değişim yapacak.

	print_array(a,sizeof(a) / sizeof(*a));
	print_array(b,sizeof(b) / sizeof(*b));


	---------------------------------------------------------------------------------
	---------------------------------------------------------------------------------

	STANDART KÜTÜPHANENİN TÜRDEN BAĞIMSIZ İŞLEM YAPAN 5 FONKSİYONU
	STRING BAŞLIK DOSYASINDA BULUNUYOR.SİSTEM PROGRAMLAMADA ÇOK KULLANILIYOR.

	memset -> bellek bloğuna tamsayı yazar
	memcpy -> belle bloğuna kopyalama yapar
	memmove -> overlapped bloklar arasında kopyalama yapar
	memchr -> belirli bir bellek bloğunda byte arar
	memcmp -> belirli bir bellek bloğunda kıyaslama yapar.
	
	Bunlar generic functionlar.
	bir parametresi mutlaka void * ve diğer parametresi size_t
	
	memset -> bir bellek bloğunun her bir baytını bir tamsayı ile dolduran fonksiyon.
	void *(void *vp, int val, size_t n)
	vp -> set edilecek bloğun adresi
	val -> set edilecek değer.
	n -> set edilecek bellek bloğunun büyüklüğü, size değeri.
	geri döndürdüğü değer, gönderdiğim vp değeri.

	Yani vp den başlayıp n adet byte set edecek.

	------------------------------------------------

	int a[SIZE];
	randomize();
	set_random_array(a, SIZE);
	print_array(a, SIZE);
	memset(a, 0, sizeof a); // dizideki bellek bloklarının herbit byte ına 0 yazacak.
	print_array(a, SIZE);

	// ----------------------------------

	char str[100] = "Bugun hava cok sugudu";
	memset(str + 6, '*', 4);
	puts(str);

	// -----------------------------------
	// en çok kullanılan şekli bir bellek bloğuna 0 yazdırması şeklindedir.
	// memset(address,0,sizeof);

	--------------------------------------------------
	
	MEMSET in kodunu yazıyorum.
	
	void* my_memset(void* vp, int val, size_t n)
	{
		char* p = (char*)vp;

		while (n--)
			*p++ = (char)val; // p char dizi olduğu için içine atanacak değeride char a cast ettik.
		
		return vp;
	}
	
	int a[4] = { 4,6,8,9 };
	my_memset(a, 0, sizeof a);
	print_array(a, 4);
	
	-----------------------------------------------------

	// SORU
	int x;
	my_memset(&x, 0, sizeof x);
	printf("x = %d\n",x); // Her bir belle bloğuna 0000 0000 0000 0000 0000 0000 0000 0000 yazar

	my_memset(&x, 255, sizeof x); // 1111 1111 1111 1111 1111 1111 1111 1111 -> -1 dir.
	printf("x = %d\n",x);

	my_memset(&x, 1, sizeof x); // 0000 0001 0000 0001 0000 0001 0000 0001 yazar.
	printf("x = %d", x);
	
	Güvenlik Amaçlı genelde kullanılan bellek bloğu sıfırlanıyor.
	Daha sonradan bu bloktaki verilere erişilemesin diye.
	
	=============================================================
	=============================================================


	void	func(void) -> func ın geri dönüş değeri olmadığını gösterir.
	void*	func(void) -> geri dönüş değeri adres fakat void türden bir adres. yani
							türü hakkında bilgimiz yok.Bunu çağıran kişi belirleyecek.


	=============================================================
	=============================================================

	void * memcpy(void *pdest, const void *psource, size_t n);


	int a[SIZE];
	int b[SIZE] = {0};
	randomize();
	set_random_array(a, SIZE);

	print_array(a, SIZE);
	memcpy(b, a, sizeof a);
	print_array(b, SIZE);

	-------------------------------------------

	ÖR:
	int a[SIZE];
	int b[SIZE] = { 0 };
	int idx_a, idx_b;
	size_t n;
	randomize();
	set_random_array(a, SIZE);

	printf("a dizisinin indexi\n");
	(void)scanf("%d", &idx_a);

	printf("b dizisinin indexi\n");
	(void)scanf("%d", &idx_b);

	printf("Kac eleman kopyalanacak\n");
	(void)scanf("%zu", &n);

	memcpy(b + idx_b, a + idx_a, n * sizeof(int)); // n eleman * int in size ı = kaç byte
													// kopyalanacak bunun bilgisini verir.
	print_array(b, SIZE);

	ŞİMDİ memcpy kodunu yazalım
	---------------------------
	---------------------------

	void* my_memcpy(void* vpdest, const void* vpsource, size_t n)
	{
		char *pdest = (char*)vpdest;
		const char *psource = (const char*)vpsource;

		while (n--)
			*pdest++ = *psource++;
			 
		return pdest;	
	}

	BURADA ÖNEMLİ BİR PROBLEM VAR.
	OVERLAPPED BLOCKS
	
	read ve write yapılan blocklar eğer kesişirse burada Undefined Behavior oluşuyordu.
	Bu tip durumlarda memmove kullanılır.
	
	derleyiciden c 2017 standartlarına çekti.

	restrict keyworde bakıyoruz. C++ ta yok
	int * restrict ptr; * dan sonra geliyor bu keyword.
	Anlamı, ptr nin gösterdiği nesneyi artık başka bir pointer gösteremiyor

	void func(int * restrict p1, int * restrict p2);
	burada p1 in gösterdiği nesne ile p2 nin gösteridği nesne ayrı olacak.
	aynı nesneyi gösteremeyecek. Buna bağlı olarakta bazı temel optimizasyonları yapacak.
	kursun sonunda görülecek.

	burada p1 bizim dizi ya da neyse bunu gösteren tek pointer olacak.
	p2 aynı diziyi gösteremez.
	Buna uyulmazsa Undefined Behavior oluşur. Mesela strcpy (a+3,a); 
	burası ub çğnkü tanımda restrict ile bildirilmiş paramtereler.
	restrict varsa çakışan bloklar varsa eğer UB de vardır.

	strcpy (a+3, a); // UB
	memcpy(a+3,a,3*sizeof(int)); // UB 
	ikisinde de overlapped blocks var.

	==================================================================
	==================================================================

	MEMMOVE Fonksiyonunun overlapped blocklar üzerinde doğru çalışma garantisi var.
	Bellek blockları kesişmiyorsa memmove kullanmaya gerek yok.
	Eğer bir dizinin ilk 10 elemanını aynı dizinin son 10 elemanına kopyalanacaksa ve 
	dizi 100 gibi bir boyutta ise memcpy ile bile UB oluşmaz.
	memmove da ise  parametreler restrict değil.çakışsalar bile UB oluşmaz.

	void * memmove(char *vpdest,const char *vpsource,size_t n);

	char str[20] = "Gulden";
	memmove(str + 3, str, strlen(str) + 1);   sorun oluşturmaz burası 
	printf("%s", str);

	MEMMOVE için strprepend örneği güzel bir örnek
	
	char * strprepend(char * pdest, const char *psource)
	{
		size_t len_source = strlen(psource);
		size_t len_dest = strlen(pdest);
		memmove(pdest+len_source, pdest, len_dest + 1); //aslında dizinin başından kopyalayacağım
														// yazı kadar kaydırıyor elemanları
														// boşalan yere source yazısını koyacak.
														//overlapped block ama UB yok.

		memcpy(pdest,psource,len_source); // kaydırdığım yere de source u kopyaladı.
		return pdest;
	}													

	char str[100] = "Ahmet";
	strprepend(str, "Celebi"); // printf("%s",strprepend(str, "Celebi")); // bu da olur. çünkü ilk
	printf("%s", str);													// parametreyi return ediyor.


	MEMMOVE KODUNU İNCELEDİĞİMDE ŞUNU FARKETTİM, BU FONKSİYON OVERLAPPED DURUMLAR İÇİN ÇOK UYGUN.
	KODUN İÇERİSİNDE POİNTERLARIN BÜYÜKLÜK KIYASLAMASI YAPILMIŞ.EĞER FARKLI ARRAYLERE AİT ADRESLER
	OLSALARDI KARŞILAŞTIRMAK ÇOK ANLAMSIZ OLACAKTI.AYNI ARRAYDE OLDUĞU İÇİN ADRESLERİ KIYASLAMAK
	KODU YAZARKEN KULLANILAN BİR İDİYOM.BUARADA memmove_ KODU İNANILMAZ MANTIKLI YAZILMIŞ.
	DERS 35. SAAT 1:03:30 

	===============================================================
	===============================================================

	MEMCHR
	bellek bloğunda bir byte arıyor.	 

	void * memchr(const void *vp,int val,size_t n);
	2. parametre int çünkü burada integral promotion var, kastedilen char olsa bile
	fonksiyona giderken int oluyor.bu sebeple int yapılıyor.

	char buffer[] = { 1,1,1,1,0,1,1,1,1 };
	char *p = (char *)memchr(buffer, 0, sizeof(buffer)); // cast yapılmasa da olur.
	if (p != NULL)
		printf("bulundu dizinin %d indisli elemani\n", p - buffer);
	else
		printf("bulunamadi\n");


	KODU
	----
	void* my_memchr(const void* vp, int val, size_t n)
	{
		const char* p = (const char*)vp;
		while (n--)
		{
			if (*p == val) // integral promotion. char türünden *p karşılaştırınca, int türüne promote edecek.
				return (char *)p; // ben burada void * a cast etmiştim ama hoca char * cast etti,
			p++;					// sonrada otomatik olarak void * a dönüştürülecek dedi.
		}							// iki şekilde de denedim ve çalıştı.

		return NULL;
	}

	NOT:
	strchr sondaki null character a güvenir.
	memchr ise size a güvenir.
	mesela yazının ilk 20 karakterinde 'x' nasıl aranır.tabiki memchr ile
	char *p = memchr(a,'x',20);

	========================================================
	========================================================

	MEMCMP

	bu iki bellek bloğunu kıyaslıytor.
	bu bloklarda yazı sayi veya başka birşey olması onu ilgilendirmiyor.

	int memcmp(const void *vp1, const void *vp2,size_t n);
	eşitse 0, vp1 > vp2 ise pozitif, vp1< vp2 ise negatif.

	karşılaştırma yapılırken bunlar unsigned olarak değerlendirilecek.
	bu bytelar işaretsiz tamsayı gibi değerlendirilecek.

	0001 0001					0001 0001
	0000 0000					0000 0000
	1111 1111					1111 1111
	0101 0101					0101 0101

	Eğer birebir eşit se aynıdır gözüyle bakılıyor.
	3. satırdakilerden birini 1111 1110 yaparsak,

	0001 0001					0001 0001
	0000 0000					0000 0000
	1111 1111					1111 1110
	0101 0101					0101 0101


	1111 1111 ile 1111 1110 işaretsiz olarak kıyaslayınca
	1111 1111 daha büyük. dolayısı ile vp1 bellek bloğu daha büyük.
	

	int a[SIZE];
	int b[SIZE];

	randomize();
	set_random_array(a, SIZE);
	memcpy(b, a, sizeof(a));
	// ikisi birbirine eşit

	if (!memcmp(a, b, sizeof a))
		printf("birbirine esit\n");
	else
		printf("Esit degil\n");

	------------------------------------
	
	int a[SIZE];
	int b[SIZE];

	randomize();
	set_random_array(a, SIZE);
	memcpy(b, a, sizeof(a));
	// ikisi birbirine eşit

	//bir elemanı değiştir.
	a[rand() % SIZE]++;//eşit değiller artık.

	if (!memcmp(a, b, sizeof a))
	printf("birbirine esit\n");
	else
	printf("Esit degil\n");

	--------------------------------------

	MEMCMP nin kodu

	int my_memcmp(const void* vp1, const void* vp2, size_t n)
	{
		const unsigned char* p1 = (const unsigned char*)vp1; // unsigned olarak kıyasladığını söylemiştik.
		const unsigned char* p2 = (const unsigned char*)vp2; // unsigned olarak kıyasladığını söylemiştik.

		while (n--)
		{
			if (*p1 != *p2) 
			{
				return *p1 > *p2 ? 1 : -1; // buradaki büyüklük, değerlerin büyüklüğü değil,
			}								// byteların kıyaslaması sonucu oluşan büyüklük.
			++p1, ++p2;						// Notlarda aşağıda yani var açıklaması.
		}

		return 0;

	}

	ÖR:
	int x, y;
	printf("iki tamsayi girin: "); // 30 ile 20 dene sonra da -4 ile 23
	scanf("%d%d", &x, &y);		// -4 > 23 çıkar mesela sonuç. çünkü byteları kıyaslıyor.

	int result = memcmp(&x, &y, sizeof(int));
	if (result > 0)
		printf("%d > %d", x, y);
	else if(result < 0)
		printf("%d < %d", x, y);
	else
		printf("%d = %d", x, y);

	AMA
	memcmp ile yazıları kıyaslayabiliriz.
	yazının belirli bir kısmını kıyaslayacaksak ya memcmp ya da strncmp kullanılır.

	1:33 te kısa bir özet var.

	========================================================================
	========================================================================
	========================================================================
	========================================================================

	VOID POINTERS 2. KISIM

	Türden bağımsız bir reverse array yazılabilir mi ?
	Evet.türden bağımsız olarak 2 blok yer değiştirilebiliyor.

	void* greverse(void* vpa, size_t size, size_t sz)// size = Gönderilen dizinin kaç elemanlı olduğunu söyler.Toplam bellek sizeof değeri değil.
	{												// sz = tek bir elemanın sizeof bilgisi.			
		char* p = (char*)vpa;

		for (size_t i = 0; i < size / 2; i++)
		{
			//p + i * sz; // ÇOK ÖNEMLİ. int dizi ise,  i= 1 olsun. 1*4 = 4 adresi, double ise 8
						// yani her seferinde verinin türüne bağlı olarak, o kadar bellek alanı
						// ileri gidiliyor.türünü bilseydik p++ derdik.Ama türü yok.
						// bellekte ne kadar gideceğini fonksiyona gelen veri türünden çıkarıyoruz.
			// p + (SIZE -i -1)*sz; de reverse edilirken kullanılan indis değeri.

			gswap(p + i * sz, p + (size - i - 1) * sz, sz);
			// yukarıdaki fonksiyon normalde 2 adet veriyi alır ve bir de veri size ını alır ve
			// bunları türden bağımsız olarak takas eder.

		}

		return vpa;

	}	

	------------------
	
	test

	int a[SIZE];
	double da[] = {1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9};
	randomize();
	set_random_array(a, SIZE);
	print_array(a, SIZE);

	greverse(a, SIZE, sizeof(int));
	greverse(da, asize(da), sizeof(double));

	print_array(a, SIZE); // int array yazdıran fonksiyon var.
	for (size_t i = 0; i < asize(da); i++) // double yazdıran fonksiyon henüz yok. for ile yazdım
		printf("%f ", da[i]);


	-------------------------------------------
	-------------------------------------------

	bir dizide linear search algo ile bir değeri arayan gsearch fonk. tasarla

	
	void* gsearch(const void* vpa, size_t size, size_t sz, const void* vpkey)
	{
		const char* p1 = (const char*)vpa;

		while (size--)
		{
			if (!memcmp(p1, vpkey, sz)) // memcpy nin de paramtetreleri zaten const void *
				return (char*)p1; // const char * dan char * a dönüştürelim.
									// compilerda void * a otomotik dönüştürür.

			p1 += sz; // çünkü adam int ise 4 byttır. p++ demek char pointer da 1 byte ilerlemek demek
						// bizde char ptr ile işlem yapıyoruz.
		}				// sz int ise 4 byte. bir bellek bloğu ilerlemek için p +1 yetersiz
						// p + sz demek lazım. Bu da zaten p + 4 demek.double olsaydı p + 8 di.

		return NULL;

	}


	int a[SIZE];
	randomize();
	set_random_array(a, SIZE);
	print_array(a, SIZE);
	int sval;

	printf("aranacak degeri girin ");
	(void)scanf("%d", &sval);
	int * p = (int *)gsearch(a, SIZE, sizeof(*a),&sval);
	// int *p = dizinin bir int dizi olduğunu biliyoruz. Dönen değerde void * olacak.
	// bizde zaten cast ettik
	// a = array
	// SIZE = Dizi uzunluğu
	// sizeof(*a) -> bir elemanın sizeof değeri
	// &sval -> aranan deger adresi. HErşey adresler üzerinden yapılıyor. memcmp de kullanılacak
	// bu değişken ve memcmp de adres ile işlem yapıyor.türden bağımsız çünkü.

	if (p)
		printf("bulundu dizinin %d indisli elemani\n", p - a);
	else
		printf("bulunamadi\n");



	--------------------------------------------------------------
	--------------------------------------------------------------
	--------------------------------------------------------------

	void * bir tür
	void ** da başka bir tür.

	void * a herhangibir nesnenin adresi atanabilir.
	void ** bu generic bir pointer türü değil. void * türünden nesnenin adresi olan bir tür.
	buna herhangibir nesnenin adresi atanamaz.Generic bir ptr türü değil.

	
	void *vptr = NULL;
	void **vp = &vptr;

	*vptr -> bu sentaks hatası çünkü türden bağımsız.kural.
	*vp -> bu ise vptr ye erişir.
	 
	yani
	*vp = &dval; demek vptr = &dval demektir.

	-----------------------------------------------------------------------
	-----------------------------------------------------------------------
	-----------------------------------------------------------------------

	öyle durumlar varki void * türünden değişkeni call by reference yöntemiyle bir
	fonksiyona göndermek istiyoruz.

	int g =10;
	double dval = 3.4;

	void func(void ** vptr)
	{
		*vptr = &dval;
	}

	int main()
	{
		void *vp = &g;
		//öyle bir fonksiyon yazalım ki, vp değerini değiştirsin, vp nin değerini g nin adresi
		//yerine dval in adresi yapsın.
		func(&vp); // yani void ** türden bir nesne gönderdim.
	}

	----------------------------------------------------------------------
	----------------------------------------------------------------------
	----------------------------------------------------------------------

	veya
	void *gvp;
	öyle bir fonksiyon düşünelim ki geri dönüş değeri gvp nin adresi olsun
	bu durumda void ** foo(void) diye tanımlanır.

	void *gvp;

	void ** foo(void)
	{
		//code  
		return &gvp;  // static ömürlü bir pointer adresi ile de geri dönülebilir.
	}

	2:13

	bir değişkenin adresinin void olamaz ama void * olabilir.
	dizi elemanları da void olamaz ama void * olabilir.

	void *a[10]; // 10 adet void * elemanı tutan bir dizi.

	int x;
	double dval;
	char buffer[];

	void *a[10] = {&x,&dval,buffer}; // bu legal.
	elemanlar void * burada



	===========================================================================
	===========================================================================
	===========================================================================
	===========================================================================
	===========================================================================
	===========================================================================
	===========================================================================



	Türden Bağımsız bir dizi sıralanabilir mi?

	EVET

	FUNCTION POINTERS
	-----------------
	Bir fonksiyonun, başka bir fonksiyona fonksiyon göndermesi. Buna Callback deniyor.
	mesela qsort böyle

	POINTERLAR 2 YE AYRILIR
	1. OBJECT POINTERS
	2. FUNCTION POINTERS

	objelerin memry de adresi vardı. bu adresler söz konusu olunca pointer kullanırız.
	function larında makina kodları var. bunların çalışması için memory ye yüklenmesi gerekiyor ve
	bunların yüklendiği bellek bloğununda adresi var.Adresi elimizdeyse bu fonksiyonu çağırabiliriz.

	Not: Fonksiyonlarında, fonksiyon adreslerininde türü var.

	bir fonksiyonun adresini, isminin operandı yaparak elde ederiz.
	&func gibi

	Türü:
	int foo(int)
	ilk önce geri dönüş türü
	sonra foo nun adres olduğunu yazıyoruz.
	sonra da parametrelerin türünü yazıyoruz.

	int (*)int türünde bir fonksiyon :D

	Soru:
	&strcmp nin türünü yaz(neden & var açıklanıyor aşağıda)
	int (*)(const char *, const char *)

	&strlen nin türü
	size_t (*)(const char *)

	void func(void) in türü
	void (*)(void)

	() -> fonksiyon çağrı operatörü
	
	Aslında bunun sentaksı şu
	fonksiyon adresi() şeklinde. Yani operandı bir fonksiyon adresi.
	Ama biz hiçbir zaman (&func)() şeklinde çağırmayız fonksiyonu. 
	(parantezin sebebi öncelikten.konulmazsa ilk önce çağrı operatörü girer devreye sonra & operatörü)
	Aynı şekilde (&func)() şeklinde de çalışır ama biz böyle kullanmıyoruz.
	fonksiyonun adını yazdığımızda function to pointer conversion devreye girer.
	yani func ile &func aynı ifade. array decay veya array to pointer conversion gibi.
	
	void func(func)
	{
		printf("cagrildi\n");
	}

	int main()
	{
		func(); // (&func)(); şeklinde de çağrılır.function to ptr conversion olduğu için gerek yok.
	}

	Function to Pointer Conversion
	Bir function ismi bir ifade içerisinde kullanılınca 
	derleyici function ismini implicit olarak ilgili functionun adresine dönüştürür.
	func ----> &func
	func() ----> (&func)()  aynı ifade bunlar.

	Şimdi bir function pointer tanımlayıp buna function adresini atayacağım.

	void func(void)
	{
		printf("func cagrildi\n");
	}

	int main()
	{
		void (*fp)(void) = func; 
		// veya aşağıdaki gibi yazılabilir aynı şey.
		// void (*fp)(void) = &func;
	}
	

	bir function pointerı ile nesne pointerının sizeof u aynı olmayabilir,
	ama tüm function ptr sizeofları kendi içinde aynı.
	Tüm obje pointerlarda kendi içinde aynı size değerine sahip.


	*/







}