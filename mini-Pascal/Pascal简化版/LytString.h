#ifndef LYTSTRING_H
#define LYTSTRING_H

#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <string.h>
#include <math.h>
#include <iomanip> 
#include "LytWString.h"

using namespace std;

class LytString
{
protected:
    int length;
    char* s;
public:
    LytString();
    /*���ܣ�����LytString(�޲���)
      ����ֵ������ΪLytString�������ַ���sΪ�գ�����lengthΪ0*/

    LytString(const char* ss);
    /*���ܣ�����LytString
      ����������Ϊ�����޸ĵ��ַ���ָ��
      ����ֵ������ΪLytString�������ַ���ָ��s����ͬ����ss*/
      
    LytString(const LytString& o);
    /*���ܣ�����LytString 
      ����������Ϊ�����޸ĵ�LytString
      ����ֵ������ͬ����o������ΪLytString*/
      
    LytString operator=(const char* ss);
    /*���ܣ����������=
            ��LytSting��=(�ַ���ָ��ss) 
      ��������¼=�Ҷ˲���������Ϊ�����޸ĵ��ַ���ָ��
      ����ֵ������ΪLytString�������ַ���ָ��s����ͬ�ڲ���ss*/
      
    LytString operator=(const LytString & o);
    /*���ܣ����������=
            (LytString)=(LytString)
      ��������¼=�Ҷ˲���������Ϊ�����޸ĵ�LytString
      ����ֵ������ΪLytString������ͬ�ڲ���o*/
      
    friend ostream& operator<<(ostream& p,const LytString& o);
    /*���ܣ����������<<���������ΪLytString�Ĳ���o 
            ��ostream��<<(LytString)
      ������p��¼<<�������Ϊostream�ĺ�����oΪ��¼<<�ұ�����ΪLytString�Ĳ���
      ����ֵ������Ϊostream*/
      
    friend istream& operator>>(istream& p,LytString& o);
    /*���ܣ����������<<���������ΪLytString�Ĳ���o 
            ��ostream��<<(LytString)
      ������p��¼<<�������Ϊostream�ĺ�����oΪ��¼<<�ұ�����ΪLytString�Ĳ���
      ����ֵ������Ϊostream*/
      
    bool operator==(const LytString& o)const;
    /*���ܣ����������==
            ��LytString��==(LytString) 
      ������o��¼==�ұߵ�LytString
      ����ֵ�����Ͳ����޸ĵ�Ϊ����ֵ���������ַ���s��ͬ�������棬��֮�򷵻ؼټ�*/
      
    bool LytString::operator!=(const LytString& o)const;
    /*���ܣ����������!=
            ��LytString��!=(LytString) 
      ������o��¼!=�ұߵ�LytString
      ����ֵ�����Ͳ����޸ĵ�Ϊ����ֵ���������ַ���s��ͬ�������棬��֮�򷵻ؼټ�*/
      
    bool LytString::operator>(const LytString& o)const;
    /*���ܣ����������> 
            ��LytString��>(LytString) 
      ������o��¼>�ұߵ�LytString
      ����ֵ�����Ͳ����޸ĵ�Ϊ����ֵ����ǰ�ߴ��ں��ߣ������棬��֮�򷵻ؼټ�*/
      
    bool LytString::operator<(const LytString& o)const;
    /*���ܣ����������< 
            ��LytString��<(LytString) 
      ������o��¼>�ұߵ�LytString
      ����ֵ�����Ͳ����޸ĵ�Ϊ����ֵ����ǰ��С�ں��ߣ������棬��֮�򷵻ؼټ�*/
      
    bool LytString::operator>=(const LytString& o)const;
    /*���ܣ����������>= 
            ��LytString��>=(LytString) 
      ������o��¼>=�ұߵ�LytString
      ����ֵ�����Ͳ����޸ĵ�Ϊ����ֵ����ǰ�ߴ��ڵ��ں��ߣ������棬��֮�򷵻ؼټ�*/
      
    bool LytString::operator<=(const LytString& o)const;
    /*���ܣ����������<=
            ��LytString��<=(LytString) 
      ������o��¼<=�ұߵ�LytString
      ����ֵ�����Ͳ����޸ĵ�Ϊ����ֵ����ǰ��С�ڵ��ں��ߣ������棬��֮�򷵻ؼټ�*/
      
    LytString operator+(const LytString& o)const;
    /*���ܣ����������+����+�������ӵ�LytString�����ַ���s�������� 
            ��LytString��+(LytString)
      ��������¼+�Ҷ˲���������Ϊ�����޸ĵ�LytString
      ����ֵ������ΪLytString�������ַ���ָ��s����Ϊ�������ַ������Ӻ�Ľ��*/
      
    LytString operator+(const char* ss)const;
    /*���ܣ����������+����+�������ӵ�LyuString�����ַ���s���ַ���ss��������
            ��LytString��+(char*)
      ��������¼+�ұ߲���������Ϊ�����޸ĵ��ַ���ָ��
      ����ֵ������ΪLytString�������ַ���ָ��s����Ϊ�������ַ������Ӻ�Ľ��*/
      
    friend LytString operator+(const char*ss , const LytString& o);
    /*���ܣ����������+��+�������ӵ��ַ���ss��LyuString�����ַ���s��������
            ��char*��+(LytString)
      ������ss��¼+����ַ���ָ�룬oΪ��¼+�ұ�����ΪLytString����
      ����ֵ������ΪLytString�������ַ���ָ��s����Ϊ�������ַ������Ӻ�Ľ��*/ 
      
    LytString sub(const int index,const int count)const;
    /*������:sub
      ����:�ӵ�indexλ��ʼ��ȡ����LytString�����ַ���ָ��s��count���ַ�
      ����:index��¼�ӵڼ�λ��ʼ����ΧΪ0<=index<=length-1������Ϊ�����޸ĵ����� 
           count��¼��ȡ���ַ���������ΧΪ1<=count<=length-index������Ϊ�����޸ĵ����� 
      ����ֵ������Ϊ�����޸ĵ�LytString�������ַ���ָ��s����Ϊ��ȡ�����ַ���
      �������ݴ���������index<0��index>length-1��count<1��count>length-index������ֵ�����ַ���ָ��sΪ��*/
      
    void insert(const int index,const LytString o);
    /*��������insert
      ���ܣ��ӵ�indexλ��ʼ����������ΪLytString���ַ���o
      ������index��¼�ӵڼ�λ��ʼ����ΧΪ0<=index<=length-1������Ϊ�����޸ĵ�����
            o��¼������ַ���������Ϊ�����޸ĵ�LytString������o�����ַ���ָ�����ݲ���Ϊ�� 
      �������ݴ���������index<0��index>length-1�����o�����ַ���ָ������Ϊ�գ��ַ��������κθı�*/
      
    void Delete(int index,int count);
    /*��������Delete
      ���ܣ��ӵ�indexλ��ʼ��ɾ��count���ַ�
      ������index��¼�ӵڼ�λ��ʼ����ΧΪ0<=index<=length-1������Ϊ�����޸ĵ�����
            count��¼ɾ���ַ��ĸ�������ΧΪ0<=count<=length-index������Ϊ�����޸ĵ�����
      �������ݴ���������index<0��index>length-1��count<0��count>length-index���ַ��������κ��޸�*/
                        
    LytString toupper()const;
    /*��������toupper
      ���ܣ�����һ��LytString�������ַ���ָ��s������Ϊ������Сд�ַ���Ϊ��д�ַ��Ľ��
      ����ֵ������Ϊ�����޸ĵ�LytString*/
    
    LytString tolower()const;
    /*��������tolower
      ���ܣ�����һ��LytString�������ַ���ָ��s������Ϊ�����д�д�ַ���ΪСд�ַ��Ľ��
      ����ֵ������Ϊ�����޸ĵ�LytString*/
      
    LytString left(const int count)const;
    /*��������left
      ���ܣ�����߿�ʼ��ȡcount���ַ�����Ϊһ������ΪLytString���ַ��� 
      ������count��¼����LytString�ĳ��ȣ���ΧΪ0<=count<=length����Ϊ�����޸ĵ�����
      ����ֵ������Ϊ�����޸ĵ�LytString
      �������ݴ���count<0��count>length�������ַ�������Ϊ��*/
      
    LytString right(const int count)const;
    /*��������right
      ���ܣ����ұ߿�ʼ��ȡcount���ַ�����Ϊһ������ΪLytString���ַ��� 
      ������count��¼����LytString�ĳ��ȣ���ΧΪ1<=count<=length����Ϊ�����޸ĵ�����
      ����ֵ������Ϊ�����޸ĵ�LytString
      �������ݴ�����count<0��count>length�������ַ�������Ϊ��*/
      
    LytString trimleft()const;
    /*��������trimleft
      ���ܣ�����һ��LytString�������ַ���ָ������sΪ������˿ո�ȥ����Ľ��
      ����ֵ������Ϊ�����޸ĵ�LytString*/
    
    LytString trimright()const;
    /*��������trimright
      ���ܣ�����һ��LytString�������ַ���ָ������sΪ�����Ҷ˿ո�ȥ����Ľ��
      ����ֵ������Ϊ�����޸ĵ�LytString*/
    
    LytString trim()const;
    /*��������trim
      ���ܣ�����һ��LytString�������ַ���ָ������sΪ��������Ҷ˿ո�ȥ����Ľ��
      ����ֵ������Ϊ�����޸ĵ�LytString*/
      
    int pos(const LytString& o)const;
    /*��������pos
      ���ܣ�����LytString���͵Ĳ���o���ַ���s�е�һ�γ��ֵ�λ��
      ������o��¼Ҫ�ҵ��ַ������������ַ���s�г���һ��(�ǿ�)������Ϊ�����޸ĵ�LytString
      ����ֵ������o���ַ���s�е�һ�γ��ֵ�λ�ã�����Ϊ�����޸ĵ�����
      �������ݴ������������ַ���s���Ҳ���o����oΪ���ַ���������-1*/
      
    int replace(const LytString& find , const LytString& result);
    /*��������replace
      ���ܣ����ַ���s���ҵ�find���ٽ����滻Ϊresult
      ������find��¼��Ҫ�滻���ַ�������find����Ϊ�գ�����Ϊ�����޸ĵ�LytString
            result��¼�滻�Ľ��������Ϊ�����޸ĵ�LytString
      ����ֵ�������޸ĵĴ���������Ϊ�����޸�����
      �������ݴ���������findΪ�ջ���s���Ҳ���find������0���ַ����������κ��޸�*/

	LytWString ToWString()const;
    
    friend int StrToInt(const LytString& o);
    friend LytString IntToStr(const int i);
    friend double StrToDouble(const LytString& o);
    friend LytString DoubleToStr(const double d); 

	int Size()const;
	char& operator[](int Index);
	const char* Buffer()const;

    
    ~LytString();
    /*��������*/
};

#endif
