#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include "nutility.h"

#define		SIZE		100

int main()
{
	/*
	bir fonksiyonun parametresi pointer ise biz buna dizinin adresini gönderebiliriz.

	pointer daki veriye p[i] veya *(p+i) ile erişilir.

	dizi değişmeyecekse const int * ptr şeklinde parametre tanımlamak mantıklı.

	fonksiyon parametrelerini başka bir fonksiyona argüman olarak gönderebilirim.

	--------------------------------------------------------------
	--------------------------------------------------------------
	
	// Standart Sapma fonksiyonu. Her bir elemanın ortalamadan farkının karesini toplayacağız
	// std. sapma = çıkan sonucun size a bölümünün karekökü.
	// bir önceki dersteki örnekle birleştirilince çalışır.
	
	double get_std_dev(const int *p, int size)
	{
		double mean = get_mean(p,size);
		int sum_square = 0;

		while(size--)
		{
			sum_square += (*p++ - mean) * (*p++ - mean);
		}
		
		return sqrt(sum_square/size);

	}

	--------------------------------------------------------------
	--------------------------------------------------------------

	//Elemanları reverse etme kodu. nutility ye eklendi
	void reverse_array(int *p,int size)
	{
		for(int i = 0;i< size /2 ;i++)
		{
			swap(p + i , p + size -1 -i);
		}
	}

	--------------------------------------------------------------
	--------------------------------------------------------------
	//Bu da nutility ye eklendi.
	void get_min_max(const int *p, int size,int *max, int *min)
	{
		*max = *min = *p;
		for(int i = 1;i<size;i++)
		{
			if(*min > *(p+i))
				*min = *(p+i);
			if(*max < *(p+i))
				*max = *(p+i);
		}
	}

	-------------------------------------
	-------------------------------------

	void bsort(int *p,int size)
	{
		for(int i = 0; i< size-1;i++)
			for{int j = 0; j<size -1 -i;j++}
				if(p[j] > p[j+1])
				{
					//swap(&p[j],&p[j+1]); buda çalışır fakat alttakini tercih ettik
					swap(p+j > p+j+1);				
				}
	}

	-----------------------------------------------------------
	-----------------------------------------------------------


	void copy_array(int *pdest,const int *psource,int n)
	{
		while(n--)
			*pdest++ = *psource++;
			
	}

	-----------------------------------------------------------
	-----------------------------------------------------------
	
	istersem kaç adet kopyalanacağını, source ve destination arraylerinde neresinden
	başlanacağını yazabilirim.
	
	p nin 60 index li elemanından, c nin 20 indisli elemanına 20 adet
	eleman kopyalıyor.

	int c[SIZE] = { 0 }; // 0 a atanmasa veri girilmemiş elemanları yazdırmaya çalışmak UB.
	copy_array(c + 20, p + 60, 20); //c[20],p[60],20 şeklinde de yazılabilirdi.
	print_array(c, SIZE);

	-----------------------------------------------------------
	-----------------------------------------------------------
	
	Bir fonksiyonun parametresinin pointer olduğunu göstermenin 2 yolu var.
	
	birincisi * notasyonu
	Örnek : func(int *p) 

	İkincisi [] notasyonu
	Buradaki p bir pointer bir dizi değil. Dizi görüntüsünde ama değil.
	Örnek : func(int p[]) 
	
	Köşeli parantezin içine rakam girilmesi önemsiz.
	Örnek: func(int p[10]) burası çok anlamsız.Sentaks hatası değil ama
	10 elemanlı bir dizi anlamına da gelmiyor bu.
	Bunu kullananlar var ama kullanmayanlarda var.
	Şahsi olarak bana diğeri daha mantıklı geliyor.

	Yani kısaca 

	func(int p[]) Eşittir func(int *p)
	p[] burada pointer olduğunu belirtiyor dizi değil.

	---------------------------------------------------------
	---------------------------------------------------------
	---------------------------------------------------------

	Dizi Pointer farklılığı.
	
	Dizi contiguous olarak bellekte n tane nesnenin birlikte tutulduğu nesneler topluluğu.
	Pointer ise sadece adres tutar.

	Mesela
	int *p;

	p[5] = 12;  TANIMSIZ DAVRANIŞ(UB)

	Array decay den dolayı karıştırılabilir.
	Array decay dizi ismini dizinin ilk elemanının adresine dönüştürüyor.


	---------------------------------------------------------
	---------------------------------------------------------
	---------------------------------------------------------

	Geçerli Pointer ve Geçersiz Pointer

	void func(int p[]) Şeklinde olabilir.
	void func(int *p) bu şekilde de olur.

	-------------------------------------------

	Valid Pointer
	Invalid Pointer
	Sentaks hatası demek değil bu kavram.

	int *p; şuanda geçersiz.KUllanılamaz şuanda
	*p; TANIMSIZ DAVRANIŞ.
	p = &x; şuanda geçerli.Kullanılabilir.

	--p; şuanda invalid.Geçersiz halde

	int a[5] = {0};
	int *p = a + 10; Invalid.dizinin böyle bir elemanı yok.

	int *ptr = &p; burası c++ sentaks hatası C de uyarı.
	çünkü pointer to pointer(**) durumu var.

	------------------------------------

	ilk değer verilmemiş atama yapılmamış pointer değişken geçersizdir.

	Dangling Pointer.
	Dynamic Memory Management kısmında aşırı önemli olacak.

	Şu Demek
	bir nesnenin adresini tutuyordu ama o nesnenin hayatı bitince artık 
	geçerli bir adres değeri tutmadığı için geçersiz pointer.

	int *ptr; // ptr is an invalid pointer
	if(1)
	{
		int x = 10;
		ptr = &x; // ptr is a valid pointer
	}

	ptr; // şuanda yine invalid çünkü x otomatik ömürlü ve 
	ve hayatı scope tan çıkınca sona erdi.

	-------------------------------------------
	-------------------------------------------
	-------------------------------------------

	int a[5] = {0};

	int *ptr = a+5; // yada a[5]
	a+b dizinin son elemanının adresi değil. dizinin bittiği yerin adresi.
	son eleman a+4 çünkü. Bu a+5 adresi yani.
	dizinin bittiği yerin adresi C/C++ dillerinde özel bir öneme sahip.
	
	bu dizinin bir elemanı daha olsaydı a+5 olacaktı zaten ama yok.
	şimdiki durumda a+5 i kullanmak Sentaks hatası değil. Kullanmak derken dereferencing
	yapmaktan bahsetmiyor. bu adresi dereference etmek TANIMSIZ DAVRANIŞ.
	
	bu adres geçerli bir adres ama geçerli demek dereferencing yapılır demek değildir.
	Yani dizinin bittiği bu adres geçerli bir adres.

	int *p = a+5; burası geçerli bir adres. ama Dereferencing yapmak TANIMSIZ DAVRANIŞ
	dereferencing ile kullanılmayacak.Tekrar tekrar yazdım anlaşılsın diye.
	
	Karşılaştırma işlemlerinde kullanılacak bu.

	int x = 10
	int *p = &x;

	++p; bu geçerli
	her bir nesne bir elemanlı tekil bir dizi gibi düşünülebilir.
	Geçerli ama *p yapılamaz.Bu TANIMSIZ DAVRANIŞ.

	int a[10] = {0};

	int *ps = a; ilk eleman.
	int *pe = a+10; bittiği yerin adresi.

	pe -ps = 10 dur ayrıca.

	a[10]; bu TANIMSIZ DAVRANIŞTIR.

	ama 

	&a[10]; ama burada tekrar addresi alındığı için UB YOK burada.
	yani adresi alındında nesneye erişmek için bir kod üretmiyor compiler ve UB YOK.

	yada 

	a+10 UB YOK.

	NULL pointer denen bir adres sabiti var.
	bir pointera bu atanınca geçerli bir pointer oluşuyor ama
	hiçbir nesneyi göstermeyen bir pointer oluşuyor.
	İleride görülecek.


	------------------------------------------------------------
	------------------------------------------------------------
	------------------------------------------------------------

	POINTERLAR VE KARŞILAŞTIRMA İŞLEMLERİ

	int *p1;
	int *p2;

	p1 == p2
	p1 != p2

	p1 < p2
	p1 <= p2
	p1 > p2
	p1 >= p2

	-------------------------

	1- İki pointerda aynı nesneyi gösteriyorsa eşittir.
	

	int x = 10, y = 20;
	int *p1 = &x;
	int *p2 = &y;

	if(p1 == p2)
	{
		printf("Evet Eşit\n");
	}
	else
		printf("eşit değil\n")   Eşit değil sonucu verecek.

	p1 = &y; yaparsak sonuç eşit çıkar.
	p1 = p2 işte aynı şey.

	-----------------------------

	2- İki pointerda aynı dizinin bittiği yerin adresini tutarsa yine eşittir.

	NOT: Bittiği yerin adresi önemli. Bittiği yerin adresinden bir sonrası geçersiz.
	Bu önemli.

	int x[10] = {0};
	int *p = x+9;
	int *q = x[10];
	
	bunlar eşit değil

	p++;

	artık eşitler. if p == q ile bakılarak bulunur.

	int *ptr = a;
	int *pend = a+SIZE;
	while(ptr != pend) // veya ptr < pend olur. aynı şey.hatta c++ ta tercih edilen budur.
	{
		printf("%3d ",*ptr);
		ptr++;
	}

	---------------------------------------

	3- NULL Pointer olursa.Yani hiçbir nesnenin adresini tutmuyorsa geçerli pointerlardır
	ve eşittir.

	int x = 10;
	int *p1 = &x;
	int *p2 = NULL;

	if(p1 == p2)
		printf("Esittir\n");
	else
		printf("esit degil.");

	--------------------------------------------
	--------------------------------------------
	--------------------------------------------

	char s1[100];
	char s2[100];

	printf("iki kelime girin\n");
	scanf("%s%s",s1,s2);

	if(s1 == s2) // always false :D diziyi değil adresleri karşılaştırıyotruz.

	-----------------------------

	p1 ve p2 NULL ptr ise veya dizinin bittiği yeri gösteriyorsa
	dereferencing operatörü ile karşılaştırmak TANIMSIZ DAVRANIŞ
	*p1 == *p2 gibi
	
	iki pointerdan biri null veya bittiği yeri gösteren ptr olsa
	TANIMSIZ DAVRANIŞ.

	-----------------------------------------

	int a = b = 34;
	int *p1 = &a,*p2= &b;

	if(p1 == p2) burası if e girmez.farklı objeleri gösteriyor.

	if(*p1 == *p2) burası if e girer.değerleri kıyaslıyor. Hepsi 34


	-----------------------------------------

	void reverseArray(int *p,int size)
	{
		int *pe = p + SIZE;
		while(p < pe)
		{					// MÜLAKAT SORUSU
			swap(p++,--pe);	// pe nin bir küçüğünü p ile yer değiştir.P yi bir artır.
		}					// pe zaten azaltlıyor işlemden önce.
	}

	----------------------------------------- 
	----------------------------------------- 
	----------------------------------------- 

	POINTER İDİYOMLARI

	profesyonel seviyede yazılan kodlara deniyor.
	İlk başlarda bu şekilde yazmak zor. İlerlettikçe bunları kullanmak daha kolay.

	mesela 
	x = y;
	y = y+1; bu şekilde yazmak yerine

	x = y++; bu bir idiyom.Bunları kullanmak C seviyesini ele verir.daha iyi bir 
	etki bırakır. Kodları en azından bir süredir kullandığımızı gösterir.

	mesela
	while(n--)
	{	
	}

	mesela
	if((x = foo()) < 10)
	{
	}

	mesela
	while((ch = getchar()) != '\n')
	{
	
	}

	Yeni tanışanların genelde bu şekilde yazmıyor. İlerletmiş olanlar yazıyor.
	Bunlar idiyomdur.

	------------------------------------------------

			++x				x++	
	
	C		rvalue			rvalue
	C++		lvalue			rvalue

	------------------------------------------------

	ÇOOOK ÖNEMLİ
	int x = 10;

	&x++;  ->	x++ rvalue exp. dur, & operatörüde lvalue exp a etki eder.Sentaks hatası.
	&++x;  ->	Aynı şekilde sentaks hatası.illegal
	++&x;  ->	&x in degeri rvalue exp. dir. ama ++ operatörü lvalue exp. e ihtiyaç duyar.
				sentaks hatası
	
	int a[10] = {0};
	int *p = a;
	*p++   ->	++ için, p bir lvalue exp dir.* operatörü ise adrese ihtiyaç duyar.Geçerli.
				bu ifade lvalue exp. * operatörü varsa lvalue exp üretir.


	-------------

	int a[5] = {0,10,20,30,40};
	int p = *a;

	// *++p; Geçerli ve ifade sol taraf değeri
	// *++p = -1; ikinci elemana yapıldı atama

	









	*/

	int p[SIZE];
	randomize();
	set_random_array(p, SIZE);
	print_array(p, SIZE);
	printf("min value : %d\n", get_min(p, SIZE));
	printf("max value : %d\n", get_max(p, SIZE));
	
	int min, max;
	get_min_max(p, SIZE, &min, &max);
	printf("pointer ile min = %d\n", min);
	printf("pointer ile max = %d\n", max);
	bsort(p, SIZE);
	print_array(p, SIZE);

	int b[SIZE];
	//copy_array(b, p, SIZE);
	//print_array(b, SIZE);
	
	int c[SIZE] = { 0 };
	copy_array(c + 20, p + 60, 20);
	print_array(c, SIZE);
	
	
}