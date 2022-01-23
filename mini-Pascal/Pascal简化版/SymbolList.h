#ifndef SYMBOLLIST_H
#define SYMBOLLIST_H

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include "List.h"
#include "LytPtr.h"
#include "Program.h"

using namespace std;

class Symbol
{
public:
	LytWString Id;
	DataType Type;

	Symbol();
	Symbol(LytWString TempId, DataType TempType);
	Symbol(const Symbol& Object);
};

class FunctionSymbolList
{
public:
	LytWString FunctionName;	//������
	int FunctionIndex;			//�������м�����е��±�
	List<LytPtr<Symbol>> ParameterList;
	List<LytPtr<Symbol>> VariableList;

	void Initialize(LytPtr<Function> TheFunction);
	const int GetMoveStep(LytWString TheId)const;	//���ر����������Base��׼�µ�ƫ������������
};

class SymbolList	//���ű�
{
public:
	List<LytPtr<FunctionSymbolList>> Data;

	void Initialize(LytPtr<Program> TheProgram);					//��ʼ��
	const int GetFunctionIndex(LytWString TheFunctionName)const;	//���غ�����Data�е��±�
};

#endif