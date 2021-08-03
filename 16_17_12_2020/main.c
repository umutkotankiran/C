#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	//yorum satırları
	// ----------------------------------------

	// yorum satırları compile edilmez.
	// gereksiz açıklamalardan kaçınmak gerekiyor.
	// değişken ve fonksiyon isimlerini düzgün seçersek açıklamaya gerek kalmıyor
	// bu yorum C99 ile geldi. Öncesinde compiler extension ile destekleniyordu.
	// En iyi açıklama yapılmayandır. Birçok yorum satırı kalitesiz kod yazıldığı için yazılıyor 
	// veya fonksiyon haline getirilmesi gereken bir kod fonksiyon haline getirilmediği için yazılıyor.
	// kodu yorum satırı haline getirmeye comment out deniyor.
	// kodda olmaması gereken bir şey yorum haline gelmiş kod.


	/*************************************************
	*	file is_prime.c
	*	returns prime numbers
	*	author : Ali Veli
	*	all rights reserved by Dell
	*	last update : 12.07.1998
	***************************************************/

	/*	  Global Declerations	*/


	/*    Function Definitions    */


	/*	
		function isprime
		test integer
		....
	*/


	// Önişlemci komutları yorum satırı yapılabilir. 
	// Yorum satırları derleyici tarafından koddan çıkarılması, 
	// önişlemci komutarının çalışmasından öncedir.


	// -----------------------------------------------------
	// -----------------------------------------------------
	// -----------------------------------------------------
	// -----------------------------------------------------
	// -----------------------------------------------------
	// -----------------------------------------------------

	// FONKSİYON BİLDİRİMLERİ

	/*
	to define to function
	to call a function
	to declare to function
	*/

	// x = func() func isimli fonksiyon olmasa bile hata vermez.Geriye dönük uyumluluktan ötürü böyle.
	// c++ da hata verir. bu fonksiyonu bulamadığını gösterir.
	
	// fonsiyon bildirimi
	// int func(int x); argüman tipi verilmeyebilir.
	// adı geri dönüş ve parametreleri hakkında bilgi verir.

	//derleyicinin ürettiği kod.
	// fonksiyon kodu aynı kaynak dosyada olmak zorunda değil. Genelde de böyle.
	// derleyici kendinsinden sonraki linker için obje dosyada bu fonksiyonun çağrıldığını anlatan özel bir isim yazacak.
	// buna external reference deniyor. Derleyicinin ürettiği derlenmiş kod, func fonksiyonunun derlenmiş koduyla 
	// linker aracılığı ile birleştirilecek. Derleyici de bu yüzden çağrılan fonksiyonun adını özel bir notasyon ile 
	// linkera yazıyor. Buna extenal reference deniyor.

	/*
	fonksiyona giriş kodları
		// linker için bir referans isim veriyor.
	fonksiyondan çıkış kodları	
	*/

	// fonksiyon bildiriminde parametre isimleri eğer faydalı ise kullanılabilir.Gerek yoksa kullanmaya gerekte yok.

	// int func(void) parametresi yok demek
	// int func() parametreleri hakkında bilgi verilmemiş demek.


	// -----------------------------

	// C de her modül iki dosyadan oluşur.
	// file.c ve file.h

	/*
		uzantısı c olan dosyaya implementation file deniyor.
		dot c file  .c file (file1.c)
		yada code file

		bu dosyada global değişkenler ve fonksiyonların tanımı var.

		Uzantısı h olan (file1.h)
		header yada başlık dosyası.file1.c deki fonksiyonların bildirimleri file1.h isimli dosyada.

		main içersinden .h olan dosya içerisindeki func() ı kullanmak istiyoruz(main.c).
		bunun için main dosyasından .h olan dosyayı include etmek gerekiyor.
		yani #include file1.h(bildirimler burada)
		 

		header file içeriği
		1 fonksiyon bildirimleri
		2 global değişken bildirimleri
		3 preprocessor komutları
			macro tanımları
		4 tüm fonksiyon bildirimleri tanımları.
		...

		printf fonksiyonunu derlemişler ve derlenmiş halini bize veriyorlar derleyiciler.
		stdio.h da printf in bildirimi var :)


	*/

	//ARMSTRONG ve PERFECT sayılar ödev.

	return 0;
}