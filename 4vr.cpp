#include "stdafx.h"
#include <conio.h>
#include <iostream>
using namespace std;

enum Cell{
	EMPTY,
	RED,
	YELLOW,
	FIELD_WIDTH = 7,
	FIELD_HEIGHT = 6
};
class Field{//п0лё
private:
	Cell cells[FIELD_WIDTH][FIELD_HEIGHT];// Двумерный массив для хранения игрового поля
	bool isRedTurn;// Очередь хода
	Cell winner;// Кто на данный момент выиграл
	const int DIR_NUMBER = 4;
	const int di[4] = { 1, 0, 1, 1 };
	const int dj[4] = { 0, 1, -1, 1 };
	const int WIN_LENGTH = 4;

	void clear(bool isRedFirst) {//0чистка 
		isRedTurn = isRedFirst;
		winner = EMPTY;
		for (int i = 0; i<FIELD_WIDTH; i++)
			for (int j = 0; j<FIELD_HEIGHT; j++)
				cells[i][j] = EMPTY;
	}

	bool isWon(bool red) const {
		return red ? (winner == RED) : (winner == YELLOW);
	}

	void checkWinner() {
		for (int i = 0; i<FIELD_WIDTH; i++)
			for (int j = 0; j<FIELD_HEIGHT; j++) {
				Cell start = cells[i][j];
				if (start == EMPTY) continue;
				for (int dir = 0; dir<DIR_NUMBER; dir++) {
					int length = 0, iline = i, jline = j;
					while (++length < WIN_LENGTH) {
						iline += di[dir];
						jline += dj[dir];
						if (iline < 0 || iline >= FIELD_WIDTH ||
							jline < 0 || jline >= FIELD_HEIGHT)
							break;
						if (cells[iline][jline] != start) break;
					}
					if (length == WIN_LENGTH) {
						winner = start;
						return;
					}
				}
			}
	}
public:
	Field(bool isRedFirst) {
		clear(isRedFirst);
	}
	
	bool makeTurn(int column) {
		if (winner != EMPTY ||
			column < 1 || column > FIELD_WIDTH)
			return false;
		int i = column - 1;
		for (int j = 0; j<FIELD_HEIGHT; j++)
			if (cells[i][j] == EMPTY)
			{
				cells[i][j] = isRedTurn ? RED : YELLOW;
				checkWinner(); // Победа?
				isRedTurn = !isRedTurn;
				return true;
			}
		return false;
	}

	bool isOver() const {
		if (winner != EMPTY)
			return true;
		for (int i = 0; i<FIELD_WIDTH; i++)
			for (int j = 0; j<FIELD_HEIGHT; j++)
				// Если хоть одна ячейка свободна,
				// игра не окончена
				if (cells[i][j] == EMPTY)
					return false;
		// Все ячейки заняты
		return true;
	}

	bool isRedTurnNow() const {
		return isRedTurn;
	}

	void print() const {
		char sym[] = { '.', 'К', 'Ж' };
		int h = 1;
		cout << "  1 2 3 4 5 6 7" << endl<< "1 ";
		for (int j = FIELD_HEIGHT - 1; j >= 0; j--){
			for (int i = 0; i<FIELD_WIDTH; i++){
				cout << sym[cells[i][j]] << " ";
			}
			if (h < 6) cout << endl<<++h<<" ";
		}
		cout <<endl<< "  1 2 3 4 5 6 7" << endl;
	}

	void printResult() const {
		if (isWon(true)) cout << "Победил КРАСНЫЙ!!!" << endl;
		else if (isWon(false)) cout << "Победил ЖЕЛТЫЙ!!!" << endl;
		else if (isOver()) cout << "Все ячейки заняты. Ничья" << endl;
	}
};

void main(){
	setlocale(LC_ALL, "Russian");
	Field field(true);
	while (!field.isOver()){
		field.print();
		cout << "Ходит " <<(field.isRedTurnNow() ? "красный" : "желтый") <<" игрок, введите ход (1-7)" << endl;
		int column;
		cin >> column;
		field.makeTurn(column);
	}
	field.printResult();
	_getch();
}
