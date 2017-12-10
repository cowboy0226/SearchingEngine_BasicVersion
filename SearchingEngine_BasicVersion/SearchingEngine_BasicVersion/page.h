#pragma once

#include "flexibleArr.h"

struct Page {
	int id;
	int referred;
	int times;
	double key;
	FlexibleArr<FlexibleArr<char> > Title;
	FlexibleArr<FlexibleArr<char> > Abstract;
	Page(int i = 0,int r = 0):id(i),referred(r),times(1),key(0){}
};
