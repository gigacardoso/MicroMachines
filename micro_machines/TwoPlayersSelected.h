#ifndef __TWOPLAYERSSELECTED_H__
#define __TWOPLAYERSSELECTED_H__

#include <string>
#include "cg/cg.h"
#include "MenuState.h"

namespace micro_machines{

	class TwoPlayersSelected:public MenuState{

	public:
		TwoPlayersSelected(Menu* menu);
		~TwoPlayersSelected();
		void drawOptions();
		void keyPressed(unsigned char key);
		void specialKeyPressed(int key);

	};
	
}

#endif