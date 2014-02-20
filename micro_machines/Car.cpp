#include "Car.h"
#include "HeadLight.h"
#include "Hud.h"

namespace micro_machines{

	Car::Car(std::string id,cg::Vector3d position,int keySet):cg::Entity(id),_position(position),_keySet(keySet),_angle(0),_fTime(0),_rTime(0),_dTime(0){}

	Car::~Car(){}

	double Car::randomBetween(double min,double max){
		return (rand()/(double)RAND_MAX*(max-min))+min;
	}

	void Car::init(){
		cg::tWindow win=cg::Manager::instance()->getApp()->getWindow();
		_winWidth=win.width;
		_winHeight=win.height;
		_size=cg::Vector3d(10,30,10);
		if(getId()=="Car0"){
			_initialColor=cg::Vector3f(0,1,0);
		}
		else{
			_initialColor=cg::Vector3f(0,1,1);
		}
		_color=_initialColor;
		_velocity=cg::Vector3d(0,0,0);
		_position[2]=5;
		_v0=cg::Vector3d(_position[0]-_size[0]/2,_position[1]-_size[1]/2,0);
		_v1=cg::Vector3d(_position[0]+_size[0]/2,_position[1]-_size[1]/2,0);
		_v2=cg::Vector3d(_position[0]-_size[0]/2,_position[1]+_size[1]/2,0);
		_v3=cg::Vector3d(_position[0]+_size[0]/2,_position[1]+_size[1]/2,0);
		_initialTopSpeed=cg::Properties::instance()->getDouble("TOP_SPEED");
		_topSpeed=_initialTopSpeed;
		_initialAcceleration=cg::Properties::instance()->getDouble("ACCELERATION");
		_acceleration=_initialAcceleration;
		_deceleration=cg::Properties::instance()->getDouble("DECELERATION");
		_breaking=cg::Properties::instance()->getDouble("BREAKING");
		_steering=cg::Properties::instance()->getDouble("STEERING");
		_way=UNDEF;
		_tManager=(TrackSectionManager*)cg::Registry::instance()->get("TrackSectionManager");
		_pManager=(PowerUpManager*)cg::Registry::instance()->get("PowerUpManager");
		_hud=(Hud*)cg::Registry::instance()->get("Hud");
		_damage=0;
		_nTS=0;
		_points=0;
		_afterMenu=false;
		_active=true;
	}

	void Car::postInit(){
		_currentTS=(TrackSection*)_tManager->get("Section1");
		_tSId=1;
		_currentTS->registerCar(this,_keySet);
		if(getId()=="Car0"){
			_hLight0=(HeadLight*)cg::Registry::instance()->get("HeadLight0");
			_hLight1=(HeadLight*)cg::Registry::instance()->get("HeadLight1");
		}
		else{
			_hLight0=(HeadLight*)cg::Registry::instance()->get("HeadLight2");
			_hLight1=(HeadLight*)cg::Registry::instance()->get("HeadLight3");
		}
	}

	void Car::update(unsigned long elapsed_millis){
		if(_afterMenu && _active){
			unsigned char upKey;
			unsigned char downKey;
			unsigned char leftKey;
			unsigned char rightKey;
			switch(_keySet){
				case(SET_0):
					upKey='w';
					downKey='s';
					leftKey='a';
					rightKey='d';
					break;		
				case(SET_1):
					upKey='i';
					downKey='k';
					leftKey='j';
					rightKey='l';
					break;
			}
			double dToR=0.01745329251994329547;
			double elapsed_seconds=elapsed_millis/1000.0;
			double speed=Car::speed();
			int status=_currentTS->getStatus(_v2,_v3,_v0,_v1);
			if(_pManager->isCollision(_v2,_v3,_v0,_v1)){
				_acceleration=_initialAcceleration*3;
				_bonusTime=0;
				_color=cg::Vector3f(1,1,1);
			}
			else{
				_bonusTime+=elapsed_millis;
				if(_bonusTime>=3000){
					_acceleration=_initialAcceleration;
					_color=_initialColor;
				}
			}
			if(cg::KeyBuffer::instance()->isKeyUp(upKey) && cg::KeyBuffer::instance()->isKeyUp(downKey) && _way==UNDEF && speed==0){
				_way=READY;
			}
			if(cg::KeyBuffer::instance()->isKeyDown(upKey) && (_way==READY || _way==FRONT)){
				_way=FRONT;
				_fTime=elapsed_seconds;
				speed=Car::speed()+_fTime*_acceleration;
				if(speed>_topSpeed){
					speed=_topSpeed;
				}
				setSpeed(speed);
			}
			if(cg::KeyBuffer::instance()->isKeyDown(upKey) && cg::KeyBuffer::instance()->isKeyUp(downKey) && _way==REAR){
				_rTime=elapsed_seconds;
				speed=-Car::speed()+_rTime*_breaking;
				if(speed>0){
					speed=0;
				}
				setSpeed(speed);
			}
			if(cg::KeyBuffer::instance()->isKeyDown(downKey) && (_way==READY || _way==REAR)){
				_way=REAR;
				_rTime=elapsed_seconds;
				speed=-Car::speed()-_rTime*_acceleration;
				if(speed<-_topSpeed){
					speed=-_topSpeed;
				}
				setSpeed(speed);
			}
			if(cg::KeyBuffer::instance()->isKeyDown(downKey) && cg::KeyBuffer::instance()->isKeyUp(upKey) && _way==FRONT){
				_fTime=elapsed_seconds;
				speed=Car::speed()-_fTime*_breaking;
				if(speed<0){
					speed=0;
				}
				setSpeed(speed);
			}
			if(cg::KeyBuffer::instance()->isKeyDown(leftKey)){
				_velocity=rotateZDeg(_velocity,_steering);
				_angle+=_steering;
				_v0=rotateZDegPosition(_v0,_position,_steering);
				_v1=rotateZDegPosition(_v1,_position,_steering);
				_v2=rotateZDegPosition(_v2,_position,_steering);
				_v3=rotateZDegPosition(_v3,_position,_steering);
			}
			if(cg::KeyBuffer::instance()->isKeyDown(rightKey)){
				_velocity=rotateZDeg(_velocity,-_steering);
				_angle-=_steering;
				_v0=rotateZDegPosition(_v0,_position,-_steering);
				_v1=rotateZDegPosition(_v1,_position,-_steering);
				_v2=rotateZDegPosition(_v2,_position,-_steering);
				_v3=rotateZDegPosition(_v3,_position,-_steering);
			}
			if(cg::KeyBuffer::instance()->isKeyUp(upKey) && cg::KeyBuffer::instance()->isKeyUp(downKey) && _way==FRONT){
				_dTime=elapsed_seconds;
				speed=Car::speed()-_dTime*_deceleration;
				if(speed<0){
					speed=0;
					_way=UNDEF;
				}
				setSpeed(speed);
			}
			if(cg::KeyBuffer::instance()->isKeyUp(downKey) && cg::KeyBuffer::instance()->isKeyUp(upKey) && _way==REAR){
				_dTime=elapsed_seconds;
				speed=-Car::speed()+_dTime*_deceleration;
				if(speed>0){
					speed=0;
					_way=UNDEF;
				}
				setSpeed(speed);
			}
			if(_tManager->isCollision(_v2,_v3,_v0,_v1,_tSId)){
				for(int i=0;i<3;++i){
					_velocity[i]=0;
					_way=UNDEF;
				}
				if(_damage<100 && _anotherCollision){
					_damage+=10;
				}
				if(_damage<80){
					_topSpeed=cg::Properties::instance()->getDouble("TOP_SPEED")*(100-_damage)/100;
					_initialTopSpeed=_topSpeed;
				}
				_anotherCollision=false;
				for(double i=_currentTS->xPosition()-_currentTS->xSize()/2;i<_currentTS->xPosition()+_currentTS->xSize()/2;i+=_currentTS->xSize()/4){
					if(repositionCarX(i)){
						break;
					}
				}
				if(_currentTS->getStatus(_v2,_v3,_v0,_v1)==HCOLLISION){
					for(double i=_currentTS->xPosition()-_currentTS->xSize()/2;i<_currentTS->xPosition()+_currentTS->xSize()/2;i+=_currentTS->xSize()/4){
						if(repositionCarX(i)){
							break;
						}
					}
				}
			}
			else{
				_anotherCollision=true;
			}
			if(status==VCOLLISION){
				_way=UNDEF;
				for(int i=0;i<3;++i){
					_velocity[i]=0;
				}
				for(double i=_currentTS->xPosition()-_currentTS->xSize()/2;i<_currentTS->xPosition()+_currentTS->xSize()/2;i+=_currentTS->xSize()/4){
					if(repositionCarX(i) && _currentTS->getStatus(_v2,_v3,_v0,_v1)!=HCOLLISION){
						break;
					}
				}
			}
			if(status==HCOLLISION){
				_way=UNDEF;
				for(int i=0;i<3;++i){
					_velocity[i]=0;
				}
				for(double i=_currentTS->yPosition()-_currentTS->ySize()/2;i<_currentTS->yPosition()+_currentTS->ySize()/2;i+=_currentTS->ySize()/4){
					if(repositionCarY(i) && _currentTS->getStatus(_v2,_v3,_v0,_v1)!=VCOLLISION){
						break;
					}
				}
			}
			if(status==OFF){
				double speed=Car::speed();
				if(speed>_topSpeed/2){
					speed-=_deceleration*elapsed_seconds*2;
					switch(_way){
						case(FRONT):
							setSpeed(speed);
							break;
						case(REAR):
							setSpeed(-speed);
							break;
					}
				}
			}
			if(status==NEXT){
				nextTS();
			}
			if(status==PREVIOUS){
				previousTS();
			}
			if(status==CLEAR){
				_topSpeed=_initialTopSpeed;
			}
			_position+=_velocity*elapsed_seconds;
			_v0+=_velocity*elapsed_seconds;
			_v1+=_velocity*elapsed_seconds;
			_v2+=_velocity*elapsed_seconds;
			_v3+=_velocity*elapsed_seconds;
			_hLight0->updatePosition((float)_position[0],(float)_position[1],(float)_position[2],(float)_angle);
			_hLight1->updatePosition((float)_position[0],(float)_position[1],(float)_position[2],(float)_angle);
		}
	}

	bool Car::badPosition(cg::Vector3d topLeft,cg::Vector3d topRight,cg::Vector3d bottomLeft,cg::Vector3d bottomRight){
		int nObstacles=cg::Properties::instance()->getDouble("OBSTACLES_PER_SECTION");
		std::ostringstream ss;
		ss<<"ObstacleManager"<<_tSId;
		ObstacleManager* oM=(ObstacleManager*)_tManager->get(ss.str());
		if(oM->isCollision(topLeft,topRight,bottomLeft,bottomRight)){
			return true;
		}
		return false;
	}

	bool Car::repositionCarY(double p){
		cg::Vector3d position=_position;
		if(getId()=="Car0"){
			position[0]=_currentTS->xPosition()-20;
		}
		if(getId()=="Car1"){
			position[0]=_currentTS->xPosition()+20;
		}
		position[1]=p;
		cg::Vector3d v0=cg::Vector3d(position[0]-_size[0]/2,position[1]-_size[1]/2,0);
		v0=rotateZDegPosition(v0,position,_angle);
		cg::Vector3d v1=cg::Vector3d(position[0]+_size[0]/2,position[1]-_size[1]/2,0);
		v1=rotateZDegPosition(v1,position,_angle);
		cg::Vector3d v2=cg::Vector3d(position[0]-_size[0]/2,position[1]+_size[1]/2,0);
		v2=rotateZDegPosition(v2,position,_angle);
		cg::Vector3d v3=cg::Vector3d(position[0]+_size[0]/2,position[1]+_size[1]/2,0);
		v3=rotateZDegPosition(v3,position,_angle);
		if(badPosition(v2,v3,v0,v1)){
			return false;
		}
		_v0=v0;
		_v1=v1;
		_v2=v2;
		_v3=v3;
		_position=position;
		return true;
	}

	bool Car::repositionCarX(double p){
		cg::Vector3d position=_position;
		if(getId()=="Car0"){
			position[1]=_currentTS->yPosition()-20;
		}
		if(getId()=="Car1"){
			position[1]=_currentTS->yPosition()+20;
		}
		position[0]=p;
		cg::Vector3d v0=cg::Vector3d(position[0]-_size[0]/2,position[1]-_size[1]/2,0);
		v0=rotateZDegPosition(v0,position,_angle);
		cg::Vector3d v1=cg::Vector3d(position[0]+_size[0]/2,position[1]-_size[1]/2,0);
		v1=rotateZDegPosition(v1,position,_angle);
		cg::Vector3d v2=cg::Vector3d(position[0]-_size[0]/2,position[1]+_size[1]/2,0);
		v2=rotateZDegPosition(v2,position,_angle);
		cg::Vector3d v3=cg::Vector3d(position[0]+_size[0]/2,position[1]+_size[1]/2,0);
		v3=rotateZDegPosition(v3,position,_angle);
		if(badPosition(v2,v3,v0,v1)){
			return false;
		}
		_v0=v0;
		_v1=v1;
		_v2=v2;
		_v3=v3;
		_position=position;
		return true;
	}

	cg::Vector3d Car::rotateZDegPosition(cg::Vector3d v,cg::Vector3d p,double a){
		cg::Vector3d vector;
		vector=v;
		v-=p;
		v=rotateZDeg(v,a);
		v+=p;
		return v;
	}

	void Car::setSpeed(double speed){
		double dToR=0.01745329251994329547;
		double alpha=_angle+90;
		_velocity[0]=speed*cos(alpha*dToR);
		_velocity[1]=speed*sin(alpha*dToR);
	}

	void Car::moveCar(cg::Vector3d move){
		_position+=move;
		_v0+=move;
		_v1+=move;
		_v2+=move;
		_v3+=move;
	}

	void Car::draw(){
		if(_afterMenu && _active){
			double dToR=0.01745329251994329547;
			cg::Vector3d vMin=-_size/2.0;
			cg::Vector3d vMax=_size/2.0;
			cg::Vector3d v0=cg::Vector3d(vMin[0],vMax[1],vMin[2]);
			cg::Vector3d v1=cg::Vector3d(vMin[0],vMax[1],vMax[2]);
			cg::Vector3d v2=cg::Vector3d(vMin[0],vMin[1],vMax[2]);
			cg::Vector3d v3=cg::Vector3d(vMax[0],vMin[1],vMax[2]);
			cg::Vector3d v4=cg::Vector3d(vMax[0],vMin[1],vMin[2]);
			cg::Vector3d v5=cg::Vector3d(vMax[0],vMax[1],vMin[2]);
			vMin=rotateZDeg(vMin,_angle);
			vMax=rotateZDeg(vMax,_angle);
			v0=rotateZDeg(v0,_angle);
			v1=rotateZDeg(v1,_angle);
			v2=rotateZDeg(v2,_angle);
			v3=rotateZDeg(v3,_angle);
			v4=rotateZDeg(v4,_angle);
			v5=rotateZDeg(v5,_angle);
			vMin+=_position;
			vMax+=_position;
			v0+=_position;
			v1+=_position;
			v2+=_position;
			v3+=_position;
			v4+=_position;
			v5+=_position;
			/*Surface Normals*/
			cg::Vector3d top=cg::Vector3d(0,0,1);
			cg::Vector3d bottom=cg::Vector3d(0,0,-1);
			cg::Vector3d front=cg::Vector3d(cos((_angle+90)*dToR),sin((_angle+90)*dToR),0);
			cg::Vector3d back=cg::Vector3d(cos((_angle+270)*dToR),sin((_angle+270)*dToR),0);
			cg::Vector3d left=cg::Vector3d(cos((_angle+180)*dToR),sin((_angle+180)*dToR),0);
			cg::Vector3d right=cg::Vector3d(cos(_angle*dToR),sin(_angle*dToR),0);
			/*Vertex Normals*/
			cg::Vector3d nMin=back+bottom+left;
			nMin/=sqrt(pow(nMin[0],2)+pow(nMin[1],2)+pow(nMin[2],2));
			cg::Vector3d nMax=front+top+right;
			nMax/=sqrt(pow(nMax[0],2)+pow(nMax[1],2)+pow(nMax[2],2));
			cg::Vector3d n0=front+bottom+left;
			n0/=sqrt(pow(n0[0],2)+pow(n0[1],2)+pow(n0[2],2));
			cg::Vector3d n1=front+top+left;
			n1/=sqrt(pow(n1[0],2)+pow(n1[1],2)+pow(n1[2],2));
			cg::Vector3d n2=back+top+left;
			n2/=sqrt(pow(n2[0],2)+pow(n2[1],2)+pow(n2[2],2));
			cg::Vector3d n3=back+top+right;
			n3/=sqrt(pow(n3[0],2)+pow(n3[1],2)+pow(n3[2],2));
			cg::Vector3d n4=back+bottom+right;
			n4/=sqrt(pow(n4[0],2)+pow(n4[1],2)+pow(n4[2],2));
			cg::Vector3d n5=front+bottom+right;
			n5/=sqrt(pow(n5[0],2)+pow(n5[1],2)+pow(n5[2],2));
			/*Materials*/
			cg::Vector3f specular=cg::Vector3f(1,1,1);
			float shininess=120.0f;
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,_color.get());
			glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular.get());
			glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shininess);
			glLineWidth(1.5);
			/*Aux*/
			cg::Vector3d aux;
			/*Top*/
			glBegin(GL_LINE_LOOP);
			glNormal3d(nMax[0],nMax[1],nMax[2]);
			glVertex3d(vMax[0],vMax[1],vMax[2]);
			glNormal3d(n1[0],n1[1],n1[2]);
			glVertex3d(v1[0],v1[1],v1[2]);
			glNormal3d(n2[0],n2[1],n2[2]);
			glVertex3d(v2[0],v2[1],v2[2]);
			glNormal3d(n3[0],n3[1],n3[2]);
			glVertex3d(v3[0],v3[1],v3[2]);
			glEnd();
			/*Bottom*/
			glBegin(GL_LINE_LOOP);
			glNormal3d(nMin[0],nMin[1],nMin[2]);
			glVertex3d(vMin[0],vMin[1],vMin[2]);
			glNormal3d(n4[0],n4[1],n4[2]);
			glVertex3d(v4[0],v4[1],v4[2]);
			glNormal3d(n5[0],n5[1],n5[2]);
			glVertex3d(v5[0],v5[1],v5[2]);
			glNormal3d(n0[0],n0[1],n0[2]);
			glVertex3d(v0[0],v0[1],v0[2]);
			glEnd();
			/*Front*/
			glBegin(GL_LINE_LOOP);
			glNormal3d(nMax[0],nMax[1],nMax[2]);
			glVertex3d(vMax[0],vMax[1],vMax[2]);
			glNormal3d(n1[0],n1[1],n1[2]);
			glVertex3d(v1[0],v1[1],v1[2]);
			glNormal3d(n0[0],n0[1],n0[2]);
			glVertex3d(v0[0],v0[1],v0[2]);
			glNormal3d(n5[0],n5[1],n5[2]);
			glVertex3d(v5[0],v5[1],v5[2]);
			glEnd();
			/*Back*/
			glBegin(GL_LINE_LOOP);
			glNormal3d(nMin[0],nMin[1],nMin[2]);
			glVertex3d(vMin[0],vMin[1],vMin[2]);
			glNormal3d(n2[0],n2[1],n2[2]);
			glVertex3d(v2[0],v2[1],v2[2]);
			glNormal3d(n3[0],n3[1],n3[2]);
			glVertex3d(v3[0],v3[1],v3[2]);
			glNormal3d(n4[0],n4[1],n4[2]);
			glVertex3d(v4[0],v4[1],v4[2]);
			glEnd();
			/*Left*/
			glBegin(GL_LINE_LOOP);
			glNormal3d(nMax[0],nMax[1],nMax[2]);
			glVertex3d(vMax[0],vMax[1],vMax[2]);
			glNormal3d(n3[0],n3[1],n3[2]);
			glVertex3d(v3[0],v3[1],v3[2]);
			glNormal3d(n4[0],n4[1],n4[2]);
			glVertex3d(v4[0],v4[1],v4[2]);
			glNormal3d(n5[0],n5[1],n5[2]);
			glVertex3d(v5[0],v5[1],v5[2]);
			glEnd();
			/*Right*/
			glBegin(GL_LINE_LOOP);
			glNormal3d(nMin[0],nMin[1],nMin[2]);
			glVertex3d(vMin[0],vMin[1],vMin[2]);
			glNormal3d(n0[0],n0[1],n0[2]);
			glVertex3d(v0[0],v0[1],v0[2]);
			glNormal3d(n1[0],n1[1],n1[2]);
			glVertex3d(v1[0],v1[1],v1[2]);
			glNormal3d(n2[0],n2[1],n2[2]);
			glVertex3d(v2[0],v2[1],v2[2]);
			glEnd();
		}
	}

	void Car::onReshape(int width,int height){
		_winWidth=width;
		_winHeight=height;
	}

	void Car::onKeyPressed(unsigned char key){
		if(_afterMenu && _active){
			unsigned char upKey;
			unsigned char downKey;
			switch(_keySet){
				case(SET_0):
					upKey='w';
					downKey='s';
					break;		
				case(SET_1):
					upKey='i';
					downKey='k';
					break;
			}
			if(key==upKey){
				_dTime=0;
				if(_way==UNDEF){
					_way=FRONT;
				}
			}
			if(key==downKey){
				_dTime=0;
				if(_way==UNDEF){
					_way=REAR;
				}
			}
			cg::KeyBuffer::instance()->pressKey(key);
			/*Full Screen*/
			if(key=='f'){
				glutFullScreen();
			}
			if(key=='g'){
				glutReshapeWindow(640,360);
			}
		}
	}

	void Car::onKeyReleased(unsigned char key){
		if(_afterMenu && _active){
			unsigned char upKey;
			unsigned char downKey;
			switch(_keySet){
				case(SET_0):
					upKey='w';
					downKey='s';
					break;		
				case(SET_1):
					upKey='i';
					downKey='k';
					break;
			}
			if(key==upKey){
				_fTime=0;
			}
			if(key==downKey){
				_rTime=0;
			}
			cg::KeyBuffer::instance()->releaseKey(key);
		}
	}

	void Car::onSpecialKeyPressed(int key){}

	void Car::onSpecialKeyReleased(int key){}

	void Car::setTS(int tSId){
		_currentTS->registerCar(0,_keySet);
		_tSId=tSId;
		std::ostringstream ss;
		ss<<"Section"<<_tSId;
		_currentTS=(TrackSection*)_tManager->get(ss.str());
		_currentTS->registerCar(this,_keySet);
	}

	void Car::nextTS(){
		_currentTS->registerCar(0,_keySet);
		if(_tSId==_tManager->nSections()){
			_tSId=1;
		}
		else{
			_tSId++;
		}
		_nTS++;
		std::ostringstream ss;
		ss<<"Section"<<_tSId;
		_currentTS=(TrackSection*)_tManager->get(ss.str());
		_currentTS->registerCar(this,_keySet);
		_hud->updateLapInfo(_tSId,_keySet);
	}

	void Car::previousTS(){
		_currentTS->registerCar(0,_keySet);
		if(_tSId==1){
			_tSId=_tManager->nSections();
		}
		else{
			_tSId--;
		}
		_nTS--;
		std::ostringstream ss;
		ss<<"Section"<<_tSId;
		_currentTS=(TrackSection*)_tManager->get(ss.str());
		_currentTS->registerCar(this,_keySet);
	}

	void Car::resetNTS(){
		_nTS=0;
	}

	int Car::isCollision(cg::Vector3d topLeft,cg::Vector3d topRight,cg::Vector3d bottomLeft,cg::Vector3d bottomRight){
		cg::Vector3d vMin=_position-_size/2.0;
		cg::Vector3d vMax=_position+_size/2.0;
		bool collision=false;
		cg::Vector3d collisionPoint;
		bool topPoint;
		/*Deteccao com Modelo de Equacoes da recta*/
		double b0;
		double b1;
		double b2;
		double b3;
		double m3;
		double m1;
		if(_v3[0]-_v1[0]!=0){
			m3=(_v3[1]-_v1[1])/(_v3[0]-_v1[0]);
			m1=(_v2[1]-_v0[1])/(_v2[0]-_v0[0]);
			b3=_v3[1]-m3*_v3[0];
			b1=_v2[1]-m1*_v2[0];
		}
		else{
			m3=DBL_MAX;
			m1=DBL_MAX;
			b3=DBL_MAX;
			b1=DBL_MAX;
		}
		double m2;
		double m0;
		if(_v3[0]-_v2[0]!=0){
			m2=(_v3[1]-_v2[1])/(_v3[0]-_v2[0]);
			m0=(_v1[1]-_v0[1])/(_v1[0]-_v0[0]);
			b2=_v3[1]-m2*_v3[0];
			b0=_v1[1]-m0*_v1[0];
		}
		else{
			m2=DBL_MAX;
			m0=DBL_MAX;
			b2=DBL_MAX;
			b0=DBL_MAX;
		}
		double dToR=0.01745329251994329547;
		double alpha=(_angle+90)*dToR;
		double sinA=sin(alpha);
		double cosA=cos(alpha);
		/*Carro na vertical orientado para cima*/
		if(sinA==1){
			if(topLeft[0]<_v3[0] && topLeft[0]>_v0[0] && topLeft[1]<_v3[1] && topLeft[1]>_v0[1]){
				collision=true;
				collisionPoint=topLeft;
				topPoint=true;
			}
			if(topRight[0]<_v3[0] && topRight[0]>_v0[0] && topRight[1]<_v3[1] && topRight[1]>_v0[1]){
				collision=true;
				collisionPoint=topRight;
				topPoint=true;
			}
			if(bottomLeft[0]<_v3[0] && bottomLeft[0]>_v0[0] && bottomLeft[1]<_v3[1] && bottomLeft[1]>_v0[1]){
				collision=true;
				collisionPoint=bottomLeft;
				topPoint=false;
			}
			if(bottomRight[0]<_v3[0] && bottomRight[0]>_v0[0] && bottomRight[1]<_v3[1] && bottomRight[1]>_v0[1]){
				collision=true;
				collisionPoint=bottomRight;
				topPoint=false;
			}
		}
		/*Carro na vertical orientado para baixo*/
		if(sinA==-1){
			if(topLeft[0]<_v0[0] && topLeft[0]>_v3[0] && topLeft[1]<_v0[1] && topLeft[1]>_v3[1]){
				collision=true;
				collisionPoint=topLeft;
				topPoint=true;
			}
			if(topRight[0]<_v0[0] && topRight[0]>_v3[0] && topRight[1]<_v0[1] && topRight[1]>_v3[1]){
				collision=true;
				collisionPoint=topRight;
				topPoint=true;
			}
			if(bottomLeft[0]<_v0[0] && bottomLeft[0]>_v3[0] && bottomLeft[1]<_v0[1] && bottomLeft[1]>_v3[1]){
				collision=true;
				collisionPoint=bottomLeft;
				topPoint=false;
			}
			if(bottomRight[0]<_v0[0] && bottomRight[0]>_v3[0] && bottomRight[1]<_v0[1] && bottomRight[1]>_v3[1]){
				collision=true;
				collisionPoint=bottomRight;
				topPoint=false;
			}
		}
		/*Carro na horizontal orientado para a direita*/
		if(cosA==1){
			if(topLeft[0]<_v2[0] && topLeft[0]>_v1[0] && topLeft[1]<_v2[1] && topLeft[1]>_v1[1]){
				collision=true;
				collisionPoint=topLeft;
				topPoint=true;
			}
			if(topRight[0]<_v2[0] && topRight[0]>_v1[0] && topRight[1]<_v2[1] && topRight[1]>_v1[1]){
				collision=true;
				collisionPoint=topRight;
				topPoint=true;
			}
			if(bottomLeft[0]<_v2[0] && bottomLeft[0]>_v1[0] && bottomLeft[1]<_v2[1] && bottomLeft[1]>_v1[1]){
				collision=true;
				collisionPoint=bottomLeft;
				topPoint=false;
			}
			if(bottomRight[0]<_v2[0] && bottomRight[0]>_v1[0] && bottomRight[1]<_v2[1] && bottomRight[1]>_v1[1]){
				collision=true;
				collisionPoint=bottomRight;
				topPoint=false;
			}
		}
		/*Carro na horizontal orientado para a esquerda*/
		if(cosA==-1){
			if(topLeft[0]<_v1[0] && topLeft[0]>_v2[0] && topLeft[1]<_v1[1] && topLeft[1]>_v2[1]){
				collision=true;
				collisionPoint=topLeft;
				topPoint=true;
			}
			if(topRight[0]<_v1[0] && topRight[0]>_v2[0] && topRight[1]<_v1[1] && topRight[1]>_v2[1]){
				collision=true;
				collisionPoint=topRight;
				topPoint=true;
			}
			if(bottomLeft[0]<_v1[0] && bottomLeft[0]>_v2[0] && bottomLeft[1]<_v1[1] && bottomLeft[1]>_v2[1]){
				collision=true;
				collisionPoint=bottomLeft;
				topPoint=false;
			}
			if(bottomRight[0]<_v1[0] && bottomRight[0]>_v2[0] && bottomRight[1]<_v1[1] && bottomRight[1]>_v2[1]){
				collision=true;
				collisionPoint=bottomRight;
				topPoint=false;
			}
		}
		/*Carro na diagonal orientado para cima/direita*/
		if(cosA>0 && sinA>0){
			if((topLeft[1]-m3*topLeft[0]-b3)>0 && (topLeft[1]-m1*topLeft[0]-b1)<0 && (topLeft[1]-m0*topLeft[0]-b0)>0 && (topLeft[1]-m2*topLeft[0]-b2)<0){
				collision=true;
				collisionPoint=topLeft;
				topPoint=true;
			}
			if((topRight[1]-m3*topRight[0]-b3)>0 && (topRight[1]-m1*topRight[0]-b1)<0 && (topRight[1]-m0*topRight[0]-b0)>0 && (topRight[1]-m2*topRight[0]-b2)<0){
				collision=true;
				collisionPoint=topRight;
				topPoint=true;
			}
			if((bottomLeft[1]-m3*bottomLeft[0]-b3)>0 && (bottomLeft[1]-m1*bottomLeft[0]-b1)<0 && (bottomLeft[1]-m0*bottomLeft[0]-b0)>0 && (bottomLeft[1]-m2*bottomLeft[0]-b2)<0){
				collision=true;
				collisionPoint=bottomLeft;
				topPoint=false;
			}
			if((bottomRight[1]-m3*bottomRight[0]-b3)>0 && (bottomRight[1]-m1*bottomRight[0]-b1)<0 && (bottomRight[1]-m0*bottomRight[0]-b0)>0 && (bottomRight[1]-m2*bottomRight[0]-b2)<0){
				collision=true;
				collisionPoint=bottomRight;
				topPoint=false;
			}
		}
		/*Carro na diagonal orientado para cima/esquerda*/
		if(cosA<0 && sinA>0){
			if((topLeft[1]-m3*topLeft[0]-b3)<0 && (topLeft[1]-m1*topLeft[0]-b1)>0 && (topLeft[1]-m0*topLeft[0]-b0)>0 && (topLeft[1]-m2*topLeft[0]-b2)<0){
				collision=true;
				collisionPoint=topLeft;
				topPoint=true;
			}
			if((topRight[1]-m3*topRight[0]-b3)<0 && (topRight[1]-m1*topRight[0]-b1)>0 && (topRight[1]-m0*topRight[0]-b0)>0 && (topRight[1]-m2*topRight[0]-b2)<0){
				collision=true;
				collisionPoint=topRight;
				topPoint=true;
			}
			if((bottomLeft[1]-m3*bottomLeft[0]-b3)<0 && (bottomLeft[1]-m1*bottomLeft[0]-b1)>0 && (bottomLeft[1]-m0*bottomLeft[0]-b0)>0 && (bottomLeft[1]-m2*bottomLeft[0]-b2)<0){
				collision=true;
				collisionPoint=bottomLeft;
				topPoint=false;
			}
			if((bottomRight[1]-m3*bottomRight[0]-b3)<0 && (bottomRight[1]-m1*bottomRight[0]-b1)>0 && (bottomRight[1]-m0*bottomRight[0]-b0)>0 && (bottomRight[1]-m2*bottomRight[0]-b2)<0){
				collision=true;
				collisionPoint=bottomRight;
				topPoint=false;
			}
		}
		/*Carro na diagonal orientado para baixo/esquerda*/
		if(cosA<0 && sinA<0){
			if((topLeft[1]-m3*topLeft[0]-b3)<0 && (topLeft[1]-m1*topLeft[0]-b1)>0 && (topLeft[1]-m0*topLeft[0]-b0)<0 && (topLeft[1]-m2*topLeft[0]-b2)>0){
				collision=true;
				collisionPoint=topLeft;
				topPoint=true;
			}
			if((topRight[1]-m3*topRight[0]-b3)<0 && (topRight[1]-m1*topRight[0]-b1)>0 && (topRight[1]-m0*topRight[0]-b0)<0 && (topRight[1]-m2*topRight[0]-b2)>0){
				collision=true;
				collisionPoint=topRight;
				topPoint=true;
			}
			if((bottomLeft[1]-m3*bottomLeft[0]-b3)<0 && (bottomLeft[1]-m1*bottomLeft[0]-b1)>0 && (bottomLeft[1]-m0*bottomLeft[0]-b0)<0 && (bottomLeft[1]-m2*bottomLeft[0]-b2)>0){
				collision=true;
				collisionPoint=bottomLeft;
				topPoint=false;
			}
			if((bottomRight[1]-m3*bottomRight[0]-b3)<0 && (bottomRight[1]-m1*bottomRight[0]-b1)>0 && (bottomRight[1]-m0*bottomRight[0]-b0)<0 && (bottomRight[1]-m2*bottomRight[0]-b2)>0){
				collision=true;
				collisionPoint=bottomRight;
				topPoint=false;
			}
		}
		/*Carro na diagonal orientado para baixo/direita*/
		if(cosA>0 && sinA<0){
			if((topLeft[1]-m3*topLeft[0]-b3)>0 && (topLeft[1]-m1*topLeft[0]-b1)<0 && (topLeft[1]-m0*topLeft[0]-b0)<0 && (topLeft[1]-m2*topLeft[0]-b2)>0){
				collision=true;
				collisionPoint=topLeft;
				topPoint=true;
			}
			if((topRight[1]-m3*topRight[0]-b3)>0 && (topRight[1]-m1*topRight[0]-b1)<0 && (topRight[1]-m0*topRight[0]-b0)<0 && (topRight[1]-m2*topRight[0]-b2)>0){
				collision=true;
				collisionPoint=topRight;
				topPoint=true;
			}
			if((bottomLeft[1]-m3*bottomLeft[0]-b3)>0 && (bottomLeft[1]-m1*bottomLeft[0]-b1)<0 && (bottomLeft[1]-m0*bottomLeft[0]-b0)<0 && (bottomLeft[1]-m2*bottomLeft[0]-b2)>0){
				collision=true;
				collisionPoint=bottomLeft;
				topPoint=false;
			}
			if((bottomRight[1]-m3*bottomRight[0]-b3)>0 && (bottomRight[1]-m1*bottomRight[0]-b1)<0 && (bottomRight[1]-m0*bottomRight[0]-b0)<0 && (bottomRight[1]-m2*bottomRight[0]-b2)>0){
				collision=true;
				collisionPoint=bottomRight;
				topPoint=false;
			}
		}
		/*Deteccao simples*/
		/*if(topLeft[0]<vMax[0] && topLeft[0]>vMin[0] && topLeft[1]<vMax[1] && topLeft[1]>vMin[1]){
			collision=true;
			collisionPoint=topLeft;
			topPoint=true;
		}
		if(topRight[0]<vMax[0] && topRight[0]>vMin[0] && topRight[1]<vMax[1] && topRight[1]>vMin[1]){
			collision=true;
			collisionPoint=topRight;
			topPoint=true;
		}
		if(bottomLeft[0]<vMax[0] && bottomLeft[0]>vMin[0] && bottomLeft[1]<vMax[1] && bottomLeft[1]>vMin[1]){
			collision=true;
			collisionPoint=bottomLeft;
			topPoint=false;
		}
		if(bottomRight[0]<vMax[0] && bottomRight[0]>vMin[0] && bottomRight[1]<vMax[1] && bottomRight[1]>vMin[1]){
			collision=true;
			collisionPoint=bottomRight;
			topPoint=false;
		}*/
		if(collision){
			/*double top=abs(collisionPoint[1]-vMax[1]);
			double bottom=abs(collisionPoint[1]-vMin[1]);
			double left=abs(collisionPoint[0]-vMin[0]);
			double right=abs(collisionPoint[0]-vMax[0]);*/
			double top=sqrt(pow(collisionPoint[0]-_v3[0],2)+pow(collisionPoint[1]-_v3[1],2));
			double bottom=sqrt(pow(collisionPoint[0]-_v1[0],2)+pow(collisionPoint[1]-_v1[1],2));
			//std::cerr << "top: " << top << " bottom : " << bottom << std::endl;
			/*if(top<bottom && top<left && top<right){
				if(topPoint){
					return TOP_COLLISION_TOP;
				}
				else{
					return TOP_COLLISION_BOTTOM;
				}
			}
			if(bottom<top && bottom<left && bottom<right){
				if(topPoint){
					return BOTTOM_COLLISION_TOP;
				}
				else{
					return BOTTOM_COLLISION_BOTTOM;
				}
			}
			if(left<top && left<bottom && left<right){
				if(topPoint){
					return LEFT_COLLISION_TOP;
				}
				else{
					return LEFT_COLLISION_BOTTOM;
				}
			}
			if(right<top && right<bottom && right<left){
				if(topPoint){
					return RIGHT_COLLISION_TOP;
				}
				else{
					return RIGHT_COLLISION_BOTTOM;
				}
			}*/
			/*Simpler version*/
			if(top<bottom){
				//std::cerr << "top<bottom" <<std::endl;
				if(topPoint){
					return TOP_COLLISION_TOP;
				}
				else{
					return TOP_COLLISION_BOTTOM;
				}
			}
			else{
				//std::cerr << "bottom<=top" <<std::endl;
				if(topPoint){
					return BOTTOM_COLLISION_TOP;
				}
				else{
					return BOTTOM_COLLISION_BOTTOM;
				}
			}
		}
		return NO_COLLISION;
	}

	int Car::detectCollision(Car* car){
		return car->isCollision(_v2,_v3,_v0,_v1);
	}

	void Car::switchWay(int way){
		if(way==UNDEF){
			if(_way==FRONT){
				_way=REAR;
				return;
			}
			if(_way==REAR){
				_way=FRONT;
				return;
			}
		}
		_way=way;
	}

	void Car::collision(){
		_collision=true;
	}

	void Car::reposition(Car* car){
		for(int i=0;i<3;++i){
			_velocity[i]=0;
		}
		_way=UNDEF;
		for(double i=_currentTS->yPosition()-_currentTS->ySize()/2;i<_currentTS->yPosition()+_currentTS->ySize()/2;i+=_currentTS->ySize()/4){
			if(repositionCarY(i) && _currentTS->getStatus(_v2,_v3,_v0,_v1)!=VCOLLISION && detectCollision(car)==NO_COLLISION){
				return;
			}
		}
	}

	void Car::incrPoints(){
		++_points;
	}

	void Car::afterMenu(){
		_afterMenu=true;
	}

	void Car::disable(){
		_active=false;
	}

}