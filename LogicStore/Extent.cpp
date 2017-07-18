#include "Page.cpp"
class Extent {
public:
	typedef std::array<Page,64> PageCollection;
private:
	PageCollection pages; //可改为 list 便于有序插入
	static Page np(){ return Page(Page::Type::FREE_LIST); }
	static Page np(unsigned cend){
		using namespace std;
		shared_ptr<Page> p;
		switch(cend){
		case 0:
			p = make_shared<Page>( Page(true) );
			break;
		case 1:
			p = make_shared<Page>( Page(false) );
			break;
		default:
			assert(cend>=2 || cend<0);
			assert(cend>=2);
			p = make_shared<Page>( np() );
			break;
		}
		return *p;
	}
public:
	inline unsigned countPage(){
		return 64;
	} 
	std::array<Page, 64>& getPages(){
		return pages;
	}
	Page& refPage(size_t j){
		assert(j<countPage());
		return getPages()[j];
	}
	Extent(){
		unsigned i=0;
		while(i<countPage()){
			pages[i] = np(i);
			i++;
		}
	}
};
