#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "nutility.h"

/*

MULTI-DIMENSIONAL ARRAYS / ÇOK BOYUTLU DİZİLER
-------------------------------------------
C de çok boyutlu dizi yoktur :D

int a[5][10]; bu tanımlanabiliyor evet.
bu dizi a dizisi elemanları 10 elemanlı int dizi olan 5 elemanlı bir dizi.
birinci parantez dizinin boyutu, ikincisi ise a nın elemanları olan int dizilerin boyutu.
yani a nın elemanlarıda dizi ve 5 adet var.

ör

int a[5][10];
printf("asize(a) = %zu",asize(a)); -> sonucu 5 tir. çünkü a 5 elemanlı :D
10 ise bu elemanların tuttuğu dizilerin boyutu.

yani a[0] ile a[4] arasındakilerin hepsi 10 elemanlı birer dizi.

sizeof değeri ise total memory deki alanı verir.Bu datalar contigues datalar.Dersin orta ve sonlarında
açıklayacak.İşlemler ilede gösterilecek.mesela 1. dizinin son elemanından sonra p++ dersem 2. dizinin
ilk elemanına erişmiş oluyorum.

printf("sizeof(a) = %zu\n", sizeof(a)); -> 200 byte yer kaplıyor. 5* 10 *sizeof(int) -> 200 ediyor benim sistemde.
çünkü int in sizeof değeri 4 bende.

NOT:
BÜTÜN DİZİLER BELLEKTE TEK BİR BLOK OLMAK ZORUNDA.

printf("sizeof(a[0])	= %zu\n", sizeof(a[0])); -> 40 byte
printf("sizeof(a[0][0]) = %zu\n", sizeof(a[0][0])); -> 4 byte

double d[3][8] -> Okunuş -> Elemanları 8 elemanlı double bir dizi olan 3 elemanlı bir dizi. 

BÜTÜN DİZİLERE İLK DEĞER VERİLEBİLİR.

for (int i = 0; i < 5; i++)
{
	for (int j = 0; j < 10; j++)
		a[i][j] = rand()%100;
}

for (int i = 0; i < 5; i++)
{
	for (int j = 0; j < 10; j++)
		printf("%3d",a[i][j]);
	printf("\n");
}

printf("\n\n\n");

int *ptr = &a[0][0];

while (n--)
{
	printf("%d  ", *ptr++); // yukarıda contigues olduğu için
	_getch();					// 1. dizinin son adresinden sonra
							// 2. dizinin 1. adresi gelir demiştik.
}

yada aşağıdaki gibi yazılabilir.

for (int i = 0; i < 5; i++)
{
	print_array(a[i], 10);
}

------------------------------------
------------------------------------

a[5][10][15];
a nın elemanları b[10][15] gibi diziler
b nin elemanları c[15] gibi diziler
c nin elemanları int x; gibi değişkenler.

-------------------------------------

ÇOK ÖNEMLİ

Aşağıdaki dizilerin türleri aynı mı farklı mı ?
int a[5][10];
int b[4][8];
int c[6][40];

FARKLI.

çünkü elemanların türleri farklı.
a nin elemanları, elemanları 10 elemanlı int dizi olan diziler
b nin elemanları, elemanları 8 elemanlı int dizi olan diziler
c nin elemanları, elemanları 40 elemanlı int dizi olan diziler

int a[5][10]; ve int c[3][10]; olsaydı aynı türden olacaktı.

MATRİS DİYE GENEL BİR TÜR YOK.

-------------------------------------------------
-------------------------------------------------
-------------------------------------------------

typedef ile kullanımı

typedef int INTA10[10];

typedef int INTA10[10];

INTA10 a[5]; // BU tanım a[5][10] demek.


-------------------------------------------------
-------------------------------------------------
-------------------------------------------------

İLK DEĞER VERME SENTAKSI

int a[5] = {1,2,3,4,5}; bu tek boyut için

int a[3][4] = { {1,1,1,1},{2,2,2,2},{3,3,3,3} }; // çoklu için

for (int i = 0; i < 3; i++)
	for (int j = 0; j < 4; j++)
		printf("%d ", a[i][j]);


hepsine değer vermeseydim 0 yazacaktı vermediklerime

AYNI ŞEKİLDE AŞAĞIDAKİ GİBİDE YAZILABİLİR

int a[3][4] = { 1,1,1,1,2,2,2,2,3,3,3,3 }; contigues olduğu için sıkıntı yok burada.

DESIGNATED INITIALIZATOR
int a[5][4] = { [2] = {1,1,1,1},[4] = {2,2,2,2}};

for (int i = 0; i < 5; i++)
	for (int j = 0; j < 4; j++)
		printf("%d ", a[i][j]);


AŞAĞIDAKİLERDEN HANGİSİ LEGAL

int a[][] = { 1,2,3,4,5,6,7,8,9 };
int b[][3] = { 1,2,3,4,5,6,7,8,9 };
int c[3][] = { 1,2,3,4,5,6,7,8,9 };

b legal çünkü diğerlerinde tür belirtilmemiş.Boyuta gerek yok ama türe gerek var.
b nin türü var , int *[3] tür bu tür.Byutunu derleyici compile time da çıkaracak.
asize ile de bakılabilir.

---------------------------------------------------
---------------------------------------------------
---------------------------------------------------

ÇOK ÖNEMLİ

int a[3][10];
int* p = a; // C de yanlış, C++ ta sentaks hatası.

a tek boyutlu olsaydı array decay ilk elemanın adresini çeviriyor.
ilk eleman int türden. adreside int * türden. bu yüzden array decay sorun çıkarmaz.

burada p nin a yı göstermesi için 1 artırdığımda, p nin değeri 10 elemanlı bir dizinin sizeof değeri kadar atlamalı.

ÖR:
 int a[10][4]; dizisinin elemanları arasında sizeof(int) * 4 kadar mesafe var. 
for (int i = 0; i < 3; i++)
{
	printf("%p   %p\n", &a[i], a + i); // 16 lık sistemde hesaplanırsa 16 kadar artmış her seferinde
}

yani bunu bir pointera atayınca, bu pointer 1 artırıldığında 16 byte artacak.Böyle bir pointer tanımlanacak.

ÖR:
int a[10][4];
Buna uygun bir ptr tanımlarsak.a nın türü int (*)[4];

int (*ptr)[4] = a;   // tür uyuşmazlığı uyarısıda vermedi.
burada ptr++ dersek sizeof(int) * 4 byte kadar ileri gider memoryde.

int a[10][4];
int(*p)[4] = a;

for (int i = 0; i < 10; i++)
{
	printf("%p   %p	   %p\n", &a[i], a + i,p); // 16 lık sistemde hesaplanırsa 16 kadar artmış her seferinde
	p++;
}

**p ile tutmak yanlıştır.C++ ta ise direkt sentaks hatası.
 
 --------------------------------
 --------------------------------
 --------------------------------

 int a[10][4];

 A NIN İLK ELEMANININ ADRESİNİ TURMAK İÇİN 3 PRATİK YOL VAR.

 int *p1 = &a[0][0];
 int *p2 = a[0]; // a nın ilk elemanı da adres tutuyor çünkü.Array decay den a[0] ın da adresine dönüşüyor.
 int *p3 = (int *)a; // normalde uyarı mesajı veriyor ama cast ederek yapabiliriz.


int a[5][10];
randomize();

set_random_array((int*)a, 5 * 10); // a nın adresi ile sıralı olarak atama yapılabiliyor.Yukarıda yazmıştık.
									// 5 * 10 da eleman sayısı.

iki boyutlu diziler tek boyutlu gibi atama yapılabiliyor.

-----------------------------------------------
-----------------------------------------------
-----------------------------------------------

int a[5][10];
randomize();

set_random_array((int*)a, 5 * 10);

int (*p)[10] = a;
int n = 5; // boyutu tutuyor aslında

while(n--)
{
	for (int i = 0; i < 10; i++)
		printf("%3d ", (*p)[i]);
	p++;
	printf("\n");
}


------------------------------------------------
------------------------------------------------
------------------------------------------------

tüm illerdeki ve tüm aylardaki ve günlerdeki sıcak değerlerini tutan dizi
double grades[81][12][30];
türü double (*)[12][30];

-----------------------------
-----------------------------

Artık yıl hesabınıda yapalım.


#define ISLEAP(y)		((y) % 4 == 0 && ((y) % 100 != 0 || (y) % 400  == 0))

//hatta bir adım sonrası.aşağıdakini de ekleyip kullanabilirim.Bu örnekte kullanmadım

#define mday(m,y)		daytabs[ISLEAP(y)][m]	

// 1. aydan başlatmak için 13 elemanlı yapıldı ve ilk eleman 0 yapıldı.
//artık yıl değilse 0 indisli dizi, artık yıl ise indisli dizi kullanılacak.
const int daytabs[][13] = { {0,31,28,31,30,31,30,31,31,30,31,30,31},
					{0,31,29,31,30,31,30,31,31,30,31,30,31} };

int y,m;
printf("yil degerini girin : ");
(void)scanf("%d%d", &y,&m);

daytabs[ISLEAP(y)][m]; //isleap artık yıl önderse 1 indisli dizi devreye girer ve onunda m indisli değeri.

-----------------------------------------------------
-----------------------------------------------------
-----------------------------------------------------
-----------------------------------------------------
-----------------------------------------------------
-----------------------------------------------------

ÇOK BOYUTLU DİZİLERİN FONKSİYONLARA GÖNDERİLMESİ

A,B VE C için kullanılabilecek fonksiyonlara ihtiyacımız olabilir.
ama türleri farklı dizileri fonksiyona göndermek farklı türlerde oldukları için her birine özel
fonksiyon yazmak anlamına gelir.

Tanımlar aşağıdaki gibi olmalıdır.Türler farklı olduğu için farklı fonksiyonlar yazıldı.


void f1(int(*p)[20],size_t size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < 20; j++)
			p[i][j] = rand() % 100;
}

void f2(int(*p)[8],size_t size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < 8; j++)
			p[i][j] = rand() % 100;
}
void f3(int(*p)[6], size_t size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < 6; j++)
			p[i][j] = rand() % 100;
}

int main()
{

	int a[10][20];
	int b[5][8];
	int c[4][6];
	int d[5][6];// bu yukarıdaki ile aynı türden.yani aynı fonksiyona gönderilebilir.

	f1(a, 10);
	f2(b, 5);
	f3(c, 4); // alttaki ile aynı fonksiyon çağrısı ile olur çünkü array türleri aynı
	f3(c, 5);

}

-------------------------------------------------------------------
-------------------------------------------------------------------
-------------------------------------------------------------------

FONKSİYONLARI HER SEFERİNDE KENDİMİZ YAZABİLİRİZ AMA DAHA KISA BİR YOLUDA VAR.
MACRO KONUSUNDA FUNCTION YAZDIRMIŞTIK.BENZER ŞEYİ BURADA DA YAPACAĞIZ.

#define		grsa(a)		void func_##a(int (*p)[a], size_t size) { \
										for(int i = 0; i < size;i++) { \
											for(int j = 0; j < a; j++) { \
												p[i][j] = rand() % 100; \
											} } }


#define		print


func_array(20)
func_array(8)
func_array(6)

int main()
{

	int a[10][20];
	int b[5][8];
	int c[4][6];
	int d[5][6];// bu yukarıdaki ile aynı türden.yani aynı fonksiyona gönderilebilir.

	grsa_20(a, 10);
	grsa_8(a, 5);
	grsa_6(a, 4);
}

-------------------------------------------------------------------
-------------------------------------------------------------------

HEM SET EDEN HEMDE YAZDIRAN KOD AŞAĞIDA.

#define		grsa(a)		void set_matrix_##a(int (*p)[a], size_t size) { \
										for(int i = 0; i < size;i++) { \
											for(int j = 0; j < a; j++) { \
												p[i][j] = rand() % 100; \
											} } }



#define		gpm(s)		void print_matrix_##s(int (*p)[s], size_t size) { \
											for(int i = 0; i < size; i++) { \
												for(int j = 0; j < s ; j++) { \
													printf("%3d ",p[i][j]);\
												} printf("\n"); } printf("\n\n\n");}


grsa(20)
grsa(8)
grsa(6)

gpm(20)
gpm(8)
gpm(6)

int main()
{

	int a[10][20];
	int b[5][8];
	int c[4][6];

	set_matrix_20(a, 10);
	set_matrix_8(b, 5);
	set_matrix_6(c, 4);

	print_matrix_20(a, 10);
	print_matrix_8(b, 5);
	print_matrix_6(c, 4);
}

-------------------------------------------------------------------
-------------------------------------------------------------------
-------------------------------------------------------------------


print etmenin birsürü yolu var.

void print_matrix(int(*p)[4], size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			printf("%3d ", p[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

void print_matrix2(int(*p)[4], size_t size)
{
	while(size--)
	{
		for (size_t j = 0; j < 4; j++)
		{
			printf("%3d ", (*p)[j]);
		}
		p++;
		printf("\n");
	}
	printf("\n\n");
}

void print_matrix3(int(*p)[4], size_t size)
{
	while (size--)
		print_array(*p++,4);

	printf("\n\n");
}


int main()
{
	int b[5][4] = { {1,1,1,1},
					{2,2,2,2},
					{3,3,3,3},
					{4,4,4,4},
					{5,5,5,5} };

	print_matrix(b, 5);
	print_matrix2(b, 5);
	print_matrix3(b, 5);
}


-------------------------------------------------------------------
-------------------------------------------------------------------
-------------------------------------------------------------------

FONKSİYON A,B,C GİBİ TÜM DİZİLER ÜZERİNDE İŞLEMLER YAPABİLİR Mİ? 
EVET YAPTIRABİLİRİZ.

NOT:
a b c farklı türlerde diziler;

sonuçta hepsinin elemanının elemanı int türden.
birini 40 diğerini 200 elemanlı diziler gibi düşünebiliriz.
contigues olması özelliğini kullanacağız.


void set_matrix(int* p, size_t row, size_t col)
{
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{ 
			p[i * col + j] = rand() % 100;
		}
	}
}

// benim daha çok tercih edeceğim.
void set_matrix2(int* p, size_t row, size_t col)
{
	for (size_t i = 0; i < row * col; i++) // veya while(size--){ *p++ = rand() % 100; }
	{
		p[i] = rand() % 100;
	}
}



void print_matrix(const int *p, size_t row, size_t col)
{
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{
			printf("%3d ", p[i * col + j]);
		}
	}
}

int main()
{

	int a[10][20];
	int b[5][8];
	int c[4][6];

	randomize();

	set_matrix((int *)a, 10, 20); // burada değerler contigues olduğu için dzinin ilk değerini cast edip
								// fonksiyonda kullanmak üzere gönderdik.burada a zaten &a[0][0] ile aynı şey.
								// yani ilk elemanın adresini int * ile cast edip gönderdik ki kullanılabilsin diye.
								//İlk elemana eriş ve sırayla yaz, işlemi aslında bu.setmatrix fonksiyonu 
								// cast sayesinde 200 elemanlı bir int dizi gibi düşünecek.
	print_array(a, 10 * 20);

}


---------------------------------------------------------------------------
---------------------------------------------------------------------------
---------------------------------------------------------------------------


C DE PARAMETRE DEĞİŞKENİNİN POİNTER OLMASI İKİ ŞEKİLDE İFADE EDİLİYOR.

void func(int *p)   ve		void func(int p[]) şeklinde yazılır ve aynı şeydir.

aynı şekilde

void func(int **p)   ile		 void func(int *p[]) arasında bir fark yok.

aynı şekilde

void func(int (*p)[10])    ile void func(int p[][10])   arasında hiçbir fark yok.

ÇOK ÖNEMLİ.
---------------------------
---------------------------
---------------------------

int a[5]; bunun türü int *;
int *ptr = a;

&a nın türü int (*)[5] tir
int (*p)[5] = &a;  doğru kullanımdır.

*p demek a demektir burada.
 
for(int i = 0; i< 5;i++)
	printf("%d",(*p)[i]); yazdırır 


++ptr  ---> sizeof(int) kadar artar
++p ----> ise sizeof(int) * 5 kadar artar.

yani 

int a[4][5]; gibi bir diziyi, int **p ile tutamayız.TEKRAR YAZDIM.

---------------------------
---------------------------
---------------------------
---------------------------
---------------------------

AŞIRI ÖNEMLİ

	BURADA TEK BOYUTLU ARRAY ÖRNEKLERİNE DİKKAT.

	int* ptr = NULL;

	int** p= &ptr; // bu olabilir.

	int* a[10];
	int** px = &a[0]; // tutabilir.
	//yada
	int** py = a; // burada da sorun yok. a 10 elemanlı int * türden bir dizi.
					// dizinin elemanları elemanları da pointer ise onu int ** ile tutarız.
					// çift boyutlu dizilerde farklılık var. int ** ile değil int (*)[4] gibi bir
					// tür ile tutulur.

	int b[20][5]; //bununla aşağıdaki arasında ilişki kurmayacağız.
	int** p;

	ama aşağıdaki olabilir.
	int *pb = b[0]; olabilir. çünkü b[0] int * türden bir adres
	
	//--------------

	int a[10][20] = { 0 };
	int* p[10];

	for (int i = 0; i < 10; i++)
	{
		p[i] = a[i];   // burası da legal. çünkü p[i] nin türü int *, a[i] nin türü de int *
	}

	for (int i = 0; i < 10; i++)
	{
		set_random_array(p[i],20);   // random değerler atanabilir. print_array yazılarak ta yazdırılabilir.
	}

	HERŞEY TÜR İLE ALAKALI. İNT * İLE İNT* VERİ TUTULUR.
	İNT *[5] İLE İNT *[5] TUTULUR.


	------------------------------------------------------------------------------------------
	------------------------------------------------------------------------------------------
	------------------------------------------------------------------------------------------
	------------------------------------------------------------------------------------------
	------------------------------------------------------------------------------------------
	------------------------------------------------------------------------------------------

	char names[5][20] = {"ahmet","mehmet","ali","veli","selim"};
	
	burası
	
	char *names[5] = {"ahmet","mehmet","ali","veli","selim"};  gibi değil.Burada olanlar string literali oluyor.
	değiştirilemez.Yukarısı ile diziye değer verme	sentaksıdır.

	char names[][20] = {...};	burası ok. ikincisi 20, birincisi compile time da derleyici tarafından değer verilecek.

	for(size_t i = 0; i< asize(names); i++)
		printf("%s",names[i]);


	burada string literali yok.bunlar diziye atanmış.Yani değiştirmek UB değil.
	ör:
	names[1][2] ='c'; burası UB değil çünku bunlar dizi içerisine atanmış veriler.

	tüm isimlerin sonuna can ekleyelim

	for(size_t i = 0; i< asize(names);i++)
		strcat(names[i],"can");

	burada char * str[20] deseydik burada string literalleri değiştirilmeye çalışsaydık UB oluştururdu.
	burada readonly tutulur string literalleri.


	--------------------------------------------------------------
	--------------------------------------------------------------
	--------------------------------------------------------------
	DİKKAT.
	Çift boyutlu diziler ile tek boyutluların türleri farklı olabiliyor.

	char names[][30] = {....};  // hocanın verdiği isimler var.

	char *p[asize(names)];

	for(size_t i = 0; i< asize(p);i++)
	{
		p[i] = names[i]; // türleri aynı, açıklama aşağıda.
	}

	names in elemanları, char türden dizileri tutan elemanlardır. 
	türü  ->   char (*pf)[30].  
	names[i] nin türü ise char * çünkü adres belirtiyor her bir öğe.

	char *a[100] -> bunu tutacak pointerın türü ise char **p şeklindedir.
	a[i] ise char *p ile tutulabilir.

	sonuçta names[i] de char * türden, a[i] de char * türden.
	yani eşitlenebilir.


	Şimdi pointer dizisini bubblesort ile sıralayabiliriz.
	
	for(size_t i = 0; i< asize(p) -1;i++)
	{
		for(size_t j = 0; j < asize(p) -1 -i; j++)
		{
			if (strcmp(p[j],p[j + 1]) > 0)
			{
				char* ptemp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = ptemp;
			}
		}
	}

	YANİ NAMES[][] DİZİSİNİ DEĞİŞTİRMEDİK FAKAT CHAR * TÜRÜNDEN ELEMANLARI TUTAN BİR DİZİ YARATTIK.
	ADI P. P DİZİSİNDEKİ ADRESLERİ YER DEĞİŞTİRDİK AMA NAMES DİZİSİ OLDUĞU GİBİ DURUYOR.
	NAMES DEĞİŞTİRMEDEN P ÜZERİNDEN BİR SORT YAPIYORUZ.YANİ P NİN İLK ELEMANI ESKİDEN 0 İNDEXLİ 
	ELEMANI GÖSTERİRKEN ŞİMDİ EN UFAK OLANI GÖSTERİYOR.O DA 200 GİBİ BİR DEĞER OLABİLİR.

	P yi yazdırırsak sonucu görürüz.

	-------------------------------------------------------------------
	-------------------------------------------------------------------
	-------------------------------------------------------------------
	-------------------------------------------------------------------
	-------------------------------------------------------------------

	const int a[10][20] = { 0 };
	a[3][3] = &x;
	dizinin hiçbir eleman artık değiştirilemez çünkü const kullanılmış

	-----------------------------------------------
	-----------------------------------------------
	-----------------------------------------------

	Aşağıda 2 boyutlu elemanları ise char* türden bir dizi yer alıyor.

		char* p[3][2] = { {"ali","veli"},
					{"hasan","huseyin"},
					{"hato","mato"} };


*/



int main()
{

	
}