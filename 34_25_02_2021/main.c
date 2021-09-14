#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "nutility.h"

void get_min_max1(const int* pa, size_t size, int** pmin, int** pmax)
{
	*pmin = *pmax = (int*)pa;

	for (size_t i = 1; i < size; i++)
	{
		if (pa[i] < **pmin)
			*pmin = (int*)(pa + i);
		if (pa[i] > **pmax)
			*pmax = (int*)(pa + i);
	}

}


void test(int** p1, int** p2)
{
	int* ptemp = *p1;
	*p1 = *p2;
	*p2 = ptemp;
}

void print_names1(char* const* p, size_t size) //aradaki const açıklanacak.
{
	for (size_t i = 0; i < size; i++)
	{
		printf("%s ", *(p + i));
	}

}



void print_names2(char* const* p, size_t size) //aradaki const açıklanacak. *p değişmez(const) demek bu
{
	while(size--)
	{
		printf("%s ", *p++);// *p++ -> burada öncelik sırası sağdan sola. p + 1 yapılıp dereference yapılıyor
	}						// kural ihlali yok. ++*p; yazılsaydı, tanımda *p değişmez diyor.sentaks hatası.

}


void sort_names(char** p, size_t size) // klasik bubble sort
{
	for (size_t i = 0; i < size - 1; i++)
		for(size_t k = 0; k < size - 1 - i;k++)
			if (strcmp(p[k], p[k + 1]) > 0)
			{
				char* ptemp = p[k];
				p[k] = p[k + 1];
				p[k + 1] = ptemp;
			}		
}



void gswap(void* vpx, void* vpy, size_t n)
{
	//void ptr larda değere ulaşamadığımız için

	char* px = (char*)vpx; //casting yapılmazsa c++ ta sentaks hatası
	char* py = (char*)vpy; // neden int * değilde char* ? çünkü değişimi byte mertebesinde yapıyor.char 1Byte eder.

	while (n--)
	{
		char temp = *px;
		*px++ = *py;
		*py++ = temp;
	}

}

#define		SIZE		10


int main()
{
	/*
		
		TEKRAR
		int x = 10;
		int y = 20;
 		int *p = &x;

		bu durumda aşağıdakiler geçerli.
		p = &y;
		*p = 300;
		
		--------------

		int * const p = &x;  olsaydı.
		Bu const pointerdır. yani p const. P değişmeyecek demek
		*p = 45; geçerli
		p = &y; sentaks hatası.
	
		------------

		const int * p = &x;
		BUna da Pointer to const int deniyor.
		const olan nesne *p demek bu. P const değil.
		Hem pointer to const int denince, pointer const int i gösteriyor 
		anlıyoruz biz zaten. Ayrıca daha kolayı, 
		tanımda const tan sonra *p geliyor(int i saymazsak), bu durumda 
		*p işlemi const demek :) iki türlü anlaşılabilir. 2. olan daha kolay.
		 
		 p = &y; sorunsuz
		 *p = 90; hata

		 --------------

		 const int * const a;
		 hem *a const
		 hemde a const.
		 ikiside değişmez.
		 ifade olarakta yine const ptr to const int.

		 *p = 300; hata
		  p = &y;  hata

		-----------------------------
		-----------------------------
		Pointer dizilerinde bakalım
		int x = 30;
		int y = 40;
		int z = 50;

		char * p[3] ={&x,&y,&z}; 
	
		Değerleri değiştirmeyecek bir ptr tanımlarsak
		const int * ptr = p; -> const olan *ptr demek bu.
		burada p[2] = &x; yazılabilir.
		*ptr[2] = 555; sentaks hatası.

		----------

		Ama elemanları dğeişmeyecek bir ptr tanımlarsak

		int * const ptr = &x;
		ptr burada const
		ptr = &y; denemez
		*ptr[2] = 456; olur


		SONUÇ;
		Pointer dizilerde
		const int *p = &x ; demek const olan nesne *p demek. 
		*p ile değer değiştirilemez demek.
		
		int * const p = &x; demekte const olan nesne p demek.
		p ile herhangibir adres ataması yapılamaz demek
		dizi elemanları değişemiyor bir bakıma. 

	---------------------------------------------------------
	---------------------------------------------------------

	Bir fonksiyon const olmaz ama geri dönüş değeri const olabilir.

	bir çok pointer dizisinde son elemana NULL ptr tanımlanır.
	son eleman NULL ptr olduğu için bir döngüden çıkmakta kolay olur.

	============================================================
	============================================================

	POINTER TO POINTER
	------------------
	Başka bir pointerın adresini tutan pointer
	Gösterici gösteren gösterici

	int x = 10;
	int *p = &x;

	p nin türü int *
	&p nin türü int **

	dolayısı ile bunu bir değişkende saklamak istersem
	bu değişken int ** türünden olmalı.

	int **ptr = &p;

	burada *ptr , p dir.
	*ptr = &y ; burada atama aslında p ye yapılır.

	**ptr = bu sefer x(yada y ye) e atama yapılır.

	----------------

	int a[5] = {1,4,6,7,8};
	int *p = a;
	int **ptr = &p;

	(*ptr)[2] -> 6 dır 


	++*ptr; -> ptr i dizinin 2. elemanının başlangıç adresine getirdi
	++**ptr; -> bu adresteki değeri 1 artırdı
	4 -> 5 oldu.

	----------------------------------------------------------------------
	----------------------------------------------------------------------
	----------------------------------------------------------------------



	int x = 10;
	int *p = &x;
	int **ptr = &p;

	
	Expression			Data Type			Value Category
	-------------------------------------------------------
		x					int					L
		-----------------------------------------
		&x					int *				R
		-----------------------------------------
		p					int *				L
		-----------------------------------------
		*p					int					L
		-----------------------------------------
		&p					int **				R
		-----------------------------------------
		ptr					int **				L
		-----------------------------------------
		*ptr				int *				L
		-----------------------------------------
		**ptr				int					L
		-----------------------------------------
		&ptr				int ***				R
		-----------------------------------------

		bu nereye kadar gider?
		int * her kodda görülür.
		int ** birçok kodda görülür.
		int *** nadiren görülür.
		int **** neredeyse hiç görmeyiz.1-2 defa belki
		int ***** bunu unut :D

		------------------------------------------

	Hoca Kod ile aşağıdaki bildirimleri yazdı.
	
	for (int i = 1; i < 21; i++)
	{
		printf("int ");
		for (int j = 0; j < i ; j++)
			putchar('*');
		printf("p%d = &p%d;\n", i, i - 1);
	}
		
	int x = 99;
	int *p1 = &x;
	int **p2 = &p1;
	int ***p3 = &p2;
	int ****p4 = &p3;
	int *****p5 = &p4;
	int ******p6 = &p5;
	int *******p7 = &p6;
	int ********p8 = &p7;
	int *********p9 = &p8;
	int **********p10 = &p9;
	int ***********p11 = &p10;
	int ************p12 = &p11;
	int *************p13 = &p12;
	int **************p14 = &p13;
	int ***************p15 = &p14;
	int ****************p16 = &p15;
	int *****************p17 = &p16;
	int ******************p18 = &p17;
	int *******************p19 = &p18;
	int ********************p20 = &p19;
	
	p20 yi dereference edip ++ nın operandı yapalım
	++********************p20; -> bu x i 1 artırır.
	x = 100 oldu

	-----------------------------------------
	-----------------------------------------

	Ne işe yarar.
	pointer değişkenlerin adresini değiştirmek için kullanılıyor.Adres değişince
	dereference ile gösterdiği nesnenin değeri de farklı olur.

	int x = 10;
	int y = 30;
	
	int *p = &x;
	int *q = &y;

	aşağıda p ile q takas edildi.	
	int *ptemp = p;
	p = q;
	q = ptemp;

	Ben bunu fonksiyon ile yapmaya çalışırsam call by reference ile yapmam gerekir.
	swap(p,q) dersem. 
	burada bu x in adresi ile y nin adresini gönderdiğimiz için x ile y yi takas eder
	p ile q yu takas etmez.p ve q nun adresi ayrı. 
	Ben ise p ile q pointer adres değişikliği istersem. p ve q nun adresini göndermeliyim.
	swap(&p,&q);

	void pswap(int **p1, int **p2)
	{
		int *ptemp = *p1; -> p1 in değerine inip onu ptemp ptr a atadık.
		*p1 = *p2;	-> p1 nin gösterdiği değişkeni, p2 inkine atadık (gösterdikleri değerlerde ptr zaten)
		*p2 = temp; -> p2 nin gösterdiğini de temp e atadık
	}

	hata olursa çok net tür uyumsuzluğu hatası verir.

	------------------------------------------------------------
	------------------------------------------------------------
	
	Aşağıdaki koda bakarsam.Bir farkı var.Burada pa ile pb swap edilmiyor. 
	a ile b swap ediliyor.
	
	void func(int **p1, int **p2)
	{
		int ptemp = **p1; 
		**p1 = **p2;	
		**p2 = temp; 
	}

	int main()
	{
		int a = 34;
		int b = 67;
		int *pa = &a;
		int *pb = &b;

		func(&pa,&pb); // pa yı pb nin adresi yaptı, pb yide pa nın adresi olarak düzenledi.

	}

	----------------------------------------------------------
	----------------------------------------------------------
	----------------------------------------------------------

	Güzel Örnek

	void get_min_max1(const int *pa,size_t size,int **pmin, int **pmax)
	{
		int *ptemp = pa;
		*pmin = *pmax = (int*)pa;
		
		for(int i = 1; i < size;i++)
		{
			if(pa[i] < **pmin)
				*pmin = (int *)(pa + i);
			if(pa[i] > **pmax)
				*pmax = (int *)(pa + i);
		}
			
	}
	
	int a[SIZE];
	randomize();
	set_random_array(a, SIZE);
	print_array(a, SIZE);

	int* ptr_min;
	int* ptr_max;

	get_min_max1(a, SIZE, &ptr_min, &ptr_max);

	printf("max = %d,  indis = %d\n", *ptr_max, ptr_max - a);
	printf("min = %d,  indis = %d\n", *ptr_min, ptr_min - a);

	swap(ptr_min, ptr_max); // bu normal swap function.kafa karışmasın.
	//odak noktası get_min_max
	print_array(a, SIZE);

	----------------------------------------------
	----------------------------------------------

	char *p[] = {"Ali","Veli","Hasan","Huseyin","Ahmet","Mehmet","Can","Kan","Ban","Zan"};
	
	Bunları yazdırmak için 2 adet fonksiyon yazacağız aynı işi yapan

	print_names1(p, SIZE);
	print_names2(p, SIZE);

	void print_names1(char* const* p, size_t size) //aradaki const açıklanacak.
	{												// adres gösteren adres olduğu için ** koymak gerekiyor.
		for (size_t i = 0; i < size; i++)
		{
			printf("%s ", *(p + i));
		}
	}



	void print_names2(char* const* p, size_t size) //aradaki const açıklanacak.
	{
		while(size--)
		{
			printf("%s ", *p++);
		}
	}

	---------------------------------------------
	---------------------------------------------

	Sıralayan bir kod yazılacak.

	void sort_names(char** p, size_t size) // klasik bubble sort
	{
		for (size_t i = 0; i < size - 1; i++)
			for(size_t k = 0; k < size - 1 - i;k++)
				if (strcmp(p[k], p[k + 1]) > 0)
				{
					char* ptemp = p[k];
					p[k] = p[k + 1];
					p[k + 1] = ptemp;
				}
	}

	int main()
	{
		char* p[] = { "Ali","Veli","Hasan","Huseyin","Ahmet","Mehmet","Can","Kan","Ban","Zan" };
		sort_names(p, SIZE);
		print_names2(p, SIZE);
	}

	=================================================
	=================================================
	=================================================

	CONST KULLANIMI
	---------------

	Yine aynı kural ama çok önemli.
	int x = 10;
	int * const p = &x; -> const kimden önce gelmiş, p. p ye atama yaparsam sentaks hatası.
	const int * p = &x -> const kimden önce gelmiş, *p. *p ye atama yapılırsa sentaks hatası.

	ÖR:

	int x = 10;
	int y = 30;
	int *p1 = &x;
	int *p2 = &y;
	int **ptr = &p1

	ptr = &p2;
	*ptr = &x;
	**ptr = 99;
	Yukarıda hiçbir hata yok.HErhangibir engelleme - const durumuda yok.

	Eğer
	int **cosnt ptr = &p1;  const burada olursa
	ptr = &p2; -> burada hata olur.
	*ptr = &x;
	**ptr = 99;

	Eğer
	int * cosnt* ptr = &p1;  const burada olursa
	ptr = &p2; 
	*ptr = &x; -> burada hata olur.
	**ptr = 99;

	Eğer
	cosnt int ** ptr = &p1;  const burada olursa
	ptr = &p2;
	*ptr = &x; 
	**ptr = 99; -> burada hata olur.

	Eğer
	cosnt int *cosnt* cosnt ptr = &p1;  const böyle bir durumda tamamen herşeyi readonly yapar.

	NOT:
	typedef int *IPTR;

	int x =10;
	const IPTR ptr = &x;
	böyle typedef kullanımlarında const olan pointerın kendisidir.
	int * const ptr; dir.


	NOT:
	Bir fonksiyonun return değeri int ** da olabilir.

	int *gp;
	int **func(void)
	{
		return &gp;
	}

	-------------------------------------------------
	-------------------------------------------------
	-------------------------------------------------

	int *func(int *p, int size)
	{
		int *ptr = p;
		//code

		return ptr; // burada UB yok.zaten p gönderilmiş ve bunun adresi geri döndürülüyor.
	}

	int **func(void)
	{
		int *ptr = NULL;
		//code

		return &ptr; //Burada UB var. çünkü otomatik ömürlü bir nesne return edilmiş
	}

	--------------------------------------------------
	--------------------------------------------------
	--------------------------------------------------


	int *gp1;
	int *gp2;
	int *gp3;

	int main()
	{
		int **pa[] = {&gp1,&gp2,&gp3};	
		pa[1]; -> gp2 nin adresi.
		*pa[1]; -> gp2 nin kendisi.
	}

	-------------------------------------------
	-------------------------------------------
	-------------------------------------------

	Sayılar bellekte nasıl tutuluyor?

	x = 1

	0000 0000 0000 0000 0000 0000 0000 0001


	2000	0000 0000	// Motorola tarzı mimari- motorola işlemcileri böyle isimlendiriliyor.
	2001	0000 0000	
	2002	0000 0000	
	2003	0000 0001



	2000	0000 0001	// Buda intel tarzı mimari. Armlar ise her ikisi gibi olabiliyor.
	2001	0000 0000
	2002	0000 0000
	2003	0000 0000

	buna endiannes deniyor. Düşük anlamlı byte düşük adreste mi yoksa düşük anlamlı byte yüksek adreste mi?
	intele little endian deniyor
	motorolaya big endian deniyor.

	Bir C kodu yazalım bu kod big veya little olduğunu test edecek.

	int main()
	{
		int x = 1;
		char *ptr = (char *)&x; burada x in adresini tutuyor char * ile.
		if(*ptr == 1) //*ptr 1 ise little endian
			printf("little endian");
		else
			printf("big endian");
	}

	yada daha güzel yazarsak

	int main()
	{
		int x = 1;

		if (*(char*)&x) //*ptr 1 ise little endian
			printf("little endian");
		else
			printf("big endian");
	}

	----------------------------------------

	Bunun Önemi veri alışverişi sırasında önem kazanıyor.
	bytelerı gönderen taraf ile kullanacak taraf arasında endianess farkı varsa
	kodu buna göre yazmak lazım.

	bu durumda 4 byte lık bir veri varsa
	ilk byte ile son byte swap
	2. ile 3. de swap.
	bu işlemden sonra ancak veri alışverişi sağlıklı olur.




	=================================================
	=================================================
	=================================================
	=================================================
	=================================================

	VOID POINTERS
	-------------
	void bir tür.int ve double nasıl birer türse void de öyle.

	diğerlerinden farklı olarak belirli kısıtlamalar var.

	1 - Bir değişkenin türü void olamaz.
	void x; sentaks hatası

	2 - C / C++ dillerinde bir ifadenin türü void olabilir.
	
	bu 2 farklı şekilde görülür.
	1. Geri dönüş değeri olmayan bir fonksiyona çağrı ifadesi.
		
		void func(int a);
		func(); ile çağrılır ve türü void dir.

	2. Tür dönüşümü ile bir ifadenin türünün void türüne dönüştürülmesi. 
		
		int func(int a);
		(void)func(); // bir ifadenin return değerini bilerek isteyerek kullanmadığımızı belirtmek için 
		ifadeyi void türüne cast ediyoruz.

	----------------------------------------

	void türden ifadeler logic ifade beklenen yerde kullanılamazlar.
	sentaks hatası olur

	void func();

	int main()
	{
		if(func()) burası sentaks hatası.
		{
		}
	}

	void fonksiyonlar geri dönüş değeri olmayan fonksiyonlardır.

	void func(void); parametresi yok
	void func(); parametreleri hakkında bilgi verilmemiş.

	C++ ta ise parametresine void yazmak ve yazmamak arasında hiçbir fark yok.

	-------------------------------------------------------------------------------
	-------------------------------------------------------------------------------
	-------------------------------------------------------------------------------
	-------------------------------------------------------------------------------
	BİR POINTER TÜRÜ VOID OLABİLİR

	void *ptr; bir adres türüdür ve değişkenin türü void * olabilir.
	void ile void * başka bir tür.

	void * ile değişken tanımlanır ama void ile tanımlanamaz.

	int *ptr;
	void *vptr; // Generic pointers ta denebilir. Türden bağımsız anlamında.

	int * , int türden bir değişkenin adresini tutabilir.
	void * pointerlar ise istediğim türden nesnenin adresini tutar.
	varlık sebebi  bu.

	int x = 10;
	double y = 20.1;
	char str[20];
	int *ptr = &x;

	void *vptr = &x;
	void *vptr = &y;
	void *vptr = str;
	void *vptr = ptr;	
	void *vptr = &ptr;	HEPSİ GEÇERLİ.
	
	-----------------
	-----------------

	Yani

	void func(void * ptr); // Generic function
	bu fonksiyona istediğimiz türden argüman gönderebiliriz.
	int *, double *.... hepsini çaırabiliriz demek. Buna Generic function denir

	----------------

	int x = 10;
	void * vptr = x; // C++ ta geçersiz C de de yanlıştır. 

	aynı şekilde
	int * p = x; bu da C++ ta geçersiz C de yanlış.

	 
	---------------

	int x = 10;
	void *p = &x;

	*p ; sentaks hatası, Void pointer Dereference işlemi yapılamaz.
								
	---------------

	int a[10] = {0};
	void *p = a;

	p + 1 yine hata. pointer artirmetiği sözkonusu olunca yine sentaks hatası void pointerlarda.

	p -1
	p++
	++p
	p--
	p - p1  

	hepsi sentaks hatası.

	--------------------------------
	--------------------------------

	VOID PTR ile neler mümkün
	-------------------------

	int x = 10;
	void * = &x; //bu legal yapılabilir.
	-------
	void *p = NULL; yapılabilir.
	-------
	if(!p) // null ptr sınanabilir.
	{
	}
	-------

	int x = 10;
	void *vp = &x;

	if(vp == &x)	yapılabilir.
		printf("Evet dogru\n");
	else
		printf("hayir yanlis\n");

	----------------------------------------
	----------------------------------------

	burada C / C++ arasında ciddi farklılık var.

	int x = 10;
	void *vp = &x;
	int *iptr;

	iptr = vp; // burada tür dönüşümü var. void * türünden int * türüne implicit dönüşüm var.
				// burası yanlış değil.
				// C++ ta ise doğrudan sentaks hatası.
				// C++ ta legal olması iiçin  iptr = (int *)vp; yapmak gerekiyor.

	// C de ise iki farklı tavır var.
	// 1. kod legal.implicit dönüşüm ile işlem yaptırılır.
	// 2. C++ ta da derlenmesi için iptr = (int *)vp; yazmak.

	------------------------------------------
	------------------------------------------
	------------------------------------------

	NE AMAÇLA KULLANILIYOR.

	En çok generic functionlarda kullanılıyor.
	Öyle işlemler varki türden bağımsız olarak yapılıyor.

	iki değişkenin takas edilmesi.
		a türe bağlı yazılabilir.
		b türden bağımsız olarak yazılabilir.
		----------------------------------------------------------
		----------------------------------------------------------
		----------------------------------------------------------
		----------------------------------------------------------
		----------------------------------------------------------
	ÖR:

	//Neden parametreler void türünde.Gönderilen belirli bir tür yok.Herhangibir tür olabilir.
	//dolayısı ile void ile belirtiliyor. Bunada type erasure deniyor.Neden size bilgisi girilmiş.
	// kopyalanacak alanın bilgisini belirtmek için. Belli bir tür olmadığı için size girmek şart.
	// neden char *px dendi. byte by byte yerdeğiştirmek için char * kullanıldı. char 1 byte çünkü.
	//burada da artık pointer aritmetiği kullanılabilir char sayesinde.

	void gswap(void *vpx, void *vpy,size_t n)
	{
		//void ptr larda değere ulaşamadığımız için (*vpx = *vpy hatadır.)
	
		char *px = (char*)vpx; // casting yapılmazsa c++ ta sentaks hatası
		char *py = (char*)vpy; // neden int * değilde char* ? çünkü değişimi byte mertebesinde yapıyor.char 1Byte eder.

		while(n--)
		{
			char temp = *px;
			*px++ = *py;
			*py++ = temp;
		}
		
	}


	int main()
	{
		int x = 10 , y = 25;
		double dx = 4.5, dy = 9.5;
		int a[] = {1,2,3,4,5};
		int b[] = {100,200,300,400,500};

		gswap(&x,&y,sizeof(int));
		printf("x = %d,   y = %d",x,y);

		gswap(&dx,&dy,sizeof(int));
		printf("x = %f,   y = %f",dx,dy);
				
		gswap(&x,&y,sizeof(int));
		print_array(a,5);
		print_array(b,5);
	
	}

		
	*/
	
	int x = 10;
	int y = 20;
	int* px = &x;
	int* py = &y;
	printf("px = %p,   py = %p\n", px, py);
	test(&px, &py);
	printf("px = %p,   py = %p\n", px, py);

}