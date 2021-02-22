/*
游戏操作：
W，A，S，D	视角上下左右
UP，DOWN	前进或后退
*/

#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <list>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string>

#include "generator.h"

#include "drawable.h"
#include "balls.h"
#include "game.h"
#include "types.h"
#include "settings.h"
#include "response.h"
#include "spark.h"
using namespace std;


bool ambient = true;	//环境光
bool diffuse = true;	//散射光
bool specular = true;	//镜面反射光
GLfloat light0_position[4] = { 0, 200, 0, 1};
const GLfloat no[4] = { 0.0, 0.0, 0.0, 1. };
GLfloat light0_ambient[] = { 0.8, 0.8, 0.8, 1 };
GLfloat light0_diffuse[] = {0.8, 0.8, 0.8, 1. };
GLfloat light0_specular[] = { 0.8, 0.8, 0.8, 1. };

GLfloat light1_position[4];
GLfloat light1_ambient[] = { 1, 1, 1, 1 };
GLfloat light1_diffuse[] = { 1, 1, 1, 1. };
GLfloat light1_specular[] = { 1, 1, 1, 1. };
GLfloat light1_direction[] = { 0, -1, 0 };

Game* game;

void mouseProcess(int button, int state, int x, int y) {
	if (state == GLUT_DOWN)
		return;
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;
	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	winX = x;
	winY = viewport[3] - (float)y;
	glReadPixels((int)winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
	game->setMouse(Vec(posX, posY, posZ));
	game->addConsumable(new MouseResponse(Vec(posX, game->getHeight(posX, posZ) + 0.1, posZ)));
	if (button == GLUT_RIGHT_BUTTON)
		game->launch();
	//cout << posX <<" "<< posY<<" "<< posZ<<endl;
}

bool open = true;
bool light0 = true;
int spotBrightness = 128;
int spotAngle = 15;

void setLight(void)
{
	if (light0){
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
		// 有无 环境光
		if (ambient == true){
			glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
		}else{
			glLightfv(GL_LIGHT0, GL_AMBIENT, no);
		}

		// 有无 散射光
		if (diffuse == true){
			glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
		}else{
			glLightfv(GL_LIGHT0, GL_DIFFUSE, no);
		}
	}
	else {
		glDisable(GL_LIGHT0);
	}
	// 有无 镜面反射光
	if (specular == true){
		glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	}else{
		glLightfv(GL_LIGHT0, GL_SPECULAR, no);
	}
	if (open) {
		glEnable(GL_LIGHT1);
		Vec mPos = game->getMotherBallPos();
		light1_position[0] = mPos.x;
		light1_position[1] = 200;
		light1_position[2] = mPos.z;
		light1_position[3] = 1;
		glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
		glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotAngle);
		glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spotBrightness);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_direction);
	}
	else {
		glDisable(GL_LIGHT1);
	}
}

void reshape(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, w, h);
	glLoadIdentity();
	float r = (float)w / h;
	gluPerspective(45., r, 0.1, 10000.0);
	glMatrixMode(GL_MODELVIEW);
}

//初始化函数
void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_ENV_MODE);
	glShadeModel(GL_SMOOTH);
}


void display();
void idle();

clock_t t;

bool debugging = false;
float posX = 100, posY = 20, posZ = 100;
int angleH = -90, angleV = 90; //angle horizontal & angel vertical

float angle = 0;
float dis = 150;


void keyProcess(unsigned char key, int x, int y)
{
	if (debugging){
		switch (key)
		{
		case 27:
			exit(0);
			break;
		case ' ':
			game->launch();
			break;
		case 'w': case 'W':
			angleV--;
			break;
		case 'a': case 'A':
			angleH++;
			break;
		case 's': case 'S':
			angleV++;
			break;
		case 'd': case 'D':
			angleH--;
			break;
		case 'o': case 'O':
			open = !open;
			break;
		case 'l': case 'L':
			light0 = !light0;
			break;
		case 'b': case 'B':
			spotBrightness++;
			cout << spotBrightness << endl;
			break;
		case 'v': case 'V':
			spotBrightness--;
			cout << spotBrightness << endl;
			break;
		case 'm': case 'M':
			spotAngle++;
			cout << spotAngle << endl;
			break;
		case 'n': case 'N':
			spotAngle--;
			cout << spotAngle << endl;
			break;
		default:
			break;
		}
		//cout << angleH << endl;
	} else {
		switch (key)
		{
		case 'o': case 'O':
			open = !open;
			break;
		case 27:
			exit(0);
			break;
		case ' ':
			game->launch();
			break;
		case 'a': case 'A': // 左转角度-1°
			angle -= 1.0;
			break;
		case 'd': case 'D': // 右转角度+1°
			angle += 1.0;
			break;
		case 'w': case 'W': // 根据左右转动后的角度，计算相机在固定坐标系中的位置
			dis -= 1;
			break;
		case 's': case 'S':
			dis += 1;
			break;
		}
	}
	glutPostRedisplay();
}

void specialKey(int key, int xx, int yy)
{
	float radH = angleH / 180.0 * 3.1415;
	float radV = angleV / 180.0 * 3.1415;
	if (debugging){
		switch (key)
		{
		case GLUT_KEY_LEFT: // 左转角度-1°
			break;
		case GLUT_KEY_RIGHT: // 右转角度+1°
			break;
		case GLUT_KEY_UP: // 根据左右转动后的角度，计算相机在固定坐标系中的位置
			posX += sin(radV)*sin(radH);
			posY += cos(radV);
			posZ += sin(radV)*cos(radH);
			break;
		case GLUT_KEY_DOWN:
			posX -= sin(radV)*sin(radH);
			posY -= cos(radV);
			posZ -= sin(radV)*cos(radH);
			break;
		}
	}
	glutPostRedisplay();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (debugging) {
		float radH = angleH / 180.0 * 3.1415;
		float radV = angleV / 180.0 * 3.1415;
		gluLookAt(posX, posY, posZ,
			posX + sin(radV)*sin(radH), posY + cos(radV), posZ + sin(radV)*cos(radH),
			0, 1, 0);
	}
	else {
		gluLookAt(dis * cos(angle / 180.0 * 3.1415), 200, dis * sin(angle / 180.0 * 3.1415), 0, 0, 0, 0, 1, 0);
	}
	//gluLookAt(0, 150, 0, 0, 0, 0, 0, 0, 1);
	//gluLookAt(100, 100, 100, 0, 0, 0, 0, 1, 0);
	setLight();
	game->draw();
	glutSwapBuffers();
}

void idle() {
	if (clock() - t < CLOCKS_PER_SEC / FPS) {
		return;
	}
	else {
		t = clock();
	}
	game->move();
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Quidditch");
	init();
	srand(time(0));
	game = Game::getGame();
	t = clock();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMouseFunc(mouseProcess);
	glutKeyboardFunc(keyProcess);
	glutSpecialFunc(specialKey);
	glutMainLoop();
}