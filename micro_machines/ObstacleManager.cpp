#include "ObstacleManager.h"

namespace micro_machines{

	ObstacleManager::ObstacleManager(std::string id,TrackSection* t):cg::Group(id),_section(t){}

	ObstacleManager::~ObstacleManager(){}

	double ObstacleManager::randomBetween(double min,double max){
		return(rand()/(double)RAND_MAX*(max-min))+min;
	}

	void ObstacleManager::createEntities(){
		int nObstacles=cg::Properties::instance()->getDouble("OBSTACLES_PER_SECTION");
		int obstacle;
		for(int i=0;i<nObstacles;++i){
			std::ostringstream os;
			os<<"Obstacle"<<i<<getId();
			obstacle=rand()%50;
			switch(obstacle){
				case(BALL):
					add(new Ball(os.str(),this,_section->xPosition()-_section->xSize()/2+rand()%(int)_section->tWidth(),_section->yPosition()-_section->ySize()/2+rand()%(int)_section->ySize()));
					break;
				case(BLOCK):
					add(new Block(os.str(),_section->xPosition()-_section->xSize()/2+rand()%(int)_section->tWidth(),_section->yPosition()-_section->ySize()/2+rand()%(int)_section->ySize()));
					break;
				default:
					add(new Block(os.str(),_section->xPosition()-_section->xSize()/2+rand()%(int)_section->tWidth(),_section->yPosition()-_section->ySize()/2+rand()%(int)_section->ySize()));
					break;
			}
		}
	}

	void ObstacleManager::postInit(){}

	bool ObstacleManager::isCollision(cg::Vector3d topLeft,cg::Vector3d topRight,cg::Vector3d bottomLeft,cg::Vector3d bottomRight){
		std::vector<Entity*>::iterator it;
		for(it=Group::begin();it<Group::end();++it){
			Obstacle* o=(Obstacle*)(*it);
			if(o->isCollision(topLeft,topRight,bottomLeft,bottomRight)){
				return true;
			}
		}
		return false;
	}

}