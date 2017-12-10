// SearchingEngine_BasicVersion.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"list.h"
#include"graph.h"
#include"flexibleArr.h"
#include"page.h"
#include"term.h"
#include"hashTable.h"
#include"stack.h"
#include<windows.h>
#include<cstdlib>
#include<cctype>
#include<iostream>
#include<istream>
#include<fstream>
#include<algorithm>
#include<ctime>

using std::cout;
using std::endl;
using std::cin;
using std::flush;
using std::ifstream;

void setTerms(char* fname, HashTable<FlexibleArr<char>, Term>& termTable, FlexibleArr<Page>& PagesTotal);
void setPages(char* fname, FlexibleArr<Page>& PagesTotal);
void setPageRankKey(FlexibleArr<Page>& PagesTotal);
void sortByRef(FlexibleArr<Page*>* pages);
void sortByKey(FlexibleArr<Page*>* pages);
void sortByTimes(FlexibleArr<Page*>* pages);
void PagesOutput(const FlexibleArr<Page*>& pages);

const int Size = 50000;
enum Mark{Word,And,Or,No,Left,Right,Wrong};

FlexibleArr<Page> PagesTotal;
HashTable<FlexibleArr<char>, Term> termTable(Size);

int main()
{
#if(1)
	setPages("link.txt", PagesTotal);
	setTerms("documents.txt", termTable, PagesTotal);
	setPageRankKey(PagesTotal);

	cout << "number of words: " << termTable.getNum() << endl;
#endif

#if(0)
	FlexibleArr<char> 
#endif
	
#if(1)
	cout << "Initialize the searching engine...\n";
	cout << "Choose how to rank the results:\n";
	cout << "r: rank by reference\n";
	cout << "f: rank by the frequency of the word appears in the paper\n";
	cout << "i: rank by the id of the paper\n";
	cout << "p: rank by PageRank\n";
	char flag = cin.get();
	while (flag != 'r' && flag != 'f' && flag != 'i' && flag != 'p') {
		cout << "Wrong input!\n";
		cout << "Choose again:\n";
		cout << "r: rank by reference\n";
		cout << "f: rank by the frequency of the word appears in the paper\n";
		cout << "i: rank by the id of the paper\n";
		cout << "p: rank by PageRank\n";
		cin.get(flag);
		while (cin.get() != '\n') continue;
	}
	while (cin.get() != '\n') continue;
	cout << "OK, the results will be ranked by ";
	if (flag == 'r') cout << "reference.\n";
	if (flag == 'f') cout << "the frequency of the word appears in the paper.\n";
	if (flag == 'i') cout << "the id of the paper.\n";
	if (flag == 'p') cout << "PageRank.\n";
	// Sleep(3000);
	while (1) {
		cout << "Use & as and, | as or, ! as no. Use () to express a statement.\n";
		cout << "Enter what you want to search:\n";

		char test;
		Stack<Term*> termStack;
		Stack<Mark> markStack;
		FlexibleArr<char> word;
		Mark mark = Mark::Word;
		Term* current = new Term(&PagesTotal);
		int cnt = 0;
		while ((test = cin.peek()) != '\n') {
			if (test == '(') {
				++cnt;
				cin.get();
			}
			else if (isalpha(test)) {
				cin >> word;
				*current = termTable.getValue(word, *current);
				termStack.push(current);
				current = new Term(&PagesTotal);
			}
			else if (test == '&') {
				cin.get();
				markStack.push(Mark::And);
			}
			else if (test == '|') {
				cin.get();
				markStack.push(Mark::Or);
			}
			else if (test == ')') {
				cin.get();
				--cnt;
				if (markStack.pop(mark)) {
					if (mark == Mark::No) {
						Term* temp;
						if (termStack.pop(temp)) {
							*current = !(*temp);
							termStack.push(current);
							delete temp;
						}
					}
					Term* term1 = new Term(&PagesTotal);
					Term* term2 = new Term(&PagesTotal);
					if (termStack.pop(term1) && termStack.pop(term2)) {
						if (mark == Mark::And) {
							*current = *term1 && *term2;
							termStack.push(current);
							delete term1;
							delete term2;
						}
						else if (mark == Mark::Or) {
							*current = *term1 || *term2;
							termStack.push(current);
							delete term1;
							delete term2;
						}
					}
				}
			}
			else {
				cout << "Wrong input!\n";
				mark = Mark::Wrong;
				while (cin.get() != '\n') continue;
				break;
			}
		}
		if (cnt != 0 || !markStack.isEmpty() || termStack.getNum() != 1) {
			cout << "Wrong input!\n";
			mark = Mark::Wrong;
		}
		if (mark != Mark::Wrong) {
			termStack.pop(current);
			FlexibleArr<Page*> result = (*current).getPages();
			delete current;
			if (flag == 'r') sortByRef(&result);
			if (flag == 'f') sortByTimes(&result);
			if (flag == 'p') sortByKey(&result);
			PagesOutput(result);
			if (result.getLength() == 0) cout << "No result!" << endl;
			else cout << result.getLength() << " results totally.\n";
		}
		while (cin.get() != '\n') continue;

		cout << "\n========================================\n\n";
		cout << "Enter q to quit, other charactor to make another search\n";
		char temp = cin.get();
		if (temp == 'q') break;
		else {
			while (cin.get() != '\n') continue;
			system("cls");
		}
	}
#endif

	return 0;
}

