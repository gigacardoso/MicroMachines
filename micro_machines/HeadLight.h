#ifndef __HEADLIGHT_H__
#define __HEADLIGHT_H__

#define _USE_MATH_DEFINES

#include <string>
#include <cmath>
#include "cg/cg.h"

namespace micro_machines{

	class HeadLight:public cg::Entity,public cg::IDrawListener{
	
	private:
		cg::Vector3f _ambient,_diffuse,_specular,_direction;
		float _x,_y,_z;
		int _idl;

	public:
		HeadLight(std::string id,int idl,float x,float y,float z);
		~HeadLight();
		void init();
		void draw();
		void updatePosition(float x,float y,float z,float angle);
		
	};
	
}

#endif