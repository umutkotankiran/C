#pragma once

#include "Employee.h"

//HANDLE TEKNİĞİ SONRASI YAZILDI
struct List; //struct data nın elemanlarını tutacak yapı.
				//adresi de str. data. nın adresini tutacak


typedef struct List* ListHandle; // client codun birşeyden haberi olmayacak.(void * da gizleme
		// amaçlı kullanılabilirdi.)
		// bunu aşağıdaki gibide kullanabilirdik

//typedef void* ListHandle; Böyle yapsadık tabiki list handle kullanılan yerlerde aşağıdaki casting yapılacaktı.
// list *lp = (list *)h;


// ESKİDEN PARAMETRESİ OLMAYAN FONKSİYONARIN ŞİMDİ LİSTHANDLE TÜRDEN PARAMETRESİ OLACAK.
// 2 ADET DATA FONKSİYON GELECEK.

//birinci gelen create_List

ListHandle create_list(void);
void destroy_list(ListHandle);


int	isempty(ListHandle); // liste boşmu
int get_size(ListHandle); // öğe sayısı
void push_front(ListHandle,const Employee*); // ya struct Employee; gibi bir incomplete type yazacaktık
									// ya da kütüphane include edecektik.Employee.h include
									// edildi.

void get_first(ListHandle,Employee*);
void pop_front(ListHandle); // ilk öğeyi siliyor
void display_list(ListHandle); // öğeleri print ediyor.
void make_empty(ListHandle); // listeyi boşaltıyor.



/*
	HANDLE TEKNİĞİNDEN SONRA PARAMETRELER DEĞİŞİYOR.YUKARIDA YAPILDI 

int	isempty(void); // liste boşmu
int get_size(void); // öğe sayısı
void push_front(const Employee*); // ya struct Employee; gibi bir incomplete type yazacaktık
									// ya da kütüphane include edecektik.Employee.h include
									// edildi.

void get_first(Employee*);
void pop_front(void); // ilk öğeyi siliyor
void display_list(void); // öğeleri print ediyor.
void make_empty(void); // listeyi boşaltıyor.

*/