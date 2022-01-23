#include "Parser.h"

LytPtr<Program> Parse(Node<Token*>* Current)
{
	if (Current) return GetProgram(Current);
	else return 0;
}

//���Ǵ浽map��Ȼ�����ڲ��ڣ�����ֱ�ӱȽ��ַ���.
bool IsKeyWord(LytWString Content)
{
	if (Content==L"function" || Content==L"procedure" || Content==L"var" || Content==L"integer" || Content==L"boolean" || Content==L"real" || Content==L"true" || Content==L"false" || Content==L"var" || Content==L"begin" || Content==L"end" || Content==L"if" || Content==L"then" || Content==L"else" || Content==L"while" || Content==L"do" || Content==L"return" || Content==L"break" || Content==L"continue") return true;
	else return false;
}

//ͬ��
bool IsDataType(LytWString Content)
{
	if (Content==L"integer" || Content==L"boolean" || Content==L"real") return true;
	else return false;
}

//�������һ���纯�������ﶼһ��~
LytPtr<Program> GetProgram(Node<Token*>*& Current)
{
	LytPtr<Program> Result=new Program;
	if (!Current)return 0;	
	else
	{
		LytPtr<FunctionHead> TheFunctionHead;	//������ͷ�ǹؼ���function+������ �������Щ�ŵ�һ����.
		LytPtr<Function> TheFunction;			//����������ͷ���ֲ�����������
		int Status=1;
		while (Current)
		{
			switch (Status)
			{
				case 1:
					if (Current->Data->Content==L"function" || Current->Data->Content==L"procedure") TheFunctionHead=GetFunctionHead(Current);
					else throw LytPtr<Error>(new Error(*(Current->Data),L"�������ͳ���"));
					Status=2;
					if (!Current)	//0��ǰ��һ�����������û��ֵ�ˣ���!nullptrΪ�棬��ʱ֪��ʲô�Ǻ���������.
					{
						Result->FunctionDeclarations.AddLast()->Data=new FunctionDeclaration(TheFunctionHead);
						return Result;
					}
					break;
				case 2:
					Status=1;
					if (Current->Data->Content==L";")	//0�������; ��˵����ǰ����������ᣬ������һ��׼������.
					{
						Result->FunctionDeclarations.AddLast()->Data=new FunctionDeclaration(TheFunctionHead);
						Current=Current->Next;
						if (!Current) return Result;
					}
					else if (Current->Data->Content==L"var" || Current->Data->Content==L"begin")//��ǰ��һ��Token,������һ������������
					{
						TheFunction=GetFunction(Current);		//Ϊʲô���������Ҫvar ��ͷ?
						//���� https://www.tutorialspoint.com/pascal/pascal_functions.htm varȷʵ�Ǻ������һ����.
						TheFunction->TheFunctionHead=TheFunctionHead;	//TheFunctionHead����������?
						Result->Functions.AddLast()->Data=TheFunction;
						if (!Current) return Result;
					}
					else throw LytPtr<Error>(new Error(*(Current->Data),L"��������ȱ�ٷֺ�"));
					break;
			}
		}
	}
	return 0;
}

//������Ǻ�����,û����.
LytPtr<Function> GetFunction(Node<Token*>*& Current)
{
	if (!Current) return 0;
	else
	{
		LytPtr<Function> Result=new Function;
		if (Current->Data->Content==L"var")	//https://www.tutorialspoint.com/pascal/pascal_functions.htm
		{
			if (Current->Next) Current=Current->Next;
			else throw LytPtr<Error>(new Error(*(Current->Data),L"ȱ�ٺ�����"));
			Result->TheVar=GetVar(Current);
		}
		if (!Current) throw LytPtr<Error>(new Error(Result->TheVar->Content.Tail->Data->Type,L"ȱ�ٺ�����"));
		else if (Current->Data->Content==L"begin")
		{
			Result->Body=GetCompoundStatement(Current);
			return Result;
		}
		else return 0;
	}
}

//���һ��������ô����ô�鷳 =_= ,���Var����һ��list��Variable�������������Ե���������ȫ�ֻ���Local,������һ��ѱ���������? û��TheDataType��struct��?
LytPtr<Var> GetVar(Node<Token*>*& Current)
{
	if (!Current) return 0;
	else
	{
		LytPtr<Var> Result=new Var;
		Link<Token> Ids;
		Token Type;
		int Status=1;
		while (Current)
		{
			switch (Status)
			{
				case 1:
					if (Current->Data->Type== RegularExpressionType::regularID)	//��Ϥ�Ŀ������ȳ�һ������������������������������ȷ��������.
					{
						if (IsKeyWord(Current->Data->Content)) throw LytPtr<Error>(new Error(*(Current->Data),L"var����������Ϊ�ؼ���"));
						Ids.AddLast()->Data=*(Current->Data);
						Status=2;
						if (Current->Next) Current=Current->Next;
						else throw LytPtr<Error>(new Error(*(Current->Data),L"var������ȱ������˵��"));
					}
					else throw LytPtr<Error>(new Error(*(Current->Data),L"var����������"));
					break;
				case 2:
					if (Current->Data->Content==L":")	//���ͳ���
					{
						Status=3;
						if (Current->Next) Current=Current->Next;
						else throw LytPtr<Error>(new Error(*(Current->Data),L"var������ȱ������˵��"));
					}
					else if (Current->Data->Content==L",")	//��������ֱ�ӻص�1��������ͺã�д���ķ��Ļ���������rest��ݹ���.
					{
						Status=1;
						if (Current->Next) Current=Current->Next;
						else throw LytPtr<Error>(new Error(*(Current->Data),L"var���ź�ȱ�ٱ���"));
					}
					else throw LytPtr<Error>(new Error(*(Current->Data),L"var��������ȱ��ð��"));
					break;
				case 3:
					if (Current->Data->Type== RegularExpressionType::regularID)
					{
						if (!IsDataType(Current->Data->Content)) throw LytPtr<Error>(new Error(*(Current->Data),L"var�б������ͳ���"));
						Type=*(Current->Data);
						Node<Token>* Temp=Ids.GetHead();	//Ŷ������ǣ�Ҫ��ǰ��ÿ�������Ͷ�����ȥ.
						while (Temp)
						{
							Result->Content.AddLast()->Data=new Variable(Temp->Data, Type);
							Temp=Temp->Next;
						}
						Ids.Clear();
						if (Current->Next) Current=Current->Next;
						else throw LytPtr<Error>(new Error(*(Current->Data),L"var��ȱ�ٺ�����"));
						if (Current->Data->Content==L";")	//ʣ�µĲ���:function name(argument(s): type1; argument(s): type2; ...): function_type;
						{
							Status=1;
							Current=Current->Next;
							if (!Current) return Result;
							else if (Current->Data->Content==L"begin") return Result;
						}
						else if (Current->Data->Content==L"begin") return Result;
						else Status=1;
					}
					else throw LytPtr<Error>(new Error(*(Current->Data),L"var�������ͳ���"));
					break;
			}
		}
	}
	return 0;
}

//Ȼ����Ǻ���ͷ��.. �ȵȣ��ܸо���ô��Ϥһ�������⣬�Ҷ�SimpleC��ʱ��Ҳ������.. ѧ����ɶ��?  ����Ȳ��ܣ��˺����ܺö���.
LytPtr<FunctionHead> GetFunctionHead(Node<Token*>*& Current)
{
	if (!Current) return 0;
	else
	{
		LytPtr<FunctionHead> Result=new FunctionHead;	//����һ�£�����ͷ��"����ͷ��function�ؼ��ֺʹ˺������������"
		int Status=1;
		Token Id;
		Token Type;
		while (Current)
		{
			switch(Status)
			{
				case 1:
					if (Current->Data->Content==L"function" || Current->Data->Content==L"procedure")	//����Ե��˺���ͷ�Ĺؼ���
					{
						Result->FunctionType=*(Current->Data);
						if (Current->Data->Content==L"function") Result->IsFunction=true;
						else Result->IsFunction=false;
					}
					else throw LytPtr<Error>(new Error(*(Current->Data),L"�������ͳ���"));
					Status=2;
					if (Current->Next) Current=Current->Next;
					else throw LytPtr<Error>(new Error(*(Current->Data),L"ȱ�ٺ�����"));
					break;
				case 2:		//����Ե��˺�����. regex��һ���´�����˵.
					if (Current->Data->Type!= RegularExpressionType::regularID) throw LytPtr<Error>(new Error(*(Current->Data),L"����������"));
					else if (IsKeyWord(Current->Data->Content)) throw LytPtr<Error>(new Error(*(Current->Data),L"����������Ϊ�ؼ���"));
					Result->FunctionName=*(Current->Data);
					Status=3;
					if (Current->Next) Current=Current->Next;
					else throw LytPtr<Error>(new Error(*(Current->Data),L"����"+Result->FunctionName.Content+L"ȱ�ٲ�����"));
					break;
				case 3:		//�������Ҫ?
					if (Current->Data->Content==L"(")
					{
						Status=4;
						if (Current->Next) Current=Current->Next;
						else throw LytPtr<Error>(new Error(*(Current->Data),L"����"+Result->FunctionName.Content+L"������ȱ��������"));
					}
					else throw LytPtr<Error>(new Error(*(Current->Data),L"����"+Result->FunctionName.Content+L"������ȱ��������"));
					break;
				case 4:		//Ŷ��������޲����͵ģ��������������档
					if (Current->Data->Content==L")")
					{
						Status=8;
						if (Result->IsFunction)
						{
							if (Current->Next) Current=Current->Next;
							else LytPtr<Error>(new Error(*(Current->Data),L"����"+Result->FunctionName.Content+L"ȱ�ٷ�������"));
						}
						else
						{
							Current=Current->Next;
							return Result;
						}
					}		//�в����Ĵ����֧������ѽ�� �˼ҵĸ�ʽ�ǣ��Ȳ�����������
					else if (Current->Data->Type== RegularExpressionType::regularID)
					{
						if (IsKeyWord(Current->Data->Content)) throw LytPtr<Error>(new Error(*(Current->Data),L"��������������Ϊ�ؼ���"));	//������ǲ���������?
						Id=*(Current->Data);
						Status=5;
						if (Current->Next) Current=Current->Next;
						else throw LytPtr<Error>(new Error(*(Current->Data),L"����"+Result->FunctionName.Content+L"����ȱ�ٷ�������"));	//Ӧ��������.
					}
					else throw LytPtr<Error>(new Error(*(Current->Data),L"����"+Result->FunctionName.Content+L"�������зǷ��ַ�"));
					break;
				case 5:
					//��������������������ͷ������һ������ 
					//function name(argument(s): type1; argument(s): type2; ...): function_type; ǰ�����type �����? �������ʾ˵����������ˣ����:��type1ǰ����Ǹ���
					if (Current->Data->Content==L":")
					{
						Status=6;
						if (Current->Next) Current=Current->Next;
						else throw LytPtr<Error>(new Error(*(Current->Data),L"����"+Result->FunctionName.Content+L"����ȱ������˵��"));
					}
					else throw LytPtr<Error>(new Error(*(Current->Data),L"����"+Result->FunctionName.Content+L"��������ȱ��ð��"));
					break;
				case 6:
					if (Current->Data->Type== RegularExpressionType::regularID)	//���ﴦ��type1.
					{
						if (!IsDataType(Current->Data->Content)) LytPtr<Error>(new Error(*(Current->Data),L"����"+Result->FunctionName.Content+L"�������ͳ���"));
						Type=*(Current->Data);
						Result->ParameterList.AddLast()->Data=new Parameter(Id, Type);	//�ð�����ȷʵ��Parameter�ģ�ԭ��������ո�û����.
						Status=7;		
						if (Current->Next) Current=Current->Next;
						else throw LytPtr<Error>(new Error(*(Current->Data),L"����"+Result->FunctionName.Content+L"ȱ��������"));
					}
					else throw LytPtr<Error>(new Error(*(Current->Data),L"����"+Result->FunctionName.Content+L"�������ͳ���"));
					break;
				case 7:		//Ȼ��Ϊɶ�����Ƿ��������Ĳ�����ֱ��)��? û�У�������if ����
					if (Current->Data->Content==L")")
					{
						Status=8;	//����Ѿ��պ��ˣ����ж��Ƿ�Ϊ������Ȼ�󷵻�.. ��ǰ������֧��return ����? ֻ��4 �У�Ϊʲô��? ��Ϊ4������һ���ս�״̬�ĵ���(�ϻ�..)
						if (Result->IsFunction)
						{
							if (Current->Next) Current=Current->Next;
							else throw LytPtr<Error>(new Error(*(Current->Data),L"����"+Result->FunctionName.Content+L"ȱ�ٷ�������˵��"));
						}
						else
						{
							Current=Current->Next;
							return Result;
						}
					}
					else if (Current->Data->Content==L";")	//���û���꣬������4��������ʣ�µĺ���.
					{
						Status=4;
						if (Current->Next) Current=Current->Next;
						else throw LytPtr<Error>(new Error(*(Current->Data),L"����"+Result->FunctionName.Content+L"�������зֺź�ȱ�ٲ���"));
					}
					else throw LytPtr<Error>(new Error(*(Current->Data),L"����"+Result->FunctionName.Content+L"ȱ��������"));
					break;
				case 8:
					if (Current->Data->Content==L":")	//�����Ƿ���������.
					{
						Status=9;
						if (Current->Next) Current=Current->Next;
						else throw LytPtr<Error>(new Error(*(Current->Data),L"����"+Result->FunctionName.Content+L"ȱ�ٷ�������˵��"));
					}
					else
					{
						if (Result->IsFunction) throw LytPtr<Error>(new Error(*(Current->Data),L"����"+Result->FunctionName.Content+L"�������ȱ��ð��"));
						else return Result;
					}
					break;
				case 9:
					if (Current->Data->Type== RegularExpressionType::regularID)
					{
						if (!IsDataType(Current->Data->Content)) LytPtr<Error>(new Error(*(Current->Data),L"����"+Result->FunctionName.Content+L"�������ͳ���"));
						Result->ReturnType=*(Current->Data);
						Current=Current->Next;
						return Result;
					}
					else throw LytPtr<Error>(new Error(*(Current->Data),L"����"+Result->FunctionName.Content+L"�������ͳ���"));
					break;
			}
		}
	}
	return 0;
}

//������ǰ���Щ�ۺ�������һ�����ս��,�ݹ�󷨺�
LytPtr<Statement> GetStatement(Node<Token*>*& Current)
{
	if (!Current) return 0;
	else
	{
		LytPtr<Statement> Result;
		if (Current->Data->Content==L"if")
			Result=GetIfStatement(Current);
		else if (Current->Data->Content==L"while")
			Result=GetWhileDoStatement(Current);
		else if (Current->Data->Content==L"do")
			Result=GetDoWhileStatement(Current);
		else if (Current->Data->Content==L"begin")
			Result=GetCompoundStatement(Current);
		else if (Current->Data->Content==L"return")
			Result=GetReturnStatement(Current);
		else if (Current->Data->Content==L"break" || Current->Data->Content==L"continue")
			Result=GetControlStatement(Current);
		else Result=GetAssignStatementOrSimpleStatement(Current);
		return Result;
	}
}

//�����С�ƹ�
LytPtr<Statement> GetAssignStatementOrSimpleStatement(Node<Token*>*& Current)
{
	if (!Current) return 0;
	else
	{
		LytPtr<AssignmentStatement> Result;	//��ֵ�Ǹ����?	Ŷ�����Ǹ�ֵ���ʽ������
		LytPtr<Expression> Left;
		LytPtr<Expression> Right;
		int Status=1;
		while (Current)
		{
			switch (Status)
			{
				case 1:
					Left=GetExpression(Current);	//��������ǻ�����ģ��š�
					if (Current && Current->Data->Content==L":=")
					{
						Result=new AssignmentStatement;
						Result->Left=Left;
						Status=2;
					}
					else
					{
						LytPtr<SimpleStatement> Result=new SimpleStatement;
						Result->Content=Left;
						return Result;
					}
					break;
				case 2:
					if (Current->Data->Content==L":=")
					{
						Status=3;
						Result->Operator=*(Current->Data);
						if (Current->Next) Current=Current->Next;
						else throw LytPtr<Error>(new Error(*(Current->Data),L"��ֵ���ȱ����ֵ"));
					}
					else throw LytPtr<Error>(new Error(*(Current->Data),L"��ֵ���ȱ�ٸ�ֵ��"));
					break;
				case 3:
					Result->Right=GetExpression(Current);
					return Result;
					break;
			}
		}
	}
	return 0;
}

//if else �Ķ������������ķ��������ˣ��ݹ��Ǽ��.
LytPtr<IfStatement> GetIfStatement(Node<Token*>*& Current)
{
	if (!Current) return 0;
	else
	{
		LytPtr<IfStatement> Result=new IfStatement;
		LytPtr<Expression> Condition;
		LytPtr<Statement> Then;
		LytPtr<Statement> Else;
		int Status=1;
		while (Current)
		{
			switch (Status)
			{
				case 1:
					Status=2;
					Result->IfToken=*(Current->Data);
					if (Current->Next) Current=Current->Next;
					else throw LytPtr<Error>(new Error(*(Current->Data),L"if���ȱ���������ʽ"));
					break;
				case 2:
					if (Current->Data->Content==L"(")	
					{
						Status=3;
						if (Current->Next) Current=Current->Next;
						else throw LytPtr<Error>(new Error(*(Current->Data),L"if���ȱ���������ʽ"));
					}
					else throw LytPtr<Error>(new Error(*(Current->Data),L"if����������ʽȱ��������"));
					break;
				case 3:	
					Result->Condition=GetExpression(Current);	////�����������"if���ȱ���������ʽ".
					Status=4;
					break;
				case 4:
					if (Current->Data->Content==L")")
					{
						Status=5;
						if (Current->Next) Current=Current->Next;
						else throw LytPtr<Error>(new Error(*(Current->Data),L"if���ȱ��then���"));
					}
					else throw LytPtr<Error>(new Error(*(Current->Data),L"if����������ʽȱ��������"));
					break;
				case 5:
					if (Current->Data->Content==L"then")
					{
						Status=6;
						Result->ThenToken=*(Current->Data);
						if(Current->Next) Current=Current->Next;
						else throw LytPtr<Error>(new Error(*(Current->Data),L"if���then��ȱ�����"));
					}
					else throw LytPtr<Error>(new Error(*(Current->Data),L"if���ȱ��\"then\""));
					break;
				case 6:
					Result->Then=GetStatement(Current);
					if (Current && Current->Data->Content==L"else") Status=7;
					else return Result;
					break;
				case 7:
					Status=8;
					Result->ElseToken=*(Current->Data);
					if(Current->Next) Current=Current->Next;
					else throw LytPtr<Error>(new Error(*(Current->Data),L"if���else��ȱ�����"));
					break;
				case 8:
					Result->Else=GetStatement(Current);
					return Result;
					break;
			}
		}
	}
	return 0;
}

//������һ�����.
LytPtr<WhileStatement> GetWhileDoStatement(Node<Token*>*& Current)
{
	if (!Current) return 0;
	else
	{
		LytPtr<WhileStatement> Result=new WhileStatement;
		Result->IsWhileDo=true;
		LytPtr<Expression> Condition;
		LytPtr<Statement> Do;
		int Status=1;
		while (Current)
		{
			switch (Status)
			{
				case 1:
					Status=2;
					Result->WhileToken=*(Current->Data);	//���Do�Ǽ����ֱ�����Ӧ���ӱ��ʽ��While token��ɶ�� �����ַ����ģ�
					if (Current->Next) Current=Current->Next;
					else throw LytPtr<Error>(new Error(*(Current->Data),L"while���ȱ���������ʽ"));
					break;
				case 2:
					if (Current->Data->Content==L"(")
					{
						Status=3;
						if (Current->Next) Current=Current->Next;
						else throw LytPtr<Error>(new Error(*(Current->Data),L"while���ȱ���������ʽ"));
					}
					else throw LytPtr<Error>(new Error(*(Current->Data),L"while����������ʽȱ��������"));
					break;
				case 3:
					Result->Condition=GetExpression(Current);
					Status=4;
					break;
				case 4:
					if (Current->Data->Content==L")")
					{
						Status=5;
						if (Current->Next) Current=Current->Next;
						else throw LytPtr<Error>(new Error(*(Current->Data),L"while���ȱ��do���"));
					}
					else throw LytPtr<Error>(new Error(*(Current->Data),L"while����������ʽȱ��������"));
					break;
				case 5:
					if (Current->Data->Content==L"do")
					{
						Status=6;
						Result->DoToken=*(Current->Data);	//��������������.
						if (Current->Next) Current=Current->Next;
						else throw LytPtr<Error>(new Error(*(Current->Data),L"while���do��ȱ�����"));
					}
					else throw LytPtr<Error>(new Error(*(Current->Data),L"while����������ʽȱ��\"do\""));
					break;
				case 6:
					Result->Do=GetStatement(Current);
					return Result;
					break;
			}
		}
	}
	return 0;
}

//�����Լ��ӵ�do-while
LytPtr<WhileStatement> GetDoWhileStatement(Node<Token*>*& Current)
{
	if (!Current) return 0;
	else
	{
		LytPtr<WhileStatement> Result=new WhileStatement;
		Result->IsWhileDo=false;	//do-while���Ϊ��
		LytPtr<Statement> Do;	//WhileStatement ������ṹ��
		LytPtr<Expression> Condition;
		int Status=1;
		while (Current)
		{
			switch (Status)
			{
				case 1:	//����ǰһ������һ���Ƚ�1
					Status=2;
					Result->DoToken=*(Current->Data);	//�Ե���Ϊ�ؼ��� ��Do?
					if (Current->Next) Current=Current->Next;	//���Ҳ���
					else throw LytPtr<Error>(new Error(*(Current->Data),L"dowhile���ȱ��do���"));
					break;
				case 2:
					Result->Do=GetStatement(Current);		
					//���������Do�ĳ��˹ؼ���֮��Ĳ�����? ȥ�����﷨~ �˼�pascal����û���ⶫ����..
					// https://www.programming-idioms.org/idiom/78/do-while-loop/930/pascal �������ƺ�û�У�ȥ��������ߵĲ���.
					// ���������Լ��ӵģ�ֱ�����ŶԱ��°�.. https://www.tutorialspoint.com/pascal/pascal_while_do_loop.htm
					//   while  a < 20  do �������.	����������ܵ��ǵ�ͬ�� a<20 ������䣬���.
					Status=3;
					if (!Current) throw LytPtr<Error>(new Error(Result->DoToken, L"dowhile���ȱ���������ʽ"));
					break;
				case 3:
					if (Current->Data->Content==L"while")	//Ȼ����ܺ����while.
					{
						Status=4;
						Result->WhileToken=*(Current->Data);	//���ˣ���Ȼ��ͣ�������ϣ�����ΪԴ����û�����ֱ��ʽ.. �Ѳ���do-while ��while-do ��һ�ȣ�û��лл��
						if (Current->Next) Current=Current->Next;
						else throw LytPtr<Error>(new Error(*(Current->Data),L"dowhile���ȱ���������ʽ"));
					}
					else throw LytPtr<Error>(new Error(*(Current->Data),L"dowhile���ȱ��\"while\""));
					break;
				case 4:
					if (Current->Data->Content==L"(")
					{
						Status=5;
						if (Current->Next) Current=Current->Next;
						else throw LytPtr<Error>(new Error(*(Current->Data),L"dowhile���ȱ���������ʽ"));
					}
					else throw LytPtr<Error>(new Error(*(Current->Data),L"dowhile����������ʽȱ��������"));
					break;
				case 5:
					Result->Condition=GetExpression(Current);
					Status=6;
					break;
				case 6:
					if (Current->Data->Content==L")")
					{
						Current=Current->Next;
						return Result;
					}
					else throw LytPtr<Error>(new Error(*(Current->Data),L"while����������ʽȱ��������"));
					break;
			}
		}
	}
	return 0;
}

//״̬���ǳ���
LytPtr<Block> GetCompoundStatement(Node<Token*>*& Current)
{
	if (!Current) return 0;
	else
	{
		LytPtr<Block> Result=new Block;
		int Status=1;
		while (Current)
		{
			switch (Status)
			{
				case 1:
					if (Current->Data->Content==L"begin")
					{
						Status=2;	//0 ���״̬�Ǹ���ģ� ������ж������ڼ���
						if (Current) Current=Current->Next;
						else throw LytPtr<Error>(new Error(*(Current->Data),L"����ȱ��end"));	//0 ֻ���ڶ�����bgein�ʹﵽ�ļ�ĩβ�Ż������.
					}
					else throw LytPtr<Error>(new Error(*(Current->Data),L"����ȱ��begin"));	//0 �������status=1���Ǽ�¼״̬��״̬�ģ�Ҫ���һ��������begin. ��������Ϊ2,�����´��ٵ���? ���ǣ���whileѭ������һ�ε�ʱ�������ƥ��end?
					break;
				case 2:
					if (Current->Data->Content==L"end")
					{
						Current=Current->Next;
						return Result;
					}
					else
					{
						Result->StatementList.AddLast()->Data=GetStatement(Current);	//�ǵģ�ƥ�䵽״̬2֮����begin֮�����end,���������֧��ѡ��������һ��״̬����������״̬�� ?���������Ϊֹ���ͱ���û��end. ���������Ϊ�յĻ������������curr? ��GetStatement()��ĺ����ǣ�ֱ�Ӷ��е��ۣ������һ����̬����������֪ʶ��
						Status=3;	//����������״ֵ̬��ɶ�ã� Ŷ���´ν����ʱ�� ������һ������ﶼһ�����͵���goto:state::three�ɡ�����Ķ���ֻ�ǿ��п��޵Ĵ�����.
						Token Temp;
						if (!Current) throw LytPtr<Error>(new Error(Temp,L"����ȱ��end")); //�к�		
					}
					break;
				case 3:
					if (Current->Data->Content==L";")
					{
						Status=2;
						if (Current->Next) Current=Current->Next;
						else throw LytPtr<Error>(new Error(*(Current->Data),L"����ȱ��end"));
						if (Current->Data->Content==L"end")
						{
							Current=Current->Next;
							return Result;
						}
					}
					else if (Current->Data->Content==L"end")
					{
						Current=Current->Next;
						return Result;
					}
					else throw LytPtr<Error>(new Error(*(Current->Data),L"��京�зǷ��ַ�"));
					break;
			}
		}//Ȼ��������~,�Ҿ����Լ�������Ҫ���﷨����������˼����Щ����.
	}
	return 0;
}

//����continue��break֮��Ĵ���
LytPtr<ControlStatement> GetControlStatement(Node<Token*>*& Current)
{
	if (!Current) return 0;
	else
	{
		LytPtr<ControlStatement> Result=new ControlStatement;
		if (Current->Data->Content==L"continue" || Current->Data->Content==L"break")
		{
			Result->Content=*(Current->Data);
			Current=Current->Next;	//���������������tokens[++i]������
			return Result;
		}
		else throw LytPtr<Error>(new Error(*(Current->Data),L"����������"));
	}
}

//���Ǻ���Ϥpascal�ķ���ֵ�������Щ��ʽ������ʵ�������������ʱ����.
LytPtr<ReturnStatement> GetReturnStatement(Node<Token*>*& Current)
{
	if (!Current) return 0;
	else
	{
		LytPtr<ReturnStatement> Result=new ReturnStatement;
		Result->ReturnToken=*(Current->Data);
		if (Current->Next) Current=Current->Next;
		else throw LytPtr<Error>(new Error(*(Current->Data),L"return������"));
		if (Current->Data->Content==L";" || Current->Data->Content==L"end") return Result;
		else
		{
			Result->Return=GetExpression(Current);
			return Result;
		}
	}
}

//�����ָ�����ı��ʽ����,������̿�����ͼ����ʽ��ʾ������?
LytPtr<Expression> GetExpression(Node<Token*>*& Current)
{
	if (!Current) return 0;
	else
	{
		Tree<LytPtr<Base>> BinaryTree;
		GetBinaryExpTree(Current, BinaryTree);
		LytPtr<Expression> Result=GetBinaryExpression(BinaryTree.TreeHead);
		return Result;
	}
}

//��Ԫ������Ԫ���ʽ��ɶ����? Ŷ������Ǵ���ı��������ϱߣ�����ExpTree�����ʵ�����Ȼ������������������š�
LytPtr<Base> GetBinaryExpression(TreeNode<LytPtr<Base>>* Current)
{
	if (Current->Left || Current->Right)
	{
		LytPtr<BinaryExpression> Result=new BinaryExpression;
		if (Current->Left) Result->Left=GetBinaryExpression(Current->Left);
		if (Current->Right) Result->Right=GetBinaryExpression(Current->Right);
		Result->Operator=Current->Data;
		return Result;
	}
	else
	{
		LytPtr<Expression> Result=Current->Data;
		return Result;
	}
}

//��Ԫ���ʽ�����㶨��SimpleC������ô����?
void GetBinaryExpTree(Node<Token*>*& Current, Tree<LytPtr<Base>>& BinaryTree)
{
	if (!Current) return;
	else
	{
		TreeNode<LytPtr<Base>>* Root=BinaryTree.TreeHead;
		TreeNode<LytPtr<Base>>* Present=Root;

		LytPtr<Expression> Left=GetSimpleExpression(Current);	//�������������current��ֵ��?��
		Present->Data=Left;

		while (Current)	//0 ���while��ʵ������rest()�ĵݹ����.		��һ��ѭ����ʱ��current�Ѿ���line 727��GetSimpleExpression�õ��˸��£�����ָ����Ǵ�������֮�����һ���ڵ�.
		{
			LytPtr<OperatorBase> BinaryOperator;
			if (Current->Data->Content==L"<" || Current->Data->Content==L"<=" || Current->Data->Content==L">=" || Current->Data->Content==L">" || Current->Data->Content==L"!=" || Current->Data->Content==L"=")
				BinaryOperator=new OperatorBase(*(Current->Data), opRELATION);
			else if (Current->Data->Content==L"xor")
				BinaryOperator=new OperatorBase(*(Current->Data), opXOR);
			else if (Current->Data->Content==L"or")
				BinaryOperator=new OperatorBase(*(Current->Data), opOR);
			else if(Current->Data->Content==L"and")
				BinaryOperator=new OperatorBase(*(Current->Data), opAND);
			else if(Current->Data->Content==L"+")
				BinaryOperator=new OperatorBase(*(Current->Data), opADD);
			else if(Current->Data->Content==L"-")
				BinaryOperator=new OperatorBase(*(Current->Data), opSUB);
			else if(Current->Data->Content==L"*")
				BinaryOperator=new OperatorBase(*(Current->Data), opMUL);
			else if(Current->Data->Content==L"/")
				BinaryOperator=new OperatorBase(*(Current->Data), opREAL_DIV);
			else if(Current->Data->Content==L"div")
				BinaryOperator=new OperatorBase(*(Current->Data), opDIV);
			else if(Current->Data->Content==L"mod")
				BinaryOperator=new OperatorBase(*(Current->Data), opMOD);
			else return;
			if (Current->Next) Current=Current->Next;	//���������Ǹ�ѭ���Ĳ���.
			else throw LytPtr<Error>(new Error(*(Current->Data),L"��Ԫ������ȱ���Ҳ�����"));
			LytPtr<Expression> Right=GetSimpleExpression(Current);	//�����Ƕ�nextȡ���ʽ.

			//���Present������ڵ�Ļ���Ŷ������������left,������Upһ��ʼ�ǲ����ڵ�,��ת��2 
			//ֱ���ڶ���ѭ����ʼ���Ź������ȼ�����.
			//�ڶ�Ȧ�Presentָ�����ɶ��?MoveDown()������Presentͷ������һ���ڵ㣬���Ұ����趨���˲�������
			while (Present->Up)		//������Щ���ڻ���Ϊwhileѭ����rest()��. �����ڵ�һ��֮�⣬������Ͳ��Ǽ򵥵���ɶ��. ֻҪnot null,����˵��������Ѿ���һ���������ˣ����Up��ʵ�ǲ���������������Ƚ�һ��=_=
			{
				LytPtr<OperatorBase> Op=Present->Up->Data;	//OpΪȡ������һ�εĲ������� ����ִ�У�������������Ĳ�������Op�����ȼ��󣬾�Ҫ
				if (Op->Precedence < BinaryOperator->Precedence) break;	//0�����ǰ���ʽ�����ȼ��ȶ�Ԫ��С������������
				else Present=Present->Up;								//0Present ���������Ŀ�ͷ���͸����������˼�ǣ�������ȼ��ȶ�Ԫ�Ĵ󣬾��ƶ���ǰ��λ�õ����棬����Op��Ķ����Ϳ��Բ鲻�����ˣ�������? �������λ��
			}	//��ⲻ��������ȼ�����Ҳ������ͼ������������ʲô??? �趨���ǳ˳����ڼӼ������ȼ�..


			//2 ��һ�δ�����ʱ�������Ȼ��  
			BinaryTree.MoveDown(Present)->Data = BinaryOperator;	//0��������ƶ� MoveDown()���ص����½��ĵ��ڵ㣬��ʱPresent�Ѿ���Ϊ���ӻ����Һ���. ����һ��ʼPresent����˭���Һ��ӣ�����Ӧ���Լ��������Ӱɣ���һ��? ȷʵ.
			//��ֻ����֪���������Present����Һ���֮ǰ��left���浽������?
			//���ڸô���λ�ã�ֻ��û��ָ�����˶���
			//AddRight()���ص����´������Һ��ӣ�������Ȧ����ĩ��Presentָ���Һ���.
			//�ڶ�Ȧ��ʱ����Ҫ����һ��?line 738������ʲô��˼? Ŷ��ֻҪ��ǰ�����Ĳ��������ȼ����磬Op<��һ����������
			Present=BinaryTree.AddRight(Present->Up);//��һȦ��ʱ��Presentִ�����֮��������right��. �������������ݷŵ�������?Ŷ
			Present->Data=Right;
		}	//�Ѿ�д�˸����Ӹ㶮�ˣ��Ժ���˵.
	}//Ȼ���Ԫ���ʽ�ͱ���ô�������.
}

//�򵥱��ʽ.. �����ţ����ķ���
//	SimpleExpression = Number | bool | CallFunctionExpression
LytPtr<Expression> GetSimpleExpression(Node<Token*>*& Current)
{
	if (!Current) return 0;
	else
	{
		if (Current->Data->Type== RegularExpressionType::regularINTEGER || Current->Data->Type== RegularExpressionType::regularREAL)//Number
		{
			LytPtr<LiteralConstant> Result=new LiteralConstant;
			Result->Content=*(Current->Data);
			Current=Current->Next;
			return Result;
		}
		else if (Current->Data->Content==L"true" || Current->Data->Content==L"false")	//bool
		{
			LytPtr<LiteralConstant> Result=new LiteralConstant;
			Result->Content=*(Current->Data);
			Current=Current->Next;
			return Result;
		}
		else if (Current->Data->Content==L"not" || Current->Data->Content==L"+" || Current->Data->Content==L"-")	//UnaryExpression,���..�ķ�������.
		{
			LytPtr<UnaryExpression> Result=new UnaryExpression;
			Result->Operator=*(Current->Data);
			if (Current->Next) Current=Current->Next;
			else  throw LytPtr<Error>(new Error(*(Current->Data),Result->Operator.Content+L"(һԪ)���ʽȱ�ٲ�����"));
			Result->Operand=GetSimpleExpression(Current);
			return Result;
		}
		else if (Current->Data->Type== RegularExpressionType::regularID)	//CallFunctionExpression
		{
			if (IsKeyWord(Current->Data->Content)) throw LytPtr<Error>(new Error(*(Current->Data),L"��ʶ������Ϊ�ؼ���"));
			if (Current->Next && Current->Next->Data->Content==L"(") return GetCallFunctionExpression(Current);
			else
			{
				LytPtr<VariableExpression> Result=new VariableExpression;
				Result->Id=*(Current->Data);
				Current=Current->Next;
				return Result;
			}
		}
		else if (Current->Data->Content==L"(")	//����������ʽ����Ǹ�һԪ�������õ�? �Ǹ���������ˣ��������ǵģ�
		{
			if (Current->Next) Current=Current->Next;
			else throw LytPtr<Error>(new Error(*(Current->Data),L"�������ʽ�������ź�Ϊ��"));
			LytPtr<Expression> Result=GetExpression(Current);

			Token Temp;
			if (!Current) throw LytPtr<Error>(new Error(Temp,L"�������ʽȱ��������")); //�к�
			else if (Current->Data->Content==L")")
			{
				Current=Current->Next;
				return Result;
			}
			else throw LytPtr<Error>(new Error(*(Current->Data),L"�������ʽȱ��������"));
		}
		else throw LytPtr<Error>(new Error(*(Current->Data),L"�������ʽ����"));
	}
}

//�����
LytPtr<CallFunctionExpression> GetCallFunctionExpression(Node<Token*>*& Current)
{
	if (!Current) return 0;
	else
	{
		LytPtr<CallFunctionExpression> Result=new CallFunctionExpression;
		int Status=1;
		while (Current)
		{
			switch (Status)
			{
				case 1:
					if (Current->Data->Type== RegularExpressionType::regularID)
					{
						if (IsKeyWord(Current->Data->Content)) throw LytPtr<Error>(new Error(*(Current->Data), L"����������Ϊ�ؼ���"));
						Result->FunctionName=*(Current->Data);
						Status=2;
						if (Current->Next) Current=Current->Next;
						else throw LytPtr<Error>(new Error(*(Current->Data), L"��������ȱ��ʵ�α�"));
					}
					else throw LytPtr<Error>(new Error(*(Current->Data), L"����������"));
					break;
				case 2:
					if (Current->Data->Content==L"(")
					{
						Status=3;
						if (Current->Next) Current=Current->Next;
						else throw LytPtr<Error>(new Error(*(Current->Data), L"ȱ��������"));
					}
					else throw LytPtr<Error>(new Error(*(Current->Data), L"ȱ��������"));
					break;
				case 3:
					if (Current->Data->Content==L")")
					{
						Current=Current->Next;
						return Result;
					}
					else
					{
						LytPtr<Expression> Exp=GetExpression(Current);
						Result->ArgumentList.AddLast()->Data=Exp;
						Status=4;
					}
					break;
				case 4:
					if (Current->Data->Content==L",")
					{
						Status=3;
						if (Current->Next) Current=Current->Next;
						else throw LytPtr<Error>(new Error(*(Current->Data), L"ʵ�α��ж��ź�ȱ��ʵ��"));
					}
					else if (Current->Data->Content==L")")
					{
						Current=Current->Next;
						return Result;
					}
					else throw LytPtr<Error>(new Error(*(Current->Data), L"ʵ�α��зǷ��ַ�"));
					break;
			}
		}
	}
	return 0;
}