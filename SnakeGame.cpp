#include<iostream>
#include<conio.h>
#include<dos.h>
#include<time.h>
#include<windows.h>

#define MAXFRAMESIZEX 120 
#define MAXFRAMESIZEY 29

using namespace std;

void gotoxy(int x, int y){
	COORD pos = {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

class Point{
	int x, y;
	public:
		Point(){}
		Point(int x, int y);
		int getX();
		int getY();
		void setPoint(int x, int y);
		void goLeft();
		void goRight();
		void goDown();
		void goUp();
		void Spawn(char head);
		void copyPosition(Point*p);
		int isEqual(Point*p);
};

//constructor
Point::Point(int x, int y) : x(x), y(y){}

//getter
int Point::getX(){ return x;}
int Point::getY(){ return y;}

//setter
void Point::setPoint(int x, int y) {
		this->x = x; 
		this->y = y;
	}

void Point::goUp(){
	y--;
	if(y < 0)
		y = MAXFRAMESIZEY; //go through walls
}

void Point::goDown(){
	y++;
	if(y > MAXFRAMESIZEY)
		y = 0; //go through walls
}

void Point::goRight(){
	x++;
	if(x > MAXFRAMESIZEX)
		x = 0; //go through walls
}

void Point::goLeft(){
	x--;
	if(x < 0)
		x = MAXFRAMESIZEX; //go through walls
}

void Point::Spawn(char head = 'O'){
	gotoxy(x,y);
	cout << head;	
}

int Point::isEqual(Point*p){
	if(p->x == x && p->y ==y)
		return 1;
	return 0;
}

void Point::copyPosition(Point*p){
	p->x = x;
	p->y = y;
}


class Snake{
	private:
		Point*body[50]; //snake
		Point food; //snake food
		int size; //size of snake
		char directions; //direction of snake
		int condition; // determining snake is dead or alive
		int start; 
	public:
		Snake(){
			body[0] = new Point(1,1); //default snake start position from the top left corner
			size = 1; //default snake size (only the head)
			food.setPoint(rand()%MAXFRAMESIZEX, rand()%MAXFRAMESIZEY);	
			condition = 0;
			start = 0;
		}
		void addBody(int x, int y);
		void turnLeft();
		void turnRight();
		void turnDown();
		void turnUp();
		void Move();
		void mainMenu();
		bool SelfHit();
};

void Snake::addBody(int x, int y){
	body[size++] = new Point(x,y); //add the number of 'O' to the body
}

void Snake::turnLeft(){
	if(directions != 'd')
	directions = 'a'; //can't go to the opposite direction
}

void Snake::turnRight(){
	if(directions != 'a')
	directions = 'd'; //can't go to the opposite direction
}
void Snake::turnDown(){
	if(directions != 'w')
	directions = 's'; //can't go to the opposite direction
}
void Snake::turnUp(){
	if(directions != 's')
	directions = 'w'; //can't go to the opposite direction
}



void Snake::mainMenu(){
	cout << "  SNAKE   \n";
	cout << "  GAME!	 ";
	cout << "\n\n   BY	 \n\n";
	cout << " DAVIDSON    \n";
	cout << " FEBRYAN    \n";	
}

void Snake::Move(){
	//clear screen
	system("cls");
			
	if(condition == 0){
		if(start == 0){
			mainMenu();
			cout << "\n\nPress Enter to play!";
			getchar();
			condition = 1;
			start = 1;
		}else{
			cout << "\nGAME OVER!";
			cout << "\n\nPress any key to return to Main Menu";
			getch();
			size = 1;
			condition = 0;
			start = 0;
		}
				
	}
			
	//make snake body follow its head
	for(int i = size - 1; i > 0; i--){
		body[i-1]->copyPosition(body[i]);
	}
			
	//controls snake head directions
	switch(directions){
		case 'w':
			body[0]->goUp();
			break;
		case 's':
			body[0]->goDown();
			break;
		case 'a':
			body[0]->goLeft();
			break;
		case 'd':
			body[0]->goRight();
			break;			
	}
			
	if(SelfHit() == true){
			condition = 0;
	   }
			
	//Eat food if head position the same as food position
	if(body[0]->getX() == food.getX() && body[0]->getY() == food.getY()){
		addBody(0,0);
		//spawn random position for food
		food.setPoint(rand()%MAXFRAMESIZEX, rand()%MAXFRAMESIZEY);
	}
			
	//to spawn the snake
	for(int i = 0; i < size; i++)
		body[i]->Spawn();
			
	food.Spawn('&'); 
	
	Sleep(10);	
}

bool Snake::SelfHit(){
	for(int i = 1; i < size; i++)
		if(body[0] -> isEqual(body[i]))
			return true;
	return false;
}



int main(){ 
	//random time generation so food places would be different each run
	srand(time(NULL));

	Snake game;
	char press;
	do{
		if(kbhit()){ //if keyboard is pressed
			press = getch();
		}
		switch(press){
			case 'w':
				game.turnUp();
				break;
			case 's':
				game.turnDown();
				break;
			case 'a':
				game.turnLeft();
				break;
			case 'd':
				game.turnRight();
				break;
		}
		game.Move();
	}while(press != 'e');
	
	return 0;
}