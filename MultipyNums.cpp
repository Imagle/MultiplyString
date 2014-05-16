// MultipyNums.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <cstring>
#include <iostream>
#include <cstdio>
using namespace std;

char *BigNumPlus(char *s, char *t){
	//假设len1大于len2，并且s后面有竟可能多的空间
	if (s == NULL || t == NULL) return NULL;
	int nTokenOver = 0;
	int len1 = strlen(s);
	int len2 = strlen(t);
	bool flag = false;
	if (len1 < len2){
		len1 = len2;
		len2 = strlen(s);
		char *temp = s;
		s = t;
		t = temp;
		flag = true;
	}
	char *p = new char[len1+2];
	p[len1 + 1] = '\0';
	int k = 0;
	for (int i=len1-1, j=len2-1; i >=0; --i){
		int nSum = s[i] - '0' + nTokenOver;
		if (j >= 0){
			nSum += t[j--] - '0';
		}
		if (nSum >= 10){
			if (i == 0){
				p[k++] = nSum-10 + '0';
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
	if (flag){
		char *temp = s;
		s = t;
		t = temp;
	}
	s[k] = '\0';
	--k;
	for (int i=0; k >= 0; --k, ++i){
		s[i] = p[k];
	}
	//cout << "plus is " << s << endl;
	delete[] p;
	return s;
}

char *MultipyBigNum(char *s, char *t){
	//假设strlen(s)大于strlen(t)，并且s后面有竟可能多的空间
	int len1 = strlen(s);
	int len2 = strlen(t);
	char *multiplier = new char[len1 + len2+1];
	multiplier[0] = '\0';
	bool zero = false;
	for (int i = 0; i < len2; ++i){
		if (t[i] != '0'){
			zero = true;
			break;
		}
	}
	if (!zero) return t;
	if (t[len2 - 1] == '0'){
		char *p = s;
		int pp = 0;
		while (p && *p&& pp<len1){
			multiplier[pp++] = *p++;
		}
		multiplier[pp] = '\0';
	}
	for (int i = len2-1, c=0; i>=0; ++c,--i){
		for (int j = 0; j < (t[i] - '0'); ++j){
			BigNumPlus(s, multiplier);
			if (c==0 && j==0){
				char *p = s;
				int pp = 0;
				while (p && *p&& pp<len1){
					multiplier[pp++] = *p++;
				}
				multiplier[pp] = '\0';

			}
		}
		if (i == len2 - 1 && t[len2 - 1] == '0'){
			s[0] = '0' + 0;
			s[1] = '\0';
		}
		*(multiplier + len1 + c) = 0+'0';
		*(multiplier + len1 + c+1) = '\0';
	}
	delete[] multiplier;
	return s;
}

void Test1(){
	char s[256] = "0999";
	char *t = "8999";
	char *ret = MultipyBigNum(s, t);
	//result should be 8990001
	cout << "Test1 is " << ret << endl;
}

void Test2(){
	char s[256] = "0999";
	char *t = "0";
	char *ret = MultipyBigNum(s, t);
	//result should be 0
	cout << "Test2 is " << ret << endl;
}

void Test3(){
	char s[256] = "0";
	char *t = "99";
	char *ret = MultipyBigNum(s, t);
	//result should be 0
	cout << "Test3 is " << ret << endl;
}

void Test4(){
	char s[256] = "0";
	char *t = "0";
	char *ret = MultipyBigNum(s, t);
	//result should be 0
	cout << "Test4 is " << ret << endl;
}

void Test5(){
	char s[256] = "120056";
	char *t = "789654";
	char *ret = MultipyBigNum(s, t);
	//result should be 94802700624
	cout << "Test5 is " << ret << endl;
}

void Test6(){
	char s[256] = "120056";
	char *t = "78960";
	char *ret = MultipyBigNum(s, t);
	//result should be 9479621760
	cout << "Test6 is " << ret << endl;
}

void Test7(){
	char s[256] = "120056";
	char *t = "7896504";
	char *ret = MultipyBigNum(s, t);
	//result should be 948022684224
	cout << "Test7 is " << ret << endl;
}

int _tmain00(int argc, _TCHAR* argv[])
{
	
	Test1();
	Test2();
	Test3();
	Test4();	
	Test5();
	Test6();
	Test7();
	return 0;
}

