#include "app.h"
bool pointInBox(sf::Vector2f a,sf::Vector2f b,float z,float w){
	if(a.x>b.x&&a.x<b.x+z&&a.y>b.y&&a.y<b.y+w) return true;
	return false;
}
void app::update(){

if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
	++MouseLeft;
}else{
	MouseLeft=0;
}
if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
	++MouseRight;
}else{
	MouseRight=0;	
}
sf::Event event;
for(unsigned int x =0;x<m_winNames.size();++x){
	while(windows[m_winNames[x]]->pollEvent(event)){
		if (event.type == sf::Event::Closed){
            windows[m_winNames[x]]->close();
			//windows.erase(m_winNames[x]);
			wins--;
			continue;
        }
        if(event.type==sf::Event::MouseMoved){
			PressedKeys[m_winNames[x]]->x=event.mouseMove.x;
			PressedKeys[m_winNames[x]]->y=event.mouseMove.y;
		}
		if(event.type == sf::Event::MouseButtonPressed){
			if(event.mouseButton.button==sf::Mouse::Right)PressedKeys[m_winNames[x]]->mouse[mouseButton::RIGHT]++;
			if(event.mouseButton.button==sf::Mouse::Left)PressedKeys[m_winNames[x]]->mouse[mouseButton::LEFT]++;
			if(event.mouseButton.button==sf::Mouse::Middle)PressedKeys[m_winNames[x]]->mouse[mouseButton::MIDDLE]++;
		}
		if(event.type == sf::Event::MouseButtonReleased){
			if(event.mouseButton.button==sf::Mouse::Right)PressedKeys[m_winNames[x]]->mouse[mouseButton::RIGHT]=0;
			if(event.mouseButton.button==sf::Mouse::Left)PressedKeys[m_winNames[x]]->mouse[mouseButton::LEFT]=0;
			if(event.mouseButton.button==sf::Mouse::Middle)PressedKeys[m_winNames[x]]->mouse[mouseButton::MIDDLE]=0;
		}
		if(event.type==sf::Event::KeyPressed){
			if(event.key.code==sf::Keyboard::A)PressedKeys[m_winNames[x]]->keys[keyIDs::A]++;
			if(event.key.code==sf::Keyboard::B)PressedKeys[m_winNames[x]]->keys[keyIDs::B]++;
			if(event.key.code==sf::Keyboard::C)PressedKeys[m_winNames[x]]->keys[keyIDs::C]++;
			if(event.key.code==sf::Keyboard::D)PressedKeys[m_winNames[x]]->keys[keyIDs::D]++;
			if(event.key.code==sf::Keyboard::E)PressedKeys[m_winNames[x]]->keys[keyIDs::E]++;
			if(event.key.code==sf::Keyboard::F)PressedKeys[m_winNames[x]]->keys[keyIDs::F]++;
			if(event.key.code==sf::Keyboard::G)PressedKeys[m_winNames[x]]->keys[keyIDs::G]++;
			if(event.key.code==sf::Keyboard::H)PressedKeys[m_winNames[x]]->keys[keyIDs::H]++;
			if(event.key.code==sf::Keyboard::I)PressedKeys[m_winNames[x]]->keys[keyIDs::I]++;
			if(event.key.code==sf::Keyboard::J)PressedKeys[m_winNames[x]]->keys[keyIDs::J]++;
			if(event.key.code==sf::Keyboard::K)PressedKeys[m_winNames[x]]->keys[keyIDs::K]++;
			if(event.key.code==sf::Keyboard::L)PressedKeys[m_winNames[x]]->keys[keyIDs::L]++;
			if(event.key.code==sf::Keyboard::M)PressedKeys[m_winNames[x]]->keys[keyIDs::M]++;
			if(event.key.code==sf::Keyboard::N)PressedKeys[m_winNames[x]]->keys[keyIDs::N]++;
			if(event.key.code==sf::Keyboard::O)PressedKeys[m_winNames[x]]->keys[keyIDs::O]++;
			if(event.key.code==sf::Keyboard::P)PressedKeys[m_winNames[x]]->keys[keyIDs::P]++;
			if(event.key.code==sf::Keyboard::Q)PressedKeys[m_winNames[x]]->keys[keyIDs::Q]++;
			if(event.key.code==sf::Keyboard::R)PressedKeys[m_winNames[x]]->keys[keyIDs::R]++;
			if(event.key.code==sf::Keyboard::S)PressedKeys[m_winNames[x]]->keys[keyIDs::S]++;
			if(event.key.code==sf::Keyboard::T)PressedKeys[m_winNames[x]]->keys[keyIDs::T]++;
			if(event.key.code==sf::Keyboard::U)PressedKeys[m_winNames[x]]->keys[keyIDs::U]++;
			if(event.key.code==sf::Keyboard::V)PressedKeys[m_winNames[x]]->keys[keyIDs::V]++;
			if(event.key.code==sf::Keyboard::W)PressedKeys[m_winNames[x]]->keys[keyIDs::W]++;
			if(event.key.code==sf::Keyboard::X)PressedKeys[m_winNames[x]]->keys[keyIDs::X]++;
			if(event.key.code==sf::Keyboard::Y)PressedKeys[m_winNames[x]]->keys[keyIDs::Y]++;
			if(event.key.code==sf::Keyboard::Z)PressedKeys[m_winNames[x]]->keys[keyIDs::Z]++;
			if(event.key.code==sf::Keyboard::Num0)PressedKeys[m_winNames[x]]->keys[keyIDs::NUM0]++;
			if(event.key.code==sf::Keyboard::Num1)PressedKeys[m_winNames[x]]->keys[keyIDs::NUM1]++;
			if(event.key.code==sf::Keyboard::Num2)PressedKeys[m_winNames[x]]->keys[keyIDs::NUM2]++;
			if(event.key.code==sf::Keyboard::Num3)PressedKeys[m_winNames[x]]->keys[keyIDs::NUM3]++;
			if(event.key.code==sf::Keyboard::Num4)PressedKeys[m_winNames[x]]->keys[keyIDs::NUM4]++;
			if(event.key.code==sf::Keyboard::Num5)PressedKeys[m_winNames[x]]->keys[keyIDs::NUM5]++;
			if(event.key.code==sf::Keyboard::Num6)PressedKeys[m_winNames[x]]->keys[keyIDs::NUM6]++;
			if(event.key.code==sf::Keyboard::Num7)PressedKeys[m_winNames[x]]->keys[keyIDs::NUM7]++;
			if(event.key.code==sf::Keyboard::Num8)PressedKeys[m_winNames[x]]->keys[keyIDs::NUM8]++;
			if(event.key.code==sf::Keyboard::Num9)PressedKeys[m_winNames[x]]->keys[keyIDs::NUM9]++;
			if(event.key.code==sf::Keyboard::LControl)PressedKeys[m_winNames[x]]->keys[keyIDs::LCTRL]++;
			if(event.key.code==sf::Keyboard::RControl)PressedKeys[m_winNames[x]]->keys[keyIDs::RCTRL]++;
			if(event.key.code==sf::Keyboard::LShift)PressedKeys[m_winNames[x]]->keys[keyIDs::LSHIFT]++;
			if(event.key.code==sf::Keyboard::RShift)PressedKeys[m_winNames[x]]->keys[keyIDs::RSHIFT]++;
			}
		if(event.type==sf::Event::KeyReleased){
			if(event.key.code==sf::Keyboard::A)PressedKeys[m_winNames[x]]->keys[keyIDs::A]=0;
			if(event.key.code==sf::Keyboard::B)PressedKeys[m_winNames[x]]->keys[keyIDs::B]=0;
			if(event.key.code==sf::Keyboard::C)PressedKeys[m_winNames[x]]->keys[keyIDs::C]=0;
			if(event.key.code==sf::Keyboard::D)PressedKeys[m_winNames[x]]->keys[keyIDs::D]=0;
			if(event.key.code==sf::Keyboard::E)PressedKeys[m_winNames[x]]->keys[keyIDs::E]=0;
			if(event.key.code==sf::Keyboard::F)PressedKeys[m_winNames[x]]->keys[keyIDs::F]=0;
			if(event.key.code==sf::Keyboard::G)PressedKeys[m_winNames[x]]->keys[keyIDs::G]=0;
			if(event.key.code==sf::Keyboard::H)PressedKeys[m_winNames[x]]->keys[keyIDs::H]=0;
			if(event.key.code==sf::Keyboard::I)PressedKeys[m_winNames[x]]->keys[keyIDs::I]=0;
			if(event.key.code==sf::Keyboard::J)PressedKeys[m_winNames[x]]->keys[keyIDs::J]=0;
			if(event.key.code==sf::Keyboard::K)PressedKeys[m_winNames[x]]->keys[keyIDs::K]=0;
			if(event.key.code==sf::Keyboard::L)PressedKeys[m_winNames[x]]->keys[keyIDs::L]=0;
			if(event.key.code==sf::Keyboard::M)PressedKeys[m_winNames[x]]->keys[keyIDs::M]=0;
			if(event.key.code==sf::Keyboard::N)PressedKeys[m_winNames[x]]->keys[keyIDs::N]=0;
			if(event.key.code==sf::Keyboard::O)PressedKeys[m_winNames[x]]->keys[keyIDs::O]=0;
			if(event.key.code==sf::Keyboard::P)PressedKeys[m_winNames[x]]->keys[keyIDs::P]=0;
			if(event.key.code==sf::Keyboard::Q)PressedKeys[m_winNames[x]]->keys[keyIDs::Q]=0;
			if(event.key.code==sf::Keyboard::R)PressedKeys[m_winNames[x]]->keys[keyIDs::R]=0;
			if(event.key.code==sf::Keyboard::S)PressedKeys[m_winNames[x]]->keys[keyIDs::S]=0;
			if(event.key.code==sf::Keyboard::T)PressedKeys[m_winNames[x]]->keys[keyIDs::T]=0;
			if(event.key.code==sf::Keyboard::U)PressedKeys[m_winNames[x]]->keys[keyIDs::U]=0;
			if(event.key.code==sf::Keyboard::V)PressedKeys[m_winNames[x]]->keys[keyIDs::V]=0;
			if(event.key.code==sf::Keyboard::W)PressedKeys[m_winNames[x]]->keys[keyIDs::W]=0;
			if(event.key.code==sf::Keyboard::X)PressedKeys[m_winNames[x]]->keys[keyIDs::X]=0;
			if(event.key.code==sf::Keyboard::Y)PressedKeys[m_winNames[x]]->keys[keyIDs::Y]=0;
			if(event.key.code==sf::Keyboard::Z)PressedKeys[m_winNames[x]]->keys[keyIDs::Z]=0;
			if(event.key.code==sf::Keyboard::Num0)PressedKeys[m_winNames[x]]->keys[keyIDs::NUM0]=0;
			if(event.key.code==sf::Keyboard::Num1)PressedKeys[m_winNames[x]]->keys[keyIDs::NUM1]=0;
			if(event.key.code==sf::Keyboard::Num2)PressedKeys[m_winNames[x]]->keys[keyIDs::NUM2]=0;
			if(event.key.code==sf::Keyboard::Num3)PressedKeys[m_winNames[x]]->keys[keyIDs::NUM3]=0;
			if(event.key.code==sf::Keyboard::Num4)PressedKeys[m_winNames[x]]->keys[keyIDs::NUM4]=0;
			if(event.key.code==sf::Keyboard::Num5)PressedKeys[m_winNames[x]]->keys[keyIDs::NUM5]=0;
			if(event.key.code==sf::Keyboard::Num6)PressedKeys[m_winNames[x]]->keys[keyIDs::NUM6]=0;
			if(event.key.code==sf::Keyboard::Num7)PressedKeys[m_winNames[x]]->keys[keyIDs::NUM7]=0;
			if(event.key.code==sf::Keyboard::Num8)PressedKeys[m_winNames[x]]->keys[keyIDs::NUM8]=0;
			if(event.key.code==sf::Keyboard::Num9)PressedKeys[m_winNames[x]]->keys[keyIDs::NUM9]=0;
			if(event.key.code==sf::Keyboard::LControl)PressedKeys[m_winNames[x]]->keys[keyIDs::LCTRL]=0;
			if(event.key.code==sf::Keyboard::RControl)PressedKeys[m_winNames[x]]->keys[keyIDs::RCTRL]=0;
			if(event.key.code==sf::Keyboard::LShift)PressedKeys[m_winNames[x]]->keys[keyIDs::LSHIFT]=0;
			if(event.key.code==sf::Keyboard::RShift)PressedKeys[m_winNames[x]]->keys[keyIDs::RSHIFT]=0;
			}
		}
	}
}
void app::run(){
update();
}
void app::newWindow(const std::string &st,const int &x,const int &y){
	windows[st]=std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(x, y),st));
	PressedKeys[st]=std::unique_ptr<inputManager>(new inputManager());
	windows[st]->setFramerateLimit(60);
	m_winNames.push_back(st);
	++wins;
}
sf::Texture* app::getTexture(const std::string& fileName){
	auto it = m_textures.find(fileName);
	if(it==m_textures.end()){
		m_textures[fileName]=std::unique_ptr<sf::Texture>(new sf::Texture);
		m_textures[fileName]->loadFromFile(fileName);
	}return m_textures[fileName].get();
}
sf::Font* app::getFont(const std::string& fontName){
	auto it = m_fonts.find(fontName);
	if(it==m_fonts.end()){
		m_fonts[fontName]=std::unique_ptr<sf::Font>(new sf::Font);
		m_fonts[fontName]->loadFromFile(fontName);
	}return m_fonts[fontName].get();
}
app::app(){
//sf::RenderWindow* window;
//window = new sf::RenderWindow(sf::VideoMode(700, 700), "SFML works!");

}
app::~app(){
//delete window;
//for(unsigned int x =0;x<m_winNames.size();++x)
//delete windows[m_winNames[x]];
}
