#include "CarCollision.h"
#include "Car.h"

namespace micro_machines{

	CarCollision::CarCollision(std::string id):Entity(id){}

	CarCollision::~CarCollision(){}

	void CarCollision::init(){
		_car0=(Car*)cg::Registry::instance()->get("Car0");
		_car1=(Car*)cg::Registry::instance()->get("Car1");
		_collisions=true;
		_afterMenu=false;
		_twoPlayers=true;
	}

	void CarCollision::update(unsigned long elapsed_millis){
		if(_afterMenu && _twoPlayers){
			int collisionType0=_car0->detectCollision(_car1);
			if(collisionType0!=NO_COLLISION && _collisions){
				collision(_car0,_car1,collisionType0);
				_collisions=false;
			}
			int collisionType1=_car1->detectCollision(_car0);
			if(collisionType1!=NO_COLLISION && _collisions){
				collision(_car1,_car0,collisionType1);
				_collisions=false;
			}
			if(collisionType0==NO_COLLISION && collisionType1==NO_COLLISION){
				_collisions=true;
			}
		}
	}

	void CarCollision::collision(Car* colliding,Car* collided,int collision){
		int way=UNDEF;
		double collidingSpeed=colliding->speed();
		double collidedSpeed=collided->speed();
		double speed=(collidingSpeed+collidedSpeed)/2.0;
		if(collidingSpeed==0){
			if(collision==TOP_COLLISION_TOP || collision==BOTTOM_COLLISION_TOP || collision==LEFT_COLLISION_TOP || collision==RIGHT_COLLISION_TOP){
				way=REAR;
			}
			else{
				way=FRONT;
			}
		}
		colliding->switchWay(way);
		colliding->collision();
		colliding->setSpeed(speed);
		/*if(way==UNDEF){
			cg::Vector3d v=colliding->velocity();
			colliding->moveCar(-v/10.0);
		}*/
		way=UNDEF;
		if(collidedSpeed==0){
			if(collision==TOP_COLLISION_TOP || collision==TOP_COLLISION_BOTTOM){
				way=REAR;
			}
			else{
				way=FRONT;
			}
		}
		collided->switchWay(way);
		collided->collision();
		collided->setSpeed(speed);
		/*if(way==UNDEF){
			cg::Vector3d v=collided->velocity();
			collided->moveCar(-v/10.0);
		}*/
		//std::cerr << colliding->getId() << " collided with " << collided->getId() << " with collision type: " << collision << std::endl;
	}

	void CarCollision::afterMenu(){
		_afterMenu=true;
	}

	void CarCollision::onePlayer(){
		_twoPlayers=false;
	}

}