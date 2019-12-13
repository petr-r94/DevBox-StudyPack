#include <GL/glut.h> //Подключаем заголовочный файлы графической библиотеки freeglut
    static int window;
    static int menu_id;
    bool start=false; //Логическая переменная отвечающая за пуск игры
void menu(int num)
{
  if(num == 0)  //Если нажали Quit
  {
    glutDestroyWindow(window);
    exit(0);
  }
  if(num == 1)  //Есди нажали Play Game
  {
    start=true;
    //glutRemoveMenuItem(1); // Удаляем элемент Play Game
    glutPostRedisplay();
  }
}

void createMenu(void) //Создаём меню
{
    glClearColor(0.1, 0.1, 0.1, 0); //Задаём цвет очистики фона
    glClear(GL_COLOR_BUFFER_BIT); // Очистка фона
    menu_id = glutCreateMenu(menu);
    glutAddMenuEntry(" Play Game ", 1);
    glutAddMenuEntry("     Quit      ", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
