#ifndef __POWERUP_H__
#define __POWERUP_H__

#include <string>
#include <cmath>
#include "cg/cg.h"

namespace micro_machines{

	class PowerUp:public cg::Entity,public cg::IDrawListener,public cg::IUpdateListener{
	
	private:
		cg::Vector3d _position,_size;
		bool _active,_afterMenu;
		double _activeTime,_angle;
		
		cg::Vector3d rotateZDegPosition(cg::Vector3d v,cg::Vector3d p,double a);

	public:
		PowerUp(std::string id);
		~PowerUp();
		void init();
		void update(unsigned long elapsed_millis);
		void draw();
		void setPosition(cg::Vector3d position);
		void setAngle(double angle);
		bool isCollision(cg::Vector3d topLeft,cg::Vector3d topRight,cg::Vector3d bottomLeft,cg::Vector3d bottomRight);
		void afterMenu();
	
	};

}

#endif