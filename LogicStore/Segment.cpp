#include "Extent.cpp"

class Segment {
public:
	typedef std::vector<Extent> ExtentCollection;
	enum Type { NODE, DATA, INDEX, ROLLBACK, OTHERS=255 };
	Segment(Segment::Type t) : type(t) { 
		//����� frag ִ�з�Ĭ�Ϲ��� 
	}
	Segment() : type(NODE) { }
	size_t insert(Row&& row, bool toExtents = true){
		assert(toExtents);
		//�� Segment ����
		if(extents.empty()){
			expand(); 
			//�Ժ�ɿ����� frag.back() ��¼ supremumҳ���±�
		} 
		assert( ! extents.empty());
		return pushExtents(std::move(row));
	}
	unsigned needPage(Row& row){
		auto need = 1 + row.space() / Page::maxSpace() ;
		if( need > 1 ) throw "Ŀǰ��֧�� < 16KB ����";
		return need;
	}
	size_t pushExtents(Row&& row){ 
		auto need = needPage(row);
		auto &ep = extents.back().getPages();
		auto supre= std::find_if(ep.begin(), ep.end(), 
							[](Page p){return p.isSupremum();});
		assert( supre < ep.end() ); // throw "��������Ϊ supremum ����������ݸ�����";
		int countFreePage = std::distance(supre, ep.end()) - 1;
		if(countFreePage ==0){
			//    ����ҳ����������Extent�ٵݹ���ã����һ�Σ� 
			expand();
			return pushExtents(std::move(row));
		}
		else{
			assert(countFreePage > 0);
			//���� supremum �����page���������� 
			(supre+need)->push(/*std::move*/(row));
			//�ٽ���
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
	std::array<Page, 32> frag; //������ĳ��Զ������� 
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