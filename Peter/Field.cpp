#ifndef FIELD_CPP
#define FIELD_CPP
#include "..\Common\stdafx.cpp"

class Field{
public:
	PRI_TYPE toPrimaryKey() { 
		return std::stoull( str.substr(str.find_first_of("0123456789")) ); 
	}
	Field(std::string s) : str(s) {}
	Field(const char* s) : str(s) {}
	Field(PRI_TYPE i) {
		std::stringstream ss;
		ss<<i;
		Field(ss.str());
	}
// Row Ҫ�����г�Ա�ɿ������ƶ�����ֵ�͹��� 
	//~Field()= default;
	//Field() = default;
	//Field(const Field&) 			= default;
	//Field(Field&&) 					= default;
	//Field& operator=(const Field&) 	= default;
	//Field& operator=(Field&&) 		= default;
	
	std::string screen(){
		return str;
	}
	unsigned space(){
		return str.size(); //�ɸĽ������ǿ��ַ� 
	}
	static unsigned spaceSum(unsigned ini, Field rhs){
		return ini + rhs.space();
	}
	
//	bool isPrimaryKey = false; // ������ӳ�Ա��ʾ���� 
	std::string str;
};
#endif