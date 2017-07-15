// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息


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






