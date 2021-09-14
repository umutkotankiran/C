#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "nutility.h"
#include <string.h>

/*

Restrict
--------
Benim gösterdiğim nesneyi bir başkası gösteremesin demek.C99 da eklendi.
C++ ta restrict yok.

kullanımı asteriskten sonra gelir. öncesinde olması sentaks hatası
int * restrict ptr;

ÖR:
void func(int* px, int* py, int* restrict pz)
{
}

burada px ve py nin pz nin gösterdiği nesneyi gösterme ihtimali yok.bunu sağlıyor.
bu derleyicinin daha iyi optimizasyon yapmasını sağlıyor.

eğer 
px = pz; yapılırsa bu bir UNDEFINED BAHAVIOR

----------

ÖR:
void func(int* px, int* py, int* restrict pz)
{
	*px += *pz;
	
	// *pz ye eriş ve onu registerda tut
	// *pz ye tekrar erişmek yerine onu registerdaki değeri ile kullan.
	//restrict olmasaydı px, pz yi gösteriyor olabilirdi ve *px değişince *pz de değişirdi.
	// bu değeride get etmek için tekrar memory ye erişmek gerekirdi. restrict ile bunu
	// ortadan kaldırıyoruz. sadece pz bu değeri tutabilir ve erişebilir.
	//bu şekilde compiler optimizasyon yapıyor.

	*py += *pz;

}

int main()
{
	int x = 10;
	int y = 20;
	int z = 30;

	func(&x, &y, &z); burası ok

	// ama aşağıdaki gibi çağrılsaydı UB olurdu
	func(&x, &y, &x);
	// pz yi aynı zamanda px te gösteriyor

}

-----------------------------

strcpy de böyle
char *strcpy(char *restrict pdest,char * restrict psource);

char str[100] = "umut";
strcpy(str, str+2); // bu bir ub.

------------------------------

CPPREFERENCE SERGEY ZUBKOV un örneği

void f(int n, int * restrict p, const int * restrict q)
{
	while(n-- > 0)
		*p++ = *q++; // none of the objects modified through *p is the same
					 // as any of the objects read through *q
					 // compiler free to optimize, vectorize, page map, etc.
}
void g(void)
{
	extern int d[100];
	f(50, d + 50, d); // OK. Kesişmiyor.birincisi d[49] da bitiyor ikinci dizi ise d[50] den başlıyor.
						// overlapped blocklar yok.UB DEĞİL.

	f(50, d + 1, d); // Undefined behavior: d[1] is accessed through both p and q in f
						//d[1] de kesişiyorlar. UNDEFINED BEHAVIOR.
}					

---------------------------------------------------------------
---------------------------------------------------------------
===============================================================
===============================================================
===============================================================
===============================================================
===============================================================
===============================================================


USER DEFINED TYPES
------------------

Types 2 ye ayrılır
Basic types ve User defined types.

BU hayatın gerçeği diyor hoca :D
bir çok prod ortamda geçiyor bunun kodu.

-------------------------------------
structures - yapılar				|
unions - birlikler					|
enumerations - numaralandırmalar	|
-------------------------------------


structures, class ların çok primitiv hali.
C nin nesne yönelimli programlama paradigmasına en çok yaklaştığı yerdeyiz.
C nin C++ a en çok yaklaştığı alan.

1 - structure decleration
struct ile başlıyor ve isimle devam ediyor ve tamamına deniyor.

2 - bu isme structure tag deniyor
structure tag opsiyoneldir.

3 - struct içindeki elemanlara member deniyor.
C++ ta boş yapı olabilir ama C de elemanlara ihtiyaç var.

struct Data{
	int x, y;
	double dval;
};

Derleyici bu nesne için elemanların toplamı kadar byte yer ayırıyor. Ama padding hizalama
konusunda görülecek daha fazla yer ayırdığıda görülebilir.İleride görülecek.

KULLANIM

struct Data{
	int x, y;
	double dval;
};

int main()
{
	struct Data mydata; // struct data türünden bir nesne yaratıldı.
}

sizeof(struct Data) ile boyutu görülebilir. 3 elemanın toplamı 16 yı verir.

Derleyici bu türden bir değişken tanımlanırsa yer ayırır.

STRUCT ELEMANLARI
Değişken, dizi, pointer, multi-dim dizi, fonksiyon ptr ... olabilir.
AMA FONKSİYONLAR direkt olarak member olamaz. FONKSİYON POİNTERLAR member olabilir.
Struct nesnesinin elemanı yine bir struct olabilir.örneği aşağıda.

struct Point{
	int x, y, z;
};

struct Rectangle{
	struct Point a,b,c,d;	
};

Struct Point mydata;
Struct Point a[10];
Struct Point *p = &mydata;  bunların hepsi geçerli.
diğer türler gibi hepsi geçerli.

burada typedef ile tanımlama kısaltılabilir.

typedef struct Point s1; dersek s1 dediğim zaman struct Point türünü belirtmiş oluyorum.


Aynı zamanda
struct Rectangle{
	struct Point a,b,c,d;
}R1;   

dersek, struct rectangle türünden R1 isimli değişken tanımlamış olduk.

typedef struct Rectangle{
	struct Point a,b,c,d;
}R1;
dersek, struct Rectangle türünün eş ismi R1 oldu.
R1 mydata; denebilir artık. İLERİDE GÖRÜLECEK.

C de empty struct yok. C++ ta var.
------------------------------------
------------------------------------
------------------------------------

struct Rectangle türünden local- global değişkenler/nesneler olabilir.
static struct Rectangle ile tanımlanabilir.
const struct Rectangle ile tanımlanabilir.
extern, volatile... hepsi geçerli structlarda

global olarak tanımlanırsa içindeki değerlere ilk değer verilmezse, 
ayrıca static ömürlü olacağından elemanları 0 olur.

local scope ta ise içindeki elemanlar  garbage/indetermined value olarak başlar.
static local olursa elemanlar bu sefer 0 olarak başlar hayata. diğer türlerde olduğu gibi.

global blokta static ile tanımlanırsa private gibi olur.
sadece bu kaynak dosyadan erişilir. internal linkage a ait olur
direkt tanımlanırsa external linkage a ait olur.

struct Data{
	int x, y;
	double dval;
};

memorydeki yerleşimleride sırasıyla oluyor. sırayla x, y ve dval gelir.
Yapı nesnesinin en başındaki adres, yapı nesnesinin ilk adresidir. 
------------------------------------------------------
------------------------------------------------------
------------------------------------------------------
------------------------------------------------------


YAPI NESNESİNİN ELEMANLARINA ERİŞİM

member selection operators

1  ()   []  .  -> 

.  ->   bunlara member selection deniyor ama insanlar nokta veya ok operatörü diyor.

dot operator ----  nokta operatörü
arrow operator ----  ok operatörü


NOT !!!!!!!!!!!!!!!!!!!!!
. operatörü struct nesnesinin kendisi yoluyla elemana erişiyor
-> operatörü struct nesnesinin adresi yoluyla elemana erişiyor

. operatörü binari infixtir.
x.y ==> derleyici böyle bir ifade görürse, sol operandı bir yapı / struct türünden nesne mi diye bakar.
çünkü böyle olmak zorunda. nokta operatörünün sağ operandı olan isim ise, sol operandının memberlarından
birisi olması gerekiyor.

struct Data {
	int x, y;
	double dval;
};

main
struct Data mydata;
mydata.x;
&mydata.x;
++mydata.x;
hepsi ok. öncelik sırası önemli. dot operator zaten 1. sırada.

yani 
int x = 10; burada x ile ilgili ne yapılıyorsa mydata.x ile de aynı şeyler yapılabilir.

Struct elemanı dizi olsaydı

struct Data {
	int x, y;
	double a[10];
};

int p* = mydata.a; yapılabilir. yani array decay geçerli.
--------------------------------------------------------------------------
--------------------------------------------------------------------------

STRUCT MEMBERLARA DEĞER VERMEK
NOT: 
YAPI ELEMANLARINA SAKIN TÜRKÇE İSİM VERME!!!

struct Data {
	int x, y;
	double dval;
};

struct Data mydata;
mydata.x = 10;
mydata.y = 10;
mydata.dval = 2.3;


struct Employee {  // hoca m_ konvensiyonunu kullanıyor.
	int m_id;
	char m_name[10];
	char m_surname[10];
	double m_wage;
};


struct Employee emp; // burada m_ yi kullanmadım.test ederken düzelt.
emp.id = 9874;
strcpy(emp.name, "Umut");
strcpy(emp.surname, "Kotankiran");
emp.wage = 120.56;

------------------------------------------------------
------------------------------------------------------

	// dinamik bellek bloğuna struct yerleştirmek
	struct Employee* pe = (struct Employee*)malloc(sizeof(struct Employee));
	(*pe).id;
	pe->id;

------------------------------------------------------
------------------------------------------------------
------------------------------------------------------
------------------------------------------------------

YAPI NESNELERİNİ INITIALIZE ETMEK / İLK DEĞER VERMEK

Dizilere ilk değer verme sentaksına benziyor.

1:20 GÜZEL BİR NASİHAT!!!

struct Data {
	int x, y;
	double dx,dy;
};

// struct Data mydata; // ilk değer verilmeden tanımlanırsa,
						// local scope ta garbage valuelar ile yaratılır.

// ilk değer verilirse
struct Data mydata = { 10,20,2.3,5.6 }; // ilk değer verildi artık.

eğer eleman sayısından fazla veri girilirse, sentaks hatası.
daha az verilirse değer verilmeyen memberlar 0 ile hayata başlar.
struct Data mydata = { 10,};  burada x 10 iken diğerleri 0 olarak hayata başlar
virgüle de trailing comma deniyor.

	
struct Data {
	int x, y;
	int a[5];
	double dx,dy;
};

	struct Data mydata = { 10,20,{1,3,},2.3,5.6 }; 

	printf("%d\n", mydata.x);
	printf("%d\n", mydata.y);
	printf("%f\n", mydata.dx);
	printf("%f\n", mydata.dy);

	print_array(mydata.a, sizeof mydata.a / sizeof * mydata.a);

	//aşağıdaki gibi olsaydı 
	struct Data mydata = { 10,20,{1,3,},2.3,5.6 };
	dizinin değer atanmamış elemanlarına 0 değeri yazılacaktı.
	struct Data mydata = { 10,20,{0,},2.3,5.6 }; dizinin elemaları tamamen 0 olurdu

	AMA
	struct Data mydata = { 10,20,1,2.3,5.6 }; burada sıra diziye geldiğinde elemanlar diziye 
												yazılacak.yani a ya 3 elemanı tamsayı olarak yazar 
												diğer iki elemana 0 yazar. sonraki dx ve dy yede 0 yazar.

	çıktı
	10
	20
	1   2   5   0   0
	0.000000
	0.000000
  
------------------------------------------------

ELEMANLAR CHAR OLSAYDI

  struct Data {
	int x, y;
	char a[20];
	double dx,dy;
};

struct Data mydata = {2,5,"Tugrul Kekec",2.3,4.5};

--------------------------------------------------------
--------------------------------------------------------

MULTIDIMENSION DIZI OLSAYDI

  struct Data {
	int x, y;
	char a[3][4];
	double dx,dy;
};

struct Data mydata = {2,5 ,{ {1,1,1,1}, {2,2,2,2}, {3,3,3,3} },2.3,4.5};

------------------------------------------------------

TEK ELEMANLI DİZİ OLSA BİLE CURLY BRACES KULLANMAK GEREKİYOR


  struct Data {
	int x;
	};

	struct Data mydata = {2}; parantez koymak şart ve içinede birşey girmek gerekiyor.
							  parantez konulduysa içide boş bırakılamıyor.


-------------------------------------------------------

DESIGNATED INITIALIZER 

int a[100] = {[5] = 12, [27] = 55}; 
bunu structlarda da kullanabiliyoruz.

struct Employee {
	int x, y;
	char name[20];
	char surname[20];
	int grades;
	int dept;
	double wage;
};


int main()
{
	struct Employee emp = { .x = 10, .y = 20,
							.name = "Ali", .surname = "atabak",
							.grades = 25, .dept = 35, .wage = 65.75};

	printf("%d\n", emp.x);
	printf("%d\n", emp.y);
	printf("%s\n", emp.name);
	printf("%s\n", emp.surname);
	printf("%d\n", emp.grades);
	printf("%d\n", emp.dept);
	printf("%f\n", emp.wage);
}

hepsi yazdırılır.

-------------------------------------------------------------------
-------------------------------------------------------------------
-------------------------------------------------------------------

MEMBERLAR GÖRÜLDÜ AMA STRUCT IN KENDİSİ NASIL KULLANILIR?

	struct Employee mydata;

	//burada mydata sadece 4 operatörün operandı yapılabilir.
	// 1. nokta operatörü . member selection operator
	// 2. sizeof operatörü (sizeof compile time sabitidir. ürettiği değer size_t türünden)
	// 3. & operatörünün operandı olabilir.
	// 4. atama operatörü = . Aynı türden yapı nesneleri arasında atama işlemleri olur.

	Farklı türden yapı nesneleri arasında atama yapılamaz.
	Farklı türden yapılar/structlar arasında tür dönüşümü yok


	struct Data mydata;
	//mydata = 5; geçersiz

	struct Nec necdata;
	//necdata = mydata; yine geçersiz çünkü türleri farklı. biri struct Nec, diğeri struct Employee

	//Tür değiştirme operatörünün operandı bir struct olamaz
	// (struct Nec)mydata; struct Nec burada hata verir.
	// bir yapı türünden diğerine ne explicit ne de implicit dönüşüm var.

	struct  Nec nx = { 12,14,4.5 };
	struct  Nec ny = { 22,44,16.5 };

	ny = nx; // TAMAMEN LEGAL. printf ile bakılabilir değerlerine.

	//bunu elemanları tek tek te kopyalayabiliriz.
	ny.x = nx.x;
	ny.y = nx.y;
	...
	//hepsi yapılabilir.

	HATTA MEMCPY ile de bu kopyalama yapılabilir.
	memcpy(&ny, &nx, sizeof(struct Data));

	sizeof büyüdükçe bu işlemde maliyetlenir.
	döngüler içinde sıksık bu işlem ciddi bir yavaşlama getirir.
	
	struct Data {
	int x, y;
	double a[20][15];
	};  2000 küsür byte eder.

	struct Data mydata1,mydata2;
	printf("%zu", sizeof mydata1);

	mydata2 = mydata1; // burada 2000 küsür bytelık bir kopyalama yapıyor.
						// bu büyük bir maliyet. atamak kolay ama çok maliyetli olabilen durumlar var.

	
	İKİ STRUCT ARASINDA İLK DEĞER VERME VEYA ATAMA YAPILABİLİR
	struct Employee ex = { 12,"alican","yilmaz", {0},54.70 };
	struct Employee ez = ex; // burasıda legal
	veya
	ez = ex; legal

	-----------------------------------------------------------

	İKİ OPERATÖR DİREKT OLARAK KARŞILAŞTIRILAMAZ

	struct Point {
	int mx, my, mz;
	};

	struct Point px = { 12,24,36 };
	struct Point py = { 12,24,36 };

	if(px == py) // BU KARŞILAŞTIRMA GEÇERSİZ !!!
				// tüm elemanları tek tek kıyaslayabilirdik
			// if(px.mx == py.mx && px.my == py.my && px.mz == py.mz) GEÇERLİ


	-------------------------------
	struct nec {
	int nec;
	};

	int main()
	{
		struct nec nec; // geçerli ama tavsiye edilmez
	}


	----------------------------------------------

	İKİ STRUCTI EŞİTLEME
	struct Ar {
	int a[10];
	};

	int main()
	{
		struct Ar a;
		struct Ar b;
		b = a; //şeklinde bir atama yapılırsa aslında a dizisini direkt olarak b dizisine atamış oluyoruz
	}			//a.a dediğimde diziye ulaşırım. b.a ilede ulaşırım.
				// bunlar direkt dizi olsaydı b = a olamazdı çünkü dizi lvalue expression değildir.
	
	Bu sayede structlar yardımıyla dizileri birbirine atamış olduk.

	----------------------------------------------------------------
	----------------------------------------------------------------

	STRUCTLAR MEMCMP İLE KIYASLANABİLİR Mİ?
	
	BELİRLİ ŞARTLAR ALTINDA EVET.
	PADDİNG VE ALİGNMENT KONULARI VAR.
	YAPI NESNELERİ İÇİNDE HİZALAMA SEBEBİYLE KULLANILMAYAN BYTELAR VAR.BUNLARA PADDİNG BYTES DENİYOR.

	struct Data{
		char x;
		int a;
		char y;
	};

	burada toplayınca aslında 6 byte ediyor.
	ama sizeof ile bakınca 12 değerini veriyor.

	x ten sonra 3 byte var diyelim. int 4 byte. 3 byte ı bir blokta 1 byte ı diğer blokta 
	olmasını engellemek için o 3 byte ı kullanmayacak.buna hizalama deniyor.İleride görülecek.
	verim düşüyor çünkü 3 byte al 1 byte ı al birleştir değere ulaş.maliyetli bir işlem.

	----------------------------------------------------------------

	BİR STRUCT TÜRÜNDEN NESNE OLUŞTURMANIN BAŞKA YOLU

	struct Data {
	int a;
	double b;
	}data;

	aslında aşağıdaki tanımlanmış.Aynı şey.
	struct Data data; 

	----------------------------------------------

	ilk değer verilebilir.

	struct Data {
		int a;
		double b;
	}data = {4,5.4};

	------------------------------------------------

	birden fazla değişken tanımlanabilir.
	struct Data {
		int a;
		double b;
	}data1,data2,data3;

	struct Data data1,data2,data3;   AYNI tanımlama

	-------------------------------------------------

	pointer tanımlanabilir

	struct Data {
		int a;
		double b;
	}data,*ptr = &data;

	buda

	struct Data data,*ptr = &data;   Tamamen aynı.

	--------------------------------------------------

	ÇOK ÖNEMLİ !!!!!!!!!!
	Mülakat sorusu. 
	tag opsiyonel.başta, maddelerde var bu.

	struct {
		int a,b,c;
	}x;     
	  
	Bu geçerli bir tanımlama. bir yapı türü oluşturulmuş ve bir nesne tanımlanmış.
	buna ilk değerde verilebilirdi
	
	struct {
		int a,b,c;
	}x = {1,2,3};

	Global bir değişken fakat tür bilgisi dışarı sızdırılmamış demek.
	Yani yazılım mühendisi kod içinde, bu türden başka bir nesne daha tanımlayamaz.
	Yani bir tane daha tanımlayamam kod içinde
	
	Amacı
	başka koda bu türü kullanma hakkı vermemek için kullanılabilir.


	struct {
		int a, b, c;
	}x,y,z;

	int main()
	{
		x.a = 10, x.b = 20, x.c = 30;
		y = x;
		z = y;
	}

	Artık bu türden bir t nesnesi daha tanımlayamayız. çünkü türün ismi yok.


	-------------------------------------------------------------------------

	MÜLAKAT sorusu

	struct {     GEÇERli Mİ ? EVET
		int a,b,c;
	}x;

	Hatta ilk değer verilebilir.

	struct {   
		int a,b,c;
	}y = {1,2,3};

	int main()
	{
		x = y;			// BURASI GEÇERLİ Mİ ? SENTAKS HATASI VAR.
	}					// GEÇERSİZ KOD. TÜR ADI YOK ÇÜNKÜ.BU DURUMDA DERLEYİCİ BUNLARA TÜR İD VERİR
						// VE BU İD LER FARKLI OLUR. FARKLI İD/İSİMLİ Lİ TÜR E SAHİP STRUCT LAR EŞİTLENEMEZ.
	

	-----------------------------------------------------
	-----------------------------------------------------
	-----------------------------------------------------
	AYNI YAPI BİLDİRİMİNİ TEKRARLAMAK SENTAKS HATASI
	GENELDE BU BİLDİRİMLER DE HEADER FİLE DAN GELECEK GENELLİKLE

	struct Data{
		int a,b,c;
	};

	struct Data{		// İKİ KERE YAZILDI AYNI YAPI/STRUCK BİLDİRİMİ.SENTAKS HATASI.
		int a,b,c;		//MULTİPLE İNCLUSİON GUARD BU İŞE YARIYOR.
	};



*/


struct data{
	int a, b, c;
};
struct data{
	int a, b, c;
};

int main()
{
	
}