// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ


#include<memory>

#include<iostream>
#include<sstream>
#include<iomanip>

#include<functional> 
#include<algorithm>
#include<numeric>
#include<cctype>

#include<vector>
#include<string>
#include<array>
#include<bitset>
#include<map>

#include<cassert>

#include "initializer_list.cpp"

typedef unsigned long long	 PRI_TYPE ;
typedef std::string			 SUB_TYPE ;

class Field;
class RowHeader;
class Row; 
namespace InnoDBPage{
	class Peter;
	typedef unsigned long long BYTE8;
	typedef unsigned short BYTE2;
	typedef unsigned char BYTE;
	//...
}






