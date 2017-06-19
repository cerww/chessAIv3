#ifndef KEYS_H
#define KEYS_H

#include <iostream>
#include <map>
#include <string>
enum class keyIDs{A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,INSERT,HOME,END,UP,DOWN,LEFT,RIGHT,NUM1,NUM2,NUM3,NUM4,NUM5,NUM6,NUM7,NUM8,NUM9,NUM0,LCTRL,RCTRL,LALT,RALT,LSHIFT,RSHIFT};
enum class mouseButton{RIGHT,LEFT,MIDDLE};
class inputManager{
public:
	inputManager();
	int getKey(keyIDs key){return keys[key];};
	int getMouse(mouseButton key){return mouse[key];};
	int x=0;
	int y=0;
	std::map<keyIDs,int> keys;
	std::map<mouseButton,int> mouse;
private:

};
#endif

