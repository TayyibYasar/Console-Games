#include<iostream>
#include<windows.h>
#include<conio.h>
#include<cstdlib>
#include<time.h>
#include<fstream>

#define Boy 8
#define En 40


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

bool gameOver=1;
int Can=3;
int oyunHiz;
int engelSayi=4;
char Saha[Boy][En];
int skor=0;

class Top{
		int y;
		
	public:
		char hareket;
		void sety(int);
		int gety();
		Top(){
			y=Boy/2;
		}
		
}top;

void Top::sety(int y){
	this->y+=y;
	if(this->y==Boy-1){
		this->y=1;
	}
	else if(this->y==0){
		this->y=Boy-2;
	}
}
int Top::gety(){return y;}


class Engel{
	
	int x,y;
	public:
		
		Engel();
		void setx();
		void sety();
		int getx();
		int gety();
		
}engel[10];


Engel::Engel(){
	x=rand()%15+24;
	y=rand()%(Boy-2)+1;
}
void Engel::setx(){
	x-=1;
	if(x==0){
		x=rand()%15+24;
		skor++;
		Engel::sety();
		
	}
}
void Engel::sety(){
	y=rand()%(Boy-2)+1;
}
int Engel::getx(){return x;}
int Engel::gety(){return y;}

void Saha_Sil(){
	for(int i=0;i<Boy;i++){
		for(int j=0;j<En;j++){
			Saha[i][j]=' ';
		}
	}
	
}

void Saha_Olustur(){
	for(int i=0;i<Boy;i++){
		for(int j=0;j<En;j++){
			if(i==0 || i==Boy-1){
				Saha[i][j]=220;
			}
		}
	}
	Saha[top.gety()][1]=224;
	
	for(int i=0;i<engelSayi;i++){
	
		Saha[engel[i].gety()][engel[i].getx()]='*';
	}
	
	
}

void Saha_Ciz(){
	Saha_Sil();
	Saha_Olustur();
	gotoxy(0,0);
	for(int i=0;i<Boy;i++){
		for(int j=0;j<En;j++){

			cout<<Saha[i][j];
		}
		cout<<endl;
	}
	gotoxy(50,0);
	cout<<"Can:"<<Can;	
	gotoxy(50,2);
	cout<<"Skor:"<<skor;

}
void klavyeKontrol(){
		
		
		if(_kbhit()){
			top.hareket=getch();
			if(top.hareket=='w'){top.sety(-1);}
			else if(top.hareket =='s'){top.sety(1);}
		}
		else{top.hareket='f';}
}

void oyunZorlastir(){
	int c=skor/50;
	engelSayi=4+c;
	if(engelSayi>9) engelSayi=9;
}

void oyunAkis(){
			oyunZorlastir();
			
			for(int i=0;i<engelSayi;i++){
				engel[i].setx();
			if(engel[i].getx()==1 && engel[i].gety()==top.gety()){
				Can--;
				if(Can<1){

					gameOver=false;
				}
			}
		}
		
}
void oyunBaslangic(){
	int b=4;
	do{
		cout<<"1-Kolay"<<endl<<"2-Orta"<<endl<<"3-Zor"<<endl;
		b=getch();
	}while(b!='1' && b!='2' && b!='3');
	if(b=='1') oyunHiz=15;
	else if(b=='2') oyunHiz=1;
	else oyunHiz=0.9;
	
	
	gotoxy(8,30);
	int a=0;
	while(a<3){
		a++;
		gotoxy(40,10);
		cout<<"STARTÝNG..."<<"   "<<a;
		Sleep(800);
	}	

	system("cls");
}
void DosyaYaz()
{
	
	
	string name;
	cout<<"Enter your name:: ";
	cin>>name;
	ofstream Dosya;
	Dosya.open("Skorlar.txt",std::ios_base::app);
	Dosya<<name<<" ";
	if(oyunHiz==15) Dosya<<"Kolay"<<" ";
	else if(oyunHiz==1) Dosya<<"Orta"<<" ";
	else Dosya<<"Zor"<<" ";
	Dosya<<skor<<endl;
	
	
	Dosya.close();
	cout<<"Dosyaya puaniniz kaydedilmiþtir..."<<endl;
	
	
}

void DosyaOku(){
	system("cls");
	ifstream dosya;
	string name;
	string mod;
	int point;
	int temp=0;
	string hname;
	string hmod;
	dosya.open("Skorlar.txt");
	while(!dosya.eof()){
		dosya>>name;
		dosya>>mod;
		dosya>>point;
		cout<<name<<" "<<mod<<" "<<point<<endl;
		if(point>temp){
			temp=point;
			hname=name;
			hmod=mod;
		}	
			
	}
	
	
	cout<<" Highest ::"<<hname<<" "<<hmod<<" "<<temp<<endl;
	
	dosya.close();
	
	
}
int main(){
	
	srand(time(NULL));
	ShowConsoleCursor(false);
	oyunBaslangic();
	
	while(gameOver){
		Saha_Ciz();
		klavyeKontrol();
		Sleep(oyunHiz);
		oyunAkis();
	}
	
		system("cls");
		cout<<"GameOver"<<endl;
		cout<<"Your score is = "<<skor<<endl;
		cout<<"Do you want to save your score(Y/N)"<<endl;
		char islem=getch();
		if(islem=='y') DosyaYaz();
		getch();
		cout<<"Do you want to see highest record(y/n)"<<endl;
		islem=getch();
		if(islem=='y') DosyaOku();
		
		
		getch();


}


