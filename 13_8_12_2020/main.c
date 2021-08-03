#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h> // rand icin eklendi
#include <stdio.h>
#include <conio.h> //standart değil._getch ve _getche icin eklendi
#include "Windows.h" // sleep icin

void clear_input_buffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != 'EOF') // newline ve hata kodu yoksa devam...
		;	// burada yapılan std inputun akış bufferından sürekli char extract etmektir.
			// newline veya eof hata kodu görürse dongu sonlanacak.
}

int isleap(int y)
{
	//	artık yılda 4 e tam bölünecek. 
	//	ya 100 e tam bölünmeyecek
	//	ya da 400 e tam bölünmeyecek. 1900 yılı bug değeri  
	return y % 4 && (y % 100 || y % 400);
}

int main()
{

	// if in doğru kısmı boş olabilir, bloklanmış {} bir birleşik deyim olur

	// if(x!=0) ile if(x) aynı şeydir.
	// if(x == 0) ile if(!x) aynı şeydir.

	/*
		en sık if hatası
		if(x = 0) // x == 0 yazılacakken bir = eksik yazıldı yani atama operatörü kullanıldı

		if((x = func()) == -1) sık kullanılan geleneksek idiyom.
		{		} // x = func() ın değeri x e atanan değerdir. bu değer de -1 ile karşılaştırılıyor.

		File *f;

		if((f = fopen("asd.txt","r")) == NULL)
		{ fprintf(stderr,"file cannot open\n")
		   return 1;
		}

		if((c = getchar()) != '\n')
		{
		}

		aşağıdaki ile aynı.
		if(c = getchar(), c!= '\n')
		{
		}

		-----------------------------------

		if(expr)
			statement
		else
			statement

		if(a<x<10) // burası always true
		{    }

		if(10 > x && x > a ) doğrusu bu

		karşılaştırma operatörü yerine atama operatörünü kullandığımızda sentaks hatası
		versin diye if(x == 5) yazmıyoruz. lvalue ile rvalue yer değiştiriyor.
		if(5 == x) yazıyoruz ki eğer yanlışlıkla bir tane = unutulursa hata versin diye.
		if(5 = x) gibi. Sentaks hatası bizim dostumuz.logical hatalar çok tehlikeli.


		if(exp1 && exp2) iki yerine bir ampersand kullanmak. yani bitsel operator
		if(exp1 || exp2) iki yerine bir ampersand kullanmak. yani bitsel operator
		bitsel operatorlerde double tipinde değişen olamıyor.
		sentaks hatası

		if(dval > 7,5) 5 olduğu için always true
		{   }
		if(dval > 7,0) 0 olduğu için always false

		func()
		{
			printf("func call\n");
			return 0;
		}

		if(func) // always true olur çünkü fonksiyon çağrısı değil bu.
		{		// fonk objesinin adını yazmışız.
		}

		if(x % 2); // buradaki ; demek if ile arasında birşey olmadığı için
		{			// null statement olarak geçiyor.
			printf("yazi");
		}

		if(x != 10 || x!= 23) // burası always true. && kullanılması mantıklı.

		if in doğru kısmı olmak zorunda
		if(x>10) sentaks hatası
		else
			++m;

		-------------------------------------

		dangling else

		if(x>10) //else ikisine birden ait görünüyor.else içteki if e aittir.
			if(y>15) // blok kullanmak daha mantıklı
				++m;
		else
			--z;

		ayrık if ifadeleri gereksiz kalabilir.compiler optimizasyon yapmazsa böyle verimsiz
		bir kod olarak kalır. bunun için elseif merdiveni kullanmak mantıklı.

		aşağısı verimsiz kod.
		if(x == 13)

		if(x == 15)

		if(x == 25)

		if(x == 47)


		ELSE IF MERDIVENI(letter) ile yazılmalı.Burası eski yazım şekli.
		if(x ==13)
			foo();
		else
			if(x == 15)
				func()
			else
				if(x == 25)
					func2();
				else
					if(x == 47)
						func3();


		Günümüzde else if anahtar sözcük gibi düşünülüp aşağıdaki gibi yazılıyor


		if(x ==13)
			foo();
		else if(x == 15)
			func()
		else if(x == 25)
			func2();
		else if(x == 47)
			func3();
		else // en son else olursa gayet iyi olur.
			func4();

	NOT: else if kullanılan yerde ayrık if deyimleri yazmayın
		1) yazımı zorlaşabilir.
		2) kodu okuyanı yanıltır.
		3) derleyici optimizasyon yapmazsa daha verimsiz bir kod oluşabilir.
		4) switch deyiminin bariz şekilde kullanılacağı yerlerde, else if yerine
		switch deyimini kullanın.
			a) kod daha kolay okunur.
			b) derleyici else if yerine, switch içn daha etkin bir kod oluşturabilir.


		if /else if yapısında oluşma ihtimali yüksek olan expressionları başa yazmak mantıklı.
		çünkü kontrol yukarıdan aşağıya yapılıyor.


		-------------------------------------------

		if deyimi bir sequence point oluşturur.
		yani if(++x > 10) bundan sonra x in artırılmış değerini kullanma garantim var.

		-------------------------------------------

		Redundant Else

		if ten sonra else kullanmayan yazım stiline deniyor.
		int getabs(int x)
		{
			if(x >= 0)
				return x

			return -x;  // burada else kullanılmadı. Bu stilde yazanlar var..Redundant else
		}

		--------------------------------------------

		else bir if e ait olmalı
		if siz bir else herzaman sentaks hatasıdır.

		--------------------------------------------

		DERLEYİCİNİN VERDİĞİ UYARI VE HATALAR

		1 - otomatik ömürlü bir değişkeni çöp değer ile kullanmak.
		2 - bir değişkeni tanımlamak ama kullanmamak.
		3 - yan etkisi olmayan bir ifade deyimi yazmak.
			çünkü deyimin olması ile olmaması arasında fark yok.
			mesela x+y; 4;

		--------------------------------------------

		STANDARD GETCHAR VE PUTCHAR FONKSİYONLARI

		getchar
		standart giriş akımının bufferından bir karakteri extract(alıyor) ve geri dönüş değeri ile
		o byte ın yada karakterin kodunu döndürüyor.Eğer buffer boşsa bir giriş yapmak gerekecek.

		printf("bir giriş yap\"); BABA yaz
		int c = getchar(); bufferdan extract etti ve B karanterini aldı
		printf("c = %d\n",c); c = 66 değerini yazdırır.


		iki getchar olsaydı ve yazdırılsaydı
		c = 66
		c = 65
		yazacaktı.

		örneği kod bölümünde

		getchardan önce buffer boş olmalı yoksa varolanı boşaltıyor.





	*/

	/*
		printf("bir giris yapiniz\n");
		int x1 = getchar();//asd gir
		int x2 = getchar();
		int x3 = getchar();

		printf("x1 = %d, x2 = %d, x3 = %d\n", x1, x2, x3);

		//	-----------------
		*/

		/*
		int a2;

		printf("bir giris yapiniz\n");
		int a1 = getchar(); //a23 giriyorum
		scanf("%d", &a2);

		printf("a2 = %d\n",a2);
		*/
		// -----------------------------
		// SCANF ORNEGI

	/*int c;
	int x;
	printf("bir tamsayi giriniz\n");
	//6789 girersek

	x = 0;
	while ((c = getchar()) != '\n')// ilk turda degeri 6, ikinci turda *10 old. icin 60 + 7
	{								// ucuncu turda 670+8, durduncu turda 6780+9
		x = x * 10 + c - '0';
		//printf("%d", c - '0');
	}
	printf("%d\n", x);
	printf("donguden cikildi\n");
	*/
	// ----------------------------------
	/*
	int k, l;

	printf("bir tamsayi giriniz \n");
	scanf("%d", &k);

	printf("bir tamsayi daha giriniz \n");
	clear_input_buffer();// bunu çağırmadan yukarıda 4564asd girersem %d ile string son string kısmını okuyamıyor.
	scanf("%d", &l);	// buradaki scanf yine stringi %d okumaya çalıştığı için okuyamıyor sonlanıyor..
						// clear buffer sayesinde buffer boşalıyor ve tekrardan giriş bekleniyor.

	*/

	// -------------------------------------


	// çok büyük sayının 3 e bölünüp bölünmemesi rakamları toplamı 3 e bölümünden geçer.
	// çok büyük int ise getchar ile çekilebilir.
	
	/*
	int c;
	int sum = 0;
	printf("Cok buyuk bir rakam giriniz\n");

	while ((c = getchar()) != '\n')
	{
		//printf("%d\n", c - '0');
		sum += c - '0'; //sıfırın ascideki yerinden çıkartılınca kendi değeri
	}
	*/
	/*
		0 = 48 sonucunu verir.
		2 = 50 verir.

		burada herhangibir sayıyı elde etmnek için sayı - '0' dersek
		örneğin 2 için => 2 (karakter kodu = 50) - '0' => 50-48 den 2 verir.
		öbür türlü direkt 2 yazılırsa 50 verir çünkü asci deki yeri 50.

	*/
	/*
	if (sum % 3 == 0)
	{
		printf("sayi 3 e bolunur\n");
	}
	else
	{
		printf("Sayi 3 e bolunmez\n");
	}
	*/  
	/* -----------------
	1 - Line-buffered bir fonksiyon(new line istemeyen)
	2 - getchar ile scanf aynı bufferı paylaşıyor.
	3 - getchar echo veren bir fonksiyon.yani girişteki karakter ekranda görünüyor
	echo vermeyen standart giriş fonksiyonu yok. std olmayan var.

	visual studio da _getch başka yerlerde getch olabilir.
	getchar ile aynı işi yapıyor.Line buffered değil ve echo da vermiyor.
	*/
	

	// _getch girer girmez karakteri sonuca geçiyor.entera basmakta gerekmiyor.
	/*
	printf("bir karakter giriniz\n");
	int c1;
	c1 = _getch();
	//c1 = _getche(); line buffered olmayan buda.new line istemiyor.
	
	printf("c1 = %d\n", c1);
	*/
	// getchar std. new line var echo var
	// _getch std değil new line var echo yok
	// _getche std değil new line yok echo var


	// --------------------------------------------
	// --------------------------------------------

	// STANDART PUTCHAR FONSIYONU
	// variadic değil.Tek parametre alıyor.
	// asci karakter kodda 65 nolu kodun karşılığı A karakteri

	/* putchar(65); // ekrana A yazar
	printf("\n");
	int c;

	printf("bir rakam gir\n");
	scanf("%d", &c);
	putchar(c);
	*/

	/*
	for (int i = 33; i < 127; i++)
	{
		putchar(i);
	}
	printf("\n");
	// veya
	for (int i = 33; i < 127; i++)
	{
		printf("%c",i);
	}
	*/
	
	// -----------------------------------------------
	//rand() % 26 -> 0 ile 25 arası rakam üretir
	//rand() % 26 + 'A' -> A dan Z ye kadar olan harfleri random üretir.'A' nın ascideki kodu üzerine
	// 0-25 han, büyük harflerin başı ve sonu aralığında sayı ekleniyor.
	
	/*
	for (;;)
	{
		putchar(rand() % 26 + 'A');
		Sleep(rand() % 20 * 10); // öncelik soldan sağa :)
	}
	*/

	// TEST FONKSIYONLARI
	// test function - query function yada C++ daha çok geçen predicate
	/*
		eğer geri dönüş değeri nonzero ise sayı asal.Zero ise asal değil.
		int isprime(int);

		int is_valid_card(int);
		iseven -> bu tip fonksiyonlar tek return ile yazılıyor genelde
		return x % 2 != 0; Yani 9 gönder false yani 0 döner.Yani çift değil gibi...

	*/
	
	// ARTIK Yıl Test Fonksiyonu
	//(şubat ayının 29 güne sahip olduğu yıllar.)
	
	/* int y;
	printf("Bir yil girin\n");
	scanf("%d", &y);

	if (isleap(y))
	{
		printf("%d artik yil\n",y);
	}
	else
	{
		printf("%d artik yil degil\n",y);
	}
	*/

	/*
	int isupper(int ch) nonzero değer true olur
	int islower(int ch) nonzero değer true olur
	int isalpha(int ch) nonzero değer true olur
	int isdigit(int ch) nonzero değer true olur
	int isalnum(int ch) nonzero değer true olur
	int isxdigit(int ch) nonzero değer true olur (0123456789ABCDEFabcdef) hex sayı sisteminde basamak gösteren karakterden biri mi
	int ispunct(int ch) nonzero değer true olur görüntüsü var ama harf yada rakam değil.
	int isspace(int ch) nonzero değer true olur space tuşu yatay duset tab \f \n \r bunlar bosluk charlar
	int isblank(int ch) nonzero değer true olur bosluk karakter ve tab karakterler blank chardır
	int isprint(int ch) nonzero değer true olur görüntüsü olan tüm charlar
	int isgraph(int ch) nonzero değer true olur görüntüsü olan tüm charlar(aynısı) sadece  ' ' char yok.
	int iscntrl(int ch) nonzero değer true olur görüntüsü olmayan özel amaçlı kullanılan karakterler. ascide 0-31 olanlar birde 127 nolular kontrol karakterleri.
	
	*/








}