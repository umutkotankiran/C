#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	/*
	
	POINTERLAR DEVAM

	POINTER -> GÖSTERİCİ -> İŞARETÇİ
	ADRES ANLAMINDA KULLANILIR.

	BUNLAR ADRES TÜRÜ.
	int *	
	double *
	char * 
	
	int *ptr -> ptr is a pointer to int
	pointer global değişken olabilir
	otomatik ömürlü yerel
	statik ömürlü yerel olabilir.
	fonksiyonun parametre değişkenide olabilir
	...

	Pointer türleri bir sistemde hep aynı yer kaplar
	double * = int * = char *
	hepsi aynı miktarda yer kaplar.
	
	OBJECT POINTERS
	FUNCTION POINTERS

	-------------------------------------------------

	int *p1, p2;
	burada aslında * tokenı sadece başına geldiği isimleri niteliyor.
	aşağıdaki gibi aslında bildirim.
	int *p1;
	int p2;

	Not:
	Kod okumak hakikaten yazmaktan daha zor.
	farklı insanların farlı stildeki kodlarını okuyup anlamak çok önemli.
	yani tüm konvensiyonları bilmek önemli.

	int x, *p, a[10], *q;  
	aşağıdaki ile aynı 
	
	int x;
	int *p;
	int a[10];
	int *q;

	-----------------------------------------------------------

	int *ptr;
	ptr garbage value değerindedir veya Indetermined value.
	kullanmak herzamanki gibi tanımsız davranış.

	statik ömürlü olsaydı eğer
	static int *ptr -> NULL pointer değerini alacaktı.

	-----------------------------------------------------------


	4 Adet Pointer Operator Var.
	---------------------------------
	& => Address of operator.Adres operatörü. 
	Operator öncelik.tab. 2. sırasında
	-------------------------------------
	* => Dereferencing/Indirection Operator. 
	İçerik Operatörü. Operator öncelik.tab. 2. sırasında
	-----------------------------------------
	[] => Subscript/Index Operator.Operator öncelik.tab. 1. sırasında
	-------------------------------------------
	->  =>  Member selection.Arrow operatörü yaygın kullanımı.Ok operatörü.
	Operator öncelik.tab. 1. sırasında


	-------------------------------------------------------------

	& binary infix olursa bitsel ve anlamındadır.
	unary prefix ise adres operatörü.

	* binary olarak kullanınca çarpma öperatörü
	unary olursa Dereferencing operatörü

	mesela
	+ unary ise sign operatörü
	binary olursa toplama operatörü


	====================================================
	====================================================

	ADDRESS/& OPERATOR 

	& operatörünün operandı L-Value expression olmak zorunda.
	anlamak için 
	int x; 
	&x; sentaks hatası yok lvalue exp ama
	&5; bu sentaks hatası yani r-value expression 

	int x = 10;
	burada  &x in türü int * dır.
	&x bir adres belirtiyor dolayısı ile türü de int * olacak
	double x olsaydı double &x, double * türünde olacaktı.
	
	int x = 10;
	int y = 20;

	int *ptr = &x; // burada bildirimde ismin pointer olduğunu belirtmek için * konuldu.
					// bu bir initialization
	
	ptr = &y; // burada ise artık başına * koymaya gerek yok.çünkü ptr bir pointer.
				// bu bir assignment/atama


	-----------------------------------------------

	ptr nin değeri x in adresi    ifadesinin karşılığı aşağıda
	ptr points to x  
	ptr x i gösteriyor.

	----------------------------

	Address operatörü / & ile oluşturulan ifadeler rvalue expressiondur.

	int x = 10;
	&x = 123213; olamaz
	&x rvalue expression.

	NOT:
	C/C++ ta hayata gelmiş nesnelerin adreslerinin değişmesi gibi bir kavram yok.

	NOT:
	int x = 10;
	& &x -> bu sentaks hatası
	çünkü adres operatörünün operandı lvalue expression olmalı.
	ayrıca x in adresinin adresi diye bir kavram yok.
	X i tutan bir pointer varsa, bu pointerın adresi var.

	mesela

	int x = 10;
	int *ptr = &x;

	&x -> bu x in adrsidir. 
	ptr -> bu da x in adresini tutuyor.
	&ptr -> bu ise ptr ın adresi
	ama &&x gibi bir kavram yok.

	------------------------------

	int x = 10;
	int *ptr = &x;
	printf("&x = %p\n",&x); %p conversion specifier deniyor bunlara.
	printf("&x = %p\n",ptr); aynı çıktıyı verirler
	printf("&x = %p\n",&ptr); bu ise ptr nin adresini yazdırır.

	microişlemcilerde adresler sözkonusu olunca adresler 16lık sayı sisteminde 
	ifade ediliyor. C dilinde de böyle.

	------------------------------

	NOT:
	bir dizinin ismi kullanıldığında, 2 case dışında bu isim dizinin ilk elemanının
	adresine dönüştürülüyor. Buna array decay veya array to pointer conversion denir.

	yani a ile &a[0] ifadesi aynı şey

	printf("a  = %p",a); // aşağıdaki ile aynı
	printf("&a[0]  = %p",&a[0]);

	Mülakat sorusu
	a nın array decay olarak kullanılmadığı bir yer var
	sizeof içinde kullanıldığında array decay olarak işlem görmüyor

	printf("sizeof(a) = %zu",sizeof(a)); // bu dizinin tamamının tuttuğu alanı verir
	printf("sizeof(&a[0]) = %zu",sizeof(&a[0])); //burası ise sadece ilk elemanın tuttuğu alan.

	
	int a[5] = {0}
	int b[10] = {0}

	int *pa = a;
	int *pb = b;  pointera dizilerin ilk eleman adresleri verilmiş.
	bu tip örnekler çok


	------------------------------
	Özet kullanımlar (şimdilik)
	int x = 10;
	int a[10];
	
	int *p = &x;
	int *q = p;
	int *pa = a;

	----------------------------
	Aşağıdaki kafa karıştırabilir ama geçerli

	int x = 10,*p = &x,a[]= {1,3,5},*q = a;

	-----------------------------

	int a[] = {5,3,7};
	int *ptr = a;

	hepsi aynı çıktıyı verir
	printf("a   = %p\n",a);
	printf("&a[0]   = %p\n",&a[0]);
	printf("ptr   = %p\n",ptr);

	-----------------------------

	
	int x = 10;
	int *ptr = x;  herzaman yanlış.Sentaks hatası değil ama yanlış.
	yani 
	int * = int işlemi yapıyoruz. int ten int* a implicit dönüşüm var.
	işlem yapılır.ama hatalı bir işlem.
	Bu işlem genelde warning verir.
	C++ ta direkt sentaks hatası.

	double x = 1.0;
	int *ptr;
	ptr = &x; bu da yanlış
	int * = double işlemi yapılıyor.yine implicit dönüşüm yapıyor.
	işlem ok ama hatadır bu işlem.warning verir.
	C++ ta yine sentaks hatası.

	===============================
	===============================

	* Dereferencing / Indirection Operator.İçeri Operatörü
	binary infix olursa çarpma
	unary prefix olarak kullanılırsa dereferencing operatörü.

	Operatör öncelik sıralamasında 2. sırada
	2. sıra sağdan sola doğruydu.

	Dereferencing operatörünün operandı address ifadesi olmak zorunda
	asi takdirde compile time da sentaks hatası olur.

	int x = 10;
	int *ptr = &x;
	int a[] = {1,4,5,6,7}

	// *234 hatalı
	// *x hatalı
	// *&x çalışır
	// *ptr çalışır
	// *a çalışır.

	------------------------------

	int x = 10;

	*&x = 45; // bu ifade geçerli. öncelk sırasında sağdan sola doğru gidilir
	çünkü 2. öncelik sırasında. x in adresinin dereference değeri kendisidir.
	yani aslında 
	x = 45 ile aynı.

	hatta
	++*&*&*&*&*&*&x; bu bile geçerli. :D
	
	---------------------------------

	int a[] = {7,24,55};
	*a = 44;  
	a[0] = 44; demek aslında array decaydan geliyor.

	---------------------------------

	int x = 10;
	int *p = &x;
	*p = 98;	yani x = 98 yaptı.En sık kullanılan tema.
	
	---------------------------------

	int x = 1;
	int *p = &x;
	p burada pointer, x ise pointee yani gösterilen yada point edilen.

	*p, x in kendisidir.

	// p =   burası adres olmalı
	// *p =   burası x e atanabilen bir değer olmalı.

	-------------------------------------

	int x = 10,*p1 = &x,*p2 = p1,*p3 = p2;
	++*p1; // hepsi x in kendisi anlamında ve ++ operatörü ile işleme girmiş.
	++*p2;
	++*p3;
	bu x i üç kere artırıyor. x = 13 oluyor.

	NOTU OKUYAN KİŞİ
	LÜTFEN ÖNCELİK SIRASINI UNUTMA. SAĞDAN SOLA DOĞRU.

	===================================================
	===================================================

	POINTER NE İŞE YARIYOR.

	void func(int a)
	{
		a = 23;
	}

	int main()
	{
		int x = 10;
		func(x);
		printf("x = %d",x);
	}

	Yukarıdaki örnekte x en son kaçtır?
	x halen 10 dur. çünkü fonksiyona gönderilen x ve daha sonrasında a olarak
	fonksiyonda işleme sokulan farklı bir obje, x değil.
	adreslere bakılırsa eğer görülür.Call by value.


	void func(int a)
	{
		a = 23;
		printf("&a = %p\n",a); // a nın adresi
	}

	int main()
	{
		int x = 10;
		func(x);
		printf("x = %d\n",x);
		printf("&x = %p\n",x); // x in adresi ve farklı objeler bunlar.
	}

	a ve x farklı adreslerde olduğunu yazar.

	--------------------------------------

	C de eğer bir yerel değişkenin başka bir fonksiyon tarafından değiştirilmesini istiyorsak
	bu değişkenin kendisini fonksiyona göndermemiz gerekiyor.
	Başka dillerde kullanımı daha kolay olabilir fakat C de pointer semantiği ile
	yapılıyor bu iş. Call by reference.

	Aşağıdaki gibi yapılır.

	void func(int *ptr)
	{
		*ptr = 100;
	}

	int main()
	{
		int x = 10;

		func(&x);
	
		printf("x = %d\n",x);
	}

	işte burada x = 100 görülür.

	------------------------------------------------

	Örnek
	mesela iki değişkeni takas yapacağım

	int a,b;
	printf("iki degisken girin : ");
	(void)scanf("%d%d",&a,&b);

	printf("a = %d    b = %d",a,b);

	int temp = a;
	a = b;
	b = temp;

	printf("a = %d    b = %d",a,b);

	Yukarıdaki takas işlemi gibi işlemleri sık sık yapacaksam eğer,
	bunu kod tekrarını engellemek ve daha taşınabilir bir kod olması amacıyla
	function haline getirmek daha mantıklı.

	void swap(int x, int y)
	{
		int temp = x;
		x = y;
		y = temp;
	}

	int main()
	{			
		int a,b;
		printf("iki degisken girin : ");
		(void)scanf("%d%d",&a,&b);

		printf("a = %d    b = %d",a,b);

		swap(a,b);

		printf("a = %d    b = %d",a,b);

	}

	Yukarıdaki kod x ile y nin yerini değiştirmez. :D
	Çünkü a ve b, x ve y değil.

	------

	Bunu çözmek için call by reference ile çağırmamız lazım fonksiyonu

	void swap(int *pa, int *pb)
	{
		int temp = *pa;
		*pa = *pb;
		*pb = temp;
	}

	int main()
	{
		int a,b;
		printf("iki degisken girin : ");
		(void)scanf("%d%d",&a,&b);

		printf("a = %d    b = %d",a,b);

		//swap(a,b);
		swap(&a,&b);

		printf("a = %d    b = %d",a,b);

	}

	Call by reference ile takas işlemi yapılır.

	int x = 10,y = 56;*px = &x,*py = &y;
	swap(px,py);
	takas eder

	--------------------------------------
	--------------------------------------

	NEDEN CALL BY REFERENCE KULANILIYOR.

	ÖYLE DURUMLAR VAR Kİ BİR DEĞİL, DAHA FAZLA NESNENİN DEĞERİNİ DEĞİŞTİRMEK
	GEREKİYOR DİYELİM.BU TİP DURUMLARDA KULLANILIR.NORMALDE FUNCTIONLAR 1 DEĞER
	RETURN EDER AMA BİZ 3 DEĞERE İHTİYAÇ DUYUYORUZ DİYELİM, BU TİP DURUMLARDA İHTİYAÇ OLUR

	MESELA 
	scanf("%d%d%d",&x,&y,&z);
	call by reference ve 3 değere tamsayı atandı.

	-------------------

	ÖRNEK

	int scan_int(int *ptr)
	{
		int c;
		*ptr = 0;
		while((c = getchar()) != '\n') // getchar karakter nosu return eder.
		{								// 5 sayısının karater nosunu bulmak için 5 - '0' 
			*ptr = *ptr * 10 + c - '0';	// yazmak gerekiyor mantıken.
		}

	}

	int main()
	{
		int sum;
		printf("bir tamsayi girin: ");
		scan_int(&sum);

		printf("sum = %d",sum);

	}

	----------------------------------

	Daha önemli sebebi ise yukarıda yazılmıştı
	Fonksiyonlar call by value ile tek değer döndürür.
	Ama biz 3-4-5... değeri değiştirecek fonksiyona ihtiyaç duyarız genelde.
	bu sebeple ihtiyaç var.Veya bir değer göndeririz hesaplamaları gönderdiğimiz
	değere yazar.bu da olabilir.

	2.17 de örneği yazıyor ben kabaca yazayım

	double get_circle(double radius)
		return 3.14 *radius*radius


	double r = 23.4242
	double area

	area = get_circle(r)
	printf area

	yukarıdaki call by value

	--------------

	Call by reference ile yazarsak


	void get_circle(double radius,int *p_area)
		*p_area = 3.14 * radius * radius


	double r = 23.4242
	double area

	get_circle(r,&area)
	printf area

	// burada gönderdiğim area değişkenine atadı.

	--------------------------------------------

	Bu tip basit işlemlerde call by value seçilebilir.
	Hesaplanacak değer tamsayı veya reel sayı ise, call by reference yöntemi
	biraz daha karmaşık hale getiriyor işi.
	Call by value burada doğru tercih olabilir.


	AMA !
	Hesaplanacak değer bellekte 50 byte 100 byte 200 byte yer kaplıyorsa, 
	iki yöntem arasında çok büyük bir maliyet farkı var.
	Assembly seviyesinde
	çağrılan fonksiyonun geri dönüş değeri geçici bir nesnede tutuluyor.
	bizde bu geçici nesneden x = func() gibi ifadeyle kendi nesnemize aktarıyoruz.
	sonra bu temp nesnede siliniyor.
	Yani 2 adet bellek kopyalama var.
	1. return değerinin temp alanına yazıması
	2. çağıran kodun return değerini kendi değişkenine aktarması.

	Burada Call by reference şeklinde kullanılması çok daha iyidir.
	2.26 da struct yazıyor ve gösteriyor.ben yazmayacağım. 

	2 adet 1608Byte alan kopyalamak yerine 4 bytelık bir pointer adresi yazıyoruz.
	Çok ciddi bir fark.

	AYnı zamanda birden fazla değeri değiştirebiliriz bu yöntemle.

	func(a,b,c,&d,&e,&f)  mesela burada d e f değişkenleri tamamen değiştirilip
	main functiondan erişilebilir
	

	*/


	


}