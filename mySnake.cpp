#include <stdio.h>
#include <stdlib.h>
#include "windowsLTP.cpp"
#include <string.h>
#include <conio.h>
#include <time.h>					
//---------------------------------------------------------------------------
//map will be 100x25
#define MaxX 100
#define MaxY 25
//---------------------------------------------------------------------------
bool endgame = false, mode1 = false, mode2 = false;
int n,m,speed,mode;
//---------------------------------------------------------------------------
enum Status {len,xuong,trai,phai};
struct point { int x,y; }; 
struct game {
	int length;
	int countfood;
	Status move;
	point snake[50];
	point food;
} player;
//---------------------------------------------------------------------------
void map(){
	for(int i = 0; i <= MaxX; i++){
		gotoxy(i,0); puts("+");
		gotoxy(i,MaxY); puts("+");
	}
	for(int j = 0; j <= MaxY; j++){
		gotoxy(0,j); puts("+");
		gotoxy(MaxX,j); puts("+");
	}
}
void show() {
	int j = 0;
	while(1) {
		SetColor(j);
		printf("\n");
		printf("\t\t ___________________________________\n");
		printf("\t\t|                                   |\n");
		printf("\t\t|       GAME SNAKE IN C CODE        |\n");
		printf("\t\t|           *Author: LTP*           |\n");
		printf("\t\t|                                   |\n");			//ko chon duoc dau :))
		printf("\t\t|                                   |\n");			//luoi lam
		printf("\t\t|            - Play -               |\n");			//lam mau thoi
		printf("\t\t|                                   |\n");
		printf("\t\t|         Chose your color          |\n");
		printf("\t\t|___________________________________|\n\n");
		Sleep(200);
		if (j == 15) j = 0;
		if (kbhit()) break;
		system("cls");
		j++;
	}
}
void start(){
	show();
	getch();
	printf("\t\tSpace to pause\n\t\tA,W,S,D to move\n\t\tEat food(*), Careful block(X)\n\t\t------------------------\n\n"); 
	printf("\t\tNhap n = "); scanf("%d",&n);
	printf("\n\t\tNhap speed (fast = 1, little fast = 2, little slow = 3, slow = 4) : "); scanf("%d",&m);
	printf("\n\t\tMode 1: Co Dien\tMode 2: Xuyen Tuong\t"); scanf("%d",&mode);
	if(mode == 1){ //co dien
		mode1 = true;
	}
	if(mode == 2){ //xuyen tuong
		mode2 = true;
	}
	switch(m) {
		case 1 : speed = 50; break;
		case 2 : speed = 100; break;
		case 3 : speed = 150; break;
		case 4 : speed = 200; break;
	}
	system("cls");
	map();
	endgame = false;
}
void khoitao(game &player,int n) {
	player.length = n+1; 
	//start in (15,5)
	for (int i = 0; i < player.length; i++) {
		player.snake[i].x = i+10; 
		player.snake[i].y = 3; 
	}
	player.move = trai;
	player.countfood = 0;
}
void xuyentuong(game &player){
	if (player.snake[0].x <= 0) {
		player.snake[0].x = MaxX - 1;
	} else if (player.snake[0].y <= 0) {
		player.snake[0].y = MaxY - 1;
	} else if (player.snake[0].x >= MaxX) {
		player.snake[0].x = 1;
	} else if (player.snake[0].y >= MaxY) {
		player.snake[0].y = 1;
	}
}
void drawsnake(game &player) {
	if(mode2 == true){
		xuyentuong(player);
	}
	for (int i = player.length; i > 0 ; i--) {
		SetColor(2);
		player.snake[i].x = player.snake[i-1].x;
		player.snake[i].y = player.snake[i-1].y;
	//check dieu kien
		if (player.snake[i].x > 0 && player.snake[i].y > 0 && player.snake[i].x < MaxX && player.snake[i].y < MaxY) {
			gotoxy(player.snake[i].x,player.snake[i].y); printf("o");
			gotoxy(player.snake[player.length].x,player.snake[player.length].y); printf(" ");
			SetColor(9);
			gotoxy(player.snake[0].x,player.snake[0].y); printf("o");
		}
	}
	SetColor(7);
}
bool needfood() {
	if (player.countfood == 1) {
		return false;
	}
	for (int i = 1; i < player.length; i++) {
		if (player.food.x == player.snake[i].x && player.food.y == player.snake[i].y) {
			return true;
		}
	}
	return true;
}
void drawfood(game &player) {
	if (needfood()) {
		srand(time(0));
		player.food.x = 1 + rand() % 99;
		player.food.y = 1 + rand() % 24;
		SetColor(3);
		gotoxy(player.food.x, player.food.y); printf("*");
		SetColor(7);
		player.countfood = 1;
	}		
}
void dieukhien(char key, game &player) {
        if (key == 'W' || key == 'w') player.move = len;
        else if (key == 'S' || key == 's') player.move = xuong;
        else if (key == 'D' || key == 'd') player.move = phai;
        else if (key == 'A' || key == 'a') player.move = trai;
        else if (key == ' ') { getch(); }		//enter to pause
}
void move(game &player) {
	if (player.move == len) player.snake[0].y--;
    else if (player.move == xuong) player.snake[0].y++;
    else if (player.move == trai) player.snake[0].x--;
    else if (player.move == phai) player.snake[0].x++;
}
void eatfood(game &player) {
	if (player.snake[0].x == player.food.x && player.snake[0].y == player.food.y) {
		player.length ++;
		player.countfood = 0;
	}
}
bool die() {
	if(mode1 == true){
		if (player.snake[0].x <= 0 || player.snake[0].y <= 0 || player.snake[0].x >= MaxX || player.snake[0].y >= MaxY) {
			endgame = true;
		}
	}
	for (int i = 5; i < player.length; i++) {
		if (player.snake[0].x == player.snake[i].x && player.snake[0].y == player.snake[i].y) {
			endgame = true;
		}	
	}
}
void checkendgame() {  
	if (endgame == true) {
		for(int i = 5; i > 0; i--){
			gotoxy(20,25);
			printf("Game Over!!! Play Again in %d s . . . Press Space to Exit",i);
			if (kbhit()) {
		    	char c = getch();
		        if(c = ' ') exit(0);
		    }
			Sleep(1000);
		}
		start();
		khoitao(player,n);
	}
}
//---------------------------------------------------------------------------
int main() {	
	HideCur(false);
	start();
	khoitao(player,n);
	
    while (1) {
    drawfood(player);
    if (kbhit()) {
    	char key = getch();
        dieukhien(key,player);
    }
    move(player);
	drawsnake(player);
    eatfood(player);
    die();
	checkendgame();
    Sleep(speed);
    }
}
