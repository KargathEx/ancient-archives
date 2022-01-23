#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include "List.h"
#include "LytPtr.h"
#include "Error.h"

using namespace std;

enum DataType // Pascal�򻯰�֧�ֵ���������
{
	INTEGER,	//����
	REAL,		//������
	BOOLEAN,	//������
	NONE,
};

enum OperatorPrecedence //���������ȼ�����ֵԽ�����ȼ�Խ��
{
	opXOR=0,
	opOR=0,
	opAND=0,
	opADD=0,
	opRELATION=1,
	opSUB=2,
	opMUL=4,
	opDIV=4,		//����
	opREAL_DIV=4,	//�����������ͣ�
	opMOD=4,
};

enum Instruction //ָ�
{
	PUSH,				//��ջ
	POP,				//��ջ
	ADD,				//��
	SUB,				//��
	MUL,				//��
	REAL_DIV,			//�����������ͣ�
	DIV,				//����
	MOD,				//ȡ��
	NEGATIVE,			//ȡ��
	GREATER_THAN,		//����
	LESS_THAN,			//С��
	EQUAL_GREATER_THAN,	//���ڵ���
	EQUAL_LESS_THAN,	//С�ڵ���
	EQUAL,				//����
	NOT_EQUAL,			//����
	AND,				//��
	OR,					//��
	XOR,				//���
	NOT,				//��
	JMP,				//��������ת
	JMP_TRUE,			//���Ϊ������ת
	JMP_FALSE,			//���Ϊ������ת
	LOAD,				//��ȡ����������
	STORE,				//��������ֵ
	CALL,				//���ú���
	RETURN_FUNCTION,	//function������return���
	RETURN_PROCEDURE,	//procedure������return���
	VAR,				//��������
	FUN,				//���庯��
	POS,				//��ǣ����ֻ����9999��
};

class InstructionSet
{
public:
	Instruction TheInstruction;	//ָ�
	LytWString Operand;			//��������һ��ָ������Ӧһ��������
	DataType OperandType;		//����������������������¼
	int Position;				//�к�

	InstructionSet();
	InstructionSet(const Instruction TempInstruction, LytWString TempOperand, DataType TempOperandType, int Pos);
	InstructionSet(const InstructionSet& Object);
};

class Base
{
public:
	virtual ~Base();
	virtual LytWString ToString(LytWString Prefix)=0;	//���﷨��ת��Ϊ�ַ���

protected:
	DataType GetDataType(Token Content);	//���ݼǺŴ��ж��������ͣ�����boolean integer real
};

class OperatorBase : public Base	//������
{
public:
	DataType Type;	//��������Ӧ�Ĳ�������������
	OperatorPrecedence Precedence;	//���������ȼ�
	Token Content;	//�������ļǺŴ�
	OperatorBase();
	OperatorBase(Token TempContent, OperatorPrecedence TempPrecedence);
	OperatorBase(const OperatorBase& Object);
	virtual ~OperatorBase();
	virtual LytWString ToString(LytWString Prefix);
};

class Program;
class Function;

class Expression : public Base	//���ʽ
{
public:
	virtual ~Expression();
	virtual bool IsLeftValue()=0;	//�жϸñ��ʽ�Ƿ�ɳ�Ϊ��ֵ
	virtual LytWString ToString(LytWString Prefix)=0;
	virtual DataType GetType(LytPtr<Program> TheProgram, LytPtr<Function> TheFunction)=0;	//���ر��ʽ����
	virtual List<InstructionSet> GetInstructionSet()=0;	//�����м����
};

class PrimitiveData : public Expression	//�������ʽ
{
public:
	virtual ~PrimitiveData();
	virtual bool IsLeftValue()=0;
	virtual LytWString ToString(LytWString Prefix)=0;
	virtual DataType GetType(LytPtr<Program> TheProgram, LytPtr<Function> TheFunction)=0;
	virtual List<InstructionSet> GetInstructionSet()=0;
};

class LiteralConstant : public PrimitiveData	//�������ʽ
{
public:
	Token Content;
	DataType Type;
	
	virtual ~LiteralConstant();
	virtual bool IsLeftValue();
	virtual LytWString ToString(LytWString Prefix);
	virtual DataType GetType(LytPtr<Program> TheProgram, LytPtr<Function> TheFunction);
	virtual List<InstructionSet> GetInstructionSet();
};

class VariableExpression : public PrimitiveData	//�������ʽ
{
public:
	Token Id;	//���������ⶼû����ʼ����.. Ŷ�������������?

	virtual ~VariableExpression();
	virtual bool IsLeftValue();
	virtual LytWString ToString(LytWString Prefix);
	virtual DataType GetType(LytPtr<Program> TheProgram, LytPtr<Function> TheFunction);
	virtual List<InstructionSet> GetInstructionSet();
};

class SimpleExpression : public Expression	//�򵥱��ʽ
{
public:
	LytPtr<PrimitiveData> Content;

	virtual ~SimpleExpression();
	virtual bool IsLeftValue();
	virtual LytWString ToString(LytWString Prefix);
	virtual DataType GetType(LytPtr<Program> TheProgram, LytPtr<Function> TheFunction);
	virtual List<InstructionSet> GetInstructionSet();
};

class UnaryExpression : public Expression	//һԪ���ʽ
{
public:
	Token Operator;				//������
	LytPtr<Expression> Operand;	//������
	
	virtual ~UnaryExpression();
	virtual bool IsLeftValue();
	virtual LytWString ToString(LytWString Prefix);
	virtual DataType GetType(LytPtr<Program> TheProgram, LytPtr<Function> TheFunction);
	virtual List<InstructionSet> GetInstructionSet();
};

class BinaryExpression : public Expression	//��Ԫ���ʽ
{
public:
	LytPtr<OperatorBase> Operator;	//������
	LytPtr<Expression> Left;		//�������
	LytPtr<Expression> Right;		//�Ҳ�����
	
	virtual ~BinaryExpression();
	virtual bool IsLeftValue();
	virtual LytWString ToString(LytWString Prefix);
	virtual DataType GetType(LytPtr<Program> TheProgram, LytPtr<Function> TheFunction);
	virtual List<InstructionSet> GetInstructionSet();
};

class CallFunctionExpression : public Expression	//�������ñ��ʽ
{
public:
	Token FunctionName;						//������
	Link<LytPtr<Expression>> ArgumentList;	//������

	virtual ~CallFunctionExpression();
	virtual bool IsLeftValue();
	virtual LytWString ToString(LytWString Prefix);
	virtual DataType GetType(LytPtr<Program> TheProgram, LytPtr<Function> TheFunction);
	virtual List<InstructionSet> GetInstructionSet();
};

class Variable : public Base	//����
{
public:
	Token Id;				//��ʶ��
	Token Type;				//���ͼǺŴ�
	DataType TheDataType;	//������������
	
	Variable();
	Variable(const Token& ObjectId, const Token& ObjectType);
	Variable(const Variable& Object);
	virtual ~Variable();
	virtual bool IsLeftValue();
	virtual LytWString ToString(LytWString Prefix);
	virtual DataType GetType(LytPtr<Program> TheProgram, LytPtr<Function> TheFunction);
	virtual List<InstructionSet> GetInstructionSet();
};

class Var : public Base		//��������
{
public:
	Link<LytPtr<Variable>> Content;
	
	virtual ~Var();
	virtual LytWString ToString(LytWString Prefix);
	virtual bool CheckType(LytPtr<Program> TheProgram, LytPtr<Function> TheFunction);
	virtual List<InstructionSet> GetInstructionSet();
};

class Parameter : public Base	//���������еĲ���
{
public:
	Token Id;				//��ʶ��
	Token Type;				//����
	DataType TheDataType;	//��������������

	Parameter();
	Parameter(const Token& ObjectId, const Token& ObjectType);
	Parameter(const Parameter& Object);
	virtual ~Parameter();
	virtual LytWString ToString(LytWString Prefix);
	virtual DataType GetType(LytPtr<Program> TheProgram);
};

class FunctionHead : public Base	//����ͷ
{
public:
	bool IsFunction;						//function����ֵΪtrue��procedure����ֵΪfalse
	Token FunctionType;						//�������ͼǺŴ�
	Token FunctionName;						//�������ǺŴ�
	Link<LytPtr<Parameter>> ParameterList;	//������
	Token ReturnType;						//�������ͼǺŴ�

	virtual ~FunctionHead();
	virtual LytWString ToString(LytWString Prefix);
	virtual bool CheckType(LytPtr<Program> TheProgram);
	virtual List<InstructionSet> GetInstructionSet();
};

class Statement : public Base	//���
{
public:
	virtual ~Statement();
	virtual LytWString ToString(LytWString Prefix)=0;
	virtual bool CheckType(LytPtr<Program> TheProgram, LytPtr<Function> TheFunction)=0;	//���ͼ��
	virtual List<InstructionSet> GetInstructionSet(LytWString BeginLoop, LytWString EndLoop, int& Mark)=0;
};

class SimpleStatement : public Statement	//���ʽ���
{
public:
	LytPtr<Expression> Content;
	
	virtual ~SimpleStatement();
	virtual LytWString ToString(LytWString Prefix);
	virtual bool CheckType(LytPtr<Program> TheProgram, LytPtr<Function> TheFunction);
	virtual List<InstructionSet> GetInstructionSet(LytWString BeginLoop, LytWString EndLoop, int& Mark);
};

class AssignmentStatement : public Statement	//��ֵ���
{
public:
	Token Operator;
	LytPtr<Expression> Left;	//�������
	LytPtr<Expression> Right;	//�Ҳ�����

	virtual ~AssignmentStatement();
	virtual LytWString ToString(LytWString Prefix);
	virtual bool CheckType(LytPtr<Program> TheProgram, LytPtr<Function> TheFunction);
	virtual List<InstructionSet> GetInstructionSet(LytWString BeginLoop, LytWString EndLoop, int& Mark);
};

class IfStatement : public Statement	//if���
{
public:
	Token IfToken;
	Token ThenToken;
	Token ElseToken;
	LytPtr<Expression> Condition;	//�������ʽ
	LytPtr<Statement> Then;
	LytPtr<Statement> Else;

	virtual ~IfStatement();
	virtual LytWString ToString(LytWString Prefix);
	virtual bool CheckType(LytPtr<Program> TheProgram, LytPtr<Function> TheFunction);
	virtual List<InstructionSet> GetInstructionSet(LytWString BeginLoop, LytWString EndLoop, int& Mark);
};

class WhileStatement : public Statement	//While���
{
public:
	Token WhileToken;
	Token DoToken;
	bool IsWhileDo;					//while-do���Ϊ�棬do-while���Ϊ��
	LytPtr<Expression> Condition;	//�������ʽ
	LytPtr<Statement> Do;

	virtual ~WhileStatement();
	virtual LytWString ToString(LytWString Prefix);
	virtual bool CheckType(LytPtr<Program> TheProgram, LytPtr<Function> TheFunction);
	virtual List<InstructionSet> GetInstructionSet(LytWString BeginLoop, LytWString EndLoop, int& Mark);
};

class ControlStatement : public Statement	//��ת��䣬����break continue
{
public:
	Token Content;
	virtual ~ControlStatement();
	virtual LytWString ToString(LytWString Prefix);
	virtual bool CheckType(LytPtr<Program> TheProgram, LytPtr<Function> TheFunction);
	virtual List<InstructionSet> GetInstructionSet(LytWString BeginLoop, LytWString EndLoop, int& Mark);
};

class ReturnStatement : public Statement	//return���
{
public:
	Token ReturnToken;
	LytPtr<Expression> Return;

	virtual ~ReturnStatement();
	virtual LytWString ToString(LytWString Prefix);
	virtual bool CheckType(LytPtr<Program> TheProgram, LytPtr<Function> TheFunction);
	virtual List<InstructionSet> GetInstructionSet(LytWString BeginLoop, LytWString EndLoop, int& Mark);
};

class Block : public Statement	//����
{
public:
	Link<LytPtr<Statement>> StatementList;
	virtual ~Block();
	virtual LytWString ToString(LytWString Prefix);
	virtual bool CheckType(LytPtr<Program> TheProgram, LytPtr<Function> TheFunction);
	virtual List<InstructionSet> GetInstructionSet(LytWString BeginLoop, LytWString EndLoop, int& Mark);
};

class FunctionDeclaration	//��������
{
public:
	LytPtr<FunctionHead> Content;

	FunctionDeclaration(LytPtr<FunctionHead> Temp);
	virtual ~FunctionDeclaration();
	virtual LytWString ToString(LytWString Prefix);
	virtual bool CheckType(LytPtr<Program> TheProgram);
};

class Function : public Base	//����
{
public:
	LytPtr<FunctionHead> TheFunctionHead;	//����ͷ
	LytPtr<Var> TheVar;						//��������
	LytPtr<Block> Body;						//������
	
	virtual ~Function();
	virtual LytWString ToString(LytWString Prefix);
	virtual bool CheckType(LytPtr<Program> TheProgram, LytPtr<Function> TheFunction);
	virtual List<InstructionSet> GetInstructionSet(LytWString BeginLoop, LytWString EndLoop, int& Mark);
};

class Program : public Base	//����
{
public:
	Link<LytPtr<Function>> Functions;
	Link<LytPtr<FunctionDeclaration>> FunctionDeclarations;

	virtual ~Program();
	virtual LytWString ToString(LytWString Prefix);
	virtual bool CheckType(LytPtr<Program> TheProgram);
	virtual List<InstructionSet> GetInstructionSet();
};

#endif