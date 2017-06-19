#ifndef GENERATOR_H
#define GENERATOR_H

template<typename retVal>
class generatorFn{
public:
	generatorFn() = default;
	
}


template<typename fn,typename retVal>
class generator{
public:
	generator(fn f):m_function(f){};
	class iterator{
		public:
			retVal val;
		retVal& operator*(){
			return val;
		}
		void operator++(){
			
		}
	};
	template<typename...Args>
	retVal call(Args... args){
		return m_function(args...);
	}
private:
	fn m_function;
};


#endif

