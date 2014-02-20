#ifndef __APP_H__
#define __APP_H__

#include "cg/cg.h"
#include "Camera.h"
#include "Car.h"
#include "CarCollision.h"
#include "HeadLight.h"
#include "Hud.h"
#include "Light.h"
#include "MiniMap.h"
#include "Menu.h"
#include "MenuCamera.h"
#include "TrackSectionManager.h"
#include "PopUpMenu.h"
#include "PowerUpManager.h"

namespace micro_machines{

	class App:public cg::Application {
	
	private:
		bool _twoPlayers,_day,_afterMenu;

	public:
		App();
		~App();
		void createEntities();
		void twoPlayers(bool tp);
		void day(bool l);

	};

}

#endif