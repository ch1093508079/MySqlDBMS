#include "Relation.cpp"
class TableScan; 
namespace global{
	TableSpace& gTableSpace(std::string name){ 
		static std::map<std::string, TableSpace> gTableSpace ;
		static bool firstCall = true;
		if(firstCall){
			firstCall = false;
			gTableSpace["IBDATA1"] = TableSpace(TableSpace::Type::SHARE);
			gTableSpace["ini"] = TableSpace(TableSpace::Type::UNIQUE);
		}
		return gTableSpace[name];
	}
	unsigned iniTableInsert(){
		std::string tableName = "ini" , s = "0" , i2s; 
		auto countLine = 0;
		for(unsigned long long i=1 ; i<=100 ; ++i){
			std::stringstream ss;
			ss<<std::setw(3)<<i;
			s.back() += 1;
			Row r ;
			countLine+= global::gTableSpace(tableName).insert(r);
		}
		return countLine;
	}
}