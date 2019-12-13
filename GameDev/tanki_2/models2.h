class Tank{
public:
	
	const double lgth=50;
	const double wdth=35;
	double centre_x;
	double centre_y;
	int azimut;
	float left, right, bottom, top;
	
	
	Tank(double x, y){
	centre_x=x;
	centre_y=y;
	left= x-lgth; right= x+lgth; bottom= y-wdth; top= y+wdth;
	}
	
	
	void go(){
		centre_x+=sin(azimut);
		centre_y+=cos(azimut);
	}
	
	void turntorght(){
		azimut++;
	}
	
	void turntolft(){
		azimut--;
	}
	
	
}


class Bullet{
public:
	
	double bul_x, bul_y;
	int azimut;
	const int vlct=5;
	
	Bullet(Tank my_T){
		bul_x=my_T+35*sin(azimut);
		bul_y=my_T+35*cos(azimut);
	}
	
	void fly(double str_time){
		while(bul_x<1280 && bul_y<900){
			bul_x+=vtlocity*difftime(str_time,clock())/CLOCKS_PER_SEC;
			bul_y+=vtlocity*difftime(str_time,clock())/CLOCKS_PER_SEC;
		}
	}
	
}




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