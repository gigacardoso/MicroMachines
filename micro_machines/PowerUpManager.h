#ifndef __POWERUPMANAGER_H__
#define __POWERUPMANAGER_H__

#include <string>
#include <cmath>
#include "cg/cg.h"
#include "PowerUp.h"

namespace micro_machines{

	class TrackSectionManager;

	class PowerUpManager:public cg::Group,public cg::GroupDraw,public cg::GroupUpdate{

	private:
		int _nPowerUps;

	protected:
		void createEntities();
		void postInit();
		
	public:
		PowerUpManager(std::string id);
		~PowerUpManager();
		bool isCollision(cg::Vector3d topLeft,cg::Vector3d topRight,cg::Vector3d bottomLeft,cg::Vector3d bottomRight);
		void createEntitiesAfterTM();
		void afterMenu();

	};

}

#endif