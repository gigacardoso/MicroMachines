#include "MenuState.h"
#include "Menu.h"

namespace micro_machines{

	MenuState::MenuState(Menu* menu):_menu(menu){
		cg::tWindow win=cg::Manager::instance()->getApp()->getWindow();
		_winWidth=win.width;
		_winHeight=win.height;
	}

	MenuState::~MenuState(){}

	void MenuState::drawOptionsBeggining(){
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0,_winWidth,0,_winHeight);  
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
		glColor3d(0,1,0);
		cg::Util::instance()->drawBitmapString("CG 2010-11, IST",20,_winHeight-20);
		cg::Util::instance()->drawBitmapString("Joao Miguel das Neves Santos Ferreira  62529",20,_winHeight-40);
		cg::Util::instance()->drawBitmapString("Daniel Sousa Veloso de Oliveira Cardoso   66964",20,_winHeight-60);
		cg::Util::instance()->drawBitmapString("Francisco Afonso Raposo   66986",20,_winHeight-80);
	}

	void MenuState::drawOptionsEnd(){
        glDisable(GL_BLEND);
	}

}