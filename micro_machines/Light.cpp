#include "Light.h"

namespace micro_machines{
	
	Light::Light(std::string id):Entity(id){}

	Light::~Light(){}

	void Light::init(){
		_ambient=cg::Vector3f(0.2,0.2,0.2);
		_diffuse=cg::Vector3f(0.8,0.8,0.8);
		_specular=cg::Vector3f(0.5,0.5,0.5);
	}

	void Light::draw(){
		if(_afterMenu){
			double sOT=sqrt(1.0/3.0);
			GLfloat position[]={sOT,sOT,sOT,0};
			glLightfv(GL_LIGHT0,GL_POSITION,position);
			glLightfv(GL_LIGHT0,GL_AMBIENT,_ambient.get());
			glLightfv(GL_LIGHT0,GL_DIFFUSE,_diffuse.get());
			glLightfv(GL_LIGHT0,GL_SPECULAR,_specular.get());
		}
	}

	void Light::updateLights(bool headLights,bool day){
		if(headLights){
			glEnable(GL_LIGHT1);
			glEnable(GL_LIGHT2);
			if(_twoPlayers){
				glEnable(GL_LIGHT3);
				glEnable(GL_LIGHT4);
			}
		}
		else{
			glDisable(GL_LIGHT1);
			glDisable(GL_LIGHT2);
			if(_twoPlayers){
				glDisable(GL_LIGHT3);
				glDisable(GL_LIGHT4);
			}
		}
		if(day){
			glEnable(GL_LIGHT0);
		}
		else{
			glDisable(GL_LIGHT0);
		}
	}

	void Light::afterMenu(bool tp){
		_afterMenu=true;
		_twoPlayers=tp;
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
		if(_twoPlayers){
			glEnable(GL_LIGHT3);
			glEnable(GL_LIGHT4);
		}
		glShadeModel(GL_SMOOTH);
	}

}