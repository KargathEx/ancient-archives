#ifndef GRAMMARTREE_H
#define GRAMMARTREE_H

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include "LytWString.h"
#include "Tree.h"
#include "SomeDataType.h"

using namespace std;

// A = A '|' B
// A = B
// B = BC
// B = C
// C = C '+'
// C = C '*'
// C = C '?'
// C = '(' A ')'
// C = D
// D = char
// D = '\' char
// D = '[' E ']'
// D = "[^" E ']'
// E = EF
// E = F
// F = char '-' char
// F = char
// F = '\' char

struct GrammarTreeNodeData
{
	int Type;
	wchar_t Data;
};

class GrammarTree
{
public:
	Tree<GrammarTreeNodeData> Data;
	
	GrammarTree();
	GrammarTree(const LytWString Input);
	void Initialize(const LytWString Input);
	void GetGrammarTree(); //����������ʽ�﷨��
	LytWString GetErrorMessage()const; // ���ش�����Ϣ
	bool IsError()const; // �Ƿ����

private:
	LytWString Expression; // ������ʽ
	const wchar_t* ExpressionBuffer;
	LytWString ErrorMessage; // ������Ϣ

	void SetErrorMessage(const LytWString ErrorInformation); // ���ô�����Ϣ
	TreeNode<GrammarTreeNodeData>* GetA(TreeNode<GrammarTreeNodeData>* Current);
	TreeNode<GrammarTreeNodeData>* GetB(TreeNode<GrammarTreeNodeData>* Current);
	TreeNode<GrammarTreeNodeData>* GetC(TreeNode<GrammarTreeNodeData>* Current);
	TreeNode<GrammarTreeNodeData>* GetD(TreeNode<GrammarTreeNodeData>* Current);
	TreeNode<GrammarTreeNodeData>* GetE(TreeNode<GrammarTreeNodeData>* Current);
	TreeNode<GrammarTreeNodeData>* GetF(TreeNode<GrammarTreeNodeData>* Current);
};

#endif