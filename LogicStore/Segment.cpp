#include "Extent.cpp"

class Segment {
public:
	typedef std::vector<Extent> ExtentCollection;
	enum Type { NODE, DATA, INDEX, ROLLBACK, OTHERS=255 };
	Segment(Segment::Type t) : type(t) { 
		//建议对 frag 执行非默认构造 
	}
	Segment() : type(NODE) { }
	size_t insert(Row&& row, bool toExtents = true){
		assert(toExtents);
		//空 Segment 处理
		if(extents.empty()){
			expand(); 
			//以后可考虑在 frag.back() 记录 supremum页的下标
		} 
		assert( ! extents.empty());
		return pushExtents(std::move(row));
	}
	unsigned needPage(Row& row){
		auto need = 1 + row.space() / Page::maxSpace() ;
		if( need > 1 ) throw "目前仅支持 < 16KB 的行";
		return need;
	}
	size_t pushExtents(Row&& row){ 
		auto need = needPage(row);
		auto &ep = extents.back().getPages();
		auto supre= std::find_if(ep.begin(), ep.end(), 
							[](Page p){return p.isSupremum();});
		assert( supre < ep.end() ); // throw "绝逼是因为 supremum 被行溢出数据覆盖了";
		int countFreePage = std::distance(supre, ep.end()) - 1;
		if(countFreePage ==0){
			//    空闲页，就申请新Extent再递归调用（最多一次） 
			expand();
			return pushExtents(std::move(row));
		}
		else{
			assert(countFreePage > 0);
			//先在 supremum 后面的page构建数据行 
			(supre+need)->push(/*std::move*/(row));
			//再交换
			using std::swap;
			swap( *supre, *(supre + need) );
			return 1;
		}
	}
	void expand(){
		unsigned countExtent = extents.size();
		switch(countExtent){
			case 0: case 1:
			default:
				extents.push_back(Extent());
		}
	} 
	ExtentCollection& getExtents(){
		return extents;
	} 
	Extent& refExtent(size_t i){
		return getExtents()[i];
	}
private:
	Type type;
	std::array<Page, 32> frag; //想把它改成自定义类型 
	ExtentCollection extents;
	std::string uint2string(unsigned u){
		std::stringstream ss;
		ss<<" "<<std::setw(2)<<(u+1)<<" : ";
		return ss.str();
	}
public:
	std::string screen(std::string name = "null name", std::string tab="\t\t"){
		std::string s;
		std::string LINE = "\n";
		s += tab + "Segment key : " + name;
		if(0==extents.size())
			s += LINE +tab/*.substr(0,tab.size()-1)*/+ "empty vector<Extent>";
		if(name == "data"){
			for(unsigned i=0; i<frag.size()/8; i++){
				s += (i%4)? "" : LINE;
				s += tab + "Frag" + uint2string(i);
				s += frag[i].screen(tab+"\t") + LINE;
			}
		}
		for(unsigned i=0; i<extents.size(); i++){
			s += tab + "Extent"+uint2string(i) + LINE;
			tab += "\t";
			for(unsigned j=0; j<extents[i].countPage(); j++){
if(DEBUG_GLOBAL)std::cerr<<"\t# "<<j<<" #\t";
				s += tab + "Page" +uint2string(j);
				s += extents[i].refPage(j).screen(tab+"\t") + LINE;
			}
		}
		return s;
	} 
};
typedef Segment BTreeNode;