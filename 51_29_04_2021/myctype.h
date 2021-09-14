#pragma once

extern const int ct_[]; //burada indis ile tutulan verilerin isupper islower ispunct ... gibi verilerin bitsel karşılılarını üretip yazdık

//0. bit upper
#define		UPPER			1
// 1 << 1 şeklinde de yazılabilirdi aşağısı
#define		LOWER			2
#define		DIGIT			4
#define		XDIGIT			8
#define		SPACE			16
#define		PUNCT			32
#define		PRINT			64
#define		CNTRL			128
//burada macroların bitsel karşılıkları var.


#define		is_upper(c)		(ct_[c] & UPPER) // burada da ve işlemi ile eğer true dönerse gönderilen karakter uyuyor demek.
#define		is_lower(c)		(ct_[c] & LOWER)
#define		is_alpha(c)		(ct_[c] & (LOWER | UPPER))
#define		is_digit(c)		(ct_[c] & DIGIT)
#define		is_alnum(c)		(ct_[c] & (UPPER | LOWER | DIGIT))
#define		is_xdigit(c)	(ct_[c] & XDIGIT)
#define		is_space(c)		(ct_[c] & SPACE)
#define		is_punct(c)		(ct_[c] & PUNCT)
#define		is_print(c)		(ct_[c] & PRINT)
#define		is_cntrl(c)		(ct_[c] & CNTRL)