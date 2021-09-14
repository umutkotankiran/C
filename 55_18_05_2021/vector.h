#ifndef VECTOR_H
#define VECTOR
#include <stdbool.h>
#include <stdint.h>

#define		DEF_CAPACITY		12
#define		NOT_FOUND			UINT32_MAX

typedef int DATATYPE;

typedef struct tagVector{
	DATATYPE* mp;
	size_t msize;
	size_t mcap;
}Vector,*HVector;


HVector create_vector(void);
HVector create_vector_with_capacity(const size_t cap);
HVector create_vector_with_array(const DATATYPE *pa,size_t size);
HVector create_filled_vector(size_t size,DATATYPE val);

bool set_capacity(HVector, size_t newcap);
bool push_back(HVector, DATATYPE val);
bool pop_back(HVector);
bool insert(HVector, size_t idx, DATATYPE val);
bool erase(HVector, size_t idx);
bool erase_val(HVector, DATATYPE val);
size_t erase_all(HVector, DATATYPE val);
size_t find(HVector, DATATYPE val);
void shrink(HVector);
void clear(HVector);
void destroy_vector(HVector);

//functional macros

#define		get_size(hvec)		((hvec)->msize)
#define		get_cap(hvec)		((hvec)->mcap)
#define		get_item(hvec,idx)		((hvec)->mp[idx])


#endif