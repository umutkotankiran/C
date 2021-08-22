// bir başlık dosyasında ilk yapılması gereken multiple inclusion guard
// bir başlık dosyasından birden fazla kez, aynı bildirimin tanımlanması hata olabiliyor.

// tempbel işi çözüm aşağıda.Derleyici yapıyor.std değil.
// #pragma once . pragma bir önişlemci komutu. std değil. derleyiciyi yazanlara bırakılmış ne yapılacağı
// %100 taşınabilir değil.

#ifndef NUTILITY_H
#define NUTILITY_H

#define		isleap(y)		((y) % == 0 && ((y) % 100 != 0 || (y) % 400  == 0))

int		ndigit(int);
int		isprime(int);
void	sleep(int millisecond);
void	putline(void);
void	clear_input_buffer(void);


#endif