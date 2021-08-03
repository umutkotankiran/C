/*

aşağıdakilerin define komutu yok
aşağıdakiler en önemlileri

Predefined symbolic constants
__LINE__	kodun hangi satırda oluduğunu verir
__FILE__	file adını
__DATE__	tarih
__TIME__	saati verir.
__func__   c99 da geldi. Bu tip daha macro var. fonksiyonun adını verir.
__STDC__	eğer derleyicinin eklentileri kapalıysa bu macro tanımlı kabul ediliyor.

yani. standart bir C derleyicisi aşağıya girer.Aksi halde defined kabul edilmeyecek.
cpp karşılığı da var __cplusplus
#ifdef __STDC__

#endif  

yukarıdaki macrolar undef ile kaldırılamaz.


====================================================================

Switch statement 
if yerine kullanılabilir.
Daha kolay okunup yazılıyor ve duruma göre derleyici daha iyi optimize ediyor switch kodunu.

buradaki x integer expression. Reel sayı olamaz.
case bir anahtar sözcük. bunlar etiket/label.bunlara case etiketi deniyor. 
goto deyiminde de etiketler kullanılıyor

not case etiketleri unique olmalı. yoksa sentaks hatası.

switch(x)
	case 1:
		statement; statement;
	case 2:
		statement;


statementlardan sonra break koymazsak koşulu sağladıktan sonraki tüm etiketlere girer.

x = 2;
switch(x)
	case 1:
	...
	case 2:  break koyulmazsa.burası ve sonraki tüm caselerin içerisine girer
	...
	case 3:  
	...
	case 4:
	...



case 4:
...
case 2:
...
case 5:
...
yukarıdaki gibide olabilir.
sıralama olmak zorunda değil.

case 10 / 2  - 1:   buda geçerli.

if ve else if merdivenleri için switch yazılabilir ama hepsi için yazamayız.
mesela 
if(x > 2.3) burada tamsayı yok.reel sayı var. switch te tamsayı olmak zorunda.
...
else if ..     

---------
int n = 3;
int x = 5;

switch(n)
{
	case 1:
		asdasdsad
	case 2:
		qweqwewqe
	case x:
		qwe123ased      x constant olmadığı için sentaks hatası. C++ ta sentaks hatası değil.
}

switch(n)
	case 'a':  bu geçerli çünkü bir karakter sabiti çünkü bir int değer olarak tutuluyor.
	case '\x1a':   bu karakter literali de tamsayı sabitidir. geçerli.

	case "Ali":		bu bir char array olduğu için hatalı.

	case SMALL:
	case MEDIUM:
	case LARGE:   bunlar sembolik sabit ise ki öyle olmalı.Geçerlidir.


	gerek else if gerek switch te oluşma sıklığı yüksek olan durumları yukarı taşımak mantıklı.


---------------

default etiketi. default bir keyword.
default else if teki else ifadesi ile aynıdır. 
default sonda değil herhangibir yerde olabilir.
 
x = 2;
switch(x)
	case 1:
	...
	case 2:  
	...
	case 3:
	...
	case 4:
	...
	
	default:
	...

	case altında 2 den fazla statement varsa fonksiyon yapmak mantıklı.
	
	tek case ifadesi yerine if else yazmak daha kolay
	switch(x)
	{
		case 1:
		...
	}
	yerine
	if(x == 1)
	{
		...
	}

	switch (x) {
	case 1:
	case 2:
	case 1: //geçersiz
}
 


	switch(x)
	{				//dikkat: herhangibir case e girdikten sonra, sonrasındaki tüm caseler çalıştırılır.
		case 1:		// 1 e girerse 1,11,21 çalışır ve break. zaten sadece 21 de yazı var.
		case 11:	//	11 e girerse 11 ve 21 çalışır ve break, yine printf çalışır.
		case 21:	// 21 e girerse sadece 21 çalışır orda da printf çalışır ve break.
			printf("st"); break; 
		case 2:				
		case 12:			
		case 22:
			printf("nd"); break;
		case 3:
		case 13:
		case 23:
			printf("rd"); break;

	}

	breaklar zorunlu değil istenirse break hiç yazılmadanda olur.

	Compiler Explorer önemli. https://godbolt.org/
	Static kod analizi programları



	----------------------

	 int sum = day;

	switch (month - 1) {
	case 11	: sum += 30; //fallthrough   //bilerek yapıldığı için bu ifade yazılmış
	case 10	: sum += 31;  //fallthrough	//yani girdiği yerden aşağı kadar devam edecek çünkü break yok.
	case 9	: sum += 30;  //fallthrough cpp olsaydı [[fallthrough]]
	case 8	: sum += 31;  //fallthrough
	case 7	: sum += 31;  //fallthrough
	case 6	: sum += 30;  //fallthrough
	case 5	: sum += 31;  //fallthrough
	case 4	: sum += 30;  //fallthrough
	case 3	: sum += 31;  //fallthrough
	case 2	: sum += 28 + isleap(year); //fallthrough
	case 1	: sum += 31;

	---------------------------------

	#include <stdio.h>
	int main()
	{
		switch (1) {
			printf("bu deyim gecerli ama yurutulmez\n");
			case 1: printf("bir\n"); break;
			case 2: printf("iki\n"); break;
		}
	//
}

	------------------------------------------------------------------
	------------------------------------------------------------------

	aşağıdaki geçerli

			int main()
			{
			int a = 1;
			switch (a) {
				int x;			// labellardan önce değişken bildirimi yapılabilir
				case 1: x = 10; break;
				case 2: x = 20; break;
				}
			}

			aşağısı ise geçersiz. case 1 altında bildirim var.

			int main()
			{
				int a = 1;
				switch (a) {
					case 1:
					int x;		//C’de geçersiz C++ ta geçerli.Bir sonraki case de block tan çıktığı için garbage value.
					x = 10;		// undefined behavior.
					//
					break;
					case 2: ++x; break;
					///
				}
			}

				int main()
			{
				int a = 1;
				switch (a) {
					case 1:
					int x = 10;		//Hem C’de geçersiz hemde C++ ta geçersiz
					//
					break;
					case 2: ++x; break;
					///
				}
			}


			Aşağıdaki geçerli çünkü case 1 null ve sonrasında bildirim
			daha sonrasında diğer case

			int main()
			{
				int a = 1;
				switch (a) {
				case 1:;
					int x = 10;		//case içinde olmadığı için bildirim geçerli
					//
				   // break;
				case 2: ++x; printf("%d\n", x); break;
					///
				}
			}



	ÖNEMLİ!!!!!!!!!!!!
	case ler sıralı bir şekilde yapıldığında(büyükten küçüğe ya da küçükten büyüğe) 
	daha low levelda C bir jump table oluşturuyor ve istenen hedefe direkt gidiyor.
	bu durum else if merdiveninde karşılığını oluşturamayabiliyor.



	=========================================
	=========================================

	goto statement

	birçok yerde jump statement var.
	while
	for
	switch
	görsekte görmesekte assembly karşılığında jump statement var.

	a ) long jump : bir fonksiyonun kod alanından başka bir fonksiyonun kod alanına geçmesine denir. Bu go to
	b ) local jump(near jump) : aynı fonksiyon alanı içerisinde başka bir yere programın akışını geçirir. setjmp, longjmp isimli fonksiyonlar yapar. 

	Not:
	iki üç tane while içerisinden bir koşula bağlı olarak hemen çıkmak için go to kullanılabilir. Baya iyi olur.
	kullanım temalarının dışında da kullanmamak lazım.

	C de labellar var. ismi olan varlıklardır.

	out:  -> bu out isimli bir etiket yaratmış olur.
	etiketten sonra bir statement gelmeli

	out:
		;
		null statement hata değil.olmasaydı sentaks hatasıydı.

	labellar ayrı bir scope kuralına tabidir.

	hatırlatma
	file scope : global isim alanında tanımlanan isimlerin kapsamı.
	block scope : block içinde tanımlanmış ismin o blockta kullanılmasıi.
	func. prorotype : func bildiriminde kullanılan değişken isimlerinin alanı. Sadece parantez içindeki alandaki isim o daisim yazılırsa yani x. void func(int x).
	function scope : bir label tanımlanır ve yukarıdan da aşağısından da bu label kullanılabilir.labellar ayrı scope olduğu için
	fonksiyon içindeki diğer isimlerle çakışmaz.

	çakışma olmaz.hata değil.
	void func()
	{
		int out = 5;
		out:
			;
	}

	goto keyword ünü bir label takip etmeli.
	goto error;

	ve bu fonksiyon içinde error tanımlanmalı

	error:			// yukarıdaki goto akışı buraya yönlendirdi.
		printf("hata");


		//statement
		//statement
		if(1)
			goto error;
		//statement
		//statement
		error:
			printf("Error\n")


			error label yukarıda da olabilirdi ama böyle bir kullanım yok.çok çok farklı bir durumda olabilir.
			hata deil ama yapılmıyor.Programı yukarı noktaya yönlendirme yok.


			while (1)
				//statement 
				while(1)
					//statement1 
					while (1)
						//statement2 
						if(x=5)
							goto result;

			//statement5
			//statement6 

			result:
				printf("result \n");


			go to olmadan da bir flag değişken alınır.
			0 değeri verilir. eğer true olursa break yapılır.
			diğer tüm while lar içerisinden flaga bakılır true ise break yapılır

			while(1)
				{
					switch(1)
					{
						break;  burası switch içinden çıkarır. while dan çıkmak için go to kullanılır.
					}
				}


			switch(x)
			{
				case 1: statement1; break;
				case 2: statement2; break;
				case 3: statement3; break;
				default : statement ; break;  // default yerinde defualt yazsaydım burada bir label yaratmış olacaktım
												// ve hata vermemiş olacaktı. keyword olan default ama defualt: bir label dır.

			}

			--------------------------------------
			case ifadeleri olarak sembolik sabitlerin (symbolic constants) kullanılması çok sık karşılaşılan bir durumdur

			#define OFF 0
			#define ON 1
			#define STANDBY 2
			#define HOLD 3
			int get_remote_case(void);
			int main()
			{
				//
				switch (get_remote_case()) {
					case OFF : //
					case ON : //
					case STANDBY : //
					case HOLD : //
					default : //
				 }
				 //
			}


			================================================================


			Multiple inclusion guard
			
			bir başlık dosyasının bir kod dosyası tarafından birden çok kez include edilmesini engelliyor.
			birden çok include sentaks hatası

			mesela struct ta da sentaks hatası olur
			//-------------------

			#line	-> bu kod üreten komutlarda kullanılır.__LINE__ macrosunun değerini değiştiriyor.
			#line 1000 dersem printf("%d",__LINE__) bu değeri 1000 verir.
			#line 1000 "umut.c"   printf("%s %d",__FILE__,__LINE__)  -> 1000 ve umut yazar. çok özel kullanım senaryosu var.

			//-------------------

			#error -> programın derlenmesini önişlemci aşamasında durduruyor.

			kodda  #error hata var  //yazınca duruyor.derleme sürecinde durduruyor.

			#ifndef  __cplusplus  -> bu C++ ta tanımlı kabul ediliyor.ama C derleyicisi bunu kabul etmiyor.
			#error BU kaynak dosya sadece c++ derleyicisi ile derlenir.
			#endif

			//--------------------

			#pragma

			pragma standart ama ne yapılacağı kendisine bağlı. tüm derleyicilerin pragmaları var.
			aynı olmak zorunda değil

			#pragma once -> multip inc. guard sağlıyor.
			#pragma pack(1) -> alignment sağlıyor.
			#pragma warning (disable: 4706)   4706 nolu uyarı mesajını verme demek bu.


*/

#include <stdio.h>

int main()
{
	

}