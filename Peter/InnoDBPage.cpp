#ifndef INNODB_PAGE_CPP
#define INNODB_PAGE_CPP
#include "..\Common\stdafx.cpp"
#include "Row.cpp"

namespace InnoDBPage{
	class Peter;
	typedef unsigned long long BYTE8;
	typedef unsigned short BYTE2;
	typedef unsigned char BYTE;
	enum FilPageType {
		HOLD = static_cast<BYTE2>(1),
		UNDO_LOG,
		INODE,
		IBUF_FREE_LIST,
		TYPE_ALLOCATED,
		IBUF_BITMAP,
		TYPE_SYS,
		TYPE_TRX_SYS,
		TYPE_FSP_HDR,
		TYPE_XDES,
		TYPE_BLOB,
		
		INDEX = static_cast<BYTE2>(0x45BF)
	};
	
	struct FileHeader{
		unsigned space_or_chksum;
		unsigned offset;
		std::shared_ptr<Peter> prev;
		std::shared_ptr<Peter> next;
		BYTE8 lsn;
		FilPageType type;
		BYTE8 flush;
		unsigned space_id;
	public:
		FileHeader() : type(FilPageType::INDEX) {  }
	};
	struct PageHeader{
		BYTE2 n_dir_slots;
		BYTE2 heap_top;
		BYTE2 n_heap;
		BYTE2 free;
		BYTE2 garbage;
		BYTE2 last_insert;
		BYTE2 direction;
		BYTE2 n_direction;
		BYTE2 n_recs;
		BYTE8 max_trx_id;
		BYTE2 level;
		std::weak_ptr<Peter> leaf; //???
		std::weak_ptr<Peter> top;
	};
	struct VirtualRecord : public Row {
		static RowHeader createSupremum(){
			RowHeader h;
			h.record_type = RowHeader::RecordType("011");
			
			return h;
		}
		static RowHeader createInfimum(RowHeader::Pointer next){
			RowHeader h;
			h.record_type = RowHeader::RecordType("010");
			h.flag4.back() = true;
			bool isLast = (next->head.record_type == RowHeader::RecordType("011"));
			bool isNull = (next)?true:false;
			assert(isLast||isNull);
			h.next_recorder = next;
			return h;
		}
		
		VirtualRecord() : Row(createSupremum()) { }
		VirtualRecord(RowHeader::Pointer next)
			: Row(createInfimum(next) ) { }
	}; 
	struct UserRecord : public Row {
		static RowHeader createUserRecord(RowHeader::Pointer next){
			RowHeader h;
			bool isLast = (next->head.record_type == RowHeader::RecordType("011"));
			bool isNode = (next->head.record_type == RowHeader::RecordType("000"));
			assert(isLast||isNode);
			h.next_recorder = next;
			return h;
		}
		UserRecord(RowHeader::Pointer next) : Row(createUserRecord(next)) { }
	}; 
	struct FreeSpace : public Row {
		static RowHeader createFreeSpace(){
			RowHeader h;
			h.flag4[2] = true; //空闲行的删除标记为true 
			return h;
		}
		FreeSpace() : Row(createFreeSpace()) { }
	};
	struct PageDirectory{
		std::vector<Field> directory;
	};
	struct FileTrailer{
		unsigned checksum;
		unsigned lsn;
	};
}
#endif