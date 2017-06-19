#ifndef APP_H
#define APP_H
#include <memory>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "inputManager.h"
class app{
	public:
		virtual void update();
		app();
		virtual ~app();
		void newWindow(const std::string &,const int &x,const int &y);
		void addBox(const std::string &,std::shared_ptr<sf::Drawable> square);
		//void addBox(const sf::Drawable &square);
		//bool removeBox(std::shared_ptr<sf::Drawable>);
		bool isRunning(){return wins;};
		virtual void run();
		void quit(){m_running = 0;};
		sf::Texture* getTexture(const std::string&);
		int getKey(const std::string& window,keyIDs key){return PressedKeys[window]->getKey(key);};
		sf::Font* getFont(const std::string& fontName);
		int getMouseClick(const std::string& window,mouseButton button){return PressedKeys[window]->getMouse(button);};
		sf::Vector2f getMouseCoords(const std::string& window){return sf::Vector2f(PressedKeys[window]->x,PressedKeys[window]->y);};
		//void draw();
		//std::map<std::string,std::vector<std::shared_ptr<sf::Drawable> > >D;
	protected:
		std::map<std::string,std::unique_ptr<sf::RenderWindow> > windows;
		
	private:
		std::map<std::string,std::unique_ptr<sf::Texture> > m_textures;
		std::map<std::string,std::unique_ptr<sf::Font> > m_fonts;
		//std::map<std::string,std::unique_ptr<sf::RenderWindow> > windows;
		std::vector<std::string> m_winNames;
		//std::map<std::string,std::unique_ptr<keys> > PressedKeys;
		std::map<std::string,std::unique_ptr<inputManager> > PressedKeys;
		bool m_running=true;
		unsigned int MouseLeft=0;
		unsigned int MouseRight=0;
		unsigned wins = 0;
		
};
#endif

