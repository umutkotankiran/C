#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "nutility.h"

/*
	DİNAMİK BELLEK YÖNETİMİ
	DYNAMIC MEMORY MANAGEMENT

	--------------------------

	ÖNCE EXİT ATEXİT VE ABORT GÖRECEĞİZ.
	Hepsi programı sonlandıran fonksiyonlar.

	atexit, exit ile kullanılan yardımcı bir fonksiyon.

	void exit(int); -> programın hangi sebeple sonlandırıldığını ifade ediyor.
	int yerine 0 verilirse program başarılı.İşini yaptı
	nonzero bir değer ise başarısız.yapamadı demektir.
	main fonksiyonundaki return deyimi de bu şekilde yorumlanıyordu zaten.
	
	MAİN İÇİNDE RETURN STATEMENT DERLEYİCİ TARAFINDAN EXİT ÇAĞRISINA DÖNÜŞTÜRÜLÜYOR.

	exit(0) -> program işini yapmış başarılı şekilde sonlanmış.kullanacak kişiye bunun bilgisini veriyor
	exit(1) -> program başarısız.kullanacak olan kişiye bu bilgiyi verir

	0 ve 1 yerine macro kullanılıyor.
	stdlib.h de var bunlar

	#define		EXIT_SUCCESS		0
	#define		EXIT_FAILURE		1

	exit(0) -> exit(EXIT_SUCCESS)  aynı anlamda
	exit(1) -> exit(EXIT_FAILURE)  aynı anlamda
	
	----------------------------------------------------------
	----------------------------------------------------------
	----------------------------------------------------------

	void f3(void)
{
	printf("f3 cagrildi\n");
	exit(EXIT_FAILURE); // bu şekilde yapılınca buradan sonra process/program sonlandırılır.
						// bunu yapmanın 1-2 sebebi var.
						// 1. işini bitirmiştir ve bu yüzden sonlandırılır.EXIT_SUCCESS ile yapılır.
						// 2. başarısızlık durumunda çağrılır.
	printf("f3 Sona erdi\n");
}

void f2(void)
{
	printf("f2 cagrildi\n");
	f3();
	printf("f2 Sona erdi\n");
}

void f1(void)
{
	printf("f1 cagrildi\n");
	f2();
	printf("f1 Sona erdi\n");
}


int main()
{
	printf("main cagrildi\n");
	f1();
	printf("main sona erdi\n");

}
-------------------------------------------------------
-------------------------------------------------------
-------------------------------------------------------

program bilerek sonlandırılıyorsa 2 ayrı sonlandırılma biçimi var.

1. normal termination
	exit

2. abnormal termination
	abort

exitin aborttan farkı, abort hemen sonlandırıyor.
exit ise programı sonlandırmadan önce bazı işlemlerin yapılmasını garanti altına alıyor.
mesela, yazma amaçlı kullanılan dosyaların bufferlarının flush edilmesi.
dosya işlemlerinde dosyaya yazma işlemi yapan fonksiyon aslında dosyaya yazmıyor, bu dosya için memoryde ayrılmış
bir buffera yazıyor. Belirli eventler oluşunca, bellek bloğundaki byte ların hepsi dosyaya yazılıyor.
buna da bufferın flush edilmesi deniyor.


int atexit(void (*fp)(void)); geri dönüş değeri olmayan parametresi olmayan fonksiyon adresi alıyor.
atexit bunu global bir fonksiyon pointerı dizisine yazıyor.
geri dönüş değeri başarı bilgisi.

exit çağrıldığında, atexit ile kaydedilmiş fonksiyonlar ters sırada çağrılacak.

------------------------------------------------------------------------------

ör:


void handler1(void)
{
	printf("handler1 cagrildi\n");
}

void handler2(void)
{
	printf("handler2 cagrildi\n");
}

void handler3(void)
{
	printf("handler3 cagrildi\n");
}


int main()
{
	printf("main basladi\n");
	atexit(handler1);
	atexit(handler2);
	atexit(handler3);

	exit(EXIT_FAILURE);  //ters sırada çağırıyor,handler 3, 2, 1 şeklinde çağrılıyor.
	printf("main sona erdi\n");
}

-----------------------------------------------------------------
-----------------------------------------------------------------
-----------------------------------------------------------------

ÖR: aşağıdaki gibi de biz yapabiliriz.

void handler1(void)
{
	printf("handler1 cagrildi\n");
}

void handler2(void)
{
	printf("handler2 cagrildi\n");
}

void handler3(void)
{
	printf("handler3 cagrildi\n");
}


int main()
{
	printf("main basladi\n");
	fregister(handler1);
	fregister(handler2);
	fregister(handler3);


	func();
	printf("main sona erdi\n");
}

mylib.h içeriği
------------
typedef void (*FPTR)(void);

void func(void);

void fregister(FPTR F);


mylib.c içeriği
---------------
#include <stdio.h>
#include "mylib.h"

#define		MAX_REGISTER_NO		10

FPTR gfa[MAX_REGISTER_NO];
int idx = 0;

void fregister(FPTR f)
{
	gfa[idx++] = f;
}

void func(void)
{
	printf("func cagrildi ve kayit edilmis functionlari cagiracak\n");

	for (int i = idx-1; 0 <= i; i--) // tersten çağırıyor atexit gibi.
		gfa[i]();
}

==========================================================================

BUnların yapılmasının sebebi veri kaybını engellemek.

db bağlantısı kapatılması, file ların flush edilmesi, hataya ilişkin logların yazılması.
bunları unutabiliriz ya da ihmal edebilriiz.bunlar için kullanılıyor.

bunlara cleanup işlemleri deniyor.

exit çağrılmasada atexit ile kaydedilen fonksiyonlar çağrıldı.
derleyici c99 dan sonra main içine return 0 koyuyor. bu da exit(0) gibi değerlendiriliyor.
veya return 1 de exit(1) çağırır.
main içinde return olduğunda exite yapılan çağrı söz konusudur.

mesela powershell ile bir exe çalıştırdım ve outputunu kullanacağım, burada işe yarıyor.

============================================================================
============================================================================
============================================================================
============================================================================
============================================================================

ABORT

void abort(void)
abnormal termination.

abort eğer programı sonlandırırsa kendisi uyarı mesajı veriyor.
Abort olduğu belli oluyor.

exit(EXIT_FAILURE) ; örneğini abort içinde yapabiliriz.

void asd(const int *p)
{
	if(p == NULL) // bu şekilde yazılan kodlara assertion denir. runtime de olunca bu kontrol dynamic assertion denir
	{				// çünkü NULL ptr dereference etmek UB oluşturur.bu hatayı alır almaz abort ile pat diye sonlandırması için.
		printf("hata\n"); // ileride görülecek assert macrosu kullanılacak. zaten geri planda o da abort u çağırıyor.
		abort();			// assert(p != NULL) ile kullanılır    1:01
	}

	while(*p)
	{
		++p;
	}

}

=======================================================================================================
=======================================================================================================
=======================================================================================================
=======================================================================================================
=======================================================================================================
=======================================================================================================
=======================================================================================================
=======================================================================================================
=======================================================================================================
=======================================================================================================
=======================================================================================================


DİNAMİC BELLEK YÖNETİMİ
DYNAMİC MEMORY MANAGEMENT

STATIC -> BU ÇEVİRİ SÜRECİNE AİT DEMEKTİR.
DYNAMIC -> BU KAVRAM İSE PROGRAMIN ÇALIŞMA ZAMANINA AİT DEMEK.

STATIC ASSERTİON -> DOĞRULAMANIN COMPİLE TİME DA
DYNAMIC ASSERTİON -> DOĞRULAMANIN RUNTİME DA YAPILDIĞINI GÖSTERİR.

STATIC/DYNAMIC BINDING c++ ta kullanılır
fonksionun çağrılması durumunda hangi fonksiyonun çağrıldığı compile time da belirleniyorsa static,
runtime da belirleniyorsa dynamic binding denir.

STATIC/DYNAMIC TYPING
Verinin ne olduğu hangi formatta olduğu compile time çeviri sürecinde anlaşılıyorsa buna static tür kavramı C/C++,
verinin ne olduğu runtime da anlaşılıyorsa buna dynamic typing deniyor. ör : python powershell

------------------------------------------------------------------------------------------------

static memory managementta,değişkenlerin storage larını derleyici çeviri sürecinde ayarlıyor.
dynamic memory managementta, bir nesnenin bellek alanı/storage ı runtime da elde edilecek.
dynamic memory management çok çok daha maliyetli.Yani belirli temaların dışında kullanmamak lazım.

Ne zaman dynamic memory management kullanılıyor? 
	Mecbur olduğumuz zaman :D:D:D:D

C# JAVA GİBİ DİLLERDE TÜM NESNELER DİNAMİK ÖMÜRLÜ.HEPSİ DİNAMİK BELLEK YÖNETİMİ İLE ELDE EDİLİYOR.

dinamik ömür, hayata istenildiği zaman getirilip, istenildiği zaman silinebilen nesnelerdir.
bunlarında yerlerinin runtime da elde edilmesi gerekiyor.Dinamik bellek yönetimi de bu bellek
bloğunun elde edilmesi ve yönetilmesi işlemlerini yapıyor

mesela bir sınıfta 20 öğrenci var ve her öğrencinin notunu bir değişkende tutmak istiyoruz.
öğrenci sayısıda ileride değişecek. burada dinamik bellek yönetimi kullanmak gerekiyor.

aynı şekilde türün çalışma zamanında belli olma durumunda kullanılabilir.burada da gerekli.

tabi verim kritik bir uygulamada dinamik memory yönetimi ciddi fark yaratabilir.
static memory management daha hızlı çalışır ve daha kolaydır.

----------------------------------
----------------------------------
----------------------------------
----------------------------------

STACK
-----
Otomatik ömürlü değişkenler buradan alan kullanır.yani fonksiyonların static ile tanımlanmayan local
parametre değişkenleri buradan alan kullanır.Fonksiyonun return değerinin yazılacağı temp adreste burada.
Yüksel sayısal adresten düşüğe doğru büyüyor.


HEAP
----
Dinamic memory management ile ayrılan alanlar memory alanları bu segmentte yer alır.
C++ ta buraya free store da denilebiliyor.


BSS
---
Static ömürlü ve değer verilmiş değişkenler buradan yer kullanır.
bunlara 0 atanır ayrıca.


DATA
----
İlk değer verilmiş static ömürlü memory bloğu.
İçinde mutable ve immutable olan datalar var.


Stack ile heap alanları taştıkları zaman birbirinden alan kullanabiliyorlar.

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

malloc
heap ten memory allocate ediyor.Çöp değeri ile veriyor

calloc
bellek alanını allocate birde onu clear ediyor.

realloc 
var olan memory bloğunu büyütüp küçültmek için kullanılıyor.

free
dinamik olarak elde edilmiş bloğu memory havuzuna geri veriyor.

---------------------------------------------------

void *malloc(size_t n);    kaç byte lık bir blok istediğimizi argüman olarak veriyoruz.
elde ettiği adres bloğu void * türünde döner. Bunu biz kullanacağız.
hangi türden kullanacaksak ona cast edeceğiz.

User Defined Types
------------------
struct
union
enums

------------------

malloc çağrıldığında 2 ihtimal var. 
1 - Allocate edebilirse eğer bu bloğun başlangıç adresini verir.
2 - Eğer allocate edemezse NULL Pointer döner

Allocate edilen memory block unun dışında bir alanı kullanmak UNDEFINED BEHAVIOR


ör:

int main()
{
	size_t n;
	int* ptr;
	printf("Kac tamsayi : ");
	(void)scanf("%zu", &n);



	if ((ptr = (int*)malloc(n * sizeof(int))) == NULL) // int * a cast etmesekte olur ama ben ediyorum.
	{											// C++ ta zaten bu sentaks hatası.C de uyarı mesajı.
		printf("Memory yetersiz!\n");
		exit(EXIT_FAILURE);
	}

	// calloc kullanmak yerine malloc ile bellek allocate edip memset kullanabiliriz
	// memset(ptr,0,sizeof(int) * 4); yapılabilir.

	randomize();
	set_random_array(ptr, n);
	print_array(ptr, n);
	free(ptr);

}

----------------------------------------------------------------------------

Ardışık yapılan malloc çağrıları, bir önceki ayrılmış bellek bloğunun sonundan mı başlar ?
Hayır.Bambaşka yerlerden verebilir bu blokları.


*/

void handler1(void)
{
	printf("handler1 cagrildi\n");
}

void handler2(void)
{
	printf("handler2 cagrildi\n");
}

void handler3(void)
{
	printf("handler3 cagrildi\n");
}


int main()
{
	size_t n;
	int* ptr;
	printf("Kac tamsayi : ");
	(void)scanf("%zu", &n);

	

	if ((ptr = (int*)malloc(n * sizeof(int))) == NULL) // int * a cast etmesekte olur ama ben ediyorum.
	{											// C++ ta zaten bu sentaks hatası.C de uyarı mesajı.
		printf("Memory yetersiz!\n");
		exit(EXIT_FAILURE);
	}

	// calloc kullanmak yerine malloc ile bellek allocate edip memset kullanabiliriz
	// memset(ptr,0,sizeof(int) * 4); yapılabilir.
	
	randomize();
	set_random_array(ptr, n);
	print_array(ptr, n);
	free(ptr);

}









