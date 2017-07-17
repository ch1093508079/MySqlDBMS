#include "..\LogicStore\TableSpace.cpp"

class Relation{
	public:
		inline static bool not_blank(char c){
			bool b = std::isblank(c);
			return !b;
		}
		inline static std::string::iterator trimStart
			(std::string::iterator b, std::string::iterator e) 
				{return std::find_if(b,e,not_blank);}
		static bool notLegalChar(char c){
			using namespace std;
			bool notLegal  = ! ( islower(c) || isdigit(c) );
			bool notDefaultTable=isblank(c) || isupper(c);
			return notLegal || notDefaultTable;
		}
		static bool isLegalRelationName(std::string s){
			auto first_not_blank = trimStart(s.begin(),s.end());
			if(std::isdigit(*first_not_blank))
				std::clog<<"警告：数字开头的标识符\n";
			auto first_not_legal = std::find_if
				(first_not_blank, s.end(), notLegalChar);
//			std::cerr<<"{"<<(s.end() - first_not_blank)<<"}"; 
//			std::cerr<<"{"<<(s.end() - first_not_legal)<<"}"; 
			return ( first_not_legal == s.end() ) ;
		}
};