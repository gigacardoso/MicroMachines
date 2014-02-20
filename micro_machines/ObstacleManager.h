#ifndef __OBSTACLEMANAGER_H__
#define __OBSTACLEMANAGER_H__

#include <string>
#include "cg/cg.h"
#include "Ball.h"
#include "Block.h"
#include "Obstacle.h"
#include "TrackSection.h"

namespace micro_machines{

	const int BALL=0;
	const int BLOCK=1;

	class ObstacleManager:public cg::Group,public cg::GroupDraw,public cg::GroupUpdate{
	
	private:
		TrackSection* _section;

		double randomBetween(double min,double max);

	protected:
		void createEntities();
		void postInit();
		
	public:
		ObstacleManager(std::string id,TrackSection* tS);
		~ObstacleManager();
		bool isCollision(cg::Vector3d topLeft,cg::Vector3d topRight,cg::Vector3d bottomLeft,cg::Vector3d bottomRight);

		TrackSection* getTrack(){
			return _section;
		}

	};

}

#endif