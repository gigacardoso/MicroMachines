#include "MiniMap.h"
#include "Car.h"
#include "TrackSectionManager.h"

namespace micro_machines{

	MiniMap::MiniMap(std::string id):Entity(id){}

	MiniMap::~MiniMap(){}

	void MiniMap::init(){
		cg::tWindow win=cg::Manager::instance()->getApp()->getWindow();
		_winWidth=win.width;
		_winHeight=win.height;
		_afterMenu=false;
		_twoPlayers=true;
		_car0=(Car*)cg::Registry::instance()->get("Car0");
		_car1=(Car*)cg::Registry::instance()->get("Car1");
		_tManager=(TrackSectionManager*)cg::Registry::instance()->get("TrackSectionManager");
		_dx=0;
		_dy=0;
		_vWidth=_winWidth;
		_vHeight=_winHeight;
	}

	void MiniMap::onReshape(int width,int height){
		if(_afterMenu){	
			double desiredRatio=16.0/9.0;
			_winWidth=width;
			_winHeight=height;
			double ratio=_winWidth/_winHeight;
			_vWidth=_winWidth;
			_vHeight=_winHeight;
			_dx=0;
			_dy=0;
			if(ratio>desiredRatio){
				_vWidth=_vHeight*desiredRatio;
				_dx=(_winWidth-_vWidth)/2;
			}
			else{
				_vHeight=_vWidth*(1.0/desiredRatio);
				_dy=(_winHeight-_vHeight)/2;
			}
		}
	}

	void MiniMap::drawOverlay(){
		if(_afterMenu){
			glDisable(GL_LIGHTING);
			drawMiniMap();
			glEnable(GL_LIGHTING);
		}
	}

	void MiniMap::afterMenu(){
		_afterMenu=true;
	}

	void MiniMap::onePlayer(){
		_twoPlayers=false;
	}

	void MiniMap::drawMiniMap(){
		double mapWidth=_vWidth/4.0;
		double mapHeight=_vHeight/4.0;
		_tManager->drawMiniMap(_dx,_dy,mapWidth,mapHeight);
	}

}