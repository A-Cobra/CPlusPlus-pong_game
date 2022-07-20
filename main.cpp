#include <iostream>

#include <conio.h>
#include <vector>


using namespace std;

using namespace System;

#define KEY_LEFT 75
#define KEY_RIGHT 77


class CBall
{
private:
	int x;

	int y;

	int dx;

	int dy;

	int color;

	int random;

	int random2;


public:
	CBall() {
		x = 26;
		y = 20;
		
		Random n;
		Random m;
		random = n.Next(1, 3);

		random2 = m.Next(1, 3);
		dx = 1 + rand() % 2;
		dy = 1 + rand() % 2;

		if (random==1) {
			dx *= 1;
		}
		else {
			dx *= -1;
		}
		if (random2 == 1) {
			dy *= 1;
		}
		else {
			dy *= -1;
		}
	};
	~CBall() {};

	void eraseBall() {

		Console::SetCursorPosition(x, y);
		cout << " ";

	}

	void drawBall() {

		Console::SetCursorPosition(x, y);
		cout << (char)169;
	}
	void jumpBall() {
		x += dx;
		y += dy;
		if (x<5 || x>47) {
			changeDX();
		}
		if (y < 3 || y>34) {
			changeDY();
		}
	
	}
	void moveBall() {
		eraseBall();
		_sleep(100);
		jumpBall();
		drawBall();

	}
	int returnDX() {
		return dx;
	}
	int returnX() { return x; }
	int returnY() { return y; }
	int returnDY() { return dy; }

	void resetPosition() {
		x = 26;
		y = 20;

		Random n;
		Random m;
		random = n.Next(1, 3);

		random2 = m.Next(1, 3);
		dx = 1 + rand() % 2;
		dy = 1 + rand() % 2;

		if (random == 1) {
			dx *= 1;
		}
		else {
			changeDX();
		}
		if (random2 == 1) {
			dy *= 1;
		}
		else {
			changeDY();
		}
	}
	void changeDX() {
		dx *= -1;
	}
	void changeDY() {
		dy *= -1;
	}
};

class CPlayer

{

protected:

	int x;

	int y;

	int dx;

	int width;

	int height;

	int color;

	int counter;
public:

	//contructores

	CPlayer() {}

	~CPlayer() {}

	//seters y geters

	void setX(int x)

	{

		this->x = x;

	}



	int getX() {

		return x;

	}

	

	void setY(int y)

	{

		this->y = y;

	}



	int getY() {

		return y;

	}

	void draw() {
		Console::SetCursorPosition(x, y);
		cout << (char)219<< (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;

	}

	void counterIncrease() {
		counter += 1;
	};

	int returnCounter() { return counter; }
};







class CHuman : public CPlayer

{
private:
	


public:

	CHuman() {

		x = 23; 

		y = 34;

		counter = 0;

	}

	~CHuman() {}

	//comportamientos

	int returnCounter() {
		return counter;
	}


	void eraseHuman() {
		Console::SetCursorPosition(x,y);
		cout << "          ";
	}
	void drawHuman() {
		Console::ForegroundColor = ConsoleColor(5);
		draw();
	}

	void moveHuman() {

		eraseHuman();

		drawHuman();

	}

};



class CComputer : public CPlayer

{
private:

	int movement;
	CBall* ball;
public:

	CComputer() {

		x = 23;

		y = 5;

		counter = 0;

	}

	~CComputer() {}

	//comportamientos

	int returnCounter() {
		return counter;
	}

	void jumpComputer() {
		movement = 1 + rand() % 2;
		movement *= 0.9;
		if (ball->returnX()>x) {
			x += movement;
		}
		else {
			x -= movement;
		}
	

	}

	void setBall(CBall* _ball) {
		ball = _ball;
	}
	void eraseComputer() {
		Console::SetCursorPosition(x, y);
		cout << "          ";
	}
	void drawComputer() {
		if (x < 12) {
			x = 12;
		}
		if (x > 40) {
			x = 40;
		}
		Console::ForegroundColor = ConsoleColor(7);
		draw();
	}

	void moveComputer() {

		eraseComputer();

		jumpComputer();

		drawComputer();

	}

};




class CJuego

{

private:

	CComputer* computer;

	int mapNewLenght;

	int mapNewWidth;

	CBall* ball;

	CHuman* human;
public:



	CJuego() {


		mapNewLenght = 45;

		mapNewWidth = 60;

		ball = new CBall();
		
		human = new CHuman();

		computer = new CComputer();

		computer->setBall(ball);

		Console::SetWindowSize(mapNewWidth, mapNewLenght);

		drawMap();
		
		
	}

	~CJuego() {}

	//comportamiento



	void drawMap() {
		for (size_t i = 3; i < mapNewWidth - 5; i++)
		{
			for (size_t j = 3; j < mapNewLenght - 8; j++)
			{
				if (i == 3) {
					Console::ForegroundColor = ConsoleColor(3);
					Console::SetCursorPosition(i, j);
					cout << (char)219;
				}
				if (i == mapNewWidth - 10) {
					Console::ForegroundColor = ConsoleColor(3);
					Console::SetCursorPosition(i, j);
					cout << (char)219;
				}
				
				if (j == 3 && i <= mapNewWidth - 10) {
					Console::ForegroundColor = ConsoleColor(4);
					Console::SetCursorPosition(i, j);
					cout << (char)219;
				}
				if (j == mapNewLenght - 9 && i <= mapNewWidth - 10) {
					Console::ForegroundColor = ConsoleColor(4);
					Console::SetCursorPosition(i, j);
					cout << (char)219;
				}
			}
		}
		Console::ForegroundColor = ConsoleColor(7);
		Console::SetCursorPosition(56, 5);
		cout << computer->returnCounter();
		Console::ForegroundColor = ConsoleColor(5);
		Console::SetCursorPosition(56, 34);
		cout << human->returnCounter();
	
	}


	void jugar() {

		while (true)

		{
			if (ball->returnY()==4) {
				human->counterIncrease();
				system("cls");
				ball->resetPosition();
				drawMap();
			}
			if (ball->returnY() == 34) {
				computer->counterIncrease();
				system("cls");
				ball->resetPosition();
				drawMap();
			}
			if ((ball->returnY() + ball->returnDY()) >= 33 && (ball->returnX() >= human->getX() && ball->returnX() <= human->getX() + 10)) {
				ball->changeDY();
			}
			if ((ball->returnY() + ball->returnDY()) <= 6 && (ball->returnX() >= computer->getX() && ball->returnX() <= computer->getX() + 10)) {
				ball->changeDY();
			}
			ball->moveBall();
			human->drawHuman();
			computer->moveComputer();
			if (_kbhit())

			{

				int tecla = _getch();

				switch (tecla)

				{
				case KEY_LEFT:
					if (human->getX() > 5 || human->getX() < 47) {
						human->eraseHuman();
						human->setX(human->getX() - 1);
					}
					
					break;
				case KEY_RIGHT:
					if (human->getX() > 5 || human->getX() < 47) {
						human->eraseHuman();
						human->setX(human->getX() + 1);
					}

					break;
				default:

					break;

				}

			}



		}

	}

};









void main() {
	
	srand(time(NULL));
	CJuego* a= new CJuego();
	a->jugar();

	system("pause>>NULL");

}