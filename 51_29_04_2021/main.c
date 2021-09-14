
/*
TEKRAR YAPILDI
text modda new line \13 \10 yazıyor
binaryde \10

text modda \26 görürse dosya sonu gelmiş gibi algılıyor.
binary modda böyle birşey yok.

----------------------------------------------------------------------------
----------------------------------------------------------------------------
----------------------------------------------------------------------------

FORMATTED INPUT / OUTPUT
------------------------

Formatsız okuma yazma 
bellekteki byteları olduğu gibi almak
bellekteki byteları olduğu gibi göndermek

formatlı okuma yazma
bellekteki byteları, veriyi ifade eden karakter kodlarına dönüştürmek ve bu karakter kodlarını
almak yada göndermek.

mesela
12312431 sayısını dosyaya nasıl yazabilirim 
ör:
48 49 ... karakter kodları yani.

==========================================================================================
==========================================================================================

FPRINTF
int fprintf(FILE *, const char *,...) ; variadic  ------------> dosyaya yazıyor
int sprintf(char *buf, const char *,...) ; variadic ----------> memoryye yazıyor
int printf(const char *,...) ; variadic ----------------------> Std outputa yazdırıyor

SSCANF
int fscanf(FILE *, const char *,...) ; variadic  ------------> file dan aldıklarını değişkenlere yazıyor
int sscanf(char *buf, const char *,...) ; variadic ----------> bir diziden dan aldıklarını değişkenlere yazıyor
int scanf(const char *,...) ; variadic ----------------------> std inputtan aldıklarını değişkenlere atıyor.

Geri dönüş değeri başarılı okunan eleman sayısı. 
Eğer okunacak karakter kalmamışsa EOF(-1) döndürür.

veri 1 2 3   ise fscanf %d %d %d   nin geri dönüş değeri 3 tür 
veri 1 2 ali   ise fscanf %d %d %d   nin geri dönüş değeri 2 dir 
veri 1 veli ali   ise fscanf %d %d %d   nin geri dönüş değeri 1 dir 
veri hasan veli ali   ise fscanf %d %d %d   nin geri dönüş değeri 0 dır 
file sonu ise geri dönüş değeri EOF

tabi file pointer EOF a kadar ilerliyor ama okuyamazsa bir değeri onu okuyana kadar kalıyor o bytta.
Yani okunmamış byte lar dosyanın bufferında kalmaya devam ediyor.
Bunu test ettiğim örnek var.primes_karisik.txt geçen örnek bunla alakalı.

=======================================================================================
BAYA ÖRNEK YAPILACAK BU DERS

int main()
{

	int x = 30;
	double dval = 45.1234;
	char str[100] = "tugrul kekec";

	FILE* f = fopen("deneme.txt", "a");
	if (!f)
	{
		printf("olusturulamadi\n");
		return 1;
	}

	for (int i = 0; i < 100; ++i)
	{
		fprintf(f, "%d\n",i);
	}

	fclose(f);

}

----------------------------------------------

//komutsatırından asalyaz isimli programı oluştur.
// asalyaz asal10000.txt 10000
// asalyaz primes.txt 10000

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		fprintf(stderr, "dogru kullanim - asalyaz - filename - count\n");
		return 1;
	}

	FILE *f = fopen(argv[1],"w");
	if (!f)
	{
		fprintf(stderr, "dosya acilamadi\n");
		return 2;
	}

	int count = atoi(argv[2]);
	int prime_count = 0;
	int val = 2;

	while (prime_count < count)
	{
		if (isprime(val))
		{
			fprintf(f, "%d ", val);
			++prime_count;
		}
		++val;
	}

	fclose(f);

}

--------------------------------------------
//notepad yanyana karakterleri fazla görünce sapıtıyor.\n ile alta geçmek lazım.

int main()
{
	//asalsayısı ve dosya adı kullanıcıdan da alınabilir.

	FILE *f = fopen("primes.txt","w");
	if (!f)
	{
		fprintf(stderr, "dosya acilamadi\n");
		return 2;
	}

	int prime_count = 0;
	int val = 2;

	while (prime_count < 1000000)
	{
		if (isprime(val))
		{
			if (prime_count && prime_count % 10 == 0)
				fprintf(f, "\n");
			fprintf(f, "%-8d ", val);
			++prime_count;
		}
		++val;
	}

	fclose(f);
}

----------------------------------------------------------------------------------------

int main()
{
	FILE* f = fopen("kayit.txt", "w");
	if (!f)
	{
		fprintf(stderr, "dosya olusturulamadi\n");
		return 1;
	}

	randomize();
	for (int i = 0; i < 10000; ++i)
	{
		//önceden yazdığımız fonksiyonlar kullnılıyor rname rsurname ..
		fprintf(f, "%-10d %-15s %-20s %-20s %-15d\n", rand(), rname(),rsurname(),rtown(),rand() % 1001);
;	}

	fclose(f);
}

---------------------------------------------------------

//Asallar arası 2 fark varsa yazdırıyor.
int main()
{
	FILE* f = fopen("primes.txt", "r");
	if (!f)
	{
		fprintf(stderr, "dosya acilamadi\n");
		return 1;
	}

	int x,y;
	while (fscanf(f, "%d%d", &x,&y) != EOF)
	{
		if (y - x == 2) 
		{
			printf("%d  %d\n", x, y);
		}
	}

	fclose(f);
}

--------------------------------------------------------------------------------

file dan okuma yapıp notu belirli bir rakam olanlar yazdırılıyor.
istenirse bu hangi ilden olanlar şeklinde de yapılır. strcmp ile kıyaslanır.

int main()
{
	int no;
	char name[40];
	char surname[40];
	char town[40];
	int grade;


	FILE* f = fopen("kayit.txt", "r");
	if (!f)
	{
		fprintf(stderr, "dosya acilamadi\n");
		return 1;
	}

	int ival;
	printf("notu kac olanlar yazdirilsin\n");
	(void)scanf("%d", &ival);

	while (fscanf(f, "%d%s%s%s%d", &no,name,surname,town,&grade) != EOF)
	{
		if(grade == ival) // strcmp() ile kıyaslama yapılabilirdi başka bir örnekte.Yazmıyorum ben
			printf("%-8d %-18s %-20s %-20s %d\n", no, name, surname, town, grade);
	}

	fclose(f);
}


--------------------------------------------------------------------------------------


int main()
{

	FILE* f = fopen("primes_karisik.txt", "r");
	if (!f)
	{
		fprintf(stderr, "Dosya acilamadi\n");
		return 1;
	}

	int x;
	char buf[100];
	while (1)
	{
		int retval = fscanf(f, "%d", &x);
		if (retval == EOF)
			break;
		else if (!retval)
		{
			(void)fscanf(f, "%s", buf);
			printf("\n%s gecerli bir tamsayi degil\n", buf);
			(void)getchar();
		}
		else
			printf("%d ", x);
	}
}


---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------

BU ÖRNEK ÇOK İYİ

//örnek, herbir ile ait dosya açmak ve o ilden katılanların notlarını yazdıran program.kayittaki iller bene sınırlı mesela
// her bir ile ait txt file aç ilgili kayıtı oraya koy.

const char* const ptowns[] = {
		"Istanbul","Ankara","Izmir","Antalya","Mugla","Aydin","Denizli","Canakkale","Kars",
		"Ardahan"
};

int main()
{
	FILE* fs = fopen("kayit.txt", "r"); // kayıt doyasında kimler hangi illerde bu bilgi var.r modda açıldı
	if (!fs)
	{
		printf("kayit.txt dosyasi acilamadi\n");
		return 1;
	}


	FILE* fa[asize(ptowns)]; //burada elemanları il sayısı kadar handle bir array var.

	char filename[40];
	for (size_t i = 0; i < asize(fa); ++i)		// bu handle dizisindeki tüm elemanlara fopen ile açılan file adresleri atandı.
	{											// hepsi w modda şuanda yazmaya hazır bekliyor.
		sprintf(filename, "%s.txt",ptowns[i]);
		fa[i] = fopen(filename, "w");
		if (!fa[i])
		{
			fprintf(stderr, "%s Dosya acilamadi\n",filename);
			return 2;
		}
	}


	int no;
	char name[40];
	char surname[40];
	char town[40];
	int grade;

	while (fscanf(fs, "%d%s%s%s%d", &no, name, surname, town, &grade) != EOF) // burada kayıt dosyasındaki değerleri değişkenlere atıyorz.
	{
		size_t i = 0;
		while (i < asize(fa) && strcmp(town, ptowns[i])) // !strcmp 0 dan farklı , strcmp eğer eşit ise 0 döndürür
			++i;											// burada eşit değilseye bakılıyor.Eşit değilse döngü dönecek.
														// burada fscanf ten bulunan town değerini const ptowns arraydeki
														// herbir eleman ile kıyaslayıp indisini bulacağız.bulunca çıkacak zaten.

		if (i == asize(fa))			// bu durum olursa sıkıntı var.eşit olmamalı zaten
		{
			fprintf(stderr, "bir hata var\n");
			return 1;
		}

		fprintf(fa[i], "%-8d %-18s %-20s %-20s %d\n", no, name, surname, town, grade); // yukarıda açılan handle lara
	}


	_fcloseall();
}

---------------------------------------------------------------------------------------------------------------------


DOSYA KOPYALAMA KODU
--------------------

int main(int argc, char **argv)
{

	// DOSYA KOPYALAMA
	//kopyala ali.exe veli.exe

	FILE* fs, * fd;
	int c;
	int byte_count = 0;

	if (argc != 3)
	{
		fprintf(stderr, "kullanim - kopyala ali.exe veli.exe\n");
		return 1;
	}

	if ((fs = fopen(argv[1], "rb")) == NULL)
	{
		fprintf(stderr,"dosya acilamadi\n");
		return 2;
	}

	if ((fd = fopen(argv[2], "wb")) == NULL)
	{
		fprintf(stderr,"%s dosya olusturulamadi",argv[2]);
		fclose(fs);
		return 3;
	}

	while ((c = fgetc(fs)) != EOF)
	{
		fputc(c, fd);
		++byte_count;
	}

	fclose(fs);
	fclose(fd);

	printf("%d bytelik %s dosyasinin %s isimli dosya kopyasi olusturuldu", byte_count, argv[1], argv[2]);

}

---------------------------------------------------------------------------------------------------------------------

BİR DOSYAYI PARÇALARA BÖLECEĞİZ VE TEKRAR BİRLEŞTİRECEĞİZ.


//DOSYAYI PARÇALARA BÖLME KODU.	bol.exe
//SONRADA O PARÇALARDAN DOSYAYI BİRLEŞTİRME KODU. birlestir.exe


//bu kısım bölme kodunu içeriyor.
int main(int argc, char **argv)
{
	char source_filename[40];
	char dest_filename[40];
	FILE* fs;
	FILE* fd;
	int c;
	int chunk;
	int file_count = 0;
	int byte_count = 0;

	if (argc != 3)
	{
		printf("dosya adini girin\n");
		(void)scanf("%s", source_filename);
		printf("chunk size bilgisini girin\n");
		(void)scanf("%d", &chunk);
	}
	else
	{
		strcpy(source_filename, argv[1]);
		chunk = atoi(argv[2]);
	}

	fs = fopen(source_filename, "rb");
	if (!fs)
	{
		fprintf(stderr, "dosya acilamadi\n");
		return 1;
	}

	fd = NULL;
	while ((c = fgetc(fs)) != EOF)
	{
		if (!fd)
		{
			sprintf(dest_filename, "parca%03d.par", file_count + 1);
			fd = fopen(dest_filename, "wb");
			if (!fd)
			{
				fprintf(stderr, "dosya acma hatasi\n");
				return 2;
			}

			++file_count;
		}

		fputc(c, fd);
		++byte_count;

		if (byte_count % chunk == 0)
		{
			fclose(fd);
			fd = NULL;
		}
	}

	if (fd)
	{
		fclose(fd);
	}
	fclose(fs);

	printf("%d byte lik %s dosyasi %d byte lik %d parcaya bolundu\n", byte_count, source_filename, chunk, file_count);
}


--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------

//bu kısımda birleştirme kısmını içeriyor.

ÖNCE 2 ADET YENİ FONKSİYON.

1 - Bu ismini aldığı dosyayı siliyor.
başarılı ise ise 0 
başarısız ise non-0 değer

int remove(const char *filename);	


2 - 2 adet yazı alıyor.
	dosyayı rename ediyor.
int rename(const char *old_filename, const char *new_filename)
başarılı ise ise 0
başarısız ise non-0 değer

--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------

ÖR:

//silme örneği
const char* const ptowns[] = {
	"Istanbul","Ankara","Izmir","Antalya","Mugla","Aydin","Denizli","Canakkale","Kars",
	"Ardahan"
};

int main(int argc, char **argv)
{
	char buffer[100];

	for (size_t i = 0; i < asize(ptowns); ++i)
	{
		sprintf(buffer, "%s.txt", ptowns[i]);
		if(remove(buffer))
		{
			printf("%s isimli dosya silinemedi",ptowns[i]);
			return 1;
		}
		printf("Dosya silindi\n");
	}
}

--------------------------------------------------------------------

//isim değiştirme örneği


int main()
{
	if (rename("primes_karisik.txt", "primes_karisik111.txt"))
		printf("isim degistirilemedi\n");
	else
		printf("isim degistirildi\n");

}

------------------------------------------------------------------------------------



//DOSYAYI PARÇALARA BÖLME KODU.	bol.exe
//SONRADA O PARÇALARDAN DOSYAYI BİRLEŞTİRME KODU. birlestir.exe

//birlestir veli.exe
int main(int argc,char **argv)
{
	char source_filename[40];
	char dest_filename[40];
	FILE* fs;
	FILE* fd;
	int c;
	int chunk;
	int file_count = 0;
	int byte_count = 0;

	if (argc != 2)
	{
		printf("dosya adini girin\n");
		(void)scanf("%s", dest_filename);
	}
	else
	{
		strcpy(dest_filename, argv[1]);
	}

	fd = fopen(dest_filename, "wb");

	if (!fd)
	{
		fprintf(stderr, "%s dosyasi olusturulamadi\n",dest_filename);
		return 1;
	}

	// tüm parçaları açmaya çalışacak
	// mesela 007 ok, 008 e geldi açamadı ise demekki yok diye düşünüp işlemi bitireceğiz.
	while (1)
	{
		sprintf(source_filename, "parca%03d.par", file_count + 1);
		if ((fs = fopen(source_filename, "rb")) == NULL)
			break;	// dosya açılamazsa çıkacak döngüden,dosya yokmuş gbi davranacak

		++file_count;
		while ((c = fgetc(fs)) != EOF)
		{
			fputc(c, fd);
			++byte_count;
		}
		fclose(fs);
	}

	fclose(fd);

	//eski parçalı dosyaları siliyoruz
	for (int i = 0; i < file_count; ++i)
	{
		sprintf(source_filename, "parca%03d.par", i + 1);
		if (remove(source_filename))
		{
			fprintf(stderr, "%s dosyasi silinemedi\n", source_filename);
			return 2;
		}
	}
}


--------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------


BİR ŞİFRELEME PROGRAMI YAZACAĞIZ.

bir sayı alacağız ve bu sayıyı seed değeri srand a vereceğiz.
ali.exe yi kopyalayacağız.
kopya dosyaya alinin değerini yazmak yerine bunun bitlerinin xor lanmış değerlerini yaz.bunuda rand ile xorlayacağız.
her iki dosyayıda kapat
ali.exe yi sil
diğer dosyanın ismini ali.exe yap.

--------------------------------------------------------------------------------------------

ÖNEMLİ BİR FONKSİYON GÖRECEĞİZ BUNDAN ÖNCE

BU FONKSİYON OS ÜZERİNDE YAZMA AMAÇLI BİR DOSYA YARATTIĞIMDA AYNI İSİMLİ DİĞER DOSYANIN ÜZERİNE YAZMA İHTİMALİNİ ENGELLİYOR.
YANİ BU FONKSİYON OS ÜZERİNDE OLMAYAN BİR DOSYA İSMİNİ YARATIYOR.
UNIQUE FILE NAME GENERATOR.

BU STDIO DA TMPNAM DİYE GEÇİYOR.

char *tmpnam(char *pbuf);

eğer fonksiyona adres gönderirsek değeri ona yazar
NULL ptr gönderirsek bu sefer return eder.Bu static ömürlü bir dizi verecek.


int main()
{
	char tempname[L_tmpnam]; // macro taşmayacak bir size veriyor.
	tmpnam(tempname); //puts(tmpnam(NULL)); buda olurdu 

	puts(tempname); // unique ismi yazdırıyor.
}

------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------

int main(int argc, char **argv)
{
	FILE* fd, * fs;

	if (argc != 3)
	{
		fprintf(stderr, "dogru kullanim <encr> <program.exe> <anahtar>");
		return 1;
	}

	if ((fs = fopen(argv[1], "rb")) == NULL)
	{
		fprintf(stderr, "%s dosya acilamadi\n",argv[1]);
		return 2;
	}

	char temp_filename[L_tmpnam];
	tmpnam(temp_filename);

	//hiçbir dosyayı ezmeyecek şekilde dosyayı açıyoruz.

	if ((fd = fopen(temp_filename, "wb")) == NULL)
	{
		fprintf(stderr, "Dosya acilamadi\n");
		return 3;
	}

	//BURADAN SONRASI BAYA ÖNEMLİ
	int seed = atoi(argv[2]);
	srand((unsigned int)seed);

	int c;

	while ((c = fgetc(fs)) != EOF)
	{
		fputc(c ^ rand(), fd);
	}

	fclose(fs);
	fclose(fd);

	if (remove(argv[1]))
	{
		fprintf(stderr, "dosya silinemedi\n");
		return 4;
	}

	if (rename(temp_filename, argv[1]))
	{
		fprintf(stderr, "Dosya isim degisikligi yapilamadi\n");
		return 5;
	}

	//.\encr.exe .\say.exe 123456
	// .\say.exe		artık çalışmayacak.

	// decrypt ediyorum.
	// .\encr.exe .\say.exe 123456
	// .\say.exe artık çalışıyor.

}















*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "nutility.h"
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv)
{

	/*
		ÖDEV
		----
		1 - FİLE İÇERİSİNDEKİ YAZILARI SIRALAYAN BİR KOD. DMM KULLANILACAK
		2 - ARA ALİ.TXT DENİZ  -> ALİ İÇİNDE DENİZ GEÇEN SATIRLARI YAZACAK
		MESELA [345]  -> DENİZ İŞYERİNDE ÇALIŞIYOR 
		SATIR NO VE DENİZ GEÇEN YERDEN SATIR SONUNA KADAR OLAN YER.
	

		-------------------------------------------------------------------
		HAFTAYA
		DOSYADAN SATIR SATIR OKUMA ---> GETS
		BİR SATIR YAZMA ---> FPUTS
		FORMATSIZ OKUMA VE YAZMA -->  FREAD FWRITE
		DOSYA KONUM GÖSTERİCİSİ FONKSİYONLARI --> REWIND FSEEK FTELL FSETPOS FGETPOS
		HATA KONTROL İŞLEMLERİ --> FEOF FERROR CLEARERR


	*/


}