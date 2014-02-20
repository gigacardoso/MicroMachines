#ifndef __TRACKSECTIONMANAGER_H__
#define __TRACKSECTIONMANAGER_H__

#include <string>
#include <fstream>
#include "cg/cg.h"
#include "TrackSection.h"
#include "ObstacleManager.h"

namespace micro_machines{

	class Car;

	class TrackSectionManager:public cg::Group,public cg::GroupDraw,public cg::GroupUpdate{
	
	private:
		Car* _car0;
		Car* _car1;
		int _nSections,_width,_height,_firstSectionX,_firstSectionY;
		double _sectionX,_sectionY;
		bool _afterMenu;

	protected:
		void createEntities();
		void postInit();
		
	public:
		TrackSectionManager(std::string id);
		~TrackSectionManager();
		void update(unsigned long elapsed_millis);
		void draw();
		bool isCollision(cg::Vector3d topLeft,cg::Vector3d topRight,cg::Vector3d bottomLeft,cg::Vector3d bottomRight,int tSId);
		void afterMenu();
		void drawMiniMap(double dx,double dy,double width,double height);
		
		int nSections() const{
			return _nSections;
		}
		
		Entity* get(std::string id){
			return cg::Group::get(id);
		}

	};

}

#endif