#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>

void show_ascii(void)
{
	FILE* file = fopen("ascii.txt", "w");
	if (!file)
	{
		fprintf(stderr, "Dosya olusturulamadi\n");
		return;
	}

	for (int i = 0; i < 128; i++)
	{
		if (iscntrl(i))
		{
			fprintf(file, "%-3d    %2X   KONTROL KARAKTERI\n", i,i);
		}
		else
		{
			fprintf(file, "%-3d    %2X   %c\n",i, i, i);
		}
		
	}
	fclose(file);

}

NOT : 20. ders ile bu ders bağlantılı kesinlikle oku

int main()
{
	0x800000fc;
	int u = 41; // onluk decimal
	int s = 041; // sekizlik octal
	int t = 0x41; // 16 lık hexadecimal 
	float f = 1.4;

	int x = 0b110111; // C dilinde böyle bir tanım compiler extension ile mümkün,
	// C++ ta ise destekleniyor.

	50000; // int türü burada sınırları aşabilir çünkü derleyiciden derleyiciye göre
	// fark ediyor. 2byte olsa sınır 32767 olacak ama int türü 4 byte ise int e sığar.
	//Buna implementation defined deniyor.

	2147483647; // int sınırı içerisinde
	2147483650; // int sınırı dışında birsonrakine gider.Aşağıda not aldım.10 luk sistemde
	// int ten sonra Long a taşar. 
	//8/16 da ise unsigned int e kayar.

	// 10 LUK SAYI SİSTEMİNDE. Burada sayıların nereye sığıldığına bakılıyor.
	// Eğer int x = 2147483650; UB dir çünkü işaretli sayılarda taşma undefined behaviour.
	//Taşma olayında eğer int 4byte long da 4 byte ise birsonraki unsigned long a taşar
	/*
	int
	long
	unsigned long 
	long long
	unsigned long long
	
	*/

	// 8/16 LIK SAYI SİSTEMİNDE
	//Taşma olayında eğer int 4byte long da 4 byte ise birsonraki unsigned long a taşar
	/*
	int
	unsigned int // bu ekstra geliyor. Decimal sayı sisteminde bu tür atlanıyor.
	long
	unsigned long
	long long
	unsigned long long


	NOT!!!!!!!!!!!!!!!!!!!!	
	Aynı tamsayı türünün işaretlisi ve işaretsizi işleme sokulursa işlem işaretsiz türde yapılır.
	İşaretsiz bir pozitif değer ile işaretli bir negatif değer ile işleme sokulursa, sign x değerini unsigned x e çevirecek. 


	*/
	
	if (f == 1.4)
	{
		printf("Dogru\n");
	}
	else
	{
		printf("yanlis\n");
	} 
		
	'\a';
		
	
	642u;
	642U;
	0x12u;
	01523;
	45L;
	39l;
	0x65L;
	0145L;

	54LU;
	57UL;

	5LL;
	4578LL;

	45ULL;
	45LLU;
	45llu;

	0;
	0u;
	0LU;
	0LL;
	
	//double
	34.0;
	34.;
	0.52;
	.51;
	//float
	34.3F;
	0.5f;

	//long double
	7.5L;
	7.L;

	2.8e8;
	3.6E7;
	4123e-5;

	show_ascii();

	'\x41'; // hexadecimal
	'\105'; // octal yani sekizli sayı sistemi
	' ';

	printf("\x42URS\x41\n"); // BURSA YAZDIRIR \x42 B , \x41 A
	printf("\102\101\102\101\012"); // \102 B , \101 A   \012 new line
	

}
