#define N 10
#define START 55 //��������� �������� ��������� ������
#define FINISH 5 //��������� �������� �������� ������
#define FREE 50 //��������� �������� ��������� ������
#define FULL (FREE+1) //��������� �������� ������� ������
#include<iostream>
#include<fstream>
using namespace std;
       int main()
{
        int field[N][N];
        int way[N][N];
        ifstream file("map.txt");
// ������ �������� ����
		for(int i=0; i<N; i++)
			way[i][0]=field[i][0]=FULL;
		for(int j=0; j<N; j++)
			way[0][j]=field[0][j]=FULL;
//��������� ������� ���������
        for(int i=1; i<N-1; i++)
        for(int j=1; j<N-1; j++)
        {
            file >> field[i][j];
            way[i][j]=field[i][j];
        }
        file.close();       
        int kol=FINISH; // ��������� �������
        int maxkol=68;  // ������������ �������� �������� = (N-2)*(N-2) + FINISH -1
 while(kol <= maxkol)
{
 for(int i=1;i<N-1;i++) // C�������� �������� ������� ������� � �����
 {
  for(int j=1;j<N-1;j++)
    {
        if(way[i][j]==kol) // ������ ������� �������� ������ ��� ���� ��������� �����
        {
         if(way[i+1][j]==FREE) way[i+1][j]=kol+1; // ������ �������
         if(way[i-1][j]==FREE) way[i-1][j]=kol+1; // ����� �������
         if(way[i][j+1]==FREE) way[i][j+1]=kol+1; // ������� �������
         if(way[i][j-1]==FREE) way[i][j-1]=kol+1; // ������ �������
         if(way[i+1][j]==START)break; // ���� ��������� � ������
         if(way[i-1][j]==START)break;
         if(way[i][j+1]==START)break;
         if(way[i][j-1]==START)break;
        }
    }
 }
 kol++;
}

for(int i=1; i<N-1; i++)           // ������� ������� ��������
        for(int j=1; j<N-1; j++)
        {
         if (way[i][j]<10) cout <<" ";
         cout << way[i][j] << " ";
         if (j==N-2) cout << "\n";
                }
                cout << "\n";

       int X=1,Y=1; // ���������� ��������� �����
       int X1=0,Y1=0; // �������������� �������� ���������
       int step=FULL; // ������ ������������ ����
       cout <<"Length of way for iterations:\nFirst String = RESULT\n";
    while(way[X][Y]!=FINISH) // ���������� �� �������� �����?
    {
       if(way[X+1][Y]<step) {step=way[X+1][Y]; X1=X+1; Y1=Y;}
       if(way[X-1][Y]<step) {step=way[X-1][Y]; X1=X-1; Y1=Y;}
       if(way[X][Y+1]<step) {step=way[X][Y+1]; X1=X; Y1=Y+1;}
       if(way[X][Y-1]<step) {step=way[X][Y-1]; X1=X; Y1=Y-1;}
       if (step==FULL) {cout << "WAY NOT FOUND!!!\n"; break;} //���� ���� �� ����������
       cout << step-FINISH+1 <<" Steps\n";
     X=X1;
     Y=Y1; 
     field[X1][Y1]=-5; // ������� ��� �� ��� ������
     }
     cout <<"\n";
        for(int i=1;i<N-1;i++)
        {
         for(int j=1;j<N-1;j++)
         {
          switch(field[i][j])
                  {
                   case FREE:{cout <<' '<< " "; break;}
                   case FULL:{cout <<'*'<< " "; break;}
                   case START:{cout <<'S'<< " "; break;}
                   case -5:{cout <<'>' << " "; break;}
                  }
         }
cout << "\n";
        }
        system("pause");
        return 0;
}
