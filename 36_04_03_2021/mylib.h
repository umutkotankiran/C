#pragma once

typedef void (*FPTR)(void);

void func(void);

FPTR setfunc(FPTR f);