#ifndef NUTILITY_H
#define NUTILITY_H

#define		isleap(y)		((y) % == 0 && ((y) % 100 != 0 || (y) % 400  == 0))
#define		asize(x)		(sizeof(x) / sizeof(x[0]))

int		ndigit(int);
int		isprime(int);
void	sleep(int millisecond);
void	putline(void);
void	clear_input_buffer(void);
void	randomize(void);
void	print_array(const int* p, int size);
void	set_random_array(int* p, int size);
void	sort_array(int *p, int size);
static int		icmp(const void* vp1, const void* vp2);
void	sgets(char* p);



#endif

