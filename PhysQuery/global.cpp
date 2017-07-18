#ifndef GLOBAL_CPP_CRC32_
#define GLOBAL_CPP_CRC32_

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
			{
				assert( r.countField() >= 2 );
				r[0] = ss.str();
				r[1] = s;
			}
			try { countLine += global::gTableSpace(tableName).insert(r); }
			catch(std::out_of_range ex){
				std::clog<<"Ô½½ç";
				throw ex;
			}
			catch(const char * str){
				using std::cerr ;
				cerr<< std::endl
					<< std::setw(4)<<"i="<<i
					<<"throw Exception: "<< str
				//	<<"where(): iniTableInsert() - for loop - "
				//	<< std::endl
					;
			}
		}
		return countLine;
	}
}
#endif
