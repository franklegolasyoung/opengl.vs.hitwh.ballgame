#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include "glut.h"
//#include <GL/glut.h>
//#pragma comment(lib, "glut.lib")
//#pragma comment(lib, "glut32.lib")


using namespace std;

//******************************************************************************/
//**** You may change the initial values of some parameter in your init() ******/
//****                                                                     *****/

double xfoc = 0., yfoc = 0.0, zfoc = 0.0;		//Focal point position
double fovy = 40.;								//Viewing angle

double xyzmax = 9.;								//Inital length of the axes in the small viewports

double Zfar = xyzmax;							//Inital distance of the far clipping plane
double Znear = 1.;								//Initial dist'n of the near clipping plane

double delta = 0.0625;							//Amount changed in a parameter when it is adjusted.

int    winWidth = 900;		 					//The default width of the window
int    winHeight = 600;							//The default height of the window

bool showCamera = true;							//Flag for showing the small viewports
bool showAxis = true;							//Flag for showing the the axes

//***                                                                      *****/
//******************************************************************************/

double xcam = 0., ycam = 0., zcam = 3.;		//Camera position



//max number of vertices and triangles
#define  MAXNUMV 2000000
#define  MAXNUMT 2500000

// the mesh
int NUMV;	        //number of vertices
int NUMT;	        //number of triangles

GLfloat vertices[MAXNUMV][3];
GLfloat normals[MAXNUMV][3];
GLfloat colors[MAXNUMV][3]; 
int indices[MAXNUMT][3];


//*****End of object definition *******************************************
GLfloat ambient[] = { .22, .15, .10, 1.};
GLfloat diffuse[] = { .89, .82, .58,1./* .5, .0, .0, 1.*/};
GLfloat specular[] = {.5, .5, .5, 1.};
float   shininess= 120.0f;

GLfloat light_ambient[] = { 0.7, 0.7, 0.7, 1.};
GLfloat light_diffuse0[] = { 0.8, .8, 0.8, 1.};
GLfloat light_specular0[] = { 0.7, .7, 0.7, 1.};
GLfloat light_position0[] = { 0.5, 0.5, 1.0, 1.0};

double  Px[9]={-0.5, 0.1, 0.5, -0.5, 0.2, 0.5, -0.5, 0.1, 0.5 };
double Py[9]= {0.1, 0.4, 0.1, -0.2, 0.2, -0.2 , -0.6, -0.4, -0.3};
double  Pz[9] ={-0.2, 0.1, 0.3, 0.2, 0.3, 0.2, 0.3, 0.5, 0.1};


//计算S(u,v)处的点(x,y,z)
void surfacepoint(double u, double v,  double& x, double& y, double& z)
{
	double ax0 = -0.5;
	double ay0 = 0.1;
	double az0 = -0.2;
	double bx0 = 0.1;
	double by0 = 0.4;
	double bz0 = 0.1;
	double cx0 = 0.5;
	double cy0 = 0.1;
	double cz0 = 0.3;
	double ax1 = -0.5;
	double ay1 = -0.2;
	double az1 = 0.2;
	double bx1 = 0.2;
	double by1 = 0.2;
	double bz1 = 0.3;
	double cx1 = 0.5;
	double cy1 = -0.2;
	double cz1 = 0.2;
	double ax2 = -0.5;
	double ay2 = -0.6;
	double az2 = 0.3;
	double bx2 = 0.1;
	double by2 = -0.4;
	double bz2 = 0.5;
	double cx2 = 0.5;
	double cy2 = -0.3;
	double cz2 = 0.1;
	double u1 = (1 - u) * (1 - u);
	double u2 = 2 * (1 - u) * u;
	double u3 = u * u;

	double ax = u1 * ax0 + u2 * ax1 + u3 * ax2;
	double ay = u1 * ay0 + u2 * ay1 + u3 * ay2;
	double az = u1 * az0 + u2 * az1 + u3 * az2;
	double bx = u1 * bx0 + u2 * bx1 + u3 * bx2;
	double by = u1 * by0 + u2 * by1 + u3 * by2;
	double bz = u1 * bz0 + u2 * bz1 + u3 * bz2;
	double cx = u1 * cx0 + u2 * cx1 + u3 * cx2;
	double cy = u1 * cy0 + u2 * cy1 + u3 * cy2;
	double cz = u1 * cz0 + u2 * cz1 + u3 * cz2;

	double v1 = (1 - v) * (1 - v);
	double v2 = 2 * (1 - v) * v;
	double v3 = v * v;
	x = v1 * ax + v2 * bx + v3 * cx;
	y = v1 * ay + v2 * by + v3 * cy;
	z = v1 * az + v2 * bz + v3 * cz;

}

void  surface_generation()
{

   int n = 30;
   double step = 1.0/n;

   // sampling points
   for(int  i = 0; i <= n; i++)
   {
	   for(int j = 0;  j <= n;  j++)
	   {
		   double  u = i * step;
		   double  v = j * step;

		   double x, y, z;

		   surfacepoint(u,v, x, y,z);
		     vertices[i * (n+1) + j][0] =  x;
			 vertices[i * (n+1) + j][1] =  y;
			 vertices[i * (n+1) + j][2] =  z;

	   }
   }

    NUMV = (n+1) * (n+1);
	NUMT = n * n * 2;
    
	int inn = 0;
	for(int i=0; i < n; i++)
	{
		for(int j = 0;  j < n; j++)
		{
			// two triangles

			indices[inn][0] = i* (n+1) +j;
			indices[inn][1] = (i+1)* (n+1) +j;
			indices[inn][2] = i * (n+1) +j + 1;


			inn++;

			indices[inn][0] = i* (n+1) +j + 1;
			indices[inn][1] = (i+1)* (n+1) +j;
			indices[inn][2] = (i + 1) * (n+1) +j + 1;

			inn ++;


		}
	}


}


//void light()
//{
//	glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
//	glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
//	glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular0);
//	glLightfv( GL_LIGHT0, GL_POSITION, light_position0);
//}
//
//void materialSkin() {
//	glMaterialfv( GL_FRONT, GL_AMBIENT, ambient);
//	glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse);	
//	glMaterialfv( GL_FRONT, GL_SPECULAR, specular);
//	glMaterialf( GL_FRONT, GL_SHININESS, shininess);
//}

void Normalize(float* const p)
{
	float mag=sqrtf(p[0]*p[0]+p[1]*p[1]+p[2]*p[2]);
	if (mag>.0f){
		p[0]/=mag;
		p[1]/=mag;
		p[2]/=mag;
	}
}

//To compute the normal of a surface from three points.
//   normal = (p1-p0) x (p2-p0) pointing outward in RH coordinate system.
void TriangleNormal(const GLfloat* const p0, const GLfloat* const p1,
					const GLfloat* const p2, GLfloat* const n) {

	double  x3, y3, z3,   x4, y4, z4;  //t: (x3, y3, z3),  r: (x4, y4, z4)

	x3 = -p1[0] + p0[0];  y3 = -p1[1] + p0[1];  z3 = -p1[2] + p0[2];  //t=P1-P0
	x4 = p2[0] - p0[0];  y4 = p2[1] - p0[1];  z4 = p2[2] - p0[2];  //r=P2-P0

	// n = t x r.  X is the cross-product. u is perpendicular to the plane
	n[0] = y3*z4 - y4*z3;   n[1] = -(x3*z4 - x4*z3);   n[2] = x3*y4 - x4*y3;

	Normalize(n);
}

void findmeshnormal()
{
	memset(normals,0,sizeof(float)*NUMV*3);  //initialize

	for (int i=0; i<NUMT; i++){
		float n[3];
		TriangleNormal(vertices[indices[i][0]],vertices[indices[i][1]],
			vertices[indices[i][2]],n);

		normals[indices[i][0]][0]+=n[0];
		normals[indices[i][0]][1]+=n[1];
		normals[indices[i][0]][2]+=n[2];
		normals[indices[i][1]][0]+=n[0];
		normals[indices[i][1]][1]+=n[1];
		normals[indices[i][1]][2]+=n[2];
		normals[indices[i][2]][0]+=n[0];
		normals[indices[i][2]][1]+=n[1];
		normals[indices[i][2]][2]+=n[2];
	}

	for (int i=0; i<NUMV; i++){
		Normalize(normals[i]);
	}
}



void init()
{
	//glClearColor( 0.0, 0.0, 0.0, 0.0);  //Set the clear color to black

	//glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// used for the transparent view frustum
	//glEnable( GL_NORMALIZE);							// must enable this if there is scaling or shearing transform
	//glShadeModel( GL_SMOOTH );		
	//
	//glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
// shading model

	//light();											// the only light source
	//glEnable( GL_LIGHTING);
	//glEnable( GL_LIGHT0);

	findmeshnormal();
	

	
}

void drawlightsphere(){
	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);
	glColor3f(1.0f,1.0f,1.0f);
	glPushMatrix();
	glTranslatef(light_position0[0],light_position0[1],light_position0[2]);
	GLUquadricObj* q=gluNewQuadric();
	gluSphere(q,.05f,8,8);
	gluDeleteQuadric(q);
	glPopMatrix();
	glPopAttrib();
}



void DrawFace()
{
	glDisable(GL_LIGHTING);
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < NUMT; i++) {
		glColor3f(colors[indices[i][0]][0], colors[indices[i][0]][1], colors[indices[i][0]][2]);
		glVertex3f(vertices[indices[i][0]][0], vertices[indices[i][0]][1], vertices[indices[i][0]][2]);
		glColor3f(colors[indices[i][1]][0], colors[indices[i][1]][1], colors[indices[i][1]][2]);
		glVertex3f(vertices[indices[i][1]][0], vertices[indices[i][1]][1], vertices[indices[i][1]][2]);
		glColor3f(colors[indices[i][2]][0], colors[indices[i][2]][1], colors[indices[i][2]][2]);
		glVertex3f(vertices[indices[i][2]][0], vertices[indices[i][2]][1], vertices[indices[i][2]][2]);
	}
	glEnd();
}




void phong()
{
	//每一个顶点计算一个颜色
	GLfloat  SZ[3];//入射光向量
	GLfloat  RZ[3];//镜面反射光向量
	GLfloat  VZ[3];//人眼的视角向量
	//每一个顶点计算一个颜色
	for (int i = 0; i < NUMV; i++) {
		//计算每个网格的视角向量，---------GLfloat vertices[MAXNUMV][3];存放网格的顶点
		VZ[0] = vertices[i][0] - xcam;//xcam、ycam、zcam是人眼的坐标
		VZ[1] = vertices[i][1] - ycam;
		VZ[2] = vertices[i][2] - zcam;
		Normalize(VZ);//单位化
		//计算光源的入向量，---------------GLfloat light_position0[] = { 0.5, 0.5, 1.0, 1.0};光源的位置
		SZ[0] = vertices[i][0] - light_position0[0];
		SZ[1] = vertices[i][1] - light_position0[1];
		SZ[2] = vertices[i][2] - light_position0[2];
		Normalize(SZ);//单位化
		//计算n·s
		GLfloat  cos1 = SZ[0] * normals[i][0] + SZ[1] * normals[i][1] + SZ[2] * normals[i][2];
		//计算反射光的向量r = 2 (n·s)n - s；ppt上的公式
		RZ[0] = 2 * (cos1)* normals[i][0] - SZ[0];
		RZ[1] = 2 * (cos1)* normals[i][1] - SZ[1];
		RZ[2] = 2 * (cos1)* normals[i][2] - SZ[2];
		Normalize(RZ);//单位化
		//计算反射光与人眼之间的夹角的cos值：r·v
		GLfloat  cos2 = RZ[0] * VZ[0] + RZ[1] * VZ[1] + RZ[2] * VZ[2];
		colors[i][0] = ambient[0] * light_ambient[0] + diffuse[0] * light_diffuse0[0] * cos1 + specular[0] * light_specular0[0] * pow(cos2, shininess);
		colors[i][1] = ambient[1] * light_ambient[1] + diffuse[1] * light_diffuse0[1] * cos1 + specular[1] * light_specular0[1] * pow(cos2, shininess);
		colors[i][2] = ambient[2] * light_ambient[2] + diffuse[2] * light_diffuse0[2] * cos1 + specular[2] * light_specular0[2] * pow(cos2, shininess);
	}
}



void draw()
{
	//light();

	//glDisable(GL_BLEND);		// disable blending used in side views
	//glEnable(GL_DEPTH_TEST);	// enable depth test
	//glEnable( GL_LIGHTING);		// enable lighting
	//glEnable( GL_LIGHT0);		// turn light 0 on
 //   
	//materialSkin();		// set material
	//	
	phong();

	DrawFace();
	
	drawlightsphere();
}



void  hkgluPlatform(void) {
     double Extent = 9.;
     int width, h = winHeight / 2;

     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     width = winWidth;
     glViewport( 0, 0, width, winHeight);

     glMatrixMode( GL_PROJECTION);
     glLoadIdentity();
	 gluPerspective( fovy, (double) width/winHeight, Znear, Zfar);

     glMatrixMode( GL_MODELVIEW);
     glLoadIdentity();
     gluLookAt( xcam, ycam, zcam, xfoc, yfoc, zfoc, 0., 1., 0.);

     draw();
	 glutSwapBuffers();

}



#define SQUARE(x) (x*x)
int initial_mouse_x, initial_mouse_y;
double initial_x, initial_y, initial_z;
bool is_leftbutton_pressed = false;
const double ROTATION_RATIO = 3.1416/1600.; // 90 deg per 800 pixel displacement

//A call back that perform some viewing function with mouse

void mouse(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) {
		//if (!is_rightbutton_pressed) {
			if (state == GLUT_DOWN) {
				initial_mouse_x = x;
				initial_mouse_y = y;
				initial_x = xcam;
				initial_y = ycam;
				initial_z = zcam;
				is_leftbutton_pressed = true;
			} else { // assume state == GLUT_UP
				is_leftbutton_pressed = false;
			}
		//}
	}
}


//A call back that change the position of camera with mouse
void mouse_motion(int mouse_x, int mouse_y) {

	if (is_leftbutton_pressed) {
			int x_displacement = initial_mouse_x - mouse_x; // -(mouse_x - initial_mouse_x);
			int y_displacement = mouse_y - initial_mouse_y; // mouse_y - initial_mouse_y;
			
			double center_x, center_y, center_z;			// coordinate of origin of rotation
			double point_x, point_y, point_z;				// final coordinate after rotation

			center_x = xfoc;
			center_y = yfoc;
			center_z = zfoc;

			/*  perform rotation about y axis  */

			double theta = static_cast<double>(x_displacement) * ROTATION_RATIO;  // rotation angle about y
			double sin_theta = sin(theta);
			double cos_theta = cos(theta);
			double init_rel_x = initial_x - center_x;		// initial relative point_x when center is translated to origin
			double init_rel_z = initial_z - center_z;		// initial relative point_z when center is translated to origin

			double relative_x = init_rel_x*cos_theta + init_rel_z*sin_theta;
			double relative_z = init_rel_z*cos_theta - init_rel_x*sin_theta;

			/*  perform rotation about a horizontal line  */

			double relative_y = initial_y - center_y;

			double alpha = static_cast<double>(y_displacement) * ROTATION_RATIO;  // rotation angle about a line on x-z plane
			double sin_alpha = sin(alpha);
			double cos_alpha = cos(alpha);

			double hyp = sqrt(SQUARE(relative_x)+SQUARE(relative_z));
			double cos_gamma = relative_x/hyp;
			double sin_gamma = relative_z/hyp;
			double cos_gamma_square = SQUARE(cos_gamma);
			double sin_gamma_square = SQUARE(sin_gamma);
			double sin_alpha_times_cos_gamma = sin_alpha*cos_gamma;
			double sin_alpha_times_sin_gamma = sin_alpha*sin_gamma;
			double camotsgcg = (cos_alpha - 1.)*sin_gamma*cos_gamma; // Cos_Alpha_Minus_One_Times_Sin_Gamma_Cos_Gamma
			
			point_x = center_x + (relative_x*(cos_alpha*cos_gamma_square+sin_gamma_square) + relative_y*(-sin_alpha_times_cos_gamma) + relative_z*(camotsgcg));
			point_y = center_y + (relative_x*(sin_alpha_times_cos_gamma) + relative_y*(cos_alpha) + relative_z*(sin_alpha_times_sin_gamma));
			point_z = center_z + (relative_x*(camotsgcg) + relative_y*(-sin_alpha_times_sin_gamma) + relative_z*(cos_alpha*sin_gamma_square+cos_gamma_square));
			
			xcam = point_x;
			ycam = point_y;
			zcam = point_z;
	}

	glutPostRedisplay();
} 

void menuf(  int i)  {
}


void reShape(int w, int h)
{   

    winWidth = w;
    winHeight = h;
    if (showCamera && (w < h) ) winHeight = w;

    glutPostRedisplay();
}


//****** The following are needed for starting hkgluPlatform1   ***/
void hkgluPlatformInit() {

    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    glutInitWindowSize(winWidth, winHeight);

    glutCreateWindow("Mesh Shading");

	glutReshapeFunc( reShape);

    glutDisplayFunc(hkgluPlatform);

    glutMouseFunc(mouse);
    glutMotionFunc(mouse_motion);

   

    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


int _tmain(int argc, _TCHAR* argv[])
{
    glutInit(&argc, argv);

    hkgluPlatformInit();

	surface_generation();

    init();
	
    glutMainLoop();

	return 0;
}


