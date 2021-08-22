#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "nutility.h"

#define		SIZE	100

int gx = 23;
int* func(void)
{
	// code
	return &gx;
}

int gy = 98;
int* foo(void)
{
	//code
	return &gy;
}

int* get_array_min(const int* p, int size)
{
	const int* pmin = p;
	for (int i = 0; i < size; i++)
	{
		if (*pmin > *(p + i))
			pmin = (p + i); // veya pmin = &p[i];
	}

	return (int*)pmin; // bu casting daha sonra açıklanacak.
}

void selection_sort(int* ptr, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		swap(ptr + i, get_array_min(ptr + i, SIZE - i));
	}

}



int main()
{
	/*
		FUNCTION RETURNING POINTERS

		Yani fonksiyonu çağırdığımzda geri dönüş değeri olarak adres veriyor.
		int *func(void);  fonksiyonun geri dönüş değeri int * türü.
		bunun geri dönüş değerini tutan nesne int * türünden bir nesne

		int *ptr;
		ptr = func();
	
		burada
		*ptr = 99; yapılırsa. adresi gönderilen nesnenin değerini 99 yapıyor.
		
		int x = 10;
		int *p1 = &x;
		int a[10] = {0};
		int *ptr;

		ptr = &x;
		ptr = p1;
		ptr = a;
		ptr = &a[0];
		ptr = func();   
		hepsi ok

		Mesela function ile benim code file ayrı source file larda olabilir.
		bir değişkene erişmek istediğimde bu funksiyon adresini bana göndebilir.

		aşağıda function return değeri int * kullanıldı ve değer değiştirildi.
		int* ptr = func();
		printf("g = %d\n", *ptr);
		*ptr = 99;
		printf("g = %d\n", *ptr);
		++*ptr;
		
		aynı şekilde 
		++*func(); func ın gösterdiği nesnenin değerini 1 artırır.
		Bunu genelde böyle yazmazlar

		--------------------------

		printf("func = %d      foo = %d\n", *func(), *foo());
		swap(func(), foo());
		printf("func = %d      foo = %d\n", *func(), *foo());
		
		return değerleriyle swap ettik.swap zaten argüman olarak adres alıyor.
		func ve foo da adres gönderiyor. 

		---------------------------

		int a[] = {10,20,30,40,50};
		int* func(void)
		{
			// code
			return a;
		}

		print_array(a,5);
		func()[2]++;   legal burası. a[2] = 31 yapar.
		print_array(a,5);

		----------------------------------
		----------------------------------
		----------------------------------

		UB Durumu - Çok Önemli.
		En klasik code hatası.
		Sınav sorusu

		int *func(void)
		{
			int x = 10; // otomatik ömürlü nesne. static int x = 10; olsaydı sıkıntı yoktu.

			return &x; // otomatik ömürlü nesnenin adresi geri dönüş değeri olmuş.UB
		}				// X in hayatı buradan çıkılınca bitecek. yani UB.

		int main()
		{
			int *ptr = func(); // buradaki ptr x in bir zamanlar tutulduğu yerin adresini
			*ptr = 765;			// tutuyor. Ama orada artık X yok. X öldü. Dangling pointer.
			printf("*ptr = %d",*ptr);
		}

		-------------------------------

		int a[10];

		int *foo()
		{
			int *p = a + 5;
			return p;
		}

		int main()
		{
			int *ptr = foo();
			*ptr = 123213;   // TAMAMEN GEÇERLİ.SIKINTI YOK.
		}


		------------------------------
		------------------------------

		Aşağıda UB YOK.Çünkü Adresi gönderilen nesne hayatına main içerisinde devam ediyor.

		int * foo(int *ptr)
		{
			++*ptr;
			return ptr;
		}

		int main()
		{
			int x = 35;
			int *p = foo(&x);    // Burada x in adresi foo ya gönderilmiş ve yeni
			*p *= 10;			// değişken olarak ptr a kopyalanmış. foo x in adresini return ediyor
			printf("%d\n",x);	// scope tan çıkılınca
								// aynı adres yani x in adresi main içerisinde devam ediyor
								// bu sebeple UB YOK.
		}

		--------------------------------
		--------------------------------

		char * get_name(void)
		{
			char str[100];
			printf("ismini yaz: ");
			scanf(%s,str);
			
			return str;
		}


		int main()
		{
			char *p = get_name();	// Burada da UB var.Yukarıdaki str dizisinin ömrü otomatik.
			printf("isminiz %s",p);	// fonksiyondan çıkar çıkmaz artık hayatıda bitti.
		}							// return edilen yeri kullanmaya çalışmak erişmek UB.

		--------------------------------------
		--------------------------------------

		TANIMSIZ DAVRANIŞ OLMAMASI İÇİN ADRES DÖNDÜREN FOKSİYON NE DÖNDÜREBİLİR

		1 - static ömürlü nesne adresi
			a - global nesne adresi
			b - static yerel nesne adresi
			c - string literalleri (string literaller static ömürlü olan char dizilerdir.)

		2 - Client koddan aldığı adresi tekrar geri döndürmesi.Mesela dizi adresi isteyen bir
			pointer fakat fonksiyonun geri dönüş değeri aynı dizinin adresi. o adres zaten hayatta
			fonksiyon çağrısı bittiğinde halen dizi hayatta. Örneği yaptık daha önce yukarıda.

		3 - Dinamik ömürlü nesne adresi döndüren fonksiyonlar. Fabrika fonksiyonları.

		NOT: Otomotik ömürlü nesnenin adresini döndürünce fonksiyon, günah işlemiş oluyor :D


		ÖR: 
		1 - c örneği
		
		char * get_day_name(int dayno)
		 {
			switch(dayno)     // Burada tanımsız davranış YOK.Çünkü hepsi 
			{					//  static ömürlü char array.
				case 1: return "pazartesi";
				case 2: return "sali";
				case 3: return "carsamba";
				case 4: return "persembe";
				case 5: return "cuma";
				case 6: return "cumartesi";
				case 7: return "pazar";
						
			}
			return "";
		 }

		-----------------------------------------

		char * get_name(void)
		{
			char str[100];
			printf("ismini yaz: ");
			scanf(%s,str);

			return str;
		}
		 burada derleyici uyarı veriyor local variable or temporary olduğu için.
		 UB oluşturur çünkü bu


		 ---------------------------------------------
		 ---------------------------------------------
	

		// bir arrayin en büyük elemanının adresini döndüren fonksiyon
		bu sayede en büyük elemana bir değerde atanablir.Öbür türlü sadece o elemanın 
		değerini gönderecekti.değiştirme yapılamayacaktı.
		burada adres gönderiyor.

		int *get_array_max(const int *p, int size)
		{
			const int *pmax = p;
			for(int i = 0; i < size ; i++)
			{
				if(*pmax < *(p+i))
					pmax = (p + i); / veya pmax = &p[i];
			}

			return (int *)pmax; // bu casting daha sonra açıklanacak.
		}

		int main()
		{
			int a[SIZE];
			set_random_array(a,SIZE);
			print_array(a,SIZE);

			int *ptr = get_array_max(a,SIZE); // a zaten burada var ve gönderdik.
											  // pmax func. scope ta bitti ama gönderdiği
											  // adres a nın içerisinde bir adres ve a yaşıyor.
											  // hiçbir hata yok.En güzel örneklerden biri.
			printf("dizinin en büyük elemanı %d indisi %d",*ptr, ptr -a);

			print_array(a,ptr-a +1); en büyük elemana kadar, en büyükte dahil yazdırıyor.
			print_array(ptr,SIZE -(ptr - a)); en büyük elemandan sonuna kadar hepsini yazdır.

			-----

			Aynı şekilde get_array_min de yazılabilir.
			aşağıda yazılıyor

			int *get_array_min(const int *p, int size)
			{
				const int *pmin = p;
				for(int i = 0; i < size ; i++)
				{
					if(*pmin > *(p+i))
						pmin = (p + i); / veya pmin = &p[i];
				}

				return (int *)pmin; // bu casting daha sonra açıklanacak.
			}

			
			--------------------------------------------
			--------------------------------------------
			--------------------------------------------
			--------------------------------------------

			Selection Sort
			
			Küçükten büyüğe yaparsak

			98 78 54  77 5 88 46 47 68
			5 78 54 77 98 88 46 47 68
			5 46 54 77 98 88 78 47 68
			5 46 47 54 77 98 88 78  68
			... devam eder.

			Bunun için (n -1 )* (n -1) -> n -1 eleman için n -1 kere yapılır. O(n2)
			iki eleman kaldığında son elemanı tekrar kıyaslamaya gerek kalmıyor
			bu nedenle n -1 elaman

			void selection_sort(int *ptr,int size)
			{
				for(int i = 0;i < size -1 ;i++)
				{
					swap(ptr + i, get_array_min(ptr + i, SIZE - i));
				}
			
			}


			int a[SIZE];
			set_random_array(a, SIZE);
			print_array(a, SIZE);

			selection_sort(a, SIZE);
			print_array(a, SIZE);

			--------------------------------------------
			--------------------------------------------
			--------------------------------------------

			Türler ve Önemi / Casting

			T bir tür

			T *
			const T *

			yada

			int *   
			const int *  farklı adres türleri bunlar

			int x = 10;
			&x; -> bunun türü int *

			const int y = 20; 
			&y; -> bunun türü const int *

			------------

			int a[5] = {123,213,213,6,7};
			const int b[5] = {345,43,543,5,5}

			a; -> bu int *
			b; -> bu const int * dır
			
			--------------

			int x = 10;
			int *ptr = &x;
			const int *p = &x;

			ptr ; -> bu int *
			p; -> bu da const int *

			----------------
			----------------

			C nin kuralları 

			int * -----> const int * a dönüşümü doğru kabul ediyor.Problem yok.
			const int * -----> int * a dönüşüm C++ sentaks hatası, C de uyarı.

			int x;
			int y = 23;
			const int *p = &x;  burada sorun yok çünkü x nesnesinin türü int *
			kopyalandığı nesne ise const int *.

			int *ptr;

			p = ptr;  burada hiçbir sorun yok.

			--------------------

			int * dan const int * a otomatik tür dönüşümü var.
			fakat const int * dan int * a C++ ta sentaks hatası, C de ise uyarı.
			warning C4090 different const qualifier  uyarı mesajı alınır.

			Bir istisnai durum var


			int *get_array_min(const int *p, int size)
			{
				const int *pmin = p;
				for(int i = 0; i < size ; i++)
				{
					if(*pmin > *(p+i))
						pmin = (p + i); / veya pmin = &p[i];
				}

				return pmin; 
			}

			burada const türünden nesneyi geçici bir nesneye kopyalıyor bu daha sonra
			bunu return ediyor.Bu sırada da warning mesajı alınıyor zaten.

		
		1. yol
		// burada return(int *)pmin; yazılır en sonda. C de daha çok bu kullanılır
		// buna const cast deniyor.Bu kodun bilerek yazıldığını gösteriyor.
		// okuyanda şaşırmaz bu şekilde. 
		
		2. yol
		// const int *get_array_min(const int *p, int size) yada bu yazılır tanımda.
		C++ ta daha çok bu kullanılıyor.s


		--------------------------------------------------------------
		--------------------------------------------------------------

		UB Var mı ? 

		int x = 10;
		const int * p = &x;

		/// code...

		// p ile x e okuma amaçlı eriştik

		// int * ptr = p; // c++ sentaks hatası, C de uyarı mesajı.
						// bu tip durumlarda otomatik dönüşüme bırakmadan cast etmemiz
						// daha uygun olur

		int * ptr = (int *)p;  // burası şimdi oldu
		*ptr = 12; // UB yok. x const değil ptr const değil.


		---------------------------------------------------
		
		int *foo(int x)
		{
			return &x;  // BURASIDA UB. x local variable. fonksiyondan çıkınca hayatı bitti.
						// array gibi adres göndermiyoruz burada. yeni bir değişkenin adresi bu.
						// sadece function scope ta yaşamı sürüyor.
		}
		
		int a;
		int *foo(void)
		{
			return &a;  // burada UB yok.LEGAL.
		}


		int *foo(int *ptr)
		{
			return ptr;  // burada da UB yok.LEGAL.
		}


		---------------------------------------------------
		---------------------------------------------------
		---------------------------------------------------
		---------------------------------------------------

		NULL POINTER
		---------------------------------------------------

		NULL bir makrodur.Yani önişlemci programa tanıtılan bir isimdir.
		NULL bir identifier değildir. NULL bir keyword de değildir.
		NULL makrosu bir çok standart başlık dosyasında tanımlanmıştır.
		stdio.h
		stdlib.h
		stddef.h
		time.h
		string.h
		...

		NULL macrosu bir adres sabitidir.bunu null pointer olarak telafuz etmek gerekir.
		sadece null değil. null pointer doğrusu

		null character
		null string
		null pointer

		null derken hangisini kastediyoruz?
		yanlış anlaşılma olmasın diye buna NULL pointer demek çok mantıklı.


	---------------------
		
		bazı dillerde
		null nil nill gibi kullanımlar var.
		bu bir değişkenin değeri olmadığını gösteriyor.

		C deki NULL bu anlamda değil.
		NULL pointer, pointer değişkenlere ilk değer verme veya atama yapmak için
		kullanılmalıdır.Pointer olmayan değişkene NULL pointer ile atama yapmak yada 
		ilk değer vermek yanlıştır yapılmamalıdır.

		int x = NULL; bu yanlıştır.Yapılmamalıdır.
		
		Ancak herhangibir türden pointer değişkene NULL pointer ile atama veya 
		ilk değer verme yapılabilir.

		int *ptr = NULL; Geçerli
		double *dptr;
		dptr = NULL; Geçerli

		------------------------------------------------------------

		Değeri NULL pointer olan pointer değişken geçerlidir.validdir.
		Değeri NULL pointer olan pointer hiçbir nesneyi göstermeyen pointer değişkendir.
		NULL pointer dereference etmek UB dir.[] veya * ile işleme sokmak mesela.
		NULL Pointerı ++ -- + - operatörlerinin operandı yapmak UB dir.

		Aşağıdaki işlemler legaldir
		
	1-	Aşağıdaki kodda hata yok.Legal
		int * ptr = NULL;
		if(ptr == NULL)
			printf("evet dogru\n");  

	2-	Eğer iki pointer da NULL pointer ise ikisi birbirine eşittir.
		Kod legal
		int *a = NULL;
		int *b = NULL;
		if(a == b)
			printf("Esittir\n");

	3-	Logical yorumlamalarda kullanılır
		Eğer if, ternary op, for, while, && || ... 
		gibi logical yorumlamalara tabi tutulan yerler varsa
		burada NULL pointer 0 dır yani yanlıştır.

		if(ptr != NULL)  yazmak ile if(ptr) yazmak aynı anlamda

		if(ptr == NULL)	 yazmak ile if(!ptr) yazmakta aynı anlamdadır.

		-----------------------------------------------------------

		Normal olarak bir pointer değişkene bir tamsayı ataması yanlıştır.
		C++ ta sentaks hatası.

		int *ptr;
		int ival = 10;
		ptr = ival;  mesela bu C++ ta sentaks hatası.Daha önce gördük.C de de yanlıştır
		ama sentaks hatası değildir.int ten int * a dönüşüme zorlanıyor otomatik olarak.
		Ama yanlıştır. Yapılmamalı.

		Bu durumun bir istisnası var.
		Eğer pointer olarak değişkene tam sayı sabiti olarak 0 değişkenini atarsak
		derleyici 0 sabitini NULL pointera dönüştürür.Buradaki dönüşüme 
		Null Pointer Conversion denir.

		ptr = NULL ile ptr = 0 yazmak arasında semantic olarak fark yok.

		şu hatalı
		int ival = 0;
		int *ptr = ival; // bu yanlış.0 ı sabit olarak atamak gerekiyor.

		-----------------

		int *ptr = NULL; // daha çok kullanılan convension bu. Önerilende bu
		int *ptr = 0; // buda doğru tabi.

		mesela 
		srand((unsiged)time(0)) -> bununla srand((unsiged)time(NULL)) aynı
		mesela NULL için başlık dosyası import etmek gerekir ama 0 da include a gerek yok
		Fark bu. NULL macrosu birsürü başlık dosyasında var çünkü.

		Özellikle stddef.h header file ı include etmek mantıklı.
		Çünkü çok küçük bir başlık dosyası bu.

		preprocessor NULL yerine 0 mı yazıyor ?
		Olabilir.Derleyiciye bağlı. Visual C++ ta ((void *)0) şeklinde define ediliyor.


		Static ömürlü bir Pointer değişkeni değer vermeden tanımlarsak bu değişken 
		hayata NULL pointer değer ile başlar.

		int *g;
		int main()
		{
			if(!g)
				printf("g is NULL");
		}

		
		int * a[10] = {}
		burası bir pointer dizisi.ilk elemana 0 verirsem yani NULL, diğer tüm elemanlar
		hayata NULL pointer olarak başlar.

		------------------------------------------------
		------------------------------------------------
		------------------------------------------------

		NULL Pointerın Kullanıldığı 4-5 Tema var

		En çok kullanılan tema, geri dönüş değeri adres olan fonksiyonlar.
		İşin başarılamaması durumunda geri dönüş değeri olarak kullanılıyor.
		
		ÖR:
		File *f fopen -> mesela burada fopen NULL pointer döndürürse başarısız olmuştır
		
		if(!f)
		{
			printf("File acilamadi\n");  // başarısız olursa buraya girer.		
		}

		malloc eğer NULL Pointer döndürürse bellek alanı allocate edememiş demektir.

		DERS Bitti...
	*/


	int a[SIZE];
	set_random_array(a, SIZE);
	print_array(a, SIZE);

	selection_sort(a, SIZE);
	print_array(a, SIZE);


		
}
