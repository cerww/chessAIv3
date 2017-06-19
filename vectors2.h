#ifndef VECTORS2_H
#define VECTORS2_H
#include <cstdint>
#include <tuple>
#include <type_traits>
#include <cmath>
//#include <vector>
#include <unordered_map>
namespace cw {

	template<class T>
	class vector2 {
	public:
		constexpr vector2() = default;
		constexpr vector2(const T& a, const T& b) :x(a), y(b) {};
		T x;
		T y;
		static_assert(std::is_integral<T>::value,"T is not integral");
	};

	template<class T>
	inline bool operator>(const vector2<T>& first, const vector2<T>& second) {
		return std::tie(first.x, first.y) > std::tie(second.x, second.y);
	}

	template<class T>
	inline bool operator<(const vector2<T>& first, const vector2<T>& second) {
		return std::tie(first.x, first.y) < std::tie(second.x, second.y);
	}

	template<class T>
	inline bool operator>=(const vector2<T>& first, const vector2<T>& second) {
		return std::tie(first.x, first.y) >= std::tie(second.x, second.y);
	}

	template<class T>
	inline bool operator<=(const vector2<T>& first, const vector2<T>& second) {
		return std::tie(first.x, first.y) <= std::tie(second.x, second.y);
	}

	template<class T>
	inline bool operator==(const vector2<T>& first, const vector2<T>& second) {
		return first.x==second.x&&first.y==second.y;
	}

	typedef vector2<int> vector2i;
	typedef vector2<uint32_t> vector2ui;

	typedef vector2<int16_t> vector2s;
	typedef vector2<uint16_t> vector2us;
	
	typedef vector2<int8_t> vector2b;
	typedef vector2<uint8_t> vector2ub;
	
	typedef vector2<int64_t> vector2ll;
	typedef vector2<uint64_t> vector2ull;
	
	template<class T>
	class iterVec2 {
	public:
		iterVec2()= default;
		iterVec2(const T& one, const T& two) {};
		T x;
		T y;
	private:
		T maxX;
		T maxY;
	};
};
//typedef cw::vector2i vector2;
namespace std {
	template<typename T>
	class hash<cw::vector2<T>> {
	public:
		size_t operator()(const cw::vector2<T>& v) const{
			return std::hash<T>()(v.x + v.y*v.x + v.y * 2 +(int)v.x^(int)v.y);
		}
	};
};

#endif // !VECTORS_H

