#include "cArray.h"
#include <cstdlib>
#include <cstring>

cArray::cArray(void)
{
	size = GROWBY;
	count = 0;
	array = (int*)calloc(GROWBY, sizeof(int));
}

cArray::~cArray(void)
{
	free(array);
}

int cArray::GetSize() const
{
	return size;
}

int cArray::GetCount() const
{
	return count;
}

// возвращает индекс последнего добавленного элемента
// return: -1 - ни одного элемента пока не добавлено
//         0..count-1 - индекс элемента
int cArray::GetUpperBound() const
{
	return count - 1;
}

bool cArray::IsEmpty() const
{
	return count == 0;
}

void cArray::SetSize(int n)
{
	if (size == n)
		return;

	if (count > n)
		count = n;

	size = n;
	array = (int*)realloc(array, n * sizeof(int));
}

void cArray::FreeExtra()
{
	if (count == size)
		return;

	size = count;
	array = (int*)realloc(array, size * sizeof(int));
}

void cArray::RemoveAll()
{
	count = 0;

	if (size > GROWBY)
	{
		size = GROWBY;
		array = (int*)realloc(array, GROWBY * sizeof(int));
	}
}

int cArray::GetAt(int index) const
{
	return array[index];
}

void cArray::SetAt(int value, int index)
{
	array[index] = value;
}

void cArray::Add(int value)
{
	if (count == size)
	{
		size += GROWBY;
		array = (int*)realloc(array, size * sizeof(int));
	}

	array[count] = value;
	count++;
}

void cArray::Append(cArray *arr)
{
	if (arr->count == 0)
		return;

	int extra = arr->GetCount() - (this->size - this->count);

	if (extra > 0)
	{
		this->size += ((extra % GROWBY) ? (extra / GROWBY + 1) : (extra / GROWBY)) * GROWBY;
		this->array = (int*)realloc(this->array, this->size * sizeof(int));
	}

	memcpy(this->array + this->count, arr->array, arr->GetCount() * sizeof(int));
	this->count += GetCount();
}

void cArray::Copy(cArray *arr)
{
	this->count = arr->count;
	this->size = arr->size;
	array = (int*)realloc(array, this->size * sizeof(int));
	memcpy(this->array, arr->array, this->count * sizeof(int));
}

void cArray::InsertAt(int value, int index)
{
	count++;
	if (count > size)
	{
		size += GROWBY;
		array = (int*)realloc(array, size * sizeof(int));
	}
	memmove(array + index + 1, array + index, (count - index) * sizeof(int));
	array[index] = value;
}

void cArray::RemoveAt(int index)
{
	memmove(array + index + 1, array + index, (count - index - 1) * sizeof(int));
	count--;
}

int& cArray::operator[](int index)
{
	return array[index];
}