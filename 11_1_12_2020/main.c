#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// ters mantık kuruyor dikkat
int get_mid(x, y, z)
{	

	if (!(x > y && x > z || x<y && x<z)) //içerideki ifade de normalde x kesinlikle ortanca değil.ifade x en küçükse veya en büyükse demek.
		return x;							// bunun değilini alırsak kesinlikle ortanca olur. bunun değili alınmış. Yani ikiside değil.ortanca demek.
	else if(!(y>x && y>z || y < x && y < z))  // aynı durum buradada geçerli
		return y;
	
	return z;
}

int main()
{	// logic operatorler doğru veya yanlışı 0/1 diye çevirir C.
	// bir ifadenin değilinin değili 1 veya sıfırdır. x = 4   !!x = 1 dir. !x = 0 dır.
	// && logic ve.  & bitsel ve
	// ||logic veya.  | bitsel veya

	/* 3 adet logic operator var
	 2 ! logical not
	 11 && logical and
	 12 || logical or

	 ------------------------------

	 ! exp
	 exp1 && exp2
	 exp1 || exp2
	 exp ? :
	 if(exp)
	 while(exp)
	 do while(exp)
	 for(;exp;)

	 logical yorumlamada eğer ifadenin değeri
	 non zero -> true
	 zero -> false değeridir.


	 */

	//dikkat !!her zaman 0 veya 1 dir.0 dan farklı bir sayının değili 0 dır.değilinin değili 1 dir.
	// 0 ın değili 1, deilinin değili 0 dır.Yani kendisi.

	int x1;
	printf("bir sayi giriniz : \n");
	scanf("%d", &x1);
	printf("girilen sayinin ! degeri : %d\n", !x1);
	printf("girilen sayinin !! degeri : %d\n", !!x1);

	
	int x2;

	printf("Bir sayi daha giriniz : ");
	scanf("%d", &x2);


	if (x1 && x2)
	{
		printf("logic dogru \n");
	}
	else
	{
		printf("logic yanlis\n");
	}

	if (x1 & x2)
	{
		printf("bitsel olarak dogru \n");
	}
	else
	{
		printf("bitsel olarak hatali\n");
	}

	//NoT
	/*
	bitsel olarak doğruluğunu anlamak için sayıyı binary sayı sisteminde yazıp bakıyoruz.
	Aşağıdakileri bitsel olarak ve yaparsak yani & operatorünün operandı yaparsak (10&20 gibi)
	10 = 0000 1010
	20 = 0001 0100
	---------------
		 0000 0000  = False döndürür.

	*/

	
	printf("2 adet sayi giriniz : ");
	scanf("%d%d", &x1, &x2);

	printf("%d && %d = %d\n", x1, x2, x1 && x2);
	printf("%d || %d = %d\n", x1, x2, x1 || x2);
	
	// NOT
	/* eğer && operatorünün ilk operandı yanlış ise ikinciyi yapmıyor.buna kısadevre deniyor.short circuit
		eğer ||operatorunun ilk operandı doğru ise ikinciyi yapmıyor.
		Yukarıdaki iki ifadenin sebebi, && operatöründe ilk ifade hatalı ise zaten ikinciye gerek yok, false
		||de ise ilki doğru ise ikinciye gerek yok, ifadenin değeri true
	*/

	//aşağıdaki kod özel veya kullanmadan onun değerini gösterebiliyor.
	// özel veyada biri 0 diperi 1 olmalı
	printf("%d ozel %d = %d\n", x1, x2, !!x1 != !!x2);

	//DE MORGAN Kuralı önemli
	// !(exp1 && exp2)  -> !exp1 || !exp2	->De Morgan Aynı ifade
	// !(exp1 || exp2)  -> !exp1 && !exp2	-> De Morgan Aynı ifade

	// ÖNEMLİ NOT
	// BU ifade hep true döndürür.Yapılan hatalardan biri
	/*
		if(x!= 5 || x!= 13) hep true döndürür
		doğrusu
		if(x!= 5 && x!= 13)
	*/

	/*Bir programlama dili olsun ve bu dilde logic operatörler var
	! && || 
	Ama bu dilde sadece 1 tane karşılaştırma operatörü var.
	 <
	 burada küçüktür yazmak kolay zaten operatör bu. Diğerleri nasıl yazılır?
	 */

	printf("iki adet tamsayı giriniz : ");
	scanf("%d%d",&x1,&x2);
	
	// küçüktür ifadesi zaten olan
	printf("%d < %d = %d\n", x1, x2, x1 < x2);

	// büyüktür için yer değiştirilir
	printf("%d > %d = %d\n", x1, x2, x2 < x1);

	// büyük eşit
	printf("%d >= %d = %d\n", x1, x2, !(x1 < x2));

	// küçük eşit
	printf("%d <= %d = %d\n", x1, x2, !(x2 < x1));

	// ikiside birbirinden küçük değil, yani eşit
	printf("%d == %d = %d\n", x1, x2, !(x1 < x2) && !(x2 < x1));

	// birbirlerine eşit değiller. Bunun için yukarısını ! operatüre ile işleme sok.
	printf("%d != %d = %d\n", x1, x2, (x1 < x2) || (x2 < x1));

	// --------------------------------------------------------------------------
	// --------------------------------------------------------------------------
	// üç tamsayıdan ortancası

	int x3;
	printf("uc tamsayi giriniz \n");
	scanf("%d%d%d", &x1, &x2, &x3);
	printf("%d %d %d sayilarinin ortancası %d\n", x1, x2, x3, get_mid(x1, x2, x3));


	// --------------------------------------------------------------------------
	// --------------------------------------------------------------------------

	int x = 0;
	int y = 23;
	int z;

	z = x && ++y; //ÇOOOOOOOOOOOOOOOOOOOOOOK Önemli 
	/*daha önce not alınmıştı. ve(&&) işleminde 
	birinci operand yanlis ise ikinci yapilmaz.Yanlış sonuç döner.Kısa devre davranışı
	(0 yanlis 1 doğru olarak yorumlanir)*/

	printf("z= %d\n", z);
	printf("y = %d\n", y);

	// ---------------------------------
	// ---------------------------------

	// atama operatörlerinin sol operandı L-Value expression olmak zorunda.
	// 5 = x , +x = 45 , x+3 = 10 bunlar tamamen geçersiz.
	//Atama operatörlerinin ürettiği değer var. Ör x = 3 eşitliği 3 değerini üretir.
	//Atama operatörlerinin yan etkisi vardır.Ör x=3 ise x in değerini 3 yapar.Yan etki budur
	x = 10;
	printf("%d\n", x);
	printf("x=3 atamasinin urettigi deger %d\n", x = 3);
	printf("%d\n", x);

	// bir örnek
	// while dan önce getchar ile alınabilirdi ve while içinden bir getchar func daha çağrılabilirdi.
	// bunun yerine while döngüsü koşul kısmında getchar çağrılıyor. Geri dönüş değeri ch a atanan değer.
	// bir if ile de  '\n' karakterde break yapılabilirdi.Ama gereksiz.

	/*
	int ch;
	printf("bir yazi giriniz : ");
	
	while ((ch = getchar()) != '\n')
	{
		printf("%c %d\n",ch,ch);
	}
	*/
	int a, b, c, d, e;

	a = b = c = d = e = 1; // anlamı a = (b = (c = (d = (e = 1)))); 14. öncelik sırası sağdan sola doğru.
	// atama operatörünün değeri sağ operandın değeri değildir. Sol operanda atanan değerdir.
	// ör  int x; double y = 4.56; x = y; burada x=y nin ürettiği değer 4.56 değildir. 4 tür. Yani x e atanan değerdir.

	// if içerisinde x = 5 yapmak ile x == 5 yapmak tamamen farklı.
	// if içerisindeki x = 0 değeri doğru ise false çevirir.Doğru NŞA da girmesi gerekir ama çevirdiği değer x e atanan değer
	// olduğu için 0 döndürür.  0 da if içesine sokmaz.

	/*
		if(5 == x) yazılabilen bir koddur.Hatta öneriliyor.yanlışlıkla gözden bir = kaçırırsak sentaks hatası verir.
		bizi uyarmış olur.
		5=x lvalue ise expressiondan dolayı hatalıdır. 
	*/


	//-----------------------------------------
	//-----------------------------------------

	// kod yazarken kodu optimize etmeye çalışma. Zaten derleyici semantik olarak tamamen birebir istediğimiz işi yapan
	// kodu yazıyor ve çok çok daha iyi yapıyor.
	// early optimization is evil. :D:D

	/*
	x += 5; x = x+5; anlamları birebir aynı fakat c de tercih edilen compound operatorler.
	x *= 2; x = x*2;
	x /= 3;
	x %= 2;
	*/

	int day, hour, min, sec;

	printf("Sureyi gun saat dakika ve saniye cinsinden yaziniz. \n");
	scanf("%d%d%d%d",&day,&hour,&min,&sec);

	min += sec / 60;
	sec %= 60;
	
	hour += min / 60;
	min %= 60;

	day += hour / 24;
	hour %= 24;

	printf("Gecen Sure : %d gun %d saat %d dakika %d saniye", day, hour, min, sec);

	return 0;
}