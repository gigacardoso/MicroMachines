#ifndef __NIGHTSELECTED_H__
#define __NIGHTSELECTED_H__

#include <string>
#include "cg/cg.h"
#include "MenuState.h"

namespace micro_machines{

	class NightSelected:public MenuState{
		
	public:
		NightSelected(Menu* menu);
		~NightSelected();
		void drawOptions();
		void keyPressed(unsigned char key);
		void specialKeyPressed(int key);

	};
	
}

#endif