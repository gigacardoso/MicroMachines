#include "Car.h"
#include "TrackSection.h"

namespace micro_machines{

	TrackSection::TrackSection(std::string id,int entry,int exit,int x,int y):cg::Entity(id),_entry(entry),_exit(exit),_position(cg::Vector2d(x,y)){}

	TrackSection::~TrackSection(){}

	double TrackSection::randomBetween(double min,double max){
		return(rand()/(double)RAND_MAX*(max-min))+min;
	}

	void TrackSection::init(){
		cg::tWindow win=cg::Manager::instance()->getApp()->getWindow();
		_winWidth=win.width;
		_winHeight=win.height;
		_size=cg::Vector2d(cg::Properties::instance()->getDouble("TRACKSECTION_WIDTH"),cg::Properties::instance()->getDouble("TRACKSECTION_HEIGHT"));
		_color=cg::Vector3f(0.5294117647058824,0.8588235294117647,0.9607843137254902);
		_trackWidth=cg::Properties::instance()->getDouble("TRACK_WIDTH");
		_car0=0;
		_car1=0;
	}

	void TrackSection::update(unsigned long elapsed_millis){}

	void TrackSection::draw(){
		double tWidth=_trackWidth;
		cg::Vector2d v0;
		cg::Vector2d v1;
		cg::Vector2d v2;
		cg::Vector2d v3;
		cg::Vector2d vA0;
		cg::Vector2d vA1;
		cg::Vector2d vA2;		
		cg::Vector2d vA3;
		switch(_entry){
			case(BOTTOM):
				v0=cg::Vector2d(_position[0]-tWidth/2.0,_position[1]-_size[1]/2.0);
				vA0=_position-_size/2.0;
				v1=cg::Vector2d(_position[0]+tWidth/2.0,_position[1]-_size[1]/2.0);
				vA1=cg::Vector2d(_position[0]+_size[0]/2.0,_position[1]-_size[1]/2.0);
				break;
			case(TOP):
				v0=cg::Vector2d(_position[0]+tWidth/2.0,_position[1]+_size[1]/2.0);
				vA0=_position+_size/2.0;
				v1=cg::Vector2d(_position[0]-tWidth/2.0,_position[1]+_size[1]/2.0);
				vA1=cg::Vector2d(_position[0]-_size[0]/2.0,_position[1]+_size[1]/2.0);
				break;
			case(LEFT):
				v0=cg::Vector2d(_position[0]-_size[0]/2.0,_position[1]-tWidth/2.0);
				vA0=_position-_size/2.0;
				v1=cg::Vector2d(_position[0]-_size[0]/2.0,_position[1]+tWidth/2.0);
				vA1=cg::Vector2d(_position[0]-_size[0]/2.0,_position[1]+_size[1]/2.0);
				break;
			case(RIGHT):
				v0=cg::Vector2d(_position[0]+_size[0]/2.0,_position[1]+tWidth/2.0);
				vA0=_position+_size/2.0;
				v1=cg::Vector2d(_position[0]+_size[0]/2.0,_position[1]-tWidth/2.0);
				vA1=cg::Vector2d(_position[0]+_size[0]/2.0,_position[1]-_size[1]/2.0);
				break;
		}
		switch(_exit){
			case(BOTTOM):
				v2=cg::Vector2d(_position[0]-tWidth/2.0,_position[1]-_size[1]/2.0);
				vA2=_position-_size/2.0;
				v3=cg::Vector2d(_position[0]+tWidth/2.0,_position[1]-_size[1]/2.0);
				vA3=cg::Vector2d(_position[0]+_size[0]/2.0,_position[1]-_size[1]/2.0);
				break;
			case(TOP):
				v2=cg::Vector2d(_position[0]+tWidth/2.0,_position[1]+_size[1]/2.0);
				vA2=_position+_size/2.0;
				v3=cg::Vector2d(_position[0]-tWidth/2.0,_position[1]+_size[1]/2.0);
				vA3=cg::Vector2d(_position[0]-_size[0]/2.0,_position[1]+_size[1]/2.0);
				break;
			case(LEFT):
				v2=cg::Vector2d(_position[0]-_size[0]/2.0,_position[1]-tWidth/2.0);
				vA2=_position-_size/2.0;
				v3=cg::Vector2d(_position[0]-_size[0]/2.0,_position[1]+tWidth/2.0);
				vA3=cg::Vector2d(_position[0]-_size[0]/2.0,_position[1]+_size[1]/2.0);
				break;
			case(RIGHT):
				v2=cg::Vector2d(_position[0]+_size[0]/2.0,_position[1]+tWidth/2.0);
				vA2=_position+_size/2.0;
				v3=cg::Vector2d(_position[0]+_size[0]/2.0,_position[1]-tWidth/2.0);
				vA3=cg::Vector2d(_position[0]+_size[0]/2.0,_position[1]-_size[1]/2.0);
				break;
		}
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,_color.get());
		glLineWidth(3);
		cg::Vector2d aux;
		double innerRadius=_size[0]/2-_trackWidth/2;
		double outerRadius=_size[0]/2+_trackWidth/2;
		if(vA0==vA2){
			if(vA0==_position-_size/2.0){
				switch(_entry){
					aux=_position+_size/2.0;
					case(LEFT):
						glBegin(GL_LINE_STRIP);
						glNormal3d(0,0,1);
						for(double alpha=0;alpha<M_PI_2;alpha+=0.05){
							glVertex3d(v2[0]+(cos(alpha)-1)*innerRadius,v2[1]+sin(alpha)*innerRadius,0);
						}
						glVertex3d(v0[0],v0[1],0);
						glEnd();
						glBegin(GL_LINE_STRIP);
						glNormal3d(0,0,1);
						for(double alpha=0;alpha<M_PI_2;alpha+=0.05){
							glVertex3d(v3[0]+(cos(alpha)-1)*outerRadius,v3[1]+sin(alpha)*outerRadius,0);
						}
						glVertex3d(v1[0],v1[1],0);
						glEnd();
						break;
					case(BOTTOM):
						glBegin(GL_LINE_STRIP);
						glNormal3d(0,0,1);
						for(double alpha=0;alpha<M_PI_2;alpha+=0.05){
							glVertex3d(v0[0]+(cos(alpha)-1)*innerRadius,v0[1]+sin(alpha)*innerRadius,0);
						}
						glVertex3d(v2[0],v2[1],0);
						glEnd();
						glBegin(GL_LINE_STRIP);
						glNormal3d(0,0,1);
						for(double alpha=0;alpha<M_PI_2;alpha+=0.05){
							glVertex3d(v1[0]+(cos(alpha)-1)*outerRadius,v1[1]+sin(alpha)*outerRadius,0);
						}
						glVertex3d(v3[0],v3[1],0);
						glEnd();
						break;
				}
			}
			else{
				aux=_position-_size/2.0;
				switch(_entry){
					case(RIGHT):
						glBegin(GL_LINE_STRIP);
						glNormal3d(0,0,1);
						for(double alpha=0;alpha<M_PI_2;alpha+=0.05){
							glVertex3d(v2[0]-(cos(alpha)-1)*innerRadius,v2[1]-sin(alpha)*innerRadius,0);
						}
						glVertex3d(v0[0],v0[1],0);
						glEnd();
						glBegin(GL_LINE_STRIP);
						glNormal3d(0,0,1);
						for(double alpha=0;alpha<M_PI_2;alpha+=0.05){
							glVertex3d(v3[0]-(cos(alpha)-1)*outerRadius,v3[1]-sin(alpha)*outerRadius,0);
						}
						glVertex3d(v1[0],v1[1],0);
						glEnd();
						break;
					case(TOP):
						glBegin(GL_LINE_STRIP);
						glNormal3d(0,0,1);
						for(double alpha=0;alpha<M_PI_2;alpha+=0.05){
							glVertex3d(v0[0]-(cos(alpha)-1)*innerRadius,v0[1]-sin(alpha)*innerRadius,0);
						}
						glVertex3d(v2[0],v2[1],0);
						glEnd();
						glBegin(GL_LINE_STRIP);
						glNormal3d(0,0,1);
						for(double alpha=0;alpha<M_PI_2;alpha+=0.05){
							glVertex3d(v1[0]-(cos(alpha)-1)*outerRadius,v1[1]-sin(alpha)*outerRadius,0);
						}
						glVertex3d(v3[0],v3[1],0);
						glEnd();
						break;
				}
			}
		}
		else{
			if(vA1==vA3){
				if(vA1==cg::Vector2d(_position[0]+_size[0]/2.0,_position[1]-_size[1]/2.0)){
					aux=cg::Vector2d(_position[0]-_size[0]/2.0,_position[1]+_size[1]/2.0);
					switch(_entry){
						case(RIGHT):
							glBegin(GL_LINE_STRIP);
							glNormal3d(0,0,1);
							for(double alpha=0;alpha<M_PI_2;alpha+=0.05){
								glVertex3d(v3[0]-(cos(alpha)-1)*innerRadius,v3[1]+sin(alpha)*innerRadius,0);
							}
							glVertex3d(v1[0],v1[1],0);
							glEnd();
							glBegin(GL_LINE_STRIP);
							glNormal3d(0,0,1);
							for(double alpha=0;alpha<M_PI_2;alpha+=0.05){
								glVertex3d(v2[0]-(cos(alpha)-1)*outerRadius,v2[1]+sin(alpha)*outerRadius,0);
							}
							glVertex3d(v0[0],v0[1],0);
							glEnd();
							break;
						case(BOTTOM):
							glBegin(GL_LINE_STRIP);
							glNormal3d(0,0,1);
							for(double alpha=0;alpha<M_PI_2;alpha+=0.05){
								glVertex3d(v1[0]-(cos(alpha)-1)*innerRadius,v1[1]+sin(alpha)*innerRadius,0);
							}
							glVertex3d(v3[0],v3[1],0);
							glEnd();
							glBegin(GL_LINE_STRIP);
							glNormal3d(0,0,1);
							for(double alpha=0;alpha<M_PI_2;alpha+=0.05){
								glVertex3d(v0[0]-(cos(alpha)-1)*outerRadius,v0[1]+sin(alpha)*outerRadius,0);
							}
							glVertex3d(v2[0],v2[1],0);
							glEnd();
							break;
					}
				}
				else{
					aux=cg::Vector2d(_position[0]+_size[0]/2.0,_position[1]-_size[1]/2.0);
					switch(_entry){
						case(LEFT):
							glBegin(GL_LINE_STRIP);
							glNormal3d(0,0,1);
							for(double alpha=0;alpha<M_PI_2;alpha+=0.05){
								glVertex3d(v3[0]+(cos(alpha)-1)*innerRadius,v3[1]-sin(alpha)*innerRadius,0);
							}
							glVertex3d(v1[0],v1[1],0);
							glEnd();
							glBegin(GL_LINE_STRIP);
							glNormal3d(0,0,1);
							for(double alpha=0;alpha<M_PI_2;alpha+=0.05){
								glVertex3d(v2[0]+(cos(alpha)-1)*outerRadius,v2[1]-sin(alpha)*outerRadius,0);
							}
							glVertex3d(v0[0],v0[1],0);
							glEnd();
							break;
						case(TOP):
							glBegin(GL_LINE_STRIP);
							glNormal3d(0,0,1);
							for(double alpha=0;alpha<M_PI_2;alpha+=0.05){
								glVertex3d(v1[0]+(cos(alpha)-1)*innerRadius,v1[1]-sin(alpha)*innerRadius,0);
							}
							glVertex3d(v3[0],v3[1],0);
							glEnd();
							glBegin(GL_LINE_STRIP);
							glNormal3d(0,0,1);
							for(double alpha=0;alpha<M_PI_2;alpha+=0.05){
								glVertex3d(v0[0]+(cos(alpha)-1)*outerRadius,v0[1]-sin(alpha)*outerRadius,0);
							}
							glVertex3d(v2[0],v2[1],0);
							glEnd();
							break;
					}
				}
			}
			else{
				glBegin(GL_LINE_LOOP);
				glNormal3d(0,0,1);
				glVertex3d(v0[0],v0[1],0);
				glVertex3d(v3[0],v3[1],0);
				//glVertex3d(vA3[0],vA3[1],0);
				//glVertex3d(vA0[0],vA0[1],0);
				glEnd();
				glBegin(GL_LINE_LOOP);
				glNormal3d(0,0,1);
				glVertex3d(v1[0],v1[1],0);
				glVertex3d(v2[0],v2[1],0);
				//glVertex3d(vA2[0],vA2[1],0);
				//glVertex3d(vA1[0],vA1[1],0);
				glEnd();
			}
		}
	}

	void TrackSection::registerCar(Car* car,int carId){
		if(carId==0){
			_car0=car;
		}
		if(carId==1){
			_car1=car;
		}
	}

	int TrackSection::getStatus(cg::Vector3d topLeft,cg::Vector3d topRight,cg::Vector3d bottomLeft,cg::Vector3d bottomRight){
		/*Testes de colisões com os limites da secção*/
		if(_entry!=TOP && _exit!=TOP){
			if(topLeft[1]>_position[1]+_size[1]/2 || topRight[1]>_position[1]+_size[1]/2 || bottomLeft[1]>_position[1]+_size[1]/2 || bottomRight[1]>_position[1]+_size[1]/2){
				return VCOLLISION;
			}
		}
		if(_entry!=BOTTOM && _exit!=BOTTOM){
			if(topLeft[1]<_position[1]-_size[1]/2 || topRight[1]<_position[1]-_size[1]/2 || bottomLeft[1]<_position[1]-_size[1]/2 || bottomRight[1]<_position[1]-_size[1]/2){
				return VCOLLISION;
			}
		}
		if(_entry!=RIGHT && _exit!=RIGHT){
			if(topLeft[0]>_position[0]+_size[0]/2 || topRight[0]>_position[0]+_size[0]/2 || bottomLeft[0]>_position[0]+_size[0]/2 || bottomRight[0]>_position[0]+_size[0]/2){
				return HCOLLISION;
			}
		}
		if(_entry!=LEFT && _exit!=LEFT){
			if(topLeft[0]<_position[0]-_size[0]/2 || topRight[0]<_position[0]-_size[0]/2 || bottomLeft[0]<_position[0]-_size[0]/2 || bottomRight[0]<_position[0]-_size[0]/2){
				return HCOLLISION;
			}
		}
		/*Testes de saída da secção actual*/
		switch(_entry){
			case(TOP):
				if(topLeft[1]>_position[1]+_size[1]/2 && topRight[1]>_position[1]+_size[1]/2 && bottomLeft[1]>_position[1]+_size[1]/2 && bottomRight[1]>_position[1]+_size[1]/2){
					return PREVIOUS;
				}
				break;
			case(BOTTOM):
				if(topLeft[1]<_position[1]-_size[1]/2 && topRight[1]<_position[1]-_size[1]/2 && bottomLeft[1]<_position[1]-_size[1]/2 && bottomRight[1]<_position[1]-_size[1]/2){
					return PREVIOUS;
				}
				break;
			case(RIGHT):
				if(topLeft[0]>_position[0]+_size[0]/2 && topRight[0]>_position[0]+_size[0]/2 && bottomLeft[0]>_position[0]+_size[0]/2 && bottomRight[0]>_position[0]+_size[0]/2){
					return PREVIOUS;
				}
				break;
			case(LEFT):
				if(topLeft[0]<_position[0]-_size[0]/2 && topRight[0]<_position[0]-_size[0]/2 && bottomLeft[0]<_position[0]-_size[0]/2 && bottomRight[0]<_position[0]-_size[0]/2){
					return PREVIOUS;
				}
				break;
		}
		switch(_exit){
			case(TOP):
				if(topLeft[1]>_position[1]+_size[1]/2 && topRight[1]>_position[1]+_size[1]/2 && bottomLeft[1]>_position[1]+_size[1]/2 && bottomRight[1]>_position[1]+_size[1]/2){
					return NEXT;
				}
				break;
			case(BOTTOM):
				if(topLeft[1]<_position[1]-_size[1]/2 && topRight[1]<_position[1]-_size[1]/2 && bottomLeft[1]<_position[1]-_size[1]/2 && bottomRight[1]<_position[1]-_size[1]/2){
					return NEXT;
				}
				break;
			case(RIGHT):
				if(topLeft[0]>_position[0]+_size[0]/2 && topRight[0]>_position[0]+_size[0]/2 && bottomLeft[0]>_position[0]+_size[0]/2 && bottomRight[0]>_position[0]+_size[0]/2){
					return NEXT;
				}
				break;
			case(LEFT):
				if(topLeft[0]<_position[0]-_size[0]/2 && topRight[0]<_position[0]-_size[0]/2 && bottomLeft[0]<_position[0]-_size[0]/2 && bottomRight[0]<_position[0]-_size[0]/2){
					return NEXT;
				}
				break;
		}
		/*Testes de movimento fora da pista*/
		if((_entry==TOP && _exit==BOTTOM) || (_entry==BOTTOM && _exit==TOP)){
			if(topLeft[0]<_position[0]-_trackWidth/2 || topRight[0]<_position[0]-_trackWidth/2 || bottomLeft[0]<_position[0]-_trackWidth/2 || bottomRight[0]<_position[0]-_trackWidth/2){
				return OFF;
			}
			if(topLeft[0]>_position[0]+_trackWidth/2 || topRight[0]>_position[0]+_trackWidth/2 || bottomLeft[0]>_position[0]+_trackWidth/2 || bottomRight[0]>_position[0]+_trackWidth/2){
				return OFF;
			}
		}
		if((_entry==LEFT && _exit==RIGHT) || (_entry==RIGHT && _exit==LEFT)){
			if(topLeft[1]<_position[1]-_trackWidth/2 || topRight[1]<_position[1]-_trackWidth/2 || bottomLeft[1]<_position[1]-_trackWidth/2 || bottomRight[1]<_position[1]-_trackWidth/2){
				return OFF;
			}
			if(topLeft[1]>_position[1]+_trackWidth/2 || topRight[1]>_position[1]+_trackWidth/2 || bottomLeft[1]>_position[1]+_trackWidth/2 || bottomRight[1]>_position[1]+_trackWidth/2){
				return OFF;
			}
		}
		double innerRadius=_size[0]/2-_trackWidth/2;
		double outerRadius=_size[0]/2+_trackWidth/2;
		if((_entry==TOP && _exit==LEFT) || (_entry==LEFT && _exit==TOP)){
			cg::Vector2d top0=cg::Vector2d(_position[0]-_trackWidth/2.0,_position[1]+_size[1]/2.0);
			cg::Vector2d top1=cg::Vector2d(_position[0]+_trackWidth/2.0,_position[1]+_size[1]/2.0);
			cg::Vector2d temp;
			for(double alpha=0;alpha<M_PI_2;alpha+=0.2){
				temp[0]=top0[0]+(cos(alpha)-1)*innerRadius;
				temp[1]=top0[1]-sin(alpha)*innerRadius;
				if((topLeft[0]<temp[0] && topLeft[1]>temp[1]) || (topRight[0]<temp[0] && topRight[1]>temp[1]) || (bottomLeft[0]<temp[0] && bottomLeft[1]>temp[1]) || (bottomRight[0]<temp[0] && bottomRight[1]>temp[1])){
					return OFF;
				}
				temp[0]=top1[0]+(cos(alpha)-1)*outerRadius;
				temp[1]=top1[1]-sin(alpha)*outerRadius;
				if((topLeft[0]>temp[0] && topLeft[1]<temp[1]) || (topRight[0]>temp[0] && topRight[1]<temp[1]) || (bottomLeft[0]>temp[0] && bottomLeft[1]<temp[1]) || (bottomRight[0]>temp[0] && bottomRight[1]<temp[1])){
					return OFF;
				}
			}
		}
		if((_entry==TOP && _exit==RIGHT) || (_entry==RIGHT && _exit==TOP)){
			cg::Vector2d top0=cg::Vector2d(_position[0]-_trackWidth/2.0,_position[1]+_size[1]/2.0);
			cg::Vector2d top1=cg::Vector2d(_position[0]+_trackWidth/2.0,_position[1]+_size[1]/2.0);
			cg::Vector2d temp;
			for(double alpha=0;alpha<M_PI_2;alpha+=0.2){
				temp[0]=top1[0]-(cos(alpha)-1)*innerRadius;
				temp[1]=top1[1]-sin(alpha)*innerRadius;
				if((topLeft[0]>temp[0] && topLeft[1]>temp[1]) || (topRight[0]>temp[0] && topRight[1]>temp[1]) || (bottomLeft[0]>temp[0] && bottomLeft[1]>temp[1]) || (bottomRight[0]>temp[0] && bottomRight[1]>temp[1])){
					return OFF;
				}
				temp[0]=top0[0]-(cos(alpha)-1)*outerRadius;
				temp[1]=top0[1]-sin(alpha)*outerRadius;
				if((topLeft[0]<temp[0] && topLeft[1]<temp[1]) || (topRight[0]<temp[0] && topRight[1]<temp[1]) || (bottomLeft[0]<temp[0] && bottomLeft[1]<temp[1]) || (bottomRight[0]<temp[0] && bottomRight[1]<temp[1])){
					return OFF;
				}
			}
		}
		if((_entry==LEFT && _exit==BOTTOM) || (_entry==BOTTOM && _exit==LEFT)){
			cg::Vector2d bottom0=cg::Vector2d(_position[0]-_trackWidth/2.0,_position[1]-_size[1]/2.0);
			cg::Vector2d bottom1=cg::Vector2d(_position[0]+_trackWidth/2.0,_position[1]-_size[1]/2.0);
			cg::Vector2d temp;
			for(double alpha=0;alpha<M_PI_2;alpha+=0.2){
				temp[0]=bottom0[0]+(cos(alpha)-1)*innerRadius;
				temp[1]=bottom0[1]+sin(alpha)*innerRadius;
				if((topLeft[0]<temp[0] && topLeft[1]<temp[1]) || (topRight[0]<temp[0] && topRight[1]<temp[1]) || (bottomLeft[0]<temp[0] && bottomLeft[1]<temp[1]) || (bottomRight[0]<temp[0] && bottomRight[1]<temp[1])){
					return OFF;
				}
				temp[0]=bottom1[0]+(cos(alpha)-1)*outerRadius;
				temp[1]=bottom1[1]+sin(alpha)*outerRadius;
				if((topLeft[0]>temp[0] && topLeft[1]>temp[1]) || (topRight[0]>temp[0] && topRight[1]>temp[1]) || (bottomLeft[0]>temp[0] && bottomLeft[1]>temp[1]) || (bottomRight[0]>temp[0] && bottomRight[1]>temp[1])){
					return OFF;
				}
			}
		}
		if((_entry==RIGHT && _exit==BOTTOM) || (_entry==BOTTOM && _exit==RIGHT)){	
			cg::Vector2d bottom0=cg::Vector2d(_position[0]-_trackWidth/2.0,_position[1]-_size[1]/2.0);
			cg::Vector2d bottom1=cg::Vector2d(_position[0]+_trackWidth/2.0,_position[1]-_size[1]/2.0);	
			cg::Vector2d temp;
			for(double alpha=0;alpha<M_PI_2;alpha+=0.2){
				temp[0]=bottom1[0]-(cos(alpha)-1)*innerRadius;
				temp[1]=bottom1[1]+sin(alpha)*innerRadius;
				if((topLeft[0]>temp[0] && topLeft[1]<temp[1]) || (topRight[0]>temp[0] && topRight[1]<temp[1]) || (bottomLeft[0]>temp[0] && bottomLeft[1]<temp[1]) || (bottomRight[0]>temp[0] && bottomRight[1]<temp[1])){
					return OFF;
				}
				temp[0]=bottom0[0]-(cos(alpha)-1)*outerRadius;
				temp[1]=bottom0[1]+sin(alpha)*outerRadius;
				if((topLeft[0]<temp[0] && topLeft[1]>temp[1]) || (topRight[0]<temp[0] && topRight[1]>temp[1]) || (bottomLeft[0]<temp[0] && bottomLeft[1]>temp[1]) || (bottomRight[0]<temp[0] && bottomRight[1]>temp[1])){
					return OFF;
				}
			}	
		}
		return CLEAR;
	}

	int TrackSection::drawMiniMap(double xPos,double yPos,double coeficient){
		cg::Vector2d entryPoint;
		cg::Vector2d exitPoint;
		cg::Vector2d topLeft=cg::Vector2d(xPos-(_size[0]/2.0)*coeficient,yPos+(_size[1]/2.0)*coeficient);
		cg::Vector2d topRight=cg::Vector2d(xPos+(_size[0]/2.0)*coeficient,yPos+(_size[1]/2.0)*coeficient);
		cg::Vector2d bottomLeft=cg::Vector2d(xPos-(_size[0]/2.0)*coeficient,yPos-(_size[1]/2.0)*coeficient);
		cg::Vector2d bottomRight=cg::Vector2d(xPos+(_size[0]/2.0)*coeficient,yPos-(_size[1]/2.0)*coeficient);
		double car0X;
		double car0Y;
		double car1X;
		double car1Y;
		cg::Vector3f color;
		double size=(_size[1]/4.0)*coeficient;
		if(_car0){
			car0X=_car0->xPosition();
			car0Y=_car0->yPosition();
			car0X-=_position[0];
			car0Y-=_position[1];
			car0X*=coeficient;
			car0Y*=coeficient;
			car0X+=xPos;
			car0Y+=yPos;
			color=_car0->color();
			glColor3f(color[0],color[1],color[2]);
			glBegin(GL_QUADS);
			glVertex3d(car0X-size,car0Y-size,0);
			glVertex3d(car0X-size,car0Y+size,0);
			glVertex3d(car0X+size,car0Y+size,0);
			glVertex3d(car0X+size,car0Y-size,0);
			glEnd();
		}
		if(_car1){
			car1X=_car1->xPosition();
			car1Y=_car1->yPosition();
			car1X-=_position[0];
			car1Y-=_position[1];
			car1X*=coeficient;
			car1Y*=coeficient;
			car1X+=xPos;
			car1Y+=yPos;
			color=_car1->color();
			glColor3f(color[0],color[1],color[2]);
			glBegin(GL_QUADS);
			glVertex3d(car1X-size,car1Y-size,0);
			glVertex3d(car1X-size,car1Y+size,0);
			glVertex3d(car1X+size,car1Y+size,0);
			glVertex3d(car1X+size,car1Y-size,0);
			glEnd();
		}
		switch(_entry){
			case(TOP):
				entryPoint=cg::Vector2d(xPos,yPos+(_size[1]/2.0)*coeficient);
				break;
			case(BOTTOM):
				entryPoint=cg::Vector2d(xPos,yPos-(_size[1]/2.0)*coeficient);
				break;
			case(LEFT):
				entryPoint=cg::Vector2d(xPos-(_size[0]/2.0)*coeficient,yPos);
				break;
			case(RIGHT):
				entryPoint=cg::Vector2d(xPos+(_size[0]/2.0)*coeficient,yPos);
				break;
		}
		switch(_exit){
			case(TOP):
				exitPoint=cg::Vector2d(xPos,yPos+(_size[1]/2.0)*coeficient);
				break;
			case(BOTTOM):
				exitPoint=cg::Vector2d(xPos,yPos-(_size[1]/2.0)*coeficient);
				break;
			case(LEFT):
				exitPoint=cg::Vector2d(xPos-(_size[0]/2.0)*coeficient,yPos);
				break;
			case(RIGHT):
				exitPoint=cg::Vector2d(xPos+(_size[0]/2.0)*coeficient,yPos);
				break;
		}
		glColor3d(0.75,0.75,0.75);
		glLineWidth(1);
		double radius=(_size[0]/2.0)*coeficient;
		switch(_entry){
			case(TOP):
				switch(_exit){
					case(BOTTOM):
						glBegin(GL_LINE_STRIP);
						glVertex3d(entryPoint[0],entryPoint[1],0);
						glVertex3d(exitPoint[0],exitPoint[1],0);
						glEnd();
						break;
					case(LEFT):
						glBegin(GL_LINE_STRIP);
						glVertex3d(entryPoint[0],entryPoint[1],0);
						for(double alpha=0;alpha<M_PI_2;alpha+=0.25){
							glVertex3d(topLeft[0]+cos(alpha)*radius,topLeft[1]-sin(alpha)*radius,0);
						}
						glVertex3d(exitPoint[0],exitPoint[1],0);
						glEnd();
						break;
					case(RIGHT):
						glBegin(GL_LINE_STRIP);
						glVertex3d(entryPoint[0],entryPoint[1],0);
						for(double alpha=0;alpha<M_PI_2;alpha+=0.25){
							glVertex3d(topRight[0]-cos(alpha)*radius,topRight[1]-sin(alpha)*radius,0);
						}
						glVertex3d(exitPoint[0],exitPoint[1],0);
						glEnd();
						break;
				}
				break;
			case(BOTTOM):
				switch(_exit){
					case(TOP):
						glBegin(GL_LINE_STRIP);
						glVertex3d(entryPoint[0],entryPoint[1],0);
						glVertex3d(exitPoint[0],exitPoint[1],0);
						glEnd();
						break;
					case(LEFT):
						glBegin(GL_LINE_STRIP);
						glVertex3d(entryPoint[0],entryPoint[1],0);
						for(double alpha=0;alpha<M_PI_2;alpha+=0.25){
							glVertex3d(bottomLeft[0]+cos(alpha)*radius,bottomLeft[1]+sin(alpha)*radius,0);
						}
						glVertex3d(exitPoint[0],exitPoint[1],0);
						glEnd();
						break;
					case(RIGHT):
						glBegin(GL_LINE_STRIP);
						glVertex3d(entryPoint[0],entryPoint[1],0);
						for(double alpha=0;alpha<M_PI_2;alpha+=0.25){
							glVertex3d(bottomRight[0]-cos(alpha)*radius,bottomRight[1]+sin(alpha)*radius,0);
						}
						glVertex3d(exitPoint[0],exitPoint[1],0);
						glEnd();
						break;
				}
				break;
			case(LEFT):
				switch(_exit){
					case(TOP):
						glBegin(GL_LINE_STRIP);
						glVertex3d(exitPoint[0],exitPoint[1],0);
						for(double alpha=0;alpha<M_PI_2;alpha+=0.25){
							glVertex3d(topLeft[0]+cos(alpha)*radius,topLeft[1]-sin(alpha)*radius,0);
						}
						glVertex3d(entryPoint[0],entryPoint[1],0);
						glEnd();
						break;
					case(BOTTOM):
						glBegin(GL_LINE_STRIP);
						glVertex3d(exitPoint[0],exitPoint[1],0);
						for(double alpha=0;alpha<M_PI_2;alpha+=0.25){
							glVertex3d(bottomLeft[0]+cos(alpha)*radius,bottomLeft[1]+sin(alpha)*radius,0);
						}
						glVertex3d(entryPoint[0],entryPoint[1],0);
						glEnd();
						break;
					case(RIGHT):
						glBegin(GL_LINE_STRIP);
						glVertex3d(entryPoint[0],entryPoint[1],0);
						glVertex3d(exitPoint[0],exitPoint[1],0);
						glEnd();
						break;
				}
				break;
			case(RIGHT):
				switch(_exit){
					case(TOP):
						glBegin(GL_LINE_STRIP);
						glVertex3d(exitPoint[0],exitPoint[1],0);
						for(double alpha=0;alpha<M_PI_2;alpha+=0.25){
							glVertex3d(topRight[0]-cos(alpha)*radius,topRight[1]-sin(alpha)*radius,0);
						}
						glVertex3d(entryPoint[0],entryPoint[1],0);
						glEnd();
						break;
					case(BOTTOM):
						glBegin(GL_LINE_STRIP);
						glVertex3d(exitPoint[0],exitPoint[1],0);
						for(double alpha=0;alpha<M_PI_2;alpha+=0.25){
							glVertex3d(bottomRight[0]-cos(alpha)*radius,bottomRight[1]+sin(alpha)*radius,0);
						}
						glVertex3d(entryPoint[0],entryPoint[1],0);
						glEnd();
						break;
					case(LEFT):
						glBegin(GL_LINE_STRIP);
						glVertex3d(entryPoint[0],entryPoint[1],0);
						glVertex3d(exitPoint[0],exitPoint[1],0);
						glEnd();
						break;
				}
				break;
		}
		return _exit;
	}

}