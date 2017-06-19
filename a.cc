#include <iostream>
#include <type_traits>
template<long t>
struct factorial:std::integral_constant<long,t*factorial<t-1>::value>{};
template<>
struct factorial<0>:std::integral_constant<long,1>{};
int main(){
	std::cout<<factorial<5>::value <<std::endl;
	return 0;
}

