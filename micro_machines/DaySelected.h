#ifndef __DAYSELECTED_H__
#define __DAYSELECTED_H__

#include <string>
#include "cg/cg.h"
#include "MenuState.h"

namespace micro_machines{

	class DaySelected:public MenuState{
		
	public:
		DaySelected(Menu* menu);
		~DaySelected();
		void drawOptions();
		void keyPressed(unsigned char key);
		void specialKeyPressed(int key);

	};
	
}

#endif