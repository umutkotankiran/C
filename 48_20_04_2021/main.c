#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "nutility.h"

/*

BITSEL İŞLEMLER / BITWISE OPERATIONS
------------------------------------
İlk önce operatörleri bilip sırasını yazmak lazım.
Kursun başında yazmıştık zaten bu tabloyu.


~ bitsel değil operatörü
^ exclusive or = ikiside farklı olursa true 
>>  bitwise right shift
<<  bitwise left shift


BİTSEL OPERATÖRLER
------------------------------------------------------------------
2	~ ---> bitsel değil operatörü
------------------------------------------------------------------
5	>> << ---> bitsel sağa/sola kaldırma operatörü.right left shift 
------------------------------------------------------------------
8   &  ---> bitsel ve
------------------------------------------------------------------
9   ^ ---> bitsel xor 
------------------------------------------------------------------
10  | ---> bitwise or
------------------------------------------------------------------
14  <<= >>= &= |= ^=  ---> işlemli atama operatörleri 
------------------------------------------------------------------

BU OPERATÖRLER TAMSAYI OPERATÖRLERİDİR.
OPERANDLARI TAMSAYI OLMALI. BİRDE MOD(%) OPERATÖRÜ VAR BÖYLE.
REEL SAYI SENTAKS HATASIDIR.

UFAK TEKRAR
1110 0101  En sağdaki bit 0. bit. En soldaki ise 7. bit. 

BİTSEL İŞLEMLERE GENELDE UNSIGNED INT TÜRÜ GENELDE KULLANILIYOR.
İLERİDE GÖRÜLECEK, UNSPECIFIED DURUMA OLUŞUYOR SIGNED TURLERDE

Bunlara bitwise denmesinin sebebi, bit bit yapılan işlemler bitwise,
pairwise ise çift çift anlamında.

x & y
101100101
111000011

bitwise manipultions veya operations deniyor işlemlere

======================================================================
======================================================================

BİTSEL DEĞİL ~ OPERATÖRÜ
NO SİDE EFFECT
UNARY PREFİX

~x 
100100101 bunun bitwise değili
011011010  budur.Tam tersi.

TEST
	int x;
	printf("bir sayi girin :");
	scanf("%d", &x);
	bitprint(x);
	bitprint(~x);
	bitprint(~~x);


1 - Değilinin değili kendisidir.

2 - ~0 da hepsi 1 dir.

3 - bir sayının bitsel değili, 1 fazlasının negatif halidir. 0 biraz daha farklı.

	int x;
	int y;
	printf("bir sayi girin :");
	scanf("%d", &x); // 10 girildi
	y = -~x; // y = 11 oldu
	printf("%d", y);


======================================================================
======================================================================

BİTSEL KAYDIRMA OPERATÖRLERİ / BITWISE SHIFT OPERATORS

------------------------------------------------------------------
5	>> << ---> bitsel sağa/sola kaldırma operatörü.right left shift
------------------------------------------------------------------

>> ---> bitsel sağa kaldırma operatörü
<< ---> bitsel sola kaldırma operatörü
Bunların yan etkileri yok.

ÖR:
a << b   bu a nın bitlerini b kadar sola kaydır demek.

11111111111  bu a olsun

a << 3 demek
11111111000 bununla eşdeğerdir.soldan 3 bit çıkar ve sağa 0 lar eklenir.

ÖR:
int main()
{
	int x = -1; // hepsi 1 olur bitler

	bitprint(x);
	bitprint(x << 3);
	printf("yan etkisi yok\n");
	bitprint(x);
}

-------------------------------

int main()
{
	int x = -1; // hepsi 1 olur bitler
	while (x)
	{
		bitprint(x);
		x <<= 1;		// x = x << 1; demek aslında
	}
		bitprint(x);
}

birde sleep ve bitprint i \r ile yazıp örnek yaptı.aynı satırdı print ediyor.


-------------------------------
-------------------------------
-------------------------------


ÇOK ÖNEMLİ!!!

1 - BİTSEL SOLA KAYDIRMA OPERATÖRÜNÜN SAĞ OPERANDININ, NEGATİF OLMASI DURUMU TANIMSIZ DAVRANIŞTIR.
	X << Y  BURADA Y < 0 İSE UNDEFINED BEHAVIOR

2 - BİTSEL SOLA KAYDIRMA OPERATÖRÜNÜN SAĞ OPERANDININ TAMSAYI DEĞERİ, SOL OPERANDIN BİT SAYISINDAN BÜYÜK VE EŞİT İSE UNDEFINED BEHAV.
	BU DURUM BİTSEL SAĞA KAYDIRMADA DA AYNI.
	X << Y 
	X İN BİT SAYISI 32 OLSUN, BU DURUMDA Y [0-31] ARALIĞINDA OLMAK ZORUNDA. 32 VEYA DAHA ÇOK UNDEFINED BEHAVIOR
	
3 - BİTSEL SOLA KAYDIRMADA (FEEDİNG) SOL OPERANDIN TÜRÜNDEN BAĞIMSIZ OLARAK 0 DIR.

NOT: 
	int x = 25;
	printf("%d\n", x);
	printf("%d\n", x<<1); // bu ifade x in 2 ile çarpımını elde eder.
	printf("%d\n", x<<2); // bu ifade x in 4 ile çarpımını elde eder.

4 - BİTSEL SAĞA KAYDIRMADA (FEDDİNG) SOL OPERANDIN TÜRÜNE BAĞLI OLARAK DEĞİŞEBİLİR.
	A - UNSİGNED TAMSAYI TÜRLERİ İÇİN SAĞA KAYDIRMADA SOLDAN 0 LAR İLE FEEDİNG YAPILIR
		int main()
		{
			unsigned int x = 2324;
			bitprint(x);
			bitprint(x >> 3); // sağa kaydırmada, soldan 0 lar gelir çünkü tür unsigned tamsayı türden.
		}
		
	B - SİGNED TAMSAYI TÜRLERİNDE(İŞARETLİLERDE) 
			B.1 - SAYININ KENDISI POZİTİF DEĞER İSE HERZAMAN BESLEME 0 İLE YAPILIR.
			(SİGNED TÜRLERDE SAYININ SIFIR OLMASI , 0.... DEMEK. YANİ 0 İLE BAŞLIYOR DEMEK)

			B.2 - SAYI NEGATİF DEĞER İSE BESLEME IMPLEMENTATION DEFINED.
				  COMPİLERA BAĞLI OLARAK FEEDİNG 0 VEYA 1 İLE YAPILIR.ÖRNEKTEN SONRA DEVAM EDİYOR.
				  (SİGNED TÜRLERDE SAYININ NEGATİF OLMASI, 1.... DEMEK. YANİ 1 İLE BAŞLIYOR DEMEK)


		    ÖR:
			1000101001101   SİGNED TÜR İÇİN BU NEGATİF BİR SAYI
			
			1 ADET SAĞA KAYDIRINCA AŞAĞIDAKİ GİBİ FEEDİNG 0 İLE YAPILIRSA SAYININ NEGATİFLİĞİ KORUNMAZ.
			BUNA LOGIC FEEDING DENİYOR.
			
			SAYININ NEGATİFLİĞİNİN KORUNMASI İÇİN 1 EKLEMESİ GEREKİR.
			BUNADA ARİTMETİK FEEDİNG DENİYOR.
			
			0100010100110 -> BURASI LOGIC FEED. 0 İLE FEED EDİLMİŞ
			1100010100110 -> BURASI ARITMETIC FEED. 1 İLE FEED EDİLMİŞ

			ÖR:

			int main()
			{
				int x = -1; // -1 negatif bir sayı.hepsi 1 olacak     1111 1111 ...
				bitprint(x>>5); // burada negatif bir sayıyı sağa kaydırma işlemi var.IMPLEMENTATION DEFINED.
								// soldan 0 veya 1 gelebilir. 0 gelirse logic feed. Sayı pozitif olur.
								// Signed türde en soldaki sign bitiydi. 1 olduğundan negatif
								
								// 1 gelirse arithmetic feed/sign extension. 1 gelirse negatiflik devam eder.

								// ya 000001111111111111 olacak yada 111111111111111111 olacak
								// benim compiler 1 atadı.aritmetic feed yaptı.
			}

------------------------------------------------------------------------------------
------------------------------------------------------------------------------------

int main()
{
	unsigned int x = ~(~0u >> 1);
	// 1111111111111 >> 1 yapacak.soldaki unsigned.
	// 0111111111111. bu bir sağa kaydırılmış hali.
	// 1000000000000 bu da onun değili.

	while (x)
	{
		bitprint(x); 1 bitini sirekli sağa kaydırıyorum.
		x >>= 1;
	}
		bitprint(x);
}

------------------------------------------------------------------------------------
------------------------------------------------------------------------------------
------------------------------------------------------------------------------------

limits.h de işaretli en küçük tamsayı gibi değeerler var.
bu değer ya oradan kullanılır ya da idiyom ile.

~(~0u >> 1) ya böyle yada INT_MIN ile.
bu işaretsiz için geçerli buarada. 1000000000000000000 işaretsiz tamsayılarda min değerdi.


====================================================================================
====================================================================================
====================================================================================

BİTSEL VE &    BİTSEL VEYA |   ÖZEL VEYA ^

NOT: BİTSEL LOGİC OPERATÖRLERİN KISA DEVRE DAVRANIŞI YOKTUR.
NOT: LOGİC OPERTÖRLERDE SOL TARAF CHAR SAĞ TARAF İNT GİBİ DEĞERSE INTEGRAL PROMOTION BURADA DA VAR.
AMA SOL OPERAND İÇİN VAR

-------------------------------------------------

BİTSEL VE &

Hepsi binary infix tir.
a & b klarşılıklı bitler "ve" işlemine sokulacak.

101000100111110
001101111010101  ve işlemi
--------------------------
001000100010100

0 ve 1 = 0
1 ve 0 = 0
0 ve 0 = 0
1 ve 1 = 1 

YAN ETKİSİ YOK.
&= operatöründe var.

NOT:
&& İLE & Yİ KARIŞTIRMA

int x = 0b101010101; bu C de compiler extension buarada. C++ ta standart.

TEKRAR
NOT: BİTSEL LOGİC OPERATÖRLERİN KISA DEVRE DAVRANIŞI YOKTUR
NOT: LOGİC OPERTÖRLERDE SOL TARAF CHAR SAĞ TARAF İNT GİBİ DEĞERSE INTEGRAL PROMOTION BURADA DA VAR.
AMA SOL OPERAND İÇİN VAR

-------------------------------------------------
-------------------------------------------------
-------------------------------------------------

BİTSEL VEYA |

1100110010010
1010101001100  bitsel veya
----------------------------
1110111011110  


int main()
{
	int x, y;
	printf("iki tamsayi gir:");
	scanf("%d%d", &x, &y);
	bitprint(x);
	bitprint(y);
	bitprint(x | y);
}


burada da || ile | yi karıştırma.


-------------------------------------------------
-------------------------------------------------
-------------------------------------------------

BİTSEL ÖZEL VEYA ^

xor yad exor deniyor.
Kural
bitler aynı ise 0
bitler farklı ise 1

0 ÖZEL VEYA	0	0
1 ÖZEL VEYA 1	0
1 ÖZEL VEYA	0	1
0 ÖZEL VEYA	1	1

010111
101010	ÖZEL VEYA
------------------
111101  


NOT!!!!!!!!!!!!!!!!!!!!!!!!!
ŞÖYLE BİR BAKINCA, ^ İŞLEMİNDE 1 BİTİ, KARŞISINDAKİNİN TERSİNİ SONUCA YAZIYOR.


int main()
{
	int x, y;
	printf("iki tamsayi gir:");
	scanf("%d%d", &x, &y);
	bitprint(x);
	bitprint(y);
	bitprint(x ^ y);
}

NOT:

X ^= Y;
X ^= Y;   X BURADA KENDİ DEĞERİNE TEKRAR GELİR.

ÖR:

int main()
{
	int x, y;
	printf("iki tamsayi gir:");
	scanf("%d%d", &x, &y);

	x ^= y;
	printf("%d\n", x);
	x ^= y;
	printf("%d\n", x); // ilk değeri geri yazdırır.
}

-------------------

ÖR:

int main()
{
	int x, y;
	printf("iki tamsayi gir:");
	scanf("%d%d", &x, &y);

	// iki tamsayıyı temp kullanmadan swap etmek.
	printf("x = %d   y = %d\n", x,y);
	x ^= y;
	y ^= x;
	x ^= y;
	printf("x = %d   y = %d\n", x,y);
}

// x ^= y,y ^= x,x ^= y; şeklinde de yazılabilir.


NOT:
	int x = 7657;
	x^ x; // bu sıfır verir. çünkü tüm bitler aynı. xor da aynı olanlar 0 dır.
	// mesela iki pointer olur ikiside &x i tutar. x ^= y,y ^= x,x ^= y; işlemini bu iki pointer a uygularsak
	// 0 verir. çünkü bir sayıyı kendi ile xor yapmış oluyoruz.xorswap(*p1,*p2) gibi



----------------------------------------------------------------

x & y << 5; gibi ifadeler var.burada öncelik var ama daha rahat okunsun diye öncelik parantezine alabiliriz.
(x & y) << 5;
x & (y << 5);


=================================================================================
=================================================================================
=================================================================================
=================================================================================


BITWISE MANIPULATION

BİR TAMSAYININ BELİRLİ BİR BİTİNİ BİRLEMEK İSTİYORUM DİYELİM.
TO SET TO BIT
TO TURN THE BIT ON

1110101011010011*10100 BİR İŞLEM İLE SADECE 5. BİTİNİ DEĞİŞTİRECEĞİM.
1110101011010011110100 BUNU ELDE EDECEĞİM.

BURADA BİTSEL VEYA KULLANILIR.BUNUN İÇİN
0000000000000000100000  KULLANILIR. BUNA BİTMASK(BİTSEL MASKE) DENİYOR.


1110101011010011*10100
0000000000000000100000	BİTSEL VEYA
-------------------------------------
1110101011010011110100


MASKI ELDE EDELİM

KURALI YAZARSAK
X BİR TAMSAYI DEĞİŞKEN, N BU TAMSAYININ SET EDİLECEK İNDEXİ OLMAK ÜZERE,
X İN N İNCİ BİTİNİ SET EDEN İFADE 
X | (1 << N) YAN ETKİ YOK
X |= (1 << N) YAN ETKİ VAR

ÖR:
int main()
{
	int x = 0;
	int n;

	printf("Kacinci bit set edilsin\n");
	(void)scanf("%d", &n);

	x |= (1 << n);
	bitprint(x);

}

----------------------------------------

int main()
{
	int x = 0;
	randomize();
	while (x != -1)
	{
		bitprint(x); // bitprint \r ile yazıldı.
		x |= 1 << (rand() % 32);
		sleep(1);
	}
		bitprint(x);
}


--------------------------------------------------------


BİR TAMSAYININ BİR BİTİNİ SIFIRLAMAK İSTERSEM
TO RESET THE BİT
TO CLEAR THE BİT
TO TURN THE BIT OFF


1110101011010011*10100 DİYELİM Kİ * BİTİNİ 0 LAMAK İSTİYORUM.

1111111111111111011111 BİTMASK OLARAK BUNU KULLANIP VE & İŞLEMİNE SOKMAM GEREKİYOR.


İŞLEM
1110101011010011*10100
1111111111111111011111  VE İŞLEMİ
---------------------------------
1110101011010011010100

SAYININ * BİTİNİ SIFIRLAMIŞ OLDUK.

ŞİMDİ MASK I ELDE EDELİM
~(1 < 5)       1111111111111111011111 BU ŞEKİLDE ELDE EDİLDİ

X & ~(1 < n)	yan etkisi yok
X &= ~(1 < n)	burada yan etki var


ÖR:
int main()
{
	int x = -1;
	int n;

	printf("kac indexli bit 0 olsun\n");
	(void)scanf("%d", &n);

	x &= ~(1 << n);
	bitprint(x);
}




--------------------------------------------------------

BİR TAMSAYININ BELİRLİ BİR BİTİNİ TERSİNE ÇEVİRMEK
TO FLIP THE BIT
TO TOGGLE THE BIT
	
1110101011010011*10100
BİTSEL XOR DA 1 KARŞISINDAKİNİ TERSİNE ÇEVİRİYORDU

1110101011010011*10100
0000000000000000100000	ÖZEL VEYA XOR
-------------------------------------
X YERİNE VAROLANIN TERSİ OLAN BİT GELİR.

X ^ (1 < N);  side effect yok
X ^= (1 < N); burada var 


ÖRNEK:
int main()
{
	int x = 0;
	randomize();

	while (x != -1)
	{
		bitprint(x);
		sleep(1);
		x |= (1 << (rand() % 32));
	}
	bitprint(x);

	while (x)
	{
		bitprint(x);
		sleep(1);
		x &= ~(1 << (rand() % 32));
	}
	bitprint(x);
}




-------------------------------------------------------------------

BİR TAMSAYININ BELİRLİ BİR BİTİNİN 1 YADA 0 OLDUĞUNU ÖĞRENMEK
TO GET A BIT

1110101011010011*10100
0000000000000000100000    BURADA VE İŞLEMİ KULLANSAK, DİĞER TÜM BİTLER 0 LANIR AMA ARADIĞIM BİT 1 İSE 1 OLACAK
							SIFIR İSE 0 OLACAK.ÇÜNKÜ O BİTİ 1 İLE İŞLEME SOKUYORUM.

IF(X & (1 << N))
	GİRERSE EĞER O BİT 0 DAN FARKLI YANİ 1 DEMEKTİR.
ELSE
	0 DEMEKTİR.

--------------------------------------------------

ÖR:
int main()
{
	int x;

	printf("bir tamsayi gir:");
	(void)scanf("%d", &x);

	bitprint(x);// \r yi \n yapmayı unutma

	// tüm bitlere bakılacak ve 32 bit zaten. int 4 byte çünkü.(sizeof x ) * 8 de yapılabilirdi.
	for (size_t i = 0; i < 32 ; ++i)
	{
		if (x & (1 << i))
			printf("%d nolu bit %d\n", i, 1);
		else
			printf("%d nolu bit %d\n", i, 0);
	}
}


--------------------------------------------------
--------------------------------------------------
--------------------------------------------------

BAZI İDİYOMLAR VE ÖRNEKLER

ÖNEMLİ ÖRNEK
İKİ SAYININ ZIT İŞARETLİ OLDUĞUNU NASIL ANLARIZ.

X ^ Y YAPARIZ. XOR BİTLER FARKLI İSE 1 DEĞİLSE 0 ÇEVİRİR.
ZIT İŞARETLİ OLMASI İÇİN EN SOLDAKİ BİTLER, BİRİNDE 1 DİĞERİNDE 0 OLMALI.
1....
0....  XOR
-----------
1
BU İŞLEMİN SONUCUNDA DA EN SOL TARAF 1 ÇIKTI YANİ NEGATİF BİR TAMSAYI ÇIKTI.
BU DURUMDA

IF((X ^ Y) < 0)
    İSE TERS İŞARETLİDİR. :)
ELSE
	AYNIDIR


ÖR:

int main()
{
	int x,y;

	printf("iki tamsayi gir:");
	(void)scanf("%d%d", &x,&y); // 10 20 gir birde 10 -20 gir

	if ((x ^ y) < 0)
		printf("zit isaretli\n");
	else
		printf("ayni isaretli\n");

}

----------------------------------------------------------------------------
----------------------------------------------------------------------------

BIR TAMSAYININ BİTLERİNİ YAZDIRMAK.
BITPRINT TE ITOA YA YAPTIRDIK.
BURADA FARKLI OLACAK

ÖR:

void bprint1(int x)
{
	for (int i = (int)(sizeof(x) * CHAR_BIT - 1); i >= 0; --i) // CHAR_BIT 8 değerini verir.
	{
		putchar(((x >> i) & 1) ? '1' : '0'); // 31 tane sağa kaydırıyor ve oradaki değeri 1 ile(0.....1) ve işlemine sokuyor
	}										// bir sonrakinde 30 kaydırıp işleme sokuyor.Her seferinde 1 ile ve işlemine sokuyor.
	putchar('\n');
}

// yukarıdaki örnekte mask sabit sayıyı kaydırıyorduk.
//aşağıdakinde mask değişecek sürekli.

void bprint2(int x)
{
	unsigned int mask = ~(~0u >> 1);
	//ne elde ettik.
	// 1. 0u
	// 2. 1111111111111
	// 3. 0111111111111  unsigned olduğu için 0 geldi.signed olsaydı implementation defined.
	// 4. 1000000000000  değer bu.

	while (mask)
	{
		putchar(x & mask ? '1' : '0');
		mask >>= 1;
	}
	putchar('\n');
}

int main()
{
	int x = 88759;
	bitprint(x);
	bprint1(x);
	bprint2(x);
}

----------------------------------------------------------------------------
----------------------------------------------------------------------------

TAMSAYININ 2 NİN KUVVETİ OLUP OLMADIĞINI SINAYAN FUNCTIONAL MACROYU BULACAĞIZ.
KATI DEĞİL KUVVETİ.

BİTLERİNDE 1 ADET 1 OLACAK

00000000000000100000   X İSE
00000000000000011111   X - 1 DİR.

BUNLARI VE İŞLEMİNE SOKUYORUZ

00000000000000000000
BURASI TUTMALI. YANİ SADECE İKİNİN KUVVETLERİNDE GEÇERLİ BU.
0 İSE LOGİC DEĞİLİ DE 1 DİR.

PROBLEM SAYININ 0 OLMASI DURUMUNDA DA BU EŞİTLİK SAĞLANIYOR.OU İF İLE KONTROL EDECEĞİZ.

!(X & (X -1)) 


ÖR:
#define		powerof2(a)		((a) && !((a) & ((a) - 1)))

int x;
printf("sayi girin ");
scanf("%d", &x);

if (x && !(x & (x - 1))) // 0 da kontrol edilmiş.
	printf("2 nin kuvveti\n");
else
	printf("2 nin kuvveti degil\n");


------------------------------------------------
ÖDEV:

16 ve 32 bitlik sayılar için  little endiannes ve big endianned dönüşümü yapan macroyu tanımlayın.
ab d2 
d2 ab olacak.
8 bit sağa 8 bit sola ve bunları bitsel veyala

#define		econ16(x)		((x) >> 8 & 255) | ((x) << 8 & 255)  

neden 255 ile & işlemine soktuk ? 

sayı negatifse derleyici 1 ile feed edebilir 
10101010 ise sayı
11111111 10101010 olabilir. 255 ile ve işlemine sokmak
00000000 11111111   demektir.yani başa gelen 0 ları ekarte ediyor.

32 BİT İÇİN BEN YAZACAĞIM.

AB CD DE FG
FG DE CD AB  GİBİ OLACAK.


-----------------------------------------------------------------------------
-----------------------------------------------------------------------------
-----------------------------------------------------------------------------

BİR TAMSAYININ SET EDİLMİŞ BİTLERİNİ LOOKUP TABLE KULANILARAK SAYILMASI.
YANİ 1 LERİN SAYISINI TUTAN LOOKUP TABLE

bu fonksiyon kaç adet 1 olduğunu bulduğumuz foksiyon.kolay oldu böyle.
çıktısını dizi yaptık ve nutility ye koyduk.

int sbc(int x)
{
	int cnt = 0;
	unsigned int mask = ~(~0u >> 1); // 10000000000.. elde ettik

	while (mask)
	{
		if (x & mask)
			cnt++;
		mask >>= 1;

	}

	return cnt;
}


----------------------------------------------------

int main()
{

	int x; // x 32 bitlik bir tamsayı
	printf("bir tamsayi girin \n");
	scanf("%d", &x);

	// biz bunu 255 ile &/ve lersek, elde ettiklerimiz sayının düşük anlamlı byteları elde edilir.
	// x i 8 sağa kaydırırsak, düşük anlamlı 2. byte ının kaç bitinin 1 olduğunu buluruz.
	// bu şekilde hepsi bulunup toplanır.
	// hem lookup table yarattık hemde bunu nutility ye koyduk.
	// sonra sbc_[x & 255] + sbc_[x >> 8 & 255] + sbc_[x >> 16 & 255] + sbc_[x >> 24 & 255] ifadesini macro yaptık.

	printf("%d sayisinin %d biti 1", x,sbc(x));

}




*/

#include <limits.h>
#include <stdlib.h>

#define		powerof2(a)		((a) && !((a) & ((a) - 1)))
#define		econ16(x)		((x) >> 8 & 255) | ((x) << 8 && 255)

int main()
{

	int x; // x 32 bitlik bir tamsayı
	printf("bir tamsayi girin \n");
	scanf("%d", &x);

	// biz bunu 255 ile &/ve lersek, elde ettiklerimiz sayının düşük anlamlı byteları elde edilir.
	// x i 8 sağa kaydırırsak, düşük anlamlı 2. byte ının kaç bitinin 1 olduğunu buluruz.
	// bu şekilde hepsi bulunup toplanır.
	// hem lookup table yarattık hemde bunu nutility ye koyduk.
	// sonra sbc_[x & 255] + sbc_[x >> 8 & 255] + sbc_[x >> 16 & 255] + sbc_[x >> 24 & 255] ifadesini macro yaptık.

	printf("%d sayisinin %d biti 1", x,sbc(x));

}