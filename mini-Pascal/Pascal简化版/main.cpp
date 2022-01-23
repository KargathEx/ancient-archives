#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include "LytWString.h"
#include "File.h"
#include "Interpret.h"
//#include<filesystem>
//#include<boost/dll/runtime_symbol_info.hpp>
using namespace std;

int main(int argc , char* argv[])
 {
	setlocale(LC_ALL,"chs");
	LytString AppPath=argv[0];
	for(int i=AppPath.Size()-1;i>=0;i--)
	{
		if(AppPath[i]==L'\\')
		{
			AppPath=AppPath.left(i+1);	
			//���ش������i+1���ַ�,Ŷ����֪���ˣ���ô����������һ��"\"!��Ϲ���ˣ�����û�е���.ֻһ�ξ�break��������"��ÿ����ɾ��һ��'\', �ǵ���ΪɶҪ+1�أ� �Լ������Ĭ�ϵ�argv[0]���ǵ������ŵĸ�ʽ��Ϊɶ��Ҫ=='\\'? ��Ϊ���ڴ��������'\\'�ĸ�ʽ���ڵģ� ԭ��? �Ҹ���ɵ�ƣ������ת���ַ���
			break;
		}
	}	//Ϊ�˻�õ�ǰ�ļ�ִ�е�Ŀ¼������ô�鷳���𣿲������ֳɵ�api����? GetCurrentDirectoryA  ��ͻ��.. �������ͦ�õ� =_= ���������ط�����windows.h��������Ȼ����д.

	//cout << AppPath << endl;	//��ִ���ļ���λ��
	//cout << std::filesystem::current_path();	//Դ�ļ���λ�ã�������ˣ�����û���ṩͳһ��,�ⲻ������֪���㵼�µģ�������ʵ��ˡ�
	// ��λ�ÿ�ִ���ļ���λ���أ����������Ļ�?
	//auto dir = weakly_canonical(filesystem::path(argv[0])).parent_path();	
	//�ɴﵽͬ����Ч��.
	// https://stackoverflow.com/a/55579815/13792395
	// https://stackoverflow.com/a/55983201/13792395

	LytWString Content=ReadFile(AppPath+"File.txt").ToWString();
	try
	{
		Interpret TheInterpret(Content.ToLower());
		TheInterpret.Print();
	}
	catch (LytPtr<Error> Info)
	{
		wcout<<Info->GetMessage()<<L"��"<<Info->Content.Content<<L"��("<<Info->Content.Position<<L")"<<endl;
	}
	_getch();
}