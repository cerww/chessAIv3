#ifndef VECS_H
#define VECS_H
template<class T>
class vector2{
	public:
		constexpr vector2(){};
		constexpr vector2(T one,T two):x(one),y(two){};
		T x;
		T y;
};
template<typename T>
inline bool operator==(const vector2<T>& one,const vector2<T>& two){
	return one.x==two.x&&one.y==two.y;
}
typedef vector2<int> vector2i;
typedef vector2<char> vector2Bytes;
#endif
