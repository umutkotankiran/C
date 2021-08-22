
#ifndef NUTILITY_H
#define NUTILITY_H

#define		isleap(y)		((y) % == 0 && ((y) % 100 != 0 || (y) % 400  == 0))
#define		randomize()		srand((unsigned)time(0))

int		ndigit(int);
int		isprime(int);
void	sleep(int millisecond);
void	putline(void);
void	clear_input_buffer(void);


#endif