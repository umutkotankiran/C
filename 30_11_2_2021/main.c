#include <stdio.h>
#include "nutility.h"
#include <stdbool.h>

int main()
{
	/*
	
		C de bir fonksiyon işini yapamazsa NULL Pointer return edebilir.
		Böyle örnekler var.

		malloc mesela başarılı olursa bir dinamik bellek bloğu adresi, başarısız olursa
		NULL ptr döndürüyor.

		yada 
		f = fopen("ahmet.txt","r");
		if(f == NULL)
			printf("dosya acilamadi\n");
			return 1;

		arama fonksiyonlarında da Değeri bulursa değerin adresini 
		başarısız olursa NULL ptr döndürüyor.

		strchr
		strstr

		int *search_val(const int *p, int size, int val)
		{
			while(size--) // for ilede yazılabilir.
			{
				if(*p == val)
					return (int *)p;
				p++;
			}
			return NULL;
		}

		int main()
		{
			int a[SIZE];
			set_random_array(a,SIZE);
			print_array(a,SIZE);
			
			printf("Aranacak degeri girin: ");
			scanf("%d",&sval);
			ptr = search_val(a,SIZE,sval);

			if(ptr)
			{
				printf("%d degeri, %d indisi\n",*ptr,ptr-a);
			}
			else
				printf("Aranan deger bulunamadi\n");

		}

		-----------------------------------------------------------

		bazı fonksiyonlar NULL ptr argüüman olarak gönderebileceğimi söylüyor.
		bunu dökümantasyonda belirtiyor.NULL gönderdiğimizde nasıl çalışacağını
		yazmak zorunda.
		Bazılarında NULL göndermek runtime hatasına yol açabilir.
		Hepsi dökümantasyonda belirtilmeli.

		Bazı fonksiyonların bildirimi

		time_t time(time_t *ptr) -> time_t bir tür eş ismi.

		ya bir nesne adresi istiyor set etmek için
		ya da NULL pointer istiyor. bu tip örnekler var.
		NULL göndermek opsiyon ise dökümantasyonda yazar.

		fflush(FILE *)  ->  bu bir nesnenin adresini istiyor ve ilişkili 
		dosyanın bufferını flush ediyor.Yani bellekteki byte ları dosyaya 
		yazıyor.


		NULL bayrak değişken gibide kullanılabilir.
		mesela

		int *ptr = NULL;
		if(expr)
		{
			ptr = nesne adresi  // if e girerse ptr değeri değişir.
		}


		int *ptr = NULL;
		//dangling pointer

		// ptr geçerli

		// hayatı sona erdi

		burada *ptr = ...  UB olur mesela.

		burada dangling hale gelmş pointer a NULL değerini atamak mesela bir kullanım 
		şeklidir.


		Birde dynamic memory kısmında göreceğiz bunları.


		------------------------------------------------------
		------------------------------------------------------
		------------------------------------------------------

		TÜR EŞ İSİM BİLDİRİMLERİ
		------------------------

		Alias -> takma ad
		type alias -> tür takma adı veya tür eş ismi

		mesela int -> word olsun
		veya  unsigned char -> Byte olsun

		----------------------------

		typedef keywordü ile yapılıyor

		typedef decleration.
		#define preprocessor ile ilgisi yok belki bazı durumlarda benzer işi yapıyor olabilir.
		ama bu bir ismin bildirimini yapıyor.alias veriyor.define ise değiştirme işlemi.
		Zaten pointer tanımlarken farklı iş yapıyor.Örnek verilecek.

		mesela
		bool çok kullanıldığı için
		C99 da karışmasın diye _Bool keyword olarak seçmişler.

		#include <stdbool.h>
		bool x = true; hata vermez. üstteki include edilen library yi silersek hata verir.
		bir macro tanımlanmş.içine bakarsam

		#define bool	_Bool
		#define true	1
		#define false	0	

		aslında define etmişler.

		typedef ise compiler ı ilgilendiriyor. preprocessor ile işi yok.

		Typedef Bildirimleri 3 ayrı derse bölünecek.

		-------------------------------------------------------

		typedef neden kullanılır.
		Türlere daha kısa isimler vermek için, 
		kodun okumasını veyazmasını kolaylaştırmak için,
		veya daha anlamlı isimler vermek için.
		
		daha sonra görülecek yeni ver, türleri tanımlamak için.

		typedef int Word;

		artık Word kullanıldığında, Word ün int türünün bir eş ismi olarak görecek.
		Word x;
		int x;  artık aynı anlamda kullanılmış oldu.



		Word func(Word);
		int main()
		{
			Word x,y,z; Türü kullanabileceğim heryerde türeş isminide kullanabilirim.
			Word a[10]; aslında elemanları int türden 10 elemanlı bir dizidir bu.
		}


		typedef int * IPTR;
		int main()
		{
			IPTR p = NULL;
			int * p = NULL;  bunların arasında hiçbir fark yok.
		}
		

		-------------------------------------
		-------------------------------------

		#define ile arasındaki fark

		#define			IPTR		int *

		mesela artık
		IPTR p; -> int *p; demek burası ok

		IPTR p1,p2; demek int *p1; int p2; ikiside pointer değil !!!!!!!!!!!!

		typedef int* IPTR;

		IPTR p1,p2; demek int *p1; int *p2; demek bu. ikiside pointer !!!!!!!!!!!!!!!!!!!

		-------------------------------------

		typedef const int * CIPTR;

		int x = 10;
		CIPTR ptr = &x;		ile const int *ptr = &x; aynı şey

		-------------------------------------
		
		KURAL!!!

		hangi türe eş isim vermek istiyorsak 3 aşamada yapacağız bunu

		1 - o türden bir değişken tanımla
			int x;

		2 - tanımlamanın başına typedef getir
			typedef int x;

		3 - Değişken ismini tür eş ismi olarak değiştir.
			typedef int Word;


		mesela
		int a[10];

		typedef int a[10]  ->   typedef int ARR[10];  

		ARR a,b,c; artık aynı şey. 
		int	a[10],b[10],c[10]; aynısı.


		----------------

		typedef int counter;
		counter x;
		int y;  tabiki int kullanılmaya devam edilebilir.

		------------------

		typedef int Word;
		typedef int INT32;
		typedef int counter;

		birsürü tanımlanabilir

		---------------------

		typedef int Word,INT32; buda legal

		-----------------

		typedef int Itype;
		typedef Itype Word;
		bu da legal

		artık word int gibi işlem görüyor.

		------------------------------

		ÖNEMLİ
		Mülakat sorusu bu.

		typedef int Word,*Ptr;
		typedef int word; ve typedef int *Ptr; ile aynı

		---------------------------

		typedef int counter;

		int main()
		{
			counter c = 0;  // diyelim ki counter int e sığmayacak ve değiştirmek gerekiyor.
		}					// burada direkt olarak typedef tanımından halledilir iş.

		typedef long long int counter; 

		--------------------------------
		--------------------------------

		Standart Library Typedef Eş İsimleri

		mesela 
		strlen() in geri dönüş değeri size_t
		size_t bir tür değil. bir türün eş ismi.

		bu unsigned int veya unsigned long türünün eş ismi olabilir.
		derleyiciye bağlı.

		typedef unsigned int size_t;

		C std. komitesi belirliyor herşeyi.

		------------------------

		size_t len = strlen();
		başka deleyicilerde derleyince kodu değiştirmek zorunda kalmayacağız.
		
		bir derleyicide unsigned int diğerinde unsigned long olabilir.

		-----------------------------

		Standart C kütüphanesinin kullandığı bazı tür eş isimleri

		size_t
		time_t
		ptrdiff_t
		clock_t
		fpos_t
		lfiv_t
		int32_t
		int16_t ... 
		gibi

		Ama hangi türün eş ismi olduğunun kararı derleyiciye bağlı.

		----------------------------------------------

		Açık ara en çok kullanılan size_t dir.

		size_t : sizeof operatörünün ürettiği değerin türüdür.

		Bu tür eş işimleri library ler içinden geliyor.

		unsigned int 
		unsigned long int 
		unsigned long long int  olabilir size_t.

		-----------------

		size_t in başka standart kütüphaneler tarafından kullanımı

		a - fonksiyonun sizeof parametresi istiyor olabilir.
			yani size_t

		b - tane - adet türü.
			strncpy() bunun işi adresteki yazının diğerine n kadar karakterini kopyalamak
			3. parametre karakter adedi. yani size_t türünden.

		c - dizi boyutu türü.
			nutility de int olarak girilen dizi boyutlarını size_t ye çeviriyoruz.
			qsort() ta 2. ve 3. parametre sizeof değeri istiyor yani size_t

		d - yazı uzunluğu türü.
			strlen() geri dönüş değeri size_t

			------------------------------

			NUTİLİTY yi şimdi update ediyorum

			ilk önce macroları tutan en light header file 
			stddef.h olduğu için bunu include ediyorum.
			içerisinde size_t var. size tutanları size_t yaptım

			for döngülerindeki değişkenide size_t ile declere ettim.


			-------------------------------------------------------
			-------------------------------------------------------
			-------------------------------------------------------

			Pointer Difference type

			ptrdiff_t

			p1 - p2 -> sonucu işaretli türden tamsayıdır.işaretli int demiyoruz.
			işaretli tamsayı. long, int , long long olablir.
			derleyiciye bağlı.

			------------------------

			birde stdint.h var

			içerisinde 
			 
			uint32_t -> hangi derleyiciyi kullanırsan kullan 4 byte yani 32 bit
			bu 4 byte int veya long olabilir. Önemli olan 4 byte olması.
			Taşınabilirlik olarak mükemmel.

			stdint include edilerek buradaki typedef isimlerine erişilir.

			Macrolar 
			işaretliler
			int8_t
			int16_t
			int32_t
			int64_t
			
			işaretsizler
			uint8_t
			uint16_t
			uint32_t
			uint64_t

			
	---------------------------------------------------------------
	---------------------------------------------------------------
	---------------------------------------------------------------

		Mülakat Sorusu

		typedef int *IPTR;

		int x = 10;
		const IPTR ptr = &x;

		// const int * ptr = &x; 1
		// int * const ptr = &x; 2

		doğru cevap iki. top level ptr

		const keyword bir typedef ismi ile kullanılırsa 
		her zaman kendisi const yapıyor pointerı.
		
		yani int * const ptr olur. ptr const olmuş oldu yani

		*ptr = 11; ve ptr =	herhangibir adres		ile test edilebilir.
		
		 -------------------------------

		 Eğer bunu low level const yapmak istersek

		 typedef const int * CIPTR;
		 int x= 20;
		 int y = 30;
		 CIPTR ptr = &x;
		 // const int *ptr = &x; demek bu.

		 typedef globalde de function scopeta da tanımlanabilir

		 ------------

		 void func(void)
		 {
			typedef const int * const CPTR;
		 }

		 ------------------------

		 baya karmaşık bildirimler yazdı
		 fonksiyon pointerları konusunda görülecek

		 burada typedef bildirimleri çok sık kullanılacak


		 ---------------------------------------------------------------
		 ---------------------------------------------------------------
		 ---------------------------------------------------------------
		 ---------------------------------------------------------------

		 YAZILAR ÜZERİNDE İŞLEM YAPAN FONKSİYONLAR
		 -----------------------------------------

		 C de aksi belirtilmedikçe char türden dizilerde tutuluyor ve son elemanı '\0' 
		 yani null character şeklinde tutuluyor.

		 yazıya okuma amaçlı erişen fonksiyonlar 
		 yazının tutulduğu dizinin boyutunu istemezler. Mantıksız oluyor.
		 zaten '\0' ile bitiyor.
		 Sadece adres yeterlidir.

		 mesela puts(str)  sadece char array adresini alıyor.size yok.

		 myputs yazıyor while ve for ile.

		 
		 2:25 civarı

		 --------------------------------------

		 bu durumda text yi tutamayacak arraya text i atayınca UB oluşur.Runtime hatası

		 diğeride dizinin boyutunuda alıp, diziyi taşırma riskini olmamasını sağlayacak

		ikisi de farklı
		tasarımla alakalı.


		*/
	

}