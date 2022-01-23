#ifndef NFA_H
#define NFA_H

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include "StatusEdge.h"
#include "EpsilonNfa.h"

using namespace std;

typedef StatusBase<NfaStatusNumber, EdgeMatchContent> NfaStatusBase;
typedef NfaStatusBase::EdgeBase NfaEdgeBase;
typedef Status<NfaStatusBase, NfaEdgeBase> NfaStatus;
typedef NfaStatus::Edge NfaEdge;

class Nfa
{
public:
	NfaStatus Start;
	Link<NfaStatusBase*> AvailableStatus; // ��Ч״̬
	int StatusSize; // ״̬����: ��Ч״̬����

	Nfa();
	Nfa(EpsilonNfa& EpsilonNfaGraph);
	void Initialize(EpsilonNfa& EpsilonNfaGraph);
	void GetNfa(EpsilonNfa& EpsilonNfaGraph); // ����NFA
	void Print();

private:
	void GetAvailableStatus(EpsilonNfa& EpsilonNfaGraph); // �ҵ�������Ч״̬
	bool IsEpsilonEdge(NfaEdgeBase* Object); // �ж��Ƿ�ΪEpsilon�ߣ��������κ�ƥ������
	void GetEpsilonClosure(NfaStatusBase* Temp_AvailableStatus, Set<NfaStatusBase*>& EpsilonClosure); // �ҵ�ĳ��״̬��Epsilon�հ�
	void InsertEdge(); // ��ӱ�Ҫ�ı�
	void RemoveUnnessaryData(); // ɾ����������
};

#endif