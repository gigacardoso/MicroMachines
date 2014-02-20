#ifndef __CARCOLLISION_H__
#define __CARCOLLISION_H__

#include <string>
#include "cg/cg.h"

namespace micro_machines{

	class Car;

	class CarCollision:public cg::Entity,public cg::IUpdateListener{
	
	private:
		Car* _car0;
		Car* _car1;
		bool _collisions,_afterMenu,_twoPlayers;

		void collision(Car* colliding,Car* collided,int collision);

	public:
		CarCollision(std::string id);
		~CarCollision();
		void init();
		void update(unsigned long elapsed_millis);
		void afterMenu();
		void onePlayer();
	
	};

}

#endif