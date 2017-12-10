#pragma once

#include "page.h"
#include "flexibleArr.h"

class Term {
private:
	FlexibleArr<Page>* pages_total;
	FlexibleArr<char> word;
	FlexibleArr<Page*> pages;
	int Bisearch(int id,int lo,int hi);
public:
	Term(FlexibleArr<Page>* pt):pages_total(pt){}
	Term(FlexibleArr<Page>* pt, const FlexibleArr<char>& fa):pages_total(pt),word(fa){}
	Term(FlexibleArr<Page>* pt, const char* cstr,int len):pages_total(pt), word(cstr,len){}
	FlexibleArr<char>& getWord() { return word; }
	FlexibleArr<Page*> getPages() { return pages; }
	const FlexibleArr<char>& getWord() const{ return word; }
	const FlexibleArr<Page*>& getPages() const{ return pages; }
	bool addPage(Page& p);
	Term operator&&(const Term& t) const;
	Term operator||(const Term& t) const;
	Term operator!() const;
	bool operator==(const FlexibleArr<char>& wrd) { return word == wrd; }
};
