#ifndef __HUD_H__
#define __HUD_H__

#include <string>
#include <cfloat>
#include "cg/cg.h"
#include "Car.h"
#include "TrackSectionManager.h"

namespace micro_machines{

	class Hud:public cg::Entity,public cg::IDrawOverlayListener,public cg::IReshapeEventListener,public cg::IUpdateListener{
	
	private:
		unsigned _elapsedMillis,_elapsedSeconds,_elapsedMinutes;
		unsigned _lapMillis0,_lapSeconds0,_lapMinutes0,_lap0,_highestSection0;
		unsigned _lapMillis1,_lapSeconds1,_lapMinutes1,_lap1,_highestSection1;
		double _winWidth,_winHeight;
		std::string _speed,_damage,_nSections,_cSection,_time,_cLap,_lapTime;
		std::map<int,cg::Vector3d> _laps0;
		std::map<int,cg::Vector3d> _laps1;
		Car* _car0;
		Car* _car1;
		TrackSectionManager* _tManager;
		bool _afterMenu,_twoPlayers;
		
	public:
		Hud(std::string id);
		~Hud();
		void init();
		void drawOverlay();
		void onReshape(int width, int height);
		void update(unsigned long elapsed_millis);
		void updateLapInfo(int section,int carId);
		void afterMenu();
		void onePlayer();
		void drawDamageBar(int damage,int carId);

	};
	
}

#endif