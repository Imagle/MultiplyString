# include "stdafx.h"
#include <cstring>
#include <iostream>

using namespace std;



string BigNumPlus(string ss, string tt){
	string ret;
	if (ss.size() <= 0 || tt.size() <= 0) return ss;
	int nTokenOver = 0;
	int len1 = ss.size();
	int len2 = tt.size();
	const char *s = ss.c_str();
	const char *t = tt.c_str();
	if (len1 < len2){
		len1 = len2;
		len2 = ss.size();
		s = tt.c_str();
		t = ss.c_str();
	}
	char *p = new char[len1 + 2];
	p[len1 + 1] = '\0';
	int k = 0;
	for (int i = len1 - 1, j = len2 - 1; i >= 0; --i){
		int nSum = s[i] - '0' + nTokenOver;
		if (j >= 0){
			nSum += t[j--] - '0';
		}
		if (nSum >= 10){
			if (i == 0){
				p[k++] = nSum - 10 + '0';
				p[k++] = 1 + '0';
				break;
			}
			nTokenOver = 1;
			nSum -= 10;
			p[k++] = nSum + '0';
		}
		else{
			nTokenOver = 0;
			p[k++] = nSum + '0';
		}
	}
	p[k] = '\0';
	--k;
	int i = 0;
	while (i < k){
		char c = p[i];
		p[i++] = p[k];
		p[k--] = c;
	}
	ret = string(p);
	delete[] p;
	return ret;
}

string multiply(string num1, string num2) {
	string ret;
	int len1 = num1.size();
	int len2 = num2.size();
	if (len1 <= 0 || len2 <= 0) return ret;
	bool zero = false;
	for (int i = 0; i < len2; ++i){
		if (num2[i] != '0'){
			zero = true;
			break;
		}
	}
	if (!zero) return num2;
	for (int i = 0; i < len1; ++i){
		if (num1[i] != '0'){
			zero = false;
			break;
		}
	}
	if (zero) return num1;
	ret = num1;
	string multiplier;
	if (num2[len2 - 1] == '0') multiplier = num1;
	for (int i = len2 - 1, c = 0; i >= 0; ++c, --i){
		for (int j = 0; j < (num2[i] - '0'); ++j){
			ret = BigNumPlus(ret, multiplier);
			if (c == 0 && j == 0){
				multiplier = num1;
			}
		}		
		if (i == len2 - 1 && num2[len2 - 1] == '0'){
			ret.clear();
			ret = "0";
		}
		multiplier += "0";
	}
	return ret;
}

void TestN1(){
	string s("9");
	string t("9");
	string ret;
	ret = multiply(s, t);
	//result should be 81
	printf("%s\n", ret.c_str());
}

void TestN2(){
	string s("439");
	string t("940");
	string ret;
	ret = multiply(s, t);
	//result should be 412660
	printf("%s\n", ret.c_str());
}

void TestN3(){
	string s = "0999";
	string t = "8999";
	string ret = multiply(s, t);
	//result should be 8990001
	printf("%s\n", ret.c_str());
}

void TestN4(){
	string s = "0999";
	string t = "0";
	string ret = multiply(s, t);
	//result should be 0
	printf("%s\n", ret.c_str());
}

void TestN5(){
	string s = "0";
	string t = "99";
	string ret = multiply(s, t);
	//result should be 0
	printf("%s\n", ret.c_str());
}

void TestN6(){
	string s = "0";
	string t = "0";
	string ret = multiply(s, t);
	//result should be 0
	printf("%s\n", ret.c_str());
}

void TestN7(){
	string s = "120056";
	string t = "789654";
	string ret = multiply(s, t);
	//result should be 94802700624
	printf("%s\n", ret.c_str());
}

void TestN8(){
	string s = "120056";
	string t = "78960";
	string ret = multiply(s, t);
	//result should be 9479621760
	printf("%s\n", ret.c_str());
}

void TestN9(){
	string s = "120056";
	string t = "7896504";
	string ret = multiply(s, t);
	//result should be 948022684224
	printf("%s\n", ret.c_str());
}

int main(){
	TestN1();
	TestN2();
	TestN3();
	TestN4();
	TestN5();
	TestN6();
	TestN7();
	TestN8();
	TestN9();
	return 0;
}