#ifndef DFAMATRIX_H
#define DFAMATRIX_H

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include "Matrix.h"
#include "Dfa.h"
#include "SomeDataType.h"

using namespace std;

class DfaMatrix
{
public:
	Matrix<int> Data;
	bool* Final; // ����Ϊ״̬����+1�����飬��¼ĳ��״̬�Ƿ��ս�״̬
	int StatusSize; // ״̬����
	int CharLinkSize; // �ַ�������

	DfaMatrix();
	DfaMatrix(const int TempStatusSize,const int TempCharLinkSize);
	void New();
	void New(const int TempStatusSize,const int TempCharLinkSize);
	void GetDfaMatrix(); // ����DFA����
	void Print();
	~DfaMatrix();
};

#endif