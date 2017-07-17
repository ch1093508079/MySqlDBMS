//#include "Relation.cpp"
#include "global.cpp"
class TableScan{
	typedef Segment::ExtentCollection::iterator	ExtentPtr;
	typedef Extent::PageCollection Block;
	typedef Block::iterator TuplePtr;
	std::string relationName;
	std::string blockFile;	//TODO:考虑用流类型，可是流不能拷贝？
	ExtentPtr b  ;
	TuplePtr  t  ;
	inline Block& tupleCollect(){ // 函数依赖于 b 的状态 
		return b->getPages();
	}
	TableSpace& ts(){return global::gTableSpace(relationName);}
public:
	TableScan(): relationName("IBDATA1"), blockFile("BLOCK1.txt"){ }
	TableScan(std::string r, std::string b="."):relationName(r),blockFile(b){
		if(relationName != "IBDATA1")
			assert(	Relation::isLegalRelationName(r));
	}

	void open(std::string key2seg = "data"){
		assert(key2seg=="data");
		if( ! ts().existKey(key2seg)){
			long long uhex = 0xbadbadbadbad07;
			throw uhex;
		}
		auto& bCollect = ts().refSegment(key2seg).getExtents();
		auto& tCollect = this->tupleCollect();
		b = bCollect.begin();
		t = tCollect.begin();
		
		unsigned bSize = std::distance(b, bCollect.end());
		unsigned tSize = std::distance(t, tCollect.end());
if(DEBUG_ITERATOR) std::cout<<"<"<<bSize<<","<<tSize<<">"<<std::endl;
		assert(bSize==bCollect.size());
		assert(tSize==b->countPage());
	}
	TuplePtr getNext(){
		assert( t != this->tupleCollect().end() );
		t++;
		if( t != this->tupleCollect().end() ){ // ### 待修改 
std::clog<<" != "; 
			assert( 0 < std::distance(t, this->tupleCollect().end()) );
			return t;
		}
		
		assert( t == this->tupleCollect().end() );
		b++;
std::clog<<"b++\n"; 
		auto& bCollect = global::gTableSpace(relationName).refSegment("data").getExtents();
		if(b == bCollect.end())throw std::out_of_range("临时异常");
		// ### 检查是否为supremum或者？？？看书 
		assert( t != this->tupleCollect().end() );
		t = this->tupleCollect().begin();
		return t; 
	}
	void Close(){}
};
