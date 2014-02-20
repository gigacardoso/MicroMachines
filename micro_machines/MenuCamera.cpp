#include "MenuCamera.h"

namespace micro_machines{

	MenuCamera::MenuCamera(std::string id):Entity(id){}

	MenuCamera::~MenuCamera(){}

	void MenuCamera::init(){
		cg::tWindow win=cg::Manager::instance()->getApp()->getWindow();
		_winWidth=win.width;
		_winHeight=win.height;
		_height=50.0/tan(M_PI/8.0);
	}

	void MenuCamera::draw(){
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45,1,50,-1);
		gluLookAt(0,0,_height,0,0,0,0,1,0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void MenuCamera::onReshape(int width,int height){
		_winWidth=width;
		_winHeight=height;
		double ratio=_winWidth/_winHeight;
		double vWidth=_winWidth;
		double vHeight=_winHeight;
		double dx=0;
		double dy=0;
		if(ratio>1){
			vWidth=vHeight*1;
			dx=(_winWidth-vWidth)/2;
		}
		else{
			vHeight=vWidth*1;
			dy=(_winHeight-vHeight)/2;
		}
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport(dx,dy,vWidth,vHeight);
	}

}