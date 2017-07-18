#ifndef RELATION_CPP_CRC32_F5B971B9
#define RELATION_CPP_CRC32_F5B971B9

#include "..\LogicStore\TableSpace.cpp"
class Relation{
	public:
		inline static bool not_space(char c){
			return std::isspace(c) == false;
		}
		inline static std::string::iterator trimStart
			(std::string::iterator b, std::string::iterator e) 
				{return std::find_if(b,e,not_space);}
		static bool notLegalChar(char c){
			using namespace std;
			bool notLegal  = ! ( islower(c) || isdigit(c) );
			bool notDefaultTable=isspace(c) || isupper(c);
			return notLegal || notDefaultTable;
		}
		static bool isLegalRelationName(std::string s){
			auto first_not_space = trimStart(s.begin(),s.end());
			if(std::isdigit(*first_not_space))
				std::clog<<"警告：数字开头的标识符\n";
			auto first_not_legal = std::find_if
				(first_not_space, s.end(), notLegalChar);
//			std::cerr<<"{"<<(s.end() - first_not_space)<<"}"; 
//			std::cerr<<"{"<<(s.end() - first_not_legal)<<"}"; 
			return ( first_not_legal == s.end() ) ;
		}
};
#endif
