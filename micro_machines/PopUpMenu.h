#ifndef __POPUPMENU_H__
#define __POPUPMENU_H__

#include <string>
#include <cmath>
#include "cg/cg.h"
#include "Light.h"

namespace micro_machines{
	
	enum MENU_ENTRY{
		DAY,
		NIGHT,
		LIGHTS_ON,
		LIGHTS_OFF,
	};

	class PopUpMenu:public cg::Entity,public cg::IUpdateListener{
    
	private:
		Light* _light;
		bool _day,_carLights,_afterMenu;

	public:
		PopUpMenu(std::string id);
		virtual ~PopUpMenu();
		void init();
		void update(unsigned long elapsed_millis);
		void updateLights();
		void afterMenu();
		void initLights(bool hL,bool d);
		
	};
	
}

#endif