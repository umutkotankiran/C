#ifndef NUTILITY_H
#define NUTILITY_H

#include <stddef.h>

#define		isleap(y)		((y) % 4 == 0 && ((y) % 100 != 0 || (y) % 400  == 0))
#define		asize(x)		(sizeof(x) / sizeof(x[0]))
#define		sbc(x)			 sbc_[x & 255] + sbc_[x >> 8 & 255] + sbc_[x >> 16 & 255] + sbc_[x >> 24 & 255]

extern const int sbc_[];

int		ndigit(int);
int		isprime(int);
void	sleep(int millisecond);
void	putline(void);
void	clear_input_buffer(void);
void	randomize(void);
void	bitprint(int);

void	print_array(const int* p, size_t size);
void	set_random_array(int* p, size_t size);
void	sort_array(int *p, size_t size);
void	sgets(char* p);
void	swap(int *p1, int *p2);
void	reverse_array(int* p, size_t size);
int		get_max(const int* p, size_t size);
int		get_min(const int* p, size_t size);
void	get_min_max(const int* p, size_t size,int *pmax,int *pmin);
void	bsort(int* p, size_t size);
void	copy_array(int* pdest, const int* psource, int n);
void	gswap(void* vp1, void* vp2, size_t size);
void	gbsort(void* vpa, size_t size, size_t sz, int (*fp)(const void*, const void*));

char* get_log_file_name(void);

const char* rname(void);
const char* rsurname(void);
const char* rtown(void);

#endif