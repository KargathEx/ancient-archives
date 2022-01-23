#ifndef DFA_H
#define DFA_H

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include "CharClass.h"
#include "StatusEdge.h"
#include "Nfa.h"

using namespace std;

typedef StatusBase<DfaStatusNumber, EdgeMatchContent> DfaStatusBase;
typedef DfaStatusBase::EdgeBase DfaEdgeBase;
typedef Status<DfaStatusBase, DfaEdgeBase> DfaStatus;
typedef DfaStatus::Edge DfaEdge;

class Dfa
{
public:
	DfaStatus Start;
	int StatusSize; // ״̬����

	Dfa();
	void GetDfa(Nfa& NfaGraph); // ����DFA
	void Print();

private:
	Set<DfaStatusBase*> UnsettledStatus; // δ�����״̬
	Set<DfaStatusBase*> ExisentStatus; // DFA���ڵ�״̬

	void SetStatusNumber(); //����״̬���
	DfaStatusBase* NfaStatusBaseToDfa(NfaStatusBase* Object); // ��NFA״̬ת��ΪDFA״̬
	void FindCorrespondingNfaStatus(Set<int>& StatusNumber, Nfa& NfaGraph, Link<NfaStatusBase*>& Result); // �ṩ״̬��ţ��ҵ�ĳ��DFA״̬����Ӧ��NFA״̬
	DfaStatusBase* IsExisentStatus(Set<int>& StatusNumber, bool Final); // ĳ��״̬�Ƿ������DFA
};

#endif