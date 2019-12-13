#define N 15 // ���������� ���� �� �����
#define E 3  //���������� �����
#define BDYSH 30
#include <ctime>
#include <time.h>
#include <math.h>
#include <iostream>
#include <GL/glfw.h> //���������� ������������ ����� ����������� ���������� GLFW
#include <GL/glut.h> //���������� ������������ ����� ����������� ���������� freeglut
#include "models.h"  //���������� ������������ ���� � �������� ��������

//#include <models2.h>

#include "kostin.h"  //���������� ������������ ���� � ����������� �������� �������������� ���������
#include "interface.h"
using namespace std;
GLint Width = 1280, Height = 900; //������������� ��������� ���������� ������
float angle=1.1;   // ����������, ���������� �� ���� �������� ����� �� ������� � ������ ������� �������
float Angle=100.0*M_PI/180; // ��� �������
float move=7.0f;                // ����������, ���������� �� ����� ��� ������� ������(� ��������)

//Bullet* bul=new Bullet(bot->left+35, bot->top+35); // ������ ������ ������ "Bullet";
Tank* bot =new Tank(500,500);
Bullet* bul =new Bullet(*bot);
float xb1,xb2,xb3,xb4,yb1,yb2,yb3,yb4; //���������� ��� �����
int a,b=0;
Wall* stena[N]; // ������ ������ ���������� �� �����
Tank* enemy[E]; // ������ ������ ���������� �� �����
void Shoot() //������� ��������� ����
{
    if ((bul->bul_y)>glutGet(GLUT_WINDOW_HEIGHT))
    {
    bul->bul_y = bot->top+35;
    bul->bul_x = bot->left+35;
    }
    glColor3ub(195,195,0);
    Gametimer(10);
    glBegin(GL_LINES);
    {
    glVertex2f(bul->bul_x,bul->bul_y+85);
    glVertex2f(bul->bul_x,bul->bul_y+90);
    }

    glEnd();
}
void Wall_Generator() // ��������� ��������� ��� ����
    {
    srand( time(0) );
    for(int i=0; i<N/2; i++)
    {
        stena[i] = new Wall(rand()%(Width-140), rand()%(Height-140),25,75); //���������� ������
    }
    for(int i=N/2; i<N; i++)
    {
        stena[i] = new Wall(rand()%(Width-140), rand()%(Height-140),75,25); //���������� ������
    }

}
void Enemy_Spawn()
{
    for(int i=0, pos=100; i<E; i++, pos+=100)
    {
        enemy[i]= new Tank(pos + rand() % 50, pos + rand() % 50); //���������� �����
    }
}
void CWall() //������� ��������� ����
{
    glPushMatrix();
    glLoadIdentity();
    glColor3ub(145,145,60);
    for(int i=0; i<N; i++)
    {
    glBegin(GL_POLYGON);
    {
        glVertex2f(stena[i]->x1,stena[i]->y1);
        glVertex2f(stena[i]->x1,stena[i]->bottom);
        glVertex2f(stena[i]->right,stena[i]->bottom);
        glVertex2f(stena[i]->right,stena[i]->y1);

    }
    glEnd();
    }
    glPopMatrix();
}
void Enemy()
{
    glPushMatrix();
    glLoadIdentity();
    for(int i=0; i<E; i++)
    {
        xb1=(enemy[i]->left+10);
        xb2=(enemy[i]->left+30);
        xb3=(enemy[i]->right-30);
        xb4=(enemy[i]->right-10);

        yb1=(enemy[i]->bottom+30);
        yb2=(enemy[i]->top+40);
        yb3=(enemy[i]->top+40);
        yb4=(enemy[i]->bottom+30);

    glBegin(GL_POLYGON); // ���� Begin-End, ���������� �� ��������� ����� (� ����� ������ ��������)
    //������ ����
        {
        glColor3ub(195,1,1); //���� ����� ����� � ���� �������� RGB
        glVertex2f(xb1,yb1); //����� ������ �����
        glVertex2f(xb2,yb2);   //����� ������� �����
        glVertex2f(xb3,yb3);  //������ ������� �����
        glVertex2f(xb4,yb4); // ������ ������ �����
        }
    glBegin(GL_POLYGON);          // ���� ���� Begin-End,���������� �� ��������� ��������������(� ����� ������ 4 -� ��������)
        {
        glColor3ub(265,265,0); //���� ������� ����� � ���� �������� RGB
        glVertex2f(enemy[i]->left,enemy[i]->bottom); //����� ������ �����
        glVertex2f(enemy[i]->left,enemy[i]->top);    //����� ������� �����
        glVertex2f(enemy[i]->right,enemy[i]->top);   //������ ������� �����
        glVertex2f(enemy[i]->right,enemy[i]->bottom);// ������ ������ �����
        }

    glBegin(GL_POLYGON); // ���� Begin-End, ���������� �� ��������� ����� (� ����� ������ ��������)
    //������ ����
        {
        glColor3ub(265,265,2); //���� ����� ����� � ���� �������� RGB
        glVertex2f(xb1,yb1); //����� ������ �����
        glVertex2f(xb2,yb2);   //����� ������� �����
        glVertex2f(xb3,yb3);  //������ ������� �����
        glVertex2f(xb4,yb4); // ������ ������ �����
        }


    glEnd();
    glFinish(); //����� �����������
    }
    glPopMatrix();
}
void CTank()
{
    glPushMatrix();
        xb1=(bot->left+10);
        xb2=(bot->left+30);
        xb3=(bot->right-30);
        xb4=(bot->right-10);

        yb1=(bot->bottom+30);
        yb2=(bot->top+40);
        yb3=(bot->top+40);
        yb4=(bot->bottom+30);
    Gametimer(10);
    glBegin(GL_POLYGON); // ���� Begin-End, ���������� �� ��������� ����� (� ����� ������ ��������)
    //������ ����
        {
        glColor3ub(195,1,1); //���� ����� ����� � ���� �������� RGB
        glVertex2f(xb1,yb1); //����� ������ �����
        glVertex2f(xb2,yb2);   //����� ������� �����
        glVertex2f(xb3,yb3);  //������ ������� �����
        glVertex2f(xb4,yb4); // ������ ������ �����
        }
    glBegin(GL_POLYGON);          // ���� ���� Begin-End,���������� �� ��������� ��������������(� ����� ������ 4 -� ��������)
        {
        glColor3ub(195,195,0); //���� ������� ����� � ���� �������� RGB
        glVertex2f(bot->left,bot->bottom); //����� ������ �����
        glVertex2f(bot->left,bot->top);    //����� ������� �����
        glVertex2f(bot->right,bot->top);   //������ ������� �����
        glVertex2f(bot->right,bot->bottom);// ������ ������ �����
        }

glBegin(GL_POLYGON); // ���� Begin-End, ���������� �� ��������� ����� (� ����� ������ ��������)
    //������ ����
        {
        glColor3ub(165,165,0); //���� ����� ����� � ���� �������� RGB
        glVertex2f(xb1,yb1); //����� ������ �����
        glVertex2f(xb2,yb2);   //����� ������� �����
        glVertex2f(xb3,yb3);  //������ ������� �����
        glVertex2f(xb4,yb4); // ������ ������ �����
        }
    glEnd();
    glFinish(); //����� �����������
    glPopMatrix();
}
void Render(void) // ������� ������� ��������� ������� �����
{
    if (start)
    {
        glClear(GL_COLOR_BUFFER_BIT); // ������� ����
        CWall(); //������ �����
        Shoot(); //������ ����
        CTank(); //������ ����
        Enemy(); //������ �����
    }
}
void Reshape(GLint w, GLint h) //�������, ������������ ��� �������� �������� ����.
//�.� �������������� �� ������ �� ������ ���������� ������
{
    Width = w;
    Height = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void Actions(unsigned char key, int x, int y)
{
    if (key== GLFW_KEY_SPACE)
    {
        for(int i=0; i<BDYSH; i++)
        {
    bul->bul_y += bul->vlct;
    Render();
        }
        delete bul;                  // ������������ ���� ����� � ������ �����
        Bullet* bul =new Bullet(*bot);
        Render();

    }
}
void SpecialInput(int key, int x, int y)
{
    switch(key)  //����� ����������
    {
        case 27:
    exit(0); // ����� �� ���������� �� ������� ������� ESC
    break;
    case GLUT_KEY_RIGHT:
        glTranslatef((bot->left)+bot->lgth, (bot->bottom)+bot->wdth, 0);
        glRotatef(-angle,0.0,0.0,1.0);
        glTranslatef(((bot->left)+bot->lgth)*(-1), ((bot->bottom)+bot->wdth)*(-1), 0);
        bot->turntorght();
        cout<<bot->azimut<<endl;
        break;


    case GLUT_KEY_LEFT:
        glTranslatef((bot->left)+bot->lgth, (bot->bottom)+bot->wdth, 0);
        glRotatef(angle,0.0,0.0,1.0);
        glTranslatef(((bot->left)+bot->lgth)*(-1), ((bot->bottom)+bot->wdth)*(-1), 0);
        bot->turntolft();
        cout<<bot->azimut<<endl;
        break;


    case GLUT_KEY_UP: //�����
        //Kostin(bot->left,bot->bottom,7);
        //Kostin(bot->left,bot->top,7);
        //Kostin(bot->right,bot->top,7);
        //Kostin(bot->right,bot->bottom,7);
        bot->go_frwd();
        bul->bul_y+=1.0;
        cout<<bot->centre_x<<" "<<bot->centre_y<<endl;
        break;

    case GLUT_KEY_DOWN: //����
        //Kostin(bot->left,bot->bottom,8);
        //Kostin(bot->left,bot->top,8);
        //Kostin(bot->right,bot->top,8);
        //Kostin(bot->right,bot->bottom,8);
        bot->go_back();
        bul->bul_y-=1.0;
        cout<<bot->centre_x<<" "<<bot->centre_y<<endl;

        break;
    }
    glutPostRedisplay();
}
int main(int argc, char *argv[])
{
    Wall_Generator();
    Enemy_Spawn();
    glutInit(&argc, argv); //������������� ����������� ����������
    glfwInit();
    glutInitDisplayMode(GLUT_RGB);  //����� �������
    glutInitWindowSize(Width, Height); // ������� ����
    glClearColor(0.1, 0.1, 0.1, 0); //����� ���� �������� ����
    glutCreateWindow("TANKS: Press Right Click to Open Game Menu");  //����
    glutReshapeFunc(Reshape);   //��������� ��������� �������� ����
    createMenu();
    glutDisplayFunc(Render);    //������� ������� ���������
    Render();
    glutSpecialFunc(SpecialInput); //�������� ����� ����������
    glutKeyboardFunc(Actions); //�������� ����� ����������
    glutMainLoop();
    delete bot; //������� ����
    delete bul; //������� ����
    for(int i=0; i<N; i++) // ������� �����
    {
        delete stena[i];
    }
    for(int i=0; i<E; i++) // ������� �����
    {
        delete enemy[i];
    }
    glfwTerminate();
    return 0;
}

