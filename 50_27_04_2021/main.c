

/*

FILE OPERATIONS / DOSYA İŞLEMLERİ
---------------------------------
Dosya nedir?
Dosya ikincil saklama ortamlarındaki byte lar. yani 1 ler ve 0 lar.
Memory alanında değil, ikincil saklama ortamında.

File format?
Bu 1 ler ve 0 ların ne anlama geldiğinin bilgisidir.
Yani bunlar int mi string mi date mi mp3 mü jpeg mi olduğunun bilgisi.

Dosya işlemlerinden sorumlu olan kim/ne ?
İşletim sistemi

Hangi işlemi yaparsak yapalım bunu gerçekleştiren işletim sistemidir.
İşletim sistemi birsürü fonksiyon içerir. Programcı tarafından çağrılan fonksiyonlara
system functions denir.Mesela dosya işlemleri için işletim sisteminin system fonksiyonları çağrılmalı.
Bu fonksiyonlarda UNIX/LINUX sistemlerde POSIX fonksiyonlarıdır.
Standart hale getirilmiş fonksiyonlardır.

Bunlarında üstünde Standart C fonksiyonları var.

Linux/ Unix te POSIX olarak adlandırılan fonksiyonlar Windows Tarafında API olarak isimlendiriliyor.

BURADA 40 FONKSİYON VAR VE BİZ 30 KÜSÜR TANESİNİ GÖRECEĞİZ.

BU FONKSİYONLAR STDIO HEADER FİLE İÇERİSİNDE BELİRTİLMİŞ.

Arka planda bir handle sistemi var.

fopen -> handle sistemini başlatan fonksiyon
fclose -> handle sistemini kapatan fonksiyon

bir yapı nesnesinin adresini döndürüyor.
Burada FILE ın elemanlarına erişim yok. Elemanlar void ile gizlenmiş durumda.
FILE* fopen

bu adresi fclose a gönderiyoruz handle sonlandırmak için.
fclose(FILE *)


-----------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------

FOPEN

FILE* fopen(const char *filename,const char *popenmode);

başarısız olursa fopen geri dönüş değeri NULL Pointer.

Dosya açış modu:
Bu neleri belirliyor?

a - dosya varsa / yoksa ne olacak?
b - bu dosya açıldığında üzerinde hangi işlemleri yapabilirim? (okuma - yazma)


											varsa / yoksa

okuma modu (read)					Dosya varsa açılır / yoksa açılmaz					Dosyadan okuma yapılır ama yazılamaz


yazma modu (write)					Dosya varsa sıfırlanır(truncate) açılır /			Dosyaya yazma yapılır ama okuma yapılamaz
										yoksa yeni birtane oluşturulur

sona ekleme modu (append)			varsa açılır / yoksa oluşturulur					Dosyadan okuma yapılamaz ama dosya sonuna yazılır


---------------------------

okuma modu + (read)					Dosya varsa açılır / yoksa açılmaz				Dosyadan okuma yapılır ve yazılabilir


yazma modu + (write)				Dosya varsa sıfırlanır(truncate) açılır /		Dosyaya yazma yapılır ve dosyadan okunabilir
										yoksa yeni birtane oluşturulur

sona ekleme + modu  (append)		varsa açılır / yoksa oluşturulur				Dosyadan okuma yapılır ve yazma işlemi sondan yapılır



BİRDE DOSYA TEXT MODUNDA MI YOKSA BINARY MODUNDA MI AÇILACAK.
Buda önemli ileride görülecek.

----------------------------

Açış Modu


Bu modlar defaultta text modu.
------------------------------
Okuma "r"
Yazma "w"
Sona yazma "a"

Okuma "r+"
Yazma "w+"
Sona yazma "a+"


Binary modlar
-------------
Okuma "rb"
Yazma "wb"
Sona yazma "ab"

Okuma "rb+"    "r+b" de olur
Yazma "wb+"	   "w+b" olabilir
Sona yazma "ab+"      "a+b" olabilir


Bir dosyanın açılmamasının bazı sebepleri olabilir.
İlgili dosya yoksa read modda açılamayabilir.
veya başka bir yerde açıksa veya açık olan dosya limitini ilgili sistemde geçersek dosya açılması başarısız olabilir.
Sistemdeki başka bir problemde olur.

fopen ın geri dönüş değeri mutlaka test edilmeli.

malloc calloc realloc gibi...


-----------------------------------------------------------------------------------------------------------------


// yoksa hata verir.
int main()
{
	FILE* f;
	if ((f = fopen("yokdosya.txt", "r")) ==  NULL)
	{
		fprintf(stderr, "dosya acilamadi\n");
		return 1;
	}

	printf("dosya acildi\n"); 
}

----------------------------


int main()
{
	FILE* f;
	if ((f = fopen("neco.txt", "w")) ==  NULL)
	{
		fprintf(stderr, "dosya olusturulamadi\n");
		return 1;
	}

	printf("dosya olusturuldu\n");
}

---------------------------

NOT: BURADA fopen içinde path de verilebilir
fopen("c:\\cdr\asd.txt","r");

----------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------

DOSYA KAPATMA

int fclose(FILE *);

geri dönüş değeri başarı bilgisi.

0 --> başarılı
non-0 --> başarısız

Özel durum sözkonusu değilse fclose un return değeri çok kontrol etmeye gerek yok.




NOT !!!!!!!
DOSYA KAPATILDIKTAN SONRA HANDLE DEĞERİ INVALİD POINTERDIR.
YENİ ATAMA YAPMADAN KULLANILMAMALIDIR.

int main()
{
	FILE* f;
	if ((f = fopen("neco.txt", "w")) ==  NULL)
	{
		fprintf(stderr, "dosya olusturulamadi\n");
		return 1;
	}

	printf("dosya olusturuldu\n");

	FILE* fx = f;
	fclose(f);
	fclose(fx); //UNDEFINED BEHAVIOR
}




STANDART C FONKSİYONU DEĞİL AMA AÇIK TÜM DOSYALARI KAPATIYOR

int fcloseall(void); 
geri dönüş değeri kapatılan dosya sayısı.

int main()
{
	FILE* f1 = fopen("ali.txt", "w");
	FILE* f2 = fopen("veli.txt", "w");
	FILE* f3 = fopen("hasan.txt", "w");


	int n = _fcloseall();
	printf("%d adet file kapatildi\n",n);
}

-----------------------------------------------------------------------------

DOSYA KAPATILMAZ İSE NE OLUR ? 

ÖNCELİKLE AÇILAN TÜM DOSYALAR KAPATILMALI.

dosya kapatılmadan dosya abnormal terminate edilirse, bu tehlikeli durum, 
dosyaya yazılan veriler fiilen dosyaya yazılmamış olabilir.

-----------------------------------------------------------------------------
-----------------------------------------------------------------------------
-----------------------------------------------------------------------------
-----------------------------------------------------------------------------
-----------------------------------------------------------------------------

FGETC

int fgetc(FILE *);
getchar fonksiyonuna benziyor. getchar standart inputtan alıyordu, bu ise dosyadan karakter alıyor.

Geri dönüş değeri 0 ile 255 aralığıunda olacak.
başarısız olursa int türden -1 döndürecek.

---------------------------------------------------------------------------------------------------

FILE POINTER
DOSYA KONUM GÖSTERİCİSİ BU.

dosyadan okuma yapan ve dosyaya yazan fonksiyonlar kendilerini çağıran koddan 
dosyanın kaçıncı byte ı okunacak yada okuma dosyanın neresinden yapılacak ya da yazma işlemi
dosyanın neresine yapılacak sorusunun cevabını istemezler.

bu işlemleri dosyanın neresinden yapılacağını tutan bir değişken var alt levelda, 
buna file pointer(tamsayı değişken) deniyor.Buna doğrudan erişim yok.

Her okuma veya yazma yapıldığında bir sonraki byte a gidiyor bu pointer.

dosyanın tamamını okumak için sürekli okuma fonksiyonunu çağırıyoruz.
Dosyanın sonuna gelince EOF değerine gelmiş oluruz. 
Bu şekilde okuma/yazma yapılmasına sequencial access deniyor.

100bin byte varsa 85 bininci byte a erişmek için SEQUENCIAL ACCESS değilde 
file pointer değişkenini set ediyoruz. 85 bininci değere getiriyoruz ve okumayı yapıyoruz.

yada 40 bininciyi yapacaksak 40bininci byte a file pointer getirilir ve işlem yapılır.
Bu tip işlemlere RANDOM ACCESS deniyor.

NOT:
FILE POINTERI MANIPULE EDEN FONKSIYONLAR VAR.

	rewind
	fseek
	gsetpos
	fgetpos
	ftell

EOF -1 dir.

#define		EOF		-1

dosyada okunacak byte kalmazsa fgetc -1 döndürür.

-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------

ÖR:

int main()
{

	FILE* f = fopen("yazi.txt", "r");
	int c;

	if (!f)
	{
		fprintf(stderr, "Dosya acilamadi\n");
		return 1;
	}

	while ((c = fgetc(f)) != EOF)
	{
		printf("%c ", c);
		_getch();
	}
	fclose(f);
}


---------------------------------------------------------------------------------------------------------------


int main(int argc, char **argv)
{

	if (argc != 2)
	{
		fprintf(stderr, "kullanim yaz - dosya ismi\n");
		return 1;
	}

	FILE* f = fopen(argv[1],"r");
	if (!f)
	{
		fprintf(stderr, "%s dosya acilma hatasi", argv[1]);
		return 2;
	}

	int c;
	while ((c = fgetc(f)) != EOF)
	{
		putchar(c);
	}

	fclose(f);
}


-------------------------------------------------------------------------------------------------

int main(int argc, char **argv)
{

	if (argc != 3)
	{
		fprintf(stderr, "kullanim say - dosya ismi - karakter\n");
		return 1;
	}

	FILE* f = fopen(argv[1],"r");
	if (!f)
	{
		fprintf(stderr, "%s dosya acilma hatasi", argv[1]);
		return 2;
	}

	int c;
	int cnt = 0;

	while ((c = fgetc(f)) != EOF)
	{
		if (c == *argv[2])
			cnt++;
	}
	printf("%c -> %d adet var", *argv[2], cnt);

	fclose(f);
}

-------------------------------------------------------------------------------------------------



int main(int argc, char **argv)
{


	if (argc != 2)
	{
		fprintf(stderr, "kullanim hsay - dosya ismi\n");
		return 1;
	}

	FILE* f = fopen(argv[1],"r");
	if (!f)
	{
		fprintf(stderr, "%s dosya acilma hatasi", argv[1]);
		return 2;
	}

	int count[26] = {0};
	int c;

	while ((c = fgetc(f)) != EOF)
	{
		if (isalpha(c))
		{
			count[toupper(c) - 'A']++;
		}
	}

	fclose(f);

	for (size_t i = 0; i < 26; ++i)
	{
		printf("%c ==> %d adet\n", i + 'A', count[i]);
	}


}


-------------------------------------------------------------------------------------------------

typedef struct {
	int cnt;
	int ch;
}Data;

int scmp(const void* vp1, const void* vp2)
{
	return ((const Data*)vp2)->cnt - ((const Data*)vp1)->cnt;
}

int main(int argc, char **argv)
{
	FILE* f = fopen(argv[1], "r");
	Data ar[26];
	int c;

	for (int i = 0; i < 26; ++i)
	{
		ar[i].ch = 'A' + i;
		ar[i].cnt = 0;
	}


	if (argc != 2)
	{
		fprintf(stderr, "kullanim yaz - dosya ismi\n");
		return 1;
	}

	if (!f)
	{
		fprintf(stderr, "%s dosya acilma hatasi", argv[1]);
		return 2;
	}

	while ((c = fgetc(f)) != EOF)
	{
		if (isalpha(c))
		{
			++ar[toupper(c) - 'A'].cnt;
		}
	}

	fclose(f);

	qsort(ar, 26, sizeof(*ar), &scmp);
	for (int i = 0; i < 26; ++i)
	{
		printf("%c %d\n", ar[i].ch, ar[i].cnt);
	}
}


-------------------------------------------------------------------------------------------------------------


SIK YAPILAN HATA
fgetc nin geri dönüş değerini char türden değişkende tutması

char c ;
c = fgetc(f);
eğer -1 dönerse  char türden değişkene atanacak ama yüksek anlamlı byteları da gidecek tabi.
bu durumda EOF ile 255 arasında bir fark kalmayacak.

Yani başarısız olunca bunu ayırt edemeiyoruz.bunu kesinlikle int türden değişkende saklamalıyız.

YANİ:

int türden olunca aşağıdaki gibi olan sayı
0000 0000 1111 1111

char türden olunca
1111 1111 
oluyor
Burasıda -1

========================================================================================
========================================================================================
========================================================================================

FPUTC
buda dosyaya yazma fonksiyonu.
putchar ın karşılığı.

int fputc(int c,FILE *);

c = dosyaya yazılacak karakter
FILE * = Hangi dosyaya yazılacağının bilgisi

geri dönüş değeri int = başarısız ise EOF yani -1, başarılı ise dosyaya yazılan byte ın değeri 


ÖR:

int main()
{

	FILE* f = fopen("deneme.txt", "w");
	if (!f)
	{
		fprintf(stderr, "Dosya yazma hatasi\n");
		return 1;
	}

	for (int i = 0; i < 26; ++i)
	{
		fputc('A' + i,f);
	}

	fputc('\n', f);
	for (int i = 0; i < 26; ++i)
	{
		fputc('a' + i, f);
	}

	fputc('\n', f);
	for (int i = 0; i < 10; ++i)
	{
		fputc('0' + i, f);
	}

	fclose(f);

}

------------------------------------------------------------------------------------------

int main()
{

	FILE* f = fopen("deneme.txt", "w");
	if (!f)
	{
		fprintf(stderr, "Dosya yazma hatasi\n");
		return 1;
	}

	for (int i = 0; i < 128; ++i)
	{
		if (isprint(i))
		{
			fputc(i,f);
		}
	}

	fclose(f);
}

------------------------------------------------------------------------------------------

int get_random_char(void)
{
	int c;
	while (!isalpha(c = rand() % 128))
		;
	return c;
}

int main(int argc, char **argv)
{
	if (argc != 5)
	{
		fprintf(stderr, "kullanim : crf - dosya ismi - satir sayisi - min satir uzunlugu - max satir uzunlugu\n");
		return 1;
	}

	FILE* f = fopen(argv[1], "w");
	if (!f)
	{
		fprintf(stderr, "%s dosyasi olusturulamadi\n", argv[1]);
		return 2;
	}

	int nlines = atoi(argv[2]);
	int max_line_len = atoi(argv[3]);
	int min_line_len = atoi(argv[4]);

	randomize();

	for (int i = 0; i < nlines; ++i)
	{
		int random_len = rand() % (max_line_len - min_line_len + 1) + min_line_len;

		while(random_len--)
		{
			fputc(get_random_char(),f);
		}

		fputc('\n', f);
	}

	fclose(f);


}


--------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------


BINARY MODE

defaultta dosyalar text modda açılıyor.
Binary file demek aslında hatalı.Tüm dosyalar aslında binary.
Burada kastedilen text dosyası olmadığıdır.

mesela mp3 , jpeg, png...

Dosyanın text modunda açılması, dosya text bilgisi tutuyor ve ben text ile ilgili işlemler yapacağım demek.

Binary modda açılması demek, dosya zaten text değil, dolayısı ile binary dosya ile ilgili işlemler yapacağım, ya da 
dosyanın ne olduğu belli değil. Burada binary mod kullanılıyor.

UNIX / LINUX kökenli sistemlerde fark yok

Windows OS lerde fark var.
------------------------------------------------------------------------------------------------------

AŞIRI ÖNEMLİ !!!!!!!!!!!!!!!!!!!!!!!!!!!
WINDOWSTA DOSYAYI TEXT MODUNDA YAZMA AMAÇLI AÇARSAK
DOSYAYA NEWLINE KARAKTERINI YAZDIĞIMIZDA DOSYAYA 1 BYTE YERINE 2 BYTE YAZILIR \13 \10 YAZILIR.
FGETC ILE OKUNDUĞUNDA DAHA KÖTÜ, SADECE \10 LAR GÖRÜLECEK
AMA BUNU DAHA SONRA BINARY MODE ILE R MODDA AÇARSAK \13 \10 LARIN IKISINIDE GÖRÜRÜZ.


DOSYAYI BINARY MODUNDA YAZMA AMAÇLI AÇARSAK
DOSYAYA NEWLINE KARAKTERINI YAZDIĞIMIZDA DOSYAYA 1 BYTE YAZILR \10 YAZILIR.
ÖRNEĞİ VAR AŞAĞIDA
BİRDE 26 nolu byte konusu var ctrl-z yani

------------------------------------------------------------------------------------------------------

2 byte yazmasının sebebi tarihsel
daktiloda satırbaşı 2 harekette yapılıyormuş,
birincisi aşağı iniyor ikincisi satırın başına alıyor.	
biri carriage return diğeri newline character.

-------------------
ör
int main(int argc, char **argv)
{
	FILE* f = fopen("asd.txt", "w");
	// hata kontrol

	for (int i = 0; i < 100; ++i)
	{
		fputc('\n', f);
	}
	fclose(f);
	//yaratılan dosya özelliklerine gir. 200 byte görülür.
}

----------------

ör

int main(int argc, char **argv)
{
	FILE* f = fopen("asd2.txt", "wb");
	// hata kontrol

	for (int i = 0; i < 100; ++i)
	{
		fputc('\n', f);
	}
	fclose(f);
	//yaratılan dosya özelliklerine gir. 100 byte görülür.
}

--------------------
ÖNEMLİ !!!!!

int main(int argc, char **argv)
{
	FILE* f = fopen("asd.txt", "r");
	// hata kontrol

	int c;

	while ((c = fgetc(f)) != EOF)
		printf("%d ", c);
	fclose(f);
	//Dosyada /13 /10 lar var ama burada sadece 10 görünüyor.çünkü text modunda açtık ve fgetc bunu tek bir byte olarak görecek.
	//Binary modda açılsaydı hem 13 hemde 10 u görecektik.
}

-----------------------------------------------
-----------------------------------------------
-----------------------------------------------

ÇOOK ÖNEMLİ !!!!!!!!!!!!!

ESKIDEN DOSYA SONUNU BELIRTEN TAMSAYI DEĞERI VARDI VE BU GELENEK DEVAM EDIYOR.
BU CTRL-Z KARAKTERI. VE ASCI KODU 26 DIR.

DOSYA TEXT MODDA AÇILIRSA, BINARY DOSYADAKI BYTELARDAN BIRI 26 ISE, OKUMA YAPAN FONKSIYON BUNU DOSYA SONU OLARAK GÖRECEK
VE OKUMA IŞLEMI SONLANACAK.

---------------------------------

ÖR

int main(int argc, char **argv)
{
	FILE* f = fopen("asd3.txt", "w");
	// hata kontrol

	int c;

	for (int i = 0; i < 100; ++i)
	{
		fputc('A', f);
	}

	fputc(26, f);

	for (int i = 0; i < 100; ++i)
	{
		fputc('Z', f);
	}

	fclose(f);
}

ŞİMDİ OKUTALIM


int main(int argc, char **argv)
{
	FILE* f = fopen("asd3.txt", "r");
	// hata kontrol

	int c;

	while ((c = fgetc(f)) != EOF)
		printf("%d -> %c    ", c,c); // Z ler görülmedi. çünkü 26. karakter ctrl-z karakteri.

	fclose(f);
}



*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "nutility.h"


int main(int argc, char **argv)
{
	printf("%c", get_random_char());
}