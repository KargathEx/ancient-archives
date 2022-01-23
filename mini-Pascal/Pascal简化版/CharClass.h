#ifndef CHARCLASS_H
#define CHARCLASS_H

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include "LytWString.h"
#include "Link.h"
#include "Tree.h"
#include "SomeDataType.h"
#include "GrammarTree.h"

using namespace std;

class CharClass
{
public:
	wchar_t Start;
	wchar_t End;
	int Type;
	int Number; // ���

	CharClass();
	~CharClass();
	bool operator==(CharClass& Temp); //���Ա��Number
	bool IsCharGroup(); //�Ƿ�ΪCharGroup
};

class CharClassLink
{
public:
	Link<CharClass*> CharLink; // �ַ�������
	int Size;

	CharClassLink();
	void SetCharNumber(GrammarTree& Expression); //�����ַ������
	void Print();
	void Clear(); // ����ַ�������CharLink
	void GetCharNumber(CharClass& Temp_CharClass, Set<int>& CharNumber); // ���ַ�����Ӧ��ţ�����CharNumber
	int GetCharNumber(const GrammarTreeNodeData& Input); // �����ַ�����Ӧ���
	~CharClassLink();

private:
	void CutIn(CharClass Temp); // �����ַ���
	void GetCharClass(TreeNode<GrammarTreeNodeData>* Temp_GrammarTree); //�����ַ�������
};

#endif