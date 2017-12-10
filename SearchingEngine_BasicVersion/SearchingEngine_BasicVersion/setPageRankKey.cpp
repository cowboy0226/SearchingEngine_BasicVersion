#include"stdafx.h"
#include"graph.h"
#include"flexibleArr.h"
#include"page.h"
#include<iostream>
#include<fstream>
#include<cmath>

using std::cout;
using std::endl;
using std::ifstream;

FlexibleArr<FlexibleArr<int>*> A;

void setPageRankKey(FlexibleArr<Page>& PagesTotal) {
	cout << "setting PageRank key...\n";
	Graph<int, int> pages(17000);
	ifstream fin("link.txt");
	int id, ref;
	while (fin.get() != EOF) {
		fin.get();
		fin >> id;
		id--;
		A.add(new FlexibleArr<int>);
		pages.addVertex(id, 1);
		if (id % 1000 == 0) cout << "pages: " << id << endl;
		fin.get();
		fin >> ref;
		fin.get();
		for (int i = 0; i < ref; ++i) {
			int srcID;
			fin >> srcID;
			srcID--;
			A[id]->add(srcID);
			pages.addVertex(srcID, 1);
			if(!pages.addEdge(srcID, id,1)) cout << "error when add edge " << id << " " << srcID << endl;
		}
		// cout << id << "  " << ref << endl;
		//if (id > 20) break;
		while (fin.get() != '\n') continue;
	}
	fin.close();
	int num = pages.getSizeOfVertex();
	double avg = 1.0 / num;
	double* R1 = new double[num];
	double* R2 = new double[num];
	double* Outd = new double[num];
	for (int i = 0; i < num; ++i) {
		R1[i] = avg;
		Outd[i] = pages.getOutDegree(i);
	}
	int cnt = 0;
	double delta = 1.0;
	while (delta > 0.0 && cnt < 100) {
		double d = 0.0;
		delta = 0.0;
		for (int i = 0; i < num; ++i) {
			int ind = pages.getInDegree(i);
			R2[i] = 0;
			for (int j = 0; j < ind; ++j) {
				int curid = (*(A[i]))[j];
				R2[i] += R1[curid] / Outd[curid];
			}
			d += abs(R1[i]) - abs(R2[i]);
		}
		for (int i = 0; i < num; ++i) {
			R2[i] += d*avg;
			delta += abs(R2[i] - R1[i]);
		}
		++cnt;
		cout << "d: " << d << " ";
		cout << "cnt: " << cnt << " delta: " << delta << endl;
		double* temp = R1;
		R1 = R2;
		R2 = temp;
	}
	for (int i = 0; i < num; ++i) PagesTotal[i].key = R1[i];
	delete[] R1;
	delete[] R2;
	delete[] Outd;
}