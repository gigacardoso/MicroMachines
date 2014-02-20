#include "Obstacle.h"

namespace micro_machines{

	Obstacle::Obstacle(std::string id,double x,double y):cg::Entity(id),_position(cg::Vector3d(x,y,0)),_initialPosition(cg::Vector3d(x,y,0)){}

	Obstacle::~Obstacle(){}

	double Obstacle::randomBetween(double min,double max){
		return (rand()/(double)RAND_MAX*(max-min))+min;
	}

	void Obstacle::init(){
		double min_size=cg::Properties::instance()->getDouble("OBSTACLE_MIN_SIZE");
		double max_size=cg::Properties::instance()->getDouble("OBSTACLE_MAX_SIZE");
		cg::tWindow win=cg::Manager::instance()->getApp()->getWindow();
		_winWidth=win.width;
		_winHeight=win.height;
		_size=cg::Vector3d(50,50,50);
		_position[2]=25;
		_color=cg::Vector3f(randomBetween(0.1,0.9),randomBetween(0.1,0.9),randomBetween(0.1,0.9));
	}

	void Obstacle::draw(){}

	void Obstacle::update(unsigned long elapsed_millis){}

	bool Obstacle::isCollision(cg::Vector3d topLeft,cg::Vector3d topRight,cg::Vector3d bottomLeft,cg::Vector3d bottomRight){
		return false;
	}

}