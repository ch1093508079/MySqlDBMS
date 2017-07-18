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
	cout<<"ִ�в���: "<<countLine<<" ����Ӱ��";
	//	<<"(0x"<<std::hex<<countLine<<std::dec<<")\n";
	cout<<(global::gTableSpace(tableName).screen(tableName,"\t"))
		<<endl;
}

int main(){
	auto scanIBDATA1 = TableScan(); 
	try{
		scanIBDATA1.open();
		scanIBDATA1.getNext();
	}
	catch(long long hex){
		std::cerr<<"ErrorCode (�������) : "<<std::hex<<hex<<std::dec<<endl;
		if(hex==0xbadbadbadbad07)
			std::cerr<<"Ŀǰ��������֧��non-exist-segments[\"data\"]�ı�\n\n";
		else
			throw hex;
	}
	catch(const char* ex){
		std::cerr<<"ErrorCode (�������) : "<<ex<<endl;
		if(std::string(ex) == std::string("map-key non-exist"))
			std::cerr<<"Ŀǰ��������֧��non-exist-segments[\"data\"]�ı�\n\n";
		else
			throw ex;
	}
	
	string tableName = "ini";
	unsigned countLine = global::iniTableInsert();
	showInsert(countLine, "don't show");
	
	auto scanIni = TableScan(tableName); 
	scanIni.open();
	for(int i=0;i<70*5;i++) 
		scanIni.getNext()->screen();
}
