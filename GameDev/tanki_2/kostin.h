// Процедура линейных преобразований координат
void Kostin(float &x0, float &y0, int direct)
{
    float mv=1.75;
    switch(direct)
    {
        case 1: //Вверх влево
        x0-=mv;
        y0+=mv;
        break;

        case 2: //Вверх вправо
        x0+=mv;
        y0+=mv;
        break;

        case 3: //Влево
        x0-=mv;
        break;


        case 4: //Вправо
        x0+=mv;
        break;

        case 5: //Вниз влево
        x0-=mv;
        y0-=mv;
        break;

        case 6: //Вниз вправо
        x0+=mv;
        y0-=mv;
        break;

        case 7: //Вверх
        y0+=mv;
        break;

        case 8: //Вниз
        y0-=mv;
        break;
    }
}
