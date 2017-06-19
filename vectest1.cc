#include "vecFuncs.h"
#include <iostream>

int main(){
	std::vector<int> a = {1,23,3,5,6};
	remFirstFromVecFast(a,23);
	remFirstFromVecFast(a,5);
	remFirstFromVecFast(a,15324);
	for(auto x:a){
		std::cout<<x<<std::endl;
	}
return 0;	
}

