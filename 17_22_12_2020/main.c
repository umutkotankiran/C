//fonksiyon bildiriminde default gelen extern konusu dinle tekrar
// static olayı önemli tekrar et.
// translation unit

/*
source file da aşağıdaki tanım yapılırsa, sadece ilgili source file içerisinden çağrılabilir demek.
diğer file lar içerisinden include edilse bile çağrılamaz.Diğer dillerdeki private değişkenler gibi.
Buradaki static ile code block içerisindeki static farklı anlamda.
global değişkenide fonksiyonlar gibi aynı şekilde private hale getirmiş olurum. 

static int a = 10; (private oldu)

static int func(void) (private)
{}

int main()
{
	static int a = 10; static ömürlü olduğunu söyler.Private değil.
}

#include önişlemci komutu diğer modulu aynı copy paste yapmış gibi çalıştırıyor.

Eğer kodda olmayan bir fonksiyonu çağırmaya çalışırsak geriye dönük uyumluluktan ötürü hata vermez.
bunu sağlamak içinde bir fonksiyon bildirimi varmış gibi davranıyor.
bu şekilde fonksiyon varmış gibi davranmasına default function decleration deniyor.
başka bir modülde varmış gibi davranıyor. Ayrıca derlendikten sonra uyarı mesajı verir.Hatta benim compilerda hem uyarı
hemde hata verdi.
bu kural kullanılmamalı !!!!!!!


// int func(); varmış gibi davranıyor 
default function decleration.

int main()
{
	func(12);	
}

================================================
================================================

PREPROCESSOR - Önişlemci Programı

bu bir text işleyen program
# ile başlar ve devamında komutlar gelir. ama komut kelimesi burada geçerli
ör : printf getchar scanf bunlar komut değildir :D :D bunlar fonksiyondur.
for ve if de kontrol statement ya da keyword.


Preprocessor komutları 
preprocessor directives.

# null directive
#include 
#define
#undef
#if
#elif
#else
#endif
#ifdef
#ifndef
#line
#error
#pragma

yorum satırı ile koddan çıkarma preprocessor den önce çalışıyor.
dolayısı ile yorum satırı olan komutlar devre dışı kalıyor.

önişlemci komutlarının sonuna ; gelmez

Önişlemcinin çıktısı derleyicinin girdisi olan kod haline translation unit deniyor.

önişlemci girdisi
source file
derleyicinin girdisi

translation unit

#include un iki ayrı biçimi var biri <> ile olan diğeri "" ile olan. 
ikisindede amaç, dosya içeriğini kodu yazılan yere kopyalamak.
farkı <> önceden belirlenmiş bir modül directory si var.buna default directory deniyor.
modülü burada arar.

"" ise actual directory de arar.

header files içine utility.h yaratıp <> ile include edemiyorum ama "" ile ediliyor.
çünkü "" actual directory.

standard header files ları <> ile include etmek mantıklı.

<> içerisine
std başlık dosyaları veya derleyici tarafından verilen isimler yazılır
stdio.h ve windows.h gibi

"" içerisine ise 
third party ve kendi yazdıklarımızı yazmak mantıklı

====================================================

conditional compiling
#if
#else
#elif
#ifdef
#ifndef

iç içe include lar olabilir.

yarım kalmış kodun başını bile include ile başka yerden tamamlayabiliyoruz.
include edilen dosya, başka birsürü dosyayı include etmiş olabilir. nested include lar olabilir.

===============================================
===============================================
===============================================




#define önişlemci komutu
önişlemci programlara isim tanıtılıyor. Buna C/C++ ta macro deniyor.Exceldeki macro değil :D

#define UMUT   -> UMUT bir macro
#define max(a,b)   (a>b ? a : b)   -> buradaki max macro

#define MAX			1000		-> macroların birinci kullanım biçimi
buna object like macro yada symbolic constant yada manifest constant
burada MAX görülen heryeri önişlemci programı değişecek ve oraya 1000 sabitini koyacak.

KOŞUL!!!
macro daha yukarıda olmalı yoksa üstündeki koda etki etmez.

MAX case sensitive dir.yani max yerine 1000 yazmaz. MAX olması şart.


Macronun nesneyi değiştirmediği durumlar
Eğer kod: 
1 case sensitive değilse
2 daha yukarıda ise
3 bir başka token ın parçası ise 
4 string literali içindeyse 
değiştirmez

KOD:
#define SIZE 100 + 40

int main()
{
	int x = SIZE * 5;  // burada yapılan şu olur int x = 100 + 40 * 5;
	printf("%d\n",SIZE);
}
//yani 700 yerine 300 yazar.  
#define SIZE (100 + 40)   yazarsak sonuç değişir.Buna dikkat.
int x = (100+40) * 5; olur

KOD:

#define ERROR_MSG		"bellek_yetersiz"

int main()
{
	printf(ERROR_MSG);  // bellek yetersiz yazar.
}

KOD:
#define		MAX		200+300+ \
500
                     // normalde oneliner şeklinde yazılıyor fakat burada alt satırıda alabiliyoruz \ ile
int main()
{
	int x = MAX;
}

KOD:
#define		SIZE	100;  // SIZE gördüğü yere 100; yazacak o yüzden kodda bir ; null statement olur
int main()
{
	int x;
	int y;
	// macrodan dolayı aşağısı 100; olur ve çalışır.
	x = SIZE
	y = x+5;
}

KOD:
#define SIZE 100;

itn main()
{
	if(x == SIZE) // x == 100; olacağından hata veirr.
	{
		x++;
	}
}

KULLANIM AMACLARI

1 sabitleri isimlendirmek. int x = NO_BOOKS; gibi. isim vererek gösteriyor gibi.
NOT: MAKRO lar genelde büyük isimlerle veriliyor.genel konvensiyon bu.

2 Aşağıdaki gibi veri tipini belirlemek için kullanılıyor.

#define BYTE	unsigned char

int main()
{
	BYTE x = 12; // 

}

3 bir başka makro ya etki etmesi için kullanılabilir.Kod aşağıda

#define		MIN		100
#define		MAX		500
#define		MEAN	((MAX+MIN)/2)

int main()
{
	int x = MEAN;
	printf("%d\n",x);
}

4 Bazı makrolar taşınabilirlik sağlamak için
int türünün 4 byte olduğu sistemde ve 2 byte olduğu sistemde maximum int sayı farklı.
Bunu hep 4 byte varsayıp 4 bytlık işaretli int türünün en büyük değeri olan 2147483647 yi int olarak
tanımlamak büyük hata olur. Bunu kontrol etmek zor ve ihmale çok açık bir durum.bunun içinde
makrolar kullanılır.

limits.h header file da bazı makrolar var.
LONG_MIN
LONG_MAX
LLONG_MIN
UINT_MIN
...
...  baya var.

sonu max olanlar ilgili türün maximum değerleri
min ile bitenlerde minimum değerleri.

yani
int x = INT_MAX;   burada int türü 2 byte lık derleyici ile derlenirse kod 32767 değerini alır
									4 bytlık bir derleyici olursa 2147483647 olur.

taşınabilirlik sağlıyor bu durum.

başka durum
FILE *f;

Büyük harfle yazılanlar makro
fseek(f,0L,SEEK_SET); buda makro

exit(EXIT_FAILURE) buda bir makro

=============================

#define 100 200 
olamıyor.isim formunda değil çünkü

#define PUBLIC
PUBLIC yazan yere boş dönecek yani PUBLIC yazan yeri silecek.

Gerçek sayı sabitleri hassas olduğu için kritik öneme sahip.
basamaklar yanlış yazılırsa başka bir sabit yazılmış olur.
#define PI2 5.1232143254354   heryere bunu yazar önişlemci programı.
okunabilirlik açısındanda gayet iyi.hatalı yazmayı engellemek için makro yaz.
O kodda değişiklik yapsın.


ÖNEMLİ!!!
=================================
=================================
Linuxta genişletilmiş C kütüphanesi var. Burada baya bir makro var.

math.h yi include edersek o da başka bir kütüphaneyi include etmiş.
içerisinde baya bir makro var.
Makroda yazan şu, math.h yi include etmeden önce _USE_MATH_DEFINES ı include edersen
aşağıdakileri kullanırsın yazmış. 14. satırda. pi ler loglar ln ler sqrt ler baya birşey var.

#define _USE_MATH_DEFINES
#define math.h

int main()
{
	double dval = M_SQRT2;	// sqrt(2)
	dval = M_SQRT1_2;		//1/sqrt(2)
}

===========================
FONKSİYONEL MAKROLAR
FUNCTIONAL MACRO
FUNCTION-LIKE MACRO

Burası daha zor.

//replacement list fonksiyondan(MAX(X,Y)) sonra gelen yerdeğiştirme işlemine deniyor
#define		MAX(a,b)	(a > b % a : b)
int main()
{

int x = 10
int y = 45

int max = MAX(X,Y); bu kodu aşağıdaki hale geririr.
int max = (x > y ? x : y);
}


ÖNEMLİ

#define		SQUARE(a)		a * a
int x = 10;
int y = SQUARE(x + 1)   burayı y = a + 1 * a + 1 olarak yapar.Parantez yok. burası sıkıntılı.
printf("y = %d";y);

diğer hali
#define		SQUARE(a)		(a) * (a)
int x = 10;
int y = SQUARE(x + 1)   burayı y = (a + 1) * (a + 1) olarak yapar. OK.
printf("y = %d";y);


#define		SQUARE(a)		(a) * (a)
int x = 5;
int y = 100 / SQUARE(x)   burayı y = 100 / 5 * 5 yapar yani 20*5 = 100 yine tam olmadı :D
printf("y = %d";y);



#define		SQUARE(a)		((a) * (a))
int x = 5;
int y = 100 / SQUARE(x)   burayı y = 100 / (5 * 5) şimdi tam oldu :D sonuç : 4 
printf("y = %d";y);

===============================
===============================

fonksiyonu makro haline getirmek

#define isleap(x)		((x) % 4  == 0 && ((x) % 100 != 0 || (x) % 400 == 0))

int main()
{
	int y;
	printf("yil gir\n");
	scanf("%d"&y);
	if(isleap(y))
		printf("%d yili artik yil.",y);
	else
		printf("%d artik yil değil.\n",y);
}

maaliyetli olan fonksiyon yerine makro kullanıldı. function-like macro.

====

#define isupper(c)		((c) > 'A' && (c) < 'Z')
#define tolower(c)		(((c) >= 'A' && (c) <= 'Z') ? (c) - 'A' + 'a' : (c))
....


ÖNEMLİ!!!

#define square(a)	((a) * (a))

int main()
{
	int a = 9;
	int b = square(a++);  burası ((a++) * (a++)) sequence point gelmeden ikinci kez yan etki ye uğramış
	printf("b = %d\n",b);	KOCAMAN BİR UNDEFINED BEHAVIOUR. Doğru sonuç vermesi önemsiz.
}

	

=================

SORU: Aşağıdaki makro ve fonksiyon tanımında hangisi çalışır ?

int square(int x)
{
	printf("function square \n");
	return x * x;
}

#define square(x)	((x) * (x))

int main()
{
int a = 20;
int b = square(a);

}

Makro devreye girer çünkü ilk önişlemci program çalışacağı için makro devreye girer.

================

Ama biz makro değilde fonksiyon çağrısı yapmak için fonksiyon ismini parantez içine almnamız gerekir

int square(int x)
{
	printf("function square \n");
	return x * x;
}

#define square(x)	((x) * (x))

int main()
{
int a = 20;
int b = square(a); burada macro devreye girer.
int b = (square)(a); burada function çağrısı devreye girer. çünkü makroda açılan parantez yok isimde :D

}

===================
ÇOOOOOOOOOOOK ÖNEMLİİİİİİİİ
macro yukarıda ve fonksiyon definition aşağıda olsaydı.
sorun olurdu.fonksiyon adı macroda belirtildiği gibi değişirdi.


#define square(x)	((x) * (x))

int square(int x) // burası int ((int x) * (int x)) olurdu.
{
	printf("function square \n");
	return x * x;
}


int main()
{
int a = 20;
int b = square(a);

}

ÖNEMLİ
bunu aşmak için iki yöntem var.
1 makroyu aşağıda, fonksiyonu kodda yukarıda yazmak
2 fonksiyon definitionda fonksiyon adını parantez içine almak
Aşağıdaki gibi

#define square(x)	((x) * (x))

int (square)(int x) // burası int ((int x) * (int x)) olmuştu önceki örnekte.burada çözüldü.
{
	printf("function square \n");
	return x * x;
}


int main()
{
int a = 20;
int b = square(a);

}

=======================
=======================

Neden functional macro kullanıyoruz ??

Eğer kod basit bir kod ise tek satırda yazılabiliyorsa, çok sık çağrılabiliyorsa,
maliyeti düşük olduğu için makro kullanılır.

çünkü fonksiyona giriş kodunu üretecek
fonksiyondan çıkış kodunu üretecek 
linker için bir referans isim yazacak
bu maaliyetli bir işlem
mümkünse macro kullanılır.Çünkü verimi artırır.
Gömülü programlamada verim çok önemli.

Bunlar daha detaylı açıklanacak
Avantajlar ve dezavantajları açıklanacak
Çok sık mülakat sorusu geliyor buradan.


*/


#include "utility.h"
#include <stdio.h>

int main()
{

	int x = func(1, 5);

	return 0;
}