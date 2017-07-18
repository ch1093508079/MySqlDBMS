#ifndef PAGE_CPP_CRC32_3CE9AD99
#define PAGE_CPP_CRC32_3CE9AD99

#include "..\Peter\Peter.cpp"
class Page {
	public:
		enum Type { NODE, UNDO, SYS, TRAN, BITMAP, FREE_LIST, UN_BLOB, BLOB };
		bool isInfimum(){
			return rows.front().isInfimum();
		}
		bool isSupremum(){
			return rows.back().isSupremum();
		}
		bool isVirtualRecord(){
			return isInfimum() || isSupremum() ;
		}
		bool isFreeSpace(){
			bool low = rows.front().isFreeSpace() || rows.back().isFreeSpace();
			bool high= type==FREE_LIST ;
			if(low ^ high)
				std::clog<<"警告！tag 不一致：FreeSpace"<<std::flush;
			return high;
		}
		bool isUserRecord(){
			bool not3 = ! ( isVirtualRecord() || isFreeSpace() );
			return not3;
		} 
		Page(Page::Type t):type(t){
			if(t==FREE_LIST){
				rows.push_back(InnoDBPage::FreeSpace());
				assertion();
			}else{
				std::stringstream ss;
				ss<<"未定义该类型 Page::Type::"<<t<<" 的构造函数";
				throw ss.str();
			}
		} 
		Page(bool cend):type(NODE){
			Row supremum= InnoDBPage::VirtualRecord();
			RowHeader::Pointer pn = std::make_shared<Row>(/*supremum*/); //用空指针规避问题 
			Row infimum = InnoDBPage::VirtualRecord(pn);
			rows.push_back( cend ? supremum : infimum );
			assertion();
		}
		Page():type(SYS){ //默认为系统页，用单个row记录列名 
			static unsigned long long call = 0;
			std::clog<<"pSys"<<(++call)<<"\t";
			rows.push_back(Row());
			assertion();
		}
		
		void push(Row&& row){
			if( ! this->isFreeSpace())
				throw "push into non-Free Page";
			rows.erase(rows.begin(),rows.end());
			rows.push_back(std::move(row));
			assertion();
		}
		void push(const Row& row){
			bool DEBUG_DEAD_LOOP = false;
			if(DEBUG_DEAD_LOOP)
				std::cerr<<"死递归检测："
						<<"push(Row&& row) -> "
						<<"call -> push(const Row& row)"
						<<std::endl;
			this->push(/*std::move*/(Row(row)));
		}
		std::string screen(std::string tab="\t\t\t\t"){
if(DEBUG_SCREEN) std::cerr<<"\nPage::screen called"<<std::endl;
if(DEBUG_SCREEN) std::cerr<<"\nPage::screen index 1"<<std::endl;
			unsigned countRow = rows.size();
if(DEBUG_SCREEN) std::cerr<<"\nPage::screen pre if"<<std::endl;
			if(0==countRow){
if(DEBUG_SCREEN) std::cerr<<"\n(0==countRow)return nil;"<<std::endl;
				return "nil";
			}
if(DEBUG_SCREEN) std::cerr<<"\nPage::screen pre loop"<<std::endl;
			std::string s; 
			for(unsigned i=0;i<countRow;++i){
				s += "Row"+uint2string(i);
				s += rows[i].screen() + tab;
			}
if(DEBUG_SCREEN) std::cerr<<"\nPage::screen return"<<std::endl;
			return s;
		}
		static const unsigned maxSpace(){ return 16*1024; }
	private:
		Type type;
		std::vector < Row > rows; 
		
		inline void assertion(){
			assert(rows.size()==1); //简化：每页只存放一行 
			//assert(rows.size()>=2);
			//assert(rows.size()<7992);
		}
		std::string uint2string(unsigned u){
			std::stringstream ss;
			ss<<" "<<std::setw(2)<<(u+1)<<" : ";
			return ss.str();
		}
};
#endif
