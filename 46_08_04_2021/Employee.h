#pragma once

#include "date.h"

typedef struct {
	int mno;
	char mname[20];
	char msurname[20];
	char mtown[20];
	Date mdate;
}Employee;

Employee* set_employee_random(Employee*);
void print_employee(const Employee*);


int cmp_employee_by_no(const Employee*, const Employee*);
int cmp_employee_by_name(const Employee*, const Employee*);
int cmp_employee_by_surname(const Employee*, const Employee*);
int cmp_employee_by_town(const Employee*, const Employee*);
int cmp_employee_by_date(const Employee*, const Employee*);
