#include "Car.h"
#include "TrackSectionManager.h"
#include "PowerUpManager.h"

namespace micro_machines{

	TrackSectionManager::TrackSectionManager(std::string id):cg::Group(id){}

	TrackSectionManager::~TrackSectionManager(){}

	void TrackSectionManager::createEntities(){
		_car0=(Car*)cg::Registry::instance()->get("Car0");
		_car1=(Car*)cg::Registry::instance()->get("Car1");
		_firstSectionX=0;
		_firstSectionY=0;
		_width=1;
		_height=1;
		int minX=0;
		int minY=0;
		int currentX=0;
		int currentY=0;
		double x=0;
		double y=0;
		double xSize=cg::Properties::instance()->getDouble("TRACKSECTION_WIDTH");
		double ySize=cg::Properties::instance()->getDouble("TRACKSECTION_HEIGHT");
		_sectionX=xSize;
		_sectionY=ySize;
		std::ifstream trackFile;
		std::string trackName=cg::Properties::instance()->getString("TRACK");
		trackFile.open(trackName.c_str(),std::ifstream::in);
		int exit,entry=BOTTOM;
		int i=0;
		TrackSection* t;
		while(trackFile.peek()>-1){
			++i;
			exit=trackFile.get()-48;
			std::ostringstream ss;
			ss<<"Section"<<i;
			t=new TrackSection(ss.str(),entry,exit,x,y);
			add(t);
			std::ostringstream os;
			os<<"ObstacleManager"<<i;
			add(new ObstacleManager(os.str(),t));
			entry=(exit+2)%4;
			switch(entry){
				case(TOP):
					y-=ySize;
					--currentY;
					if(currentY<minY){
						--minY;
					}
					break;
				case(BOTTOM):
					y+=ySize;
					++_height;
					++currentY;
					break;
				case(LEFT):
					x+=xSize;
					++_width;
					++currentX;
					break;
				case(RIGHT):
					x-=xSize;
					--currentX;
					if(currentX<minX){
						--minX;
					}
					break;
			}
		}
		_firstSectionX=-minX;
		_firstSectionY=-minY;
		_car0->postInit();
		_car1->postInit();
		_afterMenu=false;
		_width=abs(_width);
		_height=abs(_height);
	}

	void TrackSectionManager::postInit(){
		_nSections=size()/2;
		((PowerUpManager*)cg::Registry::instance()->get("PowerUpManager"))->createEntitiesAfterTM();
	}

	void TrackSectionManager::update(unsigned long elapsed_millis){
		if(_afterMenu){
			GroupUpdate::update(elapsed_millis);
		}
	}

	void TrackSectionManager::draw(){
		if(_afterMenu){
			GroupDraw::draw();
		}
	}

	bool TrackSectionManager::isCollision(cg::Vector3d topLeft,cg::Vector3d topRight,cg::Vector3d bottomLeft,cg::Vector3d bottomRight,int tSId){
		int id=tSId-1;
		if(id==0){
			id=_nSections;
		}
		for(int i=0;i<3;++id,++i){
			if(id==_nSections+1){
				id=1;
			}
			std::ostringstream oStream;
			oStream<<"ObstacleManager"<<id;
			ObstacleManager* oM=(ObstacleManager*)get(oStream.str());
			if(oM->isCollision(topLeft,topRight,bottomLeft,bottomRight)){
				return true;
			}
		}
		return false;
	}

	void TrackSectionManager::afterMenu(){
		_afterMenu=true;
		_car0->afterMenu();
		_car1->afterMenu();
	}

	void TrackSectionManager::drawMiniMap(double dx,double dy,double width,double height){
		double trackWidth=_width*_sectionX;
		double trackHeight=_height*_sectionY;
		double wCoeficient=width/trackWidth;
		double hCoeficient=height/trackHeight;
		double coeficient;
		if(wCoeficient<hCoeficient){
			coeficient=wCoeficient;
		}
		else{
			coeficient=hCoeficient;
		}
		int xRelPos=_firstSectionX;
		int yRelPos=_firstSectionY;
		double xPos=xRelPos*_sectionX*coeficient+(dx+(_sectionX*coeficient)/2.0);
		double yPos=yRelPos*_sectionY*coeficient+3*height+dy;
		for(int id=1;id<=_nSections;++id){
			std::ostringstream tSStream;
			tSStream<<"Section"<<id;
			TrackSection* tS=(TrackSection*)get(tSStream.str());
			int exit=tS->drawMiniMap(xPos,yPos,coeficient);
			switch(exit){
				case(TOP):
					++yRelPos;
					yPos=yRelPos*_sectionY*coeficient+3*height+dy;
					break;
				case(BOTTOM):
					--yRelPos;
					yPos=yRelPos*_sectionY*coeficient+3*height+dy;
					break;
				case(LEFT):
					--xRelPos;
					xPos=xRelPos*_sectionX*coeficient+(dx+(_sectionX*coeficient)/2.0);
					break;
				case(RIGHT):
					++xRelPos;
					xPos=xRelPos*_sectionX*coeficient+(dx+(_sectionX*coeficient)/2.0);
					break;
			}
		}
	}

}