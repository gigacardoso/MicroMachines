#ifndef __MENU_H__
#define __MENU_H__

#include <string>
#include "cg/cg.h"

namespace micro_machines{

	class App;
	class MenuState;

	class Menu:public cg::Entity,public cg::IDrawListener,public cg::IKeyboardEventListener{
	
	private:
		App* _app;
		MenuState* _state;
		double _winWidth,_winHeight;
		bool _afterMenu;
		
	public:
		Menu(std::string id,App* app);
		~Menu();
		virtual void init();
		virtual void draw();
		void setState(MenuState* state);
		void onePlayer();
		void twoPlayers();
		void day();
		void night();
		void onKeyPressed(unsigned char key);
		void onKeyReleased(unsigned char key){}
		void onSpecialKeyPressed(int key);
		void onSpecialKeyReleased(int key){}

	};
	
}

#endif