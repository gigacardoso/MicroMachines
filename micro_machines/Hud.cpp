#include "Hud.h"

namespace micro_machines{
	
	Hud::Hud(std::string id):Entity(id){}

	Hud::~Hud(){}

	void Hud::init(){
		cg::tWindow win=cg::Manager::instance()->getApp()->getWindow();
		_winWidth=win.width;
		_winHeight=win.height;
		_car0=(Car*)cg::Registry::instance()->get("Car0");
		_car1=0;
		_car1=(Car*)cg::Registry::instance()->get("Car1");
		_tManager=(TrackSectionManager*)cg::Registry::instance()->get("TrackSectionManager");
		_elapsedMinutes=0;
		_elapsedSeconds=0;
		_elapsedMillis=0;
		_lapMinutes0=0;
		_lapSeconds0=0;
		_lapMillis0=0;
		_highestSection0=1;
		_lap0=1;
		_lapMinutes1=0;
		_lapSeconds1=0;
		_lapMillis1=0;
		_highestSection1=1;
		_lap1=1;
		_afterMenu=false;
		_twoPlayers=true;
	}

	void Hud::drawOverlay(){
		if(_afterMenu){
			glDisable(GL_LIGHTING);
			/*Middle*/
			glColor3d(1,1,1);
			/*cg::Vector3f white=cg::Vector3f(1,1,1);
			glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,white.get());*/
			/*Time Elapsed*/
			std::ostringstream timeStream;
			timeStream<<"Time: "<<_elapsedMinutes<<":"<<_elapsedSeconds<<":"<<_elapsedMillis;
			_time=timeStream.str();
			cg::Util::instance()->drawBitmapString(_time,_winWidth/2-50,_winHeight-20);
			/*Sections*/
			/*std::ostringstream sectionStream;
			sectionStream<<_tManager->nSections()<<" sections";
			_nSections=sectionStream.str();
			cg::Util::instance()->drawBitmapString(_nSections,_winWidth/2-50,_winHeight-40);*/

			/*Player 1*/
			glColor3d(0,1,0);
			/*cg::Vector3f green=cg::Vector3f(0,1,0);
			glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,green.get());*/
			/*Current Section*/
			/*std::ostringstream cSectionStream;
			cSectionStream<<"Current Section: "<<_car0->section();
			_cSection=cSectionStream.str();
			cg::Util::instance()->drawBitmapString(_cSection,0,_winHeight-20);*/
			if(!_twoPlayers){
				/*Best Lap*/
				std::ostringstream bestLapStream;
				cg::Vector3d fastest=cg::Vector3d(DBL_MAX,DBL_MAX,DBL_MAX);
				int lapN=0;
				for(std::map<int,cg::Vector3d>::iterator it=_laps0.begin();it!=_laps0.end();++it){
					std::ostringstream lapTimesStream;
					cg::Vector3d temp=(*it).second;
					if(temp[2]==fastest[2]){
						if(temp[1]==fastest[1]){
							if(temp[0]<fastest[0]){
								fastest=temp;
								lapN=(*it).first;
							}
						}
						else{
							if(temp[1]<fastest[1]){
								fastest=temp;
								lapN=(*it).first;
							}
						}
					}
					else{
						if(temp[2]<fastest[2]){
							fastest=temp;
							lapN=(*it).first;
						}
					}
				}
				bestLapStream<<"Fastest Lap "<<lapN<<" "<<fastest[2]<<":"<<fastest[1]<<":"<<fastest[0];
				if(_lap0>1){
					cg::Util::instance()->drawBitmapString(bestLapStream.str(),10,200);
				}
				/*Lap Time*/
				std::ostringstream lapTimeStream;
				lapTimeStream<<"Lap Time: "<<_lapMinutes0<<":"<<_lapSeconds0<<":"<<_lapMillis0;
				_lapTime=lapTimeStream.str();
				cg::Util::instance()->drawBitmapString(_lapTime,10,160);
				/*Lap*/
				std::ostringstream lapStream;
				lapStream<<"Current Lap: "<<_lap0;
				_cLap=lapStream.str();
				cg::Util::instance()->drawBitmapString(_cLap,10,120);
			}
			else{
				/*Points*/
				std::ostringstream pointsStream;
				pointsStream<<"Points: "<<_car0->points();
				cg::Util::instance()->drawBitmapString(pointsStream.str(),10,120);
			}
			/*Speed*/
			std::ostringstream speedStream;
			speedStream<<"Speed: "<<_car0->speed();
			_speed=speedStream.str();
			cg::Util::instance()->drawBitmapString(_speed,10,80);
			/*Damage*/
			std::ostringstream damageStream;
			damageStream<<"Damage:";
			_damage=damageStream.str();
			cg::Util::instance()->drawBitmapString(_damage,10,50);
			drawDamageBar(_car0->damage(),0);

			/*Player 2*/
			if(_twoPlayers){
				glColor3d(0,1,1);
				/*cg::Vector3f greenblue=cg::Vector3f(0,1,1);
				glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,greenblue.get());*/
				/*Current Section*/
				/*std::ostringstream cSectionStream;
				cSectionStream<<"Current Section: "<<_car1->section();
				_cSection=cSectionStream.str();
				cg::Util::instance()->drawBitmapString(_cSection,_winWidth-165,_winHeight-20);*/
				/*Best Lap (not used in two players mode)
				std::ostringstream bestLapStream;
				cg::Vector3d fastest=cg::Vector3d(DBL_MAX,DBL_MAX,DBL_MAX);
				int lapN=0;
				for(std::map<int,cg::Vector3d>::iterator it=_laps1.begin();it!=_laps1.end();++it){
					std::ostringstream lapTimesStream;
					cg::Vector3d temp=(*it).second;
					if(temp[2]==fastest[2]){
						if(temp[1]==fastest[1]){
							if(temp[0]<fastest[0]){
								fastest=temp;
								lapN=(*it).first;
							}
						}
						else{
							if(temp[1]<fastest[1]){
								fastest=temp;
								lapN=(*it).first;
							}
						}
					}
					else{
						if(temp[2]<fastest[2]){
							fastest=temp;
							lapN=(*it).first;
						}
					}
				}
				bestLapStream<<"Fastest Lap "<<lapN<<" "<<fastest[2]<<":"<<fastest[1]<<":"<<fastest[0];
				if(_lap1>1){
					cg::Util::instance()->drawBitmapString(bestLapStream.str(),_winWidth-165,200);
				}
				Lap Time
				std::ostringstream lapTimeStream;
				lapTimeStream<<"Lap Time: "<<_lapMinutes1<<":"<<_lapSeconds1<<":"<<_lapMillis1;
				_lapTime=lapTimeStream.str();
				cg::Util::instance()->drawBitmapString(_lapTime,_winWidth-165,160);
				Lap
				std::ostringstream lapStream;
				lapStream<<"Current Lap: "<<_lap1;
				_cLap=lapStream.str();
				cg::Util::instance()->drawBitmapString(_cLap,_winWidth-165,120);*/
				/*Points*/
				std::ostringstream pointsStream;
				pointsStream<<"Points: "<<_car1->points();
				cg::Util::instance()->drawBitmapString(pointsStream.str(),_winWidth-165,120);
				/*Speed*/
				std::ostringstream speedStream;
				speedStream<<"Speed: "<<_car1->speed();
				_speed=speedStream.str();
				cg::Util::instance()->drawBitmapString(_speed,_winWidth-165,80);
				/*Damage*/
				std::ostringstream damageStream;
				damageStream<<"Damage:";
				_damage=damageStream.str();
				cg::Util::instance()->drawBitmapString(_damage,_winWidth-165,50);
				drawDamageBar(_car1->damage(),1);
			}
			glEnable(GL_LIGHTING);
		}
	}

	void Hud::onReshape(int width,int height){
		_winWidth=width;
		_winHeight=height;
	}

	void Hud::update(unsigned long elapsed_millis){
		if(_afterMenu){
			_elapsedMillis+=elapsed_millis;
			_lapMillis0+=elapsed_millis;
			_lapMillis1+=elapsed_millis;
			if(_elapsedMillis>=1000){
				_elapsedSeconds+=_elapsedMillis/1000;
				_elapsedMillis=_elapsedMillis%1000;
			}
			if(_lapMillis0>=1000){
				_lapSeconds0+=_lapMillis0/1000;
				_lapMillis0=_lapMillis0%1000;
			}
			if(_lapMillis1>=1000){
				_lapSeconds1+=_lapMillis1/1000;
				_lapMillis1=_lapMillis1%1000;
			}
			if(_elapsedSeconds>=60){
				_elapsedMinutes+=_elapsedSeconds/60;
				_elapsedSeconds=_elapsedSeconds%60;
			}
			if(_lapSeconds0>=60){
				_lapMinutes0+=_lapSeconds0/60;
				_lapSeconds0=_lapSeconds0%60;
			}
			if(_lapSeconds1>=60){
				_lapMinutes1+=_lapSeconds1/60;
				_lapSeconds1=_lapSeconds1%60;
			}
		}
	}

	void Hud::updateLapInfo(int section,int carId){
		switch(carId){
			case(0):
				if(section==_highestSection0+1 || (section==1 && _highestSection0==_tManager->nSections())){
					if(section==1){
						_highestSection0=1;
					}
					else{
						++_highestSection0;
					}
					if(_highestSection0==1){
						cg::Vector3d time=cg::Vector3d(_lapMillis0,_lapSeconds0,_lapMinutes0);
						_laps0.insert(std::pair<int,cg::Vector3d>(_lap0,time));
						_lapMillis0=0;
						_lapSeconds0=0;
						_lapMinutes0=0;
						++_lap0;
					}
				}
				break;
			case(1):
				if(section==_highestSection1+1 || (section==1 && _highestSection1==_tManager->nSections())){
					if(section==1){
						_highestSection1=1;
					}
					else{
						++_highestSection1;
					}
					if(_highestSection1==1){
						cg::Vector3d time=cg::Vector3d(_lapMillis1,_lapSeconds1,_lapMinutes1);
						_laps1.insert(std::pair<int,cg::Vector3d>(_lap1,time));
						_lapMillis1=0;
						_lapSeconds1=0;
						_lapMinutes1=0;
						++_lap1;
					}
				}
				break;
		}
	}

	void Hud::afterMenu(){
		_afterMenu=true;
	}

	void Hud::onePlayer(){
		_twoPlayers=false;
	}

	void Hud::drawDamageBar(int damage,int carId){
		int x;
		if(carId==0){
			x=10;
		}
		else{
			x=_winWidth-165;
		}
		glLineWidth(0.1);
		cg::Vector2d topLeft=cg::Vector2d(x,40);
		cg::Vector2d topRight=cg::Vector2d(x+100,40);
		cg::Vector2d bottomLeft=cg::Vector2d(x,20);
		cg::Vector2d bottomRight=cg::Vector2d(x+100,20);
		cg::Vector2d topDmg=cg::Vector2d(x+damage,40);
		cg::Vector2d bottomDmg=cg::Vector2d(x+damage,20);
		glBegin(GL_QUADS);
		glVertex3d(topLeft[0],topLeft[1],0);
		glVertex3d(topDmg[0],topDmg[1],0);
		glVertex3d(bottomDmg[0],bottomDmg[1],0);
		glVertex3d(bottomLeft[0],bottomLeft[1],0);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex3d(topLeft[0],topLeft[1],0);
		glVertex3d(topDmg[0],topDmg[1],0);
		glVertex3d(bottomDmg[0],bottomDmg[1],0);
		glVertex3d(bottomLeft[0],bottomLeft[1],0);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex3d(topDmg[0],topDmg[1],0);
		glVertex3d(topRight[0],topRight[1],0);
		glVertex3d(bottomRight[0],bottomRight[1],0);
		glVertex3d(bottomDmg[0],bottomDmg[1],0);
		glEnd();
	}

}