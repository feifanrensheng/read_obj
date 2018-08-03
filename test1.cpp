#include <cmath>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glut.h>
#include <vector>

using namespace std;

class ObjLoader
{
public:
	ObjLoader(string filename);
	void Draw();
private:
	vector<vector<GLfloat>>vSets;//存放顶点(x,y,z)坐标
	vector<vector<GLint>>fSets;//存放面的三个顶点索引
};

ObjLoader::ObjLoader(string filename)
{
	std::ifstream file(filename);
	std::string line;
while (getline(file, line))
{
	if (line.substr(0, 2) == "vt")
	{

	}
	else if (line.substr(0, 2) == "vn")
	{

	}
	else if (line.substr(0, 1) == "v")
	{
		vector<GLfloat> Point;
		GLfloat x, y, z;
		std::istringstream s(line.substr(2));
		s >> x; s >> y; s >> z;
		Point.push_back(x);
		Point.push_back(y);
		Point.push_back(z);
		vSets.push_back(Point);

	}
	else if (line.substr(0, 1) == "f")
	{
		vector<GLint> vIndexSets;
		GLint u, v, w;
		std::istringstream vtns(line.substr(2));
		vtns >> u; vtns >> v; vtns>> w;
		vIndexSets.push_back(u-1);
		vIndexSets.push_back(v-1);
		vIndexSets.push_back(w-1);
		fSets.push_back(vIndexSets);
	}
	else if (line.substr(0, 1) == "#")
	{

	}
	else
	{

	}
}
file.close();
}



void ObjLoader::Draw(){

	glBegin(GL_TRIANGLES);//开始绘制
	for (int i = 0; i < fSets.size(); i++) {
		GLfloat VN[3];
		//三个顶点
		GLfloat SV1[3];
		GLfloat SV2[3];
		GLfloat SV3[3];

		if ((fSets[i]).size() != 3) {
			cout << "the fSetsets_Size is not correct" << endl;
		}
		else {
				GLint firstVertexIndex = (fSets[i])[0];//取出顶点索引
				GLint secondVertexIndex = (fSets[i])[1];
				GLint thirdVertexIndex = (fSets[i])[2];

				SV1[0] = (vSets[firstVertexIndex])[0];//第一个顶点
				SV1[1] = (vSets[firstVertexIndex])[1];
				SV1[2] = (vSets[firstVertexIndex])[2];

				SV2[0] = (vSets[secondVertexIndex])[0]; //第二个顶点
				SV2[1] = (vSets[secondVertexIndex])[1];
				SV2[2] = (vSets[secondVertexIndex])[2];

				SV3[0] = (vSets[thirdVertexIndex])[0]; //第三个顶点
				SV3[1] = (vSets[thirdVertexIndex])[1];
				SV3[2] = (vSets[thirdVertexIndex])[2];


				GLfloat vec1[3], vec2[3], vec3[3];//计算法向量
				//(x2-x1,y2-y1,z2-z1)
				vec1[0] = SV1[0] - SV2[0];
				vec1[1] = SV1[1] - SV2[1];
				vec1[2] = SV1[2] - SV2[2];

				//(x3-x2,y3-y2,z3-z2)
				vec2[0] = SV1[0] - SV3[0];
				vec2[1] = SV1[1] - SV3[1];
				vec2[2] = SV1[2] - SV3[2];

				//(x3-x1,y3-y1,z3-z1)
				vec3[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
				vec3[1] = vec2[0] * vec1[2] - vec2[2] * vec1[0];
				vec3[2] = vec2[1] * vec1[0] - vec2[0] * vec1[1];

				GLfloat D = sqrt(pow(vec3[0], 2) + pow(vec3[1], 2) + pow(vec3[2], 2));

				VN[0] = vec3[0] / D;
				VN[1] = vec3[1] / D;
				VN[2] = vec3[2] / D;
           
				glNormal3f(VN[0], VN[1], VN[2]);//绘制法向量

				glVertex3f(SV1[0], SV1[1], SV1[2]);//绘制三角面片
				glVertex3f(SV2[0], SV2[1], SV2[2]);
				glVertex3f(SV3[0], SV3[1], SV3[2]);	
		}
	}
	glEnd();
}

//模型路径
string filePath = "../data/monkey.obj";

ObjLoader objModel = ObjLoader(filePath);
//实现移动鼠标观察模型所需变量
static float c = 3.1415926 / 180.0f;
static float r = 1.0f;
static int degree = 90;
static int oldPosY = -1;
static int oldPosX = -1;

//安置光源
void setLightRes() {
	GLfloat lightPosition[] = { 0.0f, 0.0f, 1.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glEnable(GL_LIGHTING); //启用光源
	glEnable(GL_LIGHT0);   //使用指定灯光
}

//初始化
void init() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("ObjLoader");
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	setLightRes();
	glEnable(GL_DEPTH_TEST);
}

void display()
{
	glColor3f(1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);                            
	glLoadIdentity();                                     
	glTranslatef(0.0f, 0.0f, -5.0f);              												
	setLightRes();
	glPushMatrix();

	gluLookAt(r*cos(c*degree), 0, r*sin(c*degree), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);


	objModel.Draw();//绘制obj模型
	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (GLdouble)width / (GLdouble)height, 1.0f, 200.0f);
	glMatrixMode(GL_MODELVIEW);
}

//移动鼠标360观察模型
void moseMove(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) {
		oldPosX = x; oldPosY = y;
	}
}
void changeViewPoint(int x, int y)
{
	int temp = x - oldPosX;
	degree += temp;
	oldPosX = x;
	oldPosY = y;
}

void myIdle()
{
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(moseMove);
	glutMotionFunc(changeViewPoint);
	glutIdleFunc(myIdle);
	glutMainLoop();
	return 0;
}