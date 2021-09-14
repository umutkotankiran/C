#define _CRT_SECURE_NO_WARNINGS
#include "date.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define		YEARBASE	1900

#define		isleap(y)		((y) % 4 == 0 && ((y) % 100 != 0 || (y) % 400  == 0))
#define		mdays(y,m)		(daytabs[isleap(y)][m])
#define		PRIVATE			static
#define		PUBLIC			
#define		RANDOM_YEAR_MAX		2021
#define		RANDOM_YEAR_MIN		1940



//artık gün hesabı buradan yazılacak.	
PRIVATE const int daytabs[][13] = {
	{0,31,28,31,30,31,30,31,31,30,31,30,31},
	{0,31,29,31,30,31,30,31,31,30,31,30,31}
};

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------


//hata işleme anlatılmadığı için bir fonksiyon yazılacak bunu yapan.
//internal linkage da.başlık dosyasında yok.burada yaptıkki herkes tarafından kullanılabilsin.
PRIVATE int is_valid_date(int d, int m, int y);
PRIVATE Date* set(Date* p, int d, int m, int y);
PRIVATE int totaldays(const Date*);

// burası tarihin geçerliliğini sorguluyor.
// artık yıl hesabıda dahil çünkü şubat gün farklılığı var.
// bunuda hesaba katıyor.
PRIVATE int is_valid_date(int d, int m, int y)
{
	return y >= YEARBASE && m > 0 && m <= 12 && d > 0 && d <= mdays(y, m);
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------

PRIVATE Date* set(Date *p,int d, int m, int y)
{
	if (!is_valid_date(d, m, y))
	{
		fprintf(stderr, "gecersiz tarih\n");
		exit(EXIT_FAILURE);
	}

	p->md = d;
	p->mm = m;
	p->my = y;

	return p;
}


//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
 
PRIVATE int totaldays(const Date *p) // belirtilen tarihten bu güne kaç gün olduğunu buluyoruz.
{
	int sum = get_year_day(p);
	for (int i = YEARBASE; i < p->my; ++i)
	{
		sum += isleap(i) ? 366 : 365;
	}
	return sum;
}


//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------


// bu fonksiyon ÖNEMLİ !!!
PRIVATE Date* to_date(Date* p, int totaldays)
{
	int y = YEARBASE;   
	while (totaldays > (isleap(y) ? 366 : 365)) // totaldays in kaç yıl olduğuna baktı
	{
		totaldays -= (isleap(y) ? 366 : 365);
		++y;
	}
	
	int m = 1;
	while (totaldays > (mdays(y,m))) // totaldays yıldan sonra kala kısımda kaç ay olduğuna baktı.
	{
		totaldays -= mdays(y, m);
		++m;
	}

	int d = totaldays; // geri kalanda gün zaten
	return set(p, d, m, y); // bunları p ye set etti ve return etti.

}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------


// c++ ta function definitionda bile parametrelere isim vermek mecburi değil.
PUBLIC Date* set_date(Date *p, int d, int m, int y)
{
	return set(p, d, m, y); // setdate zaten aldığı Date *p yi geri döndürüyor. bunuda return ediyoruz
}									// hata olsaydı hata yazacaktı zaten.Test edilecek.


//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------


Date* set_date_today(Date* p)
{
	time_t timer;
	time(&timer);
	struct tm *tptr= localtime(&timer);

	return set(p, tptr->tm_mday, tptr->tm_mon + 1, tptr->tm_year + 1900);

}


//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------


PUBLIC Date* set_date_from_str(Date*p, const char* pstr)
{
	int d = atoi(pstr);
	int m = atoi(pstr + 3);
	int y = atoi(pstr + 6);

	return set(p, d, m, y);
}


//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------


PUBLIC Date* set_month(Date*p, int mon)
{
	return set(p, p->md, mon, p->my); // sadece ayı set ediyoruz. gün ve yıl zaten p içerisinde olan
}										// gün veyıl olarak set edildi.yani aynı kaldı.
							// doğrudan p->mon = mon denebilir ama geçerli mi geçersiz mi bunu
							// sınamamış oluruz. bu yüzden set functiona gönderiliyor.

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------



PUBLIC Date* set_year(Date*p, int year)
{
	return set(p, p->md, p->mm, year);
}


//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------


PUBLIC Date* set_month_day(Date*p, int day)
{
	return set(p, day, p->mm, p->my);
}


//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------


//SIRADA GET FUNCTIONLAR VAR

PUBLIC int get_year(const Date* p)
{
	return p->my;
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------

PUBLIC int get_month(const Date* p)
{
	return p->mm;
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------

PUBLIC int get_month_day(const Date* p)
{
	return p->md;
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------

PUBLIC int get_year_day(const Date* p)
{
	//elimizde ayların gün sayısı var. günleri dolaşıp toplayacağız.
	// o yıl içerisindeki kaçıncı günde olduğumu veriyor.
	// mesela 06 04 2021 yılın 96. günü gibi.

	int sum = p->md;
	for (int i = 1; i < p->mm; ++i)
	{
		sum += mdays(p->my, i);
	}

	return sum;
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------

PUBLIC int get_week_day(const Date* p)
{
	// Japon birinin algoritması ile haftanın günü hesaplanıyor.

	const int t[] = { 0,3,2,5,0,3,5,1,4,6,2,4 };
	int d = p->md;
	int m = p->mm;
	int y = p->my; // 0 pazar , 1 pazartesi...

	if (m < 3)
		--y;

	return ((y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7);

}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------

PUBLIC void print_date(const Date* p)
{
	static const char* const pmons[] = {
		"",
		"Ocak",
		"Subat",
		"Mart",
		"Nisan",
		"Mayis",
		"Haziran",
		"Temmuz",
		"Agustos",
		"Eylul",
		"Ekim",
		"Kasim",
		"Aralik",
	};

	static const char* const pdays[] = {
		"Pazar",
		"Pazartesi",
		"Sali",
		"Carsamba",
		"Persembe",
		"Cuma",
		"Cumartesi",
	};

	printf("%02d %s %d %s\n", p->md, pmons[p->mm], p->my, pdays[get_week_day(p)]);

}


//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------


PUBLIC Date * set_date_random(Date *p)
{
	int y = rand() % (RANDOM_YEAR_MAX - RANDOM_YEAR_MIN + 1) + RANDOM_YEAR_MIN;
	int m = rand() % 12 + 1;
	int d = rand() % (mdays(y, m)) + 1;

	return set(p, d, m, y);

}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------


PUBLIC Date *scan_date(Date* p)
{
	int d, m, y;
	(void)scanf("%d%d%d", &d, &m, &y);
	return set(p, d, m, y);
}


//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------



PUBLIC int cmp_date(const Date* p1, const Date* p2)
{
	if (p1->my != p2->my)
		return p1->my - p2->my;

	if (p1->mm != p2->mm)
		return p1->mm - p2->mm;

	return p1->md - p2->md;
}


PUBLIC int date_diff(const Date* p1, const Date* p2)
{
	return totaldays(p1) - totaldays(p2);
}


// psource tarihten n gun sonrasini pdest e atıyor.
PUBLIC Date* ndays_date(Date* pdest, const Date* psource, int n)
{
	return to_date(pdest, totaldays(psource) + n);
}












