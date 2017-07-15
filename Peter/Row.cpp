#ifndef ROW_CPP
#define ROW_CPP
#include "..\Common\stdafx.cpp"
#include "Field.cpp"
#include "RowHeader.cpp"

class Row {
	public:
		enum Type { COMPACT , REDUNDANT , COMPRESSED , DYNAMIC };
		bool isInfimum(){
			return ( head.record_type == RowHeader::RecordType("010") );
		}
		bool isSupremum(){
			return ( head.record_type == RowHeader::RecordType("011") );
		}
		bool isVirtualRecord(){
			return isInfimum() || isSupremum() ;
		}
		bool isFreeSpace(){
			return head.flag4[2] == true;
		}
		bool isUserRecord(){
			bool nextLast = (head.next_recorder->head.record_type == RowHeader::RecordType("011"));
			bool nextNode = (head.next_recorder->head.record_type == RowHeader::RecordType("000"));
			bool not3 = ! ( isVirtualRecord() || isFreeSpace() );
			return not3 && (nextNode||nextLast);
		}
		//���캯��Ⱥ 
//		Row(std::initializer_list<Field> il) : fields(il) { }
		Row(){
			fields.push_back("ROW_ID");
			fields.push_back("STR_COL");
		}
		Row(RowHeader h) : head(h) { }
		////�������Ƴ�ԱĿǰȫ��ʹ�� default �汾 
		//~Row() = default;
		//Row(const Row&) = default;
		//Row(Row&&) = default;
		//Row& operator=(const Row&) = default;
		//Row& operator=(Row&&) = default;

		//���ߺ��� 
		std::string screen(){
if(DEBUG_SCREEN) std::cerr<<"Row::screen called\n";
			std::string s;
			const std::string SEP = " , ";
			s+="{";
			if(isVirtualRecord()){
				s += (isInfimum() ? "Infimum," : "Supremum") ;
			}
			else{
				for(auto &f : fields){
					s += SEP + f.screen() ;
				}
			}
			s+="}";
if(DEBUG_SCREEN) std::cerr<<"Row::screen return\n";
			return s;
		}
		unsigned space(){ // ���ظ���ռ�õ��ڴ�ռ��С����λ�ֽ�
			unsigned byte = 0;
			byte += sizeof(Type) ;
			byte += sizeof(unsigned short) * sizeList.size() ;
			byte += (nullFlag.size()+7)/8;
			byte += 5;
			byte += std::accumulate(fields.begin(),fields.end(),
							0, Field::spaceSum);
			return byte;
		}
		
//	private:
		std::vector<unsigned short> sizeList;
		std::vector<bool> nullFlag;
		RowHeader head;
		std::vector<Field> fields;
		
		static const Type type = COMPACT;
};
#endif