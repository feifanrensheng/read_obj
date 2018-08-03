#include "stdafx.h"
#include <GL/glut.h>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;


GLfloat step=0.0,s=0.1,move[]={0,0,0};


class obj3dmodel{
    struct vertex{
        double x,y,z;
    };
    struct face{
        unsigned int v1,v2,v3;
    };
    vector<vertex>vertexs;
    vector<face>faces;

public :
    void parse(const char *filename);
    void draw();
};

void obj3dmodel::parse(const char *filename){
    string s;
    ifstream fin(filename);
    if(!fin)return;
    while(fin>>s){
        switch(*s.c_str()){
        case 'f':
        {
            face f;
            fin>>f.v1>>f.v2>>f.v3;
            cout<<"f      "<<f.v1<<"       "<<f.v2 <<"       "<<f.v3<<endl;
            faces.push_back(f);
        }
        break;

        case 'v':
        {
            vertex v;
            fin>>v.x>>v.y>>v.z;
            cout<<"v      "<<v.x<<"       "<<v.y<<"       "<<v.z<<"       "<<endl;
            this->vertexs.push_back(v);
        }
        break;
        case 'w':break;
        case 'x':break;
        case 'y':break;
        case 'z':break;
        case '#':break;

        default: 
            {}
        break;
        
        }
    }         
}


void obj3dmodel::draw(){
    glBegin(GL_TRIANGLES);
    for(int i=0;i<faces.size();i++){
        //下标减一
        float move_y=0.5;
        vertex v1=vertexs[faces[i].v1-1];
        vertex v2=vertexs[faces[i].v2-1];
        vertex v3=vertexs[faces[i].v3-1];
        glColor3f(0.3,0.3,0);
        glVertex3f(v1.x,v1.y-move_y,v1.z);

        glColor3f(1,1,0);
        glVertex3f(v2.x,v2.y-move_y,v2.z);

        glColor3f(0.5,0.5,0);
        glVertex3f(v3.x,v3.y-move_y,v3.z);
    }
    glEnd();
}

obj3dmodel obj;

void myinit()
{

    GLfloat light_ambient[]={0.3,0.2,0.5};
    GLfloat light_diffuse[]={1,1,1};
    GLfloat light_position[]={2,2,2,1};
    GLfloat light1_ambient[]={0.3,0.3,0.2};
    GLfloat light1_diffuse[]={1,1,1};
    GLfloat light1_position[]={-2,-2,-2,1};

    //灯光
    glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
    glLightfv(GL_LIGHT0,GL_POSITION,light_position);
    glLightfv(GL_LIGHT1,GL_AMBIENT,light1_ambient);
    glLightfv(GL_LIGHT1,GL_DIFFUSE,light1_diffuse);
    glLightfv(GL_LIGHT1,GL_POSITION,light1_position);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    //深度
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    //材质
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    glEnable(GL_COLOR_MATERIAL);

}

void DrawColorBox(){
    obj.draw();
    //glutSolidTeapot(1);    
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    /*s+=0.005;
    if(s>1.0)s=0.1;*/  //不进行缩放

    //位移
    //move[0]+=0.005;        //x
    //move[1]+=0.005;        //y
    //move[2]+=0.005;        //z
    //if(move[0]>2)move[0]=0;
    //if(move[1]>2)move[1]=0;
    //if(move[2]>2)move[2]=0;

    glPushMatrix();
    //glScalef(s,s,s);
    //glTranslatef(move[0],move[1],move[2]);
    glRotatef(step,0,1,0);
    //glRotatef(step,0,0,1);
    //glRotatef(step,1,0,0);

    DrawColorBox();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}


void stepDisplay(){
    //旋转
    step=step+1;
    if(step>360)step=0;

    display();
}

void myReshape(GLsizei w,GLsizei h){
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w<=h){
        glOrtho(-1.5,1.5,-1.5*(GLfloat)h/(GLfloat)w,1.5*(GLfloat)h/(GLfloat)w,-10,10);
    }else{
        glOrtho(-1.5*(GLfloat)w/(GLfloat)h,1.5*(GLfloat)w/(GLfloat)h,-1.5,1.5,-10,10);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard (unsigned char key,int x,int y){
    switch(key){
    case 27:exit(0);break;
    }
}

int main( int argc, char** argv )
{
	obj.parse("66.txt");

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(500,400);
    glutCreateWindow("simple");
    myinit();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(stepDisplay);
    glutMainLoop();
    return 0;
    
}