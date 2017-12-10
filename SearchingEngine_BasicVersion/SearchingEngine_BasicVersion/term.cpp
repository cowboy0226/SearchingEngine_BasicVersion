#include "stdafx.h"
#include"term.h"
#include "page.h"
#include "flexibleArr.h"
#include<iostream>

using std::cout;
using std::endl;

int Term::Bisearch(int id,int lo,int hi) {
	if (lo == hi) {
		if (pages[lo]->id == id) return lo;
		else return -1;
	}
	int mid = (lo + hi) / 2;
	int iid = pages[mid]->id;
	if (iid == id) return mid;
	else if (iid > id) return Bisearch(id, lo, mid);
	else return Bisearch(id, mid + 1, hi);
}

bool Term::addPage(Page& p) {
	int len = pages.getLength();
	if (len > 0) {
		int index = Bisearch(p.id, 0, len - 1);
		if (index > -1) {
			++(pages[index]->times);
			return true;
		}
	}
	pages.add(&p);
	return true;
}

Term Term::operator&&(const Term& t) const {
	Term temp(pages_total, word);
	temp.word.add('&');
	temp.word.add('&');
	int len = t.word.getLength();
	for (int i = 0; i < len; ++i) temp.word.add(t.word[i]);
	int len1 = pages.getLength();
	int len2 = t.pages.getLength();
	int cnt1 = 0, cnt2 = 0;
	while (cnt1 < len1 && cnt2 < len2) {
		if (pages[cnt1]->id == t.pages[cnt2]->id) {
			temp.pages.add(pages[cnt1]);
			++cnt1;
			++cnt2;
		}
		else if (pages[cnt1]->id < t.pages[cnt2]->id) {
			++cnt1;
		}
		else {
			++cnt2;
		}
	}
	return temp;
}

Term Term::operator||(const Term& t) const {
	Term temp(pages_total, word);
	temp.word.add('|');
	temp.word.add('|');
	int len = t.word.getLength();
	for (int i = 0; i < len; ++i) temp.word.add(t.word[i]);
	int len1 = pages.getLength();
	int len2 = t.pages.getLength();
	int cnt1 = 0, cnt2 = 0;
	while (cnt1 < len1 && cnt2 < len2) {
		if (pages[cnt1]->id == t.pages[cnt2]->id) {
			temp.pages.add(pages[cnt1]);
			++cnt1;
			++cnt2;
		}
		else if (pages[cnt1]->id < t.pages[cnt2]->id) {
			temp.pages.add(pages[cnt1]);
			++cnt1;
		}
		else {
			temp.pages.add(t.pages[cnt2]);
			++cnt2;
		}
	}
	if (cnt1 < len1) {
		while (cnt1 < len1) temp.pages.add(pages[cnt1++]);
	}
	if (cnt2 < len2) {
		while (cnt2 < len2) temp.pages.add(t.pages[cnt2++]);
	}
	return temp;
}

Term Term::operator!() const {
	Term temp(pages_total);
	temp.word.add('!');
	int len = word.getLength();
	for (int i = 0; i < len; ++i) temp.word.add(word[i]);
	len = (*pages_total).getLength();
	int len1 = pages.getLength();
	int cnt = 0;
	for (int i = 0; i < len; ++i) {
		if ((*pages_total)[i].id < pages[cnt]->id) temp.pages.add(&((*pages_total)[i]));
		else ++cnt;
	}
	return temp;
}
