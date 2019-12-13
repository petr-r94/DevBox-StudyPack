#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#define MILL_SEC 60
const float Width = 1024, Height = 600;
const float rebro = 35.0;
const float quad_a = 6.0;
const float gap = 2.0;
const float sphereDist = 10.0;
const float DodgeMin= 0.0;
const float DodgeMax= 10.0;
const float DodgeStepUp= 0.6;
const float DodgeStepDown= -0.6;
float Dodge = 0.0;
float Sx= 1.0;
float Sy= 1.0;
float Sz= 1.0;
float vX= 45.0;
float vY= 40.0;
int Push = 0;
int up = 1;

const float dAngl= 3.0;
const float Scal= 1.018;

void AspectView() {
  glTranslatef(0, 0, -100.0);
  glRotatef(vX, 1.0, 0, 0);
  glRotatef(vY, 0, 1.0, 0);
  glScalef(Sx, Sy, Sz);
  
}

void initScene(void) {
  
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_DEPTH_TEST);
  
  glColor3f(1.0, 0, 0);
  
  // Освещение
  float light0_diffuse[] = {0.5, 0.5, 0.8, 1.0};  
  float light0_direction[] = {0, 0, -100.0, 1.0}; 
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light0_direction);
  
  //glDisable(GL_LIGHT0);

  glMatrixMode(GL_PROJECTION);
  float Aspect = Width/Height;
  gluPerspective(60.0, Aspect, 1.0f, 1000.0f);
  glMatrixMode(GL_MODELVIEW);
}

void PyraMydus(float a, float length, int position, int s) {
  glColor3f(1.0f,0.0f,0.8f);
  glPushMatrix();
  
  glRotatef(position, 0.0, 0.0, 1.0);
  float shift = length + gap;
  glTranslatef(0, shift, 0);
 
  //Боковые Грани 
  glBegin(GL_TRIANGLE_FAN);     	
      glVertex3f(0.0, -length, 0.0);
      glVertex3f(-a, -a, a);
      glVertex3f( a, -a, a);
      glVertex3f(a, -a, -a);
      glVertex3f(-a, -a, -a);
      glVertex3f(-a, -a, a);
   glEnd();
   
   //Основание
   glBegin(GL_QUADS);
      glVertex3f(-a, -a, a);
      glVertex3f(-a, -a, -a);
      glVertex3f(a, -a, -a);
      glVertex3f(a, -a, a);
   glEnd();
   
   //Сфера на основании
   if(s==1){
   glTranslatef(0, Dodge, 0);
   glTranslatef(0, sphereDist, 0);
   glColor3f(0,0,0.8f);
   glutSolidSphere(a*1.12, 10, 10);
}
   glPopMatrix();
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glLoadIdentity();
  AspectView();
  
  PyraMydus(quad_a, rebro, 0, 1);
  PyraMydus(quad_a, rebro, 90, 1);
  PyraMydus(quad_a, rebro, 180, 1);
  PyraMydus(quad_a, rebro, 270, 1);
  
  glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
 if (key == 'p') {
     Push = 0;
 }
 
 if (key == 's') {
	 Push = 1;
   
 }
 
 if (key == '+') {
    Sx*= Scal;
    Sy*=Scal;
    Sz*=Scal;
    
 }
 
 if (key == '-') {
    Sx/= Scal;
    Sy/=Scal;
    Sz/=Scal;
   
 }
 
}

void keyboardArrows(int key, int x, int y){
  if( key == GLUT_KEY_UP ){
	vX+=  dAngl;
    glutPostRedisplay(); 
  }
  
  if( key == GLUT_KEY_DOWN ){
	vX-=  dAngl;  
    glutPostRedisplay();
  }
  
  if( key == GLUT_KEY_RIGHT ){
	vY-=  dAngl;  
    glutPostRedisplay();
  }
  
  if( key == GLUT_KEY_LEFT ){
	vY+=  dAngl;  
    glutPostRedisplay();  
  }
}


void TimerFunc(int value) {
  if(Push){
   //Проверка верхней границы
   if(Dodge < DodgeMax) {
	   if(up){
	   Dodge+= DodgeStepUp;
     }
     else {
	   Dodge+= DodgeStepDown;
	 }
   }
   
   if(Dodge > DodgeMax) {
	   up=0;
	   Dodge+= DodgeStepDown;   
   }
   
   //Проверка нижней границы
	 if(Dodge < DodgeMin) {
	   up=1;
   }
 }
  glutTimerFunc(MILL_SEC, TimerFunc, 0);
  glutPostRedisplay();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(Width, Height);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("LABA_3");
  glutDisplayFunc(display);  
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(keyboardArrows);
  glutTimerFunc(MILL_SEC, TimerFunc, 0);
  initScene();
  glutMainLoop();
  return 0;             
}
