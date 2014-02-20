#include "App.h"

namespace micro_machines{

	App::App():cg::Application("config.ini"){
		_window.caption="Micro Machines";
		_window.width=640;
		_window.height=360;
	}

	App::~App(){}

	void App::createEntities(){
		addEntity(new Camera());
		addEntity(new Menu("Menu",this));
		addEntity(new Light("Light"));
		addEntity(new TrackSectionManager("TrackSectionManager"));
		addEntity(new PowerUpManager("PowerUpManager"));
		addEntity(new Car("Car0",cg::Vector3d(-10,0,0),SET_0));
		addEntity(new HeadLight("HeadLight0",1,-15,15,5));
		addEntity(new HeadLight("HeadLight1",2,-5,15,5));
		/*2nd player*/
		addEntity(new Car("Car1",cg::Vector3d(10,0,0),SET_1));
		addEntity(new CarCollision("CarCollision"));
		addEntity(new HeadLight("HeadLight2",3,5,15,5));
		addEntity(new HeadLight("HeadLight3",4,15,15,5));
		/**/
		addEntity(new Hud("Hud"));
		addEntity(new PopUpMenu("PopUpMenu"));
		addEntity(new MiniMap("MiniMap"));
	}

	void App::twoPlayers(bool tp){
		_twoPlayers=tp;
	}

	void App::day(bool l){
		_day=l;
		_afterMenu=true;
		Camera* camera=(Camera*)cg::Registry::instance()->get("Camera");
		camera->afterMenu();
		Light* light=(Light*)cg::Registry::instance()->get("Light");
		light->afterMenu(_twoPlayers);
		((TrackSectionManager*)cg::Registry::instance()->get("TrackSectionManager"))->afterMenu();
		((PowerUpManager*)cg::Registry::instance()->get("PowerUpManager"))->afterMenu();
		CarCollision* carCollision=(CarCollision*)cg::Registry::instance()->get("CarCollision");
		carCollision->afterMenu();
		Hud* hud=(Hud*)cg::Registry::instance()->get("Hud");
		hud->afterMenu();
		PopUpMenu* popUpMenu=(PopUpMenu*)cg::Registry::instance()->get("PopUpMenu");
		popUpMenu->afterMenu();
		popUpMenu->initLights(!_day,_day);
		MiniMap* miniMap=(MiniMap*)cg::Registry::instance()->get("MiniMap");
		miniMap->afterMenu();
		if(!_twoPlayers){
			camera->onePlayer();
			hud->onePlayer();
			carCollision->onePlayer();
			Car* car1=(Car*)cg::Registry::instance()->get("Car1");
			car1->disable();
			miniMap->onePlayer();
		}
	}

}