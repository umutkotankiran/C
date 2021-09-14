#include "vector.h"
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

HVector create_vector_with_capacity(const size_t cap)
{
	HVector vec = (HVector)malloc(sizeof(Vector)); // ilgili bloğun bilgilerini tutacak bir struct.
	if (!vec)										// malloc ile elde edildi sadece
	{
		fprintf(stderr, "Memory hatasi\n");
		return vec;// veya return NULL;
	}

	vec->msize = 0;
	vec->mcap = cap;
	vec->mp = (DATATYPE*)malloc(cap * sizeof(DATATYPE));
	if (!vec->mp)
	{
		fprintf(stderr,"Vector allocation hatasi\n");
		free(vec);
		return NULL;
	}


	return vec;
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------


HVector create_vector(void)
{
	return create_vector_with_capacity(DEF_CAPACITY);
}



//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------


HVector create_vector_with_array(const DATATYPE* pa, size_t size)
{
	HVector vec = create_vector_with_capacity(size);
	if (!vec)
	{
		fprintf(stderr, "Vector Error\n");
		return NULL;
	}

	/*  Bu da olur ama memmove veya memcpy kullanacağım.
	int idx;
	for (size_t idx = 0; idx < size; ++idx)
	{
		vec->mp[idx] = pa[idx];
	}
	*/

	memmove(vec->mp, pa, sizeof(DATATYPE) * size);
	vec->msize = size;

	return vec;
}


//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------


HVector create_filled_vector(size_t size, DATATYPE val)
{
	HVector vec = create_vector_with_capacity(size);
	if (!vec)
	{
		fprintf(stderr, "Memory Error\n");
		return NULL;
	}
	
	// capacity set ediliyor zaten ilk çağrılan fonksiyonda

	memset(vec->mp, val, size * sizeof(DATATYPE));
	return vec;
}


bool set_capacity(HVector vec, size_t newcap)
{
	if (newcap < vec->mcap)
		return false;
	
	if (newcap == vec->mcap)
		return true;

	DATATYPE *pd = (DATATYPE*)realloc(vec->mp,newcap * sizeof(vec));
	if (!pd)
	{
		fprintf(stderr, "Capacity Set Error\n");
		return false;
	}

	vec->mp = pd;
	vec->mcap = newcap;

	return true;
}


bool push_back(HVector vec, DATATYPE val)
{
	if (vec->msize == vec->mcap && !set_capacity(vec, vec->mcap * 2))
	{
		fprintf(stderr, "Set capacity error\n");
		return false;
	}

	vec->mp[vec->msize++] = val;
	return true;
}







bool insert(HVector vec, size_t idx, DATATYPE val)
{
	if (idx > vec->msize)
		return false;

	if (vec->msize == vec->mcap && !set_capacity(vec, vec->mcap * 2))
	{
		fprintf(stderr, "Set capacity error\n");
		return false;
	}

	memmove(vec->mp + idx + 1,vec->mp + idx, (vec->msize - idx) * sizeof(DATATYPE));
	vec->mp[idx] = val;
	vec->msize++;

	return true;
}


bool erase(HVector vec, size_t idx)
{
	if (idx >= vec->msize)
		return false;

	memmove(vec->mp + idx, vec->mp + idx + 1, (vec->msize - idx - 1) * sizeof(DATATYPE));
	vec->msize--;

	return true;
}


size_t find(HVector vec, DATATYPE val)
{
	for (size_t i = 0; i < vec->msize; i++)
	{
		if (vec->mp[i] == val)
			return i;
	}
	return NOT_FOUND;
}


bool erase_val(HVector vec, DATATYPE val)
{
	size_t val_idx = find(vec,val);
	if (val_idx != NOT_FOUND)
	{
		erase(vec, val_idx);
		return true;
	}
	vec->msize--;
	
	return false;
}


size_t erase_all(HVector vec, DATATYPE val)
{
	size_t write_idx = 0;
	size_t read_idx;

	for (read_idx = 0; read_idx < vec->msize; ++read_idx)
	{
		if (vec->mp[read_idx] != val)
		{
			vec->mp[write_idx++] = vec->mp[read_idx];
		}
	}

	vec->msize = write_idx;
	return vec->msize - write_idx;
}


void shrink(HVector vec)
{
	vec->mp = (HVector)realloc(vec->mp, sizeof(DATATYPE) * vec->msize);
	
	vec->mcap = vec->msize;
	return true;
}

void clear(HVector vec)
{
	vec->msize = 0;
}

void destroy_vector(HVector vec)
{
	free(vec->mp);
	free(vec);
} 