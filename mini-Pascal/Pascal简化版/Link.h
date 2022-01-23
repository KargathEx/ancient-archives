#ifndef LINK_H
#define LINK_H

#include <iostream>
#include <string.h>
#include <math.h>
#include <iomanip> 

using namespace std;

template<typename _Type>
class Node
{
public:
	_Type		Data;
	Node*		Prev;
	Node*		Next;

	Node():Prev(nullptr),Next(nullptr){}
	~Node(){}
};

template <typename _Type>
class Link
{
public:
	Node<_Type>*	Head;
	Node<_Type>*	Tail;

	Link() :Head(nullptr), Tail(nullptr) {}

	~Link()
	{
		Clear();
	}

	Node<_Type>* GetHead()
	{
		return Head;
	}

	Node<_Type>* GetTail()
	{
		return Tail;
	}

	void Zero()	//ȫ����Ϊ0
	{
		Node<_Type>* Temp=Head;
		while (Temp)
		{
			Temp->Data=0;
			Temp=Temp->Next;
		}
	}

	void Copy(Link<_Type>& Object)	
	{
		Node<_Type>* Temp_Object=Object.Head;
		while (Temp_Object)
		{
			AddLast()->Data=Temp_Object->Data;	//�Ҿ�����Щ�����Ҷ����Լ�ʵ��һ������֤��ȷ��,�Լ�������̫������.
			Temp_Object=Temp_Object->Next;
		}
	}

	void Clear()/*������нڵ㣬�ǵ�delete�꣬��Ҫ�ڴ�й©*/
	{
	    while(Head!=0)
	    {
	        Node<_Type>* t=Head->Next;
	        delete Head;
	        Head=t;
        }
        Tail=0;
    }    
	Node<_Type>*    AddFirst()/*�ڿ�ͷ����һ���½ڵ㣬����*/
	{
		Node<_Type>* t=new Node<_Type>;
		t->Prev=0;
		if (Head==0)
		{
		    t->Next=0;
		    Head=t;
            Head->Prev=0;
            Head->Next=0;
            Tail=t;
            Tail->Prev=0;
            Tail->Next=0;
        }
        else 
        {
            Head->Prev=t;
            t->Next=Head;
		    Head=t;
        }
		return Head;
	}

	Node<_Type>*	AddLast()/*��ĩβ����һ���½ڵ㣬����*/
	{
		Node<_Type>* t=new Node<_Type>;
		t->Next=0;
		if (Tail==0)
		{
		    t->Prev=0;
		    Head=t;
            Head->Prev=0;
            Head->Next=0;
            Tail=t;
            Tail->Prev=0;
            Tail->Next=0;
        }
        else
        {
            Tail->Next=t;
		    t->Prev=Tail;
		    Tail=t;
        }
		return Tail;
	}

	Node<_Type>*	AddPrev(Node<_Type>* X)/*��Xǰ������һ���½ڵ㣬����*/
	{
		if (X!=0)
		{
		    Node<_Type>* t=new Node<_Type>;
		    if (X->Prev==0)
		    {
                t->Prev=0;
                X->Prev=t;
                t->Next=X;
                t->Next->Prev=t;
                Head=t;
            }    
            else
            {
                t->Prev=X->Prev;
                t->Prev->Next=t;
                X->Prev=t;
                t->Next=X;
                t->Next->Prev=t;//д�಻���ΪʲôҪŪ��û������  
            }
            return t; 
		}
		return 0;
	}

	Node<_Type>*	AddNext(Node<_Type>* X)/*��X��������һ���½ڵ㣬����*/
	{
	    if (X!=0)
	    {
	        Node<_Type>* t=new Node<_Type>;
		    if (X->Next==0)
	        {
		        t->Next=0;
                X->Next=t;
                t->Prev=X;
                t->Prev->Next=t;
                Tail=t;
            }
            else
            {
                t->Next=X->Next;
                t->Next->Prev=t;
		        X->Next=t;
	            t->Prev=X;
                t->Prev->Next=t;   
            }
		    return t;
        }
		return 0;
	}

	void Delete(Node<_Type>* X)/*ɾ��X*/
	{
	    if (X!=0)
	    {
	        if (X->Prev==0 && X->Next==0)
	            Clear();
	        else if (X->Prev==0)
	        {
	            Node<_Type>* t=Head->Next;
	            delete X;
	            t->Prev=0;
	            Head=t;
            }
            else if (X->Next==0)
            {
                Node<_Type>* t=Tail->Prev;
                delete X;
                t->Next=0;
                Tail=t;
            }
            else
            {
                X->Prev->Next=X->Next;
                X->Next->Prev=X->Prev;
                delete X;
            } 
        }
	}

	Node<_Type>* Find(const _Type& Data)/*�ҵ�data��Data�Ľڵ㣬���أ����򷵻�0*/
	{
		Node<_Type>* TempNode=Head;
		while (TempNode)
		{
			if (TempNode->Data==Data)
				return TempNode;
			else TempNode=TempNode->Next;
		}
		return 0;
	}

	bool Exists (const _Type& Data)
	{
		return Find(Data)!=0;
	}
};

#endif