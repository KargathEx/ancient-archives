#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "LytString.h"

using namespace std;

/*���ܣ���ȡtxt��ʽ�ļ�
  ��������¼�ļ���������·����������ΪLytString
  ����ֵ�������ļ��������ݣ�����ΪLytString */
extern LytString ReadFile(LytString);

/*���ܣ�дtxt��ʽ�ļ�
  ��������¼��д���ݣ�����ΪLytString */
extern void WriteFile(LytString , LytString);

#endif