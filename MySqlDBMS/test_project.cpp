#include "..\Common\stdafx.cpp"
#include "..\PhysQuery\IterTableScan.cpp"

using std::cin;
using std::cout;
using std::endl;
using std::stringstream;
using std::string;
using std::vector;


void showInsert(unsigned countLine, string tableName){
	if(tableName == "don't show")
		return;
	cout<<"执行插入: "<<countLine<<" 行受影响";
	//	<<"(0x"<<std::hex<<countLine<<std::dec<<")\n";
	cout<<(global::gTableSpace(tableName).screen(tableName,"\t"))
		<<endl;
}

void testScanIBDATA1(){
	auto scanIBDATA1 = TableScan(); 
	try{
		scanIBDATA1.open();
		scanIBDATA1.getNext();
	}
	catch(long long hex){
		std::cerr<<"ErrorCode (错误代码) : "<<std::hex<<hex<<std::dec<<endl;
		if(hex==0xbadbadbadbad07)
			std::cerr<<"目前迭代器不支持non-exist-segments[\"data\"]的表\n\n";
		else
			throw hex;
	}
	catch(const char* ex){
		std::cerr<<"ErrorCode (错误代码) : "<<ex<<endl;
		if(std::string(ex) == std::string("map-key non-exist"))
			std::cerr<<"目前迭代器不支持non-exist-segments[\"data\"]的表\n\n";
		else
			throw ex;
	}
}

void testScanIni(unsigned countLine){
	auto scanIni = TableScan("ini"); 
	scanIni.open();
	for(int i=0;i<countLine+5;i++) // ###试试越界
		scanIni.getNext()->screen();
}

int main(){
	//testScanIBDATA1();
	
	unsigned countLine = global::iniTableInsert();
	showInsert(countLine, "show"); // don't 
	
	//testScanIni(countLine);
}
