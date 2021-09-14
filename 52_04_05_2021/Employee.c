#define _CRT_SECURE_NO_WARNINGS
#include "Employee.h"
#include <string.h>
#include "nutility.h"
#include <stdlib.h>
#include <stdio.h>

Employee* set_employee_random(Employee *p)
{
	p->mno = rand() % 10000;
	strcpy(p->mname, rname()); // rname yeni eklendi.random name üretiyor bir arrayden
	strcpy(p->msurname, rsurname()); 
	strcpy(p->mtown, rtown()); 
	set_date_random(&p->mdate); // mdate Date türünden bir birlik.

	return p;
}


void print_employee(const Employee* p)
{
	printf("%-5d  %-16s  %-18s  %-16s : ", p->mno, p->mname, p->msurname, p->mtown);
	print_date(&p->mdate); // mdate zaten Date türünden bir struct. 
}


int cmp_employee_by_no(const Employee* p1, const Employee* p2)
{
	return p1->mno - p2->mno;
}


int cmp_employee_by_name(const Employee*p1, const Employee*p2)
{
	return strcmp(p1->mname, p2->mname);
}

int cmp_employee_by_surname(const Employee* p1, const Employee* p2)
{
	return strcmp(p1->msurname, p2->msurname);
}


int cmp_employee_by_town(const Employee* p1, const Employee* p2)
{
	return strcmp(p1->mtown, p2->mtown);
}

int cmp_employee_by_date(const Employee* p1, const Employee* p2)
{
	return cmp_date(&p1->mdate, &p2->mdate);
}

