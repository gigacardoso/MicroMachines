#include "PowerUp.h"

namespace micro_machines{

	PowerUp::PowerUp(std::string id):Entity(id){}

	PowerUp::~PowerUp(){}

	void PowerUp::init(){
		double xSize=cg::Properties::instance()->getDouble("TRACKSECTION_WIDTH")/5.0;
		double ySize=cg::Properties::instance()->getDouble("TRACKSECTION_HEIGHT")/5.0;
		_size=cg::Vector3d(xSize,ySize,0);
		_active=false;
		_activeTime=0;
		_afterMenu=false;
	}

	void PowerUp::update(unsigned long elapsed_millis){
		if(_afterMenu){
			if(_active){
				_activeTime+=elapsed_millis;
				if(_activeTime>=3000){
					_active=false;
					_activeTime=0;
				}
			}
		}
	}

	void PowerUp::draw(){
		if(_afterMenu){
			std::vector<cg::Vector3d> points;
			cg::Vector3f blue=cg::Vector3f(0.5294117647058824,0.8588235294117647,0.9607843137254902);
			cg::Vector3f white=cg::Vector3f(1,1,1);
			if(_active){
				glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,white.get());
			}
			else{
				glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,blue.get());
			}
			double inc=_size[1]/6.0;
			for(int i=0;i<6;i+=2){
				points.push_back(rotateZDegPosition(cg::Vector3d(_position[0]-_size[0]/2.0,_position[1]-_size[1]/2.0+inc*i,0),_position,_angle));
				points.push_back(rotateZDegPosition(cg::Vector3d(_position[0],_position[1]-_size[1]/2.0+inc*(i+1),0),_position,_angle));
				points.push_back(rotateZDegPosition(cg::Vector3d(_position[0]+_size[0]/2.0,_position[1]-_size[1]/2.0+inc*i,0),_position,_angle));
				points.push_back(rotateZDegPosition(cg::Vector3d(_position[0]+_size[0]/2.0,_position[1]-_size[1]/2.0+inc*(i+1),0),_position,_angle));
				points.push_back(rotateZDegPosition(cg::Vector3d(_position[0],_position[1]-_size[1]/2.0+inc*(i+2),0),_position,_angle));
				points.push_back(rotateZDegPosition(cg::Vector3d(_position[0]-_size[0]/2.0,_position[1]-_size[1]/2.0+inc*(i+1),0),_position,_angle));
			}
			int i=0;
			for(std::vector<cg::Vector3d>::iterator it=points.begin();it<points.end();++it){
				if(i==0){
					glBegin(GL_LINE_LOOP);
					glNormal3d(0,0,1);
				}
				cg::Vector3d temp=(*it);
				glVertex3d(temp[0],temp[1],temp[2]);
				if(i==5){
					glEnd();
					i=0;
				}
				else{
					++i;
				}
			}
		}
	}

	cg::Vector3d PowerUp::rotateZDegPosition(cg::Vector3d v,cg::Vector3d p,double a){
		cg::Vector3d vector;
		vector=v;
		v-=p;
		v=rotateZDeg(v,a);
		v+=p;
		return v;
	}

	void PowerUp::setPosition(cg::Vector3d position){
		_position=position;
	}

	void PowerUp::setAngle(double angle){
		_angle=angle;
	}

	bool PowerUp::isCollision(cg::Vector3d topLeft,cg::Vector3d topRight,cg::Vector3d bottomLeft,cg::Vector3d bottomRight){
		if(!_active){	
			cg::Vector3d vMin=_position-_size/2.0;
			cg::Vector3d vMax=_position+_size/2.0;
			if(topLeft[0]<vMax[0] && topLeft[0]>vMin[0] && topLeft[1]<vMax[1] && topLeft[1]>vMin[1]){
				_active=true;
				return true;
			}
			if(topRight[0]<vMax[0] && topRight[0]>vMin[0] && topRight[1]<vMax[1] && topRight[1]>vMin[1]){
				_active=true;
				return true;
			}
			if(bottomLeft[0]<vMax[0] && bottomLeft[0]>vMin[0] && bottomLeft[1]<vMax[1] && bottomLeft[1]>vMin[1]){
				_active=true;
				return true;
			}
			if(bottomRight[0]<vMax[0] && bottomRight[0]>vMin[0] && bottomRight[1]<vMax[1] && bottomRight[1]>vMin[1]){
				_active=true;
				return true;
			}
		}
		return false;
	}

	void PowerUp::afterMenu(){
		_afterMenu=true;
	}

}