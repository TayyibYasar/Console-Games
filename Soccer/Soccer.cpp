#include<iostream>
#include<windows.h>
#include<conio.h>
#include<cstdlib>
#include<time.h>

#define Boy 25 // aþaðýya doðru
#define Derinlik 30 // yana doðru

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



char Sahne[Boy][Derinlik];
bool game = true;




void SahaOlustur(){
	for(int i =0 ; i < Boy; i++){
		for(int j = 0; j < Derinlik; j++){
			if((i == 0 || i == Boy -1) && !(j > Derinlik/2-4 && j < Derinlik/2+4 ))
				Sahne[i][j] = 220;
			if(j == 0 || j == Derinlik-1)
				Sahne[i][j] = 220;
		}
	}
}

void SahaCiz(){
	for(int i = 0 ; i < Boy; i++){
		for(int j = 0; j < Derinlik; j++){
			cout<<Sahne[i][j];
		}
		cout<<endl;
	}
}

class Ball{
	public:
		int x;
		int y;
		int accelerationx;
		int accelerationy;
		bool game;
		bool goal;
		int score[2];
		Ball(){
			accelerationx = 0;
			accelerationy = 0;
			x = Derinlik/2;
			y = Boy/2;
			Sahne[y][x] = 'o';
			game = true;
			goal = false;
			score[0] = 0;
			score[1] = 0;
		}
		void move(){
			Sahne[y][x] = ' ';
			x += accelerationx;
			y += accelerationy;
			if((y <= 0 || y >= Boy-1) && (x > Derinlik/2-4 && x < Derinlik/2+3)){
				if(y >= Boy-1)
					score[0]++;
				else
					score[1]++;
				x = Derinlik/2;
				y = Boy/2;		
			}	
			if(x < 1){
				x += (1-x)*2;
			}
			else if(x >= Derinlik-2){
				x -= (x-(Derinlik-2))*2;
			}
			if(y < 2){
				y+= (2-y)*2;
			}
			else if(y > Boy-2){
				y-=(y-(Boy-2))*2;
			}
			Sahne[y][x] = 'o';
			if(accelerationx != 0){
				if(accelerationx > 0)
					accelerationx--;
				else
					accelerationx++;
			}
			if(accelerationy != 0){
				if(accelerationy > 0)
					accelerationy--;
				else
					accelerationy++;
			}			
		}
		void setAcceleration(int x = 0, int y = 0){
			accelerationx += x;
			accelerationy += y;
		}
}ball;



class Player{
	public:
		int x;
		int y;
		int activate;
		bool side;
		Player(bool side){
			this->side = side;
			if(this->side){
				y = Boy - 2;
			}
			else{
				y = 2;
			}
			x = Boy/2 + 3;
			Sahne[y][x] = '#';
			activate = 1;
		}
		void move(char movement){
			int tempx = x;
			int tempy = y;
			if(this->side){
				Sahne[y][x] = ' ';
				if(movement == 56){
					for(int i = 0; i < activate; i++){
						y--;
						if(y == ball.y && x == ball.x){
							ball.setAcceleration(0,-(activate-i)*2);
						}
					}
					activate = 1;
				}
				else if(movement == 52){
					for(int i = 0; i < activate; i++){
						x--;
						if(y == ball.y && x == ball.x){
							ball.setAcceleration(-(activate-i)*2,0);
						}
					}
					activate = 1;
				}
				else if(movement == 53){
					for(int i = 0; i < activate; i++){
						y++;
						if(y == ball.y && x == ball.x){
							ball.setAcceleration(0,(activate-i)*2);
						}
					}
					activate = 1;
				}
				else if(movement == 54){
					for(int i=0; i < activate; i++){
						x++;
						if(y == ball.y && x == ball.x){
							ball.setAcceleration((activate-i)*2,0);
						}
					}
					activate = 1;
				}
				else if(movement == 48){
					activate = 3;
				}
			}
			else{
				Sahne[y][x] = ' ';
				if(movement == 119){
					for(int i = 0; i < activate; i++){
						y--;
						if(y == ball.y && x == ball.x){
							ball.setAcceleration(0,-(activate-i)*2);
						}
					}
					activate = 1;
				}
				else if(movement == 115){
					for(int i = 0; i < activate; i++){
						y++;
						if(y == ball.y && x == ball.x){
							ball.setAcceleration(0,(activate-i)*2);
						}
					}
					activate = 1;
				}
				else if(movement == 97){
					for(int i = 0; i < activate; i++){
						x--;
						if(y == ball.y && x == ball.x){
							ball.setAcceleration(-(activate-i)*2,0);
						}
					}
					activate = 1;
				}
				else if(movement == 100){
					for(int i=0; i < activate; i++){
						x++;
						if(y == ball.y && x == ball.x){
							ball.setAcceleration((activate-i)*2,0);
						}
					}
					activate = 1;
				}
				else if(movement == 32){
					activate = 3;
				}
			}
			if(y <= 0 || y > Boy-1 || x <= 0 || x > Derinlik-2){
				x = tempx;
				y = tempy;
			}
			Sahne[y][x] = '#';
		}
};



int main()
{
	srand(time(NULL));
	ShowConsoleCursor(false);
	Player player1(false);
	Player player2(true);
	while(ball.game){
		gotoxy(0,0);
		SahaOlustur();
		SahaCiz();
		gotoxy(Derinlik + 5, 0);
		cout<<"Score: "<<ball.score[0];
		gotoxy(Derinlik+5, Boy);
		cout<<"Score: "<<ball.score[1];
		ball.move();
		if(_kbhit()){
			char input = getch();
			player1.move(input);
			player2.move(input);
		}
	}
}
