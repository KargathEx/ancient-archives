#ifndef REGEX_H
#define REGEX_H

#include <iostream>
#include <string.h>
#include <math.h>
#include <iomanip> 
#include "LytWString.h"
#include "GrammarTree.h"
#include "EpsilonNfa.h"
#include "Nfa.h"
#include "Dfa.h"
#include "DfaMatrix.h"

using namespace std;

class Regex
{
public:

	class MatchResult
	{
	public:
		const wchar_t* Start; //ƥ��Ŀ�ʼλ�ã����ƥ��ʧ����������0
		int Length; //ƥ��ĳ���

		MatchResult();
		MatchResult(const MatchResult& Object);
		~MatchResult();
	};

	Regex();
	Regex(LytWString Expression); //��ʼ��������ʽ
	LytWString GetErrorMessage()const; //���ش�����Ϣ
	bool IsError()const; //�����Ƿ����
	MatchResult Match(const LytWString& Object); //ƥ���ַ���

private:
	LytWString ErrorMessage; //������Ϣ
	DfaMatrix DfaGraphMatrix; //DFA����
	CharClassLink CharLink; //�ַ���

	void SetErrorMessage(const LytWString ErrorInformation); //���ô�����Ϣ
	int RunDfa(const wchar_t* Input);
	void ReleaseGraph(); //�ڴ����: �ͷ�NFA��DFA
};

#endif