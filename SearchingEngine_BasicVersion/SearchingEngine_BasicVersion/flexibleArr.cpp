#include "stdafx.h"
#include"flexibleArr.h"
#include<iostream>
#include<istream>
#include<ostream>
#include<cctype>
#include<fstream>

using std::ifstream;
using std::ostream;
using std::istream;

ostream& operator<<(ostream& os, const FlexibleArr<char>& fa) {
		os << fa.arr;
	return os;
}

istream& operator>>(istream& is, FlexibleArr<char>& fa) {
	char temp;
	fa.clear();
	temp = is.peek();
	while (temp >= -1 && temp <= 255 && isalpha(temp)) {
		is.get(temp);
		fa.add(tolower(temp));
		temp = is.peek();
	}
	fa.add('\0');
	return is;
}
