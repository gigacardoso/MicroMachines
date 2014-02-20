#ifndef __CAR_H__
#define __CAR_H__

#define _USE_MATH_DEFINES

#include <string>
#include <cfloat>
#include <cmath>
#include "cg/cg.h"
#include "TrackSectionManager.h"
#include "ObstacleManager.h"
#include "Obstacle.h"
#include "PowerUpManager.h"

namespace micro_machines{

	const int UNDEF=0;
	const int FRONT=1;
	const int REAR=2;
	const int READY=3;
	const int SET_0=0;
	const int SET_1=1;

	const int NO_COLLISION=0;
	const int TOP_COLLISION_TOP=1;
	const int TOP_COLLISION_BOTTOM=2;
	const int BOTTOM_COLLISION_TOP=3;
	const int BOTTOM_COLLISION_BOTTOM=4;
	const int LEFT_COLLISION_TOP=5;
	const int LEFT_COLLISION_BOTTOM=6;
	const int RIGHT_COLLISION_TOP=7;
	const int RIGHT_COLLISION_BOTTOM=8;
	class Hud;
	class HeadLight;

	class Car:public cg::Entity,public cg::IDrawListener,public cg::IUpdateListener,public cg::IReshapeEventListener,public cg::IKeyboardEventListener{
	
	private:
		cg::Vector3d _position,_size,_direction;
		cg::Vector3d _v0,_v1,_v2,_v3;
		cg::Vector3d _velocity;
		cg::Vector3f _color,_initialColor;
		double _winWidth,_winHeight,_angle,_topSpeed,_breaking,_initialAcceleration,_acceleration,_deceleration,_fTime,_rTime,_dTime,_steering,_initialTopSpeed;
		double _bonusTime;
		bool _anotherCollision,_collision,_afterMenu,_active;
		int _way,_damage,_tSId,_keySet,_nTS,_points;
		TrackSectionManager* _tManager;
		TrackSection* _currentTS;
		Hud* _hud;
		PowerUpManager* _pManager;
		HeadLight* _hLight0;
		HeadLight* _hLight1;

		double randomBetween(double min,double max);
		bool badPosition(cg::Vector3d topLeft,cg::Vector3d topRight,cg::Vector3d bottomLeft,cg::Vector3d bottomRight);
		bool repositionCarX(double p);
		bool repositionCarY(double p);
		cg::Vector3d rotateZDegPosition(cg::Vector3d v,cg::Vector3d p,double a);

	public:
		Car(std::string id,cg::Vector3d position,int keySet);
		~Car();
		void init();
		void postInit();
		void update(unsigned long elapsed_millis);
		void draw();
		void onReshape(int width, int height);
		void onKeyPressed(unsigned char key);
		void onKeyReleased(unsigned char key);
		void onSpecialKeyPressed(int key);
		void onSpecialKeyReleased(int key);
		void nextTS();
		void previousTS();
		void setTS(int tsId);
		void setSpeed(double speed);
		void moveCar(cg::Vector3d move);
		int isCollision(cg::Vector3d topLeft,cg::Vector3d topRight,cg::Vector3d bottomLeft,cg::Vector3d bottomRight);
		int detectCollision(Car* car);
		void switchWay(int way);
		void collision();
		void resetNTS();
		void reposition(Car* car);
		void incrPoints();
		void afterMenu();
		void disable();
		
		double xPosition() const{
			return _position[0];
		}
		
		double yPosition() const{
			return _position[1];
		}
		
		double zPosition() const{
			return _position[2];
		}
		
		double angle() const{
			return _angle;
		}

		double speed() const{
			return sqrt(pow(_velocity[0],2)+pow(_velocity[1],2)+pow(_velocity[2],2));
		}

		int damage() const{
			return _damage;
		}

		int section() const{
			return _tSId;
		}

		int nTS() const{
			return _nTS;
		}

		cg::Vector3d velocity() const{
			return _velocity;
		}

		cg::Vector3f color() const{
			return _color;
		}

		int points() const{
			return _points;
		}
	
	};

}

#endif