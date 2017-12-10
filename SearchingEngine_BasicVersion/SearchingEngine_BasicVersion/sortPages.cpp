#include "stdafx.h"
#include"flexibleArr.h"
#include"page.h"

void sortPages(FlexibleArr<Page*>* pages, bool (*smallerThan)(Page*, Page*)) {
	int len = pages->getLength();
	FlexibleArr<Page*>* p = pages;
	FlexibleArr<Page*>* t = new FlexibleArr<Page*>(len+1);
	for (int seg = 1; seg <= len; seg += seg) {
		for (int start = 0; start <= len; start += 2 * seg) {
			int low = start;
			int mid = len < (start + seg) ? len : (start + seg);
			int high = len < (start + 2 * seg) ? len : (start + 2 * seg);
			int start1 = start, end1 = mid;
			int start2 = mid, end2 = high;
			int k = start;
			while (start1 < end1 && start2 < end2) {
				(*t)[k++] = smallerThan((*p)[start1], (*p)[start2]) ? (*p)[start2++] : (*p)[start1++];
			}
			while (start1 < end1) (*t)[k++] = (*p)[start1++];
			while (start2 < end2) (*t)[k++] = (*p)[start2++];
		}
		FlexibleArr<Page*>* temp = p;
		p = t;
		t = temp;
	}
	if (p != pages) {
		for (int i = 0; i < len; ++i) (*t)[i] = (*p)[i];
		delete p;
	}
	else delete t;
}

void sortByRef(FlexibleArr<Page*>* pages) {
	auto smallerThan = [](Page* p1, Page* p2) { return p1->referred < p2->referred; };
	sortPages(pages, smallerThan);
}

void sortByKey(FlexibleArr<Page*>* pages) {
	auto smallerThan = [](Page* p1, Page* p2) { return p1->key < p2->key; };
	sortPages(pages, smallerThan);
}

void sortByTimes(FlexibleArr < Page*>* pages) {
	auto smallerThan = [](Page* p1, Page* p2) { return p1->times < p2->times; };
	sortPages(pages, smallerThan);
}

