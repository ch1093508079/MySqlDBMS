#ifndef PETER_CPP
#define PETER_CPP
#include "..\Common\stdafx.cpp"
#include "Row.cpp"
#include "InnoDBPage.cpp"

class Peter{
	public:
		bool checkTrailer(){
			bool md5 = true;
			static_assert(sizeof(fileTrailer.lsn)== 4, "size assertion fail : fileTrailer.lsn");
			static_assert(sizeof(fileHeader.lsn) == 8, "size assertion fail : fileHeader.lsn");
			bool lsnEqual = fileTrailer.lsn == static_cast<unsigned>(fileHeader.lsn);
			return md5 && lsnEqual;
		}
		
		InnoDBPage::FileHeader		fileHeader;
		InnoDBPage::PageHeader		pageHeader;
		InnoDBPage::VirtualRecord	virtualRecord;
		InnoDBPage::UserRecord		userRecord;
		InnoDBPage::FreeSpace		freeSpace;
		InnoDBPage::PageDirectory	pageDirectory;
		InnoDBPage::FileTrailer		fileTrailer;
};

#endif