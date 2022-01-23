#ifndef STATUSEDGE_H
#define STATUSEDGE_H

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include "Set.h"

using namespace std;

class EdgeMatchContent // �ߵ�ƥ������
{
public:
	Set<int> Data;

	EdgeMatchContent();
	void Add(const int MatchContent);
	void Add(Set<int>& MatchContent);
};

class NfaStatusNumber // Nfa���
{
public:
	int StatusNumber;

	NfaStatusNumber();
};

class DfaStatusNumber // Dfa���
{
public:
	Set<int> NfaStatusNumberSet; // ��Ӧ��Nfa״̬���
	int StatusNumber;

	DfaStatusNumber();
	void Add(const int Temp_StatusNumber);
};

template<typename StatusNumber, typename EdgeContent>
class StatusBase
{
public:
	class EdgeBase
	{
	public:
		EdgeContent Data;
		static Link<EdgeBase*> AllEdge; // ���еı�
		StatusBase* From;
		StatusBase* To;

		EdgeBase()
		{
			From=0;
			To=0;
		}

		static void ReleaseEdge() // �ڴ����: �ͷű�
		{
			Node<EdgeBase*>* Temp=AllEdge.Head;
			while (Temp)
			{
				delete Temp->Data;
				Temp=Temp->Next;
			}
		}
	};

	Link<EdgeBase*> InEdges;
	Link<EdgeBase*> OutEdges;
	static Link<StatusBase*> AllStatus; // ���е�״̬
	bool FinalStatus;
	StatusNumber Data;

	StatusBase()
	{
		FinalStatus=0;
	}

	static void ReleaseStatus() // �ڴ����: �ͷ�״̬
	{
		Node<StatusBase*>* Temp=AllStatus.Head;
		while (Temp)
		{
			delete Temp->Data;
			Temp=Temp->Next;
		}
	}
};

template<typename StatusData, typename EdgeData>
class Status
{
public:
	class Edge
	{
	public:
		EdgeData* Data;

		Edge()
		{
			Data=0;
		}

		Edge(EdgeData* Object)
		{
			Data=Object;
		}

		void New()
		{
			Data=new EdgeData;
			EdgeData::AllEdge.AddLast()->Data=Data;
		}

		void Connect(Status& FromStatus, Status& ToStatus) // ��ӱ�����״̬FromStatus��ToStatus
		{
			New();
			FromStatus.Data->OutEdges.AddLast()->Data=Data;
			ToStatus.Data->InEdges.AddLast()->Data=Data;
			Data->From=FromStatus.Data;
			Data->To=ToStatus.Data;
		}

		void Connect(StatusData* FromStatusBase, StatusData* ToStatusBase) // ��ӱ�����״̬FromStatus��ToStatus
		{
			New();
			FromStatusBase->OutEdges.AddLast()->Data=Data;
			ToStatusBase->InEdges.AddLast()->Data=Data;
			Data->From=FromStatusBase;
			Data->To=ToStatusBase;
		}

		void CutOff() // ɾ����
		{
			Node<EdgeData*>* Temp=Data->From->OutEdges.Find(Data);
			Temp->Data=0;
			Data->From->OutEdges.Delete(Temp);

			Temp=Data->To->InEdges.Find(Data);
			Temp->Data=0;
			Data->To->InEdges.Delete(Temp);
		}

	};

	StatusData* Data;

	Status()
	{
		Data=0;
	}

	Status(StatusData* Object)
	{
		Data=Object;
	}

	void New()
	{
		Data=new StatusData;
		StatusData::AllStatus.AddLast()->Data=Data;
	}
};

#endif