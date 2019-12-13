void Gametimer(int ms) {
    int CLOCKS_PER_MSEC = CLOCKS_PER_SEC / 1000;   // новая константа
    clock_t end_time = clock() + ms * CLOCKS_PER_MSEC ;  // время завершения
    while (clock() < end_time) {}  // цикл ожидания времени
}
class Tank{
public:

	const double lgth=35;
	const double wdth=50;
	double centre_x;	//координаты центра танка
	double centre_y;
	int azimut;			//угол от направления наверх, куда смотрит дуло
	float left, right, bottom, top;			//опять же таки дубль


	Tank(double x, double y){			//конструктор
	azimut=0;
	centre_x=x;
	centre_y=y;
	left= x-lgth; right= x+lgth; bottom= y-wdth; top= y+wdth;
	}


	void go_frwd(){						//идти вперед
	    azimut=0;
		centre_x+=sin(azimut*M_PI/180);
		centre_y+=cos(azimut*M_PI/180);
		left= centre_x-lgth; right= centre_x+lgth;		//переприсвоение для отрисовки, как я понимаю
		bottom= centre_y-wdth; top= centre_y+wdth;
	}

	void go_back(){						//аналогично назад
	    azimut=0;
		centre_x-=sin(azimut);
		centre_y-=cos(azimut);
		left= centre_x-lgth; right= centre_x+lgth; bottom= centre_y-wdth; top= centre_y+wdth;
	}


	void turntorght(){			//поворот направо, на 1 градус
		//azimut++;
	}

	void turntolft(){			//аналогично налево
		//azimut--;
	}


};


class Bullet{
public:

	double bul_x, bul_y;
	int azimut;
	const int vlct=5;			//скорость полета пули при выстреле

	Bullet(Tank my_T){			//конструктор, на вход получает танк, которому принадлежит
	azimut=my_T.azimut;
		bul_x=my_T.centre_x; //+50*sin(azimut);
		bul_y=my_T.centre_y; //+90*cos(azimut);
	}

	void fly(double str_time){				//полет пулиGLUT_KEY_UP, на вход начальное время
		while(bul_x<1280 && bul_y<900){
			bul_x+=vlct*difftime(str_time,clock())/CLOCKS_PER_SEC;
			bul_y+=vlct*difftime(str_time,clock())/CLOCKS_PER_SEC;
		}
	}

};




class Wall
{

	public:
	float x1,y1;
	float x, y;
	float left, right, bottom, top; //x1,y1 - коордианаты верхнего левого угла, length - ширина, height - высота. При создании объекта конструктор принимает на вход координаты, высота, ширину. Создаётся стена с координатами верхнего левого угла в этой точке, заданной шириной и высотой.
	Wall(float in_x, float in_y, float length, float heigth): x1(in_x),y1(in_y), right(in_x+length), bottom(in_y+heigth), top(in_y)
{

}

};
