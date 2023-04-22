#include<iostream>
#include<windows.h>
#include<conio.h>
#include<cstdlib>
#include<time.h>

#define En 20
#define Boy 20

using namespace std;
void gotoxy(int x,int y){
    COORD p = { x, y };
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), p );
}
void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

char Sahne[En][Boy];

class Mermi{
public:	
	int x;
	int y;
	char direction;
	bool carpisma;
	Mermi(int _x, int _y, char _direction){
		x = _x;
		y = _y;
		direction = _direction;		
		carpisma = false;
	} 
	Mermi(){
		x = 0;
		y = 0;
		direction = 'x';
		carpisma = false;
	}
	void move(int);
};

class Player{
	public:
		int x;
		int y;
		char direction;
		Mermi mermi[4];
		Player(){
			x = Boy/2;
			y= En /2;
			direction = 's';
		}
		move(char hareket){
			if(hareket=='w'){
				if(direction == 'w'){	
					if(Sahne[y-2][x] != '*' && Sahne[y-2][x] != '&' && Sahne[y-1][x+1] != '&' && Sahne[y-1][x-1] != '&')
						y--;
				}
				else
					direction='w';
			}
			else if(hareket =='s'){
				if(direction == 's'){
					if(Sahne[y+2][x] != '*' && Sahne[y+2][x] != '&' && Sahne[y+1][x+1] != '&' && Sahne[y+1][x-1] != '&')
						y++;
				}
				else
					direction ='s';	
			}
			else if(hareket == 'd'){
				if(direction == 'd'){
					if(Sahne[y][x+2] != '*' && Sahne[y][x+2] != '&' && Sahne[y-1][x+2] !='&' && Sahne[y+1][x+2]!='&')
						x++;
				}
				else
					direction = 'd';	
			}
			else if(hareket == 'a'){
				if(direction == 'a'){
					if(Sahne[y][x-2] != '*' && Sahne[y][x-2] != '&' && Sahne[y-1][x-2] !='&' && Sahne[y+1][x-2]!= '&')
						x--;
				}
				else
					direction = 'a';	
			}
			else if(hareket == 32){
				int i=4;
				for(i=0; i<4 ; i++){
					if(mermi[i].direction == 'x'){
						cout<<i<<endl;
						break;
					}
				}
				if(i<4){
					mermi[i].x=x;
					mermi[i].y=y;
					mermi[i].direction = direction;
				}
			}
			
		}

}player;

class Enemy{
	public:
		int x;
		int y;
		char direction;
		Mermi mermi[4];
		Enemy(){
			x = 0;
			y = 0;		
			direction = 'x';
		}		
		void move(int r){
			if(x==0 && y==0){
				int t = rand()%5;
				t = r;
			if(t==r){
			
				if(r == 0 && (player.y > 4 || player.x > 4)){
					x = 2;
					y = 2; 
					direction = 's';
				}
				else if(r== 1 && (player.x > 4 || player.y<8 || player.y>12)){
					y = 10;
					x = 2;
					direction = 'd';
				}
				else if(r == 2 && (player.y < 14 || player.x > 4)){
					y = 16;
					x = 2;
					direction = 'd';
				}
				else if(r == 3 && (player.y < 14 || player.x < 14)){
					x = 16;
					y = 16;
					direction = 'w';
				}
				else if(r == 4 && (player.x<14 || player.y>12 || player.y < 8)){
					y = 10;
					x = 16;
					direction = 'a';
				}
				else if(r == 5 && (player.y > 4 || player.x < 14)){
					y = 2;
					x = 16;
					direction = 'a';
				}
			}
			}
				
			else{
				int a = rand()%4+1;
				if(a == 1){
					if(direction == 'w'){	
						if(Sahne[y-2][x] != '*')
								y--;
					}
					else
						direction='w';
				}
				else if(a == 2){
					if(direction == 's'){
						if(Sahne[y+2][x] != '*')
							y++;
					}
					else
						direction ='s';	
				}
				else if(a == 3){
					if(direction == 'd'){
						if(Sahne[y][x+2] != '*')
							x++;
					}
					else
						direction = 'd';
				}
				else if(a == 4){
					if(direction == 'a'){
						if(Sahne[y][x-2] != '*')
							x--;
					}
					else
						direction = 'a';	
				}
				a = rand()%2;
				if(a > 0){
					int i = 0;
					for(i;i<4;i++){
						if(mermi[i].direction == 'x'){
							mermi[i].x = x;
							mermi[i].y = y;
							mermi[i].direction = direction;
							break;
						}
					}
				}
			}
		}
		
}enemy[6];




void Mermi::move(int a){
	if(direction == 'w')
			y--;
		else if(direction == 's')
			y++;
		else if(direction =='d')
			x++;
		else if(direction == 'a')
			x--;	
		if(Sahne[y][x] == '*'){
			x = 0;
			y = 0;
			direction ='x';
			carpisma = false;
		}
		if(a == 1){
		
			if(Sahne[y][x] == '&'){
				direction='x';
				for(int i = 0 ;i<6;i++){
					if((x==enemy[i].x || x == enemy[i].x+1 || x== enemy[i].x-1) && (y == enemy[i].y || y == enemy[i].y-1 || y == enemy[i].y+1)){
						enemy[i].x = 0;
						enemy[i].y = 0;
						y = 0;
						x = 0;
						direction ='x';
						for(int m = 0; m < 4 ; m++){
							if(enemy[i].mermi[m].direction != 'x'){
							
								enemy[i].mermi[m].x = 0;
								enemy[i].mermi[m].y = 0; 
								enemy[i].mermi[m].direction = 'x';
								enemy[i].mermi[m].carpisma = false;
							}
						}
						break;
					}
				}
			}
		}
		else if(a == 2){
			if(Sahne[y][x] == '#'){
				direction = 'x';
				//if((x==player.x || x == player.x+1 || x== player.x-1) && (y == player.y || y == player.y-1 || y == player.y+1)){
					system("cls");
					Sleep(300);
					y = 0;
					x = 0;
					direction = 'x';
					carpisma = false;
				//} 
			}
			else if(Sahne[y][x] == '&'){
				if(carpisma){
					x = 0;
					y = 0;
					direction = 'x';
					carpisma = false;
				}
				carpisma = true;
			}
		}
				
}
void EnemyOlustur(){
	for(int e=0; e<6; e++){
		if(enemy[e].y != 0 && enemy[e].x != 0){
			for(int i=-1;i<2;i++){
				for(int j=1;j>-2;j--){
					Sahne[enemy[e].y+j][enemy[e].x+i] = '&';
				}
			}
			if(enemy[e].direction == 'w'){
				Sahne[enemy[e].y-1][enemy[e].x-1] = ' ';
				Sahne[enemy[e].y-1][enemy[e].x+1] = ' ';
				
			}
			else if(enemy[e].direction == 's'){
				Sahne[enemy[e].y+1][enemy[e].x-1] = ' ';
				Sahne[enemy[e].y+1][enemy[e].x+1] = ' ';
			
			}
			else if(enemy[e].direction == 'a'){
				Sahne[enemy[e].y+1][enemy[e].x-1] = ' ';
				Sahne[enemy[e].y-1][enemy[e].x-1] = ' ';
			
			}
			else if(enemy[e].direction == 'd'){
				Sahne[enemy[e].y+1][enemy[e].x+1] = ' ';
				Sahne[enemy[e].y-1][enemy[e].x+1] = ' ';
			
			}
		}
	}
}


void PlayerOlustur(){
	
	for(int i=-1;i<2;i++){
		for(int j=1;j>-2;j--){
			Sahne[player.y+j][player.x+i] = '#';
		}
	}
	
	if(player.direction == 'w'){
		Sahne[player.y-1][player.x-1] = ' ';
		Sahne[player.y-1][player.x+1] = ' ';
	}
	else if(player.direction == 's'){
		Sahne[player.y+1][player.x-1] = ' ';
		Sahne[player.y+1][player.x+1] = ' ';
	}
	else if(player.direction == 'a'){
		Sahne[player.y+1][player.x-1] = ' ';
		Sahne[player.y-1][player.x-1] = ' ';
	}
	else if(player.direction == 'd'){
		Sahne[player.y+1][player.x+1] = ' ';
		Sahne[player.y-1][player.x+1] = ' ';
	}
	

}
void MermiCiz(){
	for(int i=0; i<4;i++){
		if(player.mermi[i].direction != 'x')
			Sahne[player.mermi[i].y][player.mermi[i].x] = '+';
	}
	
	for(int e = 0;e<6;e++){
		for(int i =0; i<4; i++){
			if(enemy[e].mermi[i].direction != 'x')
				Sahne[enemy[e].mermi[i].y][enemy[e].mermi[i].x] = '+';
		}
	}
	
}
void SahneOlustur(){
	for(int i = 0; i<En; i++)
	{
		Sahne[i][0] = '*';	
		Sahne[i][Boy-1] = '*';	
	}
	
	for(int j =0; j<Boy; j++){
		Sahne[0][j] ='*';
		Sahne[En-1][j] = '*';
	}
	PlayerOlustur();
	EnemyOlustur();
	MermiCiz();	
}

void SahneCiz(){
	for(int i = 0; i<En; i++){
		for(int j = 0; j<Boy; j++ ){
			cout<<Sahne[i][j];
		}
		cout<<endl;
	}
	
}

void SahneSil(){
	for(int i = 0; i<En; i++){
		for(int j = 0; j<Boy; j++ ){
			Sahne[i][j] =' ';
		}
	}	
	
}



int main()
{
	enemy[0].x=2;
	enemy[0].y=2;
	srand(time(NULL));
	ShowConsoleCursor(false);
	while(1){
		gotoxy(0,0);
		SahneOlustur();
		SahneCiz();
		if(_kbhit()){
			char hareket;
			hareket=getch();
			player.move(hareket);
		}
		int a = rand()%20;
		if(a<6)	
			enemy[a].move(a);
		for(int i=0;i<4;i++){
			player.mermi[i].move(1);
		}
		for(int e = 0; e<6; e++){
			for(int i = 0 ; i<4; i++){
				enemy[e].mermi[i].move(2);
			}
		}
		SahneSil();
		Sleep(50);
	}
	return 0;
}
