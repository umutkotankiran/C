#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <Windows.h>

int	sum_digit(int val)
{
	int sum = 0;
	while (val != 0)
	{
		sum += val % 10;
		val /= 10;
	}
	return sum;
}

int ndigit_count(int val)
{
	int digit_count = 0;
	if (val == 0)
	{
		return 1;
	}
	
	while (val)
	{
		++digit_count;
		val /= 10;
	}

	return digit_count;
}

int main()
{
	/* 

	printf("bir karakter giriniz \n");
	int ch = getchar();

	if (islower(ch))
		printf("islower ok\n");
	else
		printf("islower not ok\n");
	
	if (isupper(ch))
		printf("isupper ok\n");
	else
		printf("isupper not ok\n");
	
	if (isdigit(ch))
		printf("isdigit ok\n");
	else
		printf("isdigit not ok\n");

	if (isalpha(ch))
		printf("isalpha ok\n");
	else
		printf("isalpha not ok\n");
	if (isalnum(ch))
		printf("isalnum ok\n");
	else
		printf("isalnum not ok\n");
	if (isxdigit(ch))
		printf("isxdigit ok\n");
	else
		printf("isxdigit not ok\n");
	if (ispunct(ch))
		printf("ispunct ok\n");
	else
		printf("ispunct not ok\n");

	if (isspace(ch))
		printf("isspace ok\n");
	else
		printf("isspace not ok\n");

	if (isblank(ch))
		printf("isblank ok\n");
	else
		printf("isblank not ok\n");

	if (isprint(ch))
		printf("isprint ok\n");
	else
		printf("isprint not ok\n");
	if (iscntrl(ch))
		printf("iscntrl ok\n");
	else
		printf("iscntrl not ok\n");
	*/

	// --------------------------------------------

	/*
	printf("ispunct\n");
	for (int i = 0; i <= 127; i++) 
	{
		if (ispunct(i))
			putchar(i);
	}


	printf("\n\n");
	printf("isxdigit\n");
	for (int i = 0; i <= 127; i++)
	{
		if (isxdigit(i))
			putchar(i);
	}

	printf("\n\n");
	printf("isgraph\n");
	for (int i = 0; i <= 127; i++)
	{
		if (isgraph(i))
			putchar(i);
	}
	
	printf("\n\n");
	printf("isspace\n");
	for (int i = 0; i <= 127; i++)
	{
		if (isspace(i)) //bosluk oldugundan printf ile kod numaralarını yazdırmak mantıklı
			//putchar(i);
			printf("%d ", i);
	}

	printf("\n\n");
	printf("iscntrl\n");
	for (int i = 0; i <= 127; i++)
	{
		if (iscntrl(i)) //bosluk oldugundan printf ile kod numaralarını yazdırmak mantıklı
			//putchar(i);
			printf("%d ", i);
	}

	*/

	// ------------------------------------------------------	

	// tolower toupper
    /*
    printf("bir karakter giriniz\n");
	int c = getchar();

	printf("Upper %c ---> %c\n", c, toupper(c));
	printf("Lower %c ---> %c\n", c, tolower(c));
	*/

	/*
	printf("\n");
	int c1, c2;
	printf("iki karakter giriniz\n");
	c1 = getchar();
	c2 = getchar();

	if (toupper(c1) == toupper(c2))
	{
		printf("%c ile %c ayni karakterler\n", c1, c2);
	}
	else
		printf("%c ile %c farkli karakterler\n", c1, c2);

	*/

	// -------------------------------------------------------------

	// TERNARY OPERATOR - KOŞUL OPERATORU 
	// operator - kontrol deyimi ve fonksiyon ayrı şeyler.dikkat.
	// op1 ? op2 : op3 . operator öncelikte tablosunda 13. sırada sağdan sola.
	// aynı zamanda 3 operand alıyor. birinci operator logic yorumlanıyor doğruysa 2. değilse 3. 
	// operand olarak değer üretiyor.

	/*
	int x, y;
	printf("iki tamsayi giriniz\n");
	scanf("%d%d", &x,&y);

	printf("max : %d", x > y ? x : y);
	*/
	//if(isprime(x) == isprime(y))
	// diğer dillerde olabilir ama C de ikiside doğru veya ikiside yanlış olsa bile if true olarak değer görmeyebilir.
	// çünkü return değerleri farklı.iksiide doğru ama biri 5 diğeri 1 döndürürse arada false olmadığı için
	// if kontrol deyimi içersindeki ifade false dönecektir. 5 == 1 ===> false 
	// Bu sebeple if(!!exp1 == !!exp2). Bir ifadenin değilnin değili onun logic değeridir.

	// NOT : ? :  -> Burada ? bir yan etki noktasıdır.Yani sequence pointtir.

	// genel kullanımlar
	// min = a < b ? a : b; olabilir.
	// f(a>10 ? x : y);
	// return x>y ? x : y;
	// örnekler çoğaltılabilir.

	//Örnek güzel
	// c >= 'A' && c<='Z' ? c - 'A' + 'a' : c; bu tolower a alternatif bir kod.  


	//int c = 'O';
	
	// printf("%c", c >= 'A' && c <= 'Z' ? c - 'A' + 'a' : c);

	//koşul operatörünün ürettiği değerden faydalanmıyorsan, operatörü kullanma.
	// a>0 ? f1 : f2 ; burada kullanma mesela.if ve else li ifade kullan. 

	// güzel örnek
	// x > 10 ? a : b = 0;    // C de sentaks hatası C++ ta değil
	// C de yazmanın yolu aşağıda
	// *(x > 10 ? &a : &b) = 0;


	/*
	if (x == 5)
		y = 13;
	else if(x == 7)
		y = 29;
	else
		y = 67;
	
	bunlar makrolarda karşımıza çıkacak. 
	ifadenin karşılığı. yanyana ve altalta yazılabilir.
	y = x == 5 ? 13 :
	x == 7 ? 29 : 67 ; 

	*/

	/*

	int ch;

	printf("bir yazi giriniz\n");

	while ((ch = getchar()) != '\n')
	{
		printf("%c  %d\n",ch,ch);
	}

	*/

	/*
	printf("%d\n", sum_digit(4235));
	printf("%d\n", sum_digit(987678));

	printf("%d\n", ndigit_count(54897));
	printf("%d\n", ndigit_count(9857));
	*/


	/*
	
	armstrong sayısı

	int i = 1000;
	
	while (i < 10'000)
	{
		int d1 = i / 1000;
		int d2 = i / 100 % 10;
		int d3 = i / 10 % 10;
		int d4 = i % 10;
		if (i == (d1 * d1 * d1 * d1) + (d2 * d2 * d2 * d2) + (d3 * d3 * d3 * d3) + (d4 * d4 * d4 * d4))
			printf("%d\n",i);
		++i;

	}

	*/


	return 0;
}
