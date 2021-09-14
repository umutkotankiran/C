#include "mylib.h"
#include <stdio.h>

static void foo(void)
{
	printf("foo cagrildi\n");
}

FPTR gfp = &foo;

void func(void)  // burada func çağrıldığında gfp() yani foo() yani foo çağrısı yapılır.
{
	gfp();
}


FPTR setfunc(FPTR f)
{
	FPTR fp = gfp;
	gfp = f;

	return fp;
}