#ifndef __ONEPLAYERSELECTED_H__
#define __ONEPLAYERSELECTED_H__

#include <string>
#include "cg/cg.h"
#include "MenuState.h"

namespace micro_machines{

	class OnePlayerSelected:public MenuState{

	public:
		OnePlayerSelected(Menu* menu);
		~OnePlayerSelected();
		void drawOptions();
		void keyPressed(unsigned char key);
		void specialKeyPressed(int key);

	};
	
}

#endif