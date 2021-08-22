/*
implicit compiler ın kendi yaptığı işti
bugün explicit görülecek

tür dönüşümü bir nesnenin türünü runtime da değiştirmiyor.
Geçici nesneler oluşturuyor. ve bu nesneler üzerinden işleme devam ediyor.
int x = 5
double y = 50
sum = (double)x + y; burada x in tipi artık double değil. sadece yaratılan geçici nesne double
ve bu nesne ile toplanıyor.

double mean = ival1 / ival2 -> int oldupundan bunlar istenlen sonuç çıkmaz

aşağıdaki gibi yazılırsa olabilir
double mean = 1. * ival1 / ival2  -> sol taraf artık double. işleme girenlerde double oldu.

yada daha mantıklı olan
double mean = (double)ival1 / ival2 -> ival1 cast edildi.bu daha iyi çözüm

---------------------

ival = dval -> burada hem warning alırım hemde okuyan hata ettiğimizi düşünebilir
ival = (int)dval -> burada böyle bir şey yok.bilerek yapıyoruz ve hata da kalmaz.Yanlış algıda yaratmaz.

ör:
void func(float)

double dval = 42.242

func(dval) -> possible loss of data float to double warning verir.
func(double(dval)) -> tamamen legal açık warning yok.

NOT:
Type casting ile oluşturulan ifadeler r-value expressiondur.l-value expression değildir.

(double)ival = 23.53  bu sentaks hatası

ör:
Yuvarlama

printf("[5 -5 ] aralığında sayı giriniz");
scanf("%lf",dval);
printf("girilen sayi %f yuvarlama sonucu %d",dval, dval > 0. ? (int)(dval + .5 : dval - .5)); 
pozitifler için .5 negatiflerde -.5 toplanır


============================================================
============================================================
============================================================

RASGELE SAYI ÜRETİMİ

C rasgele sayı üretiminde biraz zayıf.C++ çok çok iyi.

Rasgelelik öngürülemezlik ile ilgili.

7 7 7 7 7 7 ? 
7 gelmesi beklenir.Öngörülemezlik çok çok düşük.

1 2 3 1 2 3 1 2 ?
3 gelmesi beklenir.Rastgelelik düşük, öngörülebilirlik yüksek.

birçok programda rasgelelik çok yüksek olmalı.

oyunlar, test dataları, simülasyonlar, genetik algoritmalar, kriptoloji, olasılık hesaplama.
Bunlar rasgele sayı üretiminin yoğun olduğu yerler.

1- True	random number generation -> doğadaki olaylardan faydalanıyor.atmosferic noise, zaman
2- pseudo	random number generation  -> matematiksel süreç. herhangibir rasgelelik yok.sadece öyle bir izlenim veriyor.

1 - true -> avantajı gerçekten öngörülmez olması
dezavantajı yavaş olması ve tekrar edilebilir olmaması.

2 - pseudo -> avantajı hızlı olması ve aynı sayı zincirini istenildiği kadar tekrarlayabilir olması.
dezavantajı öngörülebilir oluyor.bir seed value gerekiyor.

En çok kullanılanı 
Mersenne Twister ama C de yok.

mesela bir kumar oyununu C nin standart random sayı üreteci ile yazarsak sonuç kötü olur.

----------------------------------

rand()  0 - RAND_MAX arasında sayılar döndürür.macronun değeri compilerların çoğunda 32767 oluyor.
srand()

Bilgisayar gerçek anlamda rasgele sayı üretmez. Deterministik bir alet çünkü.

bir seed / tohum değeri gerekiyor bunun için.
Seed değerini set eden fonksiyon srand dir

aynı seed değeri için hep aynı sayıları üretir.

for (int i = 0; i < 10; ++i)
		printf("%d\n", rand());

41
18467
6334
26500
19169
15724
11478
29358
26962
24464
aynı rakamlar gelir herseferinde

------------------------------------------------------------------

int seed;
printf("seed ddeğeri : ");
(void)scanf("%d", &seed);

srand(seed);
for (int i = 0; i < 10'000'000 -1; i++) // 10 milyona gelene kadar rand üretti
	rand();

printf("10 milyonuncu sayi :%d", rand()); // burada 10 milyonuncu sayı üretiliyor.
// herseferinde aynı 10 milyonuncu sayıyı elde edebiliriz.


-------------------------------------------------------------------------

int year_min, year_max;
printf("en kucuk ve en buyuk sayilari giriniz.\n");
scanf("%d%d",&year_min,&year_max);
for(int i = 0 ; i < 100;++i)
{
	printf("%d ",rand() % (year_max - year_min + 1) + year_min);
	//100 le 50 olsun. 100 - 50  + 1 = 51   rand() % 51 + 50 ==> 50 ile 100 arası oldu 
}

---------

aşağıdakini de ne kadar çalıştırırsam çalıştırayım sıralaması hep aynı zarlar üretilir.

----------------

rastgele sayılar üretmekte mümkün. Bunun için hava durumu, klavyeye basılma süreleri farkı, OS api
varsa ki genelde oluyor, yapıyorlar bunu. 

srand içerisine time(0) argümanını gönderirsek. bu sefer 01 01 1970 ten sonra geçen zamanı gösteriyor
bu da sürekli değişiyor.bunu almak mantıklı.

printf("%ld",time(0)); -> bu 1970 ten bu yana olan zamanı saniye cinsinden verir.

srand(time(0)) -> bu her seferinde zaman geçeceği için srand e verilen seed değeri değişecek
yani her seferinde farklı sayı zinciri oluşacak.burada uyarı mesajı verir compiler.
time() fonksiyonu long long veya unsigned long olablir.ama srand in parametresi unsigned int

bunu düzeltmek için srand((unsigned)time(0)) bunu nutility ye ekle

randomize();
	for (int i = 0; i < 10; ++i)
	{
		printf("%d\n", rand());
	}
buna rağmen yine de ilk sayı halen kötü.ama idare eder.

randomize() macrosunu farklı bir sayı zinciri elde etmek için kullanılıyor.


*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "nutility.h"
#include <ctype.h>

#define HEADS 0
#define NTOSS 10'000'000 

int roll_dice(void)
{
	int dice1 = rand() % 6 + 1;
	int dice2 = rand() % 6 + 1;
	
	return dice1 + dice2;
}

int game_(int dice_new)
{
	for (;;)
	{
		int new_roll_dice = roll_dice();
		if (new_roll_dice == dice_new)
		{
			return 1;
		}
		if (new_roll_dice == 7)
			return 0;
	}
	

}


// 1 -> win
// 0 -> lose
int game(void)
{
	int dice = roll_dice();
	switch(dice)
	{
	case 7:
	case 11:
		return 1;
	case 2:
	case 3:
	case 12:
		return 0;
	default:
		return game_(dice);
	}

}



/*
int get_random_char(void)
{
	int c;
	while (!ispunct(c = rand() % 128))
		;
	return c;
}
*/

/*
void print_random_psw(void)
{
	int len = rand() % 8 + 5;
	//randomize(); // burada çağrılsaydı her bir saniyede üretilen tüm rand değerler aynı olacak.çünkü 1sn için seed değeri
	while (len--)	// aynı kalıyor ve her seferinde tekrardan randomize fonksiyonu çalıştırıldığında o zincirin en başına atıyor.
	{
		putchar(rand() % 26 + 'a' );
	}
	putchar('\n');

}
*/

#define NGAMES 1'000'000

int main()
{
	/*
	randomize();
	for (int i = 0; i < 10; ++i)
	{
		printf("%d\n", rand());		
	}

	for (;;)
	{
		putchar(get_random_char());
		_getch();
	}
		
	*/
	/*
	randomize();	// burada olduğunda random zincirini başlatır ve her rand() fonk. a denk geldiğinde 
	for (int i = 0; i < 100; ++i) //farklı bir sayı üretir.yukarıda ise çağrılan fonksiyonda olsaydı ne olacağı yazıyor
	{
		print_random_psw();
	}

	*/

	/*
	int heads_count = 0; // tura sayısı
	//randomize(); eğer randomize macrosu çağrılırsa oluşturulan sayı zinciri daha iyi.
	for (int i = 0; i < NTOSS; i++)
	{
		if (rand() % 2 == HEADS)
			heads_count++;
	}

	printf("Tura gelme olasiligi : %.12f", (double)heads_count / NTOSS);
	*/

	int win_count = 0;

	for (int i = 0; i < NGAMES; ++i)
	{
		win_count += game();
	}

	printf("kazanma olasiligi %.12f", (double)win_count / NGAMES);












}