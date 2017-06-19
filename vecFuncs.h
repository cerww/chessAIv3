#include <vector>
#include <algorithm>
#ifndef VECFUNCS_H
#define VECFUNCS_H
template <class T>
inline T vecMin(const std::vector<T>& v){
	T min = v[0];
	for(unsigned x = 1;x<v.size();++x){
		min = (min>v[x]?v[x]:min); 
	}return min;
}
template <class T>
inline T vecMax(const std::vector<T>& v){
	T min = v[0];
	for(unsigned x = 1;x<v.size();++x){
		min = (min<v[x]?v[x]:min); 
	}return min;
}
template<class T>
inline int findFirstInVec(std::vector<T> &v,T c){
	for(std::size_t i=0;i<v.size();++i){
		if(v[i]==c) return i;
	}return v.size();
}
template<class T>
inline std::vector<T> operator+(std::vector<T> one,const std::vector<T>& two){
	one.resize(one.size()+two.size());
	for(unsigned x = 0;x<two.size();++x){
		one[x+one.size()]=two[x];
	}return one;
}
template <class T>
inline void remFirstFromVec(std::vector<T>& v,T c){//keeps order
	for(std::size_t x = 0;x<v.size();++x){
		if(v[x]==c){
			v.erase(v.begin()+x);
			return;
		}
	}
}
template <class T>
inline void remFirstFromVecFast(std::vector<T>& v,T c){//loses order
	for(std::size_t x = 0;x<v.size();++x){
		if(v[x]==c){
			std::swap(v[x],v.back());
			v.pop_back();
			return;
		}
	}
}
template <class T>
inline void remFirstFromVecFast(std::vector<T>* v,T c){//loses order
	for(std::size_t x = 0;x<v->size();++x){
		if(v->at(x)==c){
			std::swap(v->at(x),v->back());
			v->pop_back();
			return;
		}
	}
}template <class T>
inline std::vector<T> remFirstFromVecFastR(std::vector<T> v,T c){//loses order
	for(std::size_t x = 0;x<v.size();++x){
		if(v[x]==c){
			std::swap(v[x],v.back());
			v.pop_back();
			return v;
		}
	}return v;
}
template <class T>
int removeIfInVec(std::vector<T>& v,T c){
	int num = 0;
	for(int x = v.size()-1;x!=-1;--x){
		if(v[x]==c){
			v.erase(v.begin()+x);
			++num;
		}
	}return num;
}
template <class T>
int removeIfInVec(std::vector<T>* v,T c){
	int num = 0;
	for(int x = v->size()-1;x!=-1;--x){
		if(v->at(x)==c){
			v->erase(v->begin()+x);
			++num;
		}
	}return num;
}
template<class T>
T cp(T a){return a;}
//template<class T>
//std::vector<T> vecSum
template<class T>
std::vector<T> operator|(const std::vector<T>& left,const std::vector<T>& right){
	
}
template<class T>
std::vector<T> operator&(const std::vector<T>& left,const std::vector<T>& right){
	std::vector<T> returnVec;
	for(auto& i:left){
		if(std::find(right.begin(),right.end(),i)!=right.end()){
			returnVec.push_back(i);
		}
	}return returnVec;
}
#endif
