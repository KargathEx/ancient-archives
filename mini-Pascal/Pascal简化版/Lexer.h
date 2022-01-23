#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include "Link.h"
#include "Regex.h"

using namespace std;

enum class RegularExpressionType
{
	regularCOMMENT,		//ע��
	regularSTRING,		//�ַ���
	regularINTEGER,		//����
	regularREAL,		//������
	regularID,			//��ʶ��
	regularOPERATOR,	//������
	regularSPACE,		//�ո�
	regularENTER,		//�س�
	regularERROR		//������Ϣ
};

class Token
{
public:
	int Position; //��
	LytWString Content;
	RegularExpressionType Type; //��������

	Token() :Position(0), Content(), Type() {};		//Ĭ�Ϲ��캯��
	Token(LytWString TheContent, RegularExpressionType TheType, int ThePosition);
	Token(const Token& Object);
};

class RegexToken
{
public:
	Regex* TheRegex;
	RegularExpressionType Type;
	bool Exist; //�ô����Ƿ�����Ժ�ķ����б�����

	RegexToken(LytWString Expression, RegularExpressionType TempType, bool IsExist);
	~RegexToken();
};

class Lexer //�ʷ�������
{
private:
	Link<RegexToken*> Regexs;
public:
	Link<Token*> Tokens; //��ʶ��Ĵ���
	Link<Token*> ErrorTokens; //�޷�ʶ��Ĵ���

	Lexer();
	~Lexer();
	bool IsError();
	void RunLexer(LytWString Expression);
	void Print();
};

#endif