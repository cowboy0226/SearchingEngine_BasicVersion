#include"stdafx.h"
#include"flexibleArr.h"
#include"page.h"
#include<iostream>

using std::cout;
using std::endl;

void PagesOutput(const FlexibleArr<Page*>& pages) {
	int num = pages.getLength();
	for (int i = 0; i < num; ++i) {
		const Page* temp = pages[i];
		int tlen = temp->Title.getLength();
		int alen = temp->Abstract.getLength();
		cout << "ID: " << temp->id << " Referred: " << temp->referred << " Key: " << temp->key << endl;
		cout << "Title: ";
		for (int i = 0; i < tlen; ++i) {
			cout << temp->Title[i] << " ";
		}
		cout << endl;
		cout << "Abstract: ";
		for (int i = 0; i < 20 && i < alen; ++i) {
			cout << temp->Abstract[i] << " ";
		}
		cout << "...\n\n";
	}
}
