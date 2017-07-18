#ifndef TABLE_SPACE_CPP_CRC32_B50D8C2C
#define TABLE_SPACE_CPP_CRC32_B50D8C2C

#include "Segment.cpp"
class TableSpace {
	public:
		enum Type { SHARE, UNIQUE };
		TableSpace(TableSpace::Type t = UNIQUE) : type(t) {
			if(type == UNIQUE)
				setUnique();
			else if(type == SHARE)
				setShare();
			else
				assert(false); 
		}
		std::string screen(std::string name = "null name", std::string tab="\t"){
			std::string s;
			std::string LINE = "\n";
			s += tab + "TABLE name : " + name + LINE;
			for(auto &p : segments){
				auto p2 = p.second.screen(p.first , tab+"\t") + LINE;
				s += p2;
			}
			return s;
		}
		size_t insert(Row&& row, std::string seg = "data"){
			assert(segments.find(seg) != segments.end());//断言键值存在
			return (segments[seg]).insert(std::move(row));
		}
		size_t insert(Row& row, std::string seg = "data"){
			Row r(row);
			return insert(std::move(r), seg);
		}
		bool existKey(std::string key){
			return segments.find(key) != segments.end();
		}
		Segment& refSegment(std::string segmentName){
			assert(segmentName=="data");
			if(!existKey(segmentName)){
				const char* ex = "map-key non-exist";
				throw ex;
			}
			return segments.at(segmentName); // at带检查，不同于[] 
		}
	private:
		Type type;
	//	std::map < std::string, Page > frag;
		std::map < std::string, Segment > segments;
	protected:
		void setShare(){
			this->segments["undo"] = Segment(Segment::Type::OTHERS) ;       
			this->segments["transaction"] = Segment(Segment::Type::OTHERS) ;
			this->segments["buffer2write"]= Segment(Segment::Type::OTHERS) ;
		}
		void setUnique(){
			this->segments["data"] = Segment(Segment::Type::DATA) ;
			this->segments["index"]= Segment(Segment::Type::INDEX);
			this->segments["rollback"] = Segment(Segment::Type::ROLLBACK) ;
		}
};
#endif
