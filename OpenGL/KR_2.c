#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#define FPS 50
const float Width = 1024, Height = 600, zAxis = 1024;
float Visio = 60.0;
float zPos =  -100.0;
float Sx= 1.0;
float Sy= 1.0;
float Sz= 1.0;
float RotY = 0.0, RotX = 0.0;
float RotDiff = 3.0;
float phi = 0.0;
float s_phi = 0.0;

const float Scal = 1.025;
const float CENTR = 1.0;
const float sprSize = 6.0;
const float lampSize = 3.0;
const float d_phi = 0.03;
const float d_sphi = 0.05;
const float rcone = 6.0;
const float hcone = 20.0;
int ZAT = 0;

//Для Света
struct Lamp{
  float lightX;
  float lightY;
  float lightZ;
  float lDx;
  float lDy;
  float lDz;
  float diffR;
  float diffG;
  float diffB;
  int cutAn;
  
} Lamp1, Lamp2;


void AspectView() {	
  glTranslatef(0, -10.0, zPos);
  glRotatef(RotX, 1.0, 0.0, 0.0);
  glRotatef(RotY, 0.0, 1.0, 0.0);
  glScalef(Sx, Sy, Sz);
  glRotatef(40, 1.0, 0.0, 0.0);
  glRotatef(65, 0.0, 1.0, 0.0);
  
}

void Reshape(GLint w, GLint h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  float Aspect = Width/Height;
  gluPerspective(Visio, Aspect, 1.0f, 1000.0f);
}

void Fuko(float n, float m, float r) {
	float K= 300.0;
	float r1;
	float rCur;
	
	if(ZAT ==1){
	  r1= K/(phi+0.001);
      
	} else{
	  r1= r;
	  
	}
	
	rCur = r1*cos(n*phi)*sin(m*phi);
    
    float z = rCur*cos(phi);
    float x = rCur*sin(phi);
    float y = 0;

    //y = r*sin(phi);
     
     //Поверхность
    //glShadeModel(GL_SMOOTH);
    float size = r/2;
    glPushMatrix();
    glScalef(4.0,1.0,3.0);
    glBegin(GL_QUADS);
     glNormal3f(0.0, 1.0, 0);
     
      glColor4f(0.3, 1.0, 0, 1.0);
     glVertex3f( -size / 2, -size / 2, -size / 2);
      glColor4f(1.0, 0, 0, 0.8);
     glVertex3f( -size / 2, -size / 2,  size / 2);
      glColor4f(0.5, 0.3, 0.1, 0.5);
     glVertex3f(  size / 2, -size / 2,  size / 2);
      glColor4f(0, 1.0, 1.0, 0.5);
     glVertex3f(  size / 2, -size / 2, -size / 2);
    glEnd();
    glPopMatrix();
   
     //Нить
    glColor3f(0, 1.0, 0);
    glBegin(GL_LINES);
      glVertex3f(0.0, 100.0,0);
      glVertex3f(x,sprSize+y,z);
    glEnd();
    
    glPushMatrix();
    
    glTranslatef(x,sprSize+y,z);
    
    /*
    //След
    glPushMatrix();
    glTranslatef(0, -20.0, 0);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);
      glVertex3f(0.0, 0.0, 0.0);
    glEnd();
    glPopMatrix();
    */
    
    glColor3f(0, 1.0, 0);
    //Сфера	
    glutSolidSphere(sprSize, 30, 30);
    
    //Конус
    glRotatef(90, 1.0, 0, 0);
    glTranslatef(0,0,-1.0);
    glutSolidCone(rcone, hcone, 30, 30);
    
    glPopMatrix();
}

void DrawAsix() {
  glDisable(GL_LIGHTING);
  //Рисуем Оси
  //OX - синяя + от нас
  glColor3f(0, 0, 1.0);
  glBegin(GL_LINES);
  glVertex3f(0, 0, 0);
  glVertex3f(-Width,0, 0);
  glEnd();
  
  //OY - зеленая вверх
  glColor3f(0, 1.0, 0); 
  glBegin(GL_LINES);
  glVertex3f(0, 0 ,0);
  glVertex3f(0,Height,0);
  glEnd();
  
  //OZ - красная в право
  glColor3f(1.0, 0, 0); 
  glBegin(GL_LINES);
  glVertex3f(0, 0 ,0);
  glVertex3f(0,0,zAxis);
  glEnd();
  glEnable(GL_LIGHTING);

}

// Освещение От источников
void setLamp(int num, float lx, float ly, float lz, float dx, float dy, float dz, float diffR, float diffG, float diffB, int cAn) { 
  float light_pos[] = {lx, ly, lz, 1.0};	
  float light_dir[] = {dx,dy,dz};
  float light_diffuse[] = {diffR, diffG, diffB, 1.0}; 
  
  if(num == 1) {
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_dir);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, cAn);
    
    glEnable(GL_LIGHT1);
	
	glPushMatrix();
    glTranslatef(lx, ly, lz);
    glutSolidSphere(lampSize, 15, 15);
    
    
    //Рисуем вектор-направление света
    glDisable(GL_LIGHTING);
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINES);
      glVertex3f(0,0,0);
       glVertex3f(dx*5.0f, dy*5.0f, dz*5.0f);
    glEnd();
    glEnable(GL_LIGHTING);
    
    
  glPopMatrix();
  }
  
  if(num == 2) {
    
  float r = sqrt(lx*lx + ly*ly +lz*lz);
  float z = r*cos(s_phi)*1.25;
  float x = r*sin(s_phi)*0.9;
  float Nlight_pos[] = {x, ly, z, 1.0};
  
  glPushMatrix();
    glTranslatef(x, ly, z);
    glColor3f(1.0,1.0,1.0);
    glutSolidSphere(lampSize, 15, 15);
    
    //Рисуем вектор-направление света
    glDisable(GL_LIGHTING);
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINES);
      glVertex3f(0,0,0);
       glVertex3f(-x, -ly, -z);
    glEnd();
    glEnable(GL_LIGHTING);
    
  float Nlight_dir[] = {-x, -ly, -z};
  glPopMatrix();
    
    
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT2, GL_POSITION, Nlight_pos);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, Nlight_dir);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, cAn);
   
    glEnable(GL_LIGHT2);
  }
  
  
}

void initScene(void) {
  //Настройка освещения
  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  
  //Установка Ambient
  float ambient[4] = {0.5, 0.5, 0.5, 1.0};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
  
  //Инициализация ламп
  Lamp1.lightX= 0;
  Lamp1.lightY= 8.0;
  Lamp1.lightZ= 20.0;
  Lamp1.lDx= 0;
  Lamp1.lDy= -0.5;
  Lamp1.lDz= -1.0;
  Lamp1.diffR= 0.3;
  Lamp1.diffG= 0.3;
  Lamp1.diffB= 0.8;
  Lamp1.cutAn= 30;
  
  Lamp2.lightX= -25.0;
  Lamp2.lightY= 15.0;
  Lamp2.lightZ= 0;
  Lamp2.lDx= 1.0;
  Lamp2.lDy= -0.5;
  Lamp2.lDz= 0;
  Lamp2.diffR= 0.8;
  Lamp2.diffG= 0.5;
  Lamp2.diffB= 0.5;
  Lamp2.cutAn= 45;
  
  // Фоновое освещение
  
  
  //Настройка Сцены
  Sx =0.5;
  Sy =0.5;
  Sz =0.5;
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  float Aspect = Width/Height;
  gluPerspective(Visio, Aspect, 1.0f, 1000.0f);
  glMatrixMode(GL_MODELVIEW);
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glLoadIdentity();
  
  //Устанавливаем начало координат
  AspectView();
  glColor3f(1.0, 0.8, 0.9);
  
  DrawAsix();
  Fuko(3.0, 3.0, 85.0);
  
  
  //Установка Источников света
 
  setLamp(1, Lamp1.lightX, Lamp1.lightY, Lamp1.lightZ, Lamp1.lDx, Lamp1.lDy, Lamp1.lDz, Lamp1.diffR, Lamp1.diffG, Lamp1.diffB, Lamp1.cutAn);
  setLamp(2, Lamp2.lightX, Lamp2.lightY, Lamp2.lightZ, Lamp2.lDx, Lamp2.lDy, Lamp2.lDz, Lamp2.diffR, Lamp2.diffG, Lamp2.diffB, Lamp2.cutAn);

  
  glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){		
	
 if (key == 'z') {
	 if(ZAT == 1) {
		 ZAT--;
	  }
	  
	 else {
     ZAT++;
	  }
	 
     glutPostRedisplay();
 }		
  
 if (key == 'w') {
    RotX += RotDiff;
    glutPostRedisplay();
    
 }	
 
 if (key == 's') {
    RotX -= RotDiff;
    glutPostRedisplay();
    
 }
 
 if (key == 'a') {
    RotY += RotDiff;
    glutPostRedisplay();
    
 }
 
 if (key == 'd') {
    RotY -= RotDiff;
    glutPostRedisplay();
    
 }
	
}

void keyboardArrows(int key, int x, int y){
  switch(key) {
	case GLUT_KEY_UP:
    Sx*= Scal;
    Sy*=Scal;
    Sz*=Scal;
    glutPostRedisplay();
    break;  
	  
    case GLUT_KEY_DOWN:
    Sx/= Scal;
    Sy/=Scal;
    Sz/=Scal;
    glutPostRedisplay();  
    break;
      
    case GLUT_KEY_LEFT:
      
    break;
      
    case GLUT_KEY_RIGHT:
      
    break;
    
  }
}

void moving(int value)
{
  phi+= d_phi;
  s_phi+= d_sphi;
  glutPostRedisplay();
  glutTimerFunc(FPS, moving, 0);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(Width, Height);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("KONTROLNAYA_2");
  glutDisplayFunc(display);
  glutReshapeFunc(Reshape);  
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(keyboardArrows);
  glutTimerFunc(FPS, moving, 0);
  initScene();
  glutMainLoop();
  return 0;             
}

