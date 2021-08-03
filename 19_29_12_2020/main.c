/*

neden fonksiyonel makro kullanıyoruz.
Burada hile yapılıyor.fonksiyon çağrısı gibi bir görüntü var ama ortada fonksiyon yok.
fonksiyon çağrı ifadesine benzer kodu preprocessor macro olarak alıp bir replacement yapıyor.

Amaç, fonksiyonu elemine etmek.
Bunun sebeplerinden biri ve önemli olanı maliyet.
fonksiyona giriş ve fonksiyondan çıkış kodları maliyeti gereksiz yere toplam maliyete eklenecek.

isleap yerine macro
#define isleap(y)	((y) % 4 == 0 &&  ((y) % 100 != 0 || (y) % 400 == 0))

compiler ın hedeflerinden biri de kodu optimize etmek
bu optimize işini ne kadar geniş kod bloğunda yaparsa o kadar iyi optimize eder.
Fonksiyonları optimize etme şansı yok. Compiler için fonksiyon karakutu.
yani fonksiyon çağrıları compilerın optimize etme ihtimali olan kodu küçültüyor.

===============================================================================

Mülakat sorusu : fonksiyon ile makroların kıyaslanması.% 90 diyor :D

1-Macrolar generic/türden bağımsız, fonksiyonlar türe bağımlı.
2-Macrolar source kodu, dolayısıyla oluşan makina/exe kodu büyütme eğiliminde.
embedded ortamda istenilmeyen durum olabilir çünkü alan kısıtlı bu ortamlarda.
3-fonksiyonlar için debuggerlar çok iyi destek veriyor.Macrolarda bu söy konusu değil.
fonksiyon debugger friendly.
4-Macrolar güvenli değil.Yanlış kullanımda hata riski çok yüksek.
mesela #define square(x)   ((x) * (x))  
burada square(x++) yazılırsa (x++) * (x++) yani undefined behaviour.
kod istenildiği gibi çalışmadığında macrolara bi bakmak iyi olur.
5-Function pointer gereken yerde macro kullanamayız.Çünkü macroların adresi yok.
Macrolar yer değiştirme işi yapıyor zaten.

================================================================================

aşağıdaki gibi garip gelen örnekler de var.

#define isupper(c)		((c) >= "A" && (c) <= "Z")

int main()
{
	inc c = 'A';
	if isupper(c)   // burada parantez içinde değil isupper(c), çünkü macroda parantez içine alındı zaten
	{				// gariplikte direkt farkedilmemesi.Normalde if ten sonraki ifade parantez içine alınır.
		printf("ok");
	}
}

#define getval(x,y)		(ptr->a[x] * ptr->b[y])

getval(i,k)
ptr->a[i] * ptr->b[k]

getval(x + y, z - t)
ptr->a[x + y] * ptr->b[z - t]

===============================================================

Preprocessor Operators
# stringification , string yapma operatoru
## token pasting , token birleştirme operatoru
	ve defined	,  defined

# preprocessor komutlarının başındaki değil, macro tanımlarken kullanılan.
	unary prefix.
// #x macro açılımında bunu görürse "x" hale getirir.Bazı komplex macrolarda kullanılıyor.

ör: 
#define   str(x)  #x 

int main()
{
	printf(str(UMUT));   // printf("UMUT"); haline getirir.
}

#define iprint(x)   printf("%d",x)

int main()
{
int x = 15, y = 20, z = 50;
iprint(x); //  15
iprint(x+y+z); //85 
iprint(x*x+y*y+z*z); // 3125

}


#define iprint(x)	printf(#e " = %d\n",e);

int main()
{
int x = 15, y = 20, z = 50;
iprint(x); //  15
iprint(x+y+z); //85
iprint(x*x+y*y+z*z); // 3125

}

## Operatörü

a ## b -> ab  hale getiriyor.

#define bir(x,y)   x##y

int main()
{
	int value = 0;
	++bir(val, ue);
	printf("value = %d\n", value);
}

Önişlemci programa kod yazdırmak istiyoruz.
örneğin benzer iki fonksiyon var diyelim biri int değer döndürüyor diğeri double
bunları macro ile yazdırmak istiyoruz.

int func(int a, int b)
{
	int c = a*b + 258;
	int d = c * 3 / 5;		
	return c*d/2;
}

double func(double a, double b)
{
	double c = a*b + 258;
	double d = c * 3 / 5;		
	return c*d/2;
}

yukarıdaki fonksiyonlar çok benzer macro ile yazdırmak daha pratik olacak.Örnek baya güzel.

#include <stdio.h>
#include <stdlib.h>
#define make_func(t)	t func(t a, t b) \
{ \
	t c = a * b + 258; \
	t d = c * 3 / 5;  \
	return c * d / 2; \
}

make_func(int)    // burada fonksiyon isimleri C de overloading olmadığı için sentaks hatası.Çözümü birsonraki örnekte.
make_func(long)
make_func(double)

int main()
{
	int x = func(12, 24);
}



BURADA FONKSIYON ISIMLERINIDE DEGISTIRMEK GEREKIYOR


#include <stdio.h>
#include <stdlib.h>
// fonksiyonda ##t geldi yani funksiyonadı_tipi oldu
#define make_func(t)	t func_##t(t a, t b) \
{ \
	t c = a * b + 258; \
	t d = c * 3 / 5;  \
	return c * d / 2; \
}

make_func(int)    // artık yukarıda eklenen ##t birleştirme operatörü ile sorun ortadan kalktı.
make_func(long)		// globalde scope ta function definition yaptık.
make_func(double)

int main()
{
	int x = func_int(12, 24);
	int y = func_double(2.5, 7.5);
}


ÖRNEK

#include <stdio.h>

// aşağıdaki gibi bırakırsam sentaks hatası olur else kısmında
#define swap(a,b)	{int temp = a; a = b; b = temp;}


int main()
{
	int x = 10;
	int y = 45;

	if (x > y)
		swap(x, y); //sentaks hatasının sebebi fonksiyondan sonra ; geliyor ve if-else yapısını bozuyor
	else
		++x;

}


düzeltmek için do while kullanılabilir.

#include <stdio.h>

// do-while döngüsünde, while sonunda ; olduğu için 
// macroda boş bırakıyorum ki kodda ; olacağı için sentaks hatası vermemesi için.
#define swap(a,b)	do {int temp = a; a = b; b = temp;}while(0)


int main()
{
	int x = 10;
	int y = 45;

	if (x > y)
		swap(x, y);
	else
		++x;

}

=================================
=================================

kullanıldığı yerler özet

#define PUBLIC
#define SIZE	100  // symbolic constant
#define sum_square(x,y) ((x) * (x) + (y) * (y))  

Koşullu derleme komutları - Conditional compiling Sıra burada.
--------------------------------------------------------------
Donanıma bağlı olarak derleyicinin farklı kodları derlemesi
OS e bağlı olarak derleyicinin farklı kodları derlemesi
Compiler a bağlı olarak derleyicinin farklı kodları derlemesi
Programlama Diline bağlı olarak derleyicinin farklı kodları derlemesi.
Versiyona bağlı olarak derleyicinin farklı kodları derlemesi
Bölge/Ülkeye bağlı olarak derleyicinin farklı kodları derlemesi
Dile bağlı olarak derleyicinin farklı kodları derlemesi
birçok madde daha olabilir.

---------------------------------------------------------------

Assertion runtime da bir kodlama hatası varsa assertion kodunda takılıp ekrana birşeyler yazdıracak
ve bunu bulup düzeltiriz.

void func(int x)
{
	if (x == 0)
	{
		printf("%s kaynak dosyasının %d. satirinda %s fonksiyonu icinde sifira bolum hatası", __FILE__,
			__LINE__, __func__);
		abort();
	}

	int y = 5;
	y /= x;
}
int main()
{
	func(0);
}

=====================================================
Koşullu derlemeye giriş yapıldı. Bunu inceleyelim

#if
#endif
#else
#elif
#ifdef
#ifndef
#undef
=====================================================

//Preprocessor expression
//tamsayi turlerinden sabit ifadesi
//gerçek sayi olamaz

#define SIZE		100

//bu iften girerse kodları derleyiciye verir.Girmezse vermez.
#if SIZE > 10
	typedef int Word;
	Word a[10];

#endif
--------------

#if SIZE > 10
	#include "utility.h"
	typedef int Word;
	Word a[10];
#endif

--------------

#if SIZE > 10
	#include "utility.h"
	typedef int Word;
	Word a[10];
#else
	#include "futility.h"
	typedef unsigned int Word;
	Word a[20];
#endif

--------------

ifdef -> if defined demek yani bu daha önce tanımlandı mı demek.Tanımlandıysa True.

// SIZE tanımlı ise içeri ifdef e girer tanımlı değilse else e girer.
// Kaç değerine define edldiğinin bir önemi yok yeterki define edilsin.

#define UMUT
//yukarıdaki UMUT u define ediyor.

#ifdef UMUT  
	#include "utility.h"
	typedef int Word;
	Word a[10];
#else
	#include "futility.h"
	typedef unsigned int Word;
	Word a[20];
#endif

-------------------------------

ifdef in ifndef -> yani bir define işlemi ile ilgili bahsi geçen tanım yoksa girer if(!x) gibi

UMUT tanımlı değilse(tanımlanmamışsa) blue red kısmına girer.Tanımlıysa white yellow kısmına girer.
#ifndef UMUT
	enum Colors {Blue,Red}
#else
	enum Colors {while,Yellow}

#endif

================================================================

3 tane if yapısı var
#if
#ifdef
#ifndef

#define PRC 3.1234    // burada sorun yok.
#if PRC > 4.23123    // burası hata verir .Çünkü tamsayı olmak zorunda bu karşılaştırma.

if içinde karşılaştırma operatörleri
logic operatörler
aritmetik operatörler
bitsel operatörler kullanılabilir.

--------------------------------------------

#define EUR		0
#define USD		1
#define GBP		2
#define JPY		3

#define CURRENCY	EUR

#if CURRENCY == EUR
	const char *gp = eur;
#else
	#if CURRENCY == USD
	const char *gp = usd;
	#else
		#if CURRENCY == GBP
			const char *gp = gbp;
			#else
				#if CURRENCY == JPY
					const char *gp = jpy;
				#endif
		#endif
	#endif
#endif

//Yukarısı bir elseif merdiveni
// bunu elif ile yapabliriz ve daha mantıklı düzgün görünür.

#if CURRENCY == EUR
	const char *gp = eur;
#elif CURRENCY == USD
	const char *gp = usd;
#elif CURRENCY == GBP
	const char *gp = gbp;
#elif CURRENCY == JPY
	const char *gp = jpy;
#endif

===============================================
# ## defined bunlar operatörler.
Defined preprocessor operatörü.

#define UMUT
#define MEHMET

#ifdef UMUT
	#ifdef MEHMET
		typedef int Word;
	#endif
#endif

------------------------

Aşağıdaki ilk 2 örnek aynı

#if defined UMUT 
	//kod
#endif

#ifdef UMUT
	//kod
#endif

--------

Aşağıdaki ikisi aynı.

ifndef ile !defined aynı.

#ifndef UMUT
	//kod
#endif

#if !defined UMUT
	//kod
#endif


DEFINED ın farkı Aşağıda
yani aynı anda iki tane ismi kontrol edebiliyorum.&& || ile .
#if defined UMUT && defined MEHMET
	int a = 0;
#endif

//==========================================================
//==========================================================

Bir header file birden fazla kez include edilmemeli.
multiple inclusion guard -> çoklu kez dahile karşı koruma.

bir başlık dosyasını birden fazla include edilirse sentaks hatası olabilir.
Çok tehlikeli.Bu bazı bildirimlerin iki kez bildirildiğinde sentaks hatası olmasından kaynaklanıyor.
aynı fonksiyonu iki kez bildirirsek sentaks hatası değil.ama aşağıdaki bildirimi iki kere yakarsak
sentaks hatası olur.


ali.h ve veli.h da aşağıdaki bildirim olsun.

struct Data {
	int x, y, z;
};

//source file dan hem umut.h hemde mehmet.h yi include edersek, hem umut hem mehmet utility yi include
// ettiği için buradan gelen bildirimi source file da iki kere alt alta tekrar edildi
//ve bu hata verdi.
// Yani struct Data yı iki kere bildirmeye çalıştı(alt alta yapıştırdı) ve 
//sentaks hatası oldu.bunu bir koşul altına almak lazım

struct type redefinition hatası görülür.

cozmek için.Hatayı veren tanımın olduğu dosyaya gdilir.
utility.h orada komutlar yazılır.

//macro tanımlı değilse gir ve tanımla. Eğer tanımlıysa girme ve dolayısıyla tanımlayama.
//buna multiple inclusion guard deniyor.
isim olarak UTILITY_INCLUDED denebilir.
#ifndef UTILITY_INCLUDED
#define UTILITY_INCLUDED

//kodlar

struct Data {
	int x, y, z;
};

#endif
---------------------------------------------
Bunu otomotik zaten compiler yapıyor.Kendisi ekliyor.

#pragma once 

denen bir macro ekliyor dikkat edildiyse.
----------------------------------------------
KURAL
#ifndef MODUL_H
#define MODUL_h

//kodlar

struct Data {
	int x, y, z;
};

#endif
==================================

#undef 
Bir macronun tanımını ortadan kaldırıyor.
#undef SIZE   size ı ortadan kaldırır.

Neden kullanılır?

#define UMUT 100

#define UMUT 600

Yukarısı tanımsız davranış.
preprocessor bir macronun iki kere define edildiğini görmemeli.
sayi / 0 da tanımsız davranış bir not olarak düşelim.


#include "ali.h"
#include "veli.h"
#include "kudret.h"

#define SIZE 1000 
ya include edilen dosyalardan birinden SIZE macrosu gelirse. Kod tanımsız davranış olur.
Macro redefinition bu. bunun engellemek için undef kullanılır.Tanımlı değilse undef hata vermez.
Sentaks hatası oluşmaz.

Aşağıda doğrusu var.
1. kullanım alanı bu

#include "ali.h"
#include "veli.h"
#include "kudret.h"

#undef SIZE
#define SIZE 1000

2. Kullanım alanı

void func()
{
	#define SIZE 1000
	
	burada oluşturulan macro bu komutun bulunduğu yerden başlar, include edilecek dosyalar dahil 
	SIZE ı 1000 le yer değiştirir. Amacımız sadece bu macronun fonksiyonun ana bloğu içinde etkin olması
	bunun için undef SIZE denir.Bu da macroya kapsam kazandırmış oluruz.yada scope.

	#undef SIZE

}

fonksiyonlarda da kullanılır 

#define max(x,y)  (a > b ? a : b)

undef max

-------------------------------------------------

NOT: if içerisinde kullanılan macroların define edilme zorunluluğu yok.
aşağıdaki if e girmez çünkü burada MAX = 0 değerini görüyor.
Yani define edilmemiş macrolar if içersinde 0 değeri alır.

int main()
{
#if	 MAX > 0;
	typedef unsigned type char;
#endif
}

BURADAN SONRA PREDEFINED SYMBOLIC CONSTANTS Görülecek.
öyle macrolar var ki bunların bir define komutu yok. dilin kuralı gereği preprocessor
bunları yerdeğiştirme işlemine sokuluyor.(macro olayını gerçekleştiriyor).
Yani include etmedende birçok macro kullanabiliyoruz.
bunlar  
__LINE__ 
__FILE__
__DATE__
__TIME__
__STDC__

int main()
{
	printf("%d",__LINE__);

}


*/

#include <stdio.h>
#include "umut.h"
#include "mehmet.h"

int main()
{
	
}