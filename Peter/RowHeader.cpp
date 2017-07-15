#ifndef ROW_HEADER_CPP
#define ROW_HEADER_CPP
#include "..\Common\stdafx.cpp"

class RowHeader{
	public:
		typedef std::bitset<3> RecordType;
		typedef Row Recorder;
		typedef std::shared_ptr<Recorder> Pointer; //### 改为 RowIterator
		void assertion(){
			assert( n_owned>=4 && n_owned<=8 );
		}
		RowHeader() : flag4  (std::vector<bool>(4,false)), 
					  n_owned(4), 
					  heap_no(std::vector<bool>(13,0)) {  }
// Row 要求所有成员可拷贝、移动、赋值和构造 
		//~RowHeader()= default;
		//RowHeader(const RowHeader&) 			= default;
		//RowHeader(RowHeader&&) 					= default;
		//RowHeader& operator=(const RowHeader&) 	= default;
		//RowHeader& operator=(RowHeader&&) 		= default;
		
		std::vector<bool>	flag4   ;
		std::size_t			n_owned ;
		std::vector<bool>	heap_no ;
		RecordType record_type;
		Pointer next_recorder;
};
#endif