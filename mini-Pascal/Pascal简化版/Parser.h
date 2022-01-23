#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include "Link.h"
#include "Error.h"
#include "Program.h"
#include "LytPtr.h"
#include "Lexer.h"
#include "Tree.h"

using namespace std;
//[why extern?
//[extern - ��̬���̴߳洢�ں��ⲿ���ӣ���staticֻ��һ��.
//[������ȡ����Ҳûɶ���𣬼���ǰ��...

extern LytPtr<Program> Parse(Node<Token*>* Current);	//[������ĺ������������������ģ�����? �ǵġ�
extern bool IsKeyWord(LytWString Content);				//[����Ƿ�Ϊ�ؼ���
extern bool IsDataType(LytWString Content);				//[ֱ�Ӽ���ַ�������
extern LytPtr<Program> GetProgram(Node<Token*>*& Current);		//[Parse����õĵ�һ������.
extern LytPtr<Function> GetFunction(Node<Token*>*& Current);	//
extern LytPtr<Var> GetVar(Node<Token*>*& Current);
extern LytPtr<FunctionHead> GetFunctionHead(Node<Token*>*& Current);
extern LytPtr<Statement> GetStatement(Node<Token*>*& Current);
extern LytPtr<Statement> GetAssignStatementOrSimpleStatement(Node<Token*>*& Current);
extern LytPtr<IfStatement> GetIfStatement(Node<Token*>*& Current);
extern LytPtr<WhileStatement> GetWhileDoStatement(Node<Token*>*& Current);
extern LytPtr<WhileStatement> GetDoWhileStatement(Node<Token*>*& Current);
extern LytPtr<Block> GetCompoundStatement(Node<Token*>*& Current);
extern LytPtr<ControlStatement> GetControlStatement(Node<Token*>*& Current);
extern LytPtr<ReturnStatement> GetReturnStatement(Node<Token*>*& Current);
extern LytPtr<Expression> GetExpression(Node<Token*>*& Current);
extern LytPtr<Base> GetBinaryExpression(TreeNode<LytPtr<Base>>* Current);
extern void GetBinaryExpTree(Node<Token*>*& Current, Tree<LytPtr<Base>>& BinaryTree);
extern LytPtr<Expression> GetSimpleExpression(Node<Token*>*& Current);
extern LytPtr<CallFunctionExpression> GetCallFunctionExpression(Node<Token*>*& Current);

#endif