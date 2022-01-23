#ifndef INTERPRET_H
#define INTERPRET_H

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include "Error.h"
#include "Lexer.h"
#include "Parser.h"
#include "VirtualMachine.h"

using namespace std;

class Interpret
{
private:
	Lexer TheLexer; // �ʷ�������
	LytPtr<Program> TheProgram; // �﷨��
	List<InstructionSet> TheInstructionSet; // �м����
	VirtualMachine TheVirtualMachine; // �����
	LytWString Result; //���н��

public:
	void Print();
	Interpret(LytWString Content);
	LytWString InstructionSetToString(); // ���м����ת�����ַ���
};

#endif