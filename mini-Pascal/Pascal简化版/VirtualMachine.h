#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include "SymbolList.h"
#include "Stack.h"

using namespace std;

class VirtualMachine			//�����
{
public:
	class StackData				//��ջ������������
	{
	public:
		DataType Type;			//��������
		struct Data
		{
			int IntegerData;	//��������
			double RealData;	//����������
			bool BooleanData;	//����������
		}Value;

		StackData();
		StackData(DataType TheType, LytWString Data);
		StackData(const StackData& Object);
	};

	VirtualMachine();
	LytWString Excuse(LytPtr<Program> TheProgram, List<InstructionSet> TheInstructionSet);	//ִ���м����

private:
	int BaseIndex;				//��ǰBaseֵ
	Stack<StackData> TheStack;	//��ջ
	SymbolList TheSymbolList;	//���ű�
	List<int> Position;			//��־��Ӧ�кţ��±�Ϊ��־��

	LytWString GetResult(VirtualMachine::StackData Data);	//��ִ�н��ת��Ϊ�ַ���
	void Initialize(LytPtr<Program> TheProgram, List<InstructionSet> TheInstructionSet);	//��ʼ�������
	void Push(InstructionSet TheInstructionSet);
	void Push(StackData Object);
	StackData Pop();
	void Add(InstructionSet TheInstructionSet);
	void Sub(InstructionSet TheInstructionSet);
	void Mul(InstructionSet TheInstructionSet);
	void RealDiv(InstructionSet TheInstructionSet);
	void Div(InstructionSet TheInstructionSet);
	void Mod(InstructionSet TheInstructionSet);
	void Negative(InstructionSet TheInstructionSet);
	void GreaterThan(InstructionSet TheInstructionSet);
	void LessThan(InstructionSet TheInstructionSet);
	void EqualGreaterThan(InstructionSet TheInstructionSet);
	void EqualLessThan(InstructionSet TheInstructionSet);
	void Equal(InstructionSet TheInstructionSet);
	void NotEqual(InstructionSet TheInstructionSet);
	void And(InstructionSet TheInstructionSet);
	void Or(InstructionSet TheInstructionSet);
	void Not(InstructionSet TheInstructionSet);
	void Xor(InstructionSet TheInstructionSet);
	void Var(InstructionSet TheInstructionSet);
	void Load(InstructionSet TheInstructionSet);
	void Store(InstructionSet TheInstructionSet);
	int Jmp(InstructionSet TheInstructionSet);
	int JmpTrue(InstructionSet TheInstructionSet);
	int JmpFalse(InstructionSet TheInstructionSet);
	int Call(InstructionSet TheInstructionSet, int Return);
	int Return_Function(InstructionSet TheInstructionSet);
	int Return_Procedure(InstructionSet TheInstructionSet);
};

#endif