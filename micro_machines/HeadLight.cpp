#include "HeadLight.h"

namespace micro_machines{
	
	HeadLight::HeadLight(std::string id,int idl,float x,float y,float z):Entity(id),_idl(idl),_x(x),_y(y),_z(z){}

	HeadLight::~HeadLight(){}

	void HeadLight::init(){
		_ambient=cg::Vector3f(0.2,0.2,0.2);
		_diffuse=cg::Vector3f(0.8,0.8,0.8);
		_specular=cg::Vector3f(0.5,0.5,0.5);
		_direction=cg::Vector3f(0,1,0);
	}

	void HeadLight::draw(){
		GLfloat position[]={_x,_y,_z,1};
		switch(_idl){
			case(1):
				glLightfv(GL_LIGHT1,GL_POSITION,position);
				glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,20.0);
				glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,_direction.get());
				glLightf(GL_LIGHT1,GL_CONSTANT_ATTENUATION,1);
				glLightfv(GL_LIGHT1,GL_AMBIENT,_ambient.get());
				glLightfv(GL_LIGHT1,GL_DIFFUSE,_diffuse.get());
				glLightfv(GL_LIGHT1,GL_SPECULAR,_specular.get());
				break;
			case(2):
				glLightfv(GL_LIGHT2,GL_POSITION,position);
				glLightf(GL_LIGHT2,GL_SPOT_CUTOFF,20.0);
				glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION,_direction.get());
				glLightf(GL_LIGHT2,GL_CONSTANT_ATTENUATION,1);
				glLightfv(GL_LIGHT2,GL_AMBIENT,_ambient.get());
				glLightfv(GL_LIGHT2,GL_DIFFUSE,_diffuse.get());
				glLightfv(GL_LIGHT2,GL_SPECULAR,_specular.get());
				break;
			case(3):
				glLightfv(GL_LIGHT3,GL_POSITION,position);
				glLightf(GL_LIGHT3,GL_SPOT_CUTOFF,20.0);
				glLightfv(GL_LIGHT3,GL_SPOT_DIRECTION,_direction.get());
				glLightf(GL_LIGHT3,GL_CONSTANT_ATTENUATION,1);
				glLightfv(GL_LIGHT3,GL_AMBIENT,_ambient.get());
				glLightfv(GL_LIGHT3,GL_DIFFUSE,_diffuse.get());
				glLightfv(GL_LIGHT3,GL_SPECULAR,_specular.get());
				break;
			case(4):
				glLightfv(GL_LIGHT4,GL_POSITION,position);
				glLightf(GL_LIGHT4,GL_SPOT_CUTOFF,20.0);
				glLightfv(GL_LIGHT4,GL_SPOT_DIRECTION,_direction.get());
				glLightf(GL_LIGHT4,GL_CONSTANT_ATTENUATION,1);
				glLightfv(GL_LIGHT4,GL_AMBIENT,_ambient.get());
				glLightfv(GL_LIGHT4,GL_DIFFUSE,_diffuse.get());
				glLightfv(GL_LIGHT4,GL_SPECULAR,_specular.get());
				break;
		}
	}

	void HeadLight::updatePosition(float x,float y,float z,float angle){
		double dToR=0.01745329251994329547;
		_direction[0]=cos((angle+90)*dToR);
		_direction[1]=sin((angle+90)*dToR);
		float alpha,module=sqrt(15.0*15.0+5.0*5.0);
		if(_idl==1 || _idl==3){
			alpha=M_PI-atan(3.0);
			_x=x+cos(angle*dToR+alpha)*module;
			_y=y+sin(angle*dToR+alpha)*module;
			_z=z;
		}
		if(_idl==2 || _idl==4){
			alpha=atan(3.0);
			_x=x+cos(angle*dToR+alpha)*module;
			_y=y+sin(angle*dToR+alpha)*module;
			_z=z;
		}
	}

}