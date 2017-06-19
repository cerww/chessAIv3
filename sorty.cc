#include <vector>
#include <iostream>
#include <utility> //for swap with c++11
#include <map>
#include <array>
#include <random>
#include <algorithm>
//template<class T>
void inPlaceSelectSort(std::vector<int>& v){
	for(unsigned i = 0; i < v.size(); ++i){
		int index = i;
		for(unsigned int x = i; x < v.size(); ++x){
			if (v[x] > v[index])
				index=x;
			//index = v[x]>v[index]?x:index;
		}std::swap(v[i],v[index]);
	}
}
std::vector<int> notInPlaceSelectSort(std::vector<int> v){
	for(unsigned i = 0; i < v.size(); ++i){
		int index = i;
		for(unsigned int x = i; x < v.size(); ++x){
			if (v[x] > v[index])
				index=x;
		}std::swap(v[i],v[index]);
	}return v;
}
std::vector<int> notInPlaceSelectSort2(std::vector<int> v){
	std::vector<int> nl(v.size());
	for(unsigned i = 0;i<v.size();++i){
		int smallest = v[0];
		for(unsigned index = 1;index<v.size();++index){
			if(smallest>v[index]){
				smallest = v[index];
			}
		}
		remove(v.begin(),v.end(),smallest);
		nl[i] = std::move(smallest);
	}return nl;
}
void inPlaceInsertionSort(std::vector<int> &v){
	for(unsigned current = 0; current < v.size() ; ++current)
		for(int i = current; i>0 ;--i)
			if ( v[i] > v[i-1] )
			{
				std::swap(v[i],v[i-1]);
			}
			else
			{
				break;
			}
}
void inPlaceInsertionSort2(std::vector<int> &v){
	for(unsigned current = 0; current < v.size() ; ++current)
		for(int i = current; i>0&&v[i]>v[i-1] ;--i)
			std::swap(v[i],v[i-1]);
}
void shellSort(std::vector<int> &v){
	for(int k = v.size()/2;k!=0;k/=2)
		for(unsigned x = 0;x<v.size()-k;++x)
			for(int nx = x;nx>=0&&v[nx]>v[nx+k];nx-=k)
				std::swap(v[nx],v[nx+k]);
}
void bubbleSort(std::vector<int>& v){
	for(int i = v.size()-1;i>=0;--i){
		bool changed = 0;
		for(int k = 0;k<i;++k){
			if(v[k]>v[k+1]){
				std::swap(v[k],v[k+1]);
				changed = 1;
			}
		}
		if(!changed) break;
	}
}
int main(){
	std::random_device r;
	//std::vector<int> abc({1,6,23,2,2,2,2,8,8,8,8,8,8,2,8,3,32,765,2,2,2,2,2,2,2,26,432,8394,23424,4,35,5,2,4});
	std::vector<int> abc(100000);
	std::default_random_engine gen(r());
	std::uniform_int_distribution<int> dist(0,1000000000);
	for(auto& i:abc){
		i = dist(gen);
	}
	//shellSort(abc);
	//std::sort(abc.begin(),abc.end());
	//auto a = std::move(notInPlaceSelectSort2(abc));
	inPlaceSelectSort(abc);
	//bubbleSort(abc);
	//std::vector<int> opp{1,2,3,5};
	//std::vector<int> oppa{1,2,3};
	//std::vector<int> qu = opp & oppa;//

return 0;
}


