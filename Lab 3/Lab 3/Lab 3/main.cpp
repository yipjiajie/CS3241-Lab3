// CS3241Lab1.cpp : Defines the entry point for the console application.
//#include <cmath>
#include <Windows.h>
#include "math.h"
#include <iostream>
#include <fstream>
#include "GL\glut.h"


#define M_PI 3.141592654

// global variable

bool m_Smooth = FALSE;
bool m_Highlight = FALSE;
GLfloat angle = 0;   /* in degrees */
GLfloat angle2 = 0;   /* in degrees */
GLfloat zoom = 1.0;
int mouseButton = 0;
int moving, startx, starty;

#define NO_OBJECT 4;
int current_object = 0;

using namespace std;

void setupLighting()
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	// Lights, material properties
    GLfloat	ambientProperties[]  = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat	diffuseProperties[]  = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat	specularProperties[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat lightPosition[] = {-100.0f,100.0f,100.0f,1.0f};
	
    glClearDepth( 1.0 );

	glLightfv( GL_LIGHT0, GL_POSITION, lightPosition);
	
    glLightfv( GL_LIGHT0, GL_AMBIENT, ambientProperties);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseProperties);
    glLightfv( GL_LIGHT0, GL_SPECULAR, specularProperties);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);

	// Default : lighting
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}

void drawCone(float d1, float d2, float d3, float d4) {
   
	double theta, nextTheta, rightTheta, leftTheta;
    double x0, y0, x1, y1, x2, y2, x3, y3;
    double v0x, v0y, v0z, v1x, v1y, v1z, v2x, v2y, v2z, v3x, v3y, v3z;
    double vx, vy, vz, vx2, vy2, vz2,vx3, vy3, vz3;
    double normal, normalLeft, normalRight, nx, ny, nz, nx2, ny2, nz2;
    double normalize;
	
	float no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float mat_ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    float mat_ambient_color[] = {0.2f, 0.8f, 0.2f, 1.0f};
    float mat_diffuse[] = {d1, d2, d3, d4};
    float no_shininess = 0.0f;
    float mat_emission[] = {0.3f, 0.2f, 0.2f, 0.0f};
    float mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    
    if(m_Highlight)
    {
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, 100.0f);
    } else {
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
        glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
    }
    
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    
    if(m_Smooth) {     
        for(int i = 0; i < 360; i+=10) {
            glBegin(GL_POLYGON);
            
            theta = (3.141592654/180) * i;
            nextTheta = (3.141592654/180) * (i+10);
            if(i == 0) {
                leftTheta = (3.141592654/180) * (350);
            } else {
                leftTheta = (3.141592654/180) * (i-10);
            }
            rightTheta = (3.141592654/180) * (i+20);
            
            x0 = sin(leftTheta); y0 = cos(leftTheta);
            x1 = sin(theta); y1 = cos(theta);
            x2 = sin(nextTheta); y2 = cos(nextTheta);
            x3 = sin(rightTheta); y3 = cos(rightTheta);
            
            glNormal3d(0, 0, 1);
            glVertex3f(0, 0, 2);
            v0x = x1;
            v0y = y1;
            v0z = -2;
            
            v1x = x0;
            v1y = y0;
            v1z = -2;
    
            vx = v0y * v1z - v0z * v1y;
            vy = v0z * v1x - v0x * v1z;
            vz = v0x * v1y - v0y * v1x;
            
            normal = sqrt(vx*vx + vy*vy + vz*vz);
            nx = vx/normal;
            ny = vy/normal;
            nz = vz/normal;
            
            v1x = x2; v2x = x1;
            v1y = y2; v2y = y1;
            v1z = -2; v2z = -2;
           
            vx2 = v1y * v2z - v1z * v2y;
            vy2 = v1z * v2x - v1x * v2z;
            vz2 = v1x * v2y - v1y * v2x;
            
            normal = sqrt(vx2*vx2 + vy2*vy2 + vz2*vz2);
            nx2 = vx/normal;
            ny2 = vy/normal;
            nz2 = vz/normal;
            
            normalLeft = sqrt((nx+nx2)*(nx+nx2) + (ny+ny2)*(ny+ny2) + (nz+nz2)*(nz+nz2));
            glNormal3d((nx+nx2)/normalLeft, (ny+ny2)/normalLeft, (nz+nz2)/normalLeft);
            glVertex3d(x1, y1, 0);
            v2x = x3; v3x = x2;
            v2y = y3; v3y = y2;
            v2z = -2; v3z = -2;

            vx3 = v2y * v3z - v2z * v3y;
            vy3 = v2z * v3x - v2x * v3z;
            vz3 = v2x * v3y - v2y * v3x;
            
            normal = sqrt(vx3*vx3 + vy3*vy3 + vz3*vz3);
            nx = vx3/normal;
            ny = vy3/normal;
            nz = vz3/normal;
            
            normalRight = sqrt((nx+nx2)*(nx+nx2) + (ny+ny2)*(ny+ny2) + (nz+nz2)*(nz+nz2));
            glNormal3d((nx+nx2)/normalRight, (ny+ny2)/normalRight, (nz+nz2)/normalRight);
            glVertex3d(x2, y2, 0);
            glEnd();
        }
    } else {        
        for(int i = 0; i < 360; i+=10) {
        glBegin(GL_POLYGON);
            theta = (3.141592654/180) * i;
            nextTheta = (3.141592654/180) * (i+10);
            x1 = sin(theta);
            y1 = cos(theta);
            x2 = sin(nextTheta);
            y2 = cos(nextTheta);
            
            v1x = x2; v2x = x1;
            v1y = y2; v2y = y1;
            v1z = -2; v2z = -2;
     
            vx = v1y * v2z - v1z * v2y;
            vy = v1z * v2x - v1x * v2z;
            vz = v1x * v2y - v1y * v2x;
            
            normalize = sqrt(vx*vx + vy*vy + vz*vz);
            
            glNormal3d(vx/normalize, vy/normalize, vz/normalize);
            glVertex3f(0, 0, 2);
            glVertex3d(x1, y1, 0);
            glVertex3d(x2, y2, 0);
        glEnd();
        }
    }
}

void drawCylinder(double r, double h)
{
	float no_mat[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	float mat_ambient_color[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	float mat_diffuse[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	float shininess = 20.0f;

	if (m_Highlight)
	{
		// your codes for highlight here
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_ambient_color);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	}
	else
	{
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialf(GL_FRONT, GL_SHININESS, 0.0f);
	}

	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	if (m_Smooth)
	{
		for (int a = 0; a <= 45; a++) {
			glBegin(GL_POLYGON);

			int i = 2 * a;
			glNormal3d(sin(M_PI*i / 45.0), cos(M_PI*i / 45.0), 0.5*h);
			glVertex3d(r*sin(M_PI*i / 45.0), r*cos(M_PI*i / 45.0), 0.5*h);
			glNormal3d(sin(M_PI*i / 45.0), cos(M_PI*i / 45.0), -0.5*h);
			glVertex3d(r*sin(M_PI*i / 45.0), r*cos(M_PI*i / 45.0), -0.5*h);
			glNormal3d(sin(M_PI*(i + 2) / 45.0), cos(M_PI*(i + 2) / 45.0), -0.5*h);
			glVertex3d(r*sin(M_PI*(i + 2) / 45.0), r*cos(M_PI*(i + 2) / 45.0), -0.5*h);
			glNormal3d(sin(M_PI*(i + 2) / 45.0), cos(M_PI*(i + 2) / 45.0), 0.5*h);
			glVertex3d(r*sin(M_PI*(i + 2) / 45.0), r*cos(M_PI*(i + 2) / 45.0), 0.5*h);

			glEnd();
		}
	}
	else	{
		for (int a = 0; a <= 45; a++) {
			glBegin(GL_POLYGON);

			int i = 2 * a;
			glNormal3d(r*sin(M_PI*(i + 1) / 45.0), r*cos(M_PI*(i + 1) / 45.0), 0);
			glVertex3d(r*sin(M_PI*i / 45.0), r*cos(M_PI*i / 45.0), 0.5*h);
			glVertex3d(r*sin(M_PI*i / 45.0), r*cos(M_PI*i / 45.0), -0.5*h);
			glVertex3d(r*sin(M_PI*(i + 2) / 45.0), r*cos(M_PI*(i + 2) / 45.0), -0.5*h);
			glVertex3d(r*sin(M_PI*(i + 2) / 45.0), r*cos(M_PI*(i + 2) / 45.0), 0.5*h);

			glEnd();
		}
	}
}

void drawSphere(double r, float d1, float d2, float d3, float d4)
{

	float no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float mat_ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    float mat_ambient_color[] = {0.8f, 0.8f, 0.2f, 1.0f};
    float mat_diffuse[] = {d1, d2, d3, d4};
    float no_shininess = 0.0f;
    float mat_emission[] = {0.3f, 0.2f, 0.2f, 0.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	if(m_Highlight)
	{
		// your codes for highlight here
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_diffuse);
		glMaterialf(GL_FRONT, GL_SHININESS, 100.0f);
	} else {
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
	}

    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	
    int i,j;
	int n = 20;
    for(i=0;i<n;i++)
		for(j=0;j<2*n;j++)
		if(m_Smooth)
		{
			glBegin(GL_POLYGON);

			    // the normal of each vertex is actaully its own coordinates normalized for a sphere

			    // your normal here
				glNormal3d(sin(i*M_PI/n)*cos(j*M_PI/n),cos(i*M_PI/n)*cos(j*M_PI/n),sin(j*M_PI/n));
				glVertex3d(r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
			    // your normal here
				glNormal3d(sin((i+1)*M_PI/n)*cos(j*M_PI/n),cos((i+1)*M_PI/n)*cos(j*M_PI/n),sin(j*M_PI/n));
				glVertex3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
			    // your normal here
				glNormal3d(sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),sin((j+1)*M_PI/n));
				glVertex3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
			    // your normal here
				glNormal3d(sin(i*M_PI/n)*cos((j+1)*M_PI/n),cos(i*M_PI/n)*cos((j+1)*M_PI/n),sin((j+1)*M_PI/n));
				glVertex3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
 			glEnd();
		} else	{
			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i+0.5)*M_PI/n)*cos((j+0.5)*M_PI/n),cos((i+0.5)*M_PI/n)*cos((j+0.5)*M_PI/n),sin((j+0.5)*M_PI/n));
				glVertex3d(r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
				glVertex3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
				glVertex3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
				glVertex3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
 			glEnd();
		}

}

void drawIceCreamCone() {

	drawCone(0.5,0.25,0,0);

	glPushMatrix();
	drawSphere(1,1,1,1,0);
	glTranslatef(0,0,-1.1);
	drawSphere(0.7,1,0.5,0.5,0);
	glTranslatef(0,0,-1.05);
	drawSphere(0.5,0.191,0.0937,0,0);
	glPopMatrix();

}

void drawMianBaoChaoRen(){

	//Draw Face
	drawSphere(1,0.968,0.702,0.453,0);

	//Draw Nose
	glPushMatrix();
	glTranslatef(0,0.9,0);
	drawSphere(0.3,1,0,0,0);
	glPopMatrix();

	//Draw Cheeks
	glPushMatrix();
	glTranslatef(-0.4,0.8,0);
	drawSphere(0.2,0.9,0.33,0.2,0);
	glTranslatef(0.8,0,0);
	drawSphere(0.2,0.9,0.33,0.2,0);
	glPopMatrix();

	//Draw Eyes
	glPushMatrix();
	glTranslatef(-0.25,0.75,-0.5);
	drawSphere(0.1,0,0,0,0);
	glTranslatef(0.5,0,0);
	drawSphere(0.1,0,0,0,0);
	glPopMatrix();

}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		glTranslatef(0, 0, -6);

	    glRotatef(angle2, 1.0, 0.0, 0.0);
		glRotatef(angle, 0.0, 1.0, 0.0);

		glScalef(zoom,zoom,zoom);

		switch (current_object) {
		case 0:
			drawSphere(1,1,1,1,1);
			break;
		case 1:
			// draw your second primitive object here
			drawCone(1,2,2,1);
			//drawCylinder(1,1);
			break;
		case 2:
			// draw your first composite object here
			drawIceCreamCone();
			break;
		case 3:
			// draw your second composite object here
			drawMianBaoChaoRen();
			break;
		default:
			break;
		};
	glPopMatrix();
	glutSwapBuffers ();
}

void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
	case 'p':
	case 'P':
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		break;			
	case 'w':
	case 'W':
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		break;			
	case 'v':
	case 'V':
		glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
		break;			
	case 's':
	case 'S':
		m_Smooth = !m_Smooth;
		break;
	case 'h':
	case 'H':
		m_Highlight = !m_Highlight;
		break;

	case '1':
	case '2':
	case '3':
	case '4':
		current_object = key - '1';
		break;

	case 'Q':
	case 'q':
		exit(0);
	break;

	default:
	break;
	}

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
  if (state == GLUT_DOWN) {
	mouseButton = button;
    moving = 1;
    startx = x;
    starty = y;
  }
  if (state == GLUT_UP) {
	mouseButton = button;
    moving = 0;
  }
}

void motion(int x, int y)
{
  if (moving) {
	if(mouseButton==GLUT_LEFT_BUTTON)
	{
		angle = angle + (x - startx);
		angle2 = angle2 + (y - starty);
	}
	else zoom += ((y-starty)*0.001);
    startx = x;
    starty = y;
	glutPostRedisplay();
  }
  
}

int main(int argc, char **argv)
{
	cout<<"CS3241 Lab 3"<< endl<< endl;

	cout << "1-4: Draw different objects"<<endl;
	cout << "S: Toggle Smooth Shading"<<endl;
	cout << "H: Toggle Highlight"<<endl;
	cout << "W: Draw Wireframe"<<endl;
	cout << "P: Draw Polygon"<<endl;
	cout << "V: Draw Vertices"<<endl;
	cout << "Q: Quit" <<endl<< endl;

	cout << "Left mouse click and drag: rotate the object"<<endl;
	cout << "Right mouse click and drag: zooming"<<endl;

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	glutCreateWindow ("CS3241 Assignment 3");
	glClearColor (1.0,1.0,1.0, 1.0);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	setupLighting();
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST); 
	glDepthMask(GL_TRUE);

    glMatrixMode(GL_PROJECTION);
    gluPerspective( /* field of view in degree */ 40.0,
  /* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 80.0);
	glMatrixMode(GL_MODELVIEW);
	glutMainLoop();

	return 0;
}
