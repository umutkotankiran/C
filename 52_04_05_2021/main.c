/*

	ÇOOK ÖNEMLİ!!!!!!!!!!!!!
	------------------------
	1- FREAD/FWRITE
	2- FPUTS/FGETS
	3- SPRINTF/FPRINTF
	4- FPUTC/FGETC

	YUKARIDA YAZILAN FONKSİYONLARIN BİLDİRİMLERİNİ VE KISACA AÇIKLAMALARINI YAZIYORUM ÇÜNKÜ HATA FAIL DURUMDA
	EOF DÖNDÜRENDE VAR NULL DÖNDÜRENDE VAR.

	================================================================

	1- FREAD/FWRITE
	DOSYALARDAN FORMATSIZ OKUMA VE DOSYALARA FORMATSIZ YAZMA YAPILIYOR.
	EN ÇOK KULLANILANLARDAN BİRİ GRUP.

	A- size_t fread(void *vpbuf,size_t sz, size_t n,FILE *f); 

	f = BU HANDLE DAN DATALAR OKUNUR
	vpbuf = BURADAKİ DEĞERE YAZILIR
	sz = BİR ELEMAN BOYUTU
	n = KAÇ ELEMAN OLDUĞU BİLGİSİ.
	RETURN DEĞERİ KAÇ DEĞERİ OKUYABİLDİĞİ.Okuyamazsa 0

	B- size_t write(const void *vpbuf,size_t sz, size_t n,FILE *f);

	vpbuf = BURADAKİ DEĞERDEN DATALAR OKUNUR
	f = BU HANDLE A YAZILIR
	sz = BİR ELEMAN BOYUTU
	n = KAÇ ELEMAN OLDUĞU BİLGİSİ.
	RETURN DEĞERİ KAÇ DEĞERİ YAZABİLDİĞİ.Yazamazsa 0

	================================================================

	2- FPUTS/FGETS
	DOSYALARA LİNE YAZMAK VEYA OKUMAK İÇİN KULLANILIR.

	A- char* fgets(char *buffer,int n,FILE *f);,

	return değeri buradaki adres olan buffer değeridir. Hata olursa NULL pointer döner
	\n karakterini line by line gittiği için otomotik koyar.zaten satır sonunda \n var.Bunuda alıyor yani.
	f = OKUMA YAPILAN HANDLE
	n = KAC ADET OKUMA YAPILACAĞI
	buffer = BU OKUMANIN YAZILACAĞI DİZİ.

	NOT: ÇOK ÖNEMLİ !!!!!!!
	EĞER BUFFER SİZE DAN DAHA KÜÇÜK BİR KARAKTER OKURSA, DATAYI OKUR BUFFERA YAZAR VE SONUNA \n DEĞİL \0 KOYAR.
	KISACA, \n KARAKTERİNE KADAR OKURSA BUNUDA ALIR, AMA \n KARAKTERİ YOKSA VE BUFFER DOLDUYSA SONA \0 KOYAR.



	B- int fputs(char *buffer,FILE *f);
	return değeri başarılı ise non-negative değer. Hata durumunda EOF
	buffer = buradaki dizileri alır
	f = buradaki handle a line olarak girer.

	==========================================================================

	3- SPRINTF/FPRINTF - SSCANF/FSCANF

	FORMATLI OKUMA YAZMA
	BELLEKTEKI BYTELARI, VERIYI IFADE EDEN KARAKTER KODLARINA DÖNÜŞTÜRMEK VE BU KARAKTER KODLARINI
	ALMAK YADA GÖNDERMEK.

	A- PRINTF
	int fprintf(FILE *, const char *,...) ; variadic  ------------> dosyaya yazıyor
	int sprintf(char *buf, const char *,...) ; variadic ----------> memoryye yazıyor
	int printf(const char *,...) ; variadic ----------------------> Std outputa yazdırıyor

	return değer yazdırılan karakter sayısı.
	BURASI ASLINDA BİR YAZIYI ELDE ETMEK İÇİN KULANILIYOR.

	B- SCANF
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

	==========================================================================

	4- FPUTC/FGETC

	A-int fputc(int c,FILE *);

	buda dosyaya yazma fonksiyonu.
	geri dönüş değeri başarısız ise EOF yani -1, başarılı ise dosyaya yazılan byte ın değeri.
	
	B-int fgetc(FILE *);
	getchar fonksiyonuna benziyor. getchar standart inputtan alıyordu, bu ise dosyadan karakter alıyor.
	Geri dönüş değeri 0 ile 255 aralığıunda olacak.
	başarısız olursa int türden EOF yani -1 döndürecek.


	==========================================================================
	==========================================================================
	==========================================================================
	==========================================================================
	==========================================================================
	==========================================================================
	==========================================================================
	==========================================================================


	DERS BURADAN BAŞLIYOR.
	----------------------

	char* fgets(char *buffer,int n,FILE *f);
	return değeri okuduğu/set ettiği dizinin adresi geri döndürüyor.yani buffer return eder.
	hata durumunda NULL POINTER döner
	buffer = file dan okunanlar \n dahil buraya transfer ediliyor
	n = okunacak byteların boyutu
	YANİ HANDLE DAN BİR SATIR BUFFERA EKLEYECEK
	\n karakterinide dosyanın bufferından extract etti.


	int fputs(char *buffer,FILE *f);
	buda fgets in tam tersi.

	
	----------------------------------------------------------------------------
	----------------------------------------------------------------------------

	ÖR:

	int main()
	{
		char buffer[BUFFER_SIZE];
		FILE* f = fopen("kayit.txt", "r");

		if (!f)
		{
			fprintf(stderr, "dosya acma hatasi\n");
			exit(EXIT_FAILURE); //yada return 1;
		}

		while (fgets(buffer, BUFFER_SIZE, f) != NULL) // buffer 9 olsaydı 9 ar 9 ar giderdi taki new line a kadar
		{												// sonra bir alt satıra girer.
			printf("%s", buffer); // dikkat fgets \n karakterini de dosyanın bufferından extract ediyor.
			_getch();				// strrev ile ters te çevirebilir.
		}
		fclose(f);
	}

	------------------------------------------------------------------------------------
	------------------------------------------------------------------------------------

	ÖDEV ÇÖZÜMÜ.
	fsort ali.txt 

	int scmp(const void* vp1, const void* vp2)
{
	return strcmp(*(char**)vp1, *(char**)vp2);
}


#define		BUFFER_SIZE		1000

// fsort necati
int main(int argc, char **argv)
{
	char buffer[BUFFER_SIZE];
	if (argc != 2)
	{
		fprintf(stderr, "usage: <fsort><filename>\n");
		return 1;
	}

	FILE* f = fopen(argv[1], "r");
	if (!f)
	{
		fprintf(stderr, "%s dosya acma hatasi\n",argv[1]);
		return 2;
	}

	char** pd = NULL;
	int line_count = 0;

	while(fgets(buffer,BUFFER_SIZE,f))
	{
		pd = (char**)realloc(pd,(line_count + 1) * sizeof(char *));
		if (!pd)
		{
			fprintf(stderr, "Memory Hatasi\n");
			return 3;
		}

		pd[line_count++] = _strdup(buffer);
	}

	qsort(pd, line_count, sizeof(char*), &scmp);
	for (int i = 0; i < line_count; ++i)
	{
		printf("%s", pd[i]);
	}

	for (int i = 0; i < line_count; ++i)
	{
		free(pd[i]);
	}

	free(pd);

}

------------------------------------------------------

2. dosyadan okuma yöntemi fscanf ile

int main()
{
	FILE* f = fopen("kayit.txt", "r");
	if (!f)
	{
		fprintf(stderr, "Dosya acilamadi\n");
		return 1;
	}

	char str[100];
	int count = 0;
	while (fscanf(f, "%s", str) != EOF) // fgets ile yaparsak != NULL dememiz lazım.
	{
		printf("%-5d %s\n", count++, str);
		_getch();
	}
	fclose(f);
}

----------------------------------------------------------
----------------------------------------------------------

FPUTS

fputs("Bugun hava cok guzel\n",f); \n var burada

EN son hepsini yazacağım.


===================================================================================
===================================================================================
===================================================================================


DOSYALARDAN FORMATSIZ OKUMA VE FORMATSIZ YAZMA İŞLEMLERİ.
---------------------------------------------------------
UNFORMATTED INPUT OUTPUT OPERATION

Formatsız yazma demek bir verinin bellekteki bitlerine bakıyor ve bunları dosyaya yazmak demek.

bellekteki byteları oldukları gibi dosyaya transfer etmek 
dosyadaki byteları oldukları gibi belleğe transfer etmek
En önemlileri bunlardiyor hoca.
Formatsız okuma yazma


size_t fread(void *vpbuf,size_t sz, size_t n,FILE *f);

sz = bu kadar bytelık bloklardan
n = bu kadar tanesini
f = buradan okuyup
vpbuf = buraya yazıyor.
Return değeri başarılı okuma sayısıdır.


size_t fwrite(const void *vpbuf,size_t sz, size_t n,FILE *f);
tam tersini yapıyor yukarıdakinin.
sz = bu kadar bytelık bloklardan
n = bu kadar tanesini
vpbuf = buradan okuyup.
f = bu kısma yazıyor.
Return değeri yazdığı blok sayısıdır.

----------------------------------------------------------------------

ÖR:

//bir dosyaya formatsız olarak ilk n asal sayının yazdırılması
int main()
{
	char filename[100];
	int n;
	printf("dosya adi\n");
	scanf("%s", filename);
	printf("kac asal sayi yazilsin\n");
	scanf("%d", &n);

	printf("%zu bytelik %s dosyasi olusacaktir\n", sizeof(int) * n, filename);

	FILE* f = fopen(filename, "wb");
	if (!f)
	{
		fprintf(stderr,"%s dosyasi olusturulamadi\n",filename);
	}

	int prime_count = 0;
	int x = 2;
	while (prime_count < n)
	{
		if (isprime(x))
		{
			fwrite(&x,sizeof x,1,f);
			prime_count++;
		}
		x++;
	}

	fclose(f);

}

--------------------------------------------------------------

ÖR:

int main()
{
	int n;
	char file_name[100];

	printf("dosya ismi ne olsun\n");
	scanf("%s", file_name);
	printf("Kac employee yazilsin\n");
	scanf("%d", &n);

	printf("%zu byte lik %s dosyasi olusacak\n", n * sizeof(Employee), file_name);

	FILE* f = fopen(file_name, "wb");
	if (!f)
	{
		fprintf(stderr, "%s dosyasi olusturulamadi\n", file_name);
	}

	Employee emp;

	for (int i = 0; i < n; i++)
	{
		set_employee_random(&emp);
		fwrite(&emp,sizeof emp,1,f);
	}

	fclose(f);

}

BURADAN SONRA OKUYACAK

int main()
{
	FILE* f = fopen("asal1000.dat", "rb");
	if (!f)
	{
		fprintf(stderr, "dosyasi olusturulamadi\n");
		return 1;
	}

	int x;
	while (fread(&x, sizeof x, 1, f)) // geri dönüş değeri okuduğu miktar. 0 olunca çıkar
	{									// bunu 1 er 1 er okumak zorunda da değiliz.
		printf("%d ", x);
		_getch();
	}
	fclose(f);
}

----------------------

TEK SEFERDE DAHA FAZLA OKUMAK İÇİN.

#define			SIZE		10

int main()
{
	FILE* f = fopen("asal1000.dat", "rb");
	if (!f)
	{
		fprintf(stderr, "dosyasi olusturulamadi\n");
		return 1;
	}

	int a[SIZE];
	size_t n;
	while ((n = fread(a, sizeof(int), SIZE, f)) != 0) // geri dönüş değeri okuduğu miktar. 0 olunca çıkar
	{									// bunu SIZE kadar okuyor artık. ama kaç tane okuyabildiği n, print array ile
		print_array(a, n);				// n kullanılır.
		_getch();
	}
	fclose(f);
}

--------------------------------------------------------------------------------------


	FILE* f = fopen("kayitlar.dat", "rb");
	if (!f)
	{
		fprintf(stderr, "dosyasi olusturulamadi\n");
		return 1;
	}

	printf("isim ve sehir girin\n");
	char name[25];
	char town[25];
	scanf("%s%s", name, town); // ali Mugla gir. CASE SENSITIVE!

	Employee e;
	while (fread(&e, sizeof e, 1, f))
	{
		if (!strcmp(e.mname, name) && !strcmp(e.mtown,town)) // burada year ilede filtreledik. ben yazmıyorum.
		{
			print_employee(&e);
			_getch();
		}

	}

--------------------------------------------------------------------------------------

DOSYA KOPYALAMA FREAD FRWRITE İLE.

//fcopy ali.exe veli.exe
int main(int argc, char **argv)
{
	if (argc != 3)
	{
		fprintf(stderr, "kullanim : <fcopy><sourcefile><destfile>\n");
		return 1;
	}

	FILE* fs = fopen(argv[1], "rb");
	FILE* fd = fopen(argv[2], "wb");

	if (!fs)
	{
		fprintf(stderr, "file %s cannot opened", argv[1]);
		return 2;
	}

	if (!fd)
	{
		fprintf(stderr, "file %s cannot created", argv[2]);
		fclose(fs);
		return 3;
	}

	char buffer[BUFFERSIZE];
	int n;
	int total_bytes = 0;

	while ((n = fread(buffer, 1, BUFFERSIZE, fs)) != 0) // n burada kaç adet okuyabildiği.BUFFERSIZE limitim var
	{													// herdöngü tekrarında, en son kalan kısım çok ufak olursa
													// bunu n ile öğrenip ona göre yazdırıyoruz.n başarı sayısı

		total_bytes += n;  // her biri 1 btye.n tane yazıldıysa, n kadar artar boyutu.
		fwrite(buffer, 1, n, fd);
	}

	fclose(fs);
	fclose(fd);

	printf("%d byte lik %s dosyasinin %s isimli kopyasi olusturuldu\n", total_bytes, argv[1], argv[2]);


}

==========================================================================================
==========================================================================================
==========================================================================================
==========================================================================================
==========================================================================================
==========================================================================================

FILE POINTER

NOTEPADDEKİ İMLEÇ GİBİ.
BUNU FİLE POİNTERI İLE YAPIYORUZ.
İSTENİLEN YERE SET EDİLEBİLİYOR.

Bu fonksiyonlar

1- FSEEK
2- REWIND
3- FTELL
4- FSETPOS
5- FGETPOS

int fseek(FILE *f, long n, int origin); başarılı olursa 0 döndürür.başarısız olursa nonzero
f = dosya handle 
n = ne kadar ileri veya geri alacağını belirtir. ileri için +, geri için - değer.
origin = konumlandırmanın origin olarak neresi alınarak yapılacağını bildiriyor.
	SEEK_SET = 0 => Konumlandırma dosyanın başından itibaren yapılacak
	SEEK_CUR = 1 => konumlandırma dosyanın file pointerın son konumuna göre yapılır.
	SEEK_END = 2 => konumlandırma dosyanın sonundan itibaren yapılır
		 
Dosyanın başından ileri gidilebilir ama geri gidilirse UB oluşur.
fseek(f,100,SEEK_SET) -> FILE PTR dosyanın başından başlayıp 100 offsetine gider
fseek(f,0,SEEK_SET) -> FILE PTR Dosyanın başına gider.
fseek(f,-100,SEEK_END) -> sondan 100 tane geri gelir.
fseek(f,0,SEEK_END) -> FILE PTR ı dosyanın sonuna gönderir. 1 dosyayı append etmek için kullanılabilir.
fseek(f,10,SEEK_CUR) -> FILE PTR son konumundan 10 ileri
fseek(f,-10,SEEK_CUR) -> FILE PTR son konumundan 10 geri
fseek(f,0,SEEK_CUR) -> FILE PTR son konumuna getirilir. BU ÇOK ÖNEMLİ. UB engelleyen senaryolar var burada.

=================================================================================================

ÇOK ÖNEMLİ !!!!!!!!!!!!!!!!!!!
FILE POİNTER NEDEN OLDUĞU YERE SET EDİLİYOR.

LOW LEVELDA EĞER OKUMA İŞLEMİNDEN SONRA YAZMA İŞLEMİ VEYA YAZMA İŞLEMİNDEN SONRA  OKUMA İŞLEMİ 
YAPACAKSAM (R+ MODDA AÇTIYSAM), UNDEFINED BEHAVIOR OLMAMASI İÇİN MUTLAKA FİLE POİNTERI SON KONUMUNA 
SET ETMEK GEREKİYOR.
fseek(f,0,SEEK_CUR); BU İŞLEM YANİ.

=================================================================================================

REWIND

void rewind(FILE *f);
FILE POİNTERI NEREDE OLURSA FARKETMEZ, DOSYANIN BAŞINA ÇEKİLİR.


=================================================================================================

FTELL

FILE POINTER DEĞERİNİ GET EDİYOR

long ftell(FILE *);  

=================================================================================================

FSETPOS - FGETPOS

file set/get position 
fpos_t gibi bir tür kullanıyorlar. Çoğunlukla 8 bytelık bir tamsayı türü olarak typedef ediliyor.

int fsetpos(FILE *f, const fpos_t *pos ); 
int fgetpos(FILE *f, const fpos_t *pos );

return değerleri başarı bilgisi. 0 başarılı, nonzero ise başarısız.

fgetpos = file pointer/konum göstericisi bilgisini get ediyor.
bunu pos değişkenine yazıyor.

fsetpos = pos değişkenden okuduğu değer ile file pointerı set ediyor.

fseek ile ftell ile bunlar zaten yapılıyor.
Farkı ne ? 
fseek ve ftell long türü ile işlem yapıyor.bazı sistemlerde long türü 4 byte.

fpos_t ise 8 byte yani büyük dosyalarda kullanılıyor.

=================================================================================================





ÖR:

int main()
{
	FILE* f = fopen("asal500bin.dat", "rb");
	if (!f)
	{
		fprintf(stderr, "Dosya acilamadi\n");
		return 1;
	}

	int n;
	printf("Kacinci asal sayi\n");
	scanf("%d", &n);

	fseek(f, (n-1)*(long)sizeof(int), SEEK_SET); // n-1 in sebebi, sayma sayı ile index farkı.

	int ival;
	fread(&ival, sizeof(int), 1, f);
	printf("%d. ci asal sayi %d", n, ival);
	fclose(f);

}

-----------------------------------------------------------------------------------------

EMPLOYEELERLE AYNI ÖRNEK

int main()
{
	FILE* f = fopen("kayitlar.dat", "rb");
	if (!f)
	{
		fprintf(stderr, "Dosya acilamadi\n");
		return 1;
	}

	int n;
	printf("Kacinci kayit\n");
	scanf("%d", &n);

	Employee e;
	fseek(f, (n-1)*(long)sizeof(e), SEEK_SET); // n-1 in sebebi, sayma sayı ile index farkı.
	fread(&e, sizeof(e), 1, f);

	print_employee(&e);

	fclose(f);

}


-------------------------------------------------------------------------------------------------------

FTELL ÖRNEĞİ.

int main()
{
	FILE* f = fopen("kayitlar.dat", "rb");
	if (!f)
	{
		fprintf(stderr, "Dosya acilamadi\n");
		return 1;
	}

	fseek(f,0L,SEEK_END); // file pointer file sonuna getirildi.
	printf("%ld\n", ftell(f)); // yerini verecek bu kısım. Yani dosyanında byte olarak büyüküğüdür aslında.

	fclose(f);
}

--------------------------------------------------------------------------------------

NOT: DOSYADAN SATIR SİLMEK DİYE BİRŞEY YOK.
YENİSİNDE BUNU YAZMAYIP, ESKİ DOSYAYI SİLİP, YENİSİNE DE ESKİ DOSYANIN İSMİNİ VERMEK GEREKİYOR.

ÖR:

void delete_records(const char* const pfname, int mday)
{
	FILE* fs = fopen(pfname, "rb");
	if (!fs)
	{
		fprintf(stderr, "Dosya acilamadi\n");
		exit(EXIT_FAILURE);
	}

	char tempfile_name[L_tmpnam];
	tmpnam(tempfile_name);

	FILE* fd = fopen(tempfile_name, "wb");
	if (!fd)
	{
		fprintf(stderr, "Dosya acilamadi\n");
		fclose(fs);
		exit(EXIT_FAILURE);
	}

	Employee e;
	int read_count = 0;
	int write_count = 0;

	while (fread(&e, sizeof e, 1, fs))
	{
		++read_count;
		if (e.mdate.md != mday)
		{
			fwrite(&e, sizeof e, 1, fd);
			++write_count;
		}
	}

	fclose(fd);
	fclose(fs);

	if (remove(pfname))
	{
		fprintf(stderr, "Dosya silinemedi");
		exit(EXIT_FAILURE);
	}

	if (rename(tempfile_name,pfname))
	{
		fprintf(stderr, "Dosya silinemedi");
		exit(EXIT_FAILURE);
	}

	printf("%d adet veri silindi\n",read_count-write_count);

}



int main()
{

	for (int i = 0; i < 31; ++i)
	{
		if (i % 10 != 0)
		{
			delete_records("kayitlar.dat", i);
			getchar();
		}

	}
}









*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "nutility.h"
#include "Employee.h"

#define			BUFFERSIZE		1024

void print_records(const char * const pfname)
{
	FILE* f = fopen(pfname, "rb");
	if (!f)
	{
		fprintf(stderr, "file cannot opened\n");
		exit(EXIT_FAILURE);
	}

	Employee e;
	while (fread(&e, sizeof e, 1, f))
	{
		print_employee(&e);
	}

	fclose(f);
}

void replace_records(const char* const pfname, const char* const p_oldname, const char* const p_newname)
{
	FILE* f = fopen(pfname, "rb+");
	if (!f)
	{
		fprintf(stderr, "Dosya acilamadi\n");
		exit(EXIT_FAILURE);
	}
	
	Employee e;
	int replaced = 0;

	while (fread(&e, sizeof e, 1, f))
	{
		if (!strcmp(e.mname, p_oldname))
		{
			strcpy(e.mname, p_newname);
			fseek(f, -(long)sizeof(e), SEEK_CUR);
			fwrite(&e, sizeof e, 1, f);
			fseek(f, 0L, SEEK_CUR);
			++replaced;
		}
	}

	fclose(f);
	printf("%d adet kayit degistirildi\n",replaced);
}

//YUKARIDA YAZMIŞTIM.DOSYADAN DİREKT VERİ SİLMEK DİYE BİRŞEY YOK.
//YENİ DOSYAYA YAZIP İSİM DEĞİŞTİRECEĞİZ.
void delete_records(const char* const pfname, int mday)
{
	FILE* fs = fopen(pfname, "rb");
	if (!fs)
	{
		fprintf(stderr, "Dosya acilamadi\n");
		exit(EXIT_FAILURE);
	}

	char tempfile_name[L_tmpnam];
	tmpnam(tempfile_name);

	FILE* fd = fopen(tempfile_name, "wb");
	if (!fd)
	{
		fprintf(stderr, "Dosya acilamadi\n");
		fclose(fs);
		exit(EXIT_FAILURE);
	}

	Employee e;
	int read_count = 0;
	int write_count = 0;

	while (fread(&e, sizeof e, 1, fs))
	{
		++read_count;
		if (e.mdate.md != mday)
		{
			fwrite(&e, sizeof e, 1, fd);
			++write_count;
		}
	}

	fclose(fd);
	fclose(fs);

	if (remove(pfname))
	{
		fprintf(stderr, "Dosya silinemedi");
		exit(EXIT_FAILURE);
	}

	if (rename(tempfile_name,pfname))
	{
		fprintf(stderr, "Dosya silinemedi");
		exit(EXIT_FAILURE);
	}

	printf("%d adet veri silindi\n",read_count-write_count);

}



int main()
{
	
	for (int i = 0; i < 31; ++i)
	{
		if (i % 10 != 0)
		{
			delete_records("kayitlar.dat", i);
			getchar();
		}
		
	}
}