#include "stdafx.h"
#include"list.h"
#include"graph.h"
#include"flexibleArr.h"
#include"page.h"
#include"term.h"
#include"hashTable.h"
#include<iostream>
#include<fstream>

using std::cout;
using std::endl;
using std::ifstream;

void setPages(char* fname, FlexibleArr<Page>& PagesTotal) {
	cout << "setting pages...\n";
	ifstream fin;
	fin.open(fname);
	if (fin.is_open()) cout << fname << " opened.\n";
	// initial set of pages: PagesTotal;
	int id, ref;
	while (fin.get() != EOF) {
		fin.get();
		fin >> id;
		if (id % 1000 == 0) cout << "pages: " << id << endl;
		fin.get();
		fin >> ref;
		// cout << id << "  " << ref << endl;
		PagesTotal.add(Page(id, ref));
		//if (id > 20) break;
		while (fin.get() != '\n') continue;
	}
	fin.close();
}