#ifndef __TRACKSECTION_H__
#define __TRACKSECTION_H__

#define _USE_MATH_DEFINES

#include <string>
#include <cmath>
#include "cg/cg.h"

namespace micro_machines{
	
	const int TOP=0;
	const int BOTTOM=2;
	const int LEFT=1;
	const int RIGHT=3;

	const int CLEAR=0;
	const int VCOLLISION=1;
	const int HCOLLISION=2;
	const int OFF=3;
	const int NEXT=4;
	const int PREVIOUS=5;

	class Car;

	class TrackSection:public cg::Entity,public cg::IDrawListener,public cg::IUpdateListener{
		
	private:
		cg::Vector2d _position,_size;
		cg::Vector3f _color;
		double _winWidth,_winHeight,_trackWidth;
		int _entry,_exit;
		Car* _car0;
		Car* _car1;

		double randomBetween(double min,double max);

	public:
		TrackSection(std::string id,int entry,int exit,int x,int y);
		~TrackSection();
		void init();
		void draw();
		void update(unsigned long elapsed_millis);
		void registerCar(Car* car,int carId);
		int getStatus(cg::Vector3d topLeft,cg::Vector3d topRight,cg::Vector3d bottomLeft,cg::Vector3d bottomRight);
		int drawMiniMap(double xPos,double yPos,double coeficient);
		
		int entry() const{
			return _entry;
		}

		int exit() const{
			return _exit;
		}

		double xPosition() const{
			return _position[0];
		}
		
		double yPosition() const{
			return _position[1];
		}
		
		double xSize() const{
			return _size[0];
		}
		
		double ySize() const{
			return _size[1];
		}

		double tWidth() const{
			return _trackWidth;
		}
		
		Car* getCar(int carId){
			if(carId==0){
				return _car0;
			}
			if(carId==1){
				return _car1;
			}
			return 0;
		}

	};
	
}

#endif