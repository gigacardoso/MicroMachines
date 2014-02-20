#include "PowerUpManager.h"
#include "TrackSectionManager.h"

namespace micro_machines{

	PowerUpManager::PowerUpManager(std::string id):cg::Group(id){}

	PowerUpManager::~PowerUpManager(){}

	void PowerUpManager::createEntities(){
		_nPowerUps=cg::Properties::instance()->getInt("POWER_UPS");
		for(int i=0;i<_nPowerUps;++i){
			std::ostringstream ps;
			ps<<"PowerUp"<<i;
			add(new PowerUp(ps.str()));
		}
	}

	void PowerUpManager::postInit(){}

	void PowerUpManager::createEntitiesAfterTM(){
		double dToR=0.01745329251994329547;
		std::vector<int> sections;
		TrackSectionManager* tM=(TrackSectionManager*)cg::Registry::instance()->get("TrackSectionManager");
		int nSections=tM->nSections();
		for(int i=0;i<_nPowerUps;++i){
			std::ostringstream ps;
			ps<<"PowerUp"<<i;
			bool newSection=false;
			int section;
			while(!newSection){
				newSection=true;
				section=(rand()%nSections)+1;
				for(std::vector<int>::iterator it=sections.begin();it<sections.end();++it){
					if((*it)==section){
						newSection=false;
						break;
					}
				}
			}
			sections.push_back(section);
			std::ostringstream ss;
			ss<<"Section"<<section;
			TrackSection* tS=(TrackSection*)tM->get(ss.str());
			/*Atenção: Assume-se que as secções são quadradas*/
			double d=sin(45*dToR)*(tS->xSize()/2.0);
			cg::Vector3d pos;
			double angle;
			switch(tS->entry()){
				case(TOP):
					switch(tS->exit()){
						case(BOTTOM):
							angle=180;
							pos=cg::Vector3d(tS->xPosition(),tS->yPosition(),0);
							break;
						case(LEFT):
							angle=135;
							pos=cg::Vector3d(tS->xPosition()-tS->xSize()/2.0+d,tS->yPosition()+tS->ySize()/2.0-d,0);
							break;
						case(RIGHT):
							angle=225;
							pos=cg::Vector3d(tS->xPosition()+tS->xSize()/2.0-d,tS->yPosition()+tS->ySize()/2.0-d,0);
							break;
					}
					break;
				case(BOTTOM):
					switch(tS->exit()){
						case(TOP):
							angle=0;
							pos=cg::Vector3d(tS->xPosition(),tS->yPosition(),0);
							break;
						case(LEFT):
							angle=45;
							pos=cg::Vector3d(tS->xPosition()-tS->xSize()/2.0+d,tS->yPosition()-tS->ySize()/2.0+d,0);
							break;
						case(RIGHT):
							angle=315;
							pos=cg::Vector3d(tS->xPosition()+tS->xSize()/2.0-d,tS->yPosition()-tS->ySize()/2.0+d,0);
							break;
					}
					break;
				case(LEFT):
					switch(tS->exit()){
						case(TOP):
							angle=315;
							pos=cg::Vector3d(tS->xPosition()-tS->xSize()/2.0+d,tS->yPosition()+tS->ySize()/2.0-d,0);
							break;
						case(BOTTOM):
							angle=225;
							pos=cg::Vector3d(tS->xPosition()-tS->xSize()/2.0+d,tS->yPosition()-tS->ySize()/2.0+d,0);
							break;
						case(RIGHT):
							angle=270;
							pos=cg::Vector3d(tS->xPosition(),tS->yPosition(),0);
							break;
					}
					break;
				case(RIGHT):
					switch(tS->exit()){
						case(TOP):
							angle=45;
							pos=cg::Vector3d(tS->xPosition()+tS->xSize()/2.0-d,tS->yPosition()+tS->ySize()/2.0-d,0);
							break;
						case(BOTTOM):
							angle=135;
							pos=cg::Vector3d(tS->xPosition()+tS->xSize()/2.0-d,tS->yPosition()-tS->ySize()/2.0+d,0);
							break;
						case(LEFT):
							angle=90;
							pos=cg::Vector3d(tS->xPosition(),tS->yPosition(),0);
							break;
					}
					break;
			}
			PowerUp* pU=(PowerUp*)get(ps.str());
			pU->setPosition(pos);
			pU->setAngle(angle);
		}
	}

	bool PowerUpManager::isCollision(cg::Vector3d topLeft,cg::Vector3d topRight,cg::Vector3d bottomLeft,cg::Vector3d bottomRight){
		std::vector<Entity*>::iterator it;
		for(it=Group::begin();it<Group::end();++it){
			PowerUp* pU=(PowerUp*)(*it);
			if(pU->isCollision(topLeft,topRight,bottomLeft,bottomRight)){
				return true;
			}
		}
		return false;
	}

	void PowerUpManager::afterMenu(){
		std::vector<Entity*>::iterator it;
		for(it=Group::begin();it<Group::end();++it){
			PowerUp* pU=(PowerUp*)(*it);
			pU->afterMenu();
		}
	}

}