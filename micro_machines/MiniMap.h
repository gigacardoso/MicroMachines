#ifndef __MINIMAP_H__
#define __MINIMAP_H__

#include <string>
#include "cg/cg.h"

namespace micro_machines{

	class Car;
	class TrackSectionManager;

	class MiniMap:public cg::Entity,public cg::IDrawOverlayListener,public cg::IReshapeEventListener{
	
	private:
		bool _afterMenu,_twoPlayers;
		int _winWidth,_winHeight;
		double _vWidth,_vHeight,_dx,_dy;
		Car *_car0,*_car1;
		TrackSectionManager* _tManager;

		void drawMiniMap();
		
	public:
		MiniMap(std::string id);
		~MiniMap();
		void init();
		void onReshape(int width,int height);
		void drawOverlay();
		void afterMenu();
		void onePlayer();

	};
	
}

#endif