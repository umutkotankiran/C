#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	printf("%d\n", (6, 7));

	// ÇOOK Önemli bir konu daha
	/* Sequence point (sequencing) veya side effect point - yan etki noktası
	kaynak kodda yazılan kodlar kodda bir durum değişikliği yapıyor.
	mesela bir değişkenin değeri değişirse buna side effect denir.
	
	int x = 10;
	++x; buradaki x in değeri ne zaman değişecek ?
	sequence pointten sonra değişir. bir sequence point örneği ; dür.

	TANIM :
	Yan etkiye uğramış bir nesneyi, bu yan etkinin gerçekleşmesi garanti olmadan
	kullanmaya "tanımsız davranış denir." ÇOK ÖNEMLİ bu

	x++ * x bu ifade bir tanımsız davranıştır.

	x = y;
	func(x); burada sıkıntı yok.

	int a = 46;
	++a;
	b = a;

	------------------------------------------

	4 tane operatör var bunlar sequence point oluşturuyor
	
	1 &&
	2 ||
	3 ? :
	4 ,
	Aynı şekilde ; de öyle

	x++ || func(x)
	x++ && func(x)
	x++ , func(x)
	hepsi geçerli.

	if , while ve for da sequence point var gibi davranır. yan etkisi görülür

	x = 10
	if(x++ > 9) çıktıntan sonra değeri 11 oldu. yan etki gerçekleşti
		a = x; a = 11 oldu

	n = 5
	while(n-- > 0)
		func(n)

	for( ; burada da yan etki noktası var ; )
	for (int i = 0;i++ < 10;)

	------------------------------------------

	int x = 10;
	int y = x + ++x; // burası undefined behavior

	x = x++; tanımsız davranış
	sebebi x++ yan etkiye maruz kalmış ve "x =" ile de eşitleme yapılmaya çalışılmış.

	y = x + (x = 10) tanımsız davranış
	sebebi bir yan etkiye maruz kalınmış fakat herhangibir sequence point
	denk gelmeden kullanılmaya çalışılmış

	Sonuç : Yan etkiye maruz kalmış nesneyi yan etki notkası geçmeden kullanmayın.

	---------------------------------------
	---------------------------------------

	Maximum munch kuralı

	x = 10;
	y = 5;
	z = x+++y; (x + ++y olsadı sorun yoktu.)
	z ?

	tokenizing yaparken anlamlı isimleri maximum nereye kadar uzarsa onu alır 
	ör:
	x ok, 
	birincisi x
	+ anlamlı 
	++ anlamlı
	+++ anlamsız
	++ alınacak
	+ anlamlı
	+y anlamsız
	+ yı alır
	son olarakta y

	x++ + y;
	z = 16

	--------------------------------------------

	Virgül , operatörü

	virgül bazen delimiter-seperator bazende operator olarak kulanılıyor.
	int x,y,z virgüller operator değil
	func(x,y) virgül operator değil.
	int a[] = {1,2,3,4,5} virgüller operator değiller. Ayıraç olarak kullanılıyor.

	Virgül operatoru öncelik seviyesinde dipte.
	exp1 , exp2 
	a=b , b = c
	5,7 Virgül operatorü bir sequence point olşturur
	Virgün operatörünün sol operandından sonra yan etki noktası var.
	ifadenin değeri virgülün sağındaki ifadedir.

	x++, y=x, z = x+y; bu ifade ok.
	avantajı bir satırda birden fazla ifade yazılabilir.
	özellikle for döngüsü içinde var bu.
	for(i=0; ;i++,k+=i) olabilir.
	

	ÖNEMLİ 
	Virgül operatörünün ürettiği değer sağ operandının değeridir.

	if(x = func(), x > 0) burada da fonksiyonu çağırır if değeri ve sağ operand değeridir 


	func(12, 4) buradaki virgül seperator bunu operator haline getirmek için
	func((12, 4))

	int x[5] = {1,2,3,4,5};
	int x[5] = {(1,2,3,4,5)} ilkine 5 verir diğerleri sıfır.

	NOT
	(x,y) = 10; sentaks hatası verir.çnkü (x,y) lvalue expr. olma niteliğinde değil.
	c++ ise geçerli.

	int x;

	(((x))) = 4; geçerlidir.x in değer kategorisini değiştirmiyor parantez
	(x++)++ bu legal değil. geçersiz. çünkü x++ rvalue expr.

	// KONTROL DEYİMLERİ
	if
	
	while
	do while
	for statement

	switch
	goto

	break
	continue

	return

	if in içi boş kalamaz sentaks hatası.expression olmalı
	if(x) ile if(x!=0) aynı. birincisi tercih ediliyor.

	if(x == 0) ile if(!x) aynı.ikisinde de x  0 iken girer.

	*/


	double dval = 3.4;
	// buradaki virgül hata ile konuldu, nokta olmalıydı
	// virgül operatörü sağ operandın değeridir.
	if (dval > 2, 0) // 0 döndürecek ve bloğa girmeyecek.
		printf("Evet dogru\n");
	else
		printf("Dogru degil\n");


	int x = 1;
	int y = 1;
	int z = 1;
	
	x += y += z;
	//x = (x + (y = (y + z)));
	
	printf("%d %d %d",x,y,z);

	printf("--------------------------------------\n");

	x = 2, y, z;

	x *= 3 + 2;
	printf("%d\n", x); //10

	x *= y = z = 4;
	printf("%d\n", x);

	x = y == z;
	printf("%d\n", x);

	x == (y = z);
	printf("%d\n", x);


	printf("--------------------------------------\n");
	
	x = -3 + 4 * 5 - 6;
	printf("%d\n", x);

	x = 3 + 4 % 5 - 6;
	printf("%d\n", x);

	x = -3 * 4 % -6 / 5;
	printf("%d\n", x);

	x = (7 + 6) % 5 / 2;
	printf("%d\n", x);

	printf("---------------------------------------\n");

	int a = 0;

	if (-1 < a-- < 0)// if bloğu sequence point(yan etki nok) olduğu için if yanlış ama
					// a nın değeri bu noktaya gelince değeri azalmış.
		printf("if girdi %d\n", --a);
	else
		printf("else girdi %d\n", a);
		printf("else girdi %d\n", ++a);

		printf("----------------------------\n");

		x = 1;

		if (++x > 2, 5)
			printf("%d\n", ++x);
		else
			printf("%d\n", x++);

		x = 0;
		y = 1;

		printf("%d\n", !!x == !!y > x + 1);
		printf("%d\n", !!y > !y == !!x < !x);
		printf("%d\n", !x + !!x + y - !y - !!y);

		printf("---------------------------\n");

		double d = 0.;
		int i;

		d = d + 0.1 + 0.1 + 0.1 + 0.1;
		d;
		if (d == 0.4)
			printf("d, 1. degerinde\n");
		else
			printf("d, 1. degerinde degil\n");


		int t;

		x = y = z = t = 1;
		x = (++y > 1) || ((z++ > 1) && (++t > 1)); // Kısa devre kuralını unutma.!!!!! || den sonrası yapılmıyor.
		printf("%d %d %d %d", x, y, z, t);

		x = 10;
		y = ++x;
		y = x++;

}