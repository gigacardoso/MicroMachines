#ifndef __MENUCAMERA_H__
#define __MENUCAMERA_H__

#define _USE_MATH_DEFINES 

#include <string>
#include <cmath>
#include "cg/cg.h"
#include "MenuCamera.h"

namespace micro_machines{

	class MenuCamera:public cg::Entity,public cg::IDrawListener,public cg::IReshapeEventListener{
    
	private:
		double _winWidth,_winHeight,_height;

	public:
		MenuCamera(std::string id);
		virtual ~MenuCamera();
		void init();
		void draw();
		void onReshape(int width,int height);
		
	};
	
}

#endif