#include "employeelist.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	Employee data;
	struct Node* pnext;
}Node;


//	HANDLE TEKNİĞİNDEN SONRA FONKSİYONLARDA DEĞİŞİYOR.

typedef struct List {
	Node* gpfirst;
	int	gcount;
}List;

static Node* create_node(void) // buda internal linkage a ait
{
	Node* p = (Node*)malloc(sizeof(Node));
	if (!p)
	{
		fprintf(stderr, "Bellek yetersiz\n");
		exit(EXIT_FAILURE);
	}

	return p;
}

ListHandle create_list(void)
{
	ListHandle h = (ListHandle)malloc(sizeof(List)); // çünkü incomplete type olarak list *, ListHande olaratak typedef edilmiş.
	if (!h)
	{
		fprintf(stderr, "bellek yetersiz");
		exit(EXIT_FAILURE);
	}
	h->gcount = 0;
	h->gpfirst = NULL;

	return h;
}


void destroy_list(ListHandle h)
{
	make_empty(h);
	free(h);
}




int isempty(ListHandle h)
{
	//return h->gcount == 0; yada aşağıdaki gibi yazılır.
	return h->gpfirst == NULL;
}

int get_size(ListHandle h)
{
	return h->gcount;
}

void get_first(ListHandle h, Employee* p)
{
	if (!isempty(h))
	{
		fprintf(stderr, "Bos liste hatasi");
		exit(EXIT_FAILURE);
	}

	*p = h->gpfirst->data; // çok önemli burası
}


void push_front(ListHandle h,const Employee* p)
{
	Node* pnewnode = create_node();
	pnewnode->data = *p; // Node içinde Employee struct var.UNUTMA! Bu sebeple eştleniyor.
	pnewnode->pnext = h->gpfirst;
	h->gpfirst = pnewnode;
	++h->gcount;
}

void display_list(ListHandle h)
{
	for (Node* pn = h->gpfirst; pn != NULL; pn = pn->pnext) // ben while ile yapıyordum normalde
	{
		print_employee(&pn->data);// print employee ye içerisindeki datanın adresini
	}								// gönderiyorum. print_employee böyle çalışıyor
									// öncelik sırası yardımcı oluyor buarada.
	printf("-------------------------------------------------------------------\n");
}



void pop_front(ListHandle h)
{
	if (isempty(h))
	{
		fprintf(stderr, "Bos liste hatasi");
		exit(EXIT_FAILURE);
	}

	Node* ptemp = h->gpfirst;
	h->gpfirst = h->gpfirst->pnext;
	free(ptemp);
	--h->gcount;
}

void make_empty(ListHandle h)
{
	while (!isempty(h))
	{
		pop_front(h);
	}
}




/*

	HANDLE TEKNİĞİNDEN ÖNCEKİ LİBRARY.
	DEĞİŞECEKLER.

// listedeki ilk node adresini tutan global değişken.internal linkage a ait.
static Node* gpfirst = NULL;

// listedeki eleman sayısını tutuyor
int	gcount = 0;

static Node* create_node(void) // buda internal linkage a ait
{
	Node *p = (Node *)malloc(sizeof(Node));
	if (!p)
	{
		fprintf(stderr, "Bellek yetersiz\n");
		exit(EXIT_FAILURE);
	}

	return p;
}

int isempty(void)
{
	//return gcount == 0; yada aşağıdaki gibi yazılır.
	return gpfirst == NULL;
}

int get_size(void)
{
	return gcount;
}

void get_first(Employee*p)
{
	if (!isempty())
	{
		fprintf(stderr, "Bos liste hatasi");
		exit(EXIT_FAILURE);
	}

	*p = gpfirst->data; // çok önemli burası
}


void push_front(const Employee* p)
{
	Node* pnewnode = create_node();
	pnewnode->data = *p; // Node içinde Employee struct var.UNUTMA! Bu sebeple eştleniyor.
	pnewnode->pnext = gpfirst;
	gpfirst = pnewnode;
	++gcount;
}

void display_list(void)
{
	for (Node* pn = gpfirst; pn != NULL; pn= pn->pnext) // ben while ile yapıyordum normalde
	{
		print_employee(&pn->data);// print employee ye içerisindeki datanın adresini
	}								// gönderiyorum. print_employee böyle çalışıyor
									// öncelik sırası yardımcı oluyor buarada.
	printf("-------------------------------------------------------------------\n");
}


void pop_front(void)
{
	if (isempty())
	{
		fprintf(stderr, "Bos liste hatasi");
		exit(EXIT_FAILURE);
	}

	Node* ptemp = gpfirst;
	gpfirst = gpfirst->pnext;
	free(ptemp);
	--gcount;
}

void make_empty(void)
{
	while (!isempty())
	{
		pop_front();
	}
}

*/