#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <string>
#include "cg/cg.h"
#include "Obstacle.h"

namespace micro_machines{

	class Block:public Obstacle{

	public:
		Block(std::string id,double x,double y);
		~Block();
		void draw();
		bool isCollision(cg::Vector3d topLeft,cg::Vector3d topRight,cg::Vector3d bottomLeft,cg::Vector3d bottomRight);
		
	};
	
}

#endif