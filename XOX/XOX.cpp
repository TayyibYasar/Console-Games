#include<iostream>
#include<time.h>
#include<cstdlib>
#include<windows.h>
#include<conio.h>

using namespace std;


void gotoxy(short int x, short int y){
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

char sahne[11][25];
bool gameover = false;
bool win = false;
bool lose = false;
int sira = 0;
int hamleSay = 0;
int sen = 0;
int pc = 0;
bool exitt = false;
bool hard = false;

void OlusturSahne()
{
	for(int i = 0 ; i < 11; i++)
	{
		for(int j = 0 ; j < 25 ; j++)
		{
			if(j == 8)
				sahne[i][j] = 220;
			else if(j == 17)
				sahne[i][j] = 220;
			else if(i == 3)
				sahne[i][j] = 220;
			else if(i == 7)
				sahne[i][j] = 220;
			else
				sahne[i][j] = '\0';
		}		
	}
}
void CizSahne(){
	for(int i= 0 ; i<11 ;i++){
		for(int j=0; j < 25 ; j++)
		{
			cout<<sahne[i][j];
		}
		cout<<endl;
	}
}
void SilSahne(){
	for(int i= 0 ; i<11 ;i++){
		for(int j=0; j < 25 ; j++)
		{
			sahne[i][j] = 0;
		}
	}	
}
void YokEt(int tip, char sekil, int row, int column)
{
	SilSahne();
	OlusturSahne();
	if(tip == 0){
		sahne[row][3] = sahne[row][12] = sahne[row][21] = sekil;
	}
	if(tip == 1){
		sahne[1][column] = sahne[5][column] = sahne[9][column] = sekil;
	}
	if(tip == 2){
		sahne[1][3] = sahne[5][12] = sahne[9][21] = sekil;
	}
	if(tip == 3){
		sahne[1][21] = sahne[5][12] = sahne[9][3] = sekil;
	}
}


bool HamleYap(){
	if(hamleSay == 0 && sahne[5][12] != 'X' && hard){
		sahne[5][12] = 'O';
		sira--;
	}
	for(int i = 1 ; i < 10 ; i+=4)
		{
			if(sahne[i][12] == 'O'){
				if(sahne[i][21] != 'O' && sahne[i][3] =='O' && sira == 1 && sahne[i][21] != 'X'){
					sira--;
					sahne[i][21] = 'O';
				}
				else if(sahne[i][21] == 'O' && sahne[i][3] !='O' && sira == 1 && sahne[i][3] != 'X'){
					sira--;
					sahne[i][3] = 'O';
				}
			}
			else if(sahne[i][21] == 'O' && sahne[i][3] =='O' && sira == 1 && sahne[i][12] != 'X'){
				sahne[i][12] = 'O';
				sira--;
			}
			if(sahne[i][21] == 'O' && sahne[i][3] =='O' && sahne[i][12] == 'O' ){
					lose = true;
					gameover = true;
					//YokEt(0,'O',i,0);
			}
		}
		for(int j = 3 ; j < 22 ; j+=9)
		{
			if( sahne[5][j] == 'O' ){
				
				if(sahne[1][j] != 'O' && sahne[9][j] == 'O' && sira == 1 && sahne[1][j] != 'X'){
					sahne[1][j] = 'O'; 
					sira--;
				}
				else if(sahne[1][j] == 'O' && sahne[9][j] != 'O' && sira == 1 && sahne[9][j] != 'X'){
					sira--;
					sahne[9][j] = 'O';
				}
			}
			else if(sahne[1][j] == 'O' && sahne[9][j] == 'O' && sira == 1 && sahne[5][j]!= 'X'){
				sira--;
				sahne[5][j] = 'O';
			}
			if(sahne[1][j] == 'O' && sahne[9][j] == 'O' && sahne[5][j] == 'O'){
					lose = true;
					gameover = true;
					//YokEt(1,'O',0,j);
				}
		}
		
		if( sahne[5][12] == 'O' ){
			if(sahne[1][3] != 'O' && sahne[9][21] == 'O' && sira == 1 && sahne[1][3] != 'X' ){
				sahne[1][3] = 'O';
				sira--;
			}
			else if(sahne[1][3] == 'O' && sahne[9][21] != 'O' && sira == 1 && sahne[9][21] != 'X'){
				sahne[9][21] = 'O';
				sira--;
			}
			if(sahne[1][21] != 'O' && sahne[9][3] == 'O' && sira == 1 && sahne[1][21] != 'X'){
				sahne[1][21] = 'O';
				sira--;
			}
			else if(sahne[1][21] == 'O' && sahne[9][3] != 'O' && sira == 1 && sahne[9][3] != 'X'){
				sahne[9][3] = 'O';
				sira--;
			}
		}
		if(sahne[5][12] != 'O' && sahne[1][3] == 'O' && sahne[9][21] == 'O' && sira == 1 && sahne[5][12] != 'X'){
			sira--;
			sahne[5][12] = 'O';
		}
		if(sahne[5][12] != 'O' && sahne[1][21] == 'O' && sahne[9][3] == 'O' && sira == 1 && sahne[5][12] != 'X'){
			sira--;
			sahne[5][12] = 'O';
		}
		if(sahne[1][3] == 'O' && sahne[9][21] == 'O' && sahne[5][12] == 'O'){
				gameover = true;
				lose = true;
				//YokEt(2,'O',0,0);
			}
		if(sahne[1][21] == 'O' && sahne[9][3] == 'O' && sahne[5][12] == 'O'){
				gameover = true;
				lose = true;
				//YokEt(3,'O',0,0);
			}
	//Ayný satýrlarý
		for(int i = 1 ; i < 10 ; i+=4)
		{
			if(sahne[i][12] == 'X'){
				if(sahne[i][21] == 'X' && sahne[i][3] =='X' ){
					gameover = true;
					win = true;
					YokEt(0,'X',i,0);
					return gameover;
				}
				else if(sahne[i][21] != 'X' && sahne[i][3] =='X' && sira == 1 && sahne[i][21] != 'O'){
					sira--;
					sahne[i][21] = 'O';
				}
				else if(sahne[i][21] == 'X' && sahne[i][3] !='X' && sira == 1 && sahne[i][3] != 'O'){
					sira--;
					sahne[i][3] = 'O';
				}
			}
			else if(sahne[i][21] == 'X' && sahne[i][3] =='X' && sira == 1 && sahne[i][12] != 'O'){
				sahne[i][12] = 'O';
				sira--;
			}
		}
		//Ayný sutunlar
		for(int j = 3 ; j < 22 ; j+=9)
		{
			if( sahne[5][j] == 'X' ){
				if(sahne[1][j] == 'X' && sahne[9][j] == 'X'){
					gameover = true;
					win = true;
					YokEt(1,'X',0,j);
					return gameover;
				}
				else if(sahne[1][j] != 'X' && sahne[9][j] == 'X' && sira == 1 && sahne[1][j] != 'O'){
					sahne[1][j] = 'O'; 
					sira--;
				}
				else if(sahne[1][j] == 'X' && sahne[9][j] != 'X' && sira == 1 && sahne[9][j] != 'O'){
					sira--;
					sahne[9][j] = 'O';
				}
			}
			else if(sahne[1][j] == 'X' && sahne[9][j] == 'X' && sira == 1 && sahne[5][j]!= 'O'){
				sira--;
				sahne[5][j] = 'O';
			}
		}
		//Soldan saða çapraz
		if( sahne[5][12] == 'X' ){
			if(sahne[1][3] == 'X' && sahne[9][21] == 'X' ){
				gameover = true;
				win = true;
				YokEt(2,'X',0,0);
				return gameover;
			}
			else if(sahne[1][3] != 'X' && sahne[9][21] == 'X' && sira == 1 && sahne[1][3] != 'O' ){
				sahne[1][3] = 'O';
				sira--;
			}
			else if(sahne[1][3] == 'X' && sahne[9][21] != 'X' && sira == 1 && sahne[9][21] != 'O'){
				sahne[9][21] = 'O';
				sira--;
			}
			if(sahne[1][21] == 'X' && sahne[9][3] == 'X'){
				gameover = true;
				win = true;
				YokEt(3,'X',0,0);
				return gameover;
			}
			else if(sahne[1][21] != 'X' && sahne[9][3] == 'X' && sira == 1 && sahne[1][21] != 'O'){
				sahne[1][21] = 'O';
				sira--;
			}
			else if(sahne[1][21] == 'X' && sahne[9][3] != 'X' && sira == 1 && sahne[9][3] != 'O'){
				sahne[9][3] = 'O';
				sira--;
			}
		}
		if(sahne[5][12] != 'X' && sahne[1][3] == 'X' && sahne[9][21] == 'X' && sira == 1 && sahne[5][12] != 'O'){
			sira--;
			sahne[5][12] = 'O';
		}
		if(sahne[5][12] != 'X' && sahne[1][21] == 'X' && sahne[9][3] == 'X' && sira == 1 && sahne[5][12] != 'O'){
			sira--;
			sahne[5][12] = 'O';
		}
		while(sira == 1){
			if(hamleSay == 4){
				gameover = true;
				return gameover;
			}
			int xx = (rand()%3)*9+3;
			int yy = (rand()%3)*4+1;
			if(sahne[yy][xx]!= 'X' && sahne[yy][xx] != 'O'){
				sahne[yy][xx] = 'O';
				sira--;
			}
		}
		hamleSay++;
		
		
		return gameover;
}

int main()
{
	cout<<"Select difficulty"<<endl;
	cout<<"1. Easy"<<endl;
	cout<<"2. Hard"<<endl;
	char difficulty;
	do{
		difficulty = getch();
	}while(difficulty != '1' && difficulty != '2');
	if(difficulty == '2')
		hard = true;
	while(!exitt){
		srand(time(NULL));
		gameover = false;
	 	win = false;
		lose = false;
	 	sira = 0;
		hamleSay = 0;
		gotoxy(0,13);
		cout<<"Sen: "<<sen<<endl;
		cout<<"Pc: "<<pc;
		gotoxy(30,2);
		cout<<"E tusu cikis";
		OlusturSahne();
		gotoxy(0,0);
		CizSahne();
		int x = 3;
		int y = 1;

		while(!gameover){
			gotoxy(x,y);
			char komut;
			ShowConsoleCursor(true);
			komut = getch();
			ShowConsoleCursor(false);
			if(komut == 'd'){
				x += 9;
				if(x == 30)
					x = 3;
			}
			else if(komut == 'a'){
				x -= 9;
				if(x == -6)
					x = 21;
			}
			else if(komut == 's'){
				y += 4;
				if(y == 13)
					y = 1; 
			}
			else if(komut == 'w'){
				y -= 4;
				if(y == -3)
					y = 9;
			}
			else if(komut == 32 && sira == 0){
				if(sahne[y][x]!= '\0'){
					continue;
				}
				sahne[y][x] = 'X';
				sira++;
			}
			else if(komut == 'e'){
				gameover = true;
				exitt = true;
			}
			else{
				continue;
			}
			if(sira == 1)
				if(HamleYap())
				{
					gotoxy(0,0);
					CizSahne();
					Sleep(500);
					getch();	
					gotoxy(0,13);
					if(win){
						sen++;					
					}
					else if(lose){
						pc++;
					}
					break;
				}
			gotoxy(0,0);
			CizSahne();	
		}
	}
	return 0;	
}


