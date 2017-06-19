#include <iostream>
#include <map>
#include <unordered_map>
#include <utility>
#include <array>
#include <algorithm>
#define TIME_TEST_START	time_t start;\
	time_t end;\
	start = time(NULL);
#define TIME_TEST_END 

#define TIME_TEST_END end = time(NULL);\
	std::cout<<end-start<<std::endl;
class abcn{
	public:
	std::array<int,20> p;// = 0
	abcn(){};
	abcn(int k){
		for(int i = 0;i<20;++i){
			this->p[i] = k*i;
		}
	};
	~abcn(){
		//std::cout<<"anc"<<std::endl;
	};
	
};
bool operator<(const abcn& right,const abcn& left){
	return right.p[0]<left.p[0];
}
bool operator>(const abcn& right,const abcn& left){
	return right.p[0]>left.p[0];
}
bool operator==(const abcn& right,const abcn& left){
	for(int i = 0;i<20;++i){
		if(right.p[i]!=left.p[i]) return 0;
	}
	return true;
}
namespace std{
	template<>
	class hash<abcn>{
		public:
		size_t operator()(const abcn& b)const {
			return b.p[0]*b.p[5]*b.p[13]*b.p[8];
		}
	};
};
int main(){
	std::unordered_map<abcn,int> test;
	//test[abcn(0)] = 0;
	//std::cout<<&test[0]<<std::endl;
	for(int i = 0;i<200000;++i){
		test[abcn(i)] = i;
		//std::cout<<&test[i]<<std::endl;
	}
	if(test.find(abcn(888888888))!=test.end()){
		std::cout<<'a'<<std::endl;
	}
	return 0;
}

