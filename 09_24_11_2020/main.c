#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int max3(int a, int b, int c)
{
	int max = a;
	if (b > max)
	{
		max = b;
	}
	if (c > max)
	{
		max = c;
	}
	
	return max;
}


int main()
{

	/*
	Buna variadik function deniyor
	... ise epilsis anlamında
	void func(int a, ...)
	
	9877 Ali
	8979 Veli
	87   Fatma
	987  Ayşe
	98798798 Mehmet
	
	genişlik output witdh
	aradaki boşluklar noktada olabilir.Fill character deniyor buna

	Böylede olabilir.
	   9877	    Ali
	   8979 	Veli
		 87		Fatma
		987		Ayşe
   98798798		Mehmet

	+	545
	-	5464

	fixed 56465.123123
	scientific 453.2

	Nokta karakteri gösterilsinmi gösterilmesin mi, noktadan sonra kaç basamak gösterilsin

	*/

	int ival;
	printf("bir sayi giriniz : ");
	(void)scanf("%d", &ival);
	
	printf("decimal : %d , octal : %o , hexadecimal :  %x\n", ival, ival, ival);

	double kdv = 18;
	printf("%%\n");
	printf("%%kdv : %d\n", 18);

	// float ile double hesabı
	double vat = 0.4;
	double vat1 = 0.4f;
	// sayının hassasiyeti 1/2 + 1/4 + 1/8 + 1/16 ...
	// şeklinde gider eğer sayı 0.75 ise double da tam hesap tutar.

	// ikisi tam
	double val1 = 0.75;
	double val2 = 0.25;
	// bu değil çünkü tam denk gelmedi mantisa hesabında
	double val3 = 0.35;

	////////////////////////////
	int c;

	printf("Bir rakam giriniz : ");
	scanf("%d", &c);

	printf("%d kodlu karakter %c\n", c, c);

	//////////////////////////////////

	for (int i = 0; i < 20; i++)
	{
		printf("%-8d umut\n", i);
	}

	///////////////////////////////
	int x1,y1,z1;

	printf("Uc sayi giriniz : ");
	scanf("%d%d%d", &x1, &y1, &z1);
	printf("%d, %d ve %d sayilarinin en buyugu = %d\n", x1, y1, z1, max3(x1, y1, z1));

	//////////////////////////////////

	int x2 = 987;
	
	// burada printf std fonksiyonu standart outputa çıktıyı verir ve return value olan
	// verinin kaç karakter olduğunuda return eder.
	//ilk 987 yzdırır ve 3 ü return eder.
	// ikinci 3 ü yazdırır ve 1 return eder.
	// üçüncü 1 yazdırır ve 1 return eder.
	// 987 3 1
	printf("%d\n", printf("%d", printf("%d", x2)));

	///////////////////////////////
	//SCANF
	printf("\n\nSCANF\n\n");
	printf("Scanf in geri dönüş değeri çok önemli. ne kadar başarılı işlem yaptığını gösteriyor\n");
	printf("standart innputun bufferındaki karakterler silinebiliyor\n");

	int x3;
	printf("Yasinizi giriniz");
	scanf("%x",&x3);
	printf("%d", x3);

	printf("tekrar Yasinizi giriniz");
	scanf("%o", &x3);
	printf("%d", x3);

	printf("tekrar Yasinizi giriniz");
	scanf("%d", &x3);
	printf("%d", x3);

	// Standart giriş akımının bir buffer değeri var. tampon anlamında bir bellek alanı.
	//scanf in işini bitirmesi için standart inputun bufferına newline değeri gelmeli. Gelene kadar veri alıyor.

	int x5;
	//123ASD123 yaz mesela
	// int alacağı için 123 alır ve geri kalan st. inp. tamponunda kalır.
	printf("bir giris yapin: ");
	scanf("%d", &x5);

	printf("%d", x5);
	
	// aşağsı %d değilde %x ile formnatlansa

	printf("bir giris yapin: ");
	//312azxc  yazarsak hex sayı sisteminde 312a ya kadar var.bunu alır ve altta int olarak değerini verir.
	// Geri kalan st. inp bufferda kalır.
	scanf("%x", &x5);

	printf("%d", x5);

	int ival2;
	double dval2;
	printf("Bir giris yapiniz : "); // 44.567MEMO
	scanf("%d", &ival2);
	scanf("%lf", &dval2);

	printf("%d", ival2);
	printf("%lf", dval2);

	int x6 = 10;
	//ali yazarsak başarısız olacak.Yani bir atama denedik ve 0 tane yapabildi yani başarısız oldu.
	// 0 değerini return eder.x6 da 10 olarak kalır.
	printf("Bir tamsayi gir : ");
	scanf("%d", &x6);
	printf("x = %d\n", x6);


	int x7, y7, z7;
	// 12 32 44 -  yazarsak return sonuç 3 verir.Hepsi başarılı. 
	//12 ali 32 -  dersek 12 den sonra bufferdan bir değer boşaltmaz. 1 döndürür
	// Ali 32 12 - dersek Ali yi boşaltmaz hiçbir şekilde ve 0 döner
	printf("uc tamsayı tamsayi gir : ");

	int retval = scanf("%d%d%d", &x7, &y7, &z7);
	printf("retval = %d\n", retval);

	/////////////////////////
	printf("std inputun bufferi windowsta ctrl -z "
		"linuxta ctrl d ile bosaltabiliyoruz."
		"scanf e girince ctrl z enterdan sonra new line a geçince bosaltmis oluyor."
		"standart inputun bufferında karakter hic olmadan dondurursek -1 hata kodu doner");

 } 