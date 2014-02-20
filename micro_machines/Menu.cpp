#include "Menu.h"
#include "App.h"
#include "MenuState.h"
#include "OnePlayerSelected.h"
#include "TwoPlayersSelected.h"
#include "DaySelected.h"
#include "NightSelected.h"

namespace micro_machines{

	Menu::Menu(std::string id,App* app):Entity(id),_app(app){}

	Menu::~Menu(){}

	void Menu::init(){
		_state=new OnePlayerSelected(this);
		cg::tWindow win=cg::Manager::instance()->getApp()->getWindow();
		_winWidth=win.width;
		_winHeight=win.height;
		_afterMenu=false;
	}

	void Menu::draw(){
		if(!_afterMenu){
			glColor3d(0,0,0);
			glBegin(GL_QUADS);
			glVertex3d(-50,-50,0);
			glVertex3d(50,-50,0);
			glVertex3d(50,50,0);
			glVertex3d(-50,50,0);
			glEnd();
			_state->drawOptions();
		}
	}

	void Menu::setState(MenuState* state){
		_state=state;
	}

	void Menu::onePlayer(){
		_app->twoPlayers(false);
	}

	void Menu::twoPlayers(){
		_app->twoPlayers(true);
	}

	void Menu::day(){
		_app->day(true);
		_afterMenu=true;
	}

	void Menu::night(){
		_app->day(false);
		_afterMenu=true;
	}

	void Menu::onKeyPressed(unsigned char key){
		_state->keyPressed(key);	
	}

	void Menu::onSpecialKeyPressed(int key){
		_state->specialKeyPressed(key);
	}

}