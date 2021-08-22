// bir başlık dosyasında ilk yapılması gereken multiple inclusion guard
// bir başlık dosyasından birden fazla kez, aynı bildirimin tanımlanması hata olabiliyor.
// printf ile yazılanlar ekrana çıkmıyorsa muhtemelen std outputun bufferı fflush işlemine sokulması 
// gerekiyor. Daha ilerideki konu


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "nutility.h"


int main()
{
	int low, high;
	int prime_count = 0;
	
	printf("aralik değerlerini giriniz (min,max)");
	(void)scanf("%d%d", &low, &high);

	for (int i = low; i <= high; ++i)
	{
		if (isprime(i))
		{
			if (prime_count && prime_count % 10 == 0)
				putline();
			printf("%d ", i);
			++prime_count;
			sleep(50);
		}
	}		

	printf("\n%d kadar asal sayi bulundu\n", prime_count);
}