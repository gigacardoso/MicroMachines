#include "Block.h"

namespace micro_machines{

	Block::Block(std::string id,double x,double y):Obstacle(id,x,y){}

	Block::~Block(){}

	void Block::draw(){
		cg::Vector3d vMin=-_size/2.0;
		cg::Vector3d vMax=_size/2.0;
		cg::Vector3d v0=cg::Vector3d(vMin[0],vMax[1],vMin[2]);
		cg::Vector3d v1=cg::Vector3d(vMin[0],vMax[1],vMax[2]);
		cg::Vector3d v2=cg::Vector3d(vMin[0],vMin[1],vMax[2]);
		cg::Vector3d v3=cg::Vector3d(vMax[0],vMin[1],vMax[2]);
		cg::Vector3d v4=cg::Vector3d(vMax[0],vMin[1],vMin[2]);
		cg::Vector3d v5=cg::Vector3d(vMax[0],vMax[1],vMin[2]);
		vMin+=_position;
		vMax+=_position;
		v0+=_position;
		v1+=_position;
		v2+=_position;
		v3+=_position;
		v4+=_position;
		v5+=_position;
		/*Vertex Normals*/
		double sOT=sqrt(1.0/3.0);
		cg::Vector3d nMin=cg::Vector3d(-sOT,-sOT,-sOT);
		cg::Vector3d nMax=cg::Vector3d(sOT,sOT,sOT);
		cg::Vector3d n0=cg::Vector3d(-sOT,sOT,-sOT);
		cg::Vector3d n1=cg::Vector3d(-sOT,sOT,sOT);
		cg::Vector3d n2=cg::Vector3d(-sOT,-sOT,sOT);
		cg::Vector3d n3=cg::Vector3d(sOT,-sOT,sOT);
		cg::Vector3d n4=cg::Vector3d(sOT,-sOT,-sOT);
		cg::Vector3d n5=cg::Vector3d(sOT,sOT,-sOT);
		/*Materials*/
		cg::Vector3f specular=cg::Vector3f(1,1,1);
		float shininess=90.0f;
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,_color.get());
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular.get());
		glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shininess);
		glLineWidth(1.5);
		/*Top*/
		glBegin(GL_QUADS);
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
		glBegin(GL_QUADS);
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
		glBegin(GL_QUADS);
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
		glBegin(GL_QUADS);
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
		glBegin(GL_QUADS);
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
		glBegin(GL_QUADS);
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

	bool Block::isCollision(cg::Vector3d topLeft,cg::Vector3d topRight,cg::Vector3d bottomLeft,cg::Vector3d bottomRight){
		cg::Vector3d vMin=_position-_size/2.0;
		cg::Vector3d vMax=_position+_size/2.0;
		if(topLeft[0]<vMax[0] && topLeft[0]>vMin[0] && topLeft[1]<vMax[1] && topLeft[1]>vMin[1]){
			return true;
		}
		if(topRight[0]<vMax[0] && topRight[0]>vMin[0] && topRight[1]<vMax[1] && topRight[1]>vMin[1]){
			return true;
		}
		if(bottomLeft[0]<vMax[0] && bottomLeft[0]>vMin[0] && bottomLeft[1]<vMax[1] && bottomLeft[1]>vMin[1]){
			return true;
		}
		if(bottomRight[0]<vMax[0] && bottomRight[0]>vMin[0] && bottomRight[1]<vMax[1] && bottomRight[1]>vMin[1]){
			return true;
		}
		return false;
	}

}