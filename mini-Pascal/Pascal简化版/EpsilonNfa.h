#ifndef EPSILONNFA_H
#define EPSILONNFA_H

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include "Tree.h"
#include "CharClass.h"
#include "StatusEdge.h"

using namespace std;

typedef StatusBase<NfaStatusNumber, EdgeMatchContent> NfaStatusBase;
typedef NfaStatusBase::EdgeBase NfaEdgeBase;
typedef Status<NfaStatusBase, NfaEdgeBase> NfaStatus;
typedef NfaStatus::Edge NfaEdge;

class EpsilonNfa
{
public:
	NfaStatus Start;
	NfaStatus End;
	int StatusSize; // ״̬����

	EpsilonNfa();
	EpsilonNfa GetEpsilonNfa(GrammarTree& ExpressionGrammarTree, CharClassLink& CharLink); //����EpsilonNfa
	void Print();

private:
	void SetStausNumber(); // ����״̬���
	EpsilonNfa BuildEpsilonNfa(TreeNode<GrammarTreeNodeData>* Temp_TreeNode, CharClassLink& CharLink);
	void Reverse(TreeNode<GrammarTreeNodeData>* Temp_TreeNode, CharClassLink& CharLink, Set<int>& CharNumber); //���� [] �е� ^
	void RemoveUnnessaryData(); // ɾ����������
	void SetFinalStatus(); // ���ý���״̬
};

#endif