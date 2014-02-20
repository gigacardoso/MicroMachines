#include "DaySelected.h"
#include "NightSelected.h"
#include "OnePlayerSelected.h"
#include "Menu.h"

namespace micro_machines{

	DaySelected::DaySelected(Menu* menu):MenuState(menu){}

	DaySelected::~DaySelected(){}

	void DaySelected::drawOptions(){
		drawOptionsBeggining();
		glColor3d(1,1,1);
		cg::Util::instance()->drawBitmapString("Day",_winWidth/2.0,_winHeight/4.0);
		glColor3d(0.5294117647058824,0.8588235294117647,0.9607843137254902);
		cg::Util::instance()->drawBitmapString("Night",_winWidth/2.0,3*_winHeight/4.0);
		drawOptionsEnd();
	}

	void DaySelected::keyPressed(unsigned char key){
		switch(key){
			case(13):
				_menu->day();
				break;
			case(8):
				_menu->setState(new OnePlayerSelected(_menu));
				break;
		}
	}

	void DaySelected::specialKeyPressed(int key){
		switch(key){
			case(GLUT_KEY_UP):
				_menu->setState(new NightSelected(_menu));
				break;
			case(GLUT_KEY_DOWN):
				_menu->setState(new NightSelected(_menu));
				break;
		}
	}

}