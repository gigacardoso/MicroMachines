#ifndef __MENUSTATE_H__
#define __MENUSTATE_H__

#include <string>
#include "cg/cg.h"

namespace micro_machines{

	class Menu;

	class MenuState{
	
	protected:
		Menu* _menu;
		double _winWidth,_winHeight;
		
	public:
		MenuState(Menu* menu);
		~MenuState();
		void init(){}
		void drawOptionsBeggining();
		void drawOptionsEnd();
		virtual void drawOptions()=0;
		virtual void keyPressed(unsigned char key)=0;
		virtual void specialKeyPressed(int key)=0;

	};
	
}

#endif