#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define RAD 1.45
GLint Width = 900, Height = 900;
const float CSize = 4.4;
float step=0.5;

void drawCube() {
  glClearStencil(0x0);
  glEnable(GL_STENCIL_TEST);

  glStencilFunc(GL_ALWAYS, 1, 0xFF);
  glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
  glutSolidCube(2.0);

  glStencilFunc(GL_ALWAYS, 2, 0xFF);
  glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);  
  glutSolidSphere(RAD, 100, 100);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glColor3ub(120,60,30);
  glStencilFunc(GL_EQUAL, 1, 0xFF);
  glutSolidSphere(RAD, 100, 100);
  
  glColor3ub(120,60,130);
  glStencilFunc(GL_EQUAL, 2, 0xFF);
  glutSolidCube(2.0);
  glDisable(GL_STENCIL_TEST);
}	

void drawBox(void) {
  
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);
  glColor4ub(0,0,255,120);
  glutSolidCube(CSize);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING); 
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
 
  glPushMatrix();
  glTranslatef(step, 0.0, 0.0);
  drawCube();
  glPopMatrix();
  
  drawBox();
  glutSwapBuffers();
}


void aniM(int value)
{
  glutPostRedisplay();
  glutTimerFunc(1000, aniM, 0);
}


void init(void) {

  GLfloat light_diffuse[] = {0.5, 0.5, 0.5, 0.5};   
  GLfloat light_position[] = {-1.0, -1.0, 1.0, 1.0};  

  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  /* Setup the view of the cube. */
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(7.0, 0.0, 5.0,  
            0.0, 0.0, 0.0,  
            0.0, 1.0, 0.0); 

  /* Adjust cube position to be asthetic angle. */
  glTranslatef(0.0, 0.0, -1.0);  /* shift to z=-1 */
  glRotatef(40, 1.0, 0.0, 0.0);  /* rotate 60 degree around x-axe */
  glRotatef(-20, 0.0, 0.0, 1.0); /* rotate -20 degree around z-axe */

  /* Setup the projection model */
  glMatrixMode(GL_PROJECTION);
  gluPerspective( /* field of view in degree */ 50.0,
    /* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 15.0);
}

void Keyboard(unsigned char key, int x, int y) {
    if( key == 'q' ) {
		if(step >= 1.3) {
			step=-2*step;
		}
		else{
		step+=0.8;
	}
	}
	if( key == 'p' ) {
	
	}
        
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(Width, Height);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
  glutCreateWindow("Kontr_Work");
  glutDisplayFunc(display);
  glutKeyboardFunc(Keyboard);
  glutTimerFunc(1000, aniM, 0);
  init();
  glutMainLoop();
  return 0;             
}
