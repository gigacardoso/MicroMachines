#include "Ball.h"
#include "ObstacleManager.h"

namespace micro_machines{

	Ball::Ball(std::string id,ObstacleManager* oM,double x,double y):Obstacle(id,x,y),_oManager(oM),_velocity(cg::Vector3d(0,0,0)),_trackWidth(cg::Properties::instance()->getDouble("TRACK_WIDTH")),_active(true){}

	Ball::~Ball(){}

	void Ball::draw(){
		cg::Vector3f diffuse=cg::Vector3f(0,0,0.5);
		cg::Vector3f specular=cg::Vector3f(1,1,1);
		float shininess=120.0f;
		glPushMatrix();
		glTranslated(_position[0],_position[1],_position[2]);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,diffuse.get());
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular.get());
		glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shininess);
		glutSolidSphere(_size[2],25,25);
		glPopMatrix();
	}

	void Ball::update(unsigned long elapsed_millis){
		double elapsed_sec=elapsed_millis/1000.0;
		if(_oManager->getTrack()->getCar(0)!=0 && _active){
			double carX=_oManager->getTrack()->getCar(0)->xPosition();
			double carY=_oManager->getTrack()->getCar(0)->yPosition();
			if(carX<_position[0]){
				_velocity[0]=-50;
			}
			if(carX>_position[0]){
				_velocity[0]=50;
			}
			if(carY<_position[1]){
				_velocity[1]=-50;
			}
			if(carY>_position[1]){
				_velocity[1]=50;
			}
		}
		else{
			if(_oManager->getTrack()->getCar(1)!=0 && _active){
				double carX=_oManager->getTrack()->getCar(1)->xPosition();
				double carY=_oManager->getTrack()->getCar(1)->yPosition();
				if(carX<_position[0]){
					_velocity[0]=-50;
				}
				if(carX>_position[0]){
					_velocity[0]=50;
				}
				if(carY<_position[1]){
					_velocity[1]=-50;
				}
				if(carY>_position[1]){
					_velocity[1]=50;
				}
			}
			else{
				for(int i=0;i<3;++i){
					_velocity[i]=0;
				}
			}
		}
		if(_oManager->getTrack()->getCar(0)==0 && _oManager->getTrack()->getCar(1)==0){
			_active=true;
		}
		_position+=_velocity*elapsed_sec;
	}

	bool Ball::isCollision(cg::Vector3d topLeft,cg::Vector3d topRight,cg::Vector3d bottomLeft,cg::Vector3d bottomRight){
		cg::Vector3d vMin=cg::Vector3d(_position[0]-_size[0]/1.5,_position[1]-_size[0]/1.5,_position[2]-_size[0]/1.5);
		cg::Vector3d vMax=cg::Vector3d(_position[0]+_size[0]/1.5,_position[1]+_size[0]/1.5,_position[2]+_size[0]/1.5);
		if(topLeft[0]<vMax[0] && topLeft[0]>vMin[0] && topLeft[1]<vMax[1] && topLeft[1]>vMin[1]){
			_active=false;
			return true;
		}
		if(topRight[0]<vMax[0] && topRight[0]>vMin[0] && topRight[1]<vMax[1] && topRight[1]>vMin[1]){
			_active=false;
			return true;
		}
		if(bottomLeft[0]<vMax[0] && bottomLeft[0]>vMin[0] && bottomLeft[1]<vMax[1] && bottomLeft[1]>vMin[1]){
			_active=false;
			return true;
		}
		if(bottomRight[0]<vMax[0] && bottomRight[0]>vMin[0] && bottomRight[1]<vMax[1] && bottomRight[1]>vMin[1]){
			_active=false;
			return true;
		}
		return false;
	}

}