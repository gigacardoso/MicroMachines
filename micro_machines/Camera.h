#ifndef __CAMERA_H__
#define __CAMERA_H__

#define _USE_MATH_DEFINES

#include <string>
#include <cmath>
#include "cg/cg.h"
#include "Car.h"

namespace micro_machines{

	const double DTOR=0.01745329251994329547;

	class Camera:public cg::Entity,public cg::IDrawListener,public cg::IReshapeEventListener{
    
	private:
		bool _rotation,_twoPlayers;
		double _winWidth,_winHeight,_height,_initialHeight,_angle,_near,_far,_fov,_initialFov,_maxDifference;
		cg::Vector3d _up;
		Car* _car0;
		Car* _car1;
		bool _afterMenu;

	public:
		Camera();
		virtual ~Camera();
		void init();
		void draw();
		void onReshape(int width,int height);
		void updateProjectionValues();
		void afterMenu();
		void onePlayer();
		
	};
	
}

#endif