#include<iostream>
#include<cstdlib>
#include<time.h>
#include<conio.h>
#include<unistd.h>
using namespace std;

struct Player{
	int score;
	char move;
	int Ace;
	int cards[11];
	int point;
}players[2];

void Play_Game(){
	for(int i=0;i<2;i++){
		for(int b=0;b<11;b++){
			players[i].cards[b]=0;
		}
		players[i].move='d';
		int x=3;
		srand(time(0));
		players[i].cards[0]=rand()%11+1;
		//players[i].cards[0]=11;
		players[i].cards[1]=rand()%11+1;
		//players[i].cards[1]=11;

		while(1){
			system("cls");	
			cout<<"\t\t\t\t\t\t\tPlayer 1 :"<<players[0].point<<endl<<"\t\t\t\t\t\t\tPlayer 2 :"<<players[1].point<<endl;
			players[i].Ace=0;
			players[i].score=0;
			cout<<"Player"<<i+1<<endl;
			for(int a=0;a<11;a++){
				if(players[i].cards[a]!=0){
					cout<<players[i].cards[a]<<" ";
					players[i].score+=players[i].cards[a];
					if(players[i].cards[a]==11){
						players[i].Ace++;
					}									
				}
			}
			if(players[i].Ace==1){
				if(players[i].score>21){
					players[i].score-=10;	
					cout<<endl<<"Score : "<< players[i].score;
				}
				else{
					cout<<"Score : "<<players[i].score<<" / "<<players[i].score-10;
				}	
			}	
			else if(players[i].Ace==2){
				players[i].score-=10;
				if(players[i].score>21  ){
					players[i].score-=10;
					cout<<"Score : "<<players[i].score;
				}
				else{
					cout<<"Score : "<<players[i].score<<" / "<<players[i].score-10;
				}
			}	
			else	
				cout<<endl<<"Score : "<< players[i].score;
			if(players[i].score>21 || players[i].move=='s'){
				cout<<endl<<"Press keyboard ";
				getch();
				system("cls");
				if(i==0){
					cout<<"if you are player 2 press keyboard";
					getch();
				}
				break;
			}
			do
			{
				cout<<endl<<"Draw or Stand (d/s)"<<endl;
				players[i].move=getch();	
			}while(players[i].move!='d' && players[i].move !='s');
			if(players[i].move=='d'){
				players[i].cards[x]=rand()%11+1;
			//	players[i].cards[x]=11;
				x++;
			}	
		}
	}
	system("cls");
	cout<<"Player 1 score:"<<players[0].score<<endl<<"Player 2 score:"<<players[1].score<<endl;
	if(players[0].score<=21 && players[1].score<=21){
		if(players[0].score>players[1].score){
			cout<<"Player 1 is winner..."<<endl;
			players[0].point++;
		}
		else if(players[0].score == players[1].score) cout<<"Draw";
		else{
			cout<<"Player 2 is winner..."<<endl;
			players[1].point++;
		}
	}
	else if(players[0].score>21){
		if(players[1].score<=21){
			cout<<"Winner is player 2 "<<endl;
			players[1].point++;
		}
		else	cout<<"Draw";
	}
	else{
		cout<<"Winner is Player 1..."<<endl;
		players[0].point++;
	}
	
}


int main( ){
			players[0].point=0;
			players[1].point=0;
	
	while(true){
		char cont;
		Play_Game();
		cout<<"Press enter for restart";
		cont=getch();
		if(cont == '\r')
			continue;
		else
			break;
	
	}
	system("cls");
	
	cout<<"Player 1 :"<<players[0].point<<endl<<"Player 2 :"<<players[1].point<<endl;
	cout <<"Congratulations player ";
	if(players[0].score>players[1].score) cout<<"1";
	else cout<<"2";
	sleep(1);
	
}
