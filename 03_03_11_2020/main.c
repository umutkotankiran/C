/*

C de 
1 - keywordler isim olarak kullanılamaz.
2 - isimler 63 karakterlik kümenin dışına çıkamaz.

A....Z burası 26 karakter
a....z burası da 26 karkater
0-9
_ alt tire 

toplamda 63 karakter

İsimler rakam karakterleri ile başlayamaz
C case sensitive bir dildir.

Sum SUM sum SUm    bunların hepsi farklı isimler.


Bir çok varlığın ismi olabilir.

değişkenlerin - variables ismi olur
fonksiyonların - functions ismi olur.
sabitlerin - constants ismi olur
etiketlerin - tags ismi olur.
türlerin - types ismi olur.


Operatörler

Dilin işlem yaptıran tokenlarına operatör denir.
C de 45 adet operatör olur.
sizeof bir keyword olmasına rağmen bir operatördür.



---------------------------------------------------------------
---------------------------------------------------------------
---------------------------------------------------------------

TOkenlar aşağıdakiler olabilir.

Keywords
idetifiers
constants / literals
Operators
string literals
delimiters



------------------

sum += 4; -> burada 4 adet token var.

----------------

Code un yazım şekline biçimine
code layout deniyor.

---------------------------
---------------------------
---------------------------

statement ile expression farklı şeyler

expression bir ifadedir
isimlerin operatörlerin ve sabitlerib oluşturduğu bir birim.

ör
x
10
x + 5 
x + 5 > 10
Yukarıdakiler bir ifadedir.expression dur.

expressipon un değer kategorisi var.
value category
lvalue expression
rvalue expression

Object / Nesne / Bellekte bir yerden bahsediliyorsa bu bir lvalue expressiondur.
& operatörünün operandı olan expr. ler lvalue expressiondur.
mesela
x lvalue ex
5 rvalue ex
x + 5 rvalue exp.
x[4] lvalue exp.

Constant expression
derleme zamanında derleyici ifadenin değerini tam olarak hesaplayabiliyor.
mesela
10 + 80 - 40  bu bir constant exp

ama x + y değil.


Object / Nesne

int x = 10;

1001 0110
1101 1001
...

data type
programın çalışma zamanında 1 ler ve 0 lar neyi ifade ediyor. Bunun cevabı bu nesnenin türü.
memory deki 0 ve 1 lerin nasıl yorumlanacağının bilgisine nesnenin türü denir.

burada diller 2 ye ayrılır.
static type kavramına sahip diller c c++ c# java 
dynamic type kavramına sahip diller. python powershell

a - Söz konusu nesne için bellekte ne kadar yer ayrılacak
yani nesnenin storage ı yani bellekteki yeri kaç byte ?

b - bu byte taki 1 ler ve sıfırlar ne şekilde yorumlanacak

c - bu nesne hangi işlemlere sokulabilir.

Nesnenin türü aşağıdakilere de karar veriyor.

============================
============================
============================

Data Types
------------------

basic types (fundamental - default - builtin - primitive types)
user-defined types 

=============================
=============================
=============================

Decleration -> Bildirim
Statement -> Deyim / ifade

Bildirimler isimlerin ne anlama geldiğini anlatıyor.
deyimler derleyicinin kod üretmesini sağlayacak c cümlelerine denir.

expression statements 
x++;

; null statement

compound statement

{
	x++;
	y++;
	z++;		block içerisindeki deyimler compound statements
}curly brace

----------------------------------

Control statements

if
while
do while
for

switch

go to

break
continue
return

----------------

atama deyimi ifade deyiminin alt kategorisi.Tam olarak aynı şey değil
İfade deyimleri alt deyimlere ayrılır.

ifade deyimi
	boş deyim / Null statement - ;
	birleşik deyim / compound statement
	kontrol deyimi / Control statement

	Yukarıda da yazılmıştı zaten
--------------------

Nesnenin bellekteki yeri o nesnenin storage'ı dır.
Nesnenin türü de kaç byte yer kaplıyor, 1 ler ve 0 ler ne anlama geliyor, bunu yorumlar.

-----------
C de kullanılmayanlar 3 karakter

@
$
`

görüntüsü olan karakterler printable
alfa karakterler a - z A - Z arası
numeric 0-9 arası
görüntüsü olan fakat alfanumeric olmayanlar punc karakterler.

----------------------------

local isim alanı belirli bir block (function) içinde kalan alandır
tüm kaynak file ise global namespace olarak isimlendirilir.

NOT:
Global isim alanında code yazılamıyor sadece bildirim/decleration yapılabilir.

yani x = 10; ok ama x++; yazınca devamında sentaks hatası.

-----------------------------------------------
-----------------------------------------------

Undefined behavior un nedeni büyük ölçüde compiler optimization


statement ise iş yapan expressionlardır.


*/
