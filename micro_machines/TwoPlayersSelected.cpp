#include "TwoPlayersSelected.h"
#include "OnePlayerSelected.h"
#include "DaySelected.h"
#include "Menu.h"

namespace micro_machines{

	TwoPlayersSelected::TwoPlayersSelected(Menu* menu):MenuState(menu){}

	TwoPlayersSelected::~TwoPlayersSelected(){}

	void TwoPlayersSelected::drawOptions(){
		drawOptionsBeggining();
		glColor3d(0.5294117647058824,0.8588235294117647,0.9607843137254902);
		cg::Util::instance()->drawBitmapString("One Player",_winWidth/2.0,_winHeight/4.0);
		glColor3d(1,1,1);
		cg::Util::instance()->drawBitmapString("Two Players",_winWidth/2.0,3*_winHeight/4.0);
		drawOptionsEnd();
	}

	void TwoPlayersSelected::keyPressed(unsigned char key){
		switch(key){
			case(13):
				_menu->twoPlayers();
				_menu->setState(new DaySelected(_menu));
				break;
		}
	}

	void TwoPlayersSelected::specialKeyPressed(int key){
		switch(key){
			case(GLUT_KEY_UP):
				_menu->setState(new OnePlayerSelected(_menu));
				break;
			case(GLUT_KEY_DOWN):
				_menu->setState(new OnePlayerSelected(_menu));
				break;
		}
	}

}