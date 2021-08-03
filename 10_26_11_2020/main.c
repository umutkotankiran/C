#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// buffer boşaltma için fonksyon
// ikinci scanf in çalışması için std input boş olmalı yoksa arka arkaya bufferdaki değeri alır.beklemez.

void clear_buffer()
{
	int c;

	c = getchar();
	while ((c = getchar()) != '\n' && c != EOF)
		;

}

int main()
{
	int x, y;
	printf("sayi gir :");
	scanf("%d", &x);

	// clear_buffer(); bunu kaldırıp ilk scanf te 12 asd girip denenebilir.

	printf("Bir sayi daha gir : ");
	scanf("%d", &y);

	printf("x = %d\n", x);
	printf("y = %d\n", y);

	//////////////////////////////

	int a = 12, b = 6;
	printf("%d\n", a++);
	printf("%d\n", a);

	printf("%d\n",++b);

	 /*
	 Operator öncelik seviyeleri
	 
	 1	() [] . ->
	 2	+ - ! ~ & * sizeof (type cast) ++ --		sağdan sola (sağdan sola parantezlemeye başlıyoruz)
	 3	* % /										3 tanesi hariç diğerleri soldan sağa
	 4	+ -
	 5	>> <<
	 6	< <= > >=
	 7	== !=
	 8	&
	 9	^
	 10 |
	 11 &&
	 12 ||
	 13	? :											sağdan sola
	 14 = += -= *= /= %= >>= <<= &= ^=  |=			sağdan sola
	 15 ,
	 
	 */

	int x1 = 10, y1 = 10, z1 = 10;
	x1++ * y1 - 10 / 5 < z1 % 5;
	//öncelik sıralı hali
	(((x1++) * y1) - (10 / 5)) < (z1 % 5);

	10 * 5 - 5 > 10;
	// sıralı hali
	((10 * 5) - 5) > 10;

	!~x1++;
	//2. öncelik sırası sağdan sola
	!(~(x1++));

	// double tiplerde fmod isimli fonksiyon kullanılıyor.
	// int tiplerde bölüm operandın sağındaki değer 0 olursa tanımsız davranış
	// ++ ve -- nin operandı lvalue expression olmalı. Bunların yan etkisi var. artırıp azaltıyor.
	// yani bu operatorler nesnenin değerini üretir.yan etkisi değer artırmaktır.
	// ++x -> ürettigi değer in in bir fazlası.Yan etkisi de bir fazlası
	// x++ -> ürettiği değer x in kendisi. yan etkisi x in bir fazlası
	int a1 = 12;
	int b1 = 7;

	printf("%d\n", ++a1 % b1--); // 6 
	printf("%d\n", a1++ % --b1); // 3

	// C de karşılaştırma operatorleri int değer döndürür.
	// a>b doğru ise 1
	// a<b yanlış ise 0


	printf("Degerrr : %d\n", 1 == 2 != 3); //((1 == 2) != 3)
	printf("Degerrr : %d\n", 1 != 2 == 3); //((1 != 2) == 3)






}
 