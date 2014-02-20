#include "PopUpMenu.h"

namespace micro_machines{

	bool carLights=false;
	bool day=true;

	void mainMenu(int item){
		glutPostRedisplay();
		return;
	}

	void globalLightMenu(int item){
		switch(item){
			case(DAY):
				day=true;
				break;
			case(NIGHT):
				day=false;
				break;
			default:
				break;
		}
		glutPostRedisplay();
		return;
	}

	void carLightsMenu(int item){
		switch(item){
			case(LIGHTS_ON):
				carLights=true;
				break;
			case(LIGHTS_OFF):
				carLights=false;
				break;
			default:
				break;
		}
		glutPostRedisplay();
		return;
	}

	PopUpMenu::PopUpMenu(std::string id):Entity(id){}

	PopUpMenu::~PopUpMenu(){}

	void PopUpMenu::init(){
		int globalLightMenuId=glutCreateMenu(globalLightMenu);
		glutAddMenuEntry("Day",DAY);
		glutAddMenuEntry("Night",NIGHT);
		int carLightsMenuId=glutCreateMenu(carLightsMenu);
		glutAddMenuEntry("Lights On",LIGHTS_ON);
		glutAddMenuEntry("Lights Off",LIGHTS_OFF);
		int mainMenuId=glutCreateMenu(&mainMenu);
		glutAddSubMenu("Global Light",globalLightMenuId);
		glutAddSubMenu("Car Lights",carLightsMenuId);
		glutAttachMenu(GLUT_RIGHT_BUTTON);
		_light=(Light*)cg::Registry::instance()->get("Light");
		_day=true;
		_carLights=false;
		_afterMenu=false;
	}

	void PopUpMenu::update(unsigned long elapsed_millis){
		if(_afterMenu){
			if(day!=_day || carLights!=_carLights){
				_light->updateLights(carLights,day);
				_day=day;
				_carLights=carLights;
			}
		}
	}

	void PopUpMenu::afterMenu(){
		_afterMenu=true;
	}

	void PopUpMenu::initLights(bool hL,bool d){
		carLights=hL;
		day=d;
		_carLights=hL;
		_day=d;
		_light->updateLights(carLights,day);
	}

}