#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__

#include <string>
#include "cg/cg.h"

namespace micro_machines{

	class Obstacle:public cg::Entity,public cg::IDrawListener,public cg::IUpdateListener{
	
	protected:
		cg::Vector3d _initialPosition,_position,_size;
		cg::Vector3f _color;
		double _winWidth,_winHeight;
		
		double randomBetween(double min,double max);
		
	public:
		Obstacle(std::string id,double x,double y);
		~Obstacle();
		virtual void init();
		virtual void draw();
		virtual void update(unsigned long elapsed_millis);
		virtual bool isCollision(cg::Vector3d topLeft,cg::Vector3d topRight,cg::Vector3d bottomLeft,cg::Vector3d bottomRight);

	};
	
}

#endif