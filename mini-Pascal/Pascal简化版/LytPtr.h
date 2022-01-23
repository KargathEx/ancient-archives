#ifndef LYTPTR_H
#define LYTPTR_H

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>

using namespace std;

template<typename _Type>
class LytPtr // ����ָ��
{
private:
	int* Count; //���ü���
	_Type* Object; // ����ָ����ƶ���

	void Increase()		//������ڶ�����ж���˼�ǲ�Ϊ��? ʲôʱ���Ϊ��?
	{
		if (Object && Count) (*Count)++;	
	}

	void Decrease()		//������0��ʱ��ɾ�������ҹ���
	{
		if (Object && Count)
		{
			(*Count)--;
			if (!(*Count))
			{
				if (Object) delete Object;
				delete Count;
				Object=0;
				Count=0;
			}
		}
	}

public:
	LytPtr():Count(0),Object(nullptr){}

	LytPtr(_Type* Temp):Object(Temp)		
	{										
		Count=new int(1);					
	}
//Ϊʲô����˶�ϲ��new... class��Ķ����͵�������
//���Ӧ���ǽ���new xx ���ص�ָ����Ǹ����캯������LytPtr�������֮��
//������������ʧ�ĵط����û�б�Ķ���Ҫ�������Լ��������Լ������ü����������Լ���
//���ԣ�����и�ֵ�Ļ����ǡ����LytPtr���������˽�б������ģ�
//��� shared_ptr ������Թ�ͬ�й�һ��ָ�� p�������������й� p �� shared_ptr ���󶼽���˶�����й�ʱ���ͻ�ִ��delete p
	//������ȷʵ���..

	LytPtr(const LytPtr<_Type>& Temp):Count(Temp.Count),Object(Temp.Object)
	{
		Increase();
	}

	template<typename T>
	LytPtr(const LytPtr<T>& Temp)
	{
		Object=dynamic_cast<_Type*>(Temp.Buffer());	//������������������͵ĸ�ֵ����ǰ���͵ģ��ܽ��Э������? ΪʲôҪdynamic_cast?
		//��� ���ʽ �ǵ���̬���� Base ��ָ������ã��� ������ �ǵ� Derived ���͵�ָ������ã����������ʱ���.sidecast,downcast
		if (Object)				
		{
			Count=Temp.GetCount();
			Increase();
		}
		else
		{
			Object=0;
			Count=0;
		}
	}

	~LytPtr()
	{
		Decrease();
	}

	operator bool()const	//���������ɶ�� �������ĵط��� bool������ת���԰ɣ� ֻҪ������0��ת����. ����ת����.
	{
		return Object!=0;
	}

	LytPtr<_Type>& operator=(_Type* Temp)
	{
		Decrease();				
								
		Count=new int(1);		
		Object=Temp;			
		return *this;			
	}
	//���ڸ�ֵ�������ȵݼ�֮ǰ���ܵĶ���Ȼ����¶�������Ϊ1Ȼ��ӹ���ָ���ֵ�� ΪʲôҪ����Ϊ1��
	//�����ǽ���֮ǰ��ֵ?Ŷ����Ϊ������ܵ���ԭʼָ�롣 ��ԭʼָ�뱻������֮����Ҫ�Լ���delete�Լ����� ��˵�أ��Ǻ�..
	//���������Ϊ�˵�ǰָ�����������ʱ�����ɴ������������ ��ȻΪɶҪ��̬����?
	//���ߣ���Ϊ�˴��ݸ���Ķ����ʱ���������ҵ�����ַ����ֵ?  
	//���˼ҵ�����ָ��Ҳ������new�����ֲ�������? �������ǵģ���std��������?

	LytPtr<_Type>& operator=(const LytPtr<_Type>& Temp)
	{
		Decrease();
		Object=Temp.Object;
		Count=Temp.Count;
		Increase();
		return *this;
	}

	bool operator==(_Type* Temp)const
	{
		if (Object) return Object==Temp;
		else
		{
			if (Temp) return false;
			else return true;
		}
	}

	bool operator==(const LytPtr<_Type>& Temp)const
	{
		return Object==Temp.Object;
	}

	bool operator!=(_Type* Temp)const
	{
		if (Object) return Object!=Temp;
		else
		{
			if (Temp) return true;
			else return false;
		}
	}

	_Type* operator ->()const
	{
		if (Object) return Object;
		else return 0;
	}

	_Type* Buffer()const
	{
		if (Object) return Object;
		else return 0;
	}
	
	int* GetCount()const
	{
		return Count;
	}
};

#endif