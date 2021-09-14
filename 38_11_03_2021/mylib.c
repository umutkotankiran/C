#include <stdio.h>
#include "mylib.h"

#define		MAX_REGISTER_NO		10

FPTR gfa[MAX_REGISTER_NO];
int idx = 0;

void fregister(FPTR f)
{
	gfa[idx++] = f;
}

void func(void)
{
	printf("func cagrildi ve kayit edilmis functionlari cagiracak\n");

	for (int i = idx - 1; 0 <= i; i--)
		gfa[i]();
}