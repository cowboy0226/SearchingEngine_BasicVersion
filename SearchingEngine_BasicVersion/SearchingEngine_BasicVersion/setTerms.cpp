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
using std::ofstream;

FlexibleArr<char> TITLE("title", 6);
FlexibleArr<char> ABSTRACT("abstract", 9);

void setTerms(char* fname, HashTable<FlexibleArr<char>, Term>& termTable, FlexibleArr<Page>& PagesTotal) {
	cout << "setting terms...\n";
	ifstream fin;
	ofstream fout("write.txt");
	fin.open(fname);
	if (fin.is_open()) cout << fname << " open\n";
	int id = 0;
	FlexibleArr<char> temp;
	char c;
	while (fin.peek() != EOF) {
		while ((c = fin.get()) != EOF && c != '#') continue;
		if (c == EOF) break;
		fin.get();
		fin >> id;
		fout << id << endl;
		if (id % 100 == 0) cout << "pages: " << id << " num: " << termTable.getNum() << " MaxColi: " << termTable.getMaxColi() << endl;
		--id;
		fin.get();
		fin >> temp;
		while (fin >> temp) {
			if (temp.getLength() > 2) {
				Term ttemp(&PagesTotal, temp);
				termTable.getValue(temp, ttemp).addPage(PagesTotal[id]);
				fout << temp << " ";
				PagesTotal[id].Title.add(temp);
			}
			if (fin.get() == '\n') break;
		}
		fin >> temp;
		fout << "\n";
		while (fin >> temp) {
			if (temp.getLength() > 2) {
				Term ttemp(&PagesTotal, temp);
				termTable.getValue(temp, ttemp).addPage(PagesTotal[id]);
				fout << temp << " ";
				PagesTotal[id].Abstract.add(temp);
				//cout << temp << "  ";
			}
			if (fin.get() == '\n') break;
		}
		fout << "\n\n";
		//cout << endl;
	}
	fin.close();
}