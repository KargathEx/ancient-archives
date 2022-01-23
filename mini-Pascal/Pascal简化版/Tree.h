#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <stdlib.h>
#include <time.h>
//#include <string.h>
#include <conio.h>
#include <math.h>
#include "LytWString.h"

using namespace std;

template<typename _Type>
class TreeNode
{
public:
	_Type Data;
	TreeNode* Left;
	TreeNode* Right;
	TreeNode* Up;		//�Ǹ��ڵ�

	TreeNode()
	{
		Left=nullptr;
		Right=nullptr;
		Up=nullptr;
	}

	~TreeNode()	//����ݹ��������ν��е�?����Ӹ��ڵ�Ļ����ã�����Ӷ�������һ���ӾͶ��ˣ� �Ҳ�delete������������������?�ǵģ��໥�ݹ�Ĺ���.
	{
		if (Left) delete Left;	
		if (Right) delete Right;
	}

	LytWString ToString(LytWString Prefix , LytWString(*Conv)(_Type&))
	{
		if(this)
		{
			LytWString Result=Prefix+Conv(Data);
			if(Left||Right)
			{
				Result=Result+L"{\r\n";
				if(Left)
					Result=Result+Left->ToString(Prefix+L"  ",Tos);
				if(Right)
					Result=Result+Right->ToString(Prefix+L"  ",Tos);
				return Result+Prefix+L"}\r\n";
			}
			else return Result+L"\r\n";
		}
		else return L"";
	}
};

template <typename _Type>
class Tree
{
public:
	TreeNode<_Type>* TreeHead;

	Tree()
	{
		TreeHead=new TreeNode<_Type>;
	}

	~Tree()
	{
		if (TreeHead) delete TreeHead;
		TreeHead=0;
	}

	TreeNode<_Type>* AddUp()
	{
		TreeNode<_Type>* Temp=new TreeNode<_Type>;
		if (TreeHead!=0)
		{
			TreeHead->Up=Temp;	
			Temp->Up=0;
			Temp->Left=TreeHead;
			Temp->Right=0;
			Temp->Left->Up=Temp;
		}
		else
		{
			Temp->Up=0;
			Temp->Left=0;
			Temp->Right=0;
		}
		TreeHead=Temp;
		return Temp;
	}

	TreeNode<_Type>* AddLeft(TreeNode<_Type>* X)
	{
		if (X!=0 && X->Left==0)
		{
			TreeNode<_Type>* Temp=new TreeNode<_Type>;
			Temp->Up=X;
			X->Left=Temp;
			Temp->Left=0;
			Temp->Right=0;
			Temp->Up->Left=Temp;
			return Temp;
		}
		else return 0;
	}

	TreeNode<_Type>* AddRight(TreeNode<_Type>* X)
	{
		if (X!=0 && X->Right==0)
		{
			TreeNode<_Type>* Temp=new TreeNode<_Type>;
			Temp->Up=X;
			X->Right=Temp;
			Temp->Left=0;
			Temp->Right=0;
			Temp->Up->Right=Temp;
			return Temp;
		}
		else return 0;
	}

	TreeNode<_Type>* MoveDown(TreeNode<_Type>* X)	//�ѵ�ǰ�ڵ�����Ų�������Ҹ�����Ȼ���Լ��������,Temp->Left=X; ����Ĳ���ȷʵ����Ϊ�����һ�����������Լ��ĵ���������ӣ��š� ���ص�����Ϊ���ڵ��Op,���������ֵ�Ǹ���X�ĵ��ˣ��ѹ�line 734�ῴUp. ���up!=null,����ԱȽ�.
	{
		if (X!=0)
		{
			TreeNode<_Type>* Temp=new TreeNode<_Type>;	//�ڷǿյ�ǰ���£������µ�. ���X�������Ļ����ͰѴ˿յĸ���Ϊ��.
			if (X==TreeHead)
				TreeHead=Temp;
			if (X->Up!=0)	//���X�ĸ��ڵ㲻Ϊ�գ���������ĳ���ڵ���ӽڵ㣬���temp����һ������Ϊx����һ��,���X�����ӽڵ㣬������tempΪ�����ڵ�����ӽڵ� ��������Ϊ�ӽڵ㡣 Ȼ���X����Ϊtemp�ĺ��ӡ�		�����������ǣ�new����һ���½ڵ㣬�滻��X��λ�ã�Ȼ���X����Ϊ�����ӽڵ㡣
			{
				Temp->Up=X->Up;
				if (X->Up->Right==X) 
					Temp->Up->Right=Temp;
				else Temp->Up->Left=Temp;
				Temp->Left=X;
				Temp->Right=0;
				X->Up=Temp;
			}
			else
			{
				Temp->Up=0;		//���x�Ǹ��ڵ㣬���x����Ϊ���ڵ������.
				Temp->Left=X;
				Temp->Right=0;
				X->Up=Temp;
			}
			return Temp;
		}
		else return 0;
	}

	TreeNode<_Type>* MoveLeft(TreeNode<_Type>* X)
	{
		if (X!=0)
		{
			TreeNode<_Type>* Temp=new TreeNode<_Type>;
			if (X==TreeHead)
				TreeHead=Temp;
			if (X->Up!=0)
			{
				Temp->Up=X->Up;
				if (X->Up->Right==X) Temp->Up->Right=Temp;
				else Temp->Up->Left=Temp;
				Temp->Left=X;
				Temp->Right=0;
				X->Up=Temp;
			}
			else
			{
				Temp->Up=0;
				Temp->Left=X;
				Temp->Right=0;
				X->Up=Temp;
			}
			return Temp;
		}
		else return 0;
	}

	TreeNode<_Type>* MoveRight(TreeNode<_Type>* X)
	{
		if (X!=0)
		{
			TreeNode<_Type>* Temp=new TreeNode<_Type>;
			if (X==TreeHead)
				TreeHead=Temp;
			if (X->Up!=0)
			{
				Temp->Up=X->Up;
				Temp->Up->Left=Temp;
				Temp->Left=X;
				Temp->Right=0;
				X->Up=Temp;
			}
			else
			{
				Temp->Up=0;
				Temp->Left=0;
				Temp->Right=X;
				X->Up=Temp;
			}
			return Temp;
		}
		else return 0;
	}

	TreeNode<_Type>* KeepLeft(TreeNode<_Type>* X)
	{
		if (X->Left)
		{
			TreeNode<_Type>* Keep=X->Left;
			if (X->Right)
				delete X->Right;
			X->Right=0;
			if (X==TreeHead)
			{
				TreeHead=Keep;
				Keep->Up=0;
			}
			else
			{
				X->Left->Up=X->Up;
				if (X->Up->Left==X)
					X->Up->Left=X->Left;
				else X->Up->Right=X->Left;
			}
			delete X;
			X=0;
			return Keep;
		}
		return 0;
	}

	TreeNode<_Type>* KeepRight(TreeNode<_Type>* X)
	{
		if (X->Right)
		{
			TreeNode<_Type>* Keep=X->Right;
			if (X->Left)
				delete X->Left;

			if (X==TreeHead)
			{
				TreeHead=Keep;
				Keep->Up=0;
			}
			else
			{
				X->Right->Up=X->Up;
				if (X->Up->Left==X)
					X->Up->Left=X->Right;
				else X->Up->Right=X->Right;
			}
			delete X;
			X=0;
			return Keep;
		}
		return 0;
	}
};

#endif