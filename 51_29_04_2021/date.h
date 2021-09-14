#ifndef DATE_H
#define DATE_H

//BİR MODÜL YAZILIYOR.
//BU İŞLEMLER TARİH İŞLEMLERİ İÇİN KULLANILACAK BİR MODÜL.
//MÜMKÜN OLDUĞU KADAR OOP TARZI BİR MODEL OLUŞTURULACAK.YANİ STRUCT ELEMANLARINI CLİENT KODDAN
//GİZLEYECEĞİZ YADA CLİENT KOD BUNLARI KULLANMAYACAK.INCOMPLETE TYPE BURADA ÖNEMLİ.
//YAPININ ELEMANLARINI CLİENT KOD KULLANMAZSA, CLİENT KODLAR BUNU KULLANMADIĞI İÇİN KÜTÜPHANEDE
//DEĞİŞİKLİK YAPILINCA CLİENT KODLARDA BİR DEĞİŞİKLİK YAPMAYA GEREK KALMAYACAK.


//1. Opsiyon
// Yapının bildirimini hiç göstermem.
// Yapıyı incomplete type olarak kullanırım.

//2. Opsiyon
// Diğer seçenek yapıyı complete type olarak bildirip 
// bildirimini başlık dosyasına koyarım. Biz böyle yapacağız.

//3. Opsiyon
// Yapıyı yine complete type olarak bildirip içine void pointer veri elemanı koyarım.
// yapının elemanlarına ilk eleman vermek dahil herşey fonksiyonla yapılacak





typedef struct {	
	int md;
	int mm;
	int my; 
}Date;


//setters - set functions
Date* set_date(Date *, int d, int m, int y);
Date* set_date_today(Date*);
Date* set_date_from_str(Date *, const char *p);
Date* set_date_random(Date*);
Date* set_month(Date*, int mon);
Date* set_year(Date*, int year);
Date* set_month_day(Date*, int day);

// get functions - getters - accessors
// unility functions
int get_year(const Date*);
int get_month(const Date*);
int get_month_day(const Date*);
int get_year_day(const Date*);
int get_week_day(const Date*);


int cmp_date(const Date*, const Date*);
int date_diff(const Date*, const Date*);
Date* ndays_date(Date* pdest, const Date* psource, int n);

//input output functions
void print_date(const Date*);
Date *scan_date(Date*);

#endif