
// code file / implementation file
#include "nutility.h"
#include <Windows.h>
#include <stdio.h>

// bu modül bir hizmet veriyor ama verirkende aynı zamanda stdio.h tan ve windows.h tan hizmet alıyor.
// include edilme sırası, ilgili nesnelerin kullanım sırası ile alakalı.

//nutility.h buradan da import edildi çünkü
// 1 - burada macro var. include edilmeseydi macro açılmazdı
// 2 - Hem multiple inclusion guard için.Aynı bildirimi birden fazla kez alıp hata almamak için
// 3 - Hemde yukarıda yazılmış bir fonksiyon aşağıda yazılmış bir fonksiyonu çağırmak isterse
// normal şartlarda çağıramaz. fonksiyon bildirimi yukarıda olursa çağırabilir.Çünkü fonksiyon var
// demektir bu. bunu sağlıyor.

// dışarıya açık öğelere external öğeler deniyor.
// dışarıya kapatmak istediklerimizde var. bunlar global scope ta static ile tanımlanır.
// func ile değişkenler mesela static ile tanımlanırsa private oluyor. local scope ta ise 
// static in anlamı nesnenin static ömürlü olduğunu söylüyor.Programın başından sonuna kadar 
// hayatını sürdürüyor.

// Uzun fonksiyonlar çok mantıksız
// destan gibi fonksiyon yazma !!! 

// =============================================================
// =============================================================

// Tür Dönüşümleri - Type Conversions

// ival + dval (biri int diğeri double tür değişken) farklı tipte değişkenler toplanmaz.
// aynı türdekiler toplanır. burada compiler bir memory alanında ival i double türden değişken olarak
// temsil ediyor.Yani nesne oluşturuyor.Bunlara temporary nesne deniyor.sonra bu temp ile dval işleme
// giriyor.

//kodu
// ival + dval
// double temp = ival
// temp + dval

// type conversions 2 ye ayrılır.
// 1- Basit aritmetik dönüşümler . Derleyici dilin kuralları gereği sormadan bazı durumlarda işlemleri yapmak için 
// türdönüşümü yapıyor.Buna implicit type conversion deniyor.Örtülü yada otomotik tür dönüşümü.
// 2 - bizim müdahalemiz ile type-cast operatörü ile yapılan tür dönüşümüne explicit type conversion
// deniyor.
// otomotik olan -> implicit    bilerek manuel olan / operatör kullanarak -> explicit.

// ÇOK ÖNEMLİ
// int x = -1 unsigned int y = 2
// if x < y  evet dogru
// else yanlis     -> 
// sonuç yanlis ama neden ? görülecek   195. line da
//
// char c = 178
// if (c == 178) printf("dogru")
// else printf yanlis -> sonuç yanlis. NEDEN? Görülecek en sonra. 1011 0010 -> 0100 1110
//
// AŞIRI ÖNEMLİ
// a + b  a > b  a == b  a > b ? a : b de olabilir.
// a nın türü b nin türünden farklıysa.Derleyici tür dönüştürme kodu oluşturuyor.
// Bir rank var.
// en yüksek rank gerçek(reel) sayılarda. sıralaması da yukarıdan aşağıya gidiyor
// 
//	long double
//	double
//	float
//
//  daha sonra int ler gelir 
//
//  long long
//  long
//  int
//
//  int altı türler var bir de
//  
//	short
//	char
//	_Bool
//
//Tüm sıralama aşağıda
//
//	long double
//	double
//	float
//
//=========================
//
//  long long
//  long
//  int
//
//===========================
//	short
//	char
//	_Bool
//
//  Rank denilen özellik tamsayılar için işaretli işaretsiz ayrımı yapmıyor.
//  yani signed int ile int in rank i aynı.
//
//  ör
//  a + b  -> a long double b int ise işlemi long double türünden yapar
//	a + b  -> eğer long dob. değilse derleyici double mı diye bakar. çüknkü 2. bu. diğerinide double yapar
// ve işlemi double türünde yapar. o double yoksa float a bakar. yani en yukarıdakine göre çeviriyor.
//	
//  Eğer sayı reel sayı değilse
//	eğer operand short char _Bool ise bunu int türüne dönüştürür.İntegral promotion deniyor buna. 
//  char c1 = 5 , c2 = 10  
//   c1 * c2  nin türü inttir
//   c1  + c2 de inttir
//   char ile long da long a dönüşür.
//
//	Eğer biri long long ise diğerinide long long yapar.
//  eğer long ise long yapar. en son int varsa int olarak yapacak.
//		
//	1:26 da c++ ile bunu kanıtlayan kodu yazıyor hoca. C de türü belirten std kod yok.
//	cout << typeid(c1+c2).name() gibi bir kod ....
//	
//	Unsigned ve signed 
// ====================
// Operandlar aynı türden ise biri işaretli diğeri işaretsiz ise, sonuç işaretsize doğru yapılır.
// int x = 4
// unsigned int y = 0
// x + y -> sonucu unsigned int tir
// 
// long x = 5
// unsigned long y = 7  
// x * y -> tür dönüşümü unsigned longa yapılır.
// 
// Eğer biri signed diğeri unsigned olursa ve rank lar de farklı olursa
// 
// unsigned long 
// int 
// 
// int x 
// unsigned long y
// 
// x + y -> eğer yüksek olan rank unsigned, düşük olan signed ise bu işlem - >unsigned long a yapılır
// 
// TAM TERSİ !!!!!!!!!!!!!!
// long 
// unsigned int
// 
// long x 
// unsigned int y 
//  
// yüksek olan long, işaretsiz olan int 
// x + y -> rank i yüksek olan tür, düşük olan unsigned türün tüm değerlerini tutabilecek büyüklükte ise
// o zaman işlem rank i büyük olan long ta yapılır.
// AMA
// eğer rank i yüksek olan signed tür, rank i daha küçük olan unsigned türün tüm değerlerini tutamayacak ise
// o zaman işlem daha yüksek olan rank e fakat işaretsiz olarak yapılıyor.
//
// ÖRNEK
// long (4 byte)
// unsigned int (4 byte)	rank i yüksek olan long burada unsigned ın tüm değerkerini tutar mı ? 
//							hayır tutamaz. mesela 3 milyarı 4 byte long tutamaz.
//							bu durumda unsigned long a dönüşür.
//
//TAŞMA ile casting i karıştırma !!!
//
// hatalar
//  double dval =  10/3   -> burası 3.0000 olur 3.33 değil 
//  ama
//  doğrusu
//  double dval = 10 / 3.	 -> burası işte doğru 3.3333 çıkar.
//   
//-------------------------------------------------------------
//-------------------------------------------------------------
//
//	NOT !!!!!!!!!!
//
//	İŞARETLİ TAMSAYI TÜRLERİNDE TAŞMA TANIMSIZ DAVRANIŞTIR.
//
//	int x = 1000, y = 1000;
//	int 2 byte lık olsun [-32768 / 32767]
//	 x * y  -> 1'000'000 int türünde tutulacak bir değer değil. Tanımsız davranış.
//
//	mesela 1000 * 1000 = 16960 çıkıyor diyenler olabilir. 16 lık sayı sisteminde 1'000'000, F 4240 a karşılık gelir.
//	2 byte 4 hex digit yapar. 1 byte 2 hex digit yapar. int 2 byte ise yani 4 hex digit ise, F 4240 taki F atılır.
//  16lık sayı sistemindeki 4240 -> 10 luk sistemde 16960 yapar. Bu bir çok compilerde undefined behaviour. 
//
//	-------------------------------------------------------------
//
//	int türü 2 bytlık bir sistemde
//	int 2 byte
//	long 4 byte
//	
//	ival * 20 -> bu tanımsız davranış olabilir. çünkü 2 byte küçük bir değer.
//
//	önüne geçmek için aşağıdaki kod yazılır
//	ival * 20L  -> buradaki long türünden 20. long ile int işleme girerse long tipinden değer üretir.
//	



// AŞAĞISI ÇOK ÖNEMLİ
//============================================================
//============================================================
//============================================================
//============================================================
//============================================================
//============================================================

//	NOT	
//	Aynı tamsayı türünün işaretlisi ve işaretsizi işleme sokulursa işlem işaretsiz türde yapılır.
// -------------------------------------------------------------------------------------------------------------
//	NOT
//	İşaretsiz bir pozitif değer ile işaretli bir negatif değer ile işleme sokulursa, sign x değerini unsigned x e çevirecek. 
//	
//	int x = -1  // 1111 1111 1111 1111 -> bunun değeri -1
//	
//	bunu işaretsiz int e dönüştürünce  -> artık baştaki 1, işaret biti olmuyor çünkü unsigned zaten
//	dolayısı ile 1111 1111 1111 1111 bunun unsigned değeri alınır o da 4.2 milyar küsür.
//	
//	unsigned int y = 1 
//	if y > x   printf(dogru) //yukarıda artık x = 4.2 milyar küsür oldu. 1 > 4.2 false olur. bu sebeple false
//	else printf(yanlis)  
//	
//	sonucu yanlistir.
//
//	Ayrıca signed türün ve unsigned türünün kıyaslanması warning mesajı olarak ta çıkar
//	signed/unsigned mismatch. bu hataları mutlaka incelemek lazım.
//
//
// -------------------------------------------------------------------------------------------------------------
//
//	NOT
//	bir kod commit edildiğinde 0 tane warning beklenir.
//	Bilerek yazılsa bile yani false pozitif olsa bile yinede uyarı giderilmeli.
//============================================================
//============================================================
//============================================================
//============================================================
//============================================================
//============================================================
//
//	=============================================================================================================
//
//	BASİT ARİTMETİK DÖNÜŞÜMLER GÖRÜLDÜ ŞİMDİKİ KONU
//	
//	ATAMA TÜR DÖNÜŞÜMLERİ
//
//	int a = b -> derleyici b  yi ilk önce int e çevirir sonra a ya atar.
//
//	x = y  -> x double ise , y yi ilk önce double a çevirir sonra x e atar.
//
//	func(x) -> func in parametresi int olsun, argüman ise double olsun. argüman gönderirken int e çevirir. 
//
//	return y;  fonksiyonun geri dönüş değerinden farklı ise, geri dönüş değeri türüne çevirir.
//	
//	ATAMANIN YAPTIĞI NESNEYE DOĞRU TÜR DEĞİŞİR.
//
//  dezavantajı: 
//	büyük türden küçüğe kopyalama yaparken veri kaybı olur.
//	
//	char c; [-128 / 127] tutar
//	int i = 987;
//	c = i;    char 987 tutamayacağı için veri kaybı olur.
//	printf("%d",c); --> -37 çıkar

//	------------------------------------------------

// -37 nin sebebi ÇOOOOOK ÖNEMLİ
//	987 -- > HEX te 3DB dir. hex ten hesaplıyorum çünkü hesaplaması daha kolay. binary den de hesaplanır.
//	char 1 byte yani -> 3DB den 3 olmayacak -> DB kaldı -> DB = 1101 1011 -> bu da işaretli char türden negatif bir değer	
//	işaretli lerde en soldaki 1 negatif olduğunu belirtir zaten.Hesaplayarken 2 ye tümleyeni alınır. değer bulunur ve başına 
//  - konur.sayının negatifi alınır.
//
//	1101 1011 in 2 ye tümleyeni -> 0010 0101 -> 37 -> -37 dir.
//
//	Warningde de conversion from int to char possible loss of data verir.
//	Bu kod yanlış kabul edilir.
//	eğer bilerek yapıldıysa:
//	burada type-casting yapılmalı.
//
//========================================================================================
//
//	explicit type conversion.
//	
//	yani
//	c = (char)i; yapılmalı.Bu bilerek yaptım demektir.Explicit type conversion.
//
//	büyük sayi türünden küçüğe dönüşümlerde data kaybı olabilir.
//	
//	double türde bir sayıyı int e çevirirsek en iyi ihtimal ondalıklı kısmı kaybolur.
//	
//	sayının tam kısmı int e de sığmayabilir.mesela 8234323345.1234 bu int e de sığmaz.TANIMSIZ DAVRANIŞ.
//	
//	Eğer gerçekten sayının sadece tamsayı olan kısmını alacaksak.
//	Tür dönüştürme operatörünü kullanacağız.
//	ival = (int)dval;
//
//
//	-----------------------------------------
//
//	büyük reel sayı türünden daha küçüğe dönüşümler çok tehlikeli.!!!
//	compiler warning verir.
//	
//	double dval = 12324.213
//	float fval = 5432.23
//	
//	fval = dval;  // 2 adet uyarı mesajı verir.
//	1. possible loss of data
//	2. ikincisi 5432.23 bir double sayıdır ve float a atanmaya çalışılmış. doğrusu 5432.23f; yazmak
//	
//	float fval = 5432.23f
//
//	
//	taşma işaretli türlerde olur aynı zamanda İŞARETLİ TAMSAYI TÜRLERİNDE TAŞMA TANIMSIZ DAVRANIŞTIR.
//	işaretsiz türlerde taşma olmaz. 
//
//	int x = 400'000'000
//	int y = 400'000'000
//	x * y  4 byte int türüne sığmaz. Undefined behaviour.
//	
//	işaretsiz türden olsaydı taşma olmazdı.
//
//	unsigned int x = UINT_MAX   -> u int max değeri
//	x+1 -> 0 dır.
//	x+2 -> 1		ör: 757 % uint max = 757 dir.
//  x +3 -> 2
//	
//	aslında mode alıyor.  çok büyük sayi % UINT_MAX   yapıyor ve kalanı veriyor.BUNA GÜVENEREK KOD YAZILABİLİR.	
//
//	
//	ÖR:
//	int x = 20
//	int y = 10
//	double dval = 3;
//	
//	double d = (x > 10 ? y : dval) / 3;     ternary operator tur değisikliği işlemini double türde yapar.
//  printf("d = %d\n",d);                
//
//  =========================================================
//	
//	char = 178; [-128 / 127]
//	if(c == 178) // (char)178 doğrusu. böyle olursa warning vermez.ama sonuç else e girer.
//	{
//		printf("Evet doğrudur\n")
//	}
//	else
//		printf("dogru degil\n")
//	
//	178 -> 1011 0010 eder. yani bu bir negatif sayı. 1 byte

//	NOT:
// 1011 0010 2 ye tümleyeni 0100 1110 dir. bununda değeri 78. baştaki 1 oldupu için -78

//	char int ile işleme sokulmuş bu durumda char tipinde 178 int (2byte olsun) e promote edecek.
//	
//	1111 1111 1011 0010  ->   sayının negatifliğini korumak için en yksek anlamlı bitlerin hepsine 1 yazıldı.
//	sayının değeri yukarısı olmuş oldu.
//  1111 1111 1011 0010 ile 0000 0000 1011 0010 eşit olmadığı için doğru değile girer.





int ndigit(int val)
{
	int digit_count = 0;
	if (val == 0)
	{
		return 1;
	}

	while (val)
	{
		++digit_count;
		val /= 10;
	}

	return digit_count;
}

//-------------------------------------------------
//-------------------------------------------------

int isprime(int val)
{
	int is_val_prime = 1;
	if (val == 0 || val == 1)
		return 0;

	if (val % 2 == 0)
		return val == 2;

	if (val % 3 == 0)
		return val == 3;

	if (val % 5 == 0)
		return val == 5;

	else
		for (int i = 7; i * i <= val; i += 2)
			if (val % i == 0)
				return 0;

	return 1;
}

//-------------------------------------------------
//-------------------------------------------------

void sleep(int millisecond)
{
	Sleep(millisecond);
}

//-------------------------------------------------
//-------------------------------------------------

void putline(void)
{
	printf("\n-----------------------------------------\n");
}

//-------------------------------------------------
//-------------------------------------------------

void clear_input_buffer(void)
{
	int c;
	while ((c = getchar()) != '\n' && c != 'EOF')
		;

}

//-------------------------------------------------
//-------------------------------------------------


