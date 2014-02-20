#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <string>
#include "cg/cg.h"

namespace micro_machines{

	class Light:public cg::Entity,public cg::IDrawListener{
	
	private:
		cg::Vector3f _ambient,_diffuse,_specular;
		bool _headLights,_day,_afterMenu,_twoPlayers;

	public:
		Light(std::string id);
		~Light();
		void init();
		void draw();
		void updateLights(bool headLights,bool day);
		void afterMenu(bool tp);
		
	};
	
}

#endif