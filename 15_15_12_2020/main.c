#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>

int factorial(int x)
{
	return x < 2 ? 1 : x * factorial(x - 1);
}

/*
int power(int base, int exp)
{
	int result = 1;
	while (exp--)
		result *= base;
	return result;
}
*/

int main()
{

	// n kere dönen döngü idiyomu
	/*
	int n = 30;
	while(n -->0) // n-- > 0 demek. Sadece n-- yazsakta olur.
		printf("test\n");

	*/

	/*
	(void)scanf("%d",&x); // uyarı mesajını kaldırmak için tür dönüşümü yaptık.
	while(n) // n > 0 demek.
		printf("test\n");
	*/

	/*
	printf("iki sayi giriniz\n");
	int a, b;
	scanf("%d%d", &a, &b);
	printf("sonuc : %d", power(a, b));
	*/

	/*
	1 - sonsuz döngü bir kodlama hatasıdır yada
	2 - bilerek sonsuz döngüye sokuluyor.Embedded prog. var.
	3 - döngüden başka bir yolla çıkılıyor
		döngüden çıkmanın yolları
		a - kontrol ifadesinin yanlış olması
		b - break
		c - return
		c - go to
		d - exit - abort
	*/

	// break
	// switch ya da döngü deyimi içerisinde olmazsa hata verir.

	// ----------------------------------------------------------

	/*
	int c;
	int ival;
	int cnt = 0;
	int sum = 0;
	int max, min;

	while (1)
	{
		printf("Evet (e) - Hayir (h)\n");
		while ((c = _getch()) != 'e' && c != 'h')
			;

		printf("%c\n", c);

		if (c == 'h')
			break;

		printf("tam sayi giriniz\n");
		//scanf("%d",val); bunu kullanmadık aşağıdaki - ve + sayı üretecini kullandık hızlı olsun diye.
		ival = (rand() % 2 ? 1 : -1) * rand();
		if (cnt == 0)
			max = min = ival;
		else if (ival > max)
			max = ival;
		else if (ival < min)
			min = ival;

		printf("%d\n", ival);
		++cnt;
		sum += ival;
	}

	if (cnt != 0)
	{
		printf("toplam %d sayi girdiniz\n", cnt);
		printf("Average :%f\n", (double)sum / cnt);
		printf("Min : %d\n", min);
		printf("Max : %d\n", max);
	}
	else
		printf("sayi girilmedi\n");

	*/

	// for(;;) bu şekilde de olabilir.
	// while içersinde , operatörüde kullanılabiliyor.
	// do while döngü deyimi
	/*
		aşağıdakiler aynı

		while(1)
		{
		statement1;
		statement2;
		statement3;
		if(!exp)
			break;
		}

		do{
		statement1;
		statement2;
		statement3;

		}while(exp);

		-----------------------------

		int x;
		do {
			printf("bir sayi giriniz\n");
			scanf("%d",&x);
		}while(x < 0 && x > 100);

		eğer do içerisinde continue varsa bu adımı while a götürür.
		do {
		printf("%d",i);
		i++;
		if(i<15)
			continue;
		}while(0); Yani burada continue a girdikten sonra while keyword üne yönlendirir. cevap 1


		Bir döngü deyimi diğerinden iyi diye birşey yoktur
		HEr iş için uygun veya kolay gelen kullanılır.

		for(exp1;exp2;exp3)
		 exp1-2-3 olabilirde olmayabilirde
		 exp1 birkere çalışıyor.
		 exp2 kontrol edilen ifade
		 exp3 ilginç biraz.döngüye girip işlemler yapıldıktan sonra exp3 e gelir. işlemi yapar ve exp2 true mi diye bakar
		 true ise girer işlemleri yapar exp3 işlem yapar ve exp2 true mu diye bakar....

		 for döngü deyimi içersinde kullanılan değişkenler döngü içinde kullanılıyor ve while a göre daha kompakt.
		 i = 0;
		 for (;i<10;i++) ta geçerli

		 for(;i<10;)  buda geçerli.
			i++;

		for(;;) buda geçerli.ortası yani exp2 boşsa true olarak algılanır.

		for(c = getchar();c != '\n';c = getchar()) bu şekilde de yazılabilir.
			printf("%c %d",c,c);

		for(int i = 0 ; i<10;i++ ) bu c++ da geldi.

		for(int i = 0;i<10; ++i)
		{
			int i = 20;
			printf("%d",i);    // c++ ta sentaks hatası, c de değil. her seferinde 20 yazdırır.
		}						// aslında int i = 20 farklı bir scope {  
																			int i = 20 
																		} 
								gibi.
			

		for(int i = 10, k = 20; i+k < 1000 ; ++i, k+= i){}   burasıda legal.

		13! 4 bytle lık int türünde tutulamaz.taşar
		işaretli türlerde taşma tanımsız davranıştır.

		21! de 8 bytlık alana sığmaz.

		mantıklı olan bunları bir diziye almak
		hesaplatmak mantıksız.

		lookup table deniyor

		const int d[] = {
		
		1, //0
		1, //1
		2, //2
		3, //6
		4, //24
		5, //120

		}
		
		recursive olarakta hesaplanabilir 
		return x < 2 ? 1 : x*factorial(x-1);
		

		}

	*/
	/*
	
	-----------------------------------------------------------
	
	for (int i = 0; i < 13; i++)
	{
		printf("factorial(%d) : %d\n",i, factorial(i));
	}
	
	int n = 0;
	double sum = 0;

	printf("serinin kac terimi toplanacak\n");
	scanf("%d", &n);

	for (int i = 0; i < n; ++i)
	{
		if (i % 2 == 0)
			sum += 1. / (2 * i + 1);
		else
			sum -= 1. / (2 * i + 1);
	}

	printf("%.12f", 4. * sum);

	*/

	return 0;
}