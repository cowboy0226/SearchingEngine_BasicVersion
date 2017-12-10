#include "stdafx.h"
#include"hashTable.h"
#include "flexibleArr.h"


unsigned int Hash(const char* str) {
	unsigned int seed = 331;
	unsigned int hash = 0;

	while (*str) {
		hash = hash * seed + (*str++);
	}

	return (hash & 0x7FFFFFFF);
}

unsigned int Hash(const FlexibleArr<char> wrd) {
	return Hash(&(wrd[0]));
}
