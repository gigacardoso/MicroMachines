#ifndef __BALL_H__
#define __BALL_H__

#include <string>
#include "cg/cg.h"
#include "Car.h"
#include "Obstacle.h"

namespace micro_machines{

	class ObstacleManager;

	class Ball:public Obstacle{
	
	private:
		bool _active;
		double _trackWidth;
		cg::Vector3d _velocity;
		ObstacleManager* _oManager;
		
	public:
		Ball(std::string id,ObstacleManager* oM,double x,double y);
		~Ball();
		void draw();
		void update(unsigned long elapsed_millis);
		bool isCollision(cg::Vector3d topLeft,cg::Vector3d topRight,cg::Vector3d bottomLeft,cg::Vector3d bottomRight);
		
	};
	
}

#endif