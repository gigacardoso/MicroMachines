#include "Camera.h"

namespace micro_machines{

	Camera::Camera():Entity("Camera"),_up(cg::Vector3d(0,1,0)){}

	Camera::~Camera(){}

	void Camera::init(){
		cg::tWindow win=cg::Manager::instance()->getApp()->getWindow();
		_winWidth=win.width;
		_winHeight=win.height;
		_car0=(Car*)cg::Registry::instance()->get("Car0");
		_car1=(Car*)cg::Registry::instance()->get("Car1");
		_initialHeight=cg::Properties::instance()->getDouble("CAMERA_HEIGHT");
		_height=_initialHeight;
		_angle=cg::Properties::instance()->getDouble("CAMERA_ANGLE")*DTOR;
		_initialFov=cg::Properties::instance()->getDouble("FOV");
		_fov=_initialFov;
		_maxDifference=cg::Properties::instance()->getDouble("MAX_DIFFERENCE");
		if(cg::Properties::instance()->getInt("CAMERA_ROTATION")!=0){
			_rotation=true;
		}
		else{
			_rotation=false;
		}
		_far=-10;
		_near=50;
		_afterMenu=false;
		_twoPlayers=true;
	}

	void Camera::draw(){
		if(_afterMenu){
			updateProjectionValues();
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			double car0X=_car0->xPosition();
			double car0Y=_car0->yPosition();
			double car0Z=_car0->zPosition();
			if(!_twoPlayers){
				double b=90*DTOR-_angle;
				double yDiff=tan(_angle)*_height*cos(_car0->angle()*DTOR);
				double xDiff=tan(_angle)*_height*-sin(_car0->angle()*DTOR);
				if(!_rotation){
					yDiff=tan(_angle)*_height;
					xDiff=0;
					_up[1]=sin(b);
					_up[2]=cos(b);
				}
				else{
					_up[0]=sin(b)*-cos((90-_car0->angle())*DTOR);
					_up[1]=sin(b)*cos(-_car0->angle()*DTOR);
					_up[2]=cos(b);
				}
				gluPerspective(_fov,16.0/9.0,_near,_far);
				gluLookAt(car0X-xDiff,car0Y-yDiff,_height,car0X,car0Y,car0Z,_up[0],_up[1],_up[2]);
			}
			if(_twoPlayers){
				double car1X=_car1->xPosition();
				double car1Y=_car1->yPosition();
				double car1Z=_car1->zPosition();
				double middleX=(car0X+car1X)/2.0;
				double middleY=(car0Y+car1Y)/2.0;
				double middleZ=(car0Z+car1Z)/2.0;
				double yDiff=tan(_angle)*_height;
				_up[0]=0;
				_up[1]=sin(90*DTOR-_angle);
				_up[2]=cos(90*DTOR-_angle);
				gluPerspective(_fov,16.0/9.0,_near,_far);
				gluLookAt(middleX,middleY-yDiff,_height,middleX,middleY,middleZ,_up[0],_up[1],_up[2]);
			}
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}
		else{
			double height=50.0/tan(M_PI/8.0);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(45,16.0/9.0,50,-1);
			gluLookAt(0,0,height,0,0,0,0,1,0);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}
	}

	void Camera::onReshape(int width,int height){
		double desiredRatio;
		if(_afterMenu){
			desiredRatio=16.0/9.0;
		}
		else{
			desiredRatio=16.0/9.0;
		}
		_winWidth=width;
		_winHeight=height;
		double ratio=_winWidth/_winHeight;
		double vWidth=_winWidth;
		double vHeight=_winHeight;
		double dx=0;
		double dy=0;
		if(ratio>desiredRatio){
			vWidth=vHeight*desiredRatio;
			dx=(_winWidth-vWidth)/2;
		}
		else{
			vHeight=vWidth*(1.0/desiredRatio);
			dy=(_winHeight-vHeight)/2;
		}
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport(dx,dy,vWidth,vHeight);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void Camera::updateProjectionValues(){
		if(!_twoPlayers){
			_fov=_initialFov+_car0->speed()*0.03;
		}
		if(_twoPlayers){
			double x=_car0->xPosition()-_car1->xPosition();
			double y=_car0->yPosition()-_car1->yPosition();
			double z=_car0->zPosition()-_car1->zPosition();
			double distance=sqrt(pow(x,2)+pow(y,2)+pow(z,2));
			double initialDv=(9.0/8.0)*_initialHeight*tan(_fov/2.0*DTOR);
			if(distance>initialDv){
				_height=distance/((9.0/8.0)*tan((_fov/2.0)*DTOR));
			}
			else{
				_height=_initialHeight;
			}
			int difference=abs(_car0->nTS()-_car1->nTS());
			if(difference>_maxDifference){
				if(_car0->nTS()>_car1->nTS()){
					_car0->incrPoints();
					_car1->setTS(_car0->section());
					_car0->reposition(_car1);
					_car1->reposition(_car0);
				}
				else{
					_car1->incrPoints();
					_car0->setTS(_car1->section());
					_car1->reposition(_car0);
					_car0->reposition(_car1);
				}
				_car0->resetNTS();
				_car1->resetNTS();
			}
		}
	}

	void Camera::afterMenu(){
		_afterMenu=true;
	}

	void Camera::onePlayer(){
		_twoPlayers=false;
	}

}
