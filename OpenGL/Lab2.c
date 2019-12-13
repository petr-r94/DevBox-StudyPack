#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#define ESCAPE '\033'
#define ROTATE 10
#define OX 3
#define OY 2
GLint Width = 1200, Height = 800;
GLint Bound_u = -256;
GLint Bound_a = 256;
int bu = -200;
int ba = 200;
double nextCoord = 10.0;
double rotZ;
double a= 10.0, b= 10.0, c=10.0;


//Верхняя часть Гиперболоида
double Hyper(double x, double y)
{
  double result = (c*sqrt((pow(x, 2) / pow(a, 2) + pow(y, 2) / pow(b, 2) - 1))) * 5;
  //double result = c*sqrt((1 - pow(x, 2) / pow(a, 2) - pow(y, 2) / pow(b, 2))) * 5;
  return result;
}

//Нижняя часть гиперболоида
double HyperNeg(double x, double y)
{
  double result = (-c*sqrt((pow(x, 2) / pow(a, 2) + pow(y, 2) / pow(b, 2) - 1))) *5;
  return result;
}

//Маленькие составные полигоны
void Quadro(double x, double y) {
  glBegin(GL_POLYGON);
  glVertex3f(x, y, Hyper(x, y));
  glVertex3f(x + nextCoord, y, Hyper(x + nextCoord, y));
  glVertex3f(x + nextCoord, y + nextCoord, Hyper(x + nextCoord, y + nextCoord));
  glVertex3f(x, y + nextCoord, Hyper(x, y + nextCoord));
  
  glEnd();
}

void QuadroNeg(double x, double y) {
  glBegin(GL_POLYGON);
  glVertex3f(x, y, HyperNeg(x, y));
  glVertex3f(x + nextCoord, y, HyperNeg(x + nextCoord, y));
  glVertex3f(x + nextCoord, y + nextCoord, HyperNeg(x + nextCoord, y + nextCoord));
  glVertex3f(x, y + nextCoord, HyperNeg(x, y + nextCoord));
  glEnd();
}

void Display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, Width, 0, Height, Bound_u*2, Bound_a*2);
  
  //Пунктирный контур
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glMatrixMode(GL_MODELVIEW);
  glColor3ub(0, 255, 0);
      
  int x, y;
  for(x = bu; x < ba; x += nextCoord) {
    for(y = bu; y < ba; y += nextCoord) {
      glLoadIdentity();
      
      //Вид с Боку
      
      // Вращение: Третий по Оси OX и второй по оси OY четырехугольник, образующий поверхность
      glTranslated(Width / 2, Height / 2, 0);
      glTranslated(-OX * nextCoord, -OY * nextCoord, -Hyper(OX * nextCoord, OY * nextCoord));
      glRotated(rotZ, 0, 0, 1);
      glTranslated(OX * nextCoord, OY * nextCoord, Hyper(OX * nextCoord, OY * nextCoord));
      glTranslated(-Width / 2, -Height / 2, 0);
     

      glTranslated(Width / 2, Height / 2, 0);
	  //glRotated(90, 1, 0, 0);
	       
      Quadro(x, y);
      QuadroNeg(x, y);
      
    }
  }
  
  glutSwapBuffers();
}

void Reshape(GLint w, GLint h) {
    Width = w;
    Height = h;

    /* устанавливаем размеры области отображения */
    glViewport(0, 0, w, h);

    /* ортографическая проекция */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Keyboard(unsigned char key, int x, int y) {

  if( key == ESCAPE ){
    exit(0);
  }
  if( key == 'r' ){
    rotZ += ROTATE;
    glutPostRedisplay();
  }
  if( key == 'l' ){
    rotZ -= ROTATE;
    glutPostRedisplay();
  }
}

int main(int argc, char **argv) {
  rotZ = 0;
  if(argc == 4) {
  a = atoi(argv[1]);
  b = atoi(argv[2]);
  c = atoi(argv[3]);
  }
  else {
	 printf("\nInput Error! Using Default a b c\n");
  }
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(Width, Height);
  glutCreateWindow("One_Line_Hyperboloid");
  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);
  glutReshapeFunc(Reshape);
  glDisable(GL_CULL_FACE);
  glutMainLoop();
  return 0;
}




//glTranslated(bu + 3 * nextCoord, bu + 2 * nextCoord, Hyper(bu + 3 * nextCoord, bu + 2 * nextCoord));
//glRotated(rotZ, 0, 0, 1);
//glTranslated(ba - 3 * nextCoord, ba - 2 * nextCoord, -Hyper(ba + 3 * nextCoord, ba + 2 * nextCoord));
