#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#define FPS 50
#define SHN 30

//Для подсветки
const float emR=0.25;
const float emG=0.30;
const float emB=0.25;

const float Width = 1024, Height = 600, zAxis = 1024;
float Visio = 60.0;
float zPos =  -50.0;
float Sx= 1.0;
float Sy= 1.0;
float Sz= 1.0;
float RotY = 0.0, RotX = 0.0;
float RotDiff = 3.0;
float s_phi = 0.0;
float diff = 0.174533;


float em[4];
float noem[4] = {0.0, 0.0, 0.0, 1.0};
float lem[4] = {0, 1.0, 1.0, 1.0};

//Для Граней параллепипеда
float csize = 20.0;
float cw = 1.0;
float ch = 1.0;
float cz = 1.3;

float phi = 0.0;

const float Scal = 1.025;
const float CENTR = 1.0;
const float sprSize = 3.0;
const float lampSize = 1.0;
const float d_phi = 0.05;

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

void MovSphere() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, em);
	 
	float r = csize/2;
    float z = r*cos(phi)*1.25;
    float x = r*sin(phi)*0.9;
    
    glPushMatrix();
    glTranslatef(x,sprSize,z);
    glColor3f(Lamp1.diffR, Lamp1.diffG, Lamp1.diffB);	
    glutSolidSphere(sprSize, 30, 30);
    glPopMatrix();
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, noem);
    
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
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, lem);
  float light_pos[] = {lx, ly, lz, 1.0};	
  float light_diffuse[] = {diffR, diffG, diffB, 1.0}; 
  
  if(num == 1) {
  //Красная компоненты отраженного света
  float spec_one[] = {1.0, 0, 0, 1.0};
  glLightfv(GL_LIGHT1, GL_SPECULAR, spec_one);
  
  //Рисуем источник света
  glPushMatrix();
    glTranslatef(lx, ly, lz);
    glutSolidSphere(lampSize, 15, 15);
    
    
    //Рисуем вектор-направление света
    glDisable(GL_LIGHTING);
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINES);
      glVertex3f(0,0,0);
       glVertex3f(-lx+dx, -ly+dy, -lz+dz);
    glEnd();
    glEnable(GL_LIGHTING);
   
  glPopMatrix();
  
  float Slight_dir[] = {-lx+dx,-ly+dy,-lz+dz}; 
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Slight_dir);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, cAn);
    
    glEnable(GL_LIGHT1);
  }
  
  if(num == 2) { 
  float r = sqrt(pow(lx,2) + pow(ly,2) + pow(lz,2));
  float z = r*cos(s_phi);
  float x = r*sin(s_phi);
  float Nlight_pos[] = {x, ly, z, 1.0};
  
  glPushMatrix();
    glTranslatef(x, ly, z);
    glColor3f(1.0,1.0,1.0);
    glutSolidSphere(lampSize, 15, 15);
    
    //Рисуем вектор-направление вращения
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(0,1.0,0);
      glVertex3f(0,0,0);
      glVertex3f(-x, -ly, -z);
    glEnd();
    
    //Рисуем вектор-направление света
    glBegin(GL_LINES);
    glColor3f(1.0,1.0,1.0);
      glVertex3f(0,0,0);
       glVertex3f(-x+dx, -ly+dy, -z+dz);
    glEnd();
    glEnable(GL_LIGHTING);
    
  
  glPopMatrix();
    
    float Nlight_dir[] = {-x+dx, -ly+dy, -z+dz};
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT2, GL_POSITION, Nlight_pos);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, Nlight_dir);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, cAn);
   
    glEnable(GL_LIGHT2);
  }
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, noem);
}

void initScene(void) {
  //Настройка позиции второго источника
  s_phi= 23*diff;
  
  //Инициализация эмисионной подсветки
  em[0]=0;
  em[1]=emG;
  em[2]=0;
  em[4]=1.0;
  
  //Инициализация ламп
  //Первая статичная лампа
  Lamp1.lightX= 0.0;
  Lamp1.lightY= 12.0;
  Lamp1.lightZ= 20.0;
  
  Lamp1.lDx= 0.0;
  Lamp1.lDy= 0.0;
  Lamp1.lDz= 15.0;
  
  Lamp1.diffR= 1.0;
  Lamp1.diffG= 0.0;
  Lamp1.diffB= 0.0;
  Lamp1.cutAn= 45;
  
  //Вторая Лампа двужущаяся
  Lamp2.lightX= 0;
  Lamp2.lightY= 12.0;
  Lamp2.lightZ= -20.0;
  
  Lamp2.lDx= 0.0;
  Lamp2.lDy= 0.0;
  Lamp2.lDz= -22.0;
  
  Lamp2.diffR= 0.0;
  Lamp2.diffG= 0.0;
  Lamp2.diffB= 1.0;
  Lamp2.cutAn= 80;
  
  //Установка Фонового освещения
  float ambient[4] = {0.5, 0.5, 0.5, 1.0};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
  
  //Настройка свойств материала
  float Dfuse[] = {0.5,0.3,0.5,1.0};
  float Spec[] = {1.0,0.0,0.0,1.0};
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Dfuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Spec); 
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, SHN);
  
  //glEnable(GL_COLOR_MATERIAL);
  //glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
  
  
  
  //Настройка Сцены
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
  
  //Настройка освещения
  glEnable(GL_LIGHTING);
  
  
  AspectView();
  glColor3f(1.0, 0.8, 0.9);
  
  glPushMatrix();
  glScalef(cw, ch, cz);
  
  glutSolidCube(csize);
  glPopMatrix();
 
  
  //Устанавливаем начало координат
  glTranslatef(0, csize/2 + CENTR, 0);
  DrawAsix();
 
  //Установка Источников света
  setLamp(1, Lamp1.lightX, Lamp1.lightY, Lamp1.lightZ, Lamp1.lDx, Lamp1.lDy, Lamp1.lDz, Lamp1.diffR, Lamp1.diffG, Lamp1.diffB, Lamp1.cutAn);
  setLamp(2, Lamp2.lightX, Lamp2.lightY, Lamp2.lightZ, Lamp2.lDx, Lamp2.lDy, Lamp2.lDz, Lamp2.diffR, Lamp2.diffG, Lamp2.diffB, Lamp2.cutAn);
  
  //Сфера по окружности
  MovSphere();
  
  glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){		
 //Первая лампа
 if (key == '1') {
	 if(Lamp1.diffR == 1.0) {
		 Lamp1.diffR--;
	  }
	  
	 else {
     Lamp1.diffR++;
	  }
     glutPostRedisplay();
 }
   
 if (key == '2') {
	 if(Lamp1.diffG == 1.0) {
		 Lamp1.diffG--;
	  }
	  
	 else {
     Lamp1.diffG++;
	  }
	 
     glutPostRedisplay();
 }	
 
 if (key == '3') {
	 if(Lamp1.diffB == 1.0) {
		 Lamp1.diffB--;
	  }
	  
	 else {
     Lamp1.diffB++;
	  }
	 
     glutPostRedisplay();
 }	
 
 //Вторая лампа
 if (key == '4') {
	 if(Lamp2.diffR == 1.0) {
		 Lamp2.diffR--;
	  }
	  
	 else {
     Lamp2.diffR++;
	  }
     glutPostRedisplay();
 }
   
 if (key == '5') {
	 if(Lamp2.diffG == 1.0) {
		 Lamp2.diffG--;
	  }
	  
	 else {
     Lamp2.diffG++;
	  }
	 
     glutPostRedisplay();
 }	
 
 if (key == '6') {
	 if(Lamp2.diffB == 1.0) {
		 Lamp2.diffB--;
	  }
	  
	 else {
     Lamp2.diffB++;
	  }
	 
     glutPostRedisplay();
 }
 
 if (key == '7') {
	 if(em[0] == emR) {
		 em[0]-=emR;
	  }
	  
	 else {
     em[0]+=emR;
	  }
	 
     glutPostRedisplay();
 }
 
 if (key == '8') {
	 if(em[1] == emG) {
		 em[1]-=emG;
	  }
	  
	 else {
     em[1]+=emG;
	  }
	 
     glutPostRedisplay();
 }	
 
 if (key == '9') {
	 if(em[2] == emB) {
		 em[2]-=emB;
	  }
	  
	 else {
     em[2]+=emB;
	  }
	 
     glutPostRedisplay();
 }															
  
  if (key == 'q') {
    RotX += RotDiff;
    glutPostRedisplay();
    
 }	
 
   if (key == 'e') {
    RotX -= RotDiff;
    glutPostRedisplay();
    
 }
  
 if (key == 'w') {
    s_phi -= diff;
    glutPostRedisplay();
    
 }	
 
 if (key == 's') {
    s_phi += diff;
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
  glutPostRedisplay();
  glutTimerFunc(FPS, moving, 0);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(Width, Height);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("LABA_4");
  glutDisplayFunc(display);
  glutReshapeFunc(Reshape);  
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(keyboardArrows);
  glutTimerFunc(FPS, moving, 0);
  initScene();
  glutMainLoop();
  return 0;             
}





/*
void DrawQ(float size) {
	 glPushMatrix();
	 
	 
	 glBegin(GL_QUADS);
	 
     // левая грань
     glVertex3f( -size / 2, -size / 2, -size / 2);
     glVertex3f( -size / 2,  size / 2, -size / 2);
     glVertex3f( -size / 2,  size / 2,  size / 2);
     glVertex3f( -size / 2, -size / 2,  size / 2);
     glEnd();
     
     glBegin(GL_QUADS);
     // правая грань
     glVertex3f(  size / 2, -size / 2, -size / 2);
     glVertex3f(  size / 2, -size / 2,  size / 2);
     glVertex3f(  size / 2,  size / 2,  size / 2);
     glVertex3f(  size / 2,  size / 2, -size / 2);
     glEnd();
     
     glBegin(GL_QUADS);
     // нижняя грань
     glVertex3f( -size / 2, -size / 2, -size / 2);
     glVertex3f( -size / 2, -size / 2,  size / 2);
     glVertex3f(  size / 2, -size / 2,  size / 2);
     glVertex3f(  size / 2, -size / 2, -size / 2);
     glEnd();
     
     glBegin(GL_QUADS);
     // верхняя грань
     glVertex3f( -size / 2, size / 2, -size / 2);
     glVertex3f( -size / 2, size / 2,  size / 2);
     glVertex3f(  size / 2, size / 2,  size / 2);
     glVertex3f(  size / 2, size / 2, -size / 2);
     glEnd();
     
     glBegin(GL_QUADS);
     // задняя грань
     glVertex3f( -size / 2, -size / 2, -size / 2);
     glVertex3f(  size / 2, -size / 2, -size / 2);
     glVertex3f(  size / 2,  size / 2, -size / 2);
     glVertex3f( -size / 2,  size / 2, -size / 2);
     glEnd();
     
     glBegin(GL_QUADS);
     glNormal3f(0.0, 0.0, -1.0);
     // передняя грань
     glVertex3f( -size / 2, -size / 2,  size / 2);
     glVertex3f(  size / 2, -size / 2,  size / 2);
     glVertex3f(  size / 2,  size / 2,  size / 2);
     glVertex3f( -size / 2,  size / 2,  size / 2);
     glEnd();
     glPopMatrix();
}
*/
