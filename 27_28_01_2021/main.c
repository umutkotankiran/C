#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	/*
	
	POINTER DEVAM

	const anahtar sözcüğü
	açıkçası bir nesnenin readonly olduğunu belirtiyor.
	Aşağıdaki örnekte result değişecek sürekli fakat diğer değişkenler değişmeyecek.
	Değişmeyen değişken :D
	Burada 2. ve 3. nesneleri sadece okuma amaçlı kullanmak istediğimiz için başına const yazarız

	typedef struct{
		int row,col;
		int a[20][20];
	}Matrix;

	void add_matrix(Matrix *presult, const Matrix * p1, conts Matrix *p2)
	....

	Matrix x,y;
	Matrix z;
	add_matrix(&z,&x,&y);

	-------------

	Bir fonksiyon başka bir fonksiyona dizi gönderecekse bu adress yoluyla yapılmalı.

	---------------------------------
	---------------------------------
	NEDEN CALL BY REFERENCE!!!
	1 - Geri dönüş değeri yerine kullanılabilmesi.Bir adres gönderip hesaplatıp aynı 
	adresteki nesneye yazabilir.
	2 - Bazı değişkenlerimiz var diyelim. Bunları fonksiyon argümanı olarak yazdığımızda
	fonksiyon parametresi olarak kopyalanacak ve çok maliyetli olacak.Özellikle sizeof değeri yüksek ise
	Değeri değiştirme amaçlı değil, kullanma amaçlı erişiyor.(const örneği gibi)
	3 - Fonksiyon birden fazla değer iletecekse, yani kaç tane değer iletecekse
	onların adreslerini alıp işleme sokabilir.
	4 - Dizi ileteceksek bunun tek yolu fonksiyonun parametre değişkeni pointer olmalı.
	hem paratmetre hemde geridönüş değeri pointer olabilir.dizi olamaz.
	Dizi gibi görünebilir.


	=============================================
	=============================================

	const ANAHTAR SÖZCÜĞÜ
	Çok önemli.En önemli 3 keywordden biri diyor hoca.

	const int x = 10;  bu oksimoron ifade
	x hayata 10 ile geliyor ve bu değeri koruyacak.Değişmiyor.ReadOnly aslında.
	değiştirmeye çalışırsam sentaks hatası.
	++x sentaks hatası mesela.

	const int a[] = {1,5,4,3,7,8}
	mesela 
	a[2] =43; sentaks hatası. değiştirilemez.


	const int a 
	veya
	int const a olabilir. İkiside aynı anlamda.Pointerda birazcık farklı.
	dereferencing operatöründen önce ve sonra olması farklı anlamda oluyor.
	
	const anahtar sözcüğünün doğru kullanılmasına const correctness deniyor.

	eğer değişmemesi gereken bir veri varsa bunu const ile koruruz.
	mesela asal sayılar
	const int primes[] = {2,3,5,7,11,13,17,19,23}  burada kullanmak mantıklı.
	primes değişmemeli. değiştirmek logical hata.

	user defined veri yapılarında da kullanılır.

	1 - const keyword kodu okuyanında işini kolaylaştırıyor.
	
	2 - int a[]; bu dizi mutable olduğunu gösterir.write edilebilir olduğunu gösterir.
	const int a[]; bu ise immutable bir dizi.elemanları değiştirilemez.write amaçlı kullanılmayacak demek.
	
	3 - const keyword kodun optimizasyonuna faydalıdır.
	kesinlikle daha iyi kod üretir denemez ama üretecek duruma getirir.

	---------------------
	---------------------
	---------------------

	const int x = 10;
	x = 20; // SENTAKS HATASI

	---------------------

	const int x = 10;
	int *p = &x; // C++ ta sentaks hatası C de geçerli.
	*p = 98;  // burası UNDEFINED BEHAVIOR
	
	printf ile x 98 görünebilir ama bu bir UNDEFINED BEHAVIOR.

	---------
	---------
	---------


	----------------------------------------------
	----------------------------------------------
	----------------------------------------------

	int x = 10;
	int y = 20;


	int * const ptr = &x; const pointer to int şeklinde ifade edilir.yada Top-Level const
	burada ptr ın değerinin değişemeyeceğini belirtiyor.Yani ptr hayatı boyunca hep
	x i gösterecek ama *ptr (yani x) i değiştirebilirim. *ptr = 25; işleminde sorun yok.
	ama ptr = 0x123A... Sentaks hatası.

	*ptr = y; sentaks hatası değil.
	ptr = &y; sentaks hatası.

	

	const int * ptr = &x;      veya      int const * ptr = &x;		 ikiside aynı.
	pointer to const int şeklinde ifade edilir.yada Low-Level const.
	Önemli olan * dan sonra veya önce olması.
	Burada ptr nin tuttuğu değer değişebilir.Yani hayatı boyunca x i gösterecek diye birşey yok ama
	*ptr yani gösterdiği adresteki değer değişemez.Yani x değişemez.
	
	*ptr = y; sentaks hatası
	ptr = &y; sentaks hatası değil.


	
	const int * const ptr = &x;  const pointer to const int
	burada hiçbirşey değiştirilemiyor. :D
	
	*ptr = y;  sentaks hatası
	 ptr = &y; sentaks hatası.



	---------------------------------------------
	---------------------------------------------

	void func(int *ptr)     burada const olmadığı için bu bir set fonksiyonu
	set veya setter veya mutater 


	void func(const int *ptr)     burada pointer to const var ve *ptr değişmeyecek
	bu bir get fonksiyon.

	-----------------------------
	-----------------------------

	strlen() parametresi const char * , yani boyutunu alacak parametre değişmeyecek
	_strrev parametresi char * , çünkü yazı ters çevrilecek.
	strcmp() iki parametresi var.parametreleri const char * çünkü karşılaştırma var.değiştime yok.

	burada const char * ve ya const int * ...
	olarak yazılan parametre değişkenleri şunu belirtiyor.
	Eğer değişmemesi gereken bir veri varsa bunu değiştirmeye çalıştığında sentaks hatası ver
	gibi bir aksiyon almış oluyoruz.Ve kodu okuyanda zaten const değişkenin değişmeyeceğini
	anlaması gerekiyor.


	===================================================
	===================================================
	===================================================


	POINTER ARİTMETİĞİ

	C DİLİNDE
	bir adresle bir tamsayı toplanabilir.
	bir tamsayı ile bir adres toplanabilir.
	bir adresten bir tamsayı çıkartılabilir.
	bir tamsayıdan bir adres ÇIKARTILAMAZ !!!
	bir adresten başka bir adres çıkartılabilir. değeri işaretli tamsayıdır.
	bir adres ile başka bir adres TOPLANAMAZ !!!


	int a[10] = { 0,1,2,3,4,5,6,7,8,9 };

	for (int i = 0; i < 10; i++)
	{
		printf("%p  %p  %p\n", &a[i], a + i, i + a);
	}

	elemanların bellekteki yerlerine bakılabilir.
	her eleman arası sizeof(int) kadar fark var.
	double olsaydı 8 byte
	int 4 byte
	char 1 byte

	-------

	&a[5]  ile  a + 5 aynı ifade
	yani
	&a(n)  ile    a + n aynı

	----------

	int a[10] = { 0,1,2,3,4,5,6,7,8,9 };

	for (int i = 0; i < 10; i++)
	{
		printf("%d  %d  %d\n", a[i], *(a + i), *(i + a));  // Aynı şeyi yazdırırlar.ifade aynı çünkü.
	}

	----------

	int a[10] = { 0,1,2,3,4,5,6,7,8,9};
	int * p = a;

	printf("%d",*p);
	
	p++;//bir sonrakine geçiyor bu ifade ya da p = p+1; ya da p+=1;
	
	printf("%d",*p); //bir sonraki yazıldı.

	------------------------

	O zaman aşağıdaki ifadeyi yazalım tekrar.

	int a[10] = { 0,1,2,3,4,5,6,7,8,9 };

	for (int i = 0; i < 10; i++)
	{
		printf("%d  %d  %d  %d  %d\n", a[i], i[a], *(a + i), *(i + a),*ptr); 
		ptr++;
	}

	-------------
	-------------

	NOT !!!

	i[a]  bu ifade ile a[i] aynıdır
	[] subscript operatörü a[i] ifadesini *(a+i) ye çeviriyor.


	------------
	------------

	İki adres birbirinden çıkartılabilir.yazmıştım

	bu ifadenin değeri işaretli tamsayıdır.
	adresten adres çıkarsa sonuç adres çıkmaz.
	Yani adresten adres çıkarsa dizinin mesela 4. elemanı denebilen birşey çıkabilir.

	int a[] = { 5, 6, 7, 8, 9, 3, 2, 1, 1, 2, 3, 4 };
	int* p1 = &a[5];
	int* p2 = &a[8];

	printf("p1 - p2 = %d\n", p1 - p2);
	printf("p2 - p1 = %d\n", p2 - p1);


	=======================================
	=======================================
	=======================================

	INDEX/SUBSCRIPT Operatörü

	Farklı arraylerin adreslerini birbirinden çıkarmak çok mantıksız oluyor.
	mesela 
	int x[10] = {0};
	int y[10] = {0};

	&x - &y    bu ifade anlamasız.Aynı arraydeki değerlerin çıkarılması anlamlı.
	sentaks hatası yok ama anlamı yok.

	-------------------------
	-------------------------

	TEKRAR
	x[y]  -> derleyici subscript operatörünü görünce
	*(x + y) ye çevirir bunu
	yani 
	x[y]  ile y[x] aynı ifade

	x[y] = *(x+y)  aşağıdaki ile aynı.
	x[x] = *(y+x)    


	-----------------------------
	-----------------------------

	int x = 10;	// 1 elemanlı bir array gibi düşünülebilir.
	++(&x)[0];  // x = 11
	++*(&x+0); // x = 12

	-----------------------

	int a[10] = { 0,1,2,3,4,5,6,7,8,9};
	int *ptr = a + 5;

	printf("%d\n",*ptr);   // 5
	printf("%d\n",ptr[0]);  // 5 
	printf("%d\n",ptr[3]);  // 8
	printf("%d\n",ptr[-2]);  // 3 
	printf("%d\n",*(ptr - 2));  // 3 
	Bu işlemlerde diziyi taşırırsak bu Undefined Behavior.
	mesela ptr[-15] bir sentaks hatası değil ama bir UB.
	
	-----------------------

	ptr, a isimli bir dizinin bir elemanını göstermektedir.
	ptr nin gösterdiği dizi elamanının indexi nedir
	ptr - a dır.


	ptr, a isimli bir dizinin 5 indisli elemanını gösteriyor. ptr ?
	ptr = a + 5 tir
	

	================================================
	================================================
	================================================


	DİZİLERİN FONKSİYONA GÖNDERİLMESİ

	Bu dizinin adresini göndermek ile mümkün.

	//Az tercih edilen
	void print_array(cont int * ptr, int size)
	{
		for(int i = 0;i<size;i++)
		{
			printf("%d ",ptr[i]);
		}
		printf("\n--------------------------\n");	
	}


	// daha çok tercih edilen
	void print_array(const int * ptr, int size)
	{
		while(size--)
		{
			printf("%d ",*ptr);
			ptr++;
		}
		printf("\n--------------------------\n");
	}

	int main()
	{
		int a[10] = { 0,1,2,3,4,5,6,7,8,9};
		print_array(a,10);
	
	}

	DİKKAT!
	print_array de pointer olarak gönderilen nesne kesinlikle const keyword ü ile nitelenmeli.
	Yapılmazsa büyük hata olur. Mülakatlarda çok dikkat ediyorlar.


	print_array(a,5);  // ilk 5 eleman
	print_array(a+5,3);  // 5,6,7 elemanlarını çağırır.
	print_array(a+5,3);  // 5,6,7 elemanlarını çağırır.
	print_array(a+SIZE-5,5 );  // son 5 elemanının değeri.SIZE büyüklüğünü gösteren makro olsun mesela.


	------------

	// bu bir yöntem
	int sum_array(const int *ptr,int size)
	{
		int sum = 0;
		while(size--)
		{
			sum += *ptr;
			ptr++;
		}
		return sum;
	}

	//diğeri
	int sumArray(const int *a,int size)
	{
		int sum = 0;
		for(int i = 0; i<size;i++)
			sum += a[i];
	
		return sum;
	}

	randomize();
	set_random_array(a,SIZE);
	
	printf("sum = %d\n",sum_array(a,SIZE));
	printf("sum = %d\n",sumArray(a,SIZE));

	-------------------------------------
	-------------------------------------

	son örnek

	//kendi parametresine, argüman olarak gönderilen değerleri, 
	//diğer fonksiyonu çağırırken argüman olarak ekliyor.

	double get_mean(const int * ptr , int size)
	{
		return (double)sum_array(ptr,size) / size;
	}



	*/

	


}