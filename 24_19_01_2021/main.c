#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "nutility.h"
#include <ctype.h>

#define SIZE	1000

int main()
{

	//BINARY SEARCH. Sıralı dizide ortadaki elemana gidip aranılan değer kıyaslaması yapılıyor.
	// ortadaki değer aranılandan büyükse, büyük olan kısım(sağ taraf bu örnekte) tamamen kaydırılıyor.
	// kaydırma işlemi ortadaki bulunan değeri de kapsar.
	/*
	int a[SIZE];
	randomize();
	set_random_array(a, SIZE);
	sort_array(a, SIZE);
	print_array(a, SIZE);

	int sval;
	printf("aranan degeri giriniz: ");
	(void)scanf("%d", &sval);

	int idx_first = 0; // dizinin başı
	int idx_last = SIZE - 1; // sonu
	int idx_mid; // ortadaki değer
	int cnt = 0;

	// idx first, lastı geçerse olmadığı anlaşılır.
	while (idx_first <= idx_last)
	{
		cnt++;
		idx_mid = (idx_first + idx_last) / 2;
		if (a[idx_mid] == sval)
			break;
		if (a[idx_mid] > sval)
		{
			idx_last = idx_mid - 1; // ortadaki değerde silindiği için  mid - 1 artık last değer olur
		}
		else
			idx_first = idx_mid + 1; // mid yine gittiği için bir sonrakinden devam ediyor artık first
	}

	if (idx_first < idx_last) // bir süre sonra idx first ve last birbirine göre kıyaslanır.
	{							// habire değişiyor.
		printf("aranan deger bulundu dizinin %d indisli elemani ", idx_mid);
	}
	else
		printf("aranan deger bulunamadi %d sorgulama\n",cnt);

	====================================
	===================================

	*/

	//STRINGLER VE CHAR TÜRDEN DİZİLER

	//char str[100]; // yazı tutacak dizi.Yazı karakterlerden oluşur.her karakterinde kodu var.
	//char d = 65; // yazdırırsak A yazar. çünkü A nın ASCI deki kodu 65.
	//printf("%c", d);

	// Yazının son karakterinden sonra '\0' -> NULL character.
	// karakter sabiti '\0'. tamsayı değeri 0000 0000 yani 0
	// Yani NULL char demek karater kodu 0 olan tamsayı demek.
	// '\0' ile 0 arasında fark yok. ama A farklı. 'A' = 65 (0100 0001)
	// '0' ise 0 karakterinin kodu demek. 48 dir bu da
	// '\0' ise 0 dır. \ escape sequence.
	// NUll terminated byte stream. yazıların tutulma şekli C de böyle.
	// 
	/*
		int x = 0 ile int x = '\0' aynıdır.
		ama int x = '0' olursa. 0 karakterinin kodu asci de 48 olduğu için 
		x 48 değerini tutar.
	
	*/

	/*
		char array sonuna '\0' koymamak hata ama UB değil,
		UB bu char arrayi kullanmak.

		char a[SIZE]; -> burada yazının sonundaki null character görmeden yazı uzunluğunu bilme şansı yok

		char s[SIZE] = "UMUT KOTANKIRAN";
		yazdırmak için
		for(int i = 0; s[i] != '\0';i++)
			printf("%c",s[i]);
			// yada putchar(s[i]) -> tamsayı kodunu alır std outputa görüntüsünü verir.

		s[i] != '\0' burada s[i] != 0  olsada farketmez. aynı şey.
		'\0' bunu yazınca char ile ilgili bir iş yaptığımız belli oluyor.
		ya da s[i] yazılabilir.

		--------------------------------
		char s[SIZE];

		s[0] = 'A';
		s[1] = 'B';
		s[2] = 'C';
		for(int i = 0; s[i] != '\0';i++)
			printf("%c",s[i]);

			BURADA UB var. tanımlamak değil.Kullanmak UB.
		---------------------------------

		Eğer char s[SIZE]; global de tanımnlanırsa UB YOK. çünkü 0 yazar elemanlara. 
		bu da NULL char demek.

		----------------------------------------------
		
		Eğer static char s[SIZE]; şeklinde tanımlansaydı.
		elemanlara 0 yazacağı için yine UB YOK.
		global scope taki aynı zamanda static olduğu için 0 yazar elemanlara.

		------------------------------------------------

		her seferinde döngü yazmak yerine standart C fonksiyonu yazmak daha kolay
		puts

		static char s[SIZE] = "Ali ata bak";
		puts(s); // dizinin tuttuğu yazıyı stdout a yazdırıyor.
		yazdırdıktan sonra bir de newline \n veriyor.

		puts a bir adres verilebilir.variadic değil.

		printf("%s",s);  %s -> Char türden dizinin adresi ile eşleştirilirse, yazıyı yazdırır.
		burada newline yok tabi.


		char name[SIZE] = "Umut";
		char surname[SIZE] = "Kotankiran";
		int byear = 1990;
		printf("%s %s %d yilinde dogdu",name,surname,byear); sorunsuz kod.

		NOT : 
		char s[100]; char dizisi sadece char tutmaz.char bir tamsayı türü
		yani yazı yerine küçük tamsayı değerleri de tutablir.
		
		char s[100];
		s[0] = '\0'; bu da olabilir
		
		
		-----------------------------------------------
		-----------------------------------------------


		CHAR DİZİLERE İLK DEĞER VERMEK

		char türden diziye ilk değer verilebilir ama atama yapılamaz.

		char s[100] = "ali veli"; bu olur
		s = "burada yazi var"; burası sentaks hatası.
		array ler lvalue expression olamaz.
		adres operatörü ile oluşturulan ifadeler lvalue expression olamaz.

		char s[100] = {'m','e','h','m','e','t','c','a','n'}; bu şekilde olabilir.UB yok
		çünkü ilk değerler verilmiş.daha sonraki değerlerde 0 ile başlatılır.yani null character.

		char s[] = {'A','L','I'}; dizi boyutu belirtilmemiş. dizi boyutu 3 olacak. '\0' yok
		yani kullanımı UB oluşturur. aslında char s[3] = {'A','L','I'} ile aynı şey aslında.


		Çok daha kolay bir yöntem var yukarıda yazdık zaten
		char str[SIZE] = "UMUT";
		puts(str); yazdırır \n koyar sonuna.Hata yok.Defined behaviour.(Undefined ın tersi defined)

		char str[] = "UMUT"; Bunun kullanımında UB oluşmaz. Çünkü string sonuna '\0' da dahil.
		printf("%zu",sizeof(str)) -> 5 verir. UMUT'\0' gibi.


		-------------------------------------------------------------------------------------

		C ve C++ farklılığı

		char str[5] = "EMRAH"; burada C++ olsaydı sentaks hatası olurdu.çünkü null char da dahil
		6 karakter var.dizi eleman boyutu 5. sığmadığı için geçersiz. C de geçerli.
		C de geçerli ama kullanmak UB oluşturur eğer bir kullanım olursa.

		puts(str) -> bu adresteki yazıları yazdırıyor
		yukarıdaki adresin sonunda null karakter yok ve yazdırmaya çalışacağı için UB var.

		----------------------

		UB ler tekrar edilirse

		char s[100];
		s[0] = 'A';
		s[1] = 'B';		
		burada s[2] çöp değer var UB oluşturur

		char s[] = {'w','e','s'};
		dizi 3 boyutlu ve sonra null yok. UB var

		char s[3] = {'w','e','s'}; aynı şey.burada da 3 boyutlu ve 3 eleman var. null yok. UB var

		char s[5] = {'w','e','s'}; UB değil çünkü değer verildikte sonra diğerlerine 0 yazar.

		char s[] = {'w','e','s','\0'}; bu geçerli.UB oluşturmaz.

		char s[4] = "OMER"; C++ ta sentaks hatası. C de geçerli ama yazdırmaya çalışınca null char 
		olmadığı için UB oluşturur.

		----------------------------

		int c;
		int idx=0;
		char str[SIZE];

		printf("bir yazi girin: ");

		while((c = getchar()) != '\n')
		{
			str[idx++] = c;
		}
		str[idx] = '\0'; son karakter null oluyor artık.bunu koymazsam kullanımda UB oluşur.

		printf("girilen yazi (%s)\n",str);

		scanf ile alınan data arrayin tutamayacağı kadar büyükse UB

		----------------------------------

		printf("isminizi girin");
		scanf("%s",str); // ali veli

		printf("(%s)",str);   // çıktıyı ali verir. boşluğu seperatör olarak alır scanf yukarıda.

		--------------
		scanf ile sığamayacak yazıyı char array elemanlarına atamak runtime hatası 

		-----------------------------------------

		char name[SIZE];
		char surname[SIZE];
		int age;

		printf("isim soy isim ve yasinizi giriniz");
		scanf("%s%s%d",name,surname,&age);
		printf("%d yasindeki %s %s",age,name,surname);

		gets_s(pointer,SIZE) -> bu normalde güzel bir function fakat hata verdi.
		daha sonra bakılacak


		-------------------------------------

		sgets biz yazdık

		char str[25];
		printf("bir yazi gir: ");
		sgets(str); // iyi çalışıyor.
		printf("(%s)\",str);


		=========================================================
		=========================================================

		Örnekler




	*/

	/*
	char str[SIZE];
	printf("bir yazi giriniz :");
	sgets(str);
	printf("(%s)\n", str);

	printf("yazi uzunlugu bulma \n");
	
	int i;
	for (i = 0; str[i] != '\0'; i++) // while da kullanılabilir.
		;

	printf("yazi uzunlugu %d", i);

	
	printf("----------------------------------\n");
	
	char str1[100];

	printf("yazinin sonuna x ekleme\n"); 
	
	printf("bir yazi girin : ");
	scanf("%s",str1);

	int j;
	
	for (j = 0; str1[j] != '\0'; j++)
		;
	str1[j] = 'x';
	str1[j + 1] = '\0';
	printf("(%s)", str1);
	*/
	/*
	printf("----------------------------------\n");

	printf("bir karakter sayma\n");

	char str2[SIZE];
	int c;
	
	printf("bir yazi gir str2 ");
	sgets(str2);
	printf("(%s)\n", str2);

	printf("sayilacak karakterleri giriniz \n");
	c = getchar();
	int cnt = 0;

	for (int i = 0; str2[i] != '\0'; i++)
	{
		if (c == str2[i]) // büyük küçük ayrımı yapmadan istersek toupper() ile karşılaştırır.
			cnt++;
	}

	printf("%d tane %c karakteri var", cnt, c);
	*/
	
	/*
	--------------------------------------------------

	hangi karakterden kaç tane olacağını bulacağım

	
	char str[SIZE];
	int counts[26] = { 0 }; // burası hangi harften kaç tane olacağını gösterir.

	printf("bir yazi girin : ");
	sgets(str);
	printf("(%s)\n", str);

	for (int i = 0; str[i] != '\0'; i++)
	{
		if (isalpha(str[i]))
		{
			counts[toupper(str[i]) - 'A']++;
		}
	}

	for (int i = 0; i < 26; i++)
	{	
		if(counts[i])
			printf("%d adet %c\n", counts[i], 'A' + i);
	}

	------------------------------------------------------------------

	bir yazının ters çevrimesi.reverse algoritması görüldü zaten.


	char str[SIZE];

	printf("bir yazi girin : ");
	sgets(str);
	printf("(%s)\n", str);

	int len = 0;

	for (int i = 0; str[i] != '\0'; i++)
		len++;

	for (int i = 0; i < len / 2; i++)
	{
		char temp = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = temp;
	}
	printf("tersi = (%s)\n", str);

	------------------------------------------------------

	Ödev

	bir yazının palindrom olup olmadığına bakan kodu yaz.boşluklar, virgüller... önemsenmiyor burada.
	at sahibi gibi, hasta!
	traş neden şart ?

	2 yol var. kolayı ilave dizi kullanarak yapılan.
	str dizisini kullanarak ve bu diziyi değiştirmeden.

	--------------------------------------------------------

	Ödev

	iki kelime girin.
	kod bu kelimelerin yerini değiştirecek.
	can sevdiren -> sevdiren can olarak değiştirilecek.

	değişken tanımı ok ama 2. dizi olmayacak.

	-------------------------------------------------------

	Ödev

	bir yazı olacak. boşluklar olabilir kelimeler arasında, istenildiği kadar boşluk. yazılan kod kelime sayısını bulacak.
	noktalama işaretleri olmayacak verilen yazılar arasında.
	yazının başında ve sonunda da büyük boşluklar olabilir.

	-------------------------------------------------------

	Ödev

	char s1[SIZE]
	char s2[SIZE]

	ikikelime kullanıcıdan alınacak.Eşitse eşit, değilse değil yazacak.

	--------------------------------------------------------

	printf("birinci kelimenin sonuna ikinci kelime eklenecek");

	char s1[SIZE];
	char s2[SIZE];
	
	printf("iki kelime giriniz ");
	scanf("%s%s", s1, s2);

	printf("(%s) (%s)\n", s1, s2);

	int i;
	for (i = 0; s1[i] != '\0'; i++)
		;

	int k;
	for (k = 0; s2[k] != '\0'; k++)
	{
		s1[i + k] = s2[k];
	}

	s1[i + k] = '\0';

	printf("%s\n", s1);


	---------------------------------------------------------

	Ödev

	char str[SIZE];
	int ch;

	printf("bir yazi girin: ");
	gets(str); // Ankara Antalya kahramanmaras
	printf("(%s)\n",str);
	
	printf("silinecek karakteri girin: ");
	ch = getchar(); //a

	kodun çıktısı aşağıdaki gibi olacak.
	// nkr ntly khrmnmrş   


	*/




}